// KStatusBar.cpp : implementation file
//

#include "stdafx.h"
#include "kapsulse.h"
#include "KStatusBar.h"
#include "kgui.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKStatusBar dialog

extern bool bCrossing;
extern bool bSnap;
extern bool bCentroid;
extern bool bAngleSnap;
extern CKOption *KOption;

CKStatusBar::CKStatusBar(CWnd* pParent /*=NULL*/)
	: CDialog(CKStatusBar::IDD, pParent)
{
	//{{AFX_DATA_INIT(CKStatusBar)
	//}}AFX_DATA_INIT
}


void CKStatusBar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKStatusBar)
	DDX_Control(pDX, IDC_Z, m_Z);
	DDX_Control(pDX, IDC_Y, m_Y);
	DDX_Control(pDX, IDC_X, m_X);
	DDX_Control(pDX, IDC_GRIDLIST, m_GridList);
	DDX_Control(pDX, IDC_ANGLELIST, m_AngleList);
	DDX_Control(pDX, IDC_SPINZ, m_SpinZ);
	DDX_Control(pDX, IDC_SPINY, m_SpinY);
	DDX_Control(pDX, IDC_SPINX, m_SpinX);
	DDX_Control(pDX, IDC_SCROLL, m_Scroll);
	DDX_Control(pDX, IDC_READ, m_Read);
	DDX_Control(pDX, IDC_OVER, m_Over);
	DDX_Control(pDX, IDC_NUM, m_Num);
	DDX_Control(pDX, IDC_LINEXY, m_LineXY);
	DDX_Control(pDX, IDC_INFOS, m_Infos);
	DDX_Control(pDX, IDC_GRID, m_Grid);
	DDX_Control(pDX, IDC_EDITZ, m_EditZ);
	DDX_Control(pDX, IDC_EDITY, m_EditY);
	DDX_Control(pDX, IDC_EDITX, m_EditX);
	DDX_Control(pDX, IDC_CROSSING, m_Crossing);
	DDX_Control(pDX, IDC_CONSOLE, m_Console);
	DDX_Control(pDX, IDC_CENTROID, m_Centroid);
	DDX_Control(pDX, IDC_CAPS, m_Caps);
	DDX_Control(pDX, IDC_ANGLE, m_Angle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CKStatusBar, CDialog)
	//{{AFX_MSG_MAP(CKStatusBar)
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_CROSSING, OnCrossing)
	ON_BN_CLICKED(IDC_CENTROID, OnCentroid)
	ON_BN_CLICKED(IDC_ANGLE, OnAngle)
	ON_BN_CLICKED(IDC_GRID, OnGrid)
	ON_CBN_SELCHANGE(IDC_GRIDLIST, OnSelchangeGridlist)
	ON_CBN_SELCHANGE(IDC_ANGLELIST, OnSelchangeAnglelist)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKStatusBar message handlers

BOOL CKStatusBar::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_Scene=NULL;

	// Edit zones

	m_SpinX.SetBuddy(&m_EditX);
	m_SpinX.SetRange(-10000000.0f, 10000000.0f);
	m_SpinX.SetPos(0);
	m_SpinX.SetDelta(0.1f);	

	m_SpinY.SetBuddy(&m_EditY);
	m_SpinY.SetRange(-10000000.0f, 10000000.0f);
	m_SpinY.SetPos(0);
	m_SpinY.SetDelta(0.1f);	

	m_SpinZ.SetBuddy(&m_EditZ);
	m_SpinZ.SetRange(-10000000.0f, 10000000.0f);
	m_SpinZ.SetPos(0);
	m_SpinZ.SetDelta(0.1f);	

	// Bmps

	m_Grid.SetBitmaps(::LoadBitmap(AfxGetResourceHandle(),MAKEINTRESOURCE(IDB_STATUSSNAP)),RGB(255,255,255));
	m_Centroid.SetBitmaps(::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_STATUSCENTROID)),RGB(192,192,192));
	m_Crossing.SetBitmaps(::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_STATUSCROSSING)),RGB(192,192,192));

	m_Angle.SetBitmaps(::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_STATUSANGLE)),RGB(255,255,255));
	//m_Scale.SetBitmaps(::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_STATUSSCALE)),RGB(192,192,192));


	m_X.SetBitmaps(::LoadBitmap(AfxGetResourceHandle(),MAKEINTRESOURCE(IDB_X)),RGB(255,255,255));
	m_Y.SetBitmaps(::LoadBitmap(AfxGetResourceHandle(),MAKEINTRESOURCE(IDB_Y)),RGB(255,255,255));
	m_Z.SetBitmaps(::LoadBitmap(AfxGetResourceHandle(),MAKEINTRESOURCE(IDB_Z)),RGB(255,255,255));


	m_Grid.SetCheck(bSnap);
	m_Centroid.SetCheck(bCentroid);
	m_Crossing.SetCheck(bCrossing);
	
	m_X.SetCheck(BST_CHECKED);
	m_Y.SetCheck(BST_CHECKED);

	UpdateCBOption();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CKStatusBar::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	if (::IsWindow(m_Read))
	{
		m_Read.MoveWindow(cx-33,2,33,21);
		m_Scroll.MoveWindow(cx-33,25,33,21);

		m_Over.MoveWindow(cx-68,2,33,21);
		m_Caps.MoveWindow(cx-68,25,33,21);
		m_Num.MoveWindow(cx-103,25,33,21);

		m_LineXY.MoveWindow(cx-172,2,102,21);

		m_Crossing.MoveWindow(cx-172,25,28,25);
		m_Centroid.MoveWindow(cx-138,25,28,25);

		m_SpinZ.MoveWindow(cx-190,2,15,21);
		m_EditZ.MoveWindow(cx-262,2,70,21);

		m_SpinY.MoveWindow(cx-280,2,15,21);
		m_EditY.MoveWindow(cx-352,2,70,21);

		m_SpinX.MoveWindow(cx-370,2,15,21);
		m_EditX.MoveWindow(cx-442,2,70,21);

		m_Grid.MoveWindow(cx-262,25,25,25);
		m_Angle.MoveWindow(cx-352,25,25,25);

		m_Z.MoveWindow(cx-352-28,25,25,25);
		m_Y.MoveWindow(cx-352-56,25,25,25);
		m_X.MoveWindow(cx-352-84,25,25,25);

		m_GridList.SetWindowPos(NULL,cx-235,25,60,25,SWP_NOSIZE);
		m_AngleList.SetWindowPos(NULL,cx-325,25,60,25,SWP_NOSIZE);

		m_Console.MoveWindow(0,2,cx-444,21);
		m_Infos.MoveWindow(0,25,cx-444,21);

	}
	
}

void CKStatusBar::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CKStatusBar::OnOk() 
{

}

void CKStatusBar::OnCancel() 
{
}

void CKStatusBar::OnCrossing() 
{
	bCrossing=(m_Crossing.GetCheck()==BST_CHECKED);
}

void CKStatusBar::OnCentroid() 
{
	bCentroid=(m_Centroid.GetCheck()==BST_CHECKED);
	DrawViews();
}

void CKStatusBar::OnAngle() 
{
	bAngleSnap=(m_Angle.GetCheck()==BST_CHECKED);
}

void CKStatusBar::OnGrid() 
{
	bSnap=(m_Grid.GetCheck()==BST_CHECKED);
}

void CKStatusBar::UpdateChecks()
{
	m_Crossing.SetCheck(bCrossing?BST_CHECKED:BST_UNCHECKED);
	m_Angle.SetCheck(bAngleSnap?BST_CHECKED:BST_UNCHECKED);
	m_Centroid.SetCheck(bCentroid?BST_CHECKED:BST_UNCHECKED);
	m_Grid.SetCheck(bSnap?BST_CHECKED:BST_UNCHECKED);
}

void CKStatusBar::UpdateCBOption()
{
	CString tmp;

	m_AngleList.ResetContent();
	m_GridList.ResetContent();
	for (int i=0;i<5;i++)
	{
		tmp.Format("%d",KOption->GridSpace(i));
		m_GridList.AddString(tmp);
		tmp.Format("%d",KOption->AngleSnap(i));
		m_AngleList.AddString(tmp);
	}
	
}
void CKStatusBar::SetCB(CKScene *pScene)
{
	m_Scene=pScene;
	m_GridList.SetCurSel(m_Scene->SnapValCounter);
	m_AngleList.SetCurSel(m_Scene->AngleValCounter);
}

void CKStatusBar::OnSelchangeGridlist() 
{
	if (m_Scene!=NULL)
	{
		m_Scene->ChangeGrid(m_GridList.GetCurSel());
		DrawViews();
	}
}

void CKStatusBar::OnSelchangeAnglelist() 
{
	if (m_Scene!=NULL)
	{
		m_Scene->ChangeAngle(m_AngleList.GetCurSel());	
		DrawViews();
	}
}
