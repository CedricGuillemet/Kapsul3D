#ifndef Function_INCLUDED
#define Function_INCLUDED

#include <thunk/ThunkImp.h>

template <class Result=Void>
struct Function0 : Thunk0Imp<Result> {

  Function0(Result (*function)()) : f(function) {}
  Function0(const Function0<Result>& that) : f(that.f) {}

 private:

  virtual Result force() {return (*f)();}

  Result (*f)();
};



template <class A1, class Result=Void>
struct Function1 : Thunk1Imp<A1,Result> {

  Function1(Result (*function)(const A1&)) : f(function) {}
  Function1(const Function1<A1,Result>& that) : f(that.f) {}

 private:

  virtual Result force(const A1& a1) {return (*f)(a1);}

  Result (*f)(const A1&);
};



template <class A1, class A2, class Result=Void>
struct Function2 : Thunk2Imp<A1,A2,Result> {

  Function2(Result (*function)(const A1&, const A2&)) : f(function) {}
  Function2(const Function2<A1,A2,Result>& that) : f(that.f) {}

 private:

  virtual Result force(const A1& a1, const A2& a2) {return (*f)(a1, a2);}

  Result (*f)(const A1&, const A2&);
};


template <class A1, class A2, class A3, class Result=Void>
struct Function3 : Thunk3Imp<A1,A2,A3,Result> {

  Function3(Result (*function)(const A1&, const A2&, const A3&)) : f(function) {}
  Function3(const Function3<A1,A2,A3,Result>& that) : f(that.f) {}

 private:

  virtual Result force(const A1& a1, const A2& a2, const A3& a3) {
    return (*f)(a1,a2,a3);
  }

  Result (*f)(const A1&, const A2&, const A3&);
};


#endif
