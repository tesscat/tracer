// #include "hipSYCL/sycl/libkernel/builtins.hpp"
#include "resources/material.hpp"
#include "resources/sphere.hpp"
#include "utils/math.hpp"
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <math.h>
#include <optional>
#include <valarray>
#include <vector>
#include <cmath>
#include <CL/sycl.hpp>

#include <utils/vec.hpp>
#include <resources/colour.hpp>
#include <trace.hpp>

using double2 = Vec<double, 2>;
using double3 = Vec<double, 3>;

#define PI 3.14159265

using namespace tracer::colour;

// fibLattice stuff {{{

double2 fibLattice(double i, double N) {
    double x = i/1.618033988749;
    x = x - floor(x);
    return (double2){x, i/N};
}


double3 fibLatticeToUnitSphere(double2 pos) {
    double theta = 2*PI*pos[0];
    double orb = acos(1-2*pos[1]);
    double sinorb = sin(orb);
    return (double3){cos(theta) * sinorb, sin(theta) * sinorb, cos(orb)};
}

// }}}

// hit stuff {{{
double hitSphere(const Sphere sphere, double3 rayOrig, const double3 rayDir) {
    double3 ac = rayOrig - sphere.center;
    double a = pow(rayDir.length(), 2);
    double half_b = ac.dot(rayDir);
    double c = pow(ac.length(), 2) - pow(sphere.radius, 2);
    double discriminant = pow(half_b, 2) - a * c;
    if (discriminant < 0) {return -1.0;}
    else {return (-half_b - sqrt(discriminant))/a;}
}

struct DidWeHitSomethingInfo {
    double pos;
    const Sphere* sphere;
};

DidWeHitSomethingInfo didWeHitSomething(double3 orig, double3 dir, int sphCount, ClArr<Sphere> spheres) {
    // Calculate where we hit a sphere
    double hit = -1;
    const Sphere* sphere;
    for (int i_ = 0; i_ < sphCount; i_++) {
        double hit2 = hitSphere(spheres[i_], orig, dir);
        if (hit2 > 0.0 && (hit2 < hit || hit < 0.0)) {
            hit = hit2;
            sphere = &spheres[i_];
        }
    }
    return (DidWeHitSomethingInfo){.pos = hit, .sphere = sphere};
}

// }}}

typedef struct State {
    ClArr<Sphere> spheres;
    ClArr<Material> materials;
    int sphCount;
    int subRays;
    int idx;
    int maxDepth;
    int iters;
} State;


// cache stuff {{{
typedef struct CachedPoint {
    double3 point;
    double3 indir;
    double brightness;
    double transmittance;
    bool hitSky;
    size_t rfCacheStartPoint;
    const Sphere* sphere;
} CachedPoint;

typedef struct RefractionCachedPoint {
    size_t materialIndex;
} RefractionCachedPoint;

// TODO: should I just use tick increments? probably. Will I? no.
int doCacheMath(int subRays, int maxDepth, int iter) {
    // complicated. good luck figuring this out
    // draw up a tree diagram lol
    // this tries to work out, for a given iteration i,
    // how far it deviates (in nodes from the end) from the previous
    //
    // Check if it lies on a boundary, if so, which one?
    // TODO: cache POW calls for easier (cheap) thingys
    for(int i = 1; i < maxDepth; i++) {
        int groupSize = std::pow(subRays, i);
        // we're really just checking if iter is a multiple
        // TODO: why +1?
        if ((iter % groupSize) != 0) {return i + 1;}
    }
    return maxDepth;
}

// }}}

double getEnvLighting(double3 _orig, double3 dir, double wavelength) {
    auto dotprod = dir.normalized().dot({0.0, 1.0, 0.0});
    double angle = std::acos(dotprod);
    return Colour({0.3, 0.3}).Sample(wavelength)*(angle) + Colour({0.0, 0.0}).Sample(wavelength)*(PI-angle);
}

double3 reflect (const double3 normal, const double3 incident) {
    const double cosI = -normal.dot(incident);
    return incident + normal*(2.0*cosI);
}
double3 refract(const double3 normal, const double3 incident, double n1, double n2) {
    const double n = n1/n2;
    if (n == 1.0) { return incident; }
    const double cosI = -normal.dot(incident);
    const double sinT2 = n*n*(1.0 - cosI*cosI);
    if (sinT2 > 1.0) {
        // return reflect(normal, incident);
        return normal*0.0;
    }
    const double cosT = sqrt(1.0 - sinT2);
    return incident*n + normal*(n*cosI - cosT);
}

// normal points from n1 to n2
// double3 refract(const double3 normal, const double3 incident, double n1, double n2) {
//     double ni = normal.dot(incident);
//     double ni2 = ni*ni;
//     double mew = n1/n2;
//     double mew2 = mew*mew;
//     double mew2sqbr = mew2*(1.0 - ni2);
//     if (mew2sqbr > 1.0) {
//         // TIR
//         return normal*0;
//     }
//     double under_sqrt = 1.0 - mew2sqbr;
//     double sq = sqrt(under_sqrt);
//     double3 nsq = normal*sq;
//     double3 mewi = incident*mew;
//     double3 mewnni = normal*(mew*ni);
//     return mewi + nsq - mewnni;
// }


// TODO: nicer recursion
double castRay(
    State* state,
    int iter,
    double wavelength,
    CachedPoint cache[],
    RefractionCachedPoint rfCache[]
)
{
    const int backtrack = doCacheMath(state->subRays, state->maxDepth, iter);
    CachedPoint backtrack_pt = cache[state->maxDepth - backtrack];

    // we only need to run backtrack iterations! wooo!!
    // accumulated brightness so far
    double brightness = backtrack_pt.brightness;
    // how much of the light from here makes it back
    // fully dependant on albedo
    double transmittance = backtrack_pt.transmittance;

    if (backtrack_pt.hitSky) {
        return brightness;
    }

    double3 contact_pt = backtrack_pt.point;
    double3 indir = backtrack_pt.indir;
    const Sphere* sphere = backtrack_pt.sphere;
    int rfStartPoint = backtrack_pt.rfCacheStartPoint;
    int i;
    bool first = true;

    const int subRays = state->subRays;

    for (i = (state->maxDepth - backtrack); (i < state->maxDepth); i++) {

        int matIndex = sphere->matIdx;
        Material mat = state->materials[matIndex];
        // How much does this light add to us?
        //            how much this thing emits       * how much makes it back
        brightness += mat.emission.Sample(wavelength) * transmittance;
        transmittance *= mat.albedo.Sample(wavelength);
        // if no transmittance, no point simulating further
        if (transmittance <= 0.0) break;
        // or if no next iter
        if ((i + 1) == state->maxDepth) break;

        // Find the normal
        double3 norm = (contact_pt - sphere->center).normalized();
        double dot_norm_indir = norm.dot(indir);


        double translucency = mat.translucency;


        // ugly af maths to figure out which ray we're on
        int fromHereCount = floor(state->iters/pow((double)subRays, i));
        double iterMod = iter % fromHereCount;
        double index = (iterMod * subRays) / fromHereCount;
        double idx = floor(index);

        // TODO: better modelling for partially-transparent, partially-reflective materials

        // which index of ray should we start computing translucency?
        double translucency_thresh = ((double)subRays * (1.0 - translucency));
        if (idx < translucency_thresh && matIndex != 2 && false) {
            // We're calculating a diffuse/reflect ray
            // TODO: use reflect() for this
            // https://math.stackexchange.com/questions/13261/how-to-get-a-reflection-vector
            const double3 outgoing = (indir - (norm * 2 * dot_norm_indir)).normalized();

            // and some extra stuff
            const double reflectionFactor = mat.reflection;
            const double invRF = 1.0-reflectionFactor;
            const double3 newNorm = (norm * invRF + outgoing * reflectionFactor).normalized();

            double3 unitPoint = fibLatticeToUnitSphere(fibLattice(idx, translucency_thresh));
            // make it shrink
            const double angleBetween = acos(norm.dot(outgoing));
            const double blend = sin(angleBetween) * invRF;
            unitPoint *= blend;
            unitPoint += newNorm;
            indir = unitPoint.normalized();
        } else {
            // refraction!!
            // TODO: diffraction with either Anne number or Sellmeier constants
            double3 normal = norm;
            const bool isEntering = dot_norm_indir > 0.0;
            if (!isEntering) {
                // flip normal
                normal *= -1;
            }
            // n1 is material we are in
            double n1, n2;
            
            // since normal points from n1 to n2, n1 is always the material we hit
            // n1 = mat.refract.Calculate(wavelength);
            // n2 = state->materials[rfCache[rfStartPoint-1].materialIndex].refract.Calculate(wavelength);
            // if we're entering, its rfStart - 1
            if (isEntering) {
                int n1_idx = rfCache[rfStartPoint - 1].materialIndex;
                n1 = state->materials[n1_idx].refract.Calculate(wavelength);
                n2 = mat.refract.Calculate(wavelength);
                // push to the stack
                rfCache[rfStartPoint].materialIndex = matIndex;
                rfStartPoint += 1;
            } else {
                n1 = mat.refract.Calculate(wavelength);
                int n2_idx = rfCache[rfStartPoint - 1].materialIndex;
                n2 = state->materials[n2_idx].refract.Calculate(wavelength);
                // pop from the stack
                rfStartPoint -= 1;
            }




            // okay now do the math
            indir = refract(normal.normalized(), indir.normalized(), n2, n1);
        }

        // TODO: blend between translucent and non-translucent better

        // Okay, now calculate for next iter where we hit
        DidWeHitSomethingInfo hitInfo = didWeHitSomething(contact_pt, indir, state->sphCount, state->spheres);
        if (hitInfo.pos <= 0.0) {
            // no hit
            brightness += getEnvLighting(contact_pt, indir, wavelength) * transmittance;
            CachedPoint pt;
            // pt.indir = dir;
            // pt.point = orig;
            // pt.transmittance = transmittance;
            pt.brightness = brightness;
            pt.hitSky = true;
            for (i += 1; (i < state->maxDepth); i++) {
                cache[i] = pt;
            }
            break;
        }
        // recompute
        contact_pt = (indir * hitInfo.pos) + contact_pt;
        sphere = hitInfo.sphere;
        cache[i+1].brightness = brightness;
        cache[i+1].transmittance = transmittance;
        cache[i+1].hitSky = false;
        cache[i+1].point = contact_pt;
        cache[i+1].sphere = sphere;
        cache[i+1].indir = indir;
        cache[i+1].rfCacheStartPoint = rfStartPoint;
    }

    return brightness;
}

// TODO: figure out how to get double3s across
void trace(
    const int width,
    const int height,
    const int maxDepth,
    const int subRays,
    int sphCount,
    ClArr<Sphere> spheres,
    ClArr<Material> materials,
    cl::sycl::accessor<double, 1, cl::sycl::access::mode::discard_write> image,
    int x,
    int y,
    double wavelength
)
{
    State state = (State){
        .spheres = spheres,
        .materials = materials,
        .sphCount = sphCount,
        .subRays = subRays,
        .maxDepth = maxDepth,
    };
    const double focalLength = 1;
    // TODO: with 0 we get weird dead pixels. why?
    double3 rayOrig = {0.00001, 0.00001, 0.00001};

    int iters = pow((double)state.subRays, state.maxDepth - 1);
    state.iters = iters;

    int gid = y * width + x;
    double majorDim = fmax(height, width);
    state.idx = gid;
    double w = width; 
    double h = height;
    double3 pxPos = {(2*x)/w - 1, (2*y)/w - (h/w), focalLength};
    double3 rayDir = pxPos.normalized();

    double result = 0.0;

    DidWeHitSomethingInfo hitInfo = didWeHitSomething(rayOrig, rayDir, state.sphCount, state.spheres);
    if (hitInfo.pos <= 0.0) {
        image[gid] = getEnvLighting(rayOrig, rayDir, wavelength);
        return;
    }

    CachedPoint* cache = new CachedPoint[maxDepth];
    cache[0].indir = rayDir;
    // don't need to add rayOrig since is 0
    cache[0].point = rayDir * hitInfo.pos;
    cache[0].transmittance = 1.0;
    cache[0].brightness = 0.0;
    cache[0].hitSky = false;
    cache[0].sphere = hitInfo.sphere;
    cache[0].rfCacheStartPoint = 1;

    RefractionCachedPoint* rfCache = new RefractionCachedPoint[maxDepth];
    // mat 0 is air
    rfCache[0].materialIndex = 0;

    for (int i = 0; i < iters; i++) {
        result += castRay(&state, i, wavelength, cache, rfCache);
    }

    result *= (1/(double)iters);

    image[gid] = result;
}

// #endif
