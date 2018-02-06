#ifndef WGLContext_INCLUDED
#define WGLContext_INCLUDED

#pragma warning ( disable : 4786 )

#include <windows.h>
#include <thigs/GLContext.h>

struct WGLContext : GLContext {

  WGLContext(HWND hwnd);
  virtual ~WGLContext();

  virtual void grab();
  virtual void release();
  virtual void swapBuffers();

  HWND hwnd;
  HDC hdc;
  HGLRC hglrc;

  static HGLRC current_context;

};

#endif
