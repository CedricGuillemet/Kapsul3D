#ifndef Window_INCLUDED
#define Window_INCLUDED

#include <windows.h>

#include <ptr/Ptr.h>

#include <window/WindowClass.h>

struct Window {

  Window(const Ptr<WindowClass>&, const string& app_name, bool fullscreen=false);
  virtual ~Window();

  virtual LRESULT CALLBACK callback(HWND hwnd, UINT, WPARAM, LPARAM);

  virtual bool checkHide();

  virtual void leftMouse(bool);
  virtual void rightMouse(bool);
  virtual void mouse(int x, int y);
  virtual void init();
  virtual void show(int);

protected:

  bool hidden;
  HWND hwnd;

private:

  Ptr<WindowClass> window_class;
  string app_name;

  static int watch_x;
  bool left_mouse, right_mouse;

  bool fullscreen;
};

#endif
