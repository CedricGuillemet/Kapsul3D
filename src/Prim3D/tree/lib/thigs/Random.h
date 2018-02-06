#ifndef Random_INCLUDED
#define Random_INCLUDED

struct Random {

  explicit Random(double s = 1.0) : seed(s) {}

  operator double();

 private:

  double seed;

  static const double a;
  static const double m;
};

#endif
