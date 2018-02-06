#ifndef ThunkImp_INCLUDED
#define ThunkImp_INCLUDED

#pragma warning(disable:4786)
#pragma warning(disable:4800)

#include <thunk/Void.h>

template <class Result>
struct Thunk0;

template <class A1, class Result>
struct Thunk1;

template <class A1, class A2, class Result>
struct Thunk2;


template <class A1, class A2, class A3, class Result>
struct Thunk3;


template <class Result = Void>
struct Thunk0Imp {

  Thunk0Imp() : ref(0) {}
  virtual ~Thunk0Imp() {}

  friend struct Thunk0<Result>;

  protected:

  virtual Result force() = 0;

  private:

  int ref;
};


template <class A1, class Result = Void>
struct Thunk1Imp {

  Thunk1Imp() : ref(0) {}
  virtual ~Thunk1Imp() {}

  friend struct Thunk1<A1,Result>;

  protected:

  virtual Result force(const A1&) = 0;
  
  private:

  int ref;
};


template <class A1, class A2, class Result = Void>
struct Thunk2Imp {

  Thunk2Imp() : ref(0) {}
  virtual ~Thunk2Imp() {}

  friend struct Thunk2<A1,A2,Result>;

  protected:

  virtual Result force(const A1&, const A2&) = 0;

  private:
  
  int ref;
};


template <class A1, class A2, class A3, class Result = Void>
struct Thunk3Imp {

  Thunk3Imp() : ref(0) {}
  virtual ~Thunk3Imp() {}

  friend struct Thunk3<A1,A2,A3,Result>;

  protected:

  virtual Result force(const A1&, const A2&, const A3&) = 0;

  private:

  int ref;
};


#endif
