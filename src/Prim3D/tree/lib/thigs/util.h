#ifndef constants_INCLUDED
#define constants_INCLUDED

#include <stdlib.h>
#include <utility>
using std::pair;

static const double pi = 3.14159265358979323846;
inline double degToRad(double d) {return d * pi / 180.0;}
inline double radToDeg(double r) {return r * 180.0 / pi;}
inline float degToRad(float d) {return d * float(pi) / 180.0f;}
inline float radToDeg(float r) {return r * 180.0f / float(pi);}

inline pair<int,int> quotrem(int n, int d) {

  div_t qr = div(n, d);

  if (qr.rem<0) {
    --qr.quot;
    qr.rem += d;
  }

  return pair<int,int>(qr.quot,qr.rem);
}

template <class T>
inline T clamp(T a, T min, T max) {

  if (a<min) return min;
  if (a>max) return max;
  return a;
}

pair<double,double> sincos(double degrees);

#endif
