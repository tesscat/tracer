#include "hipSYCL/sycl/libkernel/builtins.hpp"
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <valarray>
#include <vector>
#include <cmath>
#include <CL/sycl.hpp>

#include <vec.hpp>

#include <poly.hpp>

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

double hitSphere(Sphere sphere, double3 rayOrig, const double3 rayDir) {
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

// double3 refract(const double3 normal, const double3 incident, 
//                double n1, double n2) 
// {
//     const double n = n1 / n2;
//     const double cosI = -dot(normal, incident);
//     const double sinT2 = n * n * (1.0 - cosI * cosI);
//     if(sinT2 > 1.0) return (double3){0, 0}; // TIR
//     const double cosT = sqrt(1.0 - sinT2);
//     return n * incident + (n * cosI - cosT) * normal;
// }

double absolute(double i) {
  if (i > 0) return i;
  return -i;
}

Colour getEnvLighting(double3 _orig, double3 dir) {
  return Colour(std::vector<double>({0.0, 3.0, -3.0}));
  // return RGB({0.0, (dir.normalized()[1] + 1)*0.5, 0.0});
}

// TODO: nicer recursion
Colour castRay(double3 orig_, double3 dir_,
  State* state,
  int iter)
{
  Colour rayColour(1.0);
  Colour incomingLight(0.0);
  std::vector<Colour> albedo (state->maxDepth);
  std::vector<Colour> emission (state->maxDepth);

  std::vector<int> matInds (state->maxDepth);
  matInds[0] = 0;
  int matIndsIndex = 0;

  double3 orig = orig_;
  double3 dir = dir_;
  int i;

  for (i = 0; i < state->maxDepth; i++) {
    double3 result;
    double hit = -1;
    Sphere sphere;
    for (int i_ = 0; i_ < state->sphCount; i_++) {
      double hit2 = hitSphere(state->spheres[i_], orig, dir);
      if (hit2 > 0.0 && (hit2 < hit || hit < 0.0)) {
        hit = hit2;
        sphere = state->spheres[i_];
        // hitIndex = i;
      }
    }
    if (hit >= 0.0) {
      orig = dir * hit + orig;
      double3 norm = (orig - sphere.center).normalized();

      // https://math.stackexchange.com/questions/13261/how-to-get-a-reflection-vector
      double3 outgoing = (dir - (norm * 2 * dot(dir, norm))).normalized();

      int matIndex = sphere.matIdx;

      double reflectionFactor = (state->materials[matIndex].reflection);
      double invRF = 1.0-reflectionFactor;
      double3 newNorm = (norm * invRF + outgoing * reflectionFactor).normalized();

      incomingLight += rayColour * state->materials[matIndex].emission;
      rayColour *= state->materials[matIndex].albedo;

      int subRays = state->subRays;
      double trans = state->materials[matIndex].translucency;
      // subRays = (int)((double)subRays * (1.0 - trans));
      int fromHereCount = floor(state->iters/pow((double)subRays, i));
      double iterMod = iter % fromHereCount;
      double index = (iterMod * subRays) / fromHereCount;
      double idx = floor(index);

      double sR = ((double)subRays * (1.0 - trans));
      if (idx < sR) {
        // EVERYTHING IS DIFFUSE
        
        double3 unitPoint = fibLatticeToUnitSphere(fibLattice(idx, sR));
        // make it shrink
        double angleBetween = acos(dot(norm, outgoing));
        double blend = sin(angleBetween) * invRF;
        unitPoint *= blend;
        unitPoint += newNorm;
        dir = unitPoint.normalized();
      } else {
        // dir unchanged; point updated;
        // so like nothing actually happens
        // wait no! refraction time
        // n1 sin i = n2 sin r
        // n1 is current refIndex, n2 is new
        // i is incidence, and r is outgoing
        // therefore r = asin ((n1 sin i)/n2)
        //
        bool isEntering = dot(norm, dir) < 0;
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
        if (dot(norm, dir) > 0) {
          norm = (norm * (-1));
          double a = n1;
          n1 = n2;
          n2 = a;
        }
        double n = n1 / n2;
        // if (n != 1.0) {return (double3){1.0, 0.0, 0.0};}
        // n = 1.2/1;
        // n = 1;
        double cosI = -dot(norm, dir);
        double sinT2 = n * n * (1.0 - (cosI * cosI));
        if(sinT2 > 1.0) return Colour(0.0); // TIR
        double cosT = sqrt(1.0 - sinT2);
        double3 outgoing = ((dir * n) + (norm * ((n * cosI) - cosT))).normalized();
        dir = outgoing;
        // refInd = n2;
        // TODO: don't abs uhh
        
        // // double outgoingAngle = asin((refInd/n2) * sin(incidence));
        // if (isEntering) {
        //   matIndsIndex += 1;
        //   matInds[matIndsIndex] = matIndex;
        // }
        // else matIndsIndex -= 1
        matIndsIndex = newMatIndsIndex;
        
      }
      // lastMatInd = matIndex;
      // matInds[i + 1] = matIndex;
    } else {
      incomingLight += getEnvLighting(orig, dir) * rayColour;
      // emission[i].b = std::clamp(5.5 * elev, 0.2, 0.5);
      break;
    }
  }

  return incomingLight;
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
  // RGB* image,
  cl::sycl::accessor<Colour, 1, cl::sycl::access::mode::discard_write> image,
  // ClArr<RGB> image,
  int x,
  int y
)
{
  State state = (State){.materials = materials,
  .spheres = spheres,
  .sphCount = sphCount,
  .maxDepth = maxDepth,
  .subRays = subRays,
  };
  // state.materials = materials;
  // state.sphereCenters = sphereCenters;
  // state.matIndexes = objMaterialIndexes;
  // state.sphereRadii = sphereRadii;
  // state.sphCount = sphCount;
  // state.maxDepth = 4;
  const double focalLength = 1;
  double3 rayOrig = {0, 0, 0};

  // state.subRays = 5;

  int iters = pow((double)state.subRays, state.maxDepth - 1);
  state.iters = iters;

  int gid = y * width + x;
  double majorDim = fmax(height, width);
  state.idx = gid;
  // double x = gid % width; 
  // double y = height - (gid - x)/majorDim; 
  double w = width; 
  double h = height;
  double3 pxPos = {(2*x)/w - 1, (2*y)/w - (h/w), focalLength};
  double3 rayDir = pxPos.normalized();
  
  Colour result(0.0);

  for (int i = 0; i < iters; i++) {
    double2 minorOffs = fibLattice(i, iters);
    minorOffs *= (1/majorDim);
    result += castRay(rayOrig, ((double3){rayDir[0] + minorOffs[0], rayDir[1] + minorOffs[1], rayDir[2]}).normalized(), &state, i); // , iters, i, seed);
  }

  result *= (1/(double)iters);

  
  // int id = gid * 4; 
  // image[id] = result.x;
  // image[id + 1] = result.y;
  // image[id + 2] = result.z;
  // image[id + 3] = 1.0;
  // res.r -= std::min({res.r, 1.0});
  // res.g -= std::min({res.r, 1.0});
  // res.b -= std::min({res.r, 1.0});
  image[gid]= result; //  = RGB(result);
}
