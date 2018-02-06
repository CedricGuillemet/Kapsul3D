#ifndef Slider_INCLUDED
#define Slider_INCLUDED

#include <windows.h>

#include <thunk/thunks.h>
#include <thigs/thigs.h>

#include "Thidget.h"

struct Slider : Thidget {

  Slider(float minimum, float maximum, float init);

  void setThunk(const Thunk1<float>&);

  void setPos(float left, float right, float bottom, float top);

  void draw(WeakPtr<GLContext>&);

  bool mouse(float x, float y); // returns focus
  void click(bool);

 private:

  void build_rod();
  void build_knob();
  void build_colors();

  Thunk1<float> thunk;
  bool focus;
  float left, right, bottom, top;
  float minimum, maximum, value;
  float knob_pos;
  bool mouse_down;


  Vec3<float> rod_color;
  Vec2<float> rod_vertices[12];
  Vec3<float> rod_colors[12];

  Vec3<float> knob_color;

  Vec3<float> knob_colors[5];
  Vec2<float> knob_vertices[8];
};

#endif
