
#include <window/Window.h>

Window::Window(const Ptr<WindowClass>& wc, const string& an, bool fs) 
  : window_class(wc), 
    app_name(an), 
    hidden(true), 
    left_mouse(false),
    right_mouse(false),
    fullscreen(fs),
    hwnd(0) {

    window_class->registerWindowClass();
}

 
Window::~Window() {

  if (hwnd) {
    bool success = DestroyWindow(hwnd);
    assert(success);
    window_class->removeWindow(hwnd, this);
  }
  ChangeDisplaySettings(NULL, 0); //dh this returns origonal display settings
}


bool Window::checkHide() {return true;}

void Window::leftMouse(bool) {}
void Window::rightMouse(bool) {}
void Window::mouse(int, int) {}

int Window::watch_x = 0;

LRESULT CALLBACK Window::callback(HWND hwnd, 
				  UINT iMsg, 
				  WPARAM wParam, 
				  LPARAM lParam) {

  switch (iMsg) {

  case WM_LBUTTONDOWN:
    left_mouse = true;
    SetCapture(hwnd);
    leftMouse(true);
    break;

  case WM_LBUTTONUP:
    left_mouse = false;
    leftMouse(false);
    if (!right_mouse) ReleaseCapture();
    break;

  case WM_RBUTTONDOWN:
    right_mouse = true;
    SetCapture(hwnd);
    rightMouse(true);
    break;

  case WM_RBUTTONUP:
    right_mouse = false;
    rightMouse(false);
    if (!left_mouse) ReleaseCapture();
    break;

  case WM_MOUSEMOVE:
    {
      short x = LOWORD(lParam);
      watch_x = x;
      short y = HIWORD(lParam);
      mouse(x, y);
    }
    break;

  case WM_CLOSE:
    if (checkHide()) {

      show(SW_HIDE);

      // check and see if all the windows are hidden
      for (WindowClass::Windows::iterator i = WindowClass::windows->begin();
	   i != WindowClass::windows->end();
	   ++i) {

	Window* window = (*i).second;
	if (!window->hidden) return 0;
      }
      if (!WindowClass::check_done || WindowClass::check_done()) {
	PostQuitMessage(0);
      }
    }
    break;

  default:
    assert((hwnd == this->hwnd) || (this->hwnd==0));
    return DefWindowProc(hwnd, iMsg, wParam, lParam);

  }

  return 0;
}


void Window::init() {

  if (fullscreen) {

    hwnd = window_class->createWindowEx(this,
					//					WS_EX_TOPMOST,
					0,
					app_name.c_str(),
					WS_POPUP | WS_VISIBLE,
					0,	// init x
					0,      // init y
					GetSystemMetrics(SM_CXSCREEN),  // width
					GetSystemMetrics(SM_CYSCREEN),  // height
					NULL,			// parent window handle
					NULL);			// window menu handle
  } else {

    hwnd = window_class->createWindow(this,
				      app_name.c_str(),
				      WS_OVERLAPPEDWINDOW,
				      CW_USEDEFAULT,	// init x
				      CW_USEDEFAULT,  // init y
				      640,	// init x size
				      480,  // init y size
				      NULL,			// parent window handle
				      NULL);			// window menu handle
  }

  assert(hwnd);
}


void Window::show(int iCmdShow) {

  if (hwnd==0) init();

  ShowWindow(hwnd, iCmdShow);

  if (iCmdShow==SW_HIDE) {
    hidden = true;
  } else {
    hidden = false;
    UpdateWindow(hwnd);
  }
}

