// tpackshad.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "tpshad.h"
#include "kfiledialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CtpackshadApp

BEGIN_MESSAGE_MAP(CtpackshadApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CtpackshadApp construction

CtpackshadApp::CtpackshadApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CtpackshadApp object

CtpackshadApp theApp;


// CtpackshadApp initialization

BOOL CtpackshadApp::InitInstance()
{
	// InitCommonControls() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	InitCommonControls();

	CWinApp::InitInstance();


	CKFileDialog dlg;
	dlg.SetExtensionsList("Image files|*.jpg;*.png;*.bmp|All files|*.*||");
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
