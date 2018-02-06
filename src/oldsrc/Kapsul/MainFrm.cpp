// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"

#include "SkyBoxEd.h"
#include "mainfrm.h"
#include "EntiDlg.h"
//#include "resource.h"
/*
#include <vector>
using std::vector;
*/

extern COption __declspec( dllimport )KOption;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_UNSELECTALL WM_USER+9
extern CKapsulApp theApp;

char		*ReadFilter,*WriteFilter;

CCoolDialogBar m_wndDialogBar;

class assocFold
{
public:
    CString PluginFolder;
    int FolderInd;

    assocFold(CString pf,int fi) { PluginFolder=pf; FolderInd=fi; };

};

// variables globales

bool bCentered=false;
bool bCrossing=false;
bool bSnap=true;

int daButton;
int iEditMode;

LibContainer *KLibs;
int FunctionID;
OGLView *View;
Desk *CurrentDesk;
GenericLib *gen=NULL;
int CurrentCursor=0;
Desk ClipBoard(NULL,NULL);
GenericLib *CurrentPlug=NULL;

MainEdit *FirstMainEdit=NULL,*NextMainEdit=NULL;

//CEditPlugFolder cepf;

void AddMainEdit(MainEdit *daMain)
{
	if (FirstMainEdit==NULL) 
	{
		FirstMainEdit=daMain;
		NextMainEdit=daMain;
	}
	else
	{
		MainEdit *tmp;
		tmp=NextMainEdit;
		NextMainEdit->Next=daMain;
		NextMainEdit=daMain;
		NextMainEdit->Prev=tmp;
	}
}

void DelMainEdit(MainEdit *daMain)
{
    if (daMain->Prev!=NULL)
        daMain->Prev->Next=daMain->Next;

    if (daMain->Next!=NULL)
        daMain->Next->Prev=daMain->Prev;

    if (daMain==FirstMainEdit) FirstMainEdit=daMain->Next;

    if (daMain==NextMainEdit) NextMainEdit=daMain->Prev;

}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame
//    ON_NOTIFY(TBN_DROPDOWN, AFX_IDW_TOOLBAR, OnToolbarDropDown)

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_COMMAND(ID_HELP_TIPOFTHEDAY, OnHelpTipoftheday)
	ON_COMMAND(ID_TOOLS_OPTION, OnToolsOption)
	ON_COMMAND(ID_EDIT_SELECT_CIRCLE, OnEditSelectCircle)
	ON_COMMAND(ID_EDIT_SELECT_FENCE, OnEditSelectFence)
	ON_COMMAND(ID_EDIT_SELECT_QUAD, OnEditSelectQuad)
	ON_COMMAND(ID_EDIT_SELECT_SINGLE, OnEditSelectSingle)
	ON_COMMAND(ID_EDIT_SCALE, OnEditScale)
	ON_COMMAND(ID_EDIT_ROTATE, OnEditRotate)
	ON_COMMAND(ID_EDIT_MOVEAXE, OnEditMoveaxe)
	ON_COMMAND(ID_EDIT_MOVE, OnEditMove)
	ON_COMMAND(ID_EDIT_MODE_VERTEX, OnEditModeVertex)
	ON_COMMAND(ID_EDIT_MODE_OBJECT, OnEditModeObject)
	ON_COMMAND(ID_EDIT_MODE_FACE, OnEditModeFace)
	ON_COMMAND(ID_EDIT_DELETE, OnEditDelete)
	ON_COMMAND(ID_VIEW_MOVESPAN, OnViewMovespan)
	ON_COMMAND(ID_VIEW_REGIONFIT, OnViewRegionfit)
	ON_COMMAND(ID_VIEW_ROTATE, OnViewRotate)
	ON_COMMAND(ID_VIEW_ZOOMINOUT, OnViewZoominout)
	ON_COMMAND(ID_VIEW_EXTENDSVIEWS, OnViewExtendsviews)
	ON_COMMAND(ID_VIEW_EXTENDVIEW, OnViewExtendview)
	ON_COMMAND(ID_VIEW_BUILDBAR, OnViewBuildbar)
	ON_COMMAND(ID_VIEW_PLUGINBAR, OnViewPluginbar)
	ON_COMMAND(ID_VIEW_MODIFY, OnViewModify)
	ON_COMMAND(ID_VIEW_MODIFYVIEW, OnViewModifyview)
	ON_UPDATE_COMMAND_UI(ID_VIEW_BUILDBAR, OnUpdateViewBuildbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MODIFY, OnUpdateViewModify)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MODIFYVIEW, OnUpdateViewModifyview)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PLUGINBAR, OnUpdateViewPluginbar)
	ON_COMMAND(ID_VIEW_SELECTION, OnViewSelection)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SELECTION, OnUpdateViewSelection)
	ON_COMMAND(ID_VIEW_VIEWCONFIGURATION, OnViewViewconfiguration)
	ON_UPDATE_COMMAND_UI(ID_VIEW_VIEWCONFIGURATION, OnUpdateViewViewconfiguration)
	ON_COMMAND(ID_VIEW_EDITMODE, OnViewEditmode)
	ON_UPDATE_COMMAND_UI(ID_VIEW_EDITMODE, OnUpdateViewEditmode)
	ON_COMMAND(ID_VIEW_RENDERMODE_MAPPED, OnViewRendermodeMapped)
	ON_COMMAND(ID_VIEW_RENDERMODE_WIRE, OnViewRendermodeWire)
	ON_COMMAND(ID_VIEW_RENDERMODE, OnViewRendermode)
	ON_UPDATE_COMMAND_UI(ID_VIEW_RENDERMODE, OnUpdateViewRendermode)
	ON_COMMAND(ID_BUILD_CENTERED, OnBuildCentered)
	ON_COMMAND(ID_BUILD_CROSSING, OnBuildCrossing)
	ON_COMMAND(ID_BUILD_SNAP, OnBuildSnap)
	ON_UPDATE_COMMAND_UI(ID_BUILD_CENTERED, OnUpdateBuildCentered)
	ON_UPDATE_COMMAND_UI(ID_BUILD_CROSSING, OnUpdateBuildCrossing)
	ON_UPDATE_COMMAND_UI(ID_BUILD_SNAP, OnUpdateBuildSnap)
	ON_UPDATE_COMMAND_UI(ID_EDIT_MODE_FACE, OnUpdateEditModeFace)
	ON_UPDATE_COMMAND_UI(ID_EDIT_MODE_OBJECT, OnUpdateEditModeObject)
	ON_UPDATE_COMMAND_UI(ID_EDIT_MODE_VERTEX, OnUpdateEditModeVertex)
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_TOOLS_SKYBOXEDITOR, OnToolsSkyboxeditor)
	ON_COMMAND(ID_VIEW_VIEWTYPES, OnViewViewtypes)
	ON_UPDATE_COMMAND_UI(ID_VIEW_VIEWTYPES, OnUpdateViewViewtypes)
	ON_COMMAND(ID_TOOLS_PLUGINSFOLDERS, OnToolsPluginsfolders)
	ON_COMMAND(ID_EDIT_REDO, OnEditRedo)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, OnUpdateEditRedo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_COMMAND(ID_VIEW_MAPSBROWSER, OnViewMapsbrowser)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MAPSBROWSER, OnUpdateViewMapsbrowser)
	ON_MESSAGE(WM_SETSTATUS,OnWmSetStatus)
	ON_MESSAGE(WM_DRAWSCENE,OnWmDrawScene)
    ON_MESSAGE(WM_SETPLUGIN,OnWmSetPlugin)
    ON_MESSAGE(WM_SETMOUSECURSOR,OnWmSetMouseCursor)
	ON_COMMAND(ID_TOOLS_ENTITYMANAGER, OnToolsEntitymanager)
	ON_COMMAND(ID_VIEW_DESKFILEBROWSER, OnViewDeskfilebrowser)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DESKFILEBROWSER, OnUpdateViewDeskfilebrowser)
	//}}AFX_MSG_MAP
    ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)
    ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipText)

	ON_COMMAND(ID_VIEW_COMPILATIONTOOLS, OnViewCompilationtools)
	ON_UPDATE_COMMAND_UI(ID_VIEW_COMPILATIONTOOLS, OnUpdateViewCompilationtools)
	ON_COMMAND(ID_VIEW_ANIMATIONBAR, OnViewAnimationbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ANIMATIONBAR, OnUpdateViewAnimationbar)
	ON_COMMAND(ID_VIEW_TOOLBAR, OnViewToolbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBAR, OnUpdateViewToolbar)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	/*
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CONTROLS,
	ID_INDICATOR_MISC,
*/
	ID_SEPARATOR,               // status line indicator 
	ID_EDIT_INDICATOR_POSITION,	 
	ID_EDIT_INDICATOR_COL,
	ID_EDIT_INDICATOR_CRLF,
	ID_INDICATOR_OVR,	
	ID_EDIT_INDICATOR_READ,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	//m_pWndCurrentChild=NULL;
}

CMainFrame::~CMainFrame()
{
    /*
	delete [] ReadFilter;
	delete [] WriteFilter;
*/

}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    int i;

	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	/*
    if (m_wndMDIClient.Attach(m_hWndMDIClient) == 0)
    {
        TRACE0("Failed to attach MDIClient.\n");
        return -1;      // fail to create
    }
	*/

	// Splash screen

	CSplashWnd::ShowSplashScreen(this);

	// register DLL


	ReadFilter=new char [1024];
	ReadFilter[0]=0;
	WriteFilter=new char [1024];
	WriteFilter[0]=0;


	KLibs=new(LibContainer);

	// compute files dll

	memset(ReadFilter,0,1024);

	strcat(ReadFilter,"Kapsul script (*.ksc)|*.ksc|");

	strcat(ReadFilter,"All supported 3D formats");
	strcat(ReadFilter,"|");

	for (i=0;i<KLibs->nb2FilesLib;i++)
	{
		if (KLibs->FilesLib[i]->ReadSupport)
		{
			strcat(ReadFilter,KLibs->FilesLib[i]->RFilter);
			strcat(ReadFilter,";");
		}
	}
	strcat(ReadFilter,"|");

	for (i=0;i<KLibs->nb2FilesLib;i++)
	{
		if (KLibs->FilesLib[i]->ReadSupport)
		{
			strcat(ReadFilter,KLibs->FilesLib[i]->RFileDesc);
			strcat(ReadFilter,"|");
			strcat(ReadFilter,KLibs->FilesLib[i]->RFilter);
			strcat(ReadFilter,"|");
		}

		if (KLibs->FilesLib[i]->WriteSupport)
		{
			strcat(WriteFilter,KLibs->FilesLib[i]->WFileDesc);
			strcat(WriteFilter,"|");
			strcat(WriteFilter,KLibs->FilesLib[i]->WFilter);
			strcat(WriteFilter,"|");
		}

	}

	for (i=0;i<1024;i++)
	{
		if (ReadFilter[i]==0x7c) ReadFilter[i]='\0';
		if (WriteFilter[i]==0x7c) WriteFilter[i]='\0';
	}

	// Kore init

    SetStatusHWND(m_hWnd,(CWnd*)this);
    SetFuncPtr(&FunctionID,&bCrossing,&bCentered,&bSnap,&KOption);
    SetButtonPtr((int *)&daButton);
	SetLib(KLibs);
	// View
	View = new OGLView();

    // Load Option
    
    LoadOptions();

	


	///////////////////////////////////////////////////////////////////////////
	// Bars

    //m_wndOutBar=new (COutBar);

	// Status bar

	m_wndStatusBar.Create(this);//,0, 2, 1);
	m_wndStatusBar.SetIndicators(indicators,sizeof(indicators)/sizeof(UINT));

    m_wndStatusBar.SetPaneInfo( 0, m_wndStatusBar.GetItemID( 0 ), SBPS_STRETCH, NULL );
	m_wndStatusBar.SetPaneInfo(1, ID_INDICATOR_CONTROLS, SBPS_NORMAL, 200);
	m_wndStatusBar.SetPaneInfo(2, ID_INDICATOR_MISC, SBPS_NORMAL, 200);

	

	// Main toolbar
	
	m_wndToolBar.CreateEx(this,TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,CRect(0, 0, 0, 0),101001);
	m_wndToolBar.LoadToolBar(IDR_MAINFRAME);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	// select
	m_wndToolBarSelect.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,CRect(0, 0, 0, 0),101002);
	m_wndToolBarSelect.LoadToolBar(IDR_SELECTBAR);
	m_wndToolBarSelect.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBarSelect);

	// View conf
	m_wndToolBarViewConf.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,CRect(0, 0, 0, 0),101003);
	m_wndToolBarViewConf.LoadToolBar(IDR_VIEWCONFIG);
	m_wndToolBarViewConf.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBarViewConf);

	// Modify
	m_wndToolBarModify.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,CRect(0, 0, 0, 0),101004);
	m_wndToolBarModify.LoadToolBar(IDR_MODIFY);
	m_wndToolBarModify.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBarModify);

	// render mode
	m_wndToolRender.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,CRect(0, 0, 0, 0),101005);
	m_wndToolRender.LoadToolBar(IDR_RENDER);
	m_wndToolRender.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolRender);

    
    
    // Anim dialog

	m_wndAnim.Create(this, &m_cAnimDlg, CString("Animate"), IDD_ANIM);
    m_wndAnim.SetBarStyle(m_wndAnim.GetBarStyle()|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_SIZE_DYNAMIC);
	m_wndAnim.EnableDocking(CBRS_ALIGN_TOP|CBRS_ALIGN_BOTTOM);
	DockControlBar(&m_wndAnim);

	// docking view
	
	m_wndDialogBar.Create(this, &m_cDialog, CString("Plugin"), IDD_TSCROLL_DIALOG);
    m_wndDialogBar.SetBarStyle(m_wndDialogBar.GetBarStyle()|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_SIZE_DYNAMIC);
	m_wndDialogBar.EnableDocking(CBRS_ALIGN_LEFT|CBRS_ALIGN_RIGHT);
	DockControlBar(&m_wndDialogBar);


	m_Plugs.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,CRect(0, 0, 0, 0),101210);
//	m_Plugs.LoadToolBar(IDR_RENDER);
	m_Plugs.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_Plugs);


    // menu bar
	/*
	GetMenu( )->CreateEx(this, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_RAISEDBORDER,CRect(0, 0, 0, 0),101000);
    GetMenu( )->LoadMenuBar(IDR_MAINFRAME);
    GetMenu( )->EnableDockingEx(CBRS_ALIGN_ANY);
    EnableDocking(CBRS_ALIGN_ANY);
    DockControlBar(&m_wndMenuBar);
*/
    

	// Projects
/*
    m_wndProjects.Create(this, &m_cProjects, CString("Project"), IDD_PROJECT);
    m_wndProjects.SetBarStyle(m_wndProjects.GetBarStyle()|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_SIZE_DYNAMIC);
	m_wndProjects.EnableDocking(CBRS_ALIGN_LEFT|CBRS_ALIGN_RIGHT);
	DockControlBar(&m_wndProjects);	

    // compile out

	m_wndCompile.Create(this, &m_cCompile, CString("Compilation"), IDD_COMPILEOUT);
    m_wndCompile.SetBarStyle(m_wndCompile.GetBarStyle()|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_SIZE_DYNAMIC);
	m_wndCompile.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndCompile);	
*/
    // Compilation
	m_wndToolCompilation.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,CRect(0, 0, 0, 0),101777);
	m_wndToolCompilation.LoadToolBar(IDR_SEER);
	m_wndToolCompilation.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolCompilation);


	// mat browser

	m_wndMatBrowser.Create(this, &m_MatBrowser, CString("MatBrowse"), IDD_MATBROWSER);
    m_wndMatBrowser.SetBarStyle(m_wndMatBrowser.GetBarStyle()|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_SIZE_DYNAMIC);
	m_wndMatBrowser.EnableDocking(CBRS_ALIGN_TOP|CBRS_ALIGN_BOTTOM|CBRS_ALIGN_LEFT|CBRS_ALIGN_RIGHT);
	DockControlBar(&m_wndMatBrowser);

	m_wndDesksBrowser.Create(this, &m_DesksBrowser, CString("DesksBrowse"), IDD_TVTEST_DIALOG);
    m_wndDesksBrowser.SetBarStyle(m_wndDesksBrowser.GetBarStyle()|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_SIZE_DYNAMIC);
	m_wndDesksBrowser.EnableDocking(CBRS_ALIGN_TOP|CBRS_ALIGN_BOTTOM|CBRS_ALIGN_LEFT|CBRS_ALIGN_RIGHT);
	DockControlBar(&m_wndDesksBrowser);

	// modif view
	m_wndToolModifView.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,CRect(0, 0, 0, 0),101147);
	m_wndToolModifView.LoadToolBar(IDR_MODIFVIEW);
	m_wndToolModifView.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolModifView);

	// modif view
	m_wndToolTypeView.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,CRect(0, 0, 0, 0),101016);
	m_wndToolTypeView.LoadToolBar(IDR_VIEWS);
	m_wndToolTypeView.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolTypeView);

	// "outlook" bar
	/*
	m_wndOutBar->Create(this, NULL, CString("Build"), NULL);
    m_wndOutBar->SetBarStyle(m_wndOutBar->GetBarStyle()|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_SIZE_DYNAMIC);
	m_wndOutBar->EnableDocking(CBRS_ALIGN_LEFT|CBRS_ALIGN_RIGHT);
	DockControlBar(m_wndOutBar);
*/
	
	// Mode
	m_wndMode.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,CRect(0, 0, 0, 0),101302);
	m_wndMode.LoadToolBar(IDR_MODE);
	m_wndMode.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndMode);

    // Script
/*
    m_wndToolScript.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,CRect(0, 0, 0, 0),101018);
	m_wndToolScript.LoadToolBar(IDR_EDITTEXT);
	m_wndToolScript.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolScript);
*/
	///////////////////////////////////////////////////////////////////////////
	// Outlook bar filling
    
    RefreshOutBar();
	//m_wndOutBar->SetImageList(&imaLarge, CGfxOutBarCtrl::fLargeIcon);


	// Mode combo
    CClientDC DC(GetDesktopWindow());
    long logical_pixels = DC.GetDeviceCaps(LOGPIXELSX);
    if(logical_pixels <100) gSmallFont.CreatePointFont(67,"DEFAULT",NULL);  
		else gSmallFont.CreatePointFont(50,"DEFAULT",NULL); 
    

	int index = 0;
    while(m_wndMode.GetItemID(index)!=IDP_CBENT) index++;
	
	RECT rect;
    //next convert that button to a seperator and get its position
    m_wndMode.SetButtonInfo(index, IDP_CBENT, TBBS_SEPARATOR, 80);
    m_wndMode.GetItemRect(index, &rect);

    //expand the rectangle to allow the combo box room to drop down
    rect.top+=2;
    rect.bottom += 200;

    // then .Create the combo box and show it
    m_wndMode.m_wndSnap.Create(WS_CHILD|WS_VISIBLE | CBS_DROPDOWNLIST , rect, &m_wndMode, 12008);
    m_wndMode.m_wndSnap.ShowWindow(SW_SHOW);

    //fill the combo box
    m_wndMode.m_wndSnap.AddString("ALL");
    m_wndMode.m_wndSnap.AddString("CAMERA");
    m_wndMode.m_wndSnap.AddString("SHAPE");
    m_wndMode.m_wndSnap.AddString("LIGHT");
    m_wndMode.m_wndSnap.AddString("OBJECT");
    m_wndMode.m_wndSnap.AddString("SKELETTON");
    m_wndMode.m_wndSnap.SetCurSel(0);
	m_wndMode.m_wndSnap.SendMessage(WM_SETFONT,(WPARAM)HFONT(gSmallFont),TRUE); 


    // status out
	SetHierarchieTree(m_DesksBrowser.m_hWnd);

	OnEditModeObject();
	LoadBarState(_T("Editor State"));

	return 0;
}

void CMainFrame::LoadOptions(void)
{
    
    int i=0;
    char temp[256],temp2[_MAX_PATH];
    
    wsprintf(temp,"MapPath%d",i);
	strcpy(temp2,(LPCTSTR)theApp.GetProfileString("MapPath",temp));
	while(strcmp(temp2,"")!=0)
	{
		KOption.AddMapDir(temp2);
		i++;
		wsprintf(temp,"MapPath%d",i);
		strcpy(temp2,(LPCTSTR)theApp.GetProfileString("MapPath",temp));
	}
    
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


/*
void CMainFrame::OnToolbarDropDown(NMTOOLBAR* pnmtb, LRESULT *plr)
{
	CWnd *pWnd;
	UINT nID;

	// load and display popup menu
	CMenu menu;
	menu.LoadMenu(nID);
	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup);

//    pPopup->AppendMenu(MF_BITMAP,50000,(const char*)LoadBitmap(AfxGetInstanceHandle( ),(const char*)IDB_BITMAP1));
	
	CRect rc;
	pWnd->SendMessage(TB_GETRECT, pnmtb->iItem, (LPARAM)&rc);
	pWnd->ClientToScreen(&rc);
	
	pPopup->TrackPopupMenu( TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_VERTICAL,
		rc.left, rc.bottom, this, &rc);
}
*/

void CMainFrame::OnDestroy() 
{
    
	delete [] ReadFilter;
	delete [] WriteFilter;

	delete KLibs;

	delete View;

	CMDIFrameWnd::OnDestroy();

}

void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	SaveBarState(_T("Editor State"));

	WINDOWPLACEMENT wp;

	wp.length=sizeof(WINDOWPLACEMENT);
	theApp.m_pMainWnd->GetWindowPlacement(&wp);

	theApp.WriteProfileInt ("Editor State","flags",wp.flags);
	theApp.WriteProfileInt("Editor State","showCmd",wp.showCmd);
	theApp.WriteProfileInt("Editor State","ptMinPositionx",wp.ptMinPosition.x);
	theApp.WriteProfileInt("Editor State","ptMinPositiony",wp.ptMinPosition.y);
	theApp.WriteProfileInt("Editor State","ptMaxPositionx",wp.ptMaxPosition.x);
	theApp.WriteProfileInt("Editor State","ptMaxPositiony",wp.ptMaxPosition.y);
	theApp.WriteProfileInt("Editor State","rcNormalPositionl",wp.rcNormalPosition.left);
	theApp.WriteProfileInt("Editor State","rcNormalPositionr",wp.rcNormalPosition.right);
	theApp.WriteProfileInt("Editor State","rcNormalPositiont",wp.rcNormalPosition.top);
	theApp.WriteProfileInt("Editor State","rcNormalPositionb",wp.rcNormalPosition.bottom);

	CMDIFrameWnd::OnClose();
}

void CMainFrame::OnHelpTipoftheday() 
{
	CTipDlg dlg;
	dlg.DoModal();		
}

void CMainFrame::OnToolsOption() 
{
    
	MOptions Options;
	Options.DoModal();	
    // Should Delete all stuffs
//    KOption.DelAllMapDir();
    LoadOptions();
    
}

void CMainFrame::OnEditSelectCircle() 
{
	FunctionID=EDIT_SELECTCIRCLE;
    if (gen!=NULL) gen->Process(KM_UNSETPLUGIN,0,0);
}

void CMainFrame::OnEditSelectFence() 
{
	FunctionID=EDIT_SELECTFENCE;
    if (gen!=NULL) gen->Process(KM_UNSETPLUGIN,0,0);
}

void CMainFrame::OnEditSelectQuad() 
{
	FunctionID=EDIT_SELECTQUAD;
    if (gen!=NULL) gen->Process(KM_UNSETPLUGIN,0,0);
}

void CMainFrame::OnEditSelectSingle() 
{
	FunctionID=EDIT_SELECTSINGLE;
    if (gen!=NULL) gen->Process(KM_UNSETPLUGIN,0,0);
}

void CMainFrame::OnEditScale() 
{
	FunctionID=EDIT_SCALEBUF;
    if (gen!=NULL) gen->Process(KM_UNSETPLUGIN,0,0);
}

void CMainFrame::OnEditRotate() 
{
	FunctionID=EDIT_ROTATEBUF;
    if (gen!=NULL) gen->Process(KM_UNSETPLUGIN,0,0);
}

void CMainFrame::OnEditMoveaxe() 
{
	FunctionID=EDIT_PUTAXIS;
    if (gen!=NULL) gen->Process(KM_UNSETPLUGIN,0,0);
}

void CMainFrame::OnEditMove() 
{
	FunctionID=EDIT_MOVEBUF;	
    if (gen!=NULL) gen->Process(KM_UNSETPLUGIN,0,0);
}

void CMainFrame::OnEditDelete() 
{
	// TODO: Add your command handler code here
	
}


void CMainFrame::OnViewMovespan() 
{
	FunctionID=EDIT_MOVEVIEW;
    if (gen!=NULL) gen->Process(KM_UNSETPLUGIN,0,0);

    //m_wndDialogBar.m_cDialog->ModifyStyleEx(0,WS_EX_CLIENTEDGE,0);
}

void CMainFrame::OnViewRegionfit() 
{
	FunctionID=EDIT_REGIONFIT;
    if (gen!=NULL) gen->Process(KM_UNSETPLUGIN,0,0);
	
}

void CMainFrame::OnViewRotate() 
{
	FunctionID=EDIT_ROTATEVIEW;
    if (gen!=NULL) gen->Process(KM_UNSETPLUGIN,0,0);
	
}

void CMainFrame::OnViewZoominout() 
{
	FunctionID=EDIT_ZOOM;
    if (gen!=NULL) gen->Process(KM_UNSETPLUGIN,0,0);
}
/*

				case IDC_AXIS:
					Idle->SetFunc(EDIT_PUTAXIS);
					break;
				case IDC_ROTATEVIEW:
					Idle->SetFunc(EDIT_ROTATEVIEW);
					break;
				case IDC_MOVESPAN:
					
					{
						Idle->SetFunc(EDIT_MOVEVIEW);

					}
					Idle->SetFunc(EDIT_MOVEVIEW);
					break;
				case IDC_ZOOM:
					Idle->SetFunc(EDIT_ZOOM);
					break;
				case IDC_REGIONFIT:
					Idle->SetFunc(EDIT_REGIONFIT);
					break;
				case IDC_SELECT:
					Idle->SetFunc(Idle->SelectedSel);
					break;
				case IDC_ROTATE:
					Idle->SetFunc(EDIT_ROTATEBUF);
					break;
				case IDC_MOVE:
					Idle->SetFunc(EDIT_MOVEBUF);
					break;
				case IDC_SCALE:
					Idle->SetFunc(EDIT_SCALEBUF);
					break;

*/

void CMainFrame::OnViewExtendsviews() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnViewExtendview() 
{
	// TODO: Add your command handler code here
	
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	return CMDIFrameWnd::OnCreateClient(lpcs, pContext);
}

///////////////////////////////////////////////////////////////////////////////
// update tool bar

void CMainFrame::OnViewBuildbar() 
{
    
	if(GetMenuState(GetMenu( )->m_hMenu,ID_VIEW_BUILDBAR, MF_BYCOMMAND) & MF_CHECKED)
	{
		ShowControlBar(&m_Plugs, FALSE, FALSE);
	}
	else
	{
		ShowControlBar(&m_Plugs, TRUE, FALSE);
	}
    
}

void CMainFrame::OnViewPluginbar() 
{
	if(GetMenuState(GetMenu( )->m_hMenu, ID_VIEW_PLUGINBAR, MF_BYCOMMAND) & MF_CHECKED)
	{
		ShowControlBar(&m_wndDialogBar, FALSE, FALSE);
	}
	else
	{
		ShowControlBar(&m_wndDialogBar, TRUE, FALSE);
	}	
}

void CMainFrame::OnViewModify() 
{
	if(GetMenuState(GetMenu( )->m_hMenu,ID_VIEW_MODIFY, MF_BYCOMMAND) & MF_CHECKED)
	{
		ShowControlBar(&m_wndToolBarModify, FALSE, FALSE);
	}
	else
	{
		ShowControlBar(&m_wndToolBarModify, TRUE, FALSE);
	}	
}

void CMainFrame::OnViewModifyview() 
{
	if(GetMenuState(GetMenu( )->m_hMenu,ID_VIEW_MODIFYVIEW, MF_BYCOMMAND) & MF_CHECKED)
	{
		ShowControlBar(&m_wndToolModifView, FALSE, FALSE);
	}
	else
	{
		ShowControlBar(&m_wndToolModifView, TRUE, FALSE);
	}	
}

void CMainFrame::OnUpdateViewBuildbar(CCmdUI* pCmdUI) 
{
	if(m_Plugs.IsVisible())
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CMainFrame::OnUpdateViewModify(CCmdUI* pCmdUI) 
{
	if(m_wndToolBarModify.IsVisible())
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CMainFrame::OnUpdateViewModifyview(CCmdUI* pCmdUI) 
{
	if(m_wndToolModifView.IsVisible())
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);	
}

void CMainFrame::OnUpdateViewPluginbar(CCmdUI* pCmdUI) 
{
	if(m_wndDialogBar.IsVisible())
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);	
}

void CMainFrame::OnViewSelection() 
{
	if(GetMenuState(GetMenu( )->m_hMenu,ID_VIEW_SELECTION, MF_BYCOMMAND) & MF_CHECKED)
	{
		ShowControlBar(&m_wndToolBarSelect, FALSE, FALSE);
	}
	else
	{
		ShowControlBar(&m_wndToolBarSelect, TRUE, FALSE);
	}
}

void CMainFrame::OnUpdateViewSelection(CCmdUI* pCmdUI) 
{
	if(m_wndToolBarSelect.IsVisible())
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CMainFrame::OnViewViewconfiguration() 
{
	if(GetMenuState(GetMenu( )->m_hMenu,ID_VIEW_VIEWCONFIGURATION, MF_BYCOMMAND) & MF_CHECKED)
	{
		ShowControlBar(&m_wndToolBarViewConf, FALSE, FALSE);
	}
	else
	{
		ShowControlBar(&m_wndToolBarViewConf, TRUE, FALSE);
	}
}

void CMainFrame::OnUpdateViewViewconfiguration(CCmdUI* pCmdUI) 
{
	if(m_wndToolBarViewConf.IsVisible())
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CMainFrame::OnViewEditmode() 
{
	if(GetMenuState(GetMenu( )->m_hMenu,ID_VIEW_EDITMODE, MF_BYCOMMAND) & MF_CHECKED)
	{
		ShowControlBar(&m_wndMode, FALSE, FALSE);
	}
	else
	{
		ShowControlBar(&m_wndMode, TRUE, FALSE);
	}
}

void CMainFrame::OnUpdateViewEditmode(CCmdUI* pCmdUI) 
{
	if(m_wndMode.IsVisible())
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

///////////////////////////////////////////////////////////////////////////////
// notify
/*
long CMainFrame::OnOutbarNotify(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
		case NM_OB_ITEMCLICK:
		// cast the lParam to an integer to get the clicked item
			{
				int index = (int) lParam;

				CString cs, cs1;
				cs1 = m_wndOutBar->wndBar->GetItemText(index);
				//cs.Format("Clicked on %d - %d - <%s>", m_wndOutBar->wndBar.GetItemData(index),(int)lParam, cs1);
				//AfxMessageBox(cs);
				KLibs->ObjectsLib[m_wndOutBar->wndBar->GetItemData(index)]->Hwnd=m_wndDialogBar.m_cDialog->m_hWnd;
				
				FunctionID=EDIT_PLUGINCREATION;

				if (gen!=NULL) gen->Close();
				
				gen=KLibs->ObjectsLib[m_wndOutBar->wndBar->GetItemData(index)];
				View->gen=KLibs->ObjectsLib[m_wndOutBar->wndBar->GetItemData(index)];
				KLibs->ObjectsLib[m_wndOutBar->wndBar->GetItemData(index)]->MainWin=m_hWnd;
				

				//CTestGLDoc *tmpdoc;
				//tmpdoc=(CTestGLDoc *)GetActiveDocument();


				CMDIChildWnd *pChild = (CMDIChildWnd *) GetActiveFrame();
                
				m_wndDialogBar.m_cDialog->SetPlug(KLibs->ObjectsLib[m_wndOutBar->wndBar->GetItemData(index)]->Param(),(CWnd *)m_wndDialogBar.m_cDialog);

                if (pChild->GetActiveView()!=NULL)
                {
				    CDeskDoc *tmpdoc = (CDeskDoc *) pChild->GetActiveView()->GetDocument();
					//if (!tmpdoc->IsKindOf( RUNTIME_CLASS( CCrystalEditView ) ) ) 
			        {
						KLibs->ObjectsLib[m_wndOutBar->wndBar->GetItemData(index)]->SetContext(tmpdoc->dk,NULL,View);
						CurrentPlug=KLibs->ObjectsLib[m_wndOutBar->wndBar->GetItemData(index)];
					}
                }
			}
		return 0;

		default:
			return 0;

	}
    
	return 0;
}
*/
void CMainFrame::OnViewRendermodeMapped() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnViewRendermodeWire() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnViewRendermode() 
{
	if(GetMenuState(GetMenu( )->m_hMenu,ID_VIEW_RENDERMODE, MF_BYCOMMAND) & MF_CHECKED)
	{
		ShowControlBar(&m_wndToolRender, FALSE, FALSE);
	}
	else
	{
		ShowControlBar(&m_wndToolRender, TRUE, FALSE);
	}	
}

void CMainFrame::OnUpdateViewRendermode(CCmdUI* pCmdUI) 
{
	if(m_wndToolRender.IsVisible())
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

///////////////////////////////////////////////////////////////////////////////
// Modes d'édition

void CMainFrame::OnBuildCentered() 
{
	bCentered=!bCentered;
}

void CMainFrame::OnBuildCrossing() 
{
	bCrossing=!bCrossing;
}

void CMainFrame::OnBuildSnap() 
{
	bSnap=!bSnap;
}

void CMainFrame::OnUpdateBuildCentered(CCmdUI* pCmdUI) 
{
	if(bCentered)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CMainFrame::OnUpdateBuildCrossing(CCmdUI* pCmdUI) 
{
	if(bCrossing)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);	
}

void CMainFrame::OnUpdateBuildSnap(CCmdUI* pCmdUI) 
{
	if(bSnap)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CMainFrame::OnEditModeVertex() 
{
	MainEdit *pcList;

	iEditMode=1;
    View->Primitive=1;

	pcList=FirstMainEdit;
	while(pcList!=NULL)
	{
		Desk *dk=pcList->dk;
		dk->cSel->UnSelectCamera(false);
		dk->cSel->UnSelectObject(false);
		dk->cSel->UnSelectShape(false);
		dk->cSel->UnSelectLights(false);
//		dk->cSel->UnSelectEmitter(false);
		dk->cSel->UnSelectSkeletton(false);
		dk->DeleteBufVert();
		pcList->DrawViews();
		pcList=pcList->Next;
	}

}

void CMainFrame::OnEditModeObject() 
{
	MainEdit *pcList;

	iEditMode=3;
    View->Primitive=3;
	pcList=FirstMainEdit;
	while(pcList!=NULL)
	{
		Desk *dk=pcList->dk;
		dk->cSel->UnSelectCamera(false);
		dk->cSel->UnSelectObject(false);
		dk->cSel->UnSelectShape(false);
		dk->cSel->UnSelectLights(false);
		//dk->cSel->UnSelectEmitter(false);
		dk->cSel->UnSelectSkeletton(false);
		dk->DeleteBufVert();
		pcList->DrawViews();
		pcList=pcList->Next;
	}
	
}

void CMainFrame::OnEditModeFace() 
{
	MainEdit *pcList;

	iEditMode=2;
    View->Primitive=2;
	pcList=FirstMainEdit;
	while(pcList!=NULL)
	{
		Desk *dk=pcList->dk;
		dk->cSel->UnSelectCamera(false);
		dk->cSel->UnSelectObject(false);
		dk->cSel->UnSelectShape(false);
		dk->cSel->UnSelectLights(false);
		//dk->cSel->UnSelectEmitter(false);
		dk->cSel->UnSelectSkeletton(false);
		dk->DeleteBufVert();
		pcList->DrawViews();
		pcList=pcList->Next;
	}
	
}
void CMainFrame::OnUpdateEditModeFace(CCmdUI* pCmdUI) 
{
	if(iEditMode==2)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);	
}

void CMainFrame::OnUpdateEditModeObject(CCmdUI* pCmdUI) 
{
	if(iEditMode==3)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CMainFrame::OnUpdateEditModeVertex(CCmdUI* pCmdUI) 
{
	if(iEditMode==1)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);	
}



///////////////////////////////////////////////////////////////////////////////
// messages perso

LRESULT CMainFrame::OnWmSetStatus(WPARAM wParam, LPARAM lParam) 
{
	m_wndStatusBar.SetPaneText( wParam, (const char*)lParam);		
	return FALSE; 
}

LRESULT CMainFrame::OnWmDrawScene(WPARAM wParam, LPARAM lParam) 
{
	CMDIChildWnd *pChild = (CMDIChildWnd *) GetActiveFrame();

	MainEdit *tmpdoc = (MainEdit *) pChild->GetActiveView();
	tmpdoc->DrawViews();
	return FALSE; 
}

LRESULT CMainFrame::OnWmSetPlugin(WPARAM wParam, LPARAM lParam) 
{
    FunctionID=EDIT_PLUGINCREATION;
    return FALSE;
}

LRESULT CMainFrame::OnWmSetMouseCursor(WPARAM wParam, LPARAM lParam) 
{
    //FunctionID=EDIT_PLUGINCREATION;
    CurrentCursor=wParam;
    return FALSE;
}


void CMainFrame::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CMDIFrameWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


///////////////////////////////////////////////////////////////////////////////
#if 0
void CMainFrame::OnViewCompilation() 
{
	if(GetMenuState(GetMenu( )->m_hMenu,ID_VIEW_COMPILATION, MF_BYCOMMAND) & MF_CHECKED)
	{
		ShowControlBar(&m_wndCompile, FALSE, FALSE);
	}
	else
	{
		ShowControlBar(&m_wndCompile, TRUE, FALSE);
	}	
}

void CMainFrame::OnUpdateViewCompilation(CCmdUI* pCmdUI) 
{
	if(m_wndCompile.IsVisible())
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);	
}

void CMainFrame::OnViewProject() 
{
	if(GetMenuState(GetMenu( )->m_hMenu,ID_VIEW_PROJECT, MF_BYCOMMAND) & MF_CHECKED)
	{
		ShowControlBar(&m_wndProjects, FALSE, FALSE);
	}
	else
	{
		ShowControlBar(&m_wndProjects, TRUE, FALSE);
	}	
}

void CMainFrame::OnUpdateViewProject(CCmdUI* pCmdUI) 
{
	if(m_wndProjects.IsVisible())
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CMainFrame::OnViewCompilationtools() 
{
	if(GetMenuState(GetMenu( )->m_hMenu,ID_VIEW_COMPILATIONTOOLS, MF_BYCOMMAND) & MF_CHECKED)
	{
		ShowControlBar(&m_wndToolCompilation, FALSE, FALSE);
	}
	else
	{
		ShowControlBar(&m_wndToolCompilation, TRUE, FALSE);
	}	
}

void CMainFrame::OnUpdateViewCompilationtools(CCmdUI* pCmdUI) 
{
	if(m_wndToolCompilation.IsVisible())
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
	
}
#endif
CEdit *eCompOut;

void myDisplay(char *msg) 
{
    CString temp;
    int i;

    eCompOut->GetWindowText(temp);
    for (i=0;i<strlen(msg);i++)
    {
        if (msg[i]!='\n')
            temp+=msg[i];
        else
            temp+="\r\n";
    }
    eCompOut->SetWindowText(temp);

}


void CMainFrame::OnToolsSkyboxeditor() 
{
    
	// TODO: Add your command handler code here
	CSkyBoxEd csb;
	
	csb.DoModal();
	
}

void CMainFrame::OnViewViewtypes() 
{
	if(GetMenuState(GetMenu( )->m_hMenu,ID_VIEW_VIEWTYPES, MF_BYCOMMAND) & MF_CHECKED)
	{
		ShowControlBar(&m_wndToolTypeView, FALSE, FALSE);
	}
	else
	{
		ShowControlBar(&m_wndToolTypeView, TRUE, FALSE);
	}	
}


void CMainFrame::OnUpdateViewViewtypes(CCmdUI* pCmdUI) 
{
	if(m_wndToolTypeView.IsVisible())
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);		
	
}

void CMainFrame::OnToolsPluginsfolders() 
{
//    cepf.DoModal();
    //m_wndOutBar->RemoveAll();
    /*
    delete m_wndOutBar;
    m_wndOutBar=new (COutBar);
    */

    RefreshOutBar();
}

//CBitmap dadib;

void CMainFrame::RefreshOutBar(void)
{

	for (int i=0;i<KLibs->nb2ObjectsLib;i++)
	{
		//imaLarge.Add(tmpbit.FromHandle(KLibs->ObjectsLib[i]->GottenBits),RGB(255,0,255));

        PlugsIds[i]=30000+i;
    }
    m_Plugs.SetButtons( PlugsIds, KLibs->nb2ObjectsLib);
    
    //dadib.LoadBitmap(IDB_BITMAP1);
    
	for (i=0;i<KLibs->nb2ObjectsLib;i++)
	{
        m_Plugs.GetToolBarCtrl().AddBitmap(1,KLibs->ObjectsLib[i]->m_Dib);
        /*
        ::SendMessage(m_Plugs.GetToolBarCtrl().m_hWnd, TB_ADDBITMAP, (WPARAM)1,
		(LPARAM)&KLibs->ObjectsLib[i]->m_Dib->m_hObject);
        */
    }
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	for (int i=0;i<KLibs->nb2ObjectsLib;i++)
        if (PlugsIds[i]==nID) return TRUE;

	return CMDIFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

BOOL CMainFrame::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if ((wParam>=30000)&&(wParam<(30000+KLibs->nb2ObjectsLib)))
    {
        
		int index = (int) wParam-30000;
		KLibs->ObjectsLib[index]->Hwnd=m_wndDialogBar.m_cDialog->m_hWnd;
		
		FunctionID=EDIT_PLUGINCREATION;

		if (gen!=NULL) gen->Close();
		
		gen=KLibs->ObjectsLib[index];
		View->gen=KLibs->ObjectsLib[index];
		KLibs->ObjectsLib[index]->MainWin=m_hWnd;
		
		CMDIChildWnd *pChild = (CMDIChildWnd *) GetActiveFrame();
        
		m_wndDialogBar.m_cDialog->SetPlug(KLibs->ObjectsLib[index]->Param(),(CWnd *)m_wndDialogBar.m_cDialog);

        if (pChild->GetActiveView()!=NULL)
        {
			CDeskDoc *tmpdoc = (CDeskDoc *) pChild->GetActiveView()->GetDocument();
			KLibs->ObjectsLib[index]->SetContext(tmpdoc->dk,NULL,View);
			CurrentPlug=KLibs->ObjectsLib[index];
        }
    }

	return CMDIFrameWnd::OnCommand(wParam, lParam);
}



BOOL CMainFrame::OnToolTipText(UINT, NMHDR* pNMHDR, LRESULT* pResult)
{
    ASSERT(pNMHDR->code == TTN_NEEDTEXTA || pNMHDR->code == TTN_NEEDTEXTW);

    // if there is a top level routing frame then let it handle the message
    //if (GetRoutingFrame() != NULL) return FALSE;

    // to be thorough we will need to handle UNICODE versions of the message also !!
    TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
    TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;
    CString strTipText;
    UINT nID = pNMHDR->idFrom;

    if (pNMHDR->code == TTN_NEEDTEXTA && (pTTTA->uFlags & TTF_IDISHWND) ||
        pNMHDR->code == TTN_NEEDTEXTW && (pTTTW->uFlags & TTF_IDISHWND))
    {
        // idFrom is actually the HWND of the tool 
        nID = ::GetDlgCtrlID((HWND)nID);
    }

    if (nID != 0) // will be zero on a separator
    {
        if ((nID>=30000)&&(nID<=30099))
//        AfxLoadString(nID, szFullText);
            strTipText=KLibs->ObjectsLib[nID-30000]->Name;//szFullText;
        else
        {
            //LoadString(nID, szFullText);
            strTipText.LoadString(nID);//=szFullText;
            strTipText.Replace( '\n',0);

            
        }

#ifndef _UNICODE
        if (pNMHDR->code == TTN_NEEDTEXTA)
        {
            lstrcpyn(pTTTA->szText, strTipText, sizeof(pTTTA->szText));
        }
        else
        {
            _mbstowcsz(pTTTW->szText, strTipText, sizeof(pTTTW->szText));
        }
#else
        if (pNMHDR->code == TTN_NEEDTEXTA)
        {
            _wcstombsz(pTTTA->szText, strTipText,sizeof(pTTTA->szText));
        }
        else
        {
            lstrcpyn(pTTTW->szText, strTipText, sizeof(pTTTW->szText));
        }
#endif

        *pResult = 0;

        // bring the tooltip window above other popup windows
        ::SetWindowPos(pNMHDR->hwndFrom, HWND_TOP, 0, 0, 0, 0,
            SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOMOVE|SWP_NOOWNERZORDER);
        
        return TRUE;
    }

    return FALSE;
}


void CMainFrame::OnEditRedo() 
{
	CMDIChildWnd *pChild = (CMDIChildWnd *) GetActiveFrame();
        
    if (pChild->GetActiveView()!=NULL)
    {
		CDeskDoc *tmpdoc = (CDeskDoc *) pChild->GetActiveView()->GetDocument();
		tmpdoc->dk->Redo();
		DrawViews();
    }	
}

void CMainFrame::OnEditUndo() 
{
	CMDIChildWnd *pChild = (CMDIChildWnd *) GetActiveFrame();
        
    if (pChild->GetActiveView()!=NULL)
    {
		CDeskDoc *tmpdoc = (CDeskDoc *) pChild->GetActiveView()->GetDocument();
		tmpdoc->dk->Undo();
		DrawViews();
    }	
}

void CMainFrame::OnUpdateEditRedo(CCmdUI* pCmdUI) 
{
	CMDIChildWnd *pChild = (CMDIChildWnd *) GetActiveFrame();
        
    if (pChild->GetActiveView()!=NULL)
    {
		CDeskDoc *tmpdoc = (CDeskDoc *) pChild->GetActiveView()->GetDocument();
		if (tmpdoc->dk->FirstRedo==NULL)
			pCmdUI->Enable(false);
		else
			pCmdUI->Enable();
		
    }	
}

void CMainFrame::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
	CMDIChildWnd *pChild = (CMDIChildWnd *) GetActiveFrame();
        
    if (pChild->GetActiveView()!=NULL)
    {
		CDeskDoc *tmpdoc = (CDeskDoc *) pChild->GetActiveView()->GetDocument();
		if (tmpdoc->dk->FirstUndo==NULL)
			pCmdUI->Enable(false);
		else
			pCmdUI->Enable();
    }	
}

void CMainFrame::OnToolsEntitymanager()
{
	CEntiDlg ediag;
	ediag.DoModal();

}

void CMainFrame::OnViewCompilationtools()
{
	if(GetMenuState(GetMenu( )->m_hMenu,ID_VIEW_COMPILATIONTOOLS, MF_BYCOMMAND) & MF_CHECKED)
	{
		ShowControlBar(&m_wndToolCompilation, FALSE, FALSE);
	}
	else
	{
		ShowControlBar(&m_wndToolCompilation, TRUE, FALSE);
	}
}

void CMainFrame::OnUpdateViewCompilationtools(CCmdUI *pCmdUI)
{
	if(m_wndToolCompilation.IsVisible())
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);	
}

void CMainFrame::OnViewAnimationbar()
{
	if(GetMenuState(GetMenu( )->m_hMenu,ID_VIEW_ANIMATIONBAR, MF_BYCOMMAND) & MF_CHECKED)
	{
		ShowControlBar(&m_wndAnim, FALSE, FALSE);
	}
	else
	{
		ShowControlBar(&m_wndAnim, TRUE, FALSE);
	}	
}

void CMainFrame::OnUpdateViewAnimationbar(CCmdUI *pCmdUI)
{
	if(m_wndAnim.IsVisible())
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);	
}

void CMainFrame::OnViewToolbar()
{
	if(GetMenuState(GetMenu( )->m_hMenu,ID_VIEW_TOOLBAR, MF_BYCOMMAND) & MF_CHECKED)
	{
		ShowControlBar(&m_wndToolBar, FALSE, FALSE);
	}
	else
	{
		ShowControlBar(&m_wndToolBar, TRUE, FALSE);
	}	
}

void CMainFrame::OnUpdateViewToolbar(CCmdUI *pCmdUI)
{
	if(m_wndToolBar.IsVisible())
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CMainFrame::OnViewMapsbrowser() 
{
	if(GetMenuState(GetMenu( )->m_hMenu,ID_VIEW_MAPSBROWSER, MF_BYCOMMAND) & MF_CHECKED)
	{
		ShowControlBar(&m_wndMatBrowser, FALSE, FALSE);
	}
	else
	{
		ShowControlBar(&m_wndMatBrowser, TRUE, FALSE);
	}	
}

void CMainFrame::OnUpdateViewMapsbrowser(CCmdUI* pCmdUI) 
{
	if(m_wndMatBrowser.IsVisible())
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CMainFrame::OnViewDeskfilebrowser() 
{
	if(GetMenuState(GetMenu( )->m_hMenu,ID_VIEW_DESKFILEBROWSER, MF_BYCOMMAND) & MF_CHECKED)
	{
		ShowControlBar(&m_wndDesksBrowser, FALSE, FALSE);
	}
	else
	{
		ShowControlBar(&m_wndDesksBrowser, TRUE, FALSE);
	}	
}

void CMainFrame::OnUpdateViewDeskfilebrowser(CCmdUI* pCmdUI) 
{
	if(m_wndDesksBrowser.IsVisible())
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);	
}
