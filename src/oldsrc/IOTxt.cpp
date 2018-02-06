
#include "stdafx.h"
#include <stdio.h>

/*
    constants
*/


CKOption *KOption;

/*
    Exports symbols
*/


CKScene *GScene;
CKSkeleton *CurSkel;
char temp[512],temp2[512];
int nBufSize=512;
float v1,v2,v3;

/*
    My functions
*/

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
    case KM_GETFILEEXT:
        value=(unsigned int)&PluginFileExt;
        break;
    case KM_GETREADSUPPORT:
        value=1;
        break;
    case KM_GETWRITESUPPORT:
        value=1;
        break;
    case KM_WRITEFILE:
        value=Write((CKScene*)wParam,(char*)lParam);
        break;
    case KM_READFILE:
        value=Read((CKScene*)wParam,(char*)lParam);
        break;

    }

    return value;
}


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


