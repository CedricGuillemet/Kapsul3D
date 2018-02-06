#include "stdafx.h"
#include "resource.h"
#include <commctrl.h>
#include "DumpInfos.h"
// call in C only, Mfc in plugins are hard to implement.


HINSTANCE g_Inst;

static AFX_EXTENSION_MODULE InfosDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove t his if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);
 
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("Infos.DLL Initializing!\n");

		g_Inst=hInstance;
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(InfosDLL, hInstance))
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

		new CDynLinkLibrary(InfosDLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("Infos.DLL Terminating!\n");
		// Terminate the library before destructors are called
		AfxTermExtensionModule(InfosDLL);
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
CString szRenderer,szVersion,szVendor,szSupportedExt;

/*
    constants
*/

static char PluginName[]={"Infos"};
static char PluginInfos[]={"Infos"};

/*
    My stuffs
*/

// put here your code
int obj,objvert,objface,camera,shape,segment,spot,omni,skeletton,bone,emitter;

void GetOGLSpecs()
{
// ASSERT(dadk);

 szVendor   = (char*)glGetString(GL_VENDOR);
 szVersion  = (char*)glGetString(GL_VERSION);
 szRenderer = (char*)glGetString(GL_EXTENSIONS);
}

void RecCalcBone(CKBone *daBone)
{
	CKBone *daBone2;
	bone++;

	daBone2=daBone->FirstBone;
	while(daBone2!=NULL)
	{
		RecCalcBone(daBone2);

		daBone2=daBone2->Next;
	}

}

void Calc(void)
{
	CKMesh *daMesh;
	CKCamera *daCam;
	//Emitter *daPart;
	CKShape *daShp;
	CKSkeleton *daSkel;
	CKSegment *daSeg;
	CKBone *daBone;

	obj=0;
	objvert=0;
	objface=0;
	camera=0;
	shape=0;
	segment=0;
	spot=0;
	omni=0;
	skeletton=0;
	bone=0;
	emitter=0;

	// Obj

	daMesh=GScene->FirstMesh;
	while(daMesh!=NULL)
	{
		if (daMesh->nb2poly!=0)
		{
			obj++;
			objvert+=daMesh->nb2vert;
			objface+=daMesh->nb2poly;
		}

		daMesh=daMesh->Next;
	}

	// cam

	daCam=GScene->FirstCam;
	while(daCam!=NULL)
	{
		camera++;
		daCam=daCam->Next;
	}

	// emit
/*
	daPart=GScene->FirstEmit;
	while(daPart!=NULL)
	{
		emitter++;
		daPart=daPart->Next;
	}
*/
	// light


	// shape

	daShp=GScene->FirstShape;
	while(daShp!=NULL)
	{

		daSeg=daShp->FirstSegment;
		if (daSeg!=NULL) shape++;
		while(daSeg!=NULL)
		{
			segment++;
			daSeg=daSeg->Next;
            if (daSeg==daShp->FirstSegment)
				break;
			
		}

		daShp=daShp->Next;
	}

	// skeletton

	daSkel=GScene->FirstSkel;
	while(daSkel!=NULL)
	{
		skeletton++;
		daBone=daSkel->bone;
		while(daBone!=NULL)
		{
			RecCalcBone(daBone);
			daBone=daBone->Next;
		}


		daSkel=daSkel->Next;
	}

}




void SetVal(HWND hDlg,int ID,int NB)
{
	char tempo[250];

	wsprintf(tempo,"%d",NB);
	SendDlgItemMessage(hDlg,ID,WM_SETTEXT,0,(long)tempo);
}


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
CDumpInfos *ModDiagHWND;

unsigned int __declspec(dllexport) Process(unsigned long Msg,unsigned long wParam,unsigned long lParam)
{
    unsigned int value=0;
	//HINSTANCE tempinst=AfxGetInstanceHandle();
	//AfxSetResourceHandle(g_Inst);

    switch (Msg)
    {
    case KM_OPEN:
        Parent=(HWND)wParam;
        tempo=CWnd::FromHandle((HWND)wParam);
		
		GetOGLSpecs();

        ModDiagHWND=new CDumpInfos;
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
        value=PLUGIN_OTHER;
        break;
    case KM_ISPROPERTY:
        value=0;
        break;
    case KM_ISCREATING:
        value=IsCreating;
        break;
    case KM_SETSCENE:
        GScene=(CKScene*)wParam;
		Calc();
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
        GDrawScene=(CKDrawScene*)wParam;
        break;
    }
	//AfxSetResourceHandle(tempinst);
    return value;
}

/*
    Functions used by this plugin
*/


#ifdef __cplusplus
    }
#endif
