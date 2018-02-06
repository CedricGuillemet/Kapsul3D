#include "util.h"

#include <math.h>

static double* table = 0;

static void initTable() {

  table = new double[901];
  for (int a = 0; a<901; ++a) {
    double rad = degToRad(double(a)*0.1);
    table[a] = sin(rad);
  }
}


static pair<double,double> sincosTenths(int tenths) {

  tenths = quotrem(tenths,3600).second;

  pair<double,double> qt = quotrem(tenths,900);
  int quadrant = qt.first;
  int theta = qt.second;
  switch(quadrant) {
  case 0:
    return pair<double,double>(table[theta], table[900-theta]);
  case 1:
    return pair<double,double>(table[900-theta], -table[theta]);
  case 2:
    return pair<double,double>(-table[theta], -table[900-theta]);
  case 3:
    return pair<double,double>(-table[900-theta], table[theta]);
  }

  abort(); // shouldn't happen  
}
    

pair<double,double> sincos(double degrees) {

  if (table==0) initTable();

  double tenths = degrees*10.0;

  double tenths_floor = floor(tenths);
  double u = tenths - tenths_floor;

  int t1 = int(tenths_floor);
  int t2 = t1 + 1;

  pair<double,double> sc1 = sincosTenths(t1);
  pair<double,double> sc2 = sincosTenths(t2);

  double s = sc1.first * (1.0-u) + sc2.first * u;
  double c = sc1.second * (1.0-u) + sc2.second * u;

  return pair<double,double>(s,c);
}
