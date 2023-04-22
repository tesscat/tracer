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

typedef struct State {
  global const double* sphereCenters;
  global const double* sphereRadii;
  global const double* materials;
  global const int* matIndexes;
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

// TODO: nicer recursion
double3 castRay(double3 orig_, double3 dir_,
  private State* state,
  int iter)
{
  double16 rAlb;
  double16 gAlb;
  double16 bAlb;
  double16 rEmi;
  double16 gEmi;
  double16 bEmi;

  int16 matInds;
  matInds[0] = 0;
  int matIndsIndex = 0;

  double3 orig = orig_;
  double3 dir = dir_;
  int i;
  // double refInd = 1.0;
  // int lastMatInd = -1;

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

      int matIndex = state->matIndexes[hitIndex] * 9;

      double reflectionFactor = (state->materials[matIndex + 6]);
      double invRF = 1.0-reflectionFactor;
      double3 newNorm = (invRF) * norm + reflectionFactor * outgoing;
      newNorm = normalize(newNorm);

      rAlb[i] = state->materials[matIndex];
      gAlb[i] = state->materials[matIndex + 1];
      bAlb[i] = state->materials[matIndex + 2];

      rEmi[i] = state->materials[matIndex + 3];
      gEmi[i] = state->materials[matIndex + 4];
      bEmi[i] = state->materials[matIndex + 5];


      // translucency
      int subRays = state->subRays;
      double trans = state->materials[matIndex + 7];
      // subRays = (int)((double)subRays * (1.0 - trans));
      int fromHereCount = floor(state->iters/pow((double)subRays, i));
      double iterMod = iter % fromHereCount;
      double index = (iterMod * subRays) / fromHereCount;
      double idx = floor(index);
      // int contRays = state->subRays * trans;
      // get all the regulars out of the way first
      double sR = ((double)subRays * (1.0 - trans));
      if (idx < sR) {

  // subrays ^ (depth - 1) total iters
  // iter / (subrays ^ (depth - 1) / subrays) floor of for first
  // (iter % (sub ^ (depth - 1 - myDepth))) / (subrays ^ (depth - 1 - myDepth) / subRays) floor for myDepth
        
        // EVERYTHING IS DIFFUSE
        
        
        double3 unitPoint = fibLatticeToUnitSphere(fibLattice(idx, sR));
        // make it shrink
        double angleBetween = acos(dot(norm, outgoing));
        double blend = sin(angleBetween) * invRF;
        unitPoint *= blend;
        unitPoint += newNorm;
        dir = normalize(unitPoint);
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
        double n1 = state->materials[matInds[matIndsIndex] * 9 + 8];
        double n2 = state->materials[matInds[newMatIndsIndex] * 9 + 8];
        // if (matIndex != lastMatInd) n2 = state->materials[matIndex + 8];
        // cope with air re-entry
        // we do need to do this better though
        // https://stackoverflow.com/questions/29758545/how-to-find-refraction-vector-from-incoming-vector-and-surface-normal
        // bool isEnteringMoreDense = n2 > n1;
        // double factor = (((double)isEnteringMoreDense) * 2) - 1;
        // always alignes
        if (dot(norm, dir) > 0) {
          norm = -norm;
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
        if(sinT2 > 1.0) return (double3){1.0, 0, 0}; // TIR
        double cosT = sqrt(1.0 - sinT2);
        double3 outgoing = normalize((n * dir) + (((n * cosI) - cosT) * norm));
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
      // skybox time
      double elev = asin(dir.y);
      bEmi[i] = clamp(5.5 * elev, 0.2, 0.5);
      rAlb[i] = 0.0;
      gAlb[i] = 0.0;
      bAlb[i] = 0.0;
      rEmi[i] = 0.2;
      gEmi[i] = 0.2;
      break;
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
}

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
  state.materials = materials;
  state.sphereCenters = sphereCenters;
  state.matIndexes = objMaterialIndexes;
  state.sphereRadii = sphereRadii;
  state.sphCount = sphCount;
  state.maxDepth = 4;
  const double focalLength = 1;
  double3 rayOrig = {0, 0, 0};

  state.subRays = 5;

  int iters = pow((double)state.subRays, state.maxDepth - 1);
  state.iters = iters;

  int gid = get_global_id(0);
  double majorDim = max(height, width);
  state.idx = gid;
  double x = gid % width; 
  double y = height - (gid - x)/majorDim; 
  double w = width; 
  double h = height;
  double3 pxPos = {(2*x)/w - 1, (2*y)/w - (h/w), focalLength};
  double3 rayDir = normalize(pxPos);
  
  double3 result = {0, 0, 0};

  for (int i = 0; i < iters; i++) {
    double2 minorOffs = fibLattice(i, iters);
    minorOffs /= majorDim;
    result += castRay(rayOrig, normalize((double3){rayDir.x + minorOffs.x, rayDir.y + minorOffs.y, rayDir.z}), &state, i); // , iters, i, seed);
  }

  result /= iters;
  
  int id = gid * 4; 
  image[id] = result.x;
  image[id + 1] = result.y;
  image[id + 2] = result.z;
  image[id + 3] = 1.0;
}
