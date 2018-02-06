#include <window/WindowClass.h>

#include <vector>
using std::vector;

#include <window/Window.h>

#include <util/util.h>

WindowClass::Windows* WindowClass::windows=0;
WindowClass::Tasks* WindowClass::tasks=0;
int WindowClass::Init::count = 0;
Thunk0<bool> WindowClass::check_done;
Window* WindowClass::creating_window = 0;

WindowClass::WindowClass(HINSTANCE hInstance, const string& cn) : registered(false), class_name(cn) {

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = callback;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = NULL;
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = class_name.c_str();
}


HWND WindowClass::createWindow(Window* window,
			       const char* app_name,
			       DWORD window_style,
			       int x,
			       int y,
			       int w,
			       int h,
			       HWND parent,
			       HMENU menu) {


  assert(!creating_window);
  creating_window = window;

  HWND hwnd = ::CreateWindow(class_name.c_str(),
			     app_name,
			     window_style,
			     x, y, w, h,
			     parent,
			     menu,
			     wndclass.hInstance,
			     NULL);
  if (!hwnd) {
    showLastError("CreateWindow: ");
    exit(-1);
  }

  pair<Windows::iterator, bool> success = 
    windows->insert(Windows::value_type(hwnd, window));
  assert(success.second);

  creating_window = 0;
  return hwnd;
}



HWND WindowClass::createWindowEx(Window* window,
				 DWORD ex_window_style,
				 const char* app_name,
				 DWORD window_style,
				 int x,
				 int y,
				 int w,
				 int h,
				 HWND parent,
				 HMENU menu) {


  assert(!creating_window);
  creating_window = window;

  HWND hwnd = ::CreateWindowEx(ex_window_style,
			       class_name.c_str(),
			       app_name,
			       window_style,
			       x, y, w, h,
			       parent,
			       menu,
			       wndclass.hInstance,
			       NULL);
  if (!hwnd) {
    showLastError("CreateWindow: ");
    exit(-1);
  }

  pair<Windows::iterator, bool> success = 
    windows->insert(Windows::value_type(hwnd, window));
  assert(success.second);

  creating_window = 0;
  return hwnd;
}



void WindowClass::removeWindow(HWND hwnd, Window* window) {

	Windows::iterator i = windows->find(hwnd);
	assert(i!=windows->end());
	assert((*i).second==window);
	windows->erase(i);
}

WindowClass::~WindowClass() {

	assert(windows->size()==0);

	if (registered) {
		bool success = UnregisterClass(class_name.c_str(), wndclass.hInstance);
		assert(success);
	}
}


void WindowClass::registerWindowClass() {

	if (!registered) {
		registered = true;
		ATOM success = RegisterClass(&wndclass);
		assert(success);
	}
}


LRESULT CALLBACK WindowClass::callback(HWND hwnd, 
				       UINT iMsg, 
				       WPARAM wParam, 
				       LPARAM lParam) {

  if (creating_window) {
    return creating_window->callback(hwnd, iMsg, wParam, lParam);
  }

  Windows::iterator i = windows->find(hwnd);
#if 0
  if (i!=windows->end()) {
    return (*i).second->callback(iMsg, wParam, lParam);
  } else {
    return DefWindowProc(hwnd, iMsg, wParam, lParam);
  }
#else
  assert(i!=windows->end());
  return (*i).second->callback(hwnd, iMsg, wParam, lParam);
#endif
}



bool WindowClass::addTask(const Thunk0<>& task) {

	pair<Tasks::iterator, bool> success = tasks->insert(task);
	return success.second;
}	


bool WindowClass::removeTask(const Thunk0<>& task) {

	Tasks::iterator i = tasks->find(task);
	if (i==tasks->end()) {
		return false;
	} else {
		tasks->erase(i);
		return true;
	}
}


UINT WindowClass::go() {

	BOOL result;
	MSG msg;

	while(true) {

		while ((tasks->size()==0) || PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)==TRUE) {

			if (result=GetMessage(&msg, NULL, 0, 0)) {

				assert(result!=-1);
				TranslateMessage(&msg);
				DispatchMessage(&msg);

			} else {

				return msg.wParam;
			}
		}

		if (tasks->size()!=0) {

			typedef vector<Thunk0<> > TaskList;
			TaskList task_list;
			for (Tasks::iterator i = tasks->begin();
				 i != tasks->end();
				 ++i) {

					 task_list.push_back(*i);
			}

			for (TaskList::iterator j = task_list.begin();
				 j != task_list.end();
				 ++j) {

					 (*j)();
			}

		}
	}
}

void WindowClass::setIcon(HICON icon) {

	wndclass.hIcon = icon;
}

