#ifndef Picture_INCLUDED
#define Picture_INCLUDED

#include <windows.h>
#include <ptr/Ptr.h>
#include <thigs/Texture.h>

#include <thidget/Thidget.h>

struct Picture : Thidget {

  Picture(const Ptr<Texture>&);

  void setPos(float left, float right, float bottom, float top);
  void draw(WeakPtr<GLContext>&);

 private:

  float left;
  float right;
  float bottom;
  float top;
  Ptr<Texture> texture;
  WeakPtr<GLContext> context;

};

#endif
