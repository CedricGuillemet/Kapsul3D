// Kapsul.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "SelTypeDoc.h"
#include "KMainEdit.h"
#include "KSelectRenderer.h"
#include "KInstall.h"
#include "Htmlhelp.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CMainFrame* mainf;
CKOption *KOption;
extern CString ReadFilter,WriteFilter;
extern CKPluginManager *GKPlugins;
extern CTVTestDlg	*m_DesksBrowser;

/////////////////////////////////////////////////////////////////////////////
// CKapsulApp

BEGIN_MESSAGE_MAP(CKapsulApp, CWinAppEx)
	//{{AFX_MSG_MAP(CKapsulApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_WINDOW_TOGGLEFULLSCREEN, OnWindowTogglefullscreen)
	ON_COMMAND(ID_HELP_CONTENTS, OnHelpContents)
	ON_COMMAND(ID_HELP_INDEX, OnHelpIndex)
	ON_COMMAND(ID_HELP_SEARCH, OnHelpSearch)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	//ON_COMMAND(ID_FILE_NEW, CWinAppEx::OnFileNew)
	//ON_COMMAND(ID_FILE_OPEN, CWinAppEx::OnFileOpen)
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
extern CKScenePlugin *GCurPlug;
//extern CKDrawScene *GDrawScene;
//extern CKEntityManager *m_EntMngr;
CKLocalization loc;

void WriteOptionsXML(void);

/////////////////////////////////////////////////////////////////////////////
// CKapsulApp initialization

BOOL CKapsulApp::InitInstance()
{
	SetRegistryKey(_T("Kapsul"));

	if( !CWinAppEx::InitInstance( _T( "{DBC808B4-CA23-4ce7-B82C-A1B81C37DBB1}" ) ) )
        return FALSE;
    
    
	// Standard initialization
	
	FullScreen=false;

	CKInstall KapsulInstalle;

	if (GetProfileInt("","Firstboot",0))
	{
		KapsulInstalle.StoreProgramPath();
		KapsulInstalle.WriteOptionsXML();
		GKPlugins=new CKPluginManager(false);
		GKPlugins->RegisterFilePlugs("plugins\\");

		KapsulInstalle.RegisterFileTypes();
		
		WriteProfileInt("","FirstBoot",0);
		MessageBox(NULL,"Kapsul has finished its setup","Installation complete",MB_ICONINFORMATION|MB_OK);
		return TRUE;
	}

	KapsulInstalle.SetProgramPath();

	loc.ReadXmlStringFile("Localization.xml");
	SetLocal(&loc);

	
//	GKPlugins->InitRendererInterface("plugins\\KOGLRenderer.dll");

	AfxEnableControlContainer();

	LoadStdProfileSettings(8);  // Load standard INI file options (including MRU)

	KOption=new CKOption(this);

	GKPlugins=new CKPluginManager(true);
	
	// Select Renderer

	if ( (strcmp(m_lpCmdLine,"SELECTRENDERER")==0) || (!GKPlugins->IsRendererValid(KOption->GetRenderer())) )
	{
		CKSelectRenderer SelRenderer;
		strcpy(m_lpCmdLine,"\0");

		SelRenderer.DoModal();
	}
	// create Selected Renderer Interface
	GKPlugins->InitRendererInterface(KOption->GetRenderer());
   

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.
	
	pDocTemplate = new CMultiDocTemplate(
		IDR_KAPSULDESK,
		RUNTIME_CLASS(CDeskDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CKMainEdit));
	AddDocTemplate(pDocTemplate);


	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	m_pMainWnd = pMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	mainf=pMainFrame;
/*
	m_EntMngr=new CKEntityManager();
	*/
	LoadXmlPresets();

	pDocTemplate->m_hMenuShared=pMainFrame->NewMenu();
	pMainFrame->m_hMenuDefault=pMainFrame->NewDefaultMenu();
 
	// This simulates a window being opened if you don't have
	// a default window displayed at startup
	pMainFrame->OnUpdateFrameMenu(pMainFrame->m_hMenuDefault);
 
	

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	/*
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
*/
	// force new desk
	if (KOption->OpenEmpty()&&(m_lpCmdLine[0] == '\0'))
	{
		pDocTemplate->OpenDocumentFile(NULL);
		pMainFrame->MDIMaximize(pMainFrame->MDIGetActive());
	}

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

	bool m_bStartup = !theApp.GetProfileInt(_T("Tip"), _T("StartUp"), 0);

	if (m_lpCmdLine[0] != '\0')
    {
		OpenCmdLine(m_lpCmdLine);
		CMDIChildWnd* tmpMdiChld=pMainFrame->MDIGetActive();

		if (tmpMdiChld)
			pMainFrame->MDIMaximize(tmpMdiChld);
	}


	if (m_bStartup)
		pMainFrame->OnHelpTipoftheday();

	return TRUE;
}
void CKapsulApp::OpenCmdLine(char *FileName)
{
	// check file Type
	//if (diag.ExtInd==0)
	{
        CDeskDoc *tmpdoc=(CDeskDoc*)theApp.pDocTemplate->OpenDocumentFile(FileName);
		if (tmpdoc!=NULL)
		{
			if (!tmpdoc->IsKindOf( RUNTIME_CLASS( CView ) ) ) 
			{
				if (GCurPlug!=NULL)
					GCurPlug->SetScene(tmpdoc->m_Scene);

				UpdateHierarchie(tmpdoc->m_Scene);
				//SetForegroundWindow(
				//tmpdoc->getv>seta
			}
		}
    }
	/*
	else
	{
		// plugin Doc/View
		GKPlugins->DocViewPlugs[(diag.ExtInd-1)]->Process(KM_OPENFILE,(UINT)FileName,0);

	}
	*/
}
void CKapsulApp::OnAppAbout()
{

	CAboutDlg aboutDlg;
	aboutDlg.DoModal();

}
CKViewEdit *curpr=NULL;

Vertex RunAv;
int FrameCount;


BOOL CKapsulApp::OnIdle(LONG lCount)
{
    BOOL bMore = CWinAppEx::OnIdle(lCount);
	CKCamera *cam;
	
	//return false;
	if (curpr!=NULL)
	{
	//CKCamera *daCam;
		if (curpr->m_Scene->ViewType[curpr->m_Scene->Active]==VIEWTYPE_CAMERA)
			if (curpr->m_Scene->cam[curpr->m_Scene->Active]!=NULL)
				cam=curpr->m_Scene->cam[curpr->m_Scene->Active];

		if (curpr->m_Scene->ViewType[curpr->m_Scene->Active]==VIEWTYPE_PERSPECTIVE)
			cam=&curpr->m_Scene->Perspective[curpr->m_Scene->Active];

		//cam=&curpr->m_Scene->Perspective[curpr->m_Scene->Active];

		curpr->m_DInput.ProcessMouse();
		curpr->m_DInput.ProcessKB();
		
		cam->angle_b=-curpr->m_DInput.m_MouseState.lX;
		cam->angle_a=-curpr->m_DInput.m_MouseState.lY;

		// AV
		if (curpr->m_DInput.buffer[(OemKeyScan('S')&0xffff)])
		{
			if (RunAv.z<0.04f) RunAv.z+=0.0008f;
		}
		else
		// AR
		if (curpr->m_DInput.buffer[(OemKeyScan('X')&0xffff)])
		{
			if (RunAv.z>-0.04f) RunAv.z-=0.0008f;
		}
		else
		{
			if (RunAv.z<0) RunAv.z+=0.0008f;
			if (RunAv.z>0) RunAv.z-=0.0008f;
		}

		// left
		if (curpr->m_DInput.buffer[(OemKeyScan('W')&0xffff)])
		{
			if (RunAv.x<0.04f) RunAv.x+=0.0008f;
		}
		else
			

		// right
		if (curpr->m_DInput.buffer[(OemKeyScan('C')&0xffff)])
		{
			if (RunAv.x>-0.04f) RunAv.x-=0.0008f;
		}
		else
		{
			if (RunAv.x<0) RunAv.x+=0.0008f;
			if (RunAv.x>0) RunAv.x-=0.0008f;
		}
			
		// wheel
		if (curpr->m_DInput.m_MouseState.lZ!=0)
		{
			int zDelta=curpr->m_DInput.m_MouseState.lZ;

			if (curpr->m_Scene->ViewType[curpr->m_Scene->Active]==VIEWTYPE_CAMERA)
			{

				if (curpr->m_Scene->cam[curpr->m_Scene->Active]!=NULL)
				{
					if (zDelta>0)
						curpr->m_Scene->cam[curpr->m_Scene->Active]->Run(30);
					else
						curpr->m_Scene->cam[curpr->m_Scene->Active]->Run(-30);
				}
			}
			else
			{
				if (curpr->m_Scene->ViewType[curpr->m_Scene->Active]==VIEWTYPE_PERSPECTIVE)
				{
					if (zDelta>0)
						curpr->m_Scene->Perspective[curpr->m_Scene->Active].Run(30);
					else
						curpr->m_Scene->Perspective[curpr->m_Scene->Active].Run(-30);
				}
			}			
		}


		Vertex Avval=(cam->Dest-cam->Source);
		Avval.Normalize();
		Avval.x*=RunAv.z;
		Avval.y*=RunAv.z;
		Avval.z*=RunAv.z;
		Avval.x*=KOption->MotionValue();
		Avval.y*=KOption->MotionValue();
		Avval.z*=KOption->MotionValue();

		float fact=(RunAv.x/cam->Length)*KOption->MotionValue();
		cam->Strafe(fact);

		cam->SetCamera();
		cam->Source+=Avval;
		cam->Dest+=Avval;
		FrameCount++;
		DrawView(curpr->m_Scene->Active);
			
		return true;
	}
	return bMore;
}

void CKapsulApp::OnFileNew() 
{
	theApp.pDocTemplate->OpenDocumentFile(NULL);
	mainf->MDIMaximize(mainf->MDIGetActive());
	if (GCurPlug!=NULL)
	{
		CMDIChildWnd *pChild = (CMDIChildWnd *) mainf->GetActiveFrame();
    
		//m_DesksBrowser->m_cDialog.SetPlug(gen->Param(),(CWnd *)&m_DesksBrowser->m_cDialog);

		if (pChild->GetActiveView()!=NULL)
		{
			CDeskDoc *tmpdoc = (CDeskDoc *) pChild->GetActiveView()->GetDocument();
			GCurPlug->SetScene(tmpdoc->m_Scene);
		}
	}
}

void CKapsulApp::OnFileOpen() 
{
	CString fileName;
	BXFileDialog dlg(TRUE, TRUE, TRUE);


	LPTSTR pch = ReadFilter.GetBuffer(1);//szFilter.GetBuffer(0); // modify the buffer in place
	                                    // MFC delimits with '|' not '\0'
	
	while ((pch = _tcschr(pch, '|')) != NULL)
			*pch++ = '\0';

	CString strTitle("Select files to open");

	dlg.m_ofn.lpstrFilter = ReadFilter ;
	dlg.m_ofn.lpstrTitle = strTitle;
	dlg.m_ofn.lpstrFile = fileName.GetBuffer(_MAX_PATH);
	dlg.m_ofn.hwndOwner = AfxGetMainWnd()->m_hWnd; 
	dlg.m_ofn.Flags|= OFN_ALLOWMULTISELECT ;

	dlg.SetAppearance(BXFileDialog::eAppearance::APPEARANCE_VSDOTNET);

	if (dlg.DoModal()==IDOK)
	{
		int nCount = 0;
		POSITION pos = dlg.GetStartPosition();
		while (pos != NULL)
		{
			OpenCmdLine(dlg.GetNextPathName(pos).GetBuffer(0));
			nCount++;
		}
	}
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

void CKapsulApp::OnWindowTogglefullscreen() 
{

	/*
	if (!FullScreen)
	{

	//pMainFrame->SetWindowPlacement(&wp);
	//ShowWindow(SW_SHOWNORMAL);
		m_pMainWnd->ShowWindow(SW_RESTORE);
		m_pMainWnd->MoveWindow(0,-23,1280,1060);
		//MessageBox("OK");

		
		HWND hShellTrayWnd = ::FindWindow(_T("Shell_TrayWnd"), NULL);
		::ShowWindow(hShellTrayWnd,SW_HIDE);

		
	}
	else
	{
		m_pMainWnd->MoveWindow(0,0,1280,1024);
		//MessageBox("OK");

		
		HWND hShellTrayWnd = ::FindWindow(_T("Shell_TrayWnd"), NULL);
		::ShowWindow(hShellTrayWnd,SW_SHOWNORMAL);

	}
	FullScreen=!FullScreen;
	*/
}

int CKapsulApp::ExitInstance() 
{
//	delete m_EntMngr;
	
	return CWinAppEx::ExitInstance();
}

void CKapsulApp::OnHelpContents() 
{
	CString HelpFile=((CKOption*)GetGOption())->m_AppDir;
	HelpFile+="KapsulDoc.chm::/UserDoc/";
	HWND hwnd =HtmlHelp(GetDesktopWindow(),HelpFile,HH_DISPLAY_TOC,NULL);
	::ShowWindow(hwnd,SW_SHOWMAXIMIZED);
}

void CKapsulApp::OnHelpIndex() 
{
	CString HelpFile=((CKOption*)GetGOption())->m_AppDir;
	HelpFile+="KapsulDoc.chm::/UserDoc/";
	HWND hwnd =HtmlHelp(GetDesktopWindow(),HelpFile,HH_DISPLAY_INDEX,NULL);	
	::ShowWindow(hwnd,SW_SHOWMAXIMIZED);
}

void CKapsulApp::OnHelpSearch() 
{
	CString HelpFile=((CKOption*)GetGOption())->m_AppDir;
	HelpFile+="KapsulDoc.chm::/UserDoc/";
	HWND hwnd =HtmlHelp(GetDesktopWindow(),HelpFile,HH_DISPLAY_TOC,NULL);
	::ShowWindow(hwnd,SW_SHOWMAXIMIZED);
}
