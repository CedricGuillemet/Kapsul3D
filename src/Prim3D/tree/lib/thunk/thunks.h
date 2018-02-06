#ifndef thunk_INCLUDED
#define thunk_INCLUDED

#include <thunk/PtrClosure.h>
#include <thunk/Curry.h>
#include <thunk/Function.h>
#include <thunk/Thunk.h>


template <class Class, class Result>
Thunk0<Result> closure0(Class* c, Result (Class::*f)(void)) {

    return Thunk0<Result>(c, f);
}


template <class Class, class A1, class Result>
Thunk1<A1,Result> closure1(Class* c, Result (Class::*f)(const A1&)) {

    return Thunk1<A1,Result>(c, f);
}


template <class Class, class A1, class A2, class Result>
Thunk2<A1,A2,Result> closure2(Class* c, Result (Class::*f)(const A1&, const A2&)) {

    return Thunk2<A1,A2,Result>(c, f);
}


template <class A1, class Result>
Thunk0<Result> curry0(Result (*f)(const A1&), const A1& a1) {

  return Thunk0<Result>(f, a1);
}

template <class A1, class Result>
Thunk0<Result> curry0(const Thunk1<A1,Result>& t, const A1& a1) {

  return Thunk0<Result>(t, a1);
}



template <class A1, class A2, class Result>
Thunk1<A2, Result> curry1(Result (*f)(const A1&, const A2&), const A1& a1) {

  return Thunk1<A2,Result>(f, a1);
}

template <class A1, class A2, class Result>
Thunk1<A2, Result> curry1(const Thunk2<A1,A2,Result>& t, const A1& a1) {

  return Thunk1<A2,Result>(t, a1);
}


template <class A1, class A2, class A3, class Result>
Thunk2<A2, A3, Result> curry2(Result (*f)(const A1&, const A2&, const A3&), const A1& a1) {

    return Thunk2<A2,A3,Result>(f, a1);
}


template <class Result>
Thunk0<Result> function0(Result (*f)()) {

  return Thunk0<Result>(f);
}


template <class A1, class Result>
Thunk1<A1,Result> function1(Result (*f)(const A1&)) {

  return Thunk1<A1,Result>(f);
}


template <class A1, class A2, class Result>
Thunk2<A1,A2,Result> function2(Result (*f)(const A1&, const A2&)) {

  return Thunk2<A1,A2,Result>(f);
}


template <class A1, class A2, class A3, class Result>
Thunk3<A1,A2,A3,Result> function3(Result (*f)(const A1&, const A2&, const A3&)) {

  return Thunk3<A1,A2,A3,Result>(f);
}

#endif
