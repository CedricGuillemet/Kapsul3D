#ifndef Thidget_INCLUDED
#define Thidget_INCLUDED

#include <windows.h>
#include <ptr/Ptr.h>
#include <thigs/GLContext.h>
#include <thigs/Vec2.h>


struct Thidget {

  Thidget();
  virtual ~Thidget();

  virtual void draw(WeakPtr<GLContext>&) = 0;
  virtual bool mouse(float x, float y);
  virtual void click(bool);
  void setVisible(bool);

 private:

  bool visible;

};


#endif
