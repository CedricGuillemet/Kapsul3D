#include "stdafx.h"
#include <math.h>
#include "BranchNoise.h"

#pragma warning( disable : 4244 )

Random BranchNoise::random;

BranchNoise::BranchNoise() : left(0), right(0) {

  branch_noise = random;

}

BranchNoise::~BranchNoise() {

  delete left;
  delete right;
}


BranchNoise* BranchNoise::getLeft() {

  if (!left) left = new BranchNoise();

  return left;
}

BranchNoise* BranchNoise::getRight() {

  if (!right) right = new BranchNoise();

  return right;
}


