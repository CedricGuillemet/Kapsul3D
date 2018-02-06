#include "stdafx.h"
#include <Kapsul3D.h>
#include <headers.h>
#include "resource.h"
#include <commctrl.h>
#include "DumpEntPlg.h"
// call in C only, Mfc in plugins are hard to implement.


HINSTANCE g_Inst;

static AFX_EXTENSION_MODULE EntPlgDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove t his if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);
 
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("EntPlg.DLL Initializing!\n");

		g_Inst=hInstance;
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(EntPlgDLL, hInstance))
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

		new CDynLinkLibrary(EntPlgDLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("EntPlg.DLL Terminating!\n");
		// Terminate the library before destructors are called
		AfxTermExtensionModule(EntPlgDLL);
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

static char PluginName[]={"Entity Builder"};
static char PluginInfos[]={"Entity Builder"};

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
CBitmap m_Dib;
CWnd *tempo;
CEntPlg *ModDiagHWND;

void LMouseDown(int X,int Y,Vertex *Pos);
void LMouseUp(int X,int Y,Vertex *Pos);
void MouseMove(int X,int Y,Vertex *Pos);
void RMouseDown(int X,int Y,Vertex *Pos);
void RMouseUp(int X,int Y,Vertex *Pos);

CEntity *CurrentEntity=NULL;
CEntity *CurrentPropEntity=NULL;
CEntityType *EntType;

unsigned int __declspec(dllexport) Process(unsigned long Msg,unsigned long wParam,unsigned long lParam)
{
    unsigned int value=0;
	CString CurrentType;
	HINSTANCE tempinst=AfxGetInstanceHandle();
	AfxSetResourceHandle(g_Inst);

    switch (Msg)
    {
    case KM_OPEN:
		IsCreating=false;
        Parent=(HWND)wParam;
        tempo=CWnd::FromHandle((HWND)wParam);

        ModDiagHWND=new CEntPlg;
        ModDiagHWND->Create((unsigned int)IDD_MODDIAG,tempo);
        
        value=(unsigned int)ModDiagHWND->m_hWnd;
        break;
    case KM_CLOSE:
        ModDiagHWND->DestroyWindow();
        break;
    case KM_GETNAME:
        value=(unsigned int)&PluginName;
        break;
    case KM_GETINFOS:
        value=(unsigned int)&PluginInfos;
        break;
    case KM_GETTYPE:
        value=PLUGIN_CREATION;
        break;
    case KM_GETSECONDARYTYPE:
        value=PLUGIN_ENTITY;
        break;
    case KM_ISPROPERTY:
        value=1;
        break;
	case KM_SETOBJECT:
		// set an entity object (property on an entity)
		CurrentPropEntity=(CEntity*)wParam;
		int ListNb;
		EntType=ModDiagHWND->FindEntityTypeByName(CurrentPropEntity->EntType,ListNb);
		if (EntType!=NULL)
		{
			//ModDiagHWND->ResetAllValues();
			ModDiagHWND->m_EntsTypes.SetCurSel(ListNb);
			ModDiagHWND->UpdatePropList(EntType);
			ModDiagHWND->UpdatePropsFromEntity();
		}
		break;
    case KM_ISCREATING:
		if (CurrentEntity!=NULL)
			value=CurrentEntity->ProcessMessage(KM_ISCREATING,0,0);
		else
		{
			CurrentEntity=NULL;
			value=0;
		}
        break;
    case KM_SETDESK:
        dk=(Desk*)wParam;
		ModDiagHWND->Invalidate();

        break;
    case KM_GETBITMAP:
        m_Dib.LoadBitmap(IDB_BITMAP);
        value=(unsigned int)&m_Dib;
        break;
    case KM_DRAW:
        value=PLUGIN_ALL;
        break;
    case KM_SETVIEW:
        View=(OGLView*)wParam;
        break;
    case KM_MOVEWINDOW:
        ModDiagHWND->MoveWindow(0,0,162,(int)lParam,TRUE);
        value=(int)lParam;
        break;

	// mouse move

	case KM_LMOUSEDOWN:
		if (CurrentEntity!=NULL)
		{
			if (CurrentEntity->ProcessMessage(KM_ISCREATING,0,0)!=0)
			{
				LMouseDown(LOWORD(wParam),HIWORD(wParam),(Vertex *)(lParam));
			}
			else
			{
				CurrentEntity=NULL;
			}
		}
		if (CurrentEntity==NULL)
		{
			ModDiagHWND->m_EntsTypes.GetLBText(ModDiagHWND->m_EntsTypes.GetCurSel(),CurrentType);
			CurrentEntity=dk->AddEntity(CurrentType.GetBuffer(1));
			CurrentPropEntity=CurrentEntity;
			CurrentEntity->ProcessMessage(KM_SETENTITY,(UINT)CurrentEntity,0);
			LMouseDown(LOWORD(wParam),HIWORD(wParam),(Vertex *)(lParam));
			ModDiagHWND->UpdatePropsFromEntity();
		}
        break;
    case KM_RMOUSEDOWN:
        RMouseDown(LOWORD(wParam),HIWORD(wParam),(Vertex *)(lParam));
        break;
    case KM_LMOUSEUP:
        LMouseUp(LOWORD(wParam),HIWORD(wParam),(Vertex *)(lParam));
        break;
    case KM_RMOUSEUP:
        RMouseUp(LOWORD(wParam),HIWORD(wParam),(Vertex *)(lParam));
        break;
    case KM_MOUSEMOVE:
        MouseMove(LOWORD(wParam),HIWORD(wParam),(Vertex *)(lParam));
        break;
    }
	AfxSetResourceHandle(tempinst);
    return value;
}



void LMouseDown(int X,int Y,Vertex *Pos)
{
    if (CurrentEntity!=NULL)
		CurrentEntity->ProcessMessage(KM_LMOUSEDOWN,MAKELONG(X,Y),(int)Pos);
}

void LMouseUp(int X,int Y,Vertex *Pos)
{
    if (CurrentEntity!=NULL)
		CurrentEntity->ProcessMessage(KM_LMOUSEUP,MAKELONG(X,Y),(int)Pos);
}

void MouseMove(int X,int Y,Vertex *Pos)
{
    if (CurrentEntity!=NULL)
		CurrentEntity->ProcessMessage(KM_MOUSEMOVE,MAKELONG(X,Y),(int)Pos);
}

void RMouseDown(int X,int Y,Vertex *Pos)
{
    if (CurrentEntity!=NULL)
		CurrentEntity->ProcessMessage(KM_RMOUSEDOWN,MAKELONG(X,Y),(int)Pos);
}

void RMouseUp(int X,int Y,Vertex *Pos)
{
    if (CurrentEntity!=NULL)
		CurrentEntity->ProcessMessage(KM_RMOUSEUP,MAKELONG(X,Y),(int)Pos);
}

/*
    Functions used by this plugin
*/




#ifdef __cplusplus
    }
#endif
