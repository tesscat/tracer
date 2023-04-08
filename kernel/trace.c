// #pragma OPENCL EXTENSION cl_khr_spir : enable
// #pragma OPENCL EXTENSION cl_khr_il_program : enable
//
// uint wang_hash(uint seed)
// {
//     seed = (seed ^ 61) ^ (seed >> 16);
//     seed *= 9;
//     seed = seed ^ (seed >> 4);
//     seed *= 0x27d4eb2d;
//     seed = seed ^ (seed >> 15);
//     return seed;
// }
//
// float rand(float seed) {
//   // pipe float p;
//   return wang_hash(4294967295*seed)/(float)4294967295;
// }
//
// double3 randSphPos(float seed) {
//   double3 out = {1, 1, 1};
//   out.z = seed;
//   while (length(out) > 1) {
//     out.x = rand(out.z);
//     out.y = rand(out.x);
//     out.z = rand(out.y);
//   }
//
//   return out;
// }

double2 fibLattice(double i, double N) {
  double x = i/1.618033988749;
  x = x - floor(x);
  return (double2){x, i/N};
}
double3 fibLatticeToUnitSphere(double2 pos) {
  double theta = 2*M_PI_F*pos.x;
  double orb = acos(1-2*pos.y);
  double sinorb = sin(orb);
  return (double3){cos(theta) * sinorb, sin(theta) * sinorb, cos(orb)};
}

double hitSphere(const double3 center, const double radius, const double3 rayOrig, const double3 rayDir) {
  double3 ac = rayOrig - center;
  double a = pow(length(rayDir), 2);
  double half_b = dot(ac, rayDir);
  double c = pow(length(ac), 2) - pow(radius, 2);
  double discriminant = pow(half_b, 2) - a * c;
  if (discriminant < 0) {return -1.0;}
  else {return (-half_b - sqrt(discriminant))/a;}
}
//
// typedef struct ColourTrace {
//   double16 rAlb;
//   double16 gAlb;
//   double16 bAlb;
//   double16 rEmi;
//   double16 gEmi;
//   double16 bEmi;
// } ColourTrace;

typedef struct State {
  global const double* sphereCenters;
  global const double* sphereRadii;
  global const double* materials;
  global const int* matIndexes;
  int sphCount;
  int subRays;
  // global uint* image;
  int idx;
  int maxDepth;
  int iters;
} State;
//
// typedef struct Ray {
//   ColourTrace trace;
//   double3 orig;
//   double3 dir;
// } Ray;
//
// subrays ^ (depth - 1) total iters
// iter / (subrays ^ (depth - 1) / subrays) floor of for first
// (iter % (sub ^ (depth - 1 - myDepth))) / / (subrays ^ (depth - 1 - myDepth) / subRays) floor for myDepth
//
// double3 finishTrace(ColourTrace trace, int bounces) {
//   double3 result = {0.0, 0.0, 0.0};
//   for (int i = bounces - 1; i >= 0; i--) {
//     result.x *= trace.rAlb[i];
//     result.y *= trace.gAlb[i];
//     result.z *= trace.bAlb[i];
//
//     result.x += trace.rEmi[i];
//     result.y += trace.gEmi[i];
//     result.z += trace.bEmi[i];
//   }
//   return result;
// }

// TODO: nicer recursion
double3 castRay(double3 orig_, double3 dir_,
  // const int sphCount,
  // global const double* sphereCenters,
  // global const double* sphereRadii,
  // global const double* materials,
  // global const int* materialIndexes,
  // ColourTrace trace,
  private State* state,
  // int depth,
  // int iters,
  // int subRays,
  int iter)
  // float seed)
{
  // if (depth >= state->maxDepth) {
  //   double3 final = finishTrace(trace, state->maxDepth);
  //   int imPos = state->idx * 4;
  //   atomic_add(&state->image[imPos], (uint)(final.x) * 4096);
  //   atomic_add(&state->image[imPos + 1], (uint)(final.y) * 4096);
  //   atomic_add(&state->image[imPos + 2], (uint)(final.z) * 4096);
  //   atomic_add(&state->contribCount[state->idx], 1);
  // }
  double16 rAlb;
  double16 gAlb;
  double16 bAlb;
  double16 rEmi;
  double16 gEmi;
  double16 bEmi;
  double3 orig = orig_;
  double3 dir = dir_;
  int i;
  // float rSeed = seed;
  for (i = 0; i < state->maxDepth; i++) {
    double3 result;
    double hit = -1;
    int hitIndex;
    double3 center;
    for (int i = 0; i < state->sphCount; i++) {
      int threei = 3 * i;
      double3 sphCenter = {state->sphereCenters[threei], state->sphereCenters[threei + 1], state->sphereCenters[threei + 2]};
      double hit2 = hitSphere(sphCenter, state->sphereRadii[i], orig, dir);
      if (hit2 > 0.0 && (hit2 < hit || hit < 0.0)) {
        hit = hit2;
        center = sphCenter;
        hitIndex = i;
      }
    }
    if (hit >= 0.0) {
      orig = dir * hit + orig;
      double3 norm = normalize(orig - center);

      // https://math.stackexchange.com/questions/13261/how-to-get-a-reflection-vector
      double3 outgoing = normalize(dir - (2 * dot(dir, norm)) * norm);
      // orig = hitPos;
      // dir = normalize(outgoing);

      int matIndex = state->matIndexes[hitIndex] * 12;

      double reflectionFactor = (state->materials[matIndex + 8]);
      double invRF = 1.0-reflectionFactor;
      double3 newNorm = (invRF) * norm + reflectionFactor * outgoing;
      newNorm = normalize(newNorm);
      // matIndex *= 12;
// subrays ^ (depth - 1) total iters
// iter / (subrays ^ (depth - 1) / subrays) floor of for first
// (iter % (sub ^ (depth - 1 - myDepth))) / (subrays ^ (depth - 1 - myDepth) / subRays) floor for myDepth
      // EVERYTHING IS DIFFUSE
      // result.x *= state->materials[matIndex];
      // result.y *= state->materials[matIndex + 1];
      // result.z *= state->materials[matIndex + 2];

      // result.x = state->materials[matIndex + 4];
      // result.y = state->materials[matIndex + 5];
      // result.z = state->materials[matIndex + 6];
      // double3 result = {0.0, 0.0, 0.0};
      // ColourTrace t2 = trace;
      rAlb[i] = state->materials[matIndex];
      gAlb[i] = state->materials[matIndex + 1];
      bAlb[i] = state->materials[matIndex + 2];

      rEmi[i] = state->materials[matIndex + 4];
      gEmi[i] = state->materials[matIndex + 5];
      bEmi[i] = state->materials[matIndex + 6];
      // queue_t default = get_default_queue();
      // ndrange_t range = ndrange_1D(1);
      // for (int i = 0; i < state->subRays; i++) {
      int fromHereCount = floor(state->iters/pow((double)state->subRays, i));
      double iterMod = iter % fromHereCount;
      double index = (iterMod * state->subRays) / fromHereCount;
      double idx = floor(index);
      double3 unitPoint = fibLatticeToUnitSphere(fibLattice(idx, state->subRays));
      // make it shrink
      double angleBetween = acos(dot(norm, outgoing));
      double blend = sin(angleBetween) * invRF;
      unitPoint *= blend;
      unitPoint += newNorm;
      dir = normalize(unitPoint);
      // if (invRF == 0) {dir = outgoing;};
        // enqueue_kernel(default, CLK_ENQUEUE_FLAGS_NO_WAIT, range, ^{castRay(hitPos, dir, trace, state, depth + 2)};)
        // result += castRay(hitPos, dir, t2, state, depth + 1);
      // }
      // result /= state->subRays;
      // is a sphere of one-tominusone
      // unitPoint.y += 1;
      // double3 unitDir = normalize(unitPoint);
      // // we suppose the normal is the new y
      // // so new x is cross
      // double3 newX = cross(norm, dir);
      // double3 newZ = cross(norm, newX);
      // dir = newX * unitDir.x + norm * unitDir.y + newZ * unitDir.z;
      // and tada new dir
      // orig = hitPos;

      
      // if (depth == 1) {return (double3){0.0,0.0, 0.0};}
      // double3 inbound;
      // if (depth > 1) {
        // inbound = castRay(orig, dir, sphCount, sphereCenters, sphereRadii, materials, materialIndexes, depth - 1);
      // } else {
        // inbound = (double3){0.0, 0.0, 0.0};
      // }


      // return inbound;
    } else {
      // t2.rAlb[depth] = state->materials[matIndex];
      // t2.gAlb[depth] = state->materials[matIndex + 1];
      // t2.bAlb[depth] = state->materials[matIndex + 2];
      // ColourTrace t2 = trace;
      // t2.rEmi[depth] = 0.1; // state->materials[matIndex + 4];
      // t2.gEmi[depth] = 0.1; // state->materials[matIndex + 5];
      // t2.bEmi[depth] = 0.1; // state->materials[matIndex + 6];
      //
      // double3 final = finishTrace(t2, depth);
      // int imPos = state->idx * 4;
      // atomic_add(&state->image[imPos], (uint)(final.x) * 4096);
      // atomic_add(&state->image[imPos + 1], (uint)(final.y) * 4096);
      // atomic_add(&state->image[imPos + 2], (uint)(final.z) * 4096);
      // atomic_add(&state->contribCount[state->idx], 1);
      // skybox time
      double elev = asin(dir.y);
      bEmi[i] = clamp(5.5 * elev, 0.2, 0.5);
      rAlb[i] = 0.0;
      gAlb[i] = 0.0;
      bAlb[i] = 0.0;
      rEmi[i] = 0.2;
      gEmi[i] = 0.2;
      // bEmi[i] = 0.1;
      break;
      // result.x = 0.1;
      // result.y = 0.1;
      // result.z = 0.1;
      // break;
      // return (double3){0.1, 0.1, 0.1};
    }
  }
  double r = 0.0;
  double g = 0.0;
  double b = 0.0;
  for (; i >= 0; i--) {
    r *= rAlb[i];
    r += rEmi[i];
    g *= gAlb[i];
    g += gEmi[i];
    b *= bAlb[i];
    b += bEmi[i];
  }
  return (double3){r, g, b};
  // return result;
}

// State state;
// TODO: figure out how to get double3s across
kernel void trace(
  const int width,
  const int height,
  int sphCount,
  global double* sphereCenters,
  global double* sphereRadii,
  global double* materials,
  global int* objMaterialIndexes,
  global double* image
)
{
  State state;
  // ColourTrace trace;
  state.materials = materials;
  state.sphereCenters = sphereCenters;
  state.matIndexes = objMaterialIndexes;
  state.sphereRadii = sphereRadii;
  state.sphCount = sphCount;
  // state.image = image;
  state.maxDepth = 4;
  const double focalLength = 1;
  double3 rayOrig = {0, 0, 0};

  // int bounceCount = 3;

  state.subRays = 20;

  int iters = pow((double)state.subRays, state.maxDepth - 1);
  state.iters = iters;

  // int passes = pow((float)state.subRays, bounceCount);

  int gid = get_global_id(0);
  state.idx = gid;
  double x = gid % width; 
  double y = height - (gid - x)/width; 
  double w = width; 
  double h = height;
  double3 pxPos = {(2*x)/w - 1, (2*y)/w - (h/w), focalLength};
  double3 rayDir = normalize(pxPos);
  
  double3 result = {0, 0, 0};

  // float seed;

  for (int i = 0; i < iters; i++) {
    // seed = wang_hash(4294967295 * (x/w) * i) + wang_hash(4294967295 * (y/h) * i);
    // result += castRay(rayOrig, rayDir, sphCount, sphereCenters, sphereRadii, materials, objMaterialIndexes, bounceCount, iters, subRays, i, seed);
    result += castRay(rayOrig, rayDir, &state, i); // , iters, i, seed);
  }

  result /= iters;
  // double3 result = castRay((double3){0, 0, 0}, (double3){0, 0, 0}, 0, NULL, NULL, NULL, NULL, 0);
  // double3 result;
  
  int id = gid * 4; 
  image[id] = result.x;
  image[id + 1] = result.y;
  image[id + 2] = result.z;
  image[id + 3] = 1.0;
}
