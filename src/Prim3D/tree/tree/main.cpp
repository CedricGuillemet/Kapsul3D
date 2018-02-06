#include <window/WindowClass.h>
#include "TreeWindow.h"

#include <strstream>
using std::istrstream;
using std::ws;

#include <vector>
using std::vector;

#include "resource.h"
#include <thigs/Image.h>
#include <ptr/Ptr.h>
#include <util/util.h>

int WINAPI WinMain(HINSTANCE hInstance,
		   HINSTANCE hPrevInstance,
		   PSTR szCmdLine,
		   int iCmdShow) {

  vector<string> args;

  istrstream cmdline(szCmdLine);
  cmdline >> ws;
  while (!cmdline.eof()) {
    string arg;
    cmdline >> arg;
    args.push_back(arg);
  }

  bool fullscreen = false;
  bool oneframe = false;

  bool tl_flag = false;
  int resolution = 0;
  int depth = 5;
  int fullness = 5;
  int bpp = 16;
  int lites = 4;
  bool fill_flag = false;
  //bool fullscreen = false;
  bool is_bench = false;

  int i=0;
  while (i<args.size()) {

    if (args[i]==string("-fullscreen")) {
      fullscreen = true;
    }

    if (args[i]==string("-test")) {
      oneframe = true;
    }
	//************** get test settings *************
	if (args[i]==string("-filltest")){
		fill_flag = true;
		fullscreen = true; ////temp set false so can run on my machine
		is_bench = true;}

	if(args[i]==string("-tltest")){
		tl_flag = true;
		fullscreen = true; //temp set false so can run on my machine
		is_bench = true;}
	
	if(args[i]==string("-640x480"))
		resolution = 1;
	if(args[i]==string("-800x600"))
		resolution = 2;
	if(args[i]==string("-1024x768"))
		resolution = 3;
	if(args[i]==string("-1280x1024"))
		resolution = 4;
	
	if(args[i]==string("-depth1"))
		depth = 1;
	if(args[i]==string("-depth2"))
		depth = 2;
	if(args[i]==string("-depth3"))
		depth = 3;
	if(args[i]==string("-depth4"))
		depth = 4;
	if(args[i]==string("-depth5"))
		depth = 5;
	if(args[i]==string("-depth6"))
		depth = 6;
	if(args[i]==string("-depth7"))
		depth = 7;
	if(args[i]==string("-depth8"))
		depth = 8;
	if(args[i]==string("-depth9"))
		depth = 9;
	if(args[i]==string("-depth10"))
		depth = 10;
	
	if(args[i]==string("-bpp16"))
		bpp = 16;
	if(args[i]==string("-bpp32"))
		bpp = 32;
	
	if(args[i]==string("-lights1"))
		lites = 1;
	if(args[i]==string("-lights2"))
		lites = 2;
	if(args[i]==string("-lights3"))
		lites = 3;
	if(args[i]==string("-lights4"))
		lites = 4;
	if(args[i]==string("-lights5"))
		lites = 5;
	if(args[i]==string("-lights6"))
		lites = 6;
	if(args[i]==string("-lights7"))
		lites = 7;
	if(args[i]==string("-lights8"))
		lites = 8;
	if(args[i]==string("-lights0"))
		lites = 0;

    ++i;
  }

  Ptr<WindowClass> window_class = new WindowClass(hInstance, "OpenGL");
  window_class->setIcon(LoadIcon(hInstance, "tree"));

  Ptr<TreeWindow> window = new TreeWindow(window_class, "Tree", fullscreen);
  if (oneframe) window->setOneFrame();

  //*********** change the current display settings *************
  if(resolution != 0){  
    DEVMODE devm, *temp = &devm;
	EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, temp);
	
	if(resolution == 1){
		devm.dmPelsWidth = 640;
		devm.dmPelsHeight = 480;
	}
	if(resolution == 2){
		devm.dmPelsWidth = 800;
		devm.dmPelsHeight = 600;
	}
	if(resolution == 3){
		devm.dmPelsWidth = 1024;
		devm.dmPelsHeight = 768;
	}
	if(resolution == 4){
		devm.dmPelsWidth = 1280;
		devm.dmPelsHeight = 1024;
	}

	if(bpp = 16)
		devm.dmBitsPerPel = 16;
	if(bpp = 32)
		devm.dmBitsPerPel = 32;
	
	devm.dmDisplayFrequency = 85;
	devm.dmDriverExtra = 0;
	devm.dmSize = sizeof(devm);
	  
	ChangeDisplaySettings(temp, CDS_SET_PRIMARY);		
  
  }//dh end set resolution if statement


  window->setBench(is_bench, depth, fill_flag, lites);

  try {

    window->show(iCmdShow);

    return WindowClass::go();

  }

  catch(const GLUnsupported& error) {

    showError(error.message.c_str());
  }

  return -1;
}
