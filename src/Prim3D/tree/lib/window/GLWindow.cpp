#include "GLWindow.h"

#include <GL/gl.h> 
#include <util/util.h>

GLWindow::GLWindow(const Ptr<WindowClass>& wc, const string& an, bool fs) 
  : Window(wc, an, fs) {

}


void GLWindow::init() {

  Window::init();
  
  context = new WGLContext(hwnd);
}


WeakPtr<GLContext> GLWindow::getContext() {

  return context;
}
