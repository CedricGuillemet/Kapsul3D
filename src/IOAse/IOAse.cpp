/*

	IOIO3ds.CPP

*/

#include "stdafx.h"
#include <Kapsul3D.h>
#include <headers.h>
#include "ase.h"
#include <stdio.h>

#ifdef __cplusplus
    extern "C" {
#endif


/*
    constants
*/

static char PluginName[]={"3DStudio ASE importer"};
static char PluginInfos[]={"3DStudio ASE importer"};
static char PluginFileDesc[]={"3DStudio"};
static char PluginFilter[]={"*.ase"};

/*
    My stuffs
*/


/*
    Exports symbols
*/

unsigned int __declspec(dllexport) Process(unsigned long Msg,unsigned long wParam,unsigned long lParam);
int  __declspec(dllexport)   Read(Desk *dk,char PathName[260]);
int  __declspec(dllexport)   Write(Desk *dk,char PathName[260]);

/*
    Process message handler
*/

unsigned int __declspec(dllexport) Process(unsigned long Msg,unsigned long wParam,unsigned long lParam)
{
    unsigned int value=0;

    switch (Msg)
    {
    case KM_OPEN:
        break;
    case KM_CLOSE:
        break;
    case KM_GETNAME:
        value=(unsigned int)&PluginName;
        break;
    case KM_GETINFOS:
        value=(unsigned int)&PluginInfos;
        break;
    case KM_GETTYPE:
        value=PLUGIN_FILE;
        break;
    case KM_GETSECONDARYTYPE:
        value=0;
        break;
    case KM_GETFILTER:
        value=(unsigned int)&PluginFilter;
        break;
    case KM_GETFILEDESC:
        value=(unsigned int)&PluginFileDesc;
        break;
    case KM_GETREADSUPPORT:
        value=1;
        break;
    case KM_GETWRITESUPPORT:
        value=0;
        break;
    case KM_WRITEFILE:
        value=Write((Desk*)wParam,(char*)lParam);
        break;
    case KM_READFILE:
        value=Read((Desk*)wParam,(char*)lParam);
        break;

    }

    return value;
}

/*
    Process Read and Write
*/

int  __declspec(dllexport)   Read(Desk *dadk,char PathName[260])
{
    // Process here your read operation
	CLoadASE ldase;
    return ldase.ImportASE(dadk, PathName);
}

int  __declspec(dllexport)   Write(Desk *dadk,char PathName[260])
{
    // Process here your write operation

    return true; //Did everything went right ?
}

#ifdef __cplusplus
    }
#endif

/*
    DLL entrypoint
*/

class CPluginApp : public CWinApp
{
public:
	CPluginApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKoreApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CKoreApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CPluginApp, CWinApp)
	//{{AFX_MSG_MAP(CPluginApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKoreApp construction

CPluginApp theApp;

CPluginApp::CPluginApp()
{
}

BOOL CPluginApp::InitInstance() 
{
	return CWinApp::InitInstance();
}

