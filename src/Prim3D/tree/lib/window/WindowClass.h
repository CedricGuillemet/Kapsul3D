#ifndef WindowClass_INCLUDED
#define WindowClass_INCLUDED

#pragma warning( disable : 4786 ) 
#pragma warning( disable : 4800 ) 

#include <windows.h>

#include <set>
using std::set;

#include <map>
using std::map;

#include <string>
using std::string;

#include <thunk/Thunk.h>
#include <ptr/Ptr.h>

struct Window;

struct WindowClass {

  WindowClass(HINSTANCE hInstance, const string& class_name);
  ~WindowClass();

  static bool addTask(const Thunk0<>&);	   // returns true upon success
  static bool removeTask(const Thunk0<>&); // returns true upon success

  static void setCheckDone(const Thunk0<bool>&);

  void setIcon(HICON);

  static UINT go();

 private:

  static LRESULT CALLBACK callback(HWND, UINT, WPARAM, LPARAM);
  
  friend struct Window;

  static Window* creating_window;

  void registerWindowClass();

  HWND createWindow(Window*,
		    const char* app_name,
		    DWORD window_style,
		    int x,
		    int y,
		    int w,
		    int h,
		    HWND parent,
		    HMENU menu);
  HWND createWindowEx(Window*,
		      DWORD ex_window_style,
		      const char* app_name,
		      DWORD window_style,
		      int x,
		      int y,
		      int w,
		      int h,
		      HWND parent,
		      HMENU menu);
  void removeWindow(HWND, Window*);


  typedef map<HWND, Window*> Windows;
  static Windows* windows;

  typedef set<Thunk0<> > Tasks;
  static Tasks* tasks;

  static Thunk0<bool> check_done;

  bool registered;
  string class_name;
  WNDCLASS wndclass;

 public:

  struct Init {
    Init() {
      if (count++==0) {
	windows = new Windows;
	tasks = new Tasks;
      }
    }
    ~Init() {
      if (--count==0) {
	delete windows;
	delete tasks;
      }
    }
    private:
    static int count;
  };
  friend struct Init;
};

static WindowClass::Init window_class_init;

#endif
