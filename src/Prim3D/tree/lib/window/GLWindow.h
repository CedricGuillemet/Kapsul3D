#ifndef GLWindow_INCLUDED
#define GLWindow_INCLUDED

#pragma warning ( disable : 4786 )


#include <windows.h>
#include <GL/gl.h>
#include <ptr/Ptr.h>
#include <window/Window.h>
#include <window/WGLContext.h>

#include <set>
using std::set;

#include <string>
using std::string;

#include <thigs/Vec2.h>
#include <thigs/Vec3.h>
#include <thigs/Vec4.h>

struct GLWindow : Window {

  GLWindow(const Ptr<WindowClass>&, 
	   const string& app_name, 
	   bool fullscreen = false);

  WeakPtr<GLContext> getContext();

  virtual void init();

 private:

  Ptr<GLContext> context;
};

#endif
