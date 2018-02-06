#include "stdafx.h"
#include "resource.h"
#include <commctrl.h>
//#include "ModdLight.h"
#include "LightMod.h"
#include "LightParam.h"
#include "LightBuild.h"
#include "PrecalcLight.h"

#include <afxdllx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HINSTANCE g_Inst;

static AFX_EXTENSION_MODULE LightDLL = { NULL, NULL };
CKUndoRedo *CurrentUndo=NULL;

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("Light.DLL Initializing!\n");

		g_Inst=hInstance;
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(LightDLL, hInstance))
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

		new CDynLinkLibrary(LightDLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("Light.DLL Terminating!\n");
		// Terminate the library before destructors are called
		AfxTermExtensionModule(LightDLL);
	}
	return 1;   // ok
}
extern CLightParam *m_ParamDiag;
extern CLightBuild *m_BuildDiag;
extern CPrecalcLight *m_PrecalcDiag;
extern double tmpradius;
// call in C only, Mfc in plugins are hard to implement.
#ifdef __cplusplus
    extern "C" {
#endif

/* 
    Plugins structure and private datas
*/

HWND Parent;
HWND LightDiagHWND;

bool IsCreating;
CKScene *GScene;
CKDrawScene *GDrawScene;
int LightType;

/*
    constants
*/

static char PluginName[]={"Light"};
static char PluginInfos[]={"Light"};

/* 
    My datas
*/
extern HINSTANCE g_Inst;
int CreateSeg;
Vertex Remem;
HWND daGDrawScene;
HWND Rec;
void *Main;
bool HasMoveCr;
unsigned char r,g,b;
//CLight *CurrentLight;

CLightMod *ModDiagHWND;
CRollupCtrl __declspec(dllexport) *m_wndRollupCtrl;
CWnd *tempo;
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

/*
    Process message handler
*/
CBitmap m_Dib,m_Dib2;

unsigned int __declspec(dllexport) Process(unsigned long Msg,unsigned long wParam,unsigned long lParam)
{
    unsigned int value=0;
    //AFX_MANAGE_STATE(AfxGetStaticModuleState());
	HINSTANCE tempinst=AfxGetInstanceHandle();
	AfxSetResourceHandle(g_Inst);

    switch (Msg)
    {
    case KM_OPEN:
        Parent=(HWND)wParam;
        tempo=CWnd::FromHandle((HWND)wParam);

        ModDiagHWND=new CLightMod;
        ModDiagHWND->Create((unsigned int)IDD_MODDIAG,tempo);
        
        value=(unsigned int)ModDiagHWND->m_hWnd;
        break;
    case KM_CLOSE:

        ModDiagHWND->DestroyWindow();
		/*
		delete m_wndRollupCtrl;
		delete ModDiagHWND;
		*/
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
        value=PLUGIN_LIGHT;
        break;
    case KM_ISPROPERTY:
        value=1;
        break;
    case KM_ISCREATING:
        value=CreateSeg;
        break;
    case KM_SETSCENE:
        GScene=(CKScene*)wParam;
        break;
    case KM_GETBITMAP:
        m_Dib.LoadBitmap(IDB_BITMAP);
        value=(unsigned int)&m_Dib;
        break;
	case KM_GETBITMAPHOT:
        m_Dib2.LoadBitmap(IDB_BITMAPHOT);
        value=(unsigned int)&m_Dib2;
        break;

	case KM_SETOBJECT:
		//CurrentLight=(CLight*)wParam;
		//tmpradius=CurrentLight->Radius;
		SetPluginActive();
//		m_ParamDiag->m_Spin1.SetPos(CurrentLight->Radius);
		m_ParamDiag->Invalidate(FALSE);
		break;
    case KM_DRAW:
        value=PLUGIN_ALL;
        break;
    case KM_LMOUSEDOWN:
        LMouseDown(LOWORD(wParam),HIWORD(wParam),(Vertex *)(lParam));
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
    case KM_SETVIEW:
        GDrawScene=(CKDrawScene*)wParam;
        break;
    case KM_MOVEWINDOW:
        m_wndRollupCtrl->MoveWindow(0,0,164,(int)lParam,TRUE);
        value=(int)lParam;
        break;
    case KM_UNSETPLUGIN:
        ModDiagHWND->UnSetPlugin();
        break;

    }
	AfxSetResourceHandle(tempinst);

    return value;
}

/*
    Functions used by this plugin
*/


void LMouseDown(int X,int Y,Vertex *Pos)
{
	/*
    if (CreateSeg==0)
    {
		m_ParamDiag->Invalidate(FALSE);
        dk->AddLight();
        CurrentLight=dk->NextLight;

		CurrentLight->r=180;
		CurrentLight->g=180;
		CurrentLight->b=180;

		CurrentLight->Type=LightType;

        CurrentLight->Source=*Pos;
        CurrentLight->Target=*Pos;
		CurrentLight->Radius=1;
		m_ParamDiag->Invalidate(FALSE);

		CurrentUndo=dk->AddUndo("light.dll",1);
		CurrentUndo->UndoType=UNDO_CREATE;

        CreateSeg=1;
    }
	else
	{
		if ((CreateSeg==1)&&(CurrentLight->Type==0))
		{
			CreateSeg=0;
			CurrentUndo->SetAfterEntry(0,PLUGIN_LIGHT,CurrentLight);
		}
		else
		{
			if (CreateSeg==2)
			{
				CreateSeg=0;
				CurrentUndo->SetAfterEntry(0,PLUGIN_LIGHT,CurrentLight);
			}
			else
				CreateSeg=2;
			
		}
	}
*/
}

void LMouseUp(int X,int Y,Vertex *Pos)
{
    if (HasMoveCr)
    {
        CreateSeg=0;
        HasMoveCr=0;

    }
}

void MouseMove(int X,int Y,Vertex *Pos)
{
	/*
    if (CreateSeg!=0)
    {
		switch (CurrentLight->Type)
		{
		case 0:
			CurrentLight->Radius=Pythagore3D(CurrentLight->Source,(*Pos));
			m_ParamDiag->SetText(CurrentLight->Radius);
			RStatus("Omni light radius : %d",(int)(CurrentLight->Radius));
			LStatus("Click to end omni light creation.");
			break;
		case 1:
			if (CreateSeg==1)
			{
				CurrentLight->Target=*Pos;
				CurrentLight->Radius=1;
				LStatus("Click to set spot light target.");
			}
			else
			{
				CurrentLight->Radius=Pythagore3D(CurrentLight->Target,(*Pos));
				CurrentLight->Radius/=2;
				m_ParamDiag->SetText(CurrentLight->Radius);
				RStatus("Spot light radius : %5.2f",CurrentLight->Radius);
				LStatus("Click to end spot light creation.");
			}
			break;
		case 2:
			if (CreateSeg==1)
			{
				CurrentLight->Target=*Pos;
				CurrentLight->Radius=1;
				LStatus("Click to set neon light end.");
			}
			else
			{
				CurrentLight->Radius=Pythagore3D(CurrentLight->Target,(*Pos));
				m_ParamDiag->SetText(CurrentLight->Radius);
				RStatus("Neon light radius : %5.2",CurrentLight->Radius);
				LStatus("Click to end neon light creation.");
			}
			break;
		}
		tmpradius=CurrentLight->Radius;
		DrawGDrawScenes();
	}
	else
	{
		LStatus("Click to set light source.");
	}
	*/

}

void RMouseDown(int X,int Y,Vertex *Pos)
{
}

void RMouseUp(int X,int Y,Vertex *Pos)
{
	/*
    if (CurrentLight!=NULL)
    {
        dk->DelLight(CurrentLight);
        CurrentLight=NULL;
		CreateSeg=0;
    }
*/
}


#ifdef __cplusplus
    }
#endif

