#include "stdafx.h"
#include "resource.h"
#include <commctrl.h>
#include "PluginDiag.h"
// call in C only, Mfc in plugins are hard to implement.


HINSTANCE g_Inst;

static AFX_EXTENSION_MODULE StdPluginDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove t his if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);
 
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("StdPlugin.DLL Initializing!\n");

		g_Inst=hInstance;
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(StdPluginDLL, hInstance))
			return 0;

		// Insert this DLL into the resource chain
		// NOTE: If this Extension DLL is being implicitly linked to by
		//  an MFC Regular DLL (such as an ActiveX Control)
		//  instead of an MFC application, then you will want to
		//  remove this line from DllMain and put it in a separate
		//  function exported from this Extension DLL.  The Regular DLL
		//  that uses this Extension DLL should then explicitly call that
		//  function to initialize this Extension DLL.  Otherwise,
		//  the CDynLinkLibrary object will not be attached to the
		//  Regular DLL's resource chain, and serious problems will
		//  result.

		new CDynLinkLibrary(StdPluginDLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("StdPlugin.DLL Terminating!\n");
		// Terminate the library before destructors are called
		AfxTermExtensionModule(StdPluginDLL);
	}
	return 1;   // ok
}

#ifdef __cplusplus
    extern "C" {
#endif

/* 
    Plugins structure and private datas
*/

HWND Parent;

HINSTANCE myHinst;
bool IsCreating;
CKScene *GScene;
CKDrawScene *GDrawScene;

/*
    My datas
*/

// put here your datas

/*
    constants
*/

static char PluginName[]={"StdPlugin"};
static char PluginStdPlugin[]={"StdPlugin"};

/*
    My stuffs
*/

// put here your code


/*
    Exports symbols
    Add here all the symbol which can be use anywhere else (exports)
*/

unsigned int __declspec(dllexport) Process(unsigned long Msg,unsigned long wParam,unsigned long lParam);
void LMouseDown(int X,int Y,Vertex *Pos);
void LMouseUp(int X,int Y,Vertex *Pos);
void MouseMove(int X,int Y,Vertex *Pos);
void RMouseDown(int X,int Y,Vertex *Pos);
void RMouseUp(int X,int Y,Vertex *Pos);


int Draw(int State ,int WichOne )
{
	return PLUGIN_ALL;// return types of plugin you want to show
}

void LMouseDown(int X,int Y,Vertex *Pos)
{
}

void LMouseUp(int X,int Y,Vertex *Pos)
{
}

void MouseMove(int X,int Y,Vertex *Pos)
{
}

void RMouseDown(int X,int Y,Vertex *Pos)
{
}

void RMouseUp(int X,int Y,Vertex *Pos)
{
}
/*
    Process message handler
*/
CBitmap m_Dib,m_Dib2;
CWnd *tempo;
CPluginDiag *ModDiag;

unsigned int __declspec(dllexport) Process(unsigned long Msg,unsigned long wParam,unsigned long lParam)
{
    unsigned int value=0;
	HINSTANCE tempinst=AfxGetInstanceHandle();
	AfxSetResourceHandle(g_Inst);

    switch (Msg)
    {
    case KM_OPEN:
        Parent=(HWND)wParam;
        tempo=CWnd::FromHandle((HWND)wParam);
		
        ModDiag=new CPluginDiag;
        ModDiag->Create((unsigned int)IDD_DIAG,tempo);
        
        value=(unsigned int)ModDiag->m_hWnd;
        break;
    case KM_CLOSE:
        ModDiag->DestroyWindow();
        break;
    case KM_GETNAME:
        value=(unsigned int)&PluginName;
        break;
    case KM_GETINFOS:
        value=(unsigned int)&PluginStdPlugin;
        break;
    case KM_GETTYPE:
        value=PLUGIN_CREATION;
        break;
    case KM_GETSECONDARYTYPE:
        value=PLUGIN_OTHER;
        break;
    case KM_ISPROPERTY:
        value=0;
        break;
    case KM_ISCREATING:
        value=IsCreating;
        break;
    case KM_SETSCENE:
		if ((CKScene*)wParam!=GScene)
		{
			// changing active document
			GScene=(CKScene*)wParam;
			ModDiag->Invalidate();
		}
        break;
    case KM_GETBITMAP:
        m_Dib.LoadBitmap(IDB_BITMAP);
        value=(unsigned int)&m_Dib;
        break;
    case KM_GETBITMAPHOT:
        m_Dib2.LoadBitmap(IDB_BITMAPHOT);
        value=(unsigned int)&m_Dib2;
        break;
    case KM_DRAW:
		value=Draw(wParam,lParam);
        
        break;
    case KM_SETVIEW:
        GDrawScene=(CKDrawScene*)wParam;
        break;
    }
	AfxSetResourceHandle(tempinst);
    return value;
}

/*
    Functions used by this plugin
*/


#ifdef __cplusplus
    }
#endif
