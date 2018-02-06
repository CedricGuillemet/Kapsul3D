#include "stdafx.h"
#include <Kapsul3D.h>
#include <headers.h>
#include "resource.h"
#include <commctrl.h>
#include "ChildFrm.h"
#include "CImageDemoDoc.h"
#include "CImageDemoView.h"
#include "PaletteDialog.h"
//#include "DumpHooking.h"
// call in C only, Mfc in plugins are hard to implement.


HINSTANCE g_Inst;

static AFX_EXTENSION_MODULE HookingDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove t his if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);
 
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("Hooking.DLL Initializing!\n");

		g_Inst=hInstance;
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(HookingDLL, hInstance))
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

		new CDynLinkLibrary(HookingDLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("Hooking.DLL Terminating!\n");
		// Terminate the library before destructors are called
		AfxTermExtensionModule(HookingDLL);
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
Desk *dk;
OGLView *View;

/*
    My datas
*/

// put here your datas

/*
    constants
*/

static char PluginName[]={"Hooking"};
static char PluginInfos[]={"Hooking"};
static char PluginExts[]={"Images files(*.jpg;*.jpeg;*.tif;*.tiff;*.pcx;*.bmp;*.tga;*.png)|*.jpg;*.jpeg;*.tif;*.tiff;*.pcx;*.bmp;*.tga;*.png"};
/*
    My stuffs
*/


/*
    Exports symbols
    Add here all the symbol which can be use anywhere else (exports)
*/

unsigned int __declspec(dllexport) Process(unsigned long Msg,unsigned long wParam,unsigned long lParam);

/*
    Process message handler
*/

CMDIFrameWnd *MainFrame; 
CMultiDocTemplate* pDocTemplate;
CPaletteDialog m_PalDiag;
CToolBar    m_wndToolBar;

unsigned int __declspec(dllexport) Process(unsigned long Msg,unsigned long wParam,unsigned long lParam)
{
    unsigned int value=0;
	//HINSTANCE tempinst=AfxGetInstanceHandle();
	//AfxSetResourceHandle(g_Inst);

    switch (Msg)
    {
    case KM_OPEN:
		// called when doc/view registration is required
		//AfxSetResourceHandle(tempinst);
		MainFrame=(CMDIFrameWnd*)wParam;
		// create your toolbar & dialog here (Hided);
		// When your view receive the focus, show the toolbar/dialogs
		// hide them when it's lost
/*
		// When a 1 of your document is modified, you have to make that:
		MainFrame->SendMessage(WM_DOCUMENTUPDATED,(UINT)MyDocStructure,0);
		// where MyDocStructure is a pointer to a KDocumentUpdate structure

		// When you close,open or create a new document you have to do that:
		MainFrame->SendMessage(WM_LISTDOCUMENT,(UINT)MyListStructure,(UINT)NumberOfDocuments);
		// where MyListStructure is a pointer to a KDocumentList array structure
		// fill it. It's used to update my document list.
		
		*/
	
		pDocTemplate = new CMultiDocTemplate(
			IDR_CIMAGETYPE,
			RUNTIME_CLASS(CCImageDemoDoc),
			RUNTIME_CLASS(CChildFrame), // custom MDI child frame
			RUNTIME_CLASS(CCImageDemoView));
		AfxGetApp()->AddDocTemplate(pDocTemplate);
		pDocTemplate->OpenDocumentFile(NULL);
		m_wndToolBar.Create(MainFrame);
		m_wndToolBar.LoadToolBar(IDR_MAINFRAME);
		m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
		m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
		MainFrame->EnableDocking(CBRS_ALIGN_ANY);
		MainFrame->DockControlBar(&m_wndToolBar);

		m_PalDiag.Create(MAKEINTRESOURCE(IDD_PALETTE),MainFrame);

        break;
    case KM_CLOSE:
		// called when the application is closed
		// free your stuffs
		
        break;
    case KM_GETNAME:
        value=(unsigned int)&PluginName;
        break;
    case KM_GETINFOS:
        value=(unsigned int)&PluginInfos;
        break;
	case KM_OPENFILE:
		pDocTemplate->OpenDocumentFile((char*)wParam);
		break;
    case KM_GETTYPE:
        value=PLUGIN_DOCVIEW;
        break;
	case KM_GETEXTENSIONS:
		value=(unsigned int)&PluginExts;
		break;
    case KM_GETSECONDARYTYPE:
        value=0;
        break;
    
    }

	
    return value;
}

/*
    Functions used by this plugin
*/




#ifdef __cplusplus
    }
#endif
