#ifndef Branch_INCLUDED
#define Branch_INCLUDED

//#include <windows.h>

//#include <ptr/Ptr.h>
//#include <thigs/thigs.h>
#include "BranchNoise.h"

struct Tree;
class Branches;
struct Leaves;

struct Branch {

  Branch(const Tree&, Branches&, Leaves&, BranchNoise*);
  Branch(const Tree&, Branches&, Leaves&, BranchNoise*,
	 const CKMatrix&,
	 double texcoord_y,
	 double twist,
	 double decay,
	 int level,int StartInd);
  ~Branch();

  void build(const Tree&,
	     Branches&,
	     Leaves&,
	     BranchNoise*,
	     const CKMatrix&,
	     double texcoord_y,
	     double twist,
	     double decay,
	     int level,int StartInd);

  int* lower;
  int* upper;

  Branch* left;
  Branch* right;

};

#endif
