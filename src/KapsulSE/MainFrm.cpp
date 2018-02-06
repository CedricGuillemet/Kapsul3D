// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"

#include "SkyBoxEd.h"
#include "mainfrm.h"
//#include "KFileDialog.h"
#include <direct.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "NewProject.h"
#include "KSelectRenderer.h"
#include "KRenderIt.h"
#include "KMaterialEditor.h"

extern CKOption *KOption;
// timer event
#define TIMER_ID 12

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_UNSELECTALL WM_USER+9
extern CKapsulApp theApp;

//char		*ReadFilter,*WriteFilter;
CString ReadFilter,WriteFilter;

CTVTestDlg	*m_DesksBrowser;

class assocFold
{
public:
    CString PluginFolder;
    int FolderInd;

    assocFold(CString pf,int fi) { PluginFolder=pf; FolderInd=fi; };

};

// variables globales

bool bCrossing=false;
bool bSnap=true;
bool bAngleSnap=false;
bool bCentroid=false;
//bool bAngle=false;


int daButton;
int iEditMode;

CKPluginManager *GKPlugins;
int FunctionID;
//CKDrawScene *GDrawScene;
CKScene *GCurrentScene;
CKScenePlugin *GCurPlug=NULL;
int CurrentCursor=0;
CKScene ClipBoard;
//GenericLib *CurrentPlug=NULL;
int GCurSelect=EDIT_SELECTQUAD;
CKViewEdit *FirstCKViewEdit=NULL,*NextCKViewEdit=NULL;

//CKEntityManager *m_EntMngr;
//CEditPlugFolder cepf;
CMainFrame *MainFrm;
extern CKLocalization loc;
void AddCKViewEdit(CKViewEdit *daMain)
{
	if (FirstCKViewEdit==NULL) 
	{
		FirstCKViewEdit=daMain;
		NextCKViewEdit=daMain;
	}
	else
	{
		CKViewEdit *tmp;
		tmp=NextCKViewEdit;
		NextCKViewEdit->Next=daMain;
		NextCKViewEdit=daMain;
		NextCKViewEdit->Prev=tmp;
	}
}

void DelCKViewEdit(CKViewEdit *daMain)
{
    if (daMain->Prev!=NULL)
        daMain->Prev->Next=daMain->Next;

    if (daMain->Next!=NULL)
        daMain->Next->Prev=daMain->Prev;

    if (daMain==FirstCKViewEdit) FirstCKViewEdit=daMain->Next;

    if (daMain==NextCKViewEdit) NextCKViewEdit=daMain->Prev;

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
	ON_COMMAND(ID_TOOLS_PLUGINSFOLDERS, OnToolsPluginsfolders)
	ON_COMMAND(ID_EDIT_REDO, OnEditRedo)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, OnUpdateEditRedo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_COMMAND(ID_VIEW_MAPSBROWSER, OnViewMapsbrowser)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MAPSBROWSER, OnUpdateViewMapsbrowser)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_ABOUT_KAPSUL, OnAboutKapsul)
	ON_WM_MEASUREITEM()
	ON_WM_MENUCHAR()
	ON_WM_INITMENUPOPUP()
	ON_COMMAND(ID_CREATEPRIM, OnCreateprim)
	ON_COMMAND(ID_VIEW_ANIMATIONBAR, OnViewAnimationbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ANIMATIONBAR, OnUpdateViewAnimationbar)
	ON_COMMAND(ID_VIEW_DOCKBAR, OnViewDockbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DOCKBAR, OnUpdateViewDockbar)
	ON_COMMAND(ID_VIEW_EDITBAR, OnViewEditbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_EDITBAR, OnUpdateViewEditbar)
	ON_COMMAND(ID_EDIT_DOSELECT, OnEditDoselect)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DOSELECT, OnUpdateEditDoselect)
	ON_UPDATE_COMMAND_UI(ID_CREATEPRIM, OnUpdateCreateprim)
	ON_COMMAND(ID_EDIT_CHOOSEMODE, OnEditChoosemode)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SELECT_CIRCLE, OnUpdateEditSelectCircle)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SELECT_FENCE, OnUpdateEditSelectFence)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SELECT_QUAD, OnUpdateEditSelectQuad)
	ON_WM_TIMER()
	ON_COMMAND(ID_BUILD_CENTROID, OnBuildCentroid)
	ON_UPDATE_COMMAND_UI(ID_BUILD_CENTROID, OnUpdateBuildCentroid)
	ON_COMMAND(ID_FILE_NEWPROJECT, OnFileNewproject)
	ON_COMMAND(ID_FILE_OPENPROJECT, OnFileOpenproject)
	ON_COMMAND(ID_FILE_CLOSEPROJECT, OnFileCloseproject)
	ON_COMMAND(ID_FILE_CLOSEALL, OnFileCloseall)
	ON_COMMAND(ID_VIEW_STATUS_BAR, OnViewStatusBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_STATUS_BAR, OnUpdateViewStatusBar)
	ON_COMMAND(ID_VIEW_PRIMITIVEBAR, OnViewPrimitivebar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PRIMITIVEBAR, OnUpdateViewPrimitivebar)
	ON_COMMAND(ID_TOOLS_MATERIALEDITOR, OnToolsMaterialeditor)
	ON_COMMAND(ID_BUILD_ANGLESNAP, OnBuildAnglesnap)
	ON_UPDATE_COMMAND_UI(ID_BUILD_ANGLESNAP, OnUpdateBuildAnglesnap)
	ON_COMMAND(ID_TOOLS_NETUPDATE, OnToolsNetupdate)
	ON_COMMAND(ID_EDIT_MOVEROTATESCALE,OnMoveRotateScale)
	ON_COMMAND(ID_EDIT_MOVEROTATETAPERSQUIZ,OnMoveRotateTaperSquiz)
	ON_COMMAND(ID_EDIT_BEND,OnMoveRotateBend)
	ON_UPDATE_COMMAND_UI(ID_EDIT_MOVEROTATESCALE, OnUpdateMoveRotateScale)
	ON_UPDATE_COMMAND_UI(ID_EDIT_MOVEROTATETAPERSQUIZ, OnUpdateMoveRotateTaperSquiz)
	ON_UPDATE_COMMAND_UI(ID_EDIT_BEND, OnUpdateMoveRotateBend)
	ON_MESSAGE(WM_SETSTATUS,OnWmSetStatus)
	ON_MESSAGE(WM_DRAWSCENE,OnWmDrawScene)
    ON_MESSAGE(WM_SETPLUGIN,OnWmSetPlugin)
    ON_MESSAGE(WM_SETMOUSECURSOR,OnWmSetMouseCursor)
	ON_COMMAND(ID_TOOLS_ENTITYMANAGER, OnToolsEntitymanager)
	ON_COMMAND(ID_TOOLS_RENDERER, OnToolsRenderer)
	//}}AFX_MSG_MAP
    ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)
    ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipText)

	ON_COMMAND(ID_VIEW_COMPILATIONTOOLS, OnViewCompilationtools)
	ON_UPDATE_COMMAND_UI(ID_VIEW_COMPILATIONTOOLS, OnUpdateViewCompilationtools)
	ON_COMMAND(ID_VIEW_ANIMATIONBAR, OnViewAnimationbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ANIMATIONBAR, OnUpdateViewAnimationbar)
	ON_COMMAND(ID_VIEW_TOOLBAR, OnViewToolbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBAR, OnUpdateViewToolbar)
	ON_COMMAND(ID_TOOLS_RENDERINGOPTIONS, OnToolsRenderingOptions)
	
	ON_WM_DROPFILES()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	/*
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CONTROLS,
	ID_INDICATOR_MISC,
*/
	ID_EDIT_INDICATOR_POSITION2,               // status line indicator 
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
	MainFrm=this;
}

CMainFrame::~CMainFrame()
{
    /*
	delete [] ReadFilter;
	delete [] WriteFilter;
*/

}

static const int	kImageWidth (24);
static const int	kImageHeight (24);
static const int	kNumImages (23);

static const UINT	kToolBarBitDepth (ILC_COLOR24);

 // this color will be treated as transparent in the loaded bitmaps --
 // in other words, any pixel of this color will be set at runtime to
 // the user's button color. The Visual Studio toolbar editor defaults
 // to 192, 192, 192 (light gray).
static const RGBTRIPLE	kBackgroundColor = {192,192,192};
static const RGBTRIPLE	DefBlack = {1,1,1};

// find every pixel of the default background color in the specified
// bitmap and set each one to the user's button color.
void	ReplaceBackgroundColor (CBitmap& ioBM)
{
 // figure out how many pixels there are in the bitmap
 BITMAP		bmInfo;

 VERIFY (ioBM.GetBitmap (&bmInfo));

 // add support for additional bit depths if you choose
 //VERIFY (bmInfo.bmBitsPixel == 24);
// VERIFY (bmInfo.bmWidthBytes == (bmInfo.bmWidth * 3));

 const UINT		numPixels (bmInfo.bmHeight * bmInfo.bmWidth);

 // get a pointer to the pixels
 DIBSECTION  ds;

 //VERIFY (ioBM.GetObject (sizeof (DIBSECTION), &ds) == sizeof (DIBSECTION));
 ioBM.GetObject (sizeof (DIBSECTION), &ds);

 RGBTRIPLE*		pixels = reinterpret_cast<RGBTRIPLE*>(ds.dsBm.bmBits);
 VERIFY (pixels != NULL);

 // get the user's preferred button color from the system
 const COLORREF		buttonColor (::GetSysColor (COLOR_BTNFACE));
 const RGBTRIPLE		userBackgroundColor = {
 GetBValue (buttonColor), GetGValue (buttonColor), GetRValue (buttonColor)};

 // search through the pixels, substituting the user's button
 // color for any pixel that has the magic background color
 for (UINT i = 0; i < numPixels; ++i)
 {
if (pixels [i].rgbtBlue == 0 
  && pixels [i].rgbtGreen == 0 
  && pixels [i].rgbtRed == 0)
  {
   pixels [i] = DefBlack;
  }

  if (pixels [i].rgbtBlue == kBackgroundColor.rgbtBlue 
  && pixels [i].rgbtGreen == kBackgroundColor.rgbtGreen 
  && pixels [i].rgbtRed == kBackgroundColor.rgbtRed)
  {
   pixels [i] = userBackgroundColor;
  }


 }
}


// create an image list for the specified BMP resource
static void	MakeToolbarImageList (UINT inBitmapID,
                                  CImageList&	outImageList)
{
 CBitmap		bm;

 // if we use CBitmap::LoadBitmap() to load the bitmap, the colors
 // will be reduced to the bit depth of the main screen and we won't
 // be able to access the pixels directly. To avoid those problems,
 // we'll load the bitmap as a DIBSection instead and attach the
 // DIBSection to the CBitmap.
 VERIFY (bm.Attach (::LoadImage (::AfxFindResourceHandle(
 MAKEINTRESOURCE (inBitmapID), RT_BITMAP),
 MAKEINTRESOURCE (inBitmapID), IMAGE_BITMAP, 0, 0,
 (LR_DEFAULTSIZE | LR_CREATEDIBSECTION))));

 // replace the specified color in the bitmap with the user's
 // button color
 ::ReplaceBackgroundColor (bm);

 // create a 24 bit image list with the same dimensions and number
 // of buttons as the toolbar
 VERIFY (outImageList.Create (
 kImageWidth, kImageHeight, kToolBarBitDepth, kNumImages, 0));

 // attach the bitmap to the image list
 VERIFY (outImageList.Add (&bm, RGB (0, 0, 0)) != -1);
}


// load the high color toolbar images and attach them to m_wndToolBar
void CMainFrame::AttachToolbarImages (CFOToolBar *m_TBDest,UINT inNormalImageID,
                                      UINT inDisabledImageID,
                                      UINT inHotImageID,
									  CImageList &m_Hot,CImageList &m_Disabled,CImageList &m_Normal)
{
  // make high-color image lists for each of the bitmaps
 ::MakeToolbarImageList (inNormalImageID, m_Normal);
 ::MakeToolbarImageList (inDisabledImageID, m_Disabled);
 ::MakeToolbarImageList (inHotImageID, m_Hot);

  // get the toolbar control associated with the CToolbar object
 CToolBarCtrl&	barCtrl = m_TBDest->GetToolBarCtrl();

  // attach the image lists to the toolbar control
 barCtrl.SetImageList (&m_Hot);
 //barCtrl.SetDisabledImageList (&m_Disabled);
 //barCtrl.SetHotImageList (&m_Hot);
}

// load the high color toolbar images and attach them to m_wndToolBar
void CMainFrame::AttachToolbarImages (CMyToolBar *m_TBDest,UINT inNormalImageID,
                                      UINT inDisabledImageID,
                                      UINT inHotImageID,
									  CImageList &m_Hot,CImageList &m_Disabled,CImageList &m_Normal)
{
  // make high-color image lists for each of the bitmaps
 ::MakeToolbarImageList (inNormalImageID, m_Normal);
 ::MakeToolbarImageList (inDisabledImageID, m_Disabled);
 ::MakeToolbarImageList (inHotImageID, m_Hot);

  // get the toolbar control associated with the CToolbar object
 CToolBarCtrl&	barCtrl = m_TBDest->GetToolBarCtrl();

  // attach the image lists to the toolbar control
 barCtrl.SetImageList (&m_Hot);
 //barCtrl.SetDisabledImageList (&m_Disabled);
 //barCtrl.SetHotImageList (&m_Hot);
}

void InitRollUpClass(void);

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    int i;

	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Splash screen

	if (KOption->ShowSplash())
		CSplashWnd::ShowSplashScreen(this);





	

	// compute files dll

	ReadFilter="";
	WriteFilter="";

	//strcat(ReadFilter,"Kapsul script (*.ksc)|*.ksc|");

	ReadFilter+="All supported 3D formats(";

	for (i=0;i<GKPlugins->FilePlugins.size();i++)
	{
		if (GKPlugins->FilePlugins[i]->SupportReading())
		{
			ReadFilter+=GKPlugins->FilePlugins[i]->GetFilter();
			if (i<(GKPlugins->FilePlugins.size()-1)) ReadFilter+=";";
		}
	}
	ReadFilter+=")|";

	for (i=0;i<GKPlugins->FilePlugins.size();i++)
	{
		if (GKPlugins->FilePlugins[i]->SupportReading())
		{
			ReadFilter+=GKPlugins->FilePlugins[i]->GetFilter();
			//tmpadds+=2;
			//strcat(ReadFilter,tmpadds);
			if (i<(GKPlugins->FilePlugins.size()-1)) ReadFilter+=";";
		}
	}
	ReadFilter+="|";
/*
	for (i=0;i<GKPlugins->DocViewPlugs.size();i++)
	{
			strcat(ReadFilter,(char*)GKPlugins->DocViewPlugs[i]->Process(KM_GETEXTENSIONS,0,0));
			strcat(ReadFilter,"|");

	}
*/
	for (i=0;i<GKPlugins->FilePlugins.size();i++)
	{
		/*
		if (GKPlugins->FilesPlugs[i]->ReadSupport)
		{
			strcat(ReadFilter,GKPlugins->FilesPlugs[i]->RFileDesc);
			strcat(ReadFilter,"|");
			strcat(ReadFilter,GKPlugins->FilesPlugs[i]->RFilter);
			strcat(ReadFilter,"|");
		}
*/
		if (GKPlugins->FilePlugins[i]->SupportWriting())
		{
			WriteFilter+=GKPlugins->FilePlugins[i]->GetFileDescription();
			WriteFilter+="|";
			WriteFilter+=GKPlugins->FilePlugins[i]->GetFilter();
			WriteFilter+="|";
		}

	}

	for (i=0;i<1024;i++)
	{
		//if (ReadFilter[i]==0x7c) ReadFilter[i]='\0';
		//if (WriteFilter[i]==0x7c) WriteFilter[i]='\0';
	}

	

	// Kore init

    
    SetFuncPtr(&FunctionID,&bCrossing,&bAngleSnap,&bSnap,&bCentroid,KOption);
    SetButtonPtr((int *)&daButton);
	SetLib(GKPlugins);
	// View
	/*
	GDrawScene = new CKDrawScene();
	GDrawScene->LocalizeNames();
	*/

    // Load Option
    
	///////////////////////////////////////////////////////////////////////////
	// Bars

	// Status bar

	/*
	m_wndStatusBar.Create(this);
	m_wndStatusBar.SetIndicators(indicators,sizeof(indicators)/sizeof(UINT));
    m_wndStatusBar.SetPaneInfo( 0, m_wndStatusBar.GetItemID( 0 ), SBPS_STRETCH, 0 );
	m_wndStatusBar.SetPaneInfo(1, ID_INDICATOR_CONTROLS, SBPS_NORMAL, 180);
	m_wndStatusBar.SetPaneInfo(2, ID_INDICATOR_MISC, SBPS_NORMAL, 100);
	m_wndStatusBar.SetPaneInfo(3, ID_INDICATOR_MISC, SBPS_NORMAL, 100);
*/
	// Main toolbar
	
	m_wndToolBar.CreateEx(this,TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,CRect(0, 0, 0, 0),101001);
	m_wndToolBar.LoadToolBar(IDR_MAINFRAME);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	AttachToolbarImages (&m_wndToolBar,IDB_MAINTOOLBAR2,IDB_MAINTOOLBAR3,IDB_MAINTOOLBAR,m_ToolbarImagesDisabledMain,m_ToolbarImagesHotMain,m_ToolbarImagesMain);

	// Edit ToolBar

	m_wndToolBarDesk.CreateEx(this,TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,CRect(0, 0, 0, 0),101002);
	m_wndToolBarDesk.LoadToolBar(IDR_MAINDESK);
	m_wndToolBarDesk.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBarDesk);
	AttachToolbarImages (&m_wndToolBarDesk,IDB_DESKTOOLBAR2,IDB_DESKTOOLBAR3,IDB_DESKTOOLBAR,m_ToolbarImagesDisabledDesk,m_ToolbarImagesHotDesk,m_ToolbarImagesDesk);

	//m_wndToolBarDesk.addFlyout(18,IDR_MAINDESK);
	m_wndToolBarDesk.Init();
 
	// plugins list bar

	m_Plugs.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,CRect(0, 0, 0, 0),101210);
	m_Plugs.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_Plugs);

	// primitives

	m_Primitives.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,CRect(0, 0, 0, 0),101293);
	m_Primitives.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_Primitives);

	// Build bar

	m_wndDesksBrowser.Create(_T("Build"), this, 123);
    m_wndDesksBrowser.SetBarStyle(m_wndDesksBrowser.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	EnableDocking(CBRS_ALIGN_ANY);
    m_wndDesksBrowser.EnableDocking(CBRS_ALIGN_LEFT|CBRS_ALIGN_RIGHT);
    DockControlBar(&m_wndDesksBrowser, AFX_IDW_DOCKBAR_LEFT);
	
	// animate bar

	m_wndAnim.Create(_T("Animate"), this, 124);
    m_wndAnim.SetBarStyle(m_wndAnim.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	EnableDocking(CBRS_ALIGN_ANY);
    m_wndAnim.EnableDocking(CBRS_ALIGN_TOP|CBRS_ALIGN_BOTTOM);
    DockControlBar(&m_wndAnim, AFX_IDW_DOCKBAR_BOTTOM);
	m_DesksBrowser=&m_wndDesksBrowser.m_cDialog;


	m_wndStatus.Create(_T("Status Bar"), this, 154);
    m_wndStatus.SetBarStyle(m_wndStatus.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	EnableDocking(CBRS_ALIGN_ANY);
    m_wndStatus.EnableDocking(CBRS_ALIGN_TOP|CBRS_ALIGN_BOTTOM);
    DockControlBar(&m_wndStatus, AFX_IDW_DOCKBAR_BOTTOM);

	SetXYZPtr(&m_wndStatus.m_cDialog.m_SpinX,&m_wndStatus.m_cDialog.m_EditX,&m_wndStatus.m_cDialog.m_SpinY,&m_wndStatus.m_cDialog.m_EditY,
		&m_wndStatus.m_cDialog.m_SpinZ,&m_wndStatus.m_cDialog.m_EditZ);

	SetStatusHWND(m_hWnd,(CWnd*)this,m_wndStatus.m_cDialog.m_Infos.m_hWnd);
	// load bar profiles

	if (theApp.GetProfileInt("Editor State","BarSaved",0))
	{
		LoadBarState("BarStates");
	}

    CString sProfile(_T("DeskBarState"));
    if (VerifyBarState(sProfile))
    {
        m_wndDesksBrowser.LoadState(sProfile);
        LoadBarState(sProfile);
    }

    sProfile=_T("AnimateBarState");
    if (VerifyBarState(sProfile))
    {
        m_wndAnim.LoadState(sProfile);
        LoadBarState(sProfile);
    }

	SetDMPHWND(&m_wndAnim.m_cDialog.m_Dump.m_Output);
    RefreshOutBar();

/*
	for (i=0;i<GKPlugins->DocViewPlugs.size();i++)
	{
        GKPlugins->DocViewPlugs[i]->Process(KM_OPEN,(UINT)this,0);
	}
*/
    // status out
	SetHierarchieTree(m_wndDesksBrowser.m_cDialog.m_hWnd);

//	OnEditModeObject();

	InitRollUpClass();

	//test zip

	/*
	GKPlugins->ResourcePlugs[0]->Process(KM_SETRESOURCE,(UINT)"d:\\tpshad.zip",0);
	int getents=GKPlugins->ResourcePlugs[0]->Process(KM_LISTFILES,(UINT)"tpshad\\",0);
	for (int jop=0;jop<getents;jop++)
	{
		PackListFiles *KEnts;
		KEnts=(PackListFiles *)GKPlugins->ResourcePlugs[0]->Process(KM_LISTFILEENTRY,jop,1);
		MessageBox(KEnts->FileName);

	}
	*/

	// test menu
	
	// Timer
	SetTimer(TIMER_ID,KOption->GetAutoSaveDelay()*60000,NULL);
	DragAcceptFiles(TRUE);

	// rendering interface
	/*
	GKPlugins->InitRendererInterface("plugins\\KOGLRenderer.dll");
	CKRenderer *trnd=GKPlugins->CreateInterface(m_hWnd);
	trnd->InfoAbout();
*/

	return 0;
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
    
	delete GKPlugins;

//	delete GDrawScene;

	CMDIFrameWnd::OnDestroy();

}

void CMainFrame::OnClose() 
{
	theApp.WriteProfileInt("Editor State","BarSaved",1);
	SaveBarState("BarStates");

	CString sProfile(_T("DeskBarState"));
	m_wndDesksBrowser.SaveState(sProfile);
    SaveBarState(sProfile);	

	sProfile=_T("AnimateBarState");
	m_wndAnim.SaveState(sProfile);
    SaveBarState(sProfile);	

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
	
	m_wndDesksBrowser.m_cDialog.m_Browser.UpdateCBPath();
	m_wndStatus.m_cDialog.UpdateCBOption();
	DrawViews();
}

void CMainFrame::OnEditSelectCircle() 
{
	FunctionID=EDIT_SELECTCIRCLE;
	m_wndToolBarDesk.m_flyout2.SetButton(1);
    if (GCurPlug!=NULL) GCurPlug->LoseFocus();
}

void CMainFrame::OnEditSelectFence() 
{
	FunctionID=EDIT_SELECTFENCE;
	m_wndToolBarDesk.m_flyout2.SetButton(2);
    if (GCurPlug!=NULL) GCurPlug->LoseFocus();
}

void CMainFrame::OnEditSelectQuad() 
{
	FunctionID=EDIT_SELECTQUAD;
	m_wndToolBarDesk.m_flyout2.SetButton(0);
    if (GCurPlug!=NULL) GCurPlug->LoseFocus();
}

void CMainFrame::OnEditDelete() 
{
	// TODO: Add your command handler code here
	
}


void CMainFrame::OnViewMovespan() 
{
	FunctionID=EDIT_MOVEVIEW;
    if (GCurPlug!=NULL) GCurPlug->LoseFocus();

    //m_wndDialogBar.m_cDialog->ModifyStyleEx(0,WS_EX_CLIENTEDGE,0);
}

void CMainFrame::OnViewRegionfit() 
{
	FunctionID=EDIT_REGIONFIT;
    if (GCurPlug!=NULL) GCurPlug->LoseFocus();
	
}

void CMainFrame::OnViewRotate() 
{
	FunctionID=EDIT_ROTATEVIEW;
    if (GCurPlug!=NULL) GCurPlug->LoseFocus();
	
}

void CMainFrame::OnViewZoominout() 
{
	FunctionID=EDIT_ZOOM;
    if (GCurPlug!=NULL) GCurPlug->LoseFocus();
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
	/*
	if(GetMenuState(GetMenu( )->m_hMenu, ID_VIEW_PLUGINBAR, MF_BYCOMMAND) & MF_CHECKED)
	{
		ShowControlBar(&m_wndDialogBar, FALSE, FALSE);
	}
	else
	{
		ShowControlBar(&m_wndDialogBar, TRUE, FALSE);
	}
	*/
}

void CMainFrame::OnViewModify() 
{
	/*
	if(GetMenuState(GetMenu( )->m_hMenu,ID_VIEW_MODIFY, MF_BYCOMMAND) & MF_CHECKED)
	{
		ShowControlBar(&m_wndToolBarModify, FALSE, FALSE);
	}
	else
	{
		ShowControlBar(&m_wndToolBarModify, TRUE, FALSE);
	}	
	*/
}

void CMainFrame::OnViewModifyview() 
{
	/*
	if(GetMenuState(GetMenu( )->m_hMenu,ID_VIEW_MODIFYVIEW, MF_BYCOMMAND) & MF_CHECKED)
	{
		ShowControlBar(&m_wndToolModifView, FALSE, FALSE);
	}
	else
	{
		ShowControlBar(&m_wndToolModifView, TRUE, FALSE);
	}
	*/
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

	/*
	if(m_wndToolBarModify.IsVisible())
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
		*/
}

void CMainFrame::OnUpdateViewModifyview(CCmdUI* pCmdUI) 
{
	/*
	if(m_wndToolModifView.IsVisible())
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);	
		*/
}

void CMainFrame::OnUpdateViewPluginbar(CCmdUI* pCmdUI) 
{
	/*
	if(m_wndDialogBar.IsVisible())
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);	
		*/
}

void CMainFrame::OnViewSelection() 
{
	/*
	if(GetMenuState(GetMenu( )->m_hMenu,ID_VIEW_SELECTION, MF_BYCOMMAND) & MF_CHECKED)
	{
		ShowControlBar(&m_wndToolBarSelect, FALSE, FALSE);
	}
	else
	{
		ShowControlBar(&m_wndToolBarSelect, TRUE, FALSE);
	}
	*/
}

void CMainFrame::OnUpdateViewSelection(CCmdUI* pCmdUI) 
{
	/*
	if(m_wndToolBarSelect.IsVisible())
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
		*/
}

void CMainFrame::OnViewViewconfiguration() 
{
	/*
	if(GetMenuState(GetMenu( )->m_hMenu,ID_VIEW_VIEWCONFIGURATION, MF_BYCOMMAND) & MF_CHECKED)
	{
		ShowControlBar(&m_wndToolBarViewConf, FALSE, FALSE);
	}
	else
	{
		ShowControlBar(&m_wndToolBarViewConf, TRUE, FALSE);
	}
	*/
}

void CMainFrame::OnUpdateViewViewconfiguration(CCmdUI* pCmdUI) 
{
	/*
	if(m_wndToolBarViewConf.IsVisible())
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
		*/
}

void CMainFrame::OnViewEditmode() 
{
	/*
	if(GetMenuState(GetMenu( )->m_hMenu,ID_VIEW_EDITMODE, MF_BYCOMMAND) & MF_CHECKED)
	{
		ShowControlBar(&m_wndMode, FALSE, FALSE);
	}
	else
	{
		ShowControlBar(&m_wndMode, TRUE, FALSE);
	}
	*/
}

void CMainFrame::OnUpdateViewEditmode(CCmdUI* pCmdUI) 
{
	/*
	if(m_wndMode.IsVisible())
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
		*/
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
				GKPlugins->MeshPlugs[m_wndOutBar->wndBar->GetItemData(index)]->Hwnd=m_wndDialogBar.m_cDialog->m_hWnd;
				
				FunctionID=EDIT_PLUGINCREATION;

				if (gen!=NULL) GCurPlug->Close();
				
				gen=GKPlugins->MeshPlugs[m_wndOutBar->wndBar->GetItemData(index)];
				View->gen=GKPlugins->MeshPlugs[m_wndOutBar->wndBar->GetItemData(index)];
				GKPlugins->MeshPlugs[m_wndOutBar->wndBar->GetItemData(index)]->MainWin=m_hWnd;
				

				//CTestGLDoc *tmpdoc;
				//tmpdoc=(CTestGLDoc *)GetActiveDocument();


				CMDIChildWnd *pChild = (CMDIChildWnd *) GetActiveFrame();
                
				m_wndDialogBar.m_cDialog->SetPlug(GKPlugins->MeshPlugs[m_wndOutBar->wndBar->GetItemData(index)]->Param(),(CWnd *)m_wndDialogBar.m_cDialog);

                if (pChild->GetActiveView()!=NULL)
                {
				    CDeskDoc *tmpdoc = (CDeskDoc *) pChild->GetActiveView()->GetDocument();
					//if (!tmpdoc->IsKindOf( RUNTIME_CLASS( CCrystalEditView ) ) ) 
			        {
						GKPlugins->MeshPlugs[m_wndOutBar->wndBar->GetItemData(index)]->SetContext(tmpdoc->dk,NULL,View);
						CurrentPlug=GKPlugins->MeshPlugs[m_wndOutBar->wndBar->GetItemData(index)];
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
	/*
	if(GetMenuState(GetMenu( )->m_hMenu,ID_VIEW_RENDERMODE, MF_BYCOMMAND) & MF_CHECKED)
	{
		ShowControlBar(&m_wndToolRender, FALSE, FALSE);
	}
	else
	{
		ShowControlBar(&m_wndToolRender, TRUE, FALSE);
	}
	*/
}

void CMainFrame::OnUpdateViewRendermode(CCmdUI* pCmdUI) 
{
	/*
	if(m_wndToolRender.IsVisible())
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
		*/
}

///////////////////////////////////////////////////////////////////////////////
// Modes d'édition

void CMainFrame::OnBuildCentered() 
{
}

void CMainFrame::OnBuildCrossing() 
{
	bCrossing=!bCrossing;
	m_wndStatus.m_cDialog.UpdateChecks();
}

void CMainFrame::OnBuildSnap() 
{
	bSnap=!bSnap;
	m_wndStatus.m_cDialog.UpdateChecks();
}

void CMainFrame::OnBuildAnglesnap() 
{
	bAngleSnap=!bAngleSnap;
	m_wndStatus.m_cDialog.UpdateChecks();
}

void CMainFrame::OnBuildCentroid() 
{
	bCentroid=!bCentroid;
	m_wndStatus.m_cDialog.UpdateChecks();
	DrawViews();
}

void CMainFrame::OnUpdateBuildCentroid(CCmdUI* pCmdUI) 
{
	if(bCentroid)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}


void CMainFrame::OnUpdateBuildAnglesnap(CCmdUI* pCmdUI) 
{
	if(bAngleSnap)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);	
}

void CMainFrame::OnUpdateBuildCentered(CCmdUI* pCmdUI) 
{
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
	//m_wndStatusBar.SetPaneText( wParam, (const char*)lParam);		
	return FALSE; 
}

LRESULT CMainFrame::OnWmDrawScene(WPARAM wParam, LPARAM lParam) 
{
	CMDIChildWnd *pChild = (CMDIChildWnd *) GetActiveFrame();

	CKViewEdit *tmpdoc = (CKViewEdit *) pChild->GetActiveView();
	if (tmpdoc!=NULL)
	{
		if (wParam==-1)
			tmpdoc->DrawViews();
		else
			tmpdoc->DrawView(wParam);
	}
	return FALSE; 
}

LRESULT CMainFrame::OnWmSetPlugin(WPARAM wParam, LPARAM lParam) 
{
    FunctionID=EDIT_PLUGINCREATION;
    return FALSE;
}

LRESULT CMainFrame::OnWmSetMouseCursor(WPARAM wParam, LPARAM lParam) 
{
    CurrentCursor=wParam;
    return FALSE;
}


void CMainFrame::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CMDIFrameWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


///////////////////////////////////////////////////////////////////////////////

void CMainFrame::OnToolsSkyboxeditor() 
{
	CSkyBoxEd csb;
	csb.DoModal();
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
void TransparentButton(CBitmap *bmp)
{
	int i;
	BYTE *dump;
	BITMAP bmpx;
	if (!bmp->GetBitmap(&bmpx)) return;
	dump=new BYTE[bmpx.bmWidthBytes*bmpx.bmHeight];

	COLORREF crBack= GetSysColor(COLOR_BTNFACE);

	bmp->GetBitmapBits( bmpx.bmWidthBytes*bmpx.bmHeight,dump);

	for (i=0;i<bmpx.bmWidthBytes*bmpx.bmHeight;i+=(bmpx.bmBitsPixel/8))
	{
		if ( (dump[i]==0)&&(dump[i+1]==0)&&(dump[i+2]==0) )
		{
			dump[i]=1;
			dump[i+1]=1;
			dump[i+2]=1;
		}
		if ( ( (dump[i]==0)&&(dump[i+1]==0)&&(dump[i+2]==0) ) ||
			( (dump[i]==192)&&(dump[i+1]==192)&&(dump[i+2]==192) ) ||
			( (dump[i]==255)&&(dump[i+1]==0)&&(dump[i+2]==255) ) )
		{
			dump[i]=GetBValue(crBack);
			dump[i+1]=GetGValue(crBack);
			dump[i+2]=GetRValue(crBack);
		}
	}
	bmp->SetBitmapBits(bmpx.bmWidthBytes*bmpx.bmHeight,dump);
	delete [] dump;
}

extern PrimBmp *gobmp[50];

void CMainFrame::RefreshOutBar(void)
{
	int i,j;
	indprim=0;
	// operations

	for (i=0;i<GKPlugins->OperationPlugins.size();i++)
	{
        PlugsIds[i]=30000+i;
    }

	m_Plugs.GetToolBarCtrl().SetBitmapSize(CSize(24,24));
	m_Plugs.GetToolBarCtrl().SetButtonSize(CSize(31,31));

	//PlugImageList.Create(24,24,ILC_COLOR24,8,1);
	PlugImageListHot.Create(24,24,ILC_COLOR24,8,1);

	if (GKPlugins->OperationPlugins.size()>0)
	{
		m_Plugs.SetButtons( PlugsIds, GKPlugins->OperationPlugins.size());
		
		for (i=0;i<GKPlugins->OperationPlugins.size();i++)
		{
			//TransparentButton(GKPlugins->OperationPlugins[i]->GetBitmap());
			TransparentButton(GKPlugins->OperationPlugins[i]->GetBitmap());

			//PlugImageList.Add(GKPlugins->OperationPlugins[i]->GetBitmap(),RGB(0,0,0));
			PlugImageListHot.Add(GKPlugins->OperationPlugins[i]->GetBitmap(),RGB(0,0,0));

		}
		m_Plugs.GetToolBarCtrl().SetImageList(&PlugImageListHot);
		//m_Plugs.GetToolBarCtrl().SetHotImageList(&PlugImageListHot);
	}

	// primitives

	for (i=0;i<GKPlugins->PrimitivePlugins.size();i++)
	{
		//gobmp[i]=(PrimBmp*)GKPlugins->PrimitivePlugins[i]->GetAllPrimitives();
		for (j=0;j<gobmp[i]->NbBmps;j++)
		{

	        PrimitivesIds[indprim]=31000+indprim;
			indprim++;
		}
    }

	m_Primitives.GetToolBarCtrl().SetBitmapSize(CSize(24,24));
	m_Primitives.GetToolBarCtrl().SetButtonSize(CSize(31,31));

	//PrimitivesImageList.Create(24,24,ILC_COLOR24,8,1);
	PrimitivesImageListHot.Create(24,24,ILC_COLOR24,8,1);

	if (GKPlugins->PrimitivePlugins.size()>0)
	{
		m_Primitives.SetButtons( PrimitivesIds, indprim);

		for (i=0;i<GKPlugins->PrimitivePlugins.size();i++)
		{
			for (j=0;j<gobmp[i]->NbBmps;j++)
			{
				//TransparentButton(&gobmp[i]->BmpOut[j]);
				TransparentButton(&gobmp[i]->Bmp[j]);

				//PrimitivesImageList.Add(&gobmp[i]->BmpOut[j],RGB(0,0,0));
				PrimitivesImageListHot.Add(&gobmp[i]->Bmp[j],RGB(0,0,0));
			}

		}
		m_Primitives.GetToolBarCtrl().SetImageList(&PrimitivesImageListHot);
		//m_Primitives.GetToolBarCtrl().SetHotImageList(&PrimitivesImageListHot);
	}
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	int i,j;
	int testprin=0;

	for (i=0;i<GKPlugins->OperationPlugins.size();i++)
        if (PlugsIds[i]==nID) return TRUE;

	for (i=0;i<GKPlugins->PrimitivePlugins.size();i++)
		for (j=0;j<gobmp[i]->NbBmps;j++)
	        if (PrimitivesIds[testprin++]==nID) return TRUE;

	if ((nID>=40000)&&(nID<(40000+loc.GetLanguageCount())))
	{
		if (pExtra!=NULL)
		{
			CCmdUI* pCmdUI = (CCmdUI*)pExtra;
			if ((loc.GetCurrentLangInd()+40000)==nID)
				pCmdUI->SetCheck(TRUE);
			else
				pCmdUI->SetCheck(FALSE);
		}
		return TRUE;
	}

	return CMDIFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

extern int CurPrimInd;
extern CKScenePlugin *CurGenLib;
extern CurAbsPrim;
BOOL CMainFrame::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	for (int i=0;i<indprim;i++)
	{
		m_Primitives.GetToolBarCtrl().SetState(PrimitivesIds[i],BST_UNCHECKED);
	}

	if (wParam==ID_CREATEPRIM)
	{
		m_Primitives.GetToolBarCtrl().SetState(PrimitivesIds[CurAbsPrim],BST_CHECKED);
	}
	if ((wParam>=30000)&&(wParam<(30000+GKPlugins->OperationPlugins.size())))
    {
        
		int index = (int) wParam-30000;
		GKPlugins->OperationPlugins[index]->m_hWnd=m_wndDesksBrowser.m_cDialog.m_cDialog.m_hWnd;
		
		FunctionID=EDIT_PLUGINCREATION;

		if (GCurPlug!=NULL) GCurPlug->Close();
		
		GCurPlug=GKPlugins->OperationPlugins[index];

		CMDIChildWnd *pChild = (CMDIChildWnd *) GetActiveFrame();
        
		m_wndDesksBrowser.m_cDialog.m_cDialog.SetPlug(GCurPlug->Open(GCurPlug->m_hWnd),(CWnd *)&m_wndDesksBrowser.m_cDialog.m_cDialog);

        if (pChild->GetActiveView()!=NULL)
        {

			CKViewEdit *edt=(CKViewEdit *)pChild->GetActiveView();
			edt->m_Renderer->m_Plugin=GKPlugins->OperationPlugins[index];
			CDeskDoc *tmpdoc = (CDeskDoc *) pChild->GetActiveView()->GetDocument();
			GKPlugins->OperationPlugins[index]->SetScene(tmpdoc->m_Scene);
			GCurPlug=GKPlugins->OperationPlugins[index];
        }
    }


	if ((wParam>=31000)&&(wParam<32000))
    {
        
		int index = (int) wParam-31000;

		m_wndToolBarDesk.m_flyout.SetDaPrime(index);
		m_Primitives.GetToolBarCtrl().SetState(PrimitivesIds[index],BST_CHECKED);
		/*
		CurPrimInd=m_wndToolBarDesk.m_flyout.Indices[index];
		CurGenLib=m_wndToolBarDesk.m_flyout.m_Plugins[index];
		m_wndToolBarDesk.m_flyout.SetButton(index);
		*/


    }
	
	if ((wParam>=40000)&&(wParam<(40000+loc.GetLanguageCount())))
	{
		MessageBox("You can't change the language in this release!");
	}

	return CMDIFrameWnd::OnCommand(wParam, lParam);
}



typedef struct
{
	DWORD MenuID,StrID;
} LocToolTips;

LocToolTips AllLocTips[206]={
{	    ID_FILE_NEW             ,207}, //"Create a new document\nNew" />
{	    ID_FILE_OPEN            ,208}, //"Open an existing document\nOpen" />
{	    ID_FILE_CLOSE           ,209}, //"Close the active document\nClose" />
{	    ID_FILE_SAVE            ,210}, //"Save the active document\nSave" />
{	    ID_FILE_SAVE_AS         ,211}, //"Save the active document with a new name\nSave As" />
{	    ID_APP_ABOUT            ,212}, //"Display program information, version number and copyright\nAbout" />
{	    ID_APP_EXIT             ,213}, //"Quit the application; prompts to save documents\nExit" />
{	    ID_FILE_MRU_FILE1       ,214}, //"Open this document" />
{	    ID_FILE_MRU_FILE2       ,215}, //"Open this document" />
{	    ID_FILE_MRU_FILE3       ,216}, //"Open this document" />
{	    ID_FILE_MRU_FILE4       ,217}, //"Open this document" />
{	    ID_FILE_MRU_FILE5       ,218}, //"Open this document" />
{	    ID_FILE_MRU_FILE6       ,219}, //"Open this document" />
{	    ID_FILE_MRU_FILE7       ,220}, //"Open this document" />
{	    ID_FILE_MRU_FILE8       ,221}, //"Open this document" />
{	    ID_FILE_MRU_FILE9       ,222}, //"Open this document" />
{	    ID_FILE_MRU_FILE10      ,223}, //"Open this document" />
{	    ID_FILE_MRU_FILE11      ,224}, //"Open this document" />
{	    ID_FILE_MRU_FILE12      ,225}, //"Open this document" />
{	    ID_FILE_MRU_FILE13      ,226}, //"Open this document" />
{	    ID_FILE_MRU_FILE14      ,227}, //"Open this document" />
{	    ID_FILE_MRU_FILE15      ,228}, //"Open this document" />
{	    ID_FILE_MRU_FILE16      ,229}, //"Open this document" />
{	    ID_NEXT_PANE            ,230}, //"Switch to the next window pane\nNext Pane" />
{	    ID_PREV_PANE            ,231}, //"Switch back to the previous window pane\nPrevious Pane" />
{	    ID_WINDOW_NEW           ,232}, //"Open another window for the active document\nNew Window" />
{	    ID_WINDOW_ARRANGE       ,233}, //"Arrange icons at the bottom of the window\nArrange Icons" />
{	    ID_WINDOW_CASCADE       ,234}, //"Arrange windows so they overlap\nCascade Windows" />
{	    ID_WINDOW_TILE_HORZ     ,235}, //"Arrange windows as non-overlapping tiles\nTile Windows" />
{	    ID_WINDOW_TILE_VERT     ,236}, //"Arrange windows as non-overlapping tiles\nTile Windows" />
{	    ID_WINDOW_SPLIT         ,237}, //"Split the active window into panes\nSplit" />
{	    ID_EDIT_CLEAR           ,238}, //"Erase the selection\nErase" />
{	    ID_EDIT_CLEAR_ALL       ,239}, //"Erase everything\nErase All" />
{	    ID_EDIT_COPY            ,240}, //"Copy the selection and put it on the Clipboard\nCopy" />
{	    ID_EDIT_CUT             ,241}, //"Cut the selection and put it on the Clipboard\nCut" />
{	    ID_EDIT_FIND            ,242}, //"Find the specified text\nFind" />
{	    ID_EDIT_PASTE           ,243}, //"Insert Clipboard contents\nPaste" />
{	    ID_EDIT_REPEAT          ,244}, //"Repeat the last action\nRepeat" />
{	    ID_EDIT_REPLACE         ,245}, //"Replace specific text with different text\nReplace" />
{	    ID_EDIT_SELECT_ALL      ,246}, //"Select the entire document\nSelect All" />
{	    ID_EDIT_UNDO            ,247}, //"Undo the last action\nUndo" />
{	    ID_EDIT_REDO            ,248}, //"Redo the previously undone action\nRedo" />
{	    ID_VIEW_TOOLBAR         ,249}, //"Show or hide the toolbar\nToggle ToolBar" />
{	    ID_VIEW_STATUS_BAR      ,250}, //"Show or hide the status bar\nToggle StatusBar" />
{	    ID_EDIT_SELECT_SINGLE   ,251}, //"Select single\nSelect single" />
{	    ID_EDIT_SELECT_CIRCLE   ,252}, //"Select circle\nSelect circle" />
{	    ID_EDIT_SELECT_QUAD     ,253}, //"Select quad\nSelect quad" />
{	    ID_EDIT_SELECT_FENCE    ,254}, //"Select fence\nSelect fence" />
{	    ID_VIEW_CONFIG_2X2      ,255}, //"2x2 view\n2x2 view" />
{	    ID_VIEW_CONFIG_1X2      ,256}, //"2x1 view\n2x1 view" />
{	    ID_VIEW_CONFIG_2X1      ,257}, //"2x1 view\n2x1 view" />
{	    ID_VIEW_CONFIG_1X3      ,258}, //"3x1 view\n3x1 view" />
{	    ID_VIEW_CONFIG_3X1      ,259}, //"3x1 view\n3x1 view" />
{	    ID_EDIT_MOVE            ,260}, //"Move\nMove" />
{	    ID_EDIT_SCALE           ,261}, //"Scale\nScale" />
{	    ID_EDIT_ROTATE          ,262}, //"Rotate\nRotate" />
{	    ID_EDIT_DELETE          ,263}, //"Delete\nDelete" />
{	    ID_VIEW_TYPE_TOP        ,264}, //"Switch view top\nSwitch view top" />
{	    ID_VIEW_TYPE_BOTTOM     ,265}, //"Switch view bottom\nSwitch view bottom" />
{	    ID_VIEW_TYPE_LEFT       ,266}, //"Switch view left\nSwitch view left" />
{	    ID_VIEW_TYPE_RIGHT      ,267}, //"Switch view right\nSwitch view right" />
{	    ID_VIEW_TYPE_FRONT      ,268}, //"Switch view front\nSwitch view front" />
{	    ID_VIEW_TYPE_BACK       ,269}, //"Switch view back\nSwitch view back" />
{	    ID_VIEW_TYPE_CAMERA     ,270}, //"Switch view camera\nSwitch view camera" />
{	    ID_VIEW_ROTATE          ,271}, //"Rotate view\nRotate view" />
{	    ID_VIEW_MOVESPAN        ,272}, //"Move view\nMove view" />
{	    ID_VIEW_ZOOMINOUT       ,273}, //"Zoom in-out\nZoom in-out" />
{	    ID_VIEW_REGIONFIT       ,274}, //"Zoom region\nZoom region" />
{	    ID_EDIT_MODE_VERTEX     ,275}, //"Vertex mode\nVertex mode" />
{	    ID_EDIT_MODE_FACE       ,276}, //"Face mode\nFace mode" />
{	    ID_EDIT_MODE_OBJECT     ,278}, //"Object mode\nObject mode" />
{	    ID_EDIT_MOVEAXE         ,279}, //"Move axis\nMove axis" />
{	    ID_VIEW_EXTENDVIEW      ,280}, //"Center view\nCenter view" />
{	    ID_VIEW_EXTENDSVIEWS    ,281}, //"Center all views\nCenter all views" />
{	    ID_VIEW_RENDERMODE_MAPPED ,282}, //"Render mapped\nRender mapped" />
{	    ID_VIEW_RENDERMODE_WIRE ,283}, //"Render wire\nRender wire" />
{	    ID_VIEW_CONFIG_FULLSCREEN ,284}, //"Switch view full window\nSwitch view full window" />
{	    ID_BUILD_SNAP           ,285}, //"Snap\nSnap" />
{	    ID_ABOUT_KAPSUL         ,286}, //"About" />
{	    ID_BUILD_CENTERED       ,287}, //"Center rotation\nCenter rotation" />
{	    ID_BUILD_CROSSING       ,288}, //"Crossing selection\nCrossing selection" />
{	    ID_VIEW_TYPE_PERSPECTIVE ,289}, //"Switch view perspective\nSwitch view perspective" />
{	    IDS_MENU_UNDO_FORMAT    ,290}, //"&Undo %s\tCtrl+Z" />
{	    IDS_MENU_REDO_FORMAT    ,291}, //"&Redo %s\tCtrl+Y" />
{	    IDS_MENU_UNDO_DEFAULT   ,292}, //"&Undo\tCtrl+Z" />
{	    IDS_MENU_REDO_DEFAULT   ,293}, //"&Redo\tCtrl+Z" />
{	    IDS_EDITOP_UNKNOWN      ,294}, //"Unknown" />
{	    IDS_EDITOP_PASTE        ,295}, //"Paste" />
{	    IDS_EDITOP_DELSELECTION ,296}, //"Delete Selection" />
{	    IDS_EDITOP_CUT          ,297}, //"Cut" />
{	    IDS_EDITOP_DELETE       ,298} }; //"Delete" />


int TTFindLocStr(DWORD dMenuID)
{
	for (int i=0;i<206;i++)
	{
		if (AllLocTips[i].MenuID==dMenuID)
			return AllLocTips[i].StrID;
	}
	return 0;
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
            strTipText=GKPlugins->OperationPlugins[nID-30000]->GetName();
        else
        {
            //LoadString(nID, szFullText);
			strTipText=loc.GetString(TTFindLocStr(nID),"ToolTip not found");
			/*
			int LocID;
			switch (nID)
			{
			case:
				break;
			}
			*/

            //strTipText.LoadString(nID);//=szFullText;
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
		tmpdoc->m_Scene->Redo();
		DrawViews();
    }	
}

void CMainFrame::OnEditUndo() 
{
	CMDIChildWnd *pChild = (CMDIChildWnd *) GetActiveFrame();
        
    if (pChild->GetActiveView()!=NULL)
    {
		CDeskDoc *tmpdoc = (CDeskDoc *) pChild->GetActiveView()->GetDocument();
		tmpdoc->m_Scene->Undo(GCurPlug);
		DrawViews();
    }	
}

void CMainFrame::OnUpdateEditRedo(CCmdUI* pCmdUI) 
{
	/*
	CMDIChildWnd *pChild = (CMDIChildWnd *) GetActiveFrame();
        
    if (pChild->GetActiveView()!=NULL)
    {
		CDeskDoc *tmpdoc = (CDeskDoc *) pChild->GetActiveView()->GetDocument();
		if (tmpdoc->dk->FirstRedo==NULL)
			pCmdUI->Enable(false);
		else
			pCmdUI->Enable();
		
    }
	*/
}

void CMainFrame::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
	/*
	CMDIChildWnd *pChild = (CMDIChildWnd *) GetActiveFrame();
        
    if (pChild->GetActiveView()!=NULL)
    {
		CDeskDoc *tmpdoc = (CDeskDoc *) pChild->GetActiveView()->GetDocument();
		if (tmpdoc->dk->FirstUndo==NULL)
			pCmdUI->Enable(false);
		else
			pCmdUI->Enable();
    }
	*/
}

void CMainFrame::OnToolsEntitymanager()
{
	/*
	CEntiDlg ediag;
	ediag.DoModal();
*/
}

void CMainFrame::OnViewCompilationtools()
{
	/*
	if(GetMenuState(GetMenu( )->m_hMenu,ID_VIEW_COMPILATIONTOOLS, MF_BYCOMMAND) & MF_CHECKED)
	{
		ShowControlBar(&m_wndToolCompilation, FALSE, FALSE);
	}
	else
	{
		ShowControlBar(&m_wndToolCompilation, TRUE, FALSE);
	}
	*/
}

void CMainFrame::OnUpdateViewCompilationtools(CCmdUI *pCmdUI)
{
	/*
	if(m_wndToolCompilation.IsVisible())
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);	
		*/
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
	/*
	if(GetMenuState(GetMenu( )->m_hMenu,ID_VIEW_MAPSBROWSER, MF_BYCOMMAND) & MF_CHECKED)
	{
		ShowControlBar(&m_wndMatBrowser, FALSE, FALSE);
	}
	else
	{
		ShowControlBar(&m_wndMatBrowser, TRUE, FALSE);
	}
	*/
}

void CMainFrame::OnUpdateViewMapsbrowser(CCmdUI* pCmdUI) 
{
	/*
	if(m_wndMatBrowser.IsVisible())
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
		*/
}

extern int FunctionSwitch;

void CMainFrame::OnMoveRotateScale()
{
	FunctionSwitch=0;
}

void CMainFrame::OnMoveRotateTaperSquiz()
{
	FunctionSwitch=1;
}

void CMainFrame::OnMoveRotateBend()
{
	FunctionSwitch=2;
}

void CMainFrame::OnUpdateMoveRotateScale(CCmdUI* pCmdUI) 
{
	if(FunctionSwitch==0)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CMainFrame::OnUpdateMoveRotateTaperSquiz(CCmdUI* pCmdUI) 
{
	if(FunctionSwitch==1)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CMainFrame::OnUpdateMoveRotateBend(CCmdUI* pCmdUI) 
{
	if(FunctionSwitch==2)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}


BOOL CMainFrame::VerifyBarState(LPCTSTR lpszProfileName)
{
    CDockState state;
    state.LoadState(lpszProfileName);

    for (int i = 0; i < state.m_arrBarInfo.GetSize(); i++)
    {
        CControlBarInfo* pInfo = (CControlBarInfo*)state.m_arrBarInfo[i];
        ASSERT(pInfo != NULL);
        int nDockedCount = pInfo->m_arrBarID.GetSize();
        if (nDockedCount > 0)
        {
            // dockbar
            for (int j = 0; j < nDockedCount; j++)
            {
                UINT nID = (UINT) pInfo->m_arrBarID[j];
                if (nID == 0) continue; // row separator
                if (nID > 0xFFFF)
                    nID &= 0xFFFF; // placeholder - get the ID
                if (GetControlBar(nID) == NULL)
                    return FALSE;
            }
        }
        
        if (!pInfo->m_bFloating) // floating dockbars can be created later
            if (GetControlBar(pInfo->m_nBarID) == NULL)
                return FALSE; // invalid bar ID
    }

    return TRUE;
}

void CMainFrame::OnAppAbout() 
{
	CAboutDlg m_About;
	m_About.DoModal();
}

void CMainFrame::OnAboutKapsul() 
{
	CAboutDlg m_About;
	m_About.DoModal();	
}

HMENU CMainFrame::NewMenu()
{
  static UINT toolbars[]={
    IDR_MAINFRAME
  };
  // Load the menu from the resources
  m_menu.LoadMenu(IDR_KAPSULDESK);  // ****replace IDR_MENUTYPE with your menu ID****
  // Use ModifyODMenu to add a bitmap to a menu options.The first parameter
  // is the menu option text string.If it's NULL, keep the current text
  // string.The second option is the ID of the menu option, or the menu
  // option text (can use this for adding bitmaps to popup options) to change.
  // The third option is the resource ID of the bitmap.This can also be a
  // toolbar ID in which case the class searches the toolbar for the
  // appropriate bitmap.Only Bitmap and Toolbar resources are supported.
  // m_menu.ModifyODMenu(NULL,ID_WINDOW_NEW,IDB_WINDOW_NEW);
  // m_menu.ModifyODMenu(NULL, "&Tile",IDB_WINDOW_TILE);
  m_menu.ModifyODMenu(loc.GetString(100),ID_FILE_NEW);
  m_menu.ModifyODMenu(loc.GetString(101),ID_FILE_OPEN);
  m_menu.ModifyODMenu(loc.GetString(102),ID_FILE_CLOSE);
  m_menu.ModifyODMenu(loc.GetString(103),ID_FILE_SAVE);
  m_menu.ModifyODMenu(loc.GetString(104),ID_FILE_SAVE_AS);
  m_menu.ModifyODMenu(loc.GetString(108),ID_APP_EXIT);
  m_menu.ModifyODMenu(loc.GetString(109),ID_EDIT_UNDO);
  m_menu.ModifyODMenu(loc.GetString(110),ID_EDIT_REDO);
  m_menu.ModifyODMenu(loc.GetString(112),ID_EDIT_CUT);
  m_menu.ModifyODMenu(loc.GetString(113),ID_EDIT_COPY);
  m_menu.ModifyODMenu(loc.GetString(114),ID_EDIT_PASTE);
  m_menu.ModifyODMenu(loc.GetString(115),ID_EDIT_SELECT_CIRCLE);
  m_menu.ModifyODMenu(loc.GetString(116),ID_EDIT_SELECT_QUAD);
  m_menu.ModifyODMenu(loc.GetString(117),ID_EDIT_SELECT_FENCE);
  m_menu.ModifyODMenu(loc.GetString(118),ID_EDIT_SELECT_ALL);
  m_menu.ModifyODMenu(loc.GetString(120),ID_EDIT_DELETE);
  m_menu.ModifyODMenu(loc.GetString(121),ID_EDIT_MOVEROTATESCALE);
  m_menu.ModifyODMenu(loc.GetString(122),ID_EDIT_MOVEROTATETAPERSQUIZ);
  m_menu.ModifyODMenu(loc.GetString(123),ID_EDIT_BEND);
  m_menu.ModifyODMenu(loc.GetString(124),ID_EDIT_MODE_VERTEX);
  m_menu.ModifyODMenu(loc.GetString(125),ID_EDIT_MODE_FACE);
  m_menu.ModifyODMenu(loc.GetString(126),ID_EDIT_MODE_OBJECT);
  m_menu.ModifyODMenu(loc.GetString(127),ID_EDIT_ENTITY_ALL);
  m_menu.ModifyODMenu(loc.GetString(128),ID_EDIT_ENTITY_CAMERA);
  m_menu.ModifyODMenu(loc.GetString(129),ID_EDIT_ENTITY_SHAPE);
  m_menu.ModifyODMenu(loc.GetString(130),ID_EDIT_ENTITY_LIGHT);
  m_menu.ModifyODMenu(loc.GetString(131),ID_EDIT_ENTITY_OBJECT);
  m_menu.ModifyODMenu(loc.GetString(132),ID_EDIT_ENTITY_PARTICLE);
  m_menu.ModifyODMenu(loc.GetString(133),ID_EDIT_ENTITY_SKELETTON);
  m_menu.ModifyODMenu(loc.GetString(134),ID_VIEW_TOOLBAR);
  m_menu.ModifyODMenu(loc.GetString(135),ID_VIEW_STATUS_BAR);
  m_menu.ModifyODMenu(loc.GetString(136),ID_VIEW_EDITBAR);
  m_menu.ModifyODMenu(loc.GetString(137),ID_VIEW_BUILDBAR);
  m_menu.ModifyODMenu(loc.GetString(138),ID_VIEW_ANIMATIONBAR);
  m_menu.ModifyODMenu(loc.GetString(139),ID_VIEW_DOCKBAR);
  m_menu.ModifyODMenu(loc.GetString(141),ID_VIEW_CONFIG_2X2);
  m_menu.ModifyODMenu(loc.GetString(142),ID_VIEW_CONFIG_1X2);
  m_menu.ModifyODMenu(loc.GetString(143),ID_VIEW_CONFIG_2X1);
  m_menu.ModifyODMenu(loc.GetString(144),ID_VIEW_CONFIG_1X3);
  m_menu.ModifyODMenu(loc.GetString(145),ID_VIEW_CONFIG_3X1);
  m_menu.ModifyODMenu(loc.GetString(146),ID_VIEW_CONFIG_FULLSCREEN);
  m_menu.ModifyODMenu(loc.GetString(147),ID_VIEW_TYPE_TOP);
  m_menu.ModifyODMenu(loc.GetString(148),ID_VIEW_TYPE_BOTTOM);
  m_menu.ModifyODMenu(loc.GetString(149),ID_VIEW_TYPE_LEFT);
  m_menu.ModifyODMenu(loc.GetString(150),ID_VIEW_TYPE_RIGHT);
  m_menu.ModifyODMenu(loc.GetString(151),ID_VIEW_TYPE_FRONT);
  m_menu.ModifyODMenu(loc.GetString(152),ID_VIEW_TYPE_BACK);
  m_menu.ModifyODMenu(loc.GetString(153),ID_VIEW_TYPE_CAMERA);
  m_menu.ModifyODMenu(loc.GetString(154),ID_VIEW_TYPE_PERSPECTIVE);
  m_menu.ModifyODMenu(loc.GetString(156),ID_VIEW_ROTATE);
  m_menu.ModifyODMenu(loc.GetString(157),ID_VIEW_MOVESPAN);
  m_menu.ModifyODMenu(loc.GetString(158),ID_VIEW_ZOOMINOUT);
  m_menu.ModifyODMenu(loc.GetString(159),ID_VIEW_REGIONFIT);
  m_menu.ModifyODMenu(loc.GetString(161),ID_VIEW_EXTENDVIEW);
  m_menu.ModifyODMenu(loc.GetString(162),ID_VIEW_EXTENDSVIEWS);
  m_menu.ModifyODMenu(loc.GetString(164),ID_VIEW_RENDER_MAPPEDOUTLINED);
  m_menu.ModifyODMenu(loc.GetString(165),ID_VIEW_RENDERMODE_MAPPED);
  m_menu.ModifyODMenu(loc.GetString(166),ID__RENDER_FLATSHADED);
  m_menu.ModifyODMenu(loc.GetString(167),ID_VIEW_RENDERMODE_WIRE);
  m_menu.ModifyODMenu(loc.GetString(168),ID_SKYBOX_LOAD);
  m_menu.ModifyODMenu(loc.GetString(169),ID_SKYBOX_NONE);
  m_menu.ModifyODMenu(loc.GetString(170),ID_VIEW_GRID_VISIBLE);
  m_menu.ModifyODMenu(loc.GetString(171),ID_VIEW_GRID_INCREASEGRID);
  m_menu.ModifyODMenu(loc.GetString(172),ID_VIEW_GRID_DECREASEGRID);
  m_menu.ModifyODMenu(loc.GetString(173),ID_VIEW_FLY);
  m_menu.ModifyODMenu(loc.GetString(174),ID_BUILD_SNAP);
  m_menu.ModifyODMenu(loc.GetString(175),ID_BUILD_CENTERED);
  m_menu.ModifyODMenu(loc.GetString(176),ID_BUILD_CROSSING);
  m_menu.ModifyODMenu(loc.GetString(177),ID_TOOLS_OPTION);
  m_menu.ModifyODMenu(loc.GetString(178),ID_TOOLS_SKYBOXEDITOR);
  m_menu.ModifyODMenu(loc.GetString(179),ID_WINDOW_NEW);
  m_menu.ModifyODMenu(loc.GetString(180),ID_WINDOW_CASCADE);
  m_menu.ModifyODMenu(loc.GetString(181),ID_WINDOW_TILE_HORZ);
  m_menu.ModifyODMenu(loc.GetString(182),ID_WINDOW_ARRANGE);
  m_menu.ModifyODMenu(loc.GetString(183),ID_ABOUT_KAPSUL);
  m_menu.ModifyODMenu(loc.GetString(184),ID_HELP_TIPOFTHEDAY);
  m_menu.ModifyODMenu(loc.GetString(312),ID_FILE_MRU_FILE1);

  m_menu.ModifyODMenu(loc.GetString(182),ID_FILE_CLOSEALL);
  m_menu.ModifyODMenu(loc.GetString(183),ID_ABOUT_KAPSUL);
  m_menu.ModifyODMenu(loc.GetString(184),ID_HELP_TIPOFTHEDAY);
  m_menu.ModifyODMenu(loc.GetString(313),ID_FILE_CLOSEALL);
  m_menu.ModifyODMenu(loc.GetString(314),ID_FILE_NEWPROJECT);
  m_menu.ModifyODMenu(loc.GetString(315),ID_FILE_OPENPROJECT);
  m_menu.ModifyODMenu(loc.GetString(316),ID_FILE_SAVEPROJECT);
  m_menu.ModifyODMenu(loc.GetString(317),ID_FILE_CLOSEPROJECT);
  m_menu.ModifyODMenu(loc.GetString(318),ID_TOOLS_BACKGROUNDWORLDCAP);
  

  
  BCMenu *tmpbc=m_menu.GetSubBCMenu(loc.GetString(16,"Localization").GetBuffer(0));
  //tmpbc->InsertMenu(tmppos,1,40000,"English",1);//,int nIconNormal=-1);

  for (int i=0;i<loc.GetLanguageCount();i++)
	tmpbc->AppendODMenu(loc.GetLanguageName(i),MF_OWNERDRAW,40000+i);

  m_menu.RemoveMenu(ID_TOOLS_LOCALIZATION_LOC1,0);
	  //("Test",ID_LOCALIZATION,40000,IDR_KAPSULDESK);
  /*
  m_menu.ModifyODMenu(loc.GetString(100),ID_FILE_NEW);
  m_menu.ModifyODMenu(loc.GetString(100),ID_FILE_NEW);
  m_menu.ModifyODMenu(loc.GetString(100),ID_FILE_NEW);
  m_menu.ModifyODMenu(loc.GetString(100),ID_FILE_NEW);
  m_menu.ModifyODMenu(loc.GetString(100),ID_FILE_NEW);
  m_menu.ModifyODMenu(loc.GetString(100),ID_FILE_NEW);
  m_menu.ModifyODMenu(loc.GetString(100),ID_FILE_NEW);
  m_menu.ModifyODMenu(loc.GetString(100),ID_FILE_NEW);
  m_menu.ModifyODMenu(loc.GetString(100),ID_FILE_NEW);
  m_menu.ModifyODMenu(loc.GetString(100),ID_FILE_NEW);
  m_menu.ModifyODMenu(loc.GetString(100),ID_FILE_NEW);
  m_menu.ModifyODMenu(loc.GetString(100),ID_FILE_NEW);
  m_menu.ModifyODMenu(loc.GetString(100),ID_FILE_NEW);
  m_menu.ModifyODMenu(loc.GetString(100),ID_FILE_NEW);
  m_menu.ModifyODMenu(loc.GetString(100),ID_FILE_NEW);
  m_menu.ModifyODMenu(loc.GetString(100),ID_FILE_NEW);
  m_menu.ModifyODMenu(loc.GetString(100),ID_FILE_NEW);
  m_menu.ModifyODMenu(loc.GetString(100),ID_FILE_NEW);
  m_menu.ModifyODMenu(loc.GetString(100),ID_FILE_NEW);
  m_menu.ModifyODMenu(loc.GetString(100),ID_FILE_NEW);
  m_menu.ModifyODMenu(loc.GetString(100),ID_FILE_NEW);
  m_menu.ModifyODMenu(loc.GetString(100),ID_FILE_NEW);
  m_menu.ModifyODMenu(loc.GetString(100),ID_FILE_NEW);
  m_menu.ModifyODMenu(loc.GetString(100),ID_FILE_NEW);
  m_menu.ModifyODMenu(loc.GetString(100),ID_FILE_NEW);
  m_menu.ModifyODMenu(loc.GetString(100),ID_FILE_NEW);
  m_menu.ModifyODMenu(loc.GetString(100),ID_FILE_NEW);
  m_menu.ModifyODMenu(loc.GetString(100),ID_FILE_NEW);
  m_menu.ModifyODMenu(loc.GetString(100),ID_FILE_NEW);
  m_menu.ModifyODMenu(loc.GetString(100),ID_FILE_NEW);
  m_menu.ModifyODMenu(loc.GetString(100),ID_FILE_NEW);
  m_menu.ModifyODMenu(loc.GetString(100),ID_FILE_NEW);
  m_menu.ModifyODMenu(loc.GetString(100),ID_FILE_NEW);
  m_menu.ModifyODMenu(loc.GetString(100),ID_FILE_NEW);
  m_menu.ModifyODMenu(loc.GetString(100),ID_FILE_NEW);
  m_menu.ModifyODMenu(loc.GetString(100),ID_FILE_NEW);
  m_menu.ModifyODMenu(loc.GetString(100),ID_FILE_NEW);
  m_menu.ModifyODMenu(loc.GetString(100),ID_FILE_NEW);
  m_menu.ModifyODMenu(loc.GetString(100),ID_FILE_NEW);
  m_menu.ModifyODMenu(loc.GetString(100),ID_FILE_NEW);
  m_menu.ModifyODMenu(loc.GetString(100),ID_FILE_NEW);
  m_menu.ModifyODMenu(loc.GetString(100),ID_FILE_NEW);
  m_menu.ModifyODMenu(loc.GetString(100),ID_FILE_NEW);
  m_menu.ModifyODMenu(loc.GetString(100),ID_FILE_NEW);
  m_menu.ModifyODMenu(loc.GetString(100),ID_FILE_NEW);
*/
  /*
  m_menu.FindMenuOption("Option");
  m_menu.setwin
  */
  // Another method for adding bitmaps to menu options is through the
  // LoadToolbars member function.This method allows you to add all
  // the bitmaps in a toolbar object to menu options (if they exist).
  // The first function parameter is an array of toolbar id's.
  // The second is the number of toolbar id's. There is also a
  // function called LoadToolbar that just takes an id.
  m_menu.LoadToolbars(toolbars,1);
  return(m_menu.Detach());
}
  

HMENU CMainFrame::NewDefaultMenu()
{
  m_default.LoadMenu(IDR_MAINFRAME);
	m_default.ModifyODMenu(loc.GetString(100),ID_FILE_NEW);
  m_default.ModifyODMenu(loc.GetString(101),ID_FILE_OPEN);
  m_default.ModifyODMenu(loc.GetString(102),ID_FILE_CLOSE);
  m_default.ModifyODMenu(loc.GetString(103),ID_FILE_SAVE);
  m_default.ModifyODMenu(loc.GetString(104),ID_FILE_SAVE_AS);
  m_default.ModifyODMenu(loc.GetString(108),ID_APP_EXIT);
  m_default.ModifyODMenu(loc.GetString(109),ID_EDIT_UNDO);
  m_default.ModifyODMenu(loc.GetString(110),ID_EDIT_REDO);
  m_default.ModifyODMenu(loc.GetString(112),ID_EDIT_CUT);
  m_default.ModifyODMenu(loc.GetString(113),ID_EDIT_COPY);
  m_default.ModifyODMenu(loc.GetString(114),ID_EDIT_PASTE);
  m_default.ModifyODMenu(loc.GetString(115),ID_EDIT_SELECT_CIRCLE);
  m_default.ModifyODMenu(loc.GetString(116),ID_EDIT_SELECT_QUAD);
  m_default.ModifyODMenu(loc.GetString(117),ID_EDIT_SELECT_FENCE);
  m_default.ModifyODMenu(loc.GetString(118),ID_EDIT_SELECT_ALL);
  m_default.ModifyODMenu(loc.GetString(120),ID_EDIT_DELETE);
  m_default.ModifyODMenu(loc.GetString(121),ID_EDIT_MOVEROTATESCALE);
  m_default.ModifyODMenu(loc.GetString(122),ID_EDIT_MOVEROTATETAPERSQUIZ);
  m_default.ModifyODMenu(loc.GetString(123),ID_EDIT_BEND);
  m_default.ModifyODMenu(loc.GetString(124),ID_EDIT_MODE_VERTEX);
  m_default.ModifyODMenu(loc.GetString(125),ID_EDIT_MODE_FACE);
  m_default.ModifyODMenu(loc.GetString(126),ID_EDIT_MODE_OBJECT);
  m_default.ModifyODMenu(loc.GetString(127),ID_EDIT_ENTITY_ALL);
  m_default.ModifyODMenu(loc.GetString(128),ID_EDIT_ENTITY_CAMERA);
  m_default.ModifyODMenu(loc.GetString(129),ID_EDIT_ENTITY_SHAPE);
  m_default.ModifyODMenu(loc.GetString(130),ID_EDIT_ENTITY_LIGHT);
  m_default.ModifyODMenu(loc.GetString(131),ID_EDIT_ENTITY_OBJECT);
  m_default.ModifyODMenu(loc.GetString(132),ID_EDIT_ENTITY_PARTICLE);
  m_default.ModifyODMenu(loc.GetString(133),ID_EDIT_ENTITY_SKELETTON);
  m_default.ModifyODMenu(loc.GetString(134),ID_VIEW_TOOLBAR);
  m_default.ModifyODMenu(loc.GetString(135),ID_VIEW_STATUS_BAR);
  m_default.ModifyODMenu(loc.GetString(136),ID_VIEW_EDITBAR);
  m_default.ModifyODMenu(loc.GetString(137),ID_VIEW_BUILDBAR);
  m_default.ModifyODMenu(loc.GetString(138),ID_VIEW_ANIMATIONBAR);
  m_default.ModifyODMenu(loc.GetString(139),ID_VIEW_DOCKBAR);
  m_default.ModifyODMenu(loc.GetString(141),ID_VIEW_CONFIG_2X2);
  m_default.ModifyODMenu(loc.GetString(142),ID_VIEW_CONFIG_1X2);
  m_default.ModifyODMenu(loc.GetString(143),ID_VIEW_CONFIG_2X1);
  m_default.ModifyODMenu(loc.GetString(144),ID_VIEW_CONFIG_1X3);
  m_default.ModifyODMenu(loc.GetString(145),ID_VIEW_CONFIG_3X1);
  m_default.ModifyODMenu(loc.GetString(146),ID_VIEW_CONFIG_FULLSCREEN);
  m_default.ModifyODMenu(loc.GetString(147),ID_VIEW_TYPE_TOP);
  m_default.ModifyODMenu(loc.GetString(148),ID_VIEW_TYPE_BOTTOM);
  m_default.ModifyODMenu(loc.GetString(149),ID_VIEW_TYPE_LEFT);
  m_default.ModifyODMenu(loc.GetString(150),ID_VIEW_TYPE_RIGHT);
  m_default.ModifyODMenu(loc.GetString(151),ID_VIEW_TYPE_FRONT);
  m_default.ModifyODMenu(loc.GetString(152),ID_VIEW_TYPE_BACK);
  m_default.ModifyODMenu(loc.GetString(153),ID_VIEW_TYPE_CAMERA);
  m_default.ModifyODMenu(loc.GetString(154),ID_VIEW_TYPE_PERSPECTIVE);
  m_default.ModifyODMenu(loc.GetString(156),ID_VIEW_ROTATE);
  m_default.ModifyODMenu(loc.GetString(157),ID_VIEW_MOVESPAN);
  m_default.ModifyODMenu(loc.GetString(158),ID_VIEW_ZOOMINOUT);
  m_default.ModifyODMenu(loc.GetString(159),ID_VIEW_REGIONFIT);
  m_default.ModifyODMenu(loc.GetString(161),ID_VIEW_EXTENDVIEW);
  m_default.ModifyODMenu(loc.GetString(162),ID_VIEW_EXTENDSVIEWS);
  m_default.ModifyODMenu(loc.GetString(164),ID_VIEW_RENDER_MAPPEDOUTLINED);
  m_default.ModifyODMenu(loc.GetString(165),ID_VIEW_RENDERMODE_MAPPED);
  m_default.ModifyODMenu(loc.GetString(166),ID__RENDER_FLATSHADED);
  m_default.ModifyODMenu(loc.GetString(167),ID_VIEW_RENDERMODE_WIRE);
  m_default.ModifyODMenu(loc.GetString(168),ID_SKYBOX_LOAD);
  m_default.ModifyODMenu(loc.GetString(169),ID_SKYBOX_NONE);
  m_default.ModifyODMenu(loc.GetString(170),ID_VIEW_GRID_VISIBLE);
  m_default.ModifyODMenu(loc.GetString(171),ID_VIEW_GRID_INCREASEGRID);
  m_default.ModifyODMenu(loc.GetString(172),ID_VIEW_GRID_DECREASEGRID);
  m_default.ModifyODMenu(loc.GetString(173),ID_VIEW_FLY);
  m_default.ModifyODMenu(loc.GetString(174),ID_BUILD_SNAP);
  m_default.ModifyODMenu(loc.GetString(175),ID_BUILD_CENTERED);
  m_default.ModifyODMenu(loc.GetString(176),ID_BUILD_CROSSING);
  m_default.ModifyODMenu(loc.GetString(177),ID_TOOLS_OPTION);
  m_default.ModifyODMenu(loc.GetString(178),ID_TOOLS_SKYBOXEDITOR);
  m_default.ModifyODMenu(loc.GetString(179),ID_WINDOW_NEW);
  m_default.ModifyODMenu(loc.GetString(180),ID_WINDOW_CASCADE);
  m_default.ModifyODMenu(loc.GetString(181),ID_WINDOW_TILE_HORZ);
  m_default.ModifyODMenu(loc.GetString(182),ID_WINDOW_ARRANGE);
  m_default.ModifyODMenu(loc.GetString(183),ID_ABOUT_KAPSUL);
  m_default.ModifyODMenu(loc.GetString(184),ID_HELP_TIPOFTHEDAY);
  m_default.ModifyODMenu(loc.GetString(312),ID_FILE_MRU_FILE1);
  m_default.ModifyODMenu(loc.GetString(314),ID_FILE_NEWPROJECT);
  m_default.ModifyODMenu(loc.GetString(315),ID_FILE_OPENPROJECT);
  
  BCMenu *tmpbc=m_default.GetSubBCMenu(loc.GetString(16,"Localization").GetBuffer(0));
  //tmpbc->InsertMenu(tmppos,1,40000,"English",1);//,int nIconNormal=-1);

  for (int i=0;i<loc.GetLanguageCount();i++)
	tmpbc->AppendODMenu(loc.GetLanguageName(i),MF_OWNERDRAW,40000+i);

  m_default.RemoveMenu(ID_TOOLS_LOCALIZATION_LOC1,0);
  /*
  BCMenu *tmpbc=m_default.GetSubBCMenu(loc.GetString(16,"Localization").GetBuffer(0));
  //tmpbc->InsertMenu(tmppos,1,40000,"English",1);//,int nIconNormal=-1);

  for (int i=0;i<loc.GetLanguageCount();i++)
	tmpbc->AppendODMenu(loc.GetLanguageName(i),MF_OWNERDRAW,40000+i);

  m_default.RemoveMenu(ID_TOOLS_LOCALIZATION_LOC1,0);
  */
  m_default.LoadToolbar(IDR_MAINFRAME);
  return(m_default.Detach());
}

//This handler ensure that the popup menu items are drawn correctly
void CMainFrame::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
  BOOL setflag=FALSE;
  if(lpMeasureItemStruct->CtlType==ODT_MENU){
    if(IsMenu((HMENU)lpMeasureItemStruct->itemID)){
      CMenu* cmenu=CMenu::FromHandle((HMENU)lpMeasureItemStruct->itemID);
      if(BCMenu::IsMenu(cmenu)){
        m_menu.MeasureItem(lpMeasureItemStruct);
        setflag=TRUE;
      }
    }
  }
  if(!setflag)CMDIFrameWnd::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}
 
//This handler ensures that keyboard shortcuts work
LRESULT CMainFrame::OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu) 
{
  LRESULT lresult;
  if(BCMenu::IsMenu(pMenu))
    lresult=BCMenu::FindKeyboardShortcut(nChar, nFlags, pMenu);
  else
    lresult=CMDIFrameWnd::OnMenuChar(nChar, nFlags, pMenu);
  return(lresult);
}
 
//This handler updates the menus from time to time
void CMainFrame::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu) 
{
  CMDIFrameWnd::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
  if(!bSysMenu){
    if(BCMenu::IsMenu(pPopupMenu))BCMenu::UpdateMenu(pPopupMenu);
  }
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

void CMainFrame::OnUpdateViewAnimationbar(CCmdUI* pCmdUI) 
{
	if(m_wndAnim.IsVisible())
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);

}

void CMainFrame::OnViewDockbar() 
{
	if(GetMenuState(GetMenu()->m_hMenu,ID_VIEW_DOCKBAR, MF_BYCOMMAND) & MF_CHECKED)
	{
		ShowControlBar(&m_wndDesksBrowser, FALSE, FALSE);
	}
	else
	{
		ShowControlBar(&m_wndDesksBrowser, TRUE, FALSE);
	}	
}

void CMainFrame::OnUpdateViewDockbar(CCmdUI* pCmdUI) 
{
	if(m_wndDesksBrowser.IsVisible())
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CMainFrame::OnViewEditbar() 
{
	if(GetMenuState(GetMenu( )->m_hMenu,ID_VIEW_EDITBAR, MF_BYCOMMAND) & MF_CHECKED)
	{
		ShowControlBar(&m_wndToolBarDesk, FALSE, FALSE);
	}
	else
	{
		ShowControlBar(&m_wndToolBarDesk, TRUE, FALSE);
	}	
}

void CMainFrame::OnUpdateViewEditbar(CCmdUI* pCmdUI) 
{
	if(m_wndToolBarDesk.IsVisible())
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
	
}

void CMainFrame::OnEditDoselect() 
{
	FunctionID=GCurSelect;
    if (GCurPlug!=NULL) GCurPlug->LoseFocus();
}

void CMainFrame::OnUpdateEditDoselect(CCmdUI* pCmdUI) 
{
	if ( (FunctionID==EDIT_SELECTFENCE)||
		(FunctionID==EDIT_SELECTQUAD)||(FunctionID==EDIT_SELECTCIRCLE) )
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void SetCreationPlugin(void);

void CMainFrame::OnCreateprim() 
{
	FunctionID=EDIT_PLUGINPRIMITIVE;
	SetCreationPlugin();
}


void CMainFrame::OnUpdateCreateprim(CCmdUI* pCmdUI) 
{
	if (FunctionID==EDIT_PLUGINPRIMITIVE)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);

	
}


void CMainFrame::OnEditChoosemode() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnUpdateEditSelectCircle(CCmdUI* pCmdUI) 
{
	if (FunctionID==EDIT_SELECTCIRCLE)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CMainFrame::OnUpdateEditSelectFence(CCmdUI* pCmdUI) 
{
	if (FunctionID==EDIT_SELECTFENCE)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CMainFrame::OnUpdateEditSelectQuad(CCmdUI* pCmdUI) 
{
	if (FunctionID==EDIT_SELECTQUAD)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}


void CMainFrame::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent==TIMER_ID)
	{
		KillTimer(TIMER_ID);
		if (KOption->GetEnableAutoSave())
		{
			DMPOutputString("Begining autosaves.\r\n");
			// autosaves
			for (CKViewEdit *meav=FirstCKViewEdit;meav!=NULL;meav=meav->Next)
			{
				CDeskDoc *tmpdoc=(CDeskDoc*)meav->GetDocument();
				//tmpdoc->

				char szTempName[MAX_PATH]; 

				GetTempFileName(KOption->GetAutoSaveDir(),tmpdoc->GetTitle(),0,szTempName);          
				CKFilePlugin *svgplug;
				if (tmpdoc->m_SavePlugin==NULL)
				{
					svgplug=GKPlugins->GetFilePluginByName("Kapsul Desk Text IO");
				}
				else
				{
					if (tmpdoc->m_SavePlugin->SupportWriting())
						svgplug=tmpdoc->m_SavePlugin;
					else
						svgplug=GKPlugins->GetFilePluginByName("Kapsul Desk Text IO");
				}

				DMPOutputString("Saving %s.\r\n",szTempName);
				svgplug->Write(tmpdoc->m_Scene,szTempName);
			}

			DMPOutputString("Autosaves finished.\r\n");
		}
		SetTimer(TIMER_ID,KOption->GetAutoSaveDelay()*60000,NULL);
	}
	
	CMDIFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::OnDropFiles(HDROP hDropInfo) 
{
	//MessageBox("Yop!");
	UINT nNumFilesDropped = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);

	//
	// Iterate through them and do some funky stuff
	//
	TCHAR szFilename[MAX_PATH + 1];
	for (UINT nFile = 0 ; nFile < nNumFilesDropped; nFile++)
	{
		//
		// Get the pathname
		//
		DragQueryFile(hDropInfo, nFile, szFilename, MAX_PATH + 1);
		
		struct _stat buf;
		int result = _tstat( szFilename, &buf );
		if( result == 0 )
		{
			//
			// Do we have a directory? (if we want dirs)
			//
			/*
			if ((buf.st_mode & _S_IFDIR) == _S_IFDIR)
			//
			// Do something with it...pretty useless, 
			// but only example
			//
			
			if (FindString(0,szFilename)==LB_ERR)
				AddString(szFilename);
				*/
			//MessageBox(szFilename);
			theApp.OpenCmdLine(szFilename);
		}
	}
	
	//
	// Windows allocates the memory for 
	// file information, so we must clean it up
	//
	DragFinish(hDropInfo);
	
	
//	CMainFrame::OnDropFiles(hDropInfo);
}

void CMainFrame::OnFileNewproject() 
{
	CNewProject newprj;

	if (newprj.DoModal()==IDOK)
	{
		MessageBox("Newprj");
	}

}

void CMainFrame::OnFileOpenproject() 
{
	CString fileName;
	BXFileDialog dlg(TRUE, TRUE, TRUE);

	LPTSTR pch = "Kapsul project file\0*.KProject\0\0";

	CString strTitle("Select project to open");

	dlg.m_ofn.lpstrFilter = pch;
	dlg.m_ofn.lpstrTitle = strTitle;
	dlg.m_ofn.lpstrFile = fileName.GetBuffer(_MAX_PATH);
	dlg.m_ofn.hwndOwner = AfxGetMainWnd()->m_hWnd; 

	dlg.SetAppearance(BXFileDialog::eAppearance::APPEARANCE_VSDOTNET);

	if (dlg.DoModal()==IDOK)
	{
		if ((!m_DesksBrowser->m_Project.m_ProjectName.IsEmpty())&&(m_DesksBrowser->m_Project.m_ProjectModified))
		{
			int rtmsg=MessageBox("Your project has been modified. Do you want to save it?","Save Project",MB_YESNOCANCEL);
			if (rtmsg==IDYES)
			{
				m_DesksBrowser->m_Project.SaveProject(m_DesksBrowser->m_Project.m_ProjectName);
				
			}
			else
			if (rtmsg==IDNO)
			{
				m_DesksBrowser->m_Project.LoadProject(fileName);
			}
		}
		else
			m_DesksBrowser->m_Project.LoadProject(fileName);
		
	}
}

void CMainFrame::OnFileCloseproject() 
{
	if ((!m_DesksBrowser->m_Project.m_ProjectName.IsEmpty())&&(m_DesksBrowser->m_Project.m_ProjectModified))
	{
		if (MessageBox("Your project has been modified. Do you want to save it?","Save Project",MB_YESNO)==IDYES)
		{
			m_DesksBrowser->m_Project.CloseProject();
		}
	}
	else
		m_DesksBrowser->m_Project.CloseProject();
}

void CMainFrame::OnFileCloseall() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnViewStatusBar() 
{
	if(GetMenuState(GetMenu( )->m_hMenu,ID_VIEW_STATUS_BAR, MF_BYCOMMAND) & MF_CHECKED)
	{
		ShowControlBar(&m_wndStatus, FALSE, FALSE);
	}
	else
	{
		ShowControlBar(&m_wndStatus, TRUE, FALSE);
	}	
}

void CMainFrame::OnUpdateViewStatusBar(CCmdUI* pCmdUI) 
{
	if(m_wndStatus.IsVisible())
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}


void CMainFrame::OnToolsRenderingOptions()
{
	CKSelectRenderer SelRenderer;

	SelRenderer.DoModal();
}

void CMainFrame::OnViewPrimitivebar() 
{
	if(GetMenuState(GetMenu( )->m_hMenu,ID_VIEW_PRIMITIVEBAR, MF_BYCOMMAND) & MF_CHECKED)
	{
		ShowControlBar(&m_Primitives, FALSE, FALSE);
	}
	else
	{
		ShowControlBar(&m_Primitives, TRUE, FALSE);
	}
}

void CMainFrame::OnUpdateViewPrimitivebar(CCmdUI* pCmdUI) 
{
	if(m_Primitives.IsVisible())
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);	
}

void CMainFrame::OnToolsMaterialeditor() 
{
	CKMaterialEditor MatEdit;
	MatEdit.DoModal();
}

void CMainFrame::OnToolsRenderer() 
{
	CKRenderIt RenderIt;
	RenderIt.DoModal();
}

void CMainFrame::OnToolsNetupdate() 
{
	if (MessageBox("Kapsul needs to shutdown the application before updating it.\nDo you want to save all your changes and exit?","Net Updating",MB_YESNO|MB_ICONQUESTION)==IDYES)
	{
		STARTUPINFO si;
		PROCESS_INFORMATION pi;

		ZeroMemory( &si, sizeof(si) );
		si.cb = sizeof(si);
		ZeroMemory( &pi, sizeof(pi) );

		// Start the child process. 
		if( !CreateProcess( NULL, // No module name (use command line). 
			"KUpNet.exe", // Command line. 
			NULL,             // Process handle not inheritable. 
			NULL,             // Thread handle not inheritable. 
			FALSE,            // Set handle inheritance to FALSE. 
			0,                // No creation flags. 
			NULL,             // Use parent's environment block. 
			NULL,             // Use parent's starting directory. 
			&si,              // Pointer to STARTUPINFO structure.
			&pi )             // Pointer to PROCESS_INFORMATION structure.
		) 
		{
			MessageBox("Unable to run net updater (KUpnet.exe).\nPlease, re-install Kapsul.","Net Updater Error.",MB_ICONERROR|MB_OK);
		}
		else
		{
			theApp.SaveAllModified();
			theApp.CloseAllDocuments(TRUE);
		
			PostQuitMessage(0);
		}
	}
}

