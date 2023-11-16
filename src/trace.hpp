// #include "hipSYCL/sycl/libkernel/builtins.hpp"
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <valarray>
#include <vector>
#include <cmath>
#include <CL/sycl.hpp>

#include <vec.hpp>
#include <colour.hpp>

// #include <poly.hpp>

using double2 = Vec<double, 2>;
using double3 = Vec<double, 3>;

#define PI 3.14159265


template<typename T>
using ClArr = cl::sycl::accessor<T, 1, cl::sycl::access::mode::read>;


class Material {
public:
  Colour albedo;
  Colour emission;
  double reflection = 0.0;
  double translucency = 0.0;
  double refIndex = 1.0;
/*
  std::vector<double> Flatten() {
    std::vector<double> out = albedo.Flatten();
    std::vector<double> tmp = emission.Flatten();
    out.insert(out.end(), tmp.begin(), tmp.end());
    out.push_back(reflection);
    out.push_back(translucency);
    out.push_back(refIndex);
    return out;
  }
*/
};

class Sphere {
public:
  double3 center;
  double radius;
  int matIdx;
  Sphere(double3 center_, double radius_, int matIdx_) : center{center_}, radius{radius_}, matIdx{matIdx_} {}
  Sphere() = default;
};

// using double2 = Vec<double, 2>;
//
template<typename T, int len>
T dot(Vec<T, len> a, Vec<T, len> b) {
  T sum = 0;
  for (int i = 0; i < len; i++) {
    sum += a[i] * b[i];
  }
  return sum;
}


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

double hitSphere(const Sphere sphere, double3 rayOrig, const double3 rayDir) {
  double3 ac = rayOrig - sphere.center;
  double a = pow(rayDir.length(), 2);
  double half_b = dot(ac, rayDir);
  double c = pow(ac.length(), 2) - pow(sphere.radius, 2);
  double discriminant = pow(half_b, 2) - a * c;
  if (discriminant < 0) {return -1.0;}
  else {return (-half_b - sqrt(discriminant))/a;}
}

typedef struct State {
  ClArr<Sphere> spheres;
  ClArr<Material> materials;
  int sphCount;
  int subRays;
  int idx;
  int maxDepth;
  int iters;
} State;

typedef struct CachedPoint {
  double3 point;
  double3 indir;
  double brightness;
  double transmittance;
  bool hitSky;
  const Sphere* sphere;
} CachedPoint;


double absolute(double i) {
  if (i > 0) return i;
  return -i;
}
Colour EnvC (std::vector<double>({0.5, 0.5, 0.9}));
double getEnvLighting(double3 _orig, double3 dir, double wavelength) {
  return EnvC.Sample(wavelength);
  return 0.5; // Colour(std::vector<double>({0.0, 3.0, 0.5}));
}
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
      // hitIndex = i;
    }
  }
  return (DidWeHitSomethingInfo){.pos = hit, .sphere = sphere};
}

// TODO: nicer recursion
double castRay(
  State* state,
  int iter,
  double wavelength,
  CachedPoint cache[]
  )
{
  int backtrack = doCacheMath(state->subRays, state->maxDepth, iter);
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


  // std::vector<int> matInds (state->maxDepth);
  // matInds[0] = 0;
  // int matIndsIndex = 0;

  double3 contact_pt = backtrack_pt.point;
  double3 indir = backtrack_pt.indir;
  const Sphere* sphere = backtrack_pt.sphere;
  int i;
  bool first = true;
  
  for (i = (state->maxDepth - backtrack); (i < state->maxDepth); i++) {

    // Calculate where we hit a sphere
    // // ugly hack, TODO: make nicer
    // if (!first) {
    //   DidWeHitSomethingInfo hitInfo = didWeHitSomething(orig, dir, state->sphCount, state->spheres);
    // }


    // Assume we hit one (we did)
    // if (hitInfo.pos >= 0.0) {
    // Get material
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

    // Find where we hit
    // orig = dir * hitInfo.pos + orig;
    // Find the normal
    double3 norm = (contact_pt - sphere->center).normalized();

    // https://math.stackexchange.com/questions/13261/how-to-get-a-reflection-vector
    double3 outgoing = (indir - (norm * 2 * dot(indir, norm))).normalized();


    // and some extra stuff
    double reflectionFactor = mat.reflection;
    double invRF = 1.0-reflectionFactor;
    double3 newNorm = (norm * invRF + outgoing * reflectionFactor).normalized();
    double translucency = mat.translucency;

    
    
    // how many sub rays should we cast?
    int subRays = state->subRays;

    // ugly af maths to figure out which ray we're on
    int fromHereCount = floor(state->iters/pow((double)subRays, i));
    double iterMod = iter % fromHereCount;
    double index = (iterMod * subRays) / fromHereCount;
    double idx = floor(index);

    // TODO: better modelling for partially-transparent, partially-reflective materials
    
    // which index of ray should we start computing translucency?
    double translucency_thresh = ((double)subRays * (1.0 - translucency));
    if (idx < translucency_thresh) {
      // We're calculating a diffuse/reflect ray
      
      double3 unitPoint = fibLatticeToUnitSphere(fibLattice(idx, translucency_thresh));
      // make it shrink
      double angleBetween = acos(dot(norm, outgoing));
      double blend = sin(angleBetween) * invRF;
      unitPoint *= blend;
      unitPoint += newNorm;
      indir = unitPoint.normalized();
    } else {
      // refraction!!
      // TODO: diffraction with either Anne number or Sellmeier constants
      return 1.0;
      // EDITOR'S NOTE: i do not understand this
      // TODO: rewrite
      // get angle o incidence
      double incidence = std::acos(dot(norm, indir));
      // n1 sin i = n2 sin r moment
      // ie sin r = n1/n2 (sin i)

      // dir unchanged; point updated;
      // so like nothing actually happens
      // wait no! refraction time
      // n1 sin i = n2 sin r
      // n1 is current refIndex, n2 is new
      // i is incidence, and r is outgoing
      // therefore r = asin ((n1 sin i)/n2)
      //
      /*
      bool isEntering = dot(norm, indir) < 0;
      int newMatIndsIndex;
      if (isEntering) {
        newMatIndsIndex = matIndsIndex + 1;
        matInds[newMatIndsIndex] = matIndex;
      } else {
        newMatIndsIndex = matIndsIndex - 1;
      }
      //
      // BIG TODO: things like TIR
      // double incidence = acos(dot(norm, dir));
      double n1 = state->materials[matInds[matIndsIndex]].refIndex;
      double n2 = state->materials[matInds[newMatIndsIndex]].refIndex;
      // if (matIndex != lastMatInd) n2 = state->materials[matIndex + 8];
      // cope with air re-entry
      // we do need to do this better though
      // https://stackoverflow.com/questions/29758545/how-to-find-refraction-vector-from-incoming-vector-and-surface-normal
      // bool isEnteringMoreDense = n2 > n1;
      // double factor = (((double)isEnteringMoreDense) * 2) - 1j89aha1woh;
      // always alignes
      if (dot(norm, indir) > 0) {
        norm = (norm * (-1));
        double a = n1;
        n1 = n2;
        n2 = a;
      }
      double n = n1 / n2;
      // if (n != 1.0) {return (double3){1.0, 0.0, 0.0};}
      // n = 1.2/1;
      // n = 1;
      double cosI = -dot(norm, indir);
      double sinT2 = n * n * (1.0 - (cosI * cosI));
      if(sinT2 > 1.0) return 0.0; // TIR
      double cosT = sqrt(1.0 - sinT2);
      double3 outgoing = ((indir * n) + (norm * ((n * cosI) - cosT))).normalized();
      indir = outgoing;
      // refInd = n2;
      // TODO: don't abs uhh
      
      // // double outgoingAngle = asin((refInd/n2) * sin(incidence));
      // if (isEntering) {
      //   matIndsIndex += 1;
      //   matInds[matIndsIndex] = matIndex;
      // }
      // else matIndsIndex -= 1
      matIndsIndex = newMatIndsIndex; */
      
    }

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

    // } else {
    //   brightness += getEnvLighting(orig, dir, wavelength) * transmittance;
    //   CachedPoint pt;
    //   // pt.indir = dir;
    //   // pt.point = orig;
    //   // pt.transmittance = transmittance;
    //   pt.brightness = brightness;
    //   pt.hitSky = true;
    //   for (; (i < state->maxDepth); i++) {
    //     cache[i] = pt;
    //   }
    //
    //   break;
    // }
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
  double3 rayOrig = {0, 0, 0};

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

  CachedPoint cache[maxDepth];
  cache[0].indir = rayDir;
  // don't need to add rayOrig since is 0
  cache[0].point = rayDir * hitInfo.pos;
  cache[0].transmittance = 1.0;
  cache[0].brightness = 0.0;
  cache[0].hitSky = false;
  cache[0].sphere = hitInfo.sphere;

  for (int i = 0; i < iters; i++) {
    // double2 minorOffs = fibLattice(i, iters);
    // minorOffs *= (1/majorDim);
    result += castRay(&state, i, wavelength, cache);
  }

  result *= (1/(double)iters);

  image[gid] = result;
}
