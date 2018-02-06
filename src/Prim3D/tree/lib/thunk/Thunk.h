#ifndef Thunk_INCLUDED
#define Thunk_INCLUDED

#include <functional>

using std::less;
using std::equal_to;

#include <thunk/ThunkImp.h>
#include <thunk/PtrClosure.h>
#include <thunk/Curry.h>
#include <thunk/Function.h>

template <class Result = Void>
struct Thunk0 {

  template <class Class>
  Thunk0(Class* c, Result (Class::*f)(void)) {
    imp = new PtrClosure0<Class, Result>(c, f);
    ++(imp->ref);
  }

  template <class A1>
  Thunk0(Result (*f)(const A1&), const A1& a1) {
    imp = new Curry0<Result (*)(const A1&),A1,Result>(f, a1);
    ++(imp->ref);
  }


  template <class A1>
  Thunk0(const Thunk1<A1,Result>& t, const A1& a1) {
    imp = new Curry0<Thunk1<A1,Result>,A1,Result>(t, a1);
    ++(imp->ref);
  }

  Thunk0(Result (*f)()) {
    imp = new Function0<Result>(f);
    ++(imp->ref);
  }

  Thunk0() : imp(0) {}
  Thunk0(const Thunk0& that) {imp = that.imp; if (imp) ++(imp->ref);}

  Thunk0& operator=(const Thunk0& that) {
    if (that.imp) ++that.imp->ref;
    if (imp && --imp->ref==0) delete imp;
    imp = that.imp;
    return *this;
  }
  ~Thunk0() {
    if (imp && --imp->ref==0) delete imp;
  }

  Result operator() () const {
    if (imp) 
      return imp->force();
    else
      return Result();
  }

  operator bool() {return imp!=0;}

  friend inline bool operator==(const Thunk0& a, const Thunk0& b) {
    return equal_to<Thunk0Imp<Result>*>()(a.imp,b.imp);
  }
  friend inline bool operator<(const Thunk0& a, const Thunk0& b) {
    return less<Thunk0Imp<Result>*>()(a.imp,b.imp);
  }

 private:

  Thunk0Imp<Result>* imp;
};


template <class A1, class Result = Void>
struct Thunk1 {

  template <class Class>
  Thunk1(Class* c, Result (Class::*f)(const A1&)) {
    imp = new PtrClosure1<Class, A1, Result>(c, f);
    ++(imp->ref);
  }

  template <class T>
  Thunk1(Result (*f)(const T&, const A1&), const T& a) {
    imp = new Curry1<Result (*)(const T&, const A1&),T,A1,Result>(f, a);
    ++(imp->ref);
  }


  template <class T>
  Thunk1(const Thunk2<T,A1,Result>& t, const T& a) {
    imp = new Curry1<Thunk2<T,A1,Result>,T,A1,Result>(t, a);
    ++(imp->ref);
  }


  Thunk1(Result (*f)(const A1&)) {
    imp = new Function1<A1,Result>(f);
    ++(imp->ref);
  }


  Thunk1() : imp(0) {}
  Thunk1(const Thunk1& that) {imp = that.imp; if (imp) ++(imp->ref);}

  Thunk1& operator=(const Thunk1& that) {
    if (that.imp) ++that.imp->ref;
    if (imp && --imp->ref==0) delete imp;
    imp = that.imp;
    return *this;
  }
  ~Thunk1() {
    if (imp && --imp->ref==0) delete imp;
  }

  Result operator() (const A1& a1) const {
    if (imp) 
      return imp->force(a1);
    else
      return Result();
  }

  operator bool() {return imp!=0;}

  friend inline bool operator==(const Thunk1& a, const Thunk1& b) {
    return equal_to<Thunk1Imp<A1,Result>*>()(a.imp, b.imp);
  }
  friend inline bool operator<(const Thunk1& a, const Thunk1& b) {
    return less<Thunk1Imp<A1,Result>*>()(a.imp, b.imp);
  }    

 private:

  Thunk1Imp<A1,Result>* imp;

};



template <class A1, class A2, class Result = Void>
struct Thunk2 {

  template <class Class>
  Thunk2(Class* c, Result (Class::*f)(const A1&, const A2&)) {
    imp = new PtrClosure2<Class,A1,A2,Result>(c, f);
    ++(imp->ref);
  }

  template <class T>
  Thunk2(Result (*f)(const T&, const A1&, const A2&), const T& a) {
    imp = new Curry2<Result (*)(const T&, const A1&, const A2&),
                     T,A1,A2,Result>(f, a);
    ++(imp->ref);
  }


  template <class T>
  Thunk2(const Thunk3<T,A1,A2,Result>& t, const T& a) {
    imp = new Curry2<Thunk3<T,A1,A2,Result>,T,A1,A2,Result>(t, a);
    ++(imp->ref);
  }


  Thunk2(Result (*f)(const A1&, const A2&)) {
    imp = new Function2<A1,A2,Result>(f);
    ++(imp->ref);
  }


  Thunk2() : imp(0) {}
  Thunk2(const Thunk2& that) {imp = that.imp;	if (imp) ++(imp->ref);}
  Thunk2& operator=(const Thunk2& that) {
    if (that.imp) ++that.imp->ref;
    if (imp && --imp->ref==0) delete imp;
    imp = that.imp;
    return *this;
  }
  ~Thunk2() {
    if (imp && --imp->ref==0) delete imp;
  }

  Result operator() (const A1& a1, const A2& a2) const {
    if (imp) 
      return imp->force(a1,a2);
    else
      return Result();
  }

  operator bool() {return imp!=0;}

  friend inline bool operator==(const Thunk2& a, 
				const Thunk2& b) {
    return equal_to<Thunk2Imp<A1,A2,Result>*>()(a.imp,b.imp);
  }
  friend inline bool operator<(const Thunk2& a, 
			       const Thunk2& b) {
    return less<Thunk2Imp<A1,A2,Result>*>()(a.imp,b.imp);
  }

 private:

  Thunk2Imp<A1,A2,Result> *imp;

};


template <class A1, class A2, class A3, class Result = Void>
struct Thunk3 {

  Thunk3(Result (*f)(const A1&, const A2&, const A3&)) {
    imp = new Function3<A1,A2,A3,Result>(f);
    ++(imp->ref);
  }

  Thunk3() : imp(0) {}
  Thunk3(const Thunk3& that) {imp = that.imp;	if (imp) ++(imp->ref);}
  Thunk3& operator=(const Thunk3& that) {
    if (that.imp) ++that.imp->ref;
    if (imp && --imp->ref==0) delete imp;
    imp = that.imp;
    return *this;
  }
  ~Thunk3() {
    if (imp && --imp->ref==0) delete imp;
  }

  Result operator() (const A1& a1, const A2& a2, const A3& a3) const {
    if (imp) 
      return imp->force(a1,a2,a3);
    else
      return Result();
  }

  operator bool() {return imp!=0;}

  friend inline bool operator==(const Thunk3& a, 
				const Thunk3& b) {
    return equal_to<Thunk3Imp<A1,A2,A3,Result>*>()(a.imp,b.imp);
  }
  friend inline bool operator<(const Thunk3& a, 
			       const Thunk3& b) {
    return less<Thunk3Imp<A1,A2,A3,Result>*>()(a.imp,b.imp);
  }

 private:

  Thunk3Imp<A1,A2,A3,Result> *imp;

};

#endif

