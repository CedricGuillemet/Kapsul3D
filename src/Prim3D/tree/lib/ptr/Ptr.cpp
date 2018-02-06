#include "Ptr.h"


PtrRefBase::Refs* PtrRefBase::refs = 0;

int PtrRefBase::Init::count = 0;

PtrRefBase::~PtrRefBase() {

  assert(count==0);
  for (WeakPtrs::iterator i = weak_ptrs.begin();
       i!=weak_ptrs.end();
       ++i) {

    (*i)->invalidate();
  }
}





