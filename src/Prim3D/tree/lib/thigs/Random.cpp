#include "Random.h"

#include <math.h>

const double Random::a = 16807.0;
const double Random::m = 2147483647.0;

Random::operator double() {

    double t = a * seed;
    seed = t - m * floor(t/m);

    return seed/m;
}
