#ifndef Curry_INCLUDED
#define Curry_INCLUDED

#include <thunk/ThunkImp.h>

template <class F, class A1, class Result=Void>
struct Curry0 : Thunk0Imp<Result> {

  Curry0(const F& function, const A1& arg1) : f(function), a1(arg1) {}
  Curry0(const Curry0<F, A1, Result>& that) : f(that.f), a1(that.a1) {}

 private:

  virtual Result force() {return f(a1);}

  F f;
  A1 a1;
};



template <class F, class A1, class A2, class Result=Void>
struct Curry1 : Thunk1Imp<A2, Result> {

  Curry1(const F& function, const A1& arg1) : f(function), a1(arg1) {}
  Curry1(const Curry1<F, A1, A2, Result>& that) : f(that.f), a1(that.a1) {}

 private:

  virtual Result force(const A2& a2) {return f(a1, a2);}

  F f;
  A1 a1;
};



template <class F, class A1, class A2, class A3, class Result=Void>
struct Curry2 : Thunk2Imp<A2,A3,Result> {

  Curry2(const F& function, const A1& arg1) : f(function), a1(arg1) {}
  Curry2(const Curry2<F, A1, A2, A3, Result>& that) : f(that.f), a1(that.a1) {}

 private:

  virtual Result force(const A2& a2, const A3& a3) {return f(a1, a2, a3);}

  F f;
  A1 a1;
};


#endif
