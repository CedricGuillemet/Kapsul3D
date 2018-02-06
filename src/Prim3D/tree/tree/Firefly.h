#ifndef Firefly_INCLUDED
#define Firefly_INCLUDED

#include <windows.h>
#include <ptr/Ptr.h>

#include <thigs/Vec3.h>
#include <thigs/Vec4.h>
#include <thigs/Color.h>
#include <thigs/GLContext.h>

struct Firefly {

  Firefly();

  Vec3<float> pos;
  Vec3<float> vel;
  Vec4<float> c;

  void move(float dt);
  void draw(WeakPtr<GLContext>&);

  float range;

  HSVA hsva;

};

#endif
