#include "stdafx.h"

#include "KViewEdit.h"
#include "Mainfrm.h"
#include "BackWorldCap.h"


#define WM_UNSELECTALL WM_USER+9

//extern CKDrawScene *GDrawScene;
extern CKOption *KOption;
//extern HWND hWndMain;
extern CString WriteFilter,ReadFilter;
extern CKPluginManager *GKPlugins;
extern int CurrentCursor;

CKScenePlugin *tmpPlugin;

HWND StatusBar;

extern CMainFrame* mainf;
extern int FunctionID;

extern bool bCentered;
extern bool bCrossing;
extern bool bSnap;

extern int iEditMode;
bool MovingSel;

extern CKScene ClipBoard;
extern CKScenePlugin *GCurPlug;
extern int daButton;

extern CTVTestDlg	*m_DesksBrowser;
extern int m_TextureLayer;
extern CKLocalization loc;
int FunctionSwitch;
extern CKapsulApp theApp;

extern CKViewEdit *curpr;
extern int FrameCount;

BEGIN_MESSAGE_MAP(CKViewEdit,CView)
	//{{AFX_MSG_MAP(CView)
    ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
	ON_COMMAND(ID_VIEW_CONFIG_1X2, OnViewConfig1x2)
	ON_COMMAND(ID_VIEW_CONFIG_1X3, OnViewConfig1x3)
	ON_COMMAND(ID_VIEW_CONFIG_2X1, OnViewConfig2x1)
	ON_COMMAND(ID_VIEW_CONFIG_2X2, OnViewConfig2x2)
	ON_COMMAND(ID_VIEW_CONFIG_3X1, OnViewConfig3x1)
	ON_COMMAND(ID_VIEW_CONFIG_FULLSCREEN, OnViewConfigFullscreen)
	ON_COMMAND(ID_VIEW_EXTENDSVIEWS, OnViewExtendsviews)
	ON_COMMAND(ID_VIEW_EXTENDVIEW, OnViewExtendview)
	ON_COMMAND(ID_VIEW_TYPE_BACK, OnViewTypeBack)
	ON_COMMAND(ID_VIEW_TYPE_BOTTOM, OnViewTypeBottom)
	ON_COMMAND(ID_VIEW_TYPE_CAMERA, OnViewTypeCamera)
	ON_COMMAND(ID_VIEW_TYPE_FRONT, OnViewTypeFront)
	ON_COMMAND(ID_VIEW_TYPE_LEFT, OnViewTypeLeft)
	ON_COMMAND(ID_VIEW_TYPE_RIGHT, OnViewTypeRight)
	ON_COMMAND(ID_VIEW_TYPE_TOP, OnViewTypeTop)
	ON_COMMAND(ID_VIEW_PERSPECTIVE_UVMAPPING, OnViewMapping)
	ON_COMMAND(ID_VIEW_PERSPECTIVE_USERORTHO, OnViewOrthoUser)
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_KEYDOWN()
    ON_WM_KEYUP()
	ON_COMMAND(ID_VIEW_RENDERMODE_MAPPED, OnViewRendermodeMapped)
	ON_COMMAND(ID_VIEW_RENDER_MAPPEDOUTLINED, OnRenderModeMappedOutline)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
    ON_COMMAND(ID_EDIT_DELETE, OnEditDetete)
	ON_COMMAND(ID_VIEW_RENDERMODE_WIRE, OnViewRendermodeWire)
	ON_COMMAND(ID__RENDER_FLATSHADED,OnRenderModeFlatShaded)
	ON_COMMAND(ID_EDIT_SELECT_BYNAME, OnViewSelectByName)
	ON_COMMAND(ID_EDIT_SELECT_ALL, OnEditSelectAll)
	ON_WM_ACTIVATE()
	ON_WM_CHILDACTIVATE()
	ON_MESSAGE(WM_UNSELECTALL,OnWmUnSelectAll)
    ON_WM_KILLFOCUS()
	ON_COMMAND(ID_PROPERTIES, OnProperties)
	ON_COMMAND(ID_SKYBOX_LOAD,OnSkyBoxLoad)
	ON_COMMAND(ID_SKYBOX_NONE,OnSkyBoxNone)
	ON_COMMAND(ID_EDIT_MOVEROTATESCALE,OnMoveRotateScale)
	ON_COMMAND(ID_EDIT_MOVEROTATETAPERSQUIZ,OnMoveRotateTaperSquiz)
	ON_COMMAND(ID_EDIT_BEND,OnMoveRotateBend)
	ON_UPDATE_COMMAND_UI(ID_EDIT_MOVEROTATESCALE, OnUpdateMoveRotateScale)
	ON_UPDATE_COMMAND_UI(ID_EDIT_MOVEROTATETAPERSQUIZ, OnUpdateMoveRotateTaperSquiz)
	ON_UPDATE_COMMAND_UI(ID_EDIT_BEND, OnUpdateMoveRotateBend)
	ON_COMMAND(ID_VIEW_FLY,OnViewFly)
	ON_COMMAND(ID_VIEW_GRID_DECREASEGRID, OnViewGridDecreasegrid)
	ON_COMMAND(ID_VIEW_GRID_INCREASEGRID, OnViewGridIncreasegrid)
	ON_COMMAND(ID_VIEW_GRID_VISIBLE, OnViewGridVisible)
	ON_COMMAND(ID_TOOLS_BACKGROUNDWORLDCAP, OnBackWorldCap)
	ON_UPDATE_COMMAND_UI(ID_VIEW_GRID_VISIBLE, OnUpdateViewGridVisible)
	ON_COMMAND(ID_VIEW_TYPE_PERSPECTIVE, OnViewTypePerspective)
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI(ID_SKYBOX_LOAD, OnUpdateSkyboxLoad)
	ON_WM_MBUTTONDOWN()
//	ON_WM_MBUTTONDBLCLK()
ON_WM_MBUTTONUP()
ON_WM_MOUSEWHEEL()
ON_COMMAND(ID_VIEW_UNDOVIEWCHANGE, OnUndoViewChange)
ON_COMMAND(ID_VIEW_REDOVIEWCHANGE, OnRedoViewChange)
ON_COMMAND(ID_EDIT_HOOKCAMERATARGET, OnHookCameraTarget)

END_MESSAGE_MAP()

// ----------------------------------------------------------------------------

IMPLEMENT_DYNCREATE(CKViewEdit,CView)

CKViewEdit::CKViewEdit(HWND daHwnd)
{
	hWnd=daHwnd;

	CircleHui = new Vertex [100];
	temp=new char [256];
	tmp=new char [10];
	TmpName=new char [255];

//    FirstDesk=NULL;
    //NextDesk=NULL;

    // variables

	Snap=false;
	Center=false;
    Crossing=false;
    //gen=NULL;

    PropEnt=NULL;
	IsMoving=false;

	SnapVal.x=8;
	SnapVal.y=8;
	SnapVal.z=8;

	SelectedSel=EDIT_SELECTQUAD;
    
	m_Renderer=m_Scene->m_Renderer;
	dap=new CKPlan;

	FunctionSwitch=0;

	SetForegroundWindow();//theApp.GetMainWnd()->m_hWnd);

	

}

void AddCKViewEdit(CKViewEdit *daMain);
void DelCKViewEdit(CKViewEdit *daMain);
	CButton test; 

CKViewEdit::CKViewEdit()
{
	Next=NULL;
	Prev=NULL;
	CircleHui = new Vertex [100];
	temp=new char [256];
	tmp=new char [10];
	TmpName=new char [255];

//    FirstDesk=NULL;
    //NextDesk=NULL;

    // variables

	Snap=false;
	Center=false;
    Crossing=false;
    //gen=NULL;

    PropEnt=NULL;
	IsMoving=false;

	SnapVal.x=8;
	SnapVal.y=8;
	SnapVal.z=8;

	SelectedSel=EDIT_SELECTQUAD;
	
	
	dap=new CKPlan;

//	CTestGLDoc *tmpdoc;
/*
	tmpdoc=(CTestGLDoc*)GetDocument();
*/


	m_Scene=NULL;
	AddCKViewEdit(this);

}

CKViewEdit::~CKViewEdit()
{
	delete [] CircleHui;
	delete [] temp;
	delete [] tmp;
	delete [] TmpName;

	delete dap;

	DelCKViewEdit(this);
}

void CKViewEdit::DrawViews(void)
{
	Invalidate(TRUE);
}

void CKViewEdit::DrawView(int ViewNb)
{
	m_Renderer->m_Scene=m_Scene;

	m_Renderer->BeginRender();
	m_Renderer->RenderOne(ViewNb);
	m_Renderer->EndRender();
}



void CKViewEdit::Paint()
{
}


void CKViewEdit::KeyDown(int dawParam)
{
	switch (dawParam)
	{
		case VK_SHIFT:
			ButtonState|=ssShift;
			break;
		case VK_CONTROL:
			ButtonState|=ssCtrl;
			break;
	}
}

void CKViewEdit::KeyUp(int dawParam)
{
	switch (dawParam)
	{
		case VK_SHIFT:
			ButtonState&=!ssShift;
			break;
		case VK_CONTROL:
			ButtonState&=!ssCtrl;
			break;
	}
}

// ----------------------------------------------------------------------------


/////////////////////////////////////////////////////////////////////////////
// CTestGLView message handlers

void CKViewEdit::OnLButtonDown(UINT nFlags, CPoint point) 
{
	KMouseDown((int)nFlags,(int)point.x,(int)point.y);
}

void CKViewEdit::OnLButtonUp(UINT nFlags, CPoint point) 
{
	KMouseUp((int)nFlags,(int)point.x,(int)point.y);
}

void CKViewEdit::OnRButtonDown(UINT nFlags, CPoint point) 
{
	KMouseDown((int)nFlags,(int)point.x,(int)point.y);
}

void CKViewEdit::OnRButtonUp(UINT nFlags, CPoint point) 
{
	KMouseUp((int)nFlags,(int)point.x,(int)point.y);
}

void CKViewEdit::OnMouseMove(UINT nFlags, CPoint point) 
{
	KMouseMove((int)nFlags,(int)point.x,(int)point.y);
}

void CKViewEdit::OnMButtonDown(UINT nFlags, CPoint point)
{
	KMouseDown((int)nFlags|MK_MBUTTON,(int)point.x,(int)point.y);
}

void CKViewEdit::OnMButtonUp(UINT nFlags, CPoint point)
{
	KMouseUp((int)nFlags|MK_MBUTTON,(int)point.x,(int)point.y);
}

bool CKViewEdit::ToggleSnap(void)
{
	Snap=!Snap;
	return Snap;
}
bool CKViewEdit::ToggleWindow(void)
{
	Crossing=!Crossing;
	return Crossing;
}
bool CKViewEdit::ToggleCenter(void)
{
	Center=!Center;
	return Center;
}

int CKViewEdit::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1) return -1;
	CDeskDoc *tmpdoc;
// OpenGL rendering context creation
	//PIXELFORMATDESCRIPTOR pfd;
	if (m_Scene==NULL)
	{
		tmpdoc=(CDeskDoc *)GetDocument();
		m_Scene=tmpdoc->m_Scene;
	}

	m_Renderer=m_Scene->m_Renderer;

    m_Renderer->InitContext(m_hWnd);
	//test.Create("Test",WS_CHILD|WS_VISIBLE,CRect(10,10,30,30),this,15401);
	//MessageBox("Here");

	return 0;
}
void CKViewEdit::OnDraw(CDC* pDC)
{
	m_Renderer->m_Scene=m_Scene;
	m_Renderer->BeginRender();
	m_Renderer->Render();
	m_Renderer->EndRender();
}


void CKViewEdit::OnDestroy() 
{

	m_Renderer->DeleteContext();
// finally call the base function
	CView::OnDestroy();	
}

BOOL CKViewEdit::PreCreateWindow(CREATESTRUCT& cs) 
{
// these styles are requested by OpenGL
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

// these styles are meant for a use of this class in a MDI application
	cs.lpszClass = AfxRegisterWndClass(CS_OWNDC | CS_HREDRAW | CS_VREDRAW);

	return CView::PreCreateWindow(cs);
}


BOOL CKViewEdit::OnEraseBkgnd(CDC* pDC) 
{
// OGL has his own background erasing so tell Windows to skip
	return TRUE;
}


void CKViewEdit::OnShowWindow(BOOL bShow, UINT nStatus) 
{
//	CTestGLView::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	//Invalidate(TRUE);
	
}

void CKViewEdit::OnSize(UINT nType, int cx, int cy) 
{

	CDeskDoc *tmpdoc;

	if (m_Scene==NULL)
	{
		tmpdoc=(CDeskDoc *)GetDocument();
		m_Scene=tmpdoc->m_Scene;
	}

	m_Renderer->m_Scene=m_Scene;

	m_Scene->Height=cy;
	m_Scene->Width=cx;
	m_Scene->Left=0;
	m_Scene->Top=0;

	m_Scene->ComputeSize();

	m_Renderer->Resize(cx,cy);

	CView::OnSize(nType, cx, cy);

}
BOOL CKViewEdit::OnSetCursor(CWnd* /*pWnd*/, UINT /*nHitTest*/, UINT /*message*/) 
{
    /*
	ASSERT(m_hMouseCursor!=NULL);
	::SetCursor(m_hMouseCursor);
    */
	if (CurrentCursor==0)
		::SetCursor(::LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDC_STANDARD)));
	else
		::SetCursor((HCURSOR)CurrentCursor);
	/*
    switch(CurrentCursor)
    {
    case 1:
        ::SetCursor(::LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDC_SELSINGLE)));
        break;
    case 2:
        ::SetCursor(::LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDC_SELSINGLEFOUND)));
        break;
    default:
        ::SetCursor(::LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDC_STANDARD)));
        break;

    }
	*/
	return TRUE;
}
void CKViewEdit::OnViewConfig1x2() 
{
	m_Scene->FullScreen=false;
	m_Scene->daViewMode=VIEW_MODE1x2a;
	m_Scene->ComputeSize();
	Invalidate(TRUE);
	
}

void CKViewEdit::OnViewConfig1x3() 
{
	m_Scene->FullScreen=false;
	m_Scene->daViewMode=VIEW_MODE1x3a;
	m_Scene->ComputeSize();
	Invalidate(TRUE);
}

void CKViewEdit::OnViewConfig2x1() 
{
	m_Scene->FullScreen=false;
	m_Scene->daViewMode=VIEW_MODE1x2b;
	m_Scene->ComputeSize();
	Invalidate(TRUE);
}

void CKViewEdit::OnViewConfig2x2() 
{
	m_Scene->FullScreen=false;
	m_Scene->daViewMode=VIEW_MODE2x2;
	m_Scene->ComputeSize();
	Invalidate();
}

void CKViewEdit::OnViewConfig3x1() 
{
	m_Scene->FullScreen=false;
	m_Scene->daViewMode=VIEW_MODE1x3b;
	m_Scene->ComputeSize();
	Invalidate(TRUE);
}

void CKViewEdit::OnViewConfigFullscreen() 
{
	m_Scene->FullScreen=!m_Scene->FullScreen;
	Invalidate(TRUE);
}

void CKViewEdit::OnViewExtendsviews() 
{
	Vertex hui,huitemp,hui2,hui3,Min,Max;
	if (m_Scene->GetMinMax(PLUGIN_ALL,(Vertex*)&Min,(Vertex*)&Max))
	{


		for (int i=0;i<4;i++)
		{
			if ((m_Scene->ViewType[m_Scene->Active]!=VIEWTYPE_CAMERA)&&(m_Scene->ViewType[m_Scene->Active]!=VIEWTYPE_PERSPECTIVE))
			{
				m_Scene->ViewPos[i]=Min+((Max-Min)/2);
				//TmpEcran=(Max-Min);

				m_Renderer->Project((Vertex*)&Min,(Vertex*)&huitemp,i);
				m_Renderer->Project((Vertex*)&Max,(Vertex*)&hui,i);


				hui2=m_Renderer->GetIsoCoord(hui.x,huitemp.y,i);
				hui=m_Renderer->GetIsoCoord(hui.x,hui.y,i);


				huitemp=m_Renderer->GetIsoCoord(huitemp.x,huitemp.y,i);


				hui3.x=Pythagore3D(huitemp,hui2);
				// en y
				hui3.y=Pythagore3D(hui2,hui);


				if ((hui3.x/m_Scene->ViewEnd[i].x)>(hui3.y/m_Scene->ViewEnd[i].y))
				{
					hui3.x/=2;
					hui3.x*=1.1f;
					m_Scene->ViewSize[i]=hui3;
				}
				else
				{

					hui3.x=m_Scene->ViewEnd[i].x;
					hui3.x/=m_Scene->ViewEnd[i].y;
					hui3.x*=hui3.y;
					hui3.x/=2;
					hui3.x*=1.1f;
					m_Scene->ViewSize[i]=hui3;
				}
			}
		}
		Invalidate(TRUE);
	}
}

void CKViewEdit::OnViewExtendview() 
{
	Vertex hui,huitemp,hui2,hui3,Min,Max;

	if (m_Scene->GetMinMax(PLUGIN_ALL,(Vertex*)&Min,(Vertex*)&Max))
	{

		if ((m_Scene->ViewType[m_Scene->Active]!=VIEWTYPE_CAMERA)&&(m_Scene->ViewType[m_Scene->Active]!=VIEWTYPE_PERSPECTIVE))
		{
			m_Scene->ViewPos[m_Scene->Active]=Min+((Max-Min)/2);
			//TmpEcran=(Max-Min);

			m_Renderer->Project((Vertex*)&Min,(Vertex*)&huitemp,m_Scene->Active);
			m_Renderer->Project((Vertex*)&Max,(Vertex*)&hui,m_Scene->Active);


			hui2=m_Renderer->GetIsoCoord(hui.x,huitemp.y,m_Scene->Active);
			hui=m_Renderer->GetIsoCoord(hui.x,hui.y,m_Scene->Active);


			huitemp=m_Renderer->GetIsoCoord(huitemp.x,huitemp.y,m_Scene->Active);


			hui3.x=Pythagore3D(huitemp,hui2);
			// en y
			hui3.y=Pythagore3D(hui2,hui);


			if ((hui3.x/m_Scene->ViewEnd[m_Scene->Active].x)>(hui3.y/m_Scene->ViewEnd[m_Scene->Active].y))
			{
				hui3.x/=2;
				hui3.x*=1.1f;
				m_Scene->ViewSize[m_Scene->Active]=hui3;
			}
			else
			{

				hui3.x=m_Scene->ViewEnd[m_Scene->Active].x;
				hui3.x/=m_Scene->ViewEnd[m_Scene->Active].y;
				hui3.x*=hui3.y;
				hui3.x/=2;
				hui3.x*=1.1f;
				m_Scene->ViewSize[m_Scene->Active]=hui3;
			}
		}
		Invalidate(TRUE);
	}

}


void CKViewEdit::OnViewTypeCamera() 
{
	if (curpr==NULL)
	{
		CSelectCam selcam;
		selcam.m_Scene=m_Scene;
		selcam.DoModal();
		if (selcam.SelCam!=NULL)
		{
			m_Scene->ViewType[m_Scene->Active]=VIEWTYPE_CAMERA;
			m_Scene->cam[m_Scene->Active]=selcam.SelCam;
			Invalidate(TRUE);
		}
	}
}

void CKViewEdit::OnViewTypeFront() 
{
    m_Scene->ViewNg[m_Scene->Active].x=-90;
    m_Scene->ViewNg[m_Scene->Active].y=0;
    m_Scene->ViewNg[m_Scene->Active].z=0;
	m_Scene->ViewType[m_Scene->Active]=VIEWTYPE_ORTHO;
	m_Scene->cam[m_Scene->Active]=NULL;
    DrawViews();
}

void CKViewEdit::OnViewTypeLeft() 
{
    m_Scene->ViewNg[m_Scene->Active].x=270;
    m_Scene->ViewNg[m_Scene->Active].y=0;
    m_Scene->ViewNg[m_Scene->Active].z=270;
	m_Scene->ViewType[m_Scene->Active]=VIEWTYPE_ORTHO;
	m_Scene->cam[m_Scene->Active]=NULL;
    DrawViews();
}

void CKViewEdit::OnViewTypeRight() 
{
    m_Scene->ViewNg[m_Scene->Active].x=-90;
    m_Scene->ViewNg[m_Scene->Active].y=0;
    m_Scene->ViewNg[m_Scene->Active].z=90;
	m_Scene->ViewType[m_Scene->Active]=VIEWTYPE_ORTHO;
	m_Scene->cam[m_Scene->Active]=NULL;
    DrawViews();
}

void CKViewEdit::OnViewTypeTop() 
{
	m_Scene->ViewNg[m_Scene->Active].x=0;
    m_Scene->ViewNg[m_Scene->Active].y=0;
    m_Scene->ViewNg[m_Scene->Active].z=0;
	m_Scene->ViewType[m_Scene->Active]=VIEWTYPE_ORTHO;
	m_Scene->cam[m_Scene->Active]=NULL;
	DrawViews();
}

void CKViewEdit::OnViewTypeBack() 
{
	m_Scene->ViewNg[m_Scene->Active].x=90;
    m_Scene->ViewNg[m_Scene->Active].y=180;
    m_Scene->ViewNg[m_Scene->Active].z=0;
	m_Scene->ViewType[m_Scene->Active]=VIEWTYPE_ORTHO;
	m_Scene->cam[m_Scene->Active]=NULL;
	DrawViews();
}

void CKViewEdit::OnViewTypeBottom() 
{
	m_Scene->ViewNg[m_Scene->Active].x=0;
    m_Scene->ViewNg[m_Scene->Active].y=180;
    m_Scene->ViewNg[m_Scene->Active].z=180;
	m_Scene->ViewType[m_Scene->Active]=VIEWTYPE_ORTHO;
	m_Scene->cam[m_Scene->Active]=NULL;
	DrawViews();
}

void CKViewEdit::OnViewMapping() 
{

	m_Scene->ViewType[m_Scene->Active]=VIEWTYPE_UV;
	m_Scene->cam[m_Scene->Active]=NULL;
	DrawViews();
}

void CKViewEdit::OnViewOrthoUser() 
{
	m_Scene->ViewType[m_Scene->Active]=VIEWTYPE_ORTHO;
	m_Scene->cam[m_Scene->Active]=NULL;
	DrawViews();
}
void CKViewEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
    Vertex hui;
    
    switch(nChar)
    {
    case VK_UP:
	    if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_CAMERA)
	    {

		    if (m_Scene->cam[m_Scene->Active]!=NULL)
		    {
                m_Scene->cam[m_Scene->Active]->Run(10);
                m_Scene->cam[m_Scene->Active]->SetCamera();
                DrawViews();
		    }
	    }
        else
            if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_PERSPECTIVE)
            {
                m_Scene->Perspective[m_Scene->Active].Run(10);
                m_Scene->Perspective[m_Scene->Active].SetCamera();
                DrawViews();
            }
            else
            {
                hui=m_Renderer->GetIsoCoord(0,-10,m_Scene->Active)-m_Renderer->GetIsoCoord(0,0,m_Scene->Active);
	            if (bSnap) hui.Snap(SnapVal);
	            m_Scene->ViewPos[m_Scene->Active]-=hui;
                DrawViews();
            }
        break;
    case VK_DOWN:
	    if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_CAMERA)
	    {

		    if (m_Scene->cam[m_Scene->Active]!=NULL)
		    {
                m_Scene->cam[m_Scene->Active]->Run(-10);
                m_Scene->cam[m_Scene->Active]->SetCamera();
                DrawViews();
		    }
	    }
        else
            if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_PERSPECTIVE)
            {
                m_Scene->Perspective[m_Scene->Active].Run(-10);
                m_Scene->Perspective[m_Scene->Active].SetCamera();
                DrawViews();
            }
            else
            {
                hui=m_Renderer->GetIsoCoord(0,10,m_Scene->Active)-m_Renderer->GetIsoCoord(0,0,m_Scene->Active);
	            if (bSnap) hui.Snap(SnapVal);
	            m_Scene->ViewPos[m_Scene->Active]-=hui;
                DrawViews();
            }

        break;
    case VK_LEFT:
	    if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_CAMERA)
	    {
		    if (m_Scene->cam[m_Scene->Active]!=NULL)
		    {
                m_Scene->cam[m_Scene->Active]->Strafe(0.10f);
                DrawViews();
		    }
	    }
        else
            if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_PERSPECTIVE)
            {
				m_Scene->Perspective[m_Scene->Active].Strafe(0.10f);
                DrawViews();
            }
            else
            {
                hui=m_Renderer->GetIsoCoord(-10,0,m_Scene->Active)-m_Renderer->GetIsoCoord(0,0,m_Scene->Active);
	            if (bSnap) hui.Snap(SnapVal);
	            m_Scene->ViewPos[m_Scene->Active]-=hui;
                DrawViews();
            }

        break;
    case VK_RIGHT:
	    if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_CAMERA)
	    {
		    if (m_Scene->cam[m_Scene->Active]!=NULL)
		    {
                m_Scene->cam[m_Scene->Active]->Strafe(-0.10f);
                DrawViews();
		    }
	    }
        else
            if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_PERSPECTIVE)
            {
				m_Scene->Perspective[m_Scene->Active].Strafe(-0.10f);
                DrawViews();
            }
            else
            {
                hui=m_Renderer->GetIsoCoord(10,0,m_Scene->Active)-m_Renderer->GetIsoCoord(0,0,m_Scene->Active);
	            if (bSnap) hui.Snap(SnapVal);
	            m_Scene->ViewPos[m_Scene->Active]-=hui;
                DrawViews();
            }

        break;
    case VK_PRIOR:
	    if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_CAMERA)
	    {
		    if (m_Scene->cam[m_Scene->Active]!=NULL)
		    {
                m_Scene->cam[m_Scene->Active]->MoveUp(0.1f);
                DrawViews();
		    }
	    }
        else
            if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_PERSPECTIVE)
            {
                m_Scene->Perspective[m_Scene->Active].MoveUp(0.1f);
                DrawViews();
            }
        break;
    case VK_NEXT:
	    if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_CAMERA)
	    {
		    if (m_Scene->cam[m_Scene->Active]!=NULL)
		    {
                m_Scene->cam[m_Scene->Active]->MoveUp(-0.1f);
                DrawViews();
		    }
	    }
        else
            if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_PERSPECTIVE)
            {
                m_Scene->Perspective[m_Scene->Active].MoveUp(-0.1f);
                DrawViews();
            }
        break;

    case VK_HOME:
		if ((m_Scene->ViewType[m_Scene->Active]!=VIEWTYPE_PERSPECTIVE)&&(m_Scene->ViewType[m_Scene->Active]!=VIEWTYPE_CAMERA))
		{
			m_Scene->ViewSize[m_Scene->Active].x=m_Scene->ViewSize[m_Scene->Active].x*1.05f;
			m_Scene->ViewSize[m_Scene->Active].y=m_Scene->ViewSize[m_Scene->Active].y*1.05f;
			DrawViews();
		}
        break;
    case VK_END:
		if ((m_Scene->ViewType[m_Scene->Active]!=VIEWTYPE_PERSPECTIVE)&&(m_Scene->ViewType[m_Scene->Active]!=VIEWTYPE_CAMERA))
		{
			m_Scene->ViewSize[m_Scene->Active].x=m_Scene->ViewSize[m_Scene->Active].x*0.95f;
			m_Scene->ViewSize[m_Scene->Active].y=m_Scene->ViewSize[m_Scene->Active].y*0.95f;
			DrawViews();
		}
        break;
    case VK_ESCAPE:
		m_Scene->UnSelectAll(false);
		m_Scene->DeleteBufVert();
		m_Scene->SomeThingSel=false;
        DrawViews();
        break;
        
    }
    if (GCurPlug!=NULL) GCurPlug->KeyDown(nChar);

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CKViewEdit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
    if (GCurPlug!=NULL) GCurPlug->KeyUp(nChar);

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CKViewEdit::OnViewRendermodeMapped() 
{
//    Material *DaMat;

//	m_Scene->daSky=new CSkyBox();
/*
	DaMat=m_Scene->FirstMat;
	while (DaMat!=NULL)
	{

		DaMat->Init();
		DaMat=DaMat->Next;
	}
*/
	m_Scene->State[m_Scene->Active]=2;
    
    DrawViews();

}
void CKViewEdit::OnRenderModeFlatShaded()
{
	m_Scene->State[m_Scene->Active]=1;
    
    DrawViews();
}

void CKViewEdit::OnRenderModeMappedOutline()
{
	m_Scene->State[m_Scene->Active]=3;
    DrawViews();
}

void CKViewEdit::OnFileSaveAs() 
{

	CString fileName;
	BXFileDialog dlg(FALSE, TRUE, TRUE);


	LPTSTR pch = WriteFilter.GetBuffer(1);//szFilter.GetBuffer(0); // modify the buffer in place
	       
	// MFC delimits with '|' not '\0'
	while ((pch = _tcschr(pch, '|')) != NULL)
			*pch++ = '\0';

	CString strTitle("Save file");

	dlg.m_ofn.lpstrFilter = WriteFilter ;
	dlg.m_ofn.lpstrTitle = strTitle;
	dlg.m_ofn.lpstrFile = fileName.GetBuffer(_MAX_PATH);
	dlg.m_ofn.hwndOwner = AfxGetMainWnd()->m_hWnd; 
	//dlg.m_ofn.Flags|= OFN_ALLOWMULTISELECT ;

	dlg.SetAppearance(BXFileDialog::eAppearance::APPEARANCE_VSDOTNET);

	if (dlg.DoModal()==IDOK)
	{
		//theApp.OpenDocumentFile(m_FileDiag->m_ofn.lpstrFile);
		CString FileName;
		FileName=dlg.GetPathName();//m_FileDiag->m_ofn.lpstrFile;

		if (!ExtPresent(FileName,GKPlugins->WriteGen[(dlg.m_ofn.nFilterIndex-1)]->GetFileExtension()))
			FileName+=GKPlugins->WriteGen[(dlg.m_ofn.nFilterIndex-1)]->GetFileExtension();

        CDeskDoc *tmpdoc = (CDeskDoc *) GetDocument();

		tmpdoc->SetPathName(FileName);
        tmpdoc->SetModifiedFlag(FALSE);

        GKPlugins->WriteGen[(dlg.m_ofn.nFilterIndex-1)]->Write(m_Scene,FileName);
        tmpdoc->m_SavePlugin=GKPlugins->WriteGen[(dlg.m_ofn.nFilterIndex-1)];
        tmpdoc->SetTitle(FileName);
		tmpdoc->IsNamed=true;
		tmpdoc->SetModifiedFlag(false);
	}	
}

void CKViewEdit::OnFileSave() 
{
    
    CDeskDoc *tmpdoc = (CDeskDoc *) GetDocument();
	if (!tmpdoc->IsNamed)
	{
        OnFileSaveAs();
		tmpdoc->SetModifiedFlag(false);
    }
    else
    {
		if (!tmpdoc->m_SavePlugin->SupportWriting())
		{
			OnFileSaveAs();
			tmpdoc->SetModifiedFlag(false);
		}
		else
		{
			tmpdoc->SetModifiedFlag(FALSE);
			//tmpdoc->m_SavePlugin->>Process(KM_SAVEDESK,0,0);
			CString tmp=tmpdoc->GetPathName();
			if (!tmp.IsEmpty())
			{
				tmpdoc->m_SavePlugin->Write(m_Scene,tmp);
				tmpdoc->SetModifiedFlag(false);
			}
			else
			{
				MessageBox("File name not good. Try to Save As","File saving error.",MB_ICONERROR|MB_OK);
			}
		}
    }
}

void CKViewEdit::OnEditCopy() 
{
    ClipBoard.DeleteAll();
	m_Scene->CopySelectedTo(&ClipBoard);
}

void CKViewEdit::OnEditCut() 
{
	ClipBoard.DeleteAll();
	m_Scene->CopySelectedTo(&ClipBoard);
	if (GCurPlug!=NULL)
		GCurPlug->DeleteStuff();

	m_Scene->GetNbSelectedMeshs();
	m_Scene->SetSelectedToBeforeUndo("KAPSUL.DLL",UNDO_DELETE);

    m_Scene->DeleteSelected();
    DrawViews();
}

void CKViewEdit::OnEditPaste() 
{
    m_Scene->DeleteBufVert();
    m_Scene->UnSelectAll(false);


	ClipBoard.CopySelectedTo(m_Scene);

	m_Scene->GetNbSelectedMeshs();
	m_Scene->SetSelectedToAfterUndo("KAPSUL.DLL",UNDO_CREATE);


    DrawViews();
}

void CKViewEdit::OnEditDetete() 
{
	if (GCurPlug!=NULL)
		GCurPlug->DeleteStuff();

	m_Scene->GetNbSelectedMeshs();
	m_Scene->SetSelectedToBeforeUndo("KAPSUL.DLL",UNDO_DELETE);

    m_Scene->DeleteSelected();
    DrawViews();
}



void CKViewEdit::OnViewRendermodeWire() 
{
	m_Scene->State[m_Scene->Active]=0;
    DrawViews();
}

void CKViewEdit::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	CView::OnActivate(nState, pWndOther, bMinimized);
}

void CKViewEdit::OnChildActivate() 
{
	CView::OnChildActivate();

}

void CKViewEdit::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	CKViewEdit *cv=NULL;
	cv=(CKViewEdit *)pActivateView;

    if ((cv!=NULL)&&(bActivate))
    {
		CDeskDoc *tmpdoc = (CDeskDoc *) cv->GetDocument();

		if (!tmpdoc->IsKindOf( RUNTIME_CLASS( CView ) ) ) 
		{
			if (GCurPlug!=NULL)
				GCurPlug->SetScene(tmpdoc->m_Scene);

			UpdateGridInfo();

			UpdateHierarchie(tmpdoc->m_Scene);
            this->SetFocus();
			mainf->m_wndStatus.m_cDialog.SetCB(tmpdoc->m_Scene);
		}
	}
}
LRESULT CKViewEdit::OnWmUnSelectAll(WPARAM wParam, LPARAM lParam) 
{
	m_Scene->UnSelectAll(false);

    m_Scene->DeleteBufVert();
	m_Scene->SomeThingSel=false;
	DrawViews();

	return 0;
}


void CKViewEdit::OnKillFocus( CWnd* pNewWnd )
{
    //if (!pNewWnd->IsKindOf( RUNTIME_CLASS( CView ) ) )
        //this->SetFocus();
}


void CKViewEdit::OnProperties() 
{
	tmpPlugin=GKPlugins->GetScenePluginByName("Entity Builder");
	if ((tmpPlugin!=NULL)&&(PropEnt!=NULL))
	{
		/*
		if (tmpPlugin==(GenericLib*)0x1) //hack
		{
			CObjProps objprop;
			objprop.daObj=(CKMesh *)PropEnt;
			objprop.DoModal();
		}
		else
		*/
		{
			
			tmpPlugin->m_hWnd=m_DesksBrowser->m_cDialog.m_hWnd;
			
			FunctionID=EDIT_PLUGINCREATION;

			if (GCurPlug!=NULL) GCurPlug->Close();
			
			GCurPlug=tmpPlugin;
			m_Renderer->m_Plugin=tmpPlugin;
//			tmpPlugin->MainWin=m_hWnd;

			CMDIChildWnd *pChild = (CMDIChildWnd *) mainf->GetActiveFrame();

			m_DesksBrowser->m_cDialog.SetPlug(tmpPlugin->Open(tmpPlugin->m_hWnd),(CWnd *)&m_DesksBrowser->m_cDialog);


			if (pChild->GetActiveView()!=NULL)
			{
				CDeskDoc *tmpdoc = (CDeskDoc *) pChild->GetActiveView()->GetDocument();
				tmpPlugin->SetScene(tmpdoc->m_Scene);
				GCurPlug=tmpPlugin;
			}
			tmpPlugin->SetObject((void*)PropEnt,(int)PropType);
		}
	}
}



void CKViewEdit::OnViewSelectByName()
{
}

void CKViewEdit::OnEditSelectAll()
{
	m_Scene->SelectAll();
	DrawViews();
}

void CKViewEdit::OnSkyBoxLoad()
{
    CFileDialog m_FileDiag(TRUE,"*.skk",NULL,OFN_OVERWRITEPROMPT,
		"Skybox (*.skk)|*.skk||",this);

	if (m_FileDiag.DoModal()==IDOK)
	{
		CString das;
		das=m_FileDiag.GetPathName();
		m_Scene->m_skybox[m_Scene->Active].Load((unsigned char*)das.GetBuffer(10));

	}
}

void CKViewEdit::OnSkyBoxNone()
{
	m_Scene->m_skybox[m_Scene->Active].UnLoad();
	DrawViews();
}

void CKViewEdit::OnUpdateSkyboxLoad(CCmdUI *pCmdUI)
{
	if (m_Scene->ViewType[m_Scene->Active]!=VIEWTYPE_ORTHO)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);

}

void CKViewEdit::OnMoveRotateScale()
{
	FunctionSwitch=0;
}

void CKViewEdit::OnMoveRotateTaperSquiz()
{
	FunctionSwitch=1;
}

void CKViewEdit::OnMoveRotateBend()
{
	FunctionSwitch=2;
}
void CKViewEdit::OnUpdateMoveRotateScale(CCmdUI* pCmdUI) 
{
	if(FunctionSwitch==0)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CKViewEdit::OnUpdateMoveRotateTaperSquiz(CCmdUI* pCmdUI) 
{
	if(FunctionSwitch==1)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CKViewEdit::OnUpdateMoveRotateBend(CCmdUI* pCmdUI) 
{
	if(FunctionSwitch==2)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}



VOID CALLBACK TimerProc(HWND hwnd,UINT uMsg,UINT_PTR idEvent,DWORD dwTime )
{
	char buf[10];
	sprintf(buf,"FPS %d",FrameCount);
	mainf->SendMessage(WM_SETSTATUS,2,(long)buf);
	FrameCount=0;
}

void CKViewEdit::OnViewFly()
{
	
	//DWORD thId;
	//HANDLE thHand=::CreateThread(NULL,NULL,DrawThreadProc,this,NULL,&thId);

	//CKViewEdit *curpr;	
	if ( (m_Scene->ViewType[m_Scene->Active]!=VIEWTYPE_CAMERA)&&(m_Scene->ViewType[m_Scene->Active]!=VIEWTYPE_PERSPECTIVE) )
		return;

	CKCamera *daCam;
	if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_CAMERA)
		if (m_Scene->cam[m_Scene->Active]!=NULL)
			daCam=m_Scene->cam[m_Scene->Active];

	if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_PERSPECTIVE)
		daCam=&m_Scene->Perspective[m_Scene->Active];
					
	RECT rc;
	GetClientRect(&rc);
	
	POINT posMid;
	posMid.x=0;
	posMid.y=0;
	ClientToScreen(&posMid);
	
	posMid.x=posMid.x+m_Scene->ViewStart[m_Scene->Active].x+(m_Scene->ViewEnd[m_Scene->Active].x/2);
	posMid.y=posMid.y+(rc.bottom-(m_Scene->ViewStart[m_Scene->Active].y+(m_Scene->ViewEnd[m_Scene->Active].y/2)));

	flypos.x=posMid.x;
	flypos.y=posMid.y;

	SetCursorPos(flypos.x,flypos.y);

	if (curpr==NULL)
	{
		daCam->DrawHUD=true;
		curpr=this;//(CKViewEdit*)lpParameter;
		FrameCount=0;
		m_DInput.InitDI(mainf->m_hWnd,AfxGetInstanceHandle(),USEKEYBOARD|USEMOUSE);
		::SetTimer(NULL,1,1000,TimerProc);
	}
	else 
	{
		daCam->DrawHUD=false;
		::KillTimer(NULL,1);
		curpr=NULL;
		m_DInput.DIShutdown();
		DrawViews();
	}

/*
	//DrawViews();
	huitemp=m_Renderer->GetIsoCoord(10,10,m_Scene->Active);
	m_Scene->Perspective[m_Scene->Active].SetMousePos();
	m_Scene->Perspective[m_Scene->Active].BeginMove();

	huitemp=m_Renderer->GetIsoCoord(10,10,m_Scene->Active);
	m_Scene->Perspective[m_Scene->Active].angle_a=45;//oy-tmpop.y;
	m_Scene->Perspective[m_Scene->Active].SetCamera();
	//Invalidate(FALSE);
	Invalidate(TRUE);
*/
	//OnMButtonDown(0,CPoint(10,10));

	//IsMoving=false;

	//FunctionID=SvgFunctionID;
  /*
	for (int i=0;i<2000;i++)
	{
		DrawThreadProc(this);
		Sleep(10);
	}
	*/
}

void CKViewEdit::OnViewGridDecreasegrid() 
{
	m_Scene->ChangeGrid(m_Scene->SnapValCounter-1);
	mainf->m_wndStatus.m_cDialog.SetCB(m_Scene);
	UpdateGridInfo();
	DrawViews();
}

void CKViewEdit::OnViewGridIncreasegrid() 
{
	m_Scene->ChangeGrid(m_Scene->SnapValCounter+1);
	mainf->m_wndStatus.m_cDialog.SetCB(m_Scene);
	UpdateGridInfo();
	DrawViews();
}

void CKViewEdit::OnViewGridVisible() 
{
	m_Scene->m_GridVisible[m_Scene->Active]=!m_Scene->m_GridVisible[m_Scene->Active];
	DrawViews();
}

void CKViewEdit::OnUpdateViewGridVisible(CCmdUI* pCmdUI) 
{
	if(m_Scene->m_GridVisible[m_Scene->Active])
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CKViewEdit::UpdateGridInfo(void)
{
	char buf[64];
	sprintf(buf,"Grid %2.0f",m_Scene->SnapVal.x/*,m_Scene->SnapVal.y,m_Scene->SnapVal.z*/);
	mainf->SendMessage(WM_SETSTATUS,3,(long)buf);
}


void CKViewEdit::OnBackWorldCap(void)
{
	
	CBackWorldCap bwc;

	bwc.m_Scene=m_Scene;
	bwc.DoModal();
	
/*
	CKMesh *CurObj=m_Scene->AddMesh();
	CKGenericMesh mobj;

	mobj.VecX=Vertex(1,0,0);
	mobj.VecY=Vertex(0,1,0);
	mobj.VecZ=Vertex(0,0,1);

	mobj.CreateCube(CurObj,Vertex(50,50,50),128,128,128);

*/

}

void CKViewEdit::OnUndoViewChange(void)
{
	m_Scene->UndoViewChange();
}

void CKViewEdit::OnRedoViewChange(void)
{
	m_Scene->RedoViewChange();
}


void CKViewEdit::KMouseDown(int Button,int X, int Y)
{
}

void CKViewEdit::KMouseMove(int Button, int X, int Y)
{
}

void CKViewEdit::KMouseUp(int Button, int X, int Y)
{
}

BOOL CKViewEdit::KMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	return CView::OnMouseWheel(nFlags,zDelta,pt);
}

BOOL CKViewEdit::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	return KMouseWheel(nFlags,zDelta,pt);
}

void CKViewEdit::OnHookCameraTarget()
{
	if (m_Scene->SomeThingSel)
	{
		Vertex Cntr=((m_Scene->HookMaxSel+m_Scene->HookMinSel)/2.0f);
		if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_CAMERA)
		{
			m_Scene->cam[m_Scene->Active]->Dest=Cntr;
			m_Scene->cam[m_Scene->Active]->SetCamera();
		}
		else
		if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_PERSPECTIVE)
		{
			m_Scene->Perspective[m_Scene->Active].Dest=Cntr;
			m_Scene->Perspective[m_Scene->Active].SetCamera();
		}
		DrawViews();
	}
}

void CKViewEdit::OnViewTypePerspective() 
{
	m_Scene->ViewType[m_Scene->Active]=VIEWTYPE_PERSPECTIVE;
	Invalidate(TRUE);
}
