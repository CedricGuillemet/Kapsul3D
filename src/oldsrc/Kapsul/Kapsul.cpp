// Kapsul.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "SampleChildFrm.h"
#include "SampleDoc.h"
#include "SampleView.h"
#include "SelTypeDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CMainFrame* mainf;
COption KOption;
extern char *ReadFilter,*WriteFilter;

/////////////////////////////////////////////////////////////////////////////
// CKapsulApp

BEGIN_MESSAGE_MAP(CKapsulApp, CWinApp)
	//{{AFX_MSG_MAP(CKapsulApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	//ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	//ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKapsulApp construction

CKapsulApp::CKapsulApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CKapsulApp object

CKapsulApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CKapsulApp initialization

BOOL CKapsulApp::InitInstance()
{
	// Standard initialization
	SetRegistryKey(_T("Kapsul"));

	LoadStdProfileSettings(8);  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.
	
	pDocTemplate = new CMultiDocTemplate(
		IDR_KAPSULDESK,
		RUNTIME_CLASS(CDeskDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(MainEdit));
	AddDocTemplate(pDocTemplate);

	// Text Edit
	pDocScript = new CMultiDocTemplate(
		IDR_KAPSULSCRIPT,
		RUNTIME_CLASS(CSampleDoc),
		RUNTIME_CLASS(CSampleChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CSampleView));
	AddDocTemplate(pDocScript);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	m_pMainWnd = pMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	mainf=pMainFrame;

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	/*
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
*/
	// force new desk
	pDocTemplate->OpenDocumentFile(NULL);
	//pDocScript->OpenDocumentFile(NULL);

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	WINDOWPLACEMENT wp;

	wp.length=sizeof(WINDOWPLACEMENT);

	wp.flags=GetProfileInt ("Editor State","flags",-1);
	wp.showCmd=GetProfileInt ("Editor State","showCmd",0);
	wp.ptMinPosition.x=GetProfileInt ("Editor State","ptMinPositionx",0);
	wp.ptMinPosition.y=GetProfileInt ("Editor State","ptMinPositiony",0);
	wp.ptMaxPosition.x=GetProfileInt ("Editor State","ptMaxPositionx",0);
	wp.ptMaxPosition.y=GetProfileInt ("Editor State","ptMaxPositiony",0);
	wp.rcNormalPosition.left=GetProfileInt ("Editor State","rcNormalPositionl",0);
	wp.rcNormalPosition.right=GetProfileInt ("Editor State","rcNormalPositionr",300);
	wp.rcNormalPosition.top=GetProfileInt ("Editor State","rcNormalPositiont",0);
	wp.rcNormalPosition.bottom=GetProfileInt ("Editor State","rcNormalPositionb",300);


    if (wp.flags!=-1)
    {
	    theApp.m_pMainWnd->SetWindowPlacement(&wp);
    }

	pMainFrame->MDIMaximize(pMainFrame->MDIGetActive());

	bool m_bStartup = !theApp.GetProfileInt(_T("Tip"), _T("StartUp"), 0);

	if (m_bStartup)
		pMainFrame->OnHelpTipoftheday();

	return TRUE;
}

void CKapsulApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

void CKapsulApp::OnFileNew() 
{
	//theApp.pDocScript->OpenDocumentFile(NULL);
	
	CSelTypeDoc cSelDoc;

	if (cSelDoc.DoModal()==IDOK)
	{
		switch (cSelDoc.TypeDoc)
		{
		case 0:
			theApp.pDocTemplate->OpenDocumentFile(NULL);
			break;
		case 1:
			theApp.pDocScript->OpenDocumentFile(NULL);
			break;
		}
	}
}

void CKapsulApp::OnFileOpen() 
{
	//char tempFilters[256]={"Kapsul script (*.ksc)\0*.ksc\0"};
    CFileDialog *m_FileDiag;
	m_FileDiag=new CFileDialog(TRUE);
	//strcpy(tempFilters,"Kapsul script (*.ksc)\0*.ksc\0");
	//strcat(tempFilters,ReadFilter);
	m_FileDiag->m_ofn.lpstrFilter=ReadFilter;
	
	if (m_FileDiag->DoModal()==IDOK)
	{
        if (m_FileDiag->m_ofn.nFilterIndex==1)
        {
            // script
			theApp.pDocScript->OpenDocumentFile(m_FileDiag->m_ofn.lpstrFile);
        }
        else
        {
            theApp.pDocTemplate->OpenDocumentFile(m_FileDiag->m_ofn.lpstrFile);
        }
	}
	delete m_FileDiag;
}
/*
void CKapsulApp::OnFileSave() 
{
    CDeskDoc *tmpdoc = (CDeskDoc *) theApp.pDocTemplate3D->GetDocument();
    if (tmpdoc->IsModified()) 
    {
        OnFileSaveAs();
    }
    else
    {
        tmpdoc->SetModifiedFlag(FALSE);
        gen->Process(KM_SAVEDESK,0,0);
        CString tmp=tmpdoc->GetPathName();
        tmpdoc->genSave->Write(dk,tmp.GetBuffer(_MAX_PATH));
    }	
}
*/