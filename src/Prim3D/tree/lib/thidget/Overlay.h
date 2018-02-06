#ifndef Overlay_INCLUDED
#define Overlay_INCLUDED

#pragma warning( disable : 4786 ) 

#include <vector>
using std::vector;

#include <windows.h>
#include <gl/GL.h>

#include <thunk/thunks.h>
#include <ptr/Ptr.h>

#include "Thidget.h"

struct Overlay {

  Overlay();

  void setOrtho(int width, int height,
		float left, float right, float bottom, float top);

  void addThidget(const Ptr<Thidget>&);
  void removeThidget(const Ptr<Thidget>&);

  bool mouse(int x, int y);
  void click(bool);
  void draw(WeakPtr<GLContext>&);

  private:

  Vec2<int> window_size;
  typedef vector<Ptr<Thidget> > Thidgets;
  Thidgets thidgets;
  int current_thidget;

  int width; int height;
  float left, right, bottom, top;
};

#endif

