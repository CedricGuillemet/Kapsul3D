#ifndef PtrClosure_INCLUDED
#define PtrClosure_INCLUDED

#include <thunk/ThunkImp.h>

template <class R, class Result = Void>
struct PtrClosure0 : Thunk0Imp<Result> {

  PtrClosure0(R* receiver, Result (R::*function)(void)) 
    : r(receiver), f(function) {}
  PtrClosure0(const PtrClosure0<R,Result>& that) : r(that.r), f(that.f) {}

 private:

  virtual Result force() {return (r->*f)();}

  R* r;
  Result (R::*f)();
};


template <class R, class A1, class Result = Void>
struct PtrClosure1 : Thunk1Imp<A1, Result> {

  PtrClosure1(R* receiver, Result (R::*function)(const A1&)) 
    : r(receiver), f(function) {}
  PtrClosure1(const PtrClosure1<R, A1,Result>& that) : r(that.r), f(that.f) {}

 private:

  virtual Result force(const A1& a1) {
    return (r->*f)(a1);
  }

  R* r;
  Result (R::*f)(const A1&);
};



template <class R, class A1, class A2, class Result = Void>
struct PtrClosure2 : Thunk2Imp<A1, A2, Result> {

  PtrClosure2(R* receiver, Result (R::*function)(const A1&, const A2&)) 
    : r(receiver), f(function) {}
  PtrClosure2(const PtrClosure2<R, A1, A2, Result>& that) 
    : r(that.r), f(that.f) {}

 private:

  virtual Result force(const A1& a1, const A2& a2) {
    return (r->*f)(a1, a2);
  }

  R* r;
  Result (R::*f)(const A1&, const A2&);
};




#endif

