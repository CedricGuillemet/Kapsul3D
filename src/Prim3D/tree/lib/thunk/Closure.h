#ifndef Closure_INCLUDED
#define Closure_INCLUDED

#include <thunk/ThunkImp.h>

template <class R, class Result = Void>
struct Closure0 : Thunk0Imp<Result> {

  Closure0(R& receiver, Result (R::*function)(void)) 
    : r(receiver), f(function) {}
  Closure0(const Closure0<R,Result>& that) : r(that.r), f(that.f) {}

 private:

  virtual Result force() {return (r.*f)();}

  R r;
  Result (R::*f)();
};


template <class R, class A1, class Result = Void>
struct Closure1 : Thunk1Imp<A1, Result> {

  Closure1(R& receiver, Result (R::*function)(const A1&)) 
    : r(receiver), f(function) {}
  Closure1(const Closure1<R, A1,Result>& that) : r(that.r), f(that.f) {}

 private:

  virtual Result force(const A1& a1) {
    return (r.*f)(a1);
  }

  R r;
  Result (R::*f)(const A1&);
};



template <class R, class A1, class A2, class Result = Void>
struct Closure2 : Thunk2Imp<A1, A2, Result> {

  Closure2(R& receiver, Result (R::*function)(const A1&, const A2&)) 
    : r(receiver), f(function) {}
  Closure2(const Closure2<R, A1, A2, Result>& that) : r(that.r), f(that.f) {}

 private:

  virtual Result force(const A1& a1, const A2& a2) {
    return (r.*f)(a1, a2);
  }

  R r;
  Result (R::*f)(const A1&, const A2&);
};




#endif

