// ThumbnailDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include	<vector>
//#include "dib.h"
#include "ThumbnailDlg.h"
#include "headers.h"
#include "MapEdUtils.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define	THUMBNAIL_WIDTH		100
#define	THUMBNAIL_HEIGHT	75
extern "C" COption *KOption;
extern "C" Desk *dk;
extern "C" TypeEdit;


void SetSelectedNGon(int nbSide);
void Symetry(Vertex value);
void RotateBuf(Vertex Vect,double ng);

extern HINSTANCE g_Inst;

CThumbnailDlg::CThumbnailDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CThumbnailDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CThumbnailDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
//	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CThumbnailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CThumbnailDlg)
	DDX_Control(pDX, IDC_BUILDIT, m_BuildIt);
	DDX_Control(pDX, IDC_TRANSLATECOORDS, m_TranslateCoords);
	DDX_Control(pDX, IDC_SCALECOORDS, m_ScaleCoords);
	DDX_Control(pDX, IDC_ROTATECOORDS, m_RotateCoords);
	DDX_Control(pDX, IDC_MOVEVERTEX, m_MoveVertex);
	DDX_Control(pDX, IDC_MOVEEDGE, m_MoveEdge);
	DDX_Control(pDX, IDC_NGONLIST, m_ListNGon);
	DDX_Control(pDX, IDC_CLIPPER, m_Clipper);
	DDX_Control(pDX, IDC_HOLLOW, m_Hollow);
	DDX_Control(pDX, IDC_CSGSUB, m_CsgSub);
	DDX_Control(pDX, IDC_CSGMERGE, m_CsgMerge);
	DDX_Control(pDX, IDC_SZ, m_SZ);
	DDX_Control(pDX, IDC_SY, m_SY);
	DDX_Control(pDX, IDC_SX, m_SX);
	DDX_Control(pDX, IDC_RZ, m_RZ);
	DDX_Control(pDX, IDC_RY, m_RY);
	DDX_Control(pDX, IDC_RX, m_RX);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CThumbnailDlg, CDialog)
	//{{AFX_MSG_MAP(CThumbnailDlg)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_KEYDOWN()
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_WM_CHAR()
	ON_BN_CLICKED(IDC_HOLLOW, OnHollow)
	ON_BN_CLICKED(IDC_CSGMERGE, OnCsgmerge)
	ON_BN_CLICKED(IDC_CSGSUB, OnCsgsub)
	ON_BN_CLICKED(IDC_CLIPPER, OnClipper)
	ON_BN_CLICKED(IDC_RX, OnRx)
	ON_BN_CLICKED(IDC_SX, OnSx)
	ON_BN_CLICKED(IDC_RY, OnRy)
	ON_BN_CLICKED(IDC_SY, OnSy)
	ON_BN_CLICKED(IDC_RZ, OnRz)
	ON_BN_CLICKED(IDC_SZ, OnSz)
	ON_BN_CLICKED(IDC_MOVEVERTEX, OnMovevertex)
	ON_BN_CLICKED(IDC_MOVEEDGE, OnMoveedge)
	ON_BN_CLICKED(IDC_TRANSLATECOORDS, OnTranslatecoords)
	ON_BN_CLICKED(IDC_SCALECOORDS, OnScalecoords)
	ON_BN_CLICKED(IDC_ROTATECOORDS, OnRotatecoords)
	ON_WM_SYSCOMMAND()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUILDIT, OnBuildit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThumbnailDlg message handlers

BOOL CThumbnailDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

//	m_nSelectedItem = 0;
    
    m_SX.SetBitmap(LoadBitmap(g_Inst,MAKEINTRESOURCE(IDB_SX)));
    m_SY.SetBitmap(LoadBitmap(g_Inst,MAKEINTRESOURCE(IDB_SY)));
    m_SZ.SetBitmap(LoadBitmap(g_Inst,MAKEINTRESOURCE(IDB_SZ)));
    m_RX.SetBitmap(LoadBitmap(g_Inst,MAKEINTRESOURCE(IDB_RX)));
    m_RY.SetBitmap(LoadBitmap(g_Inst,MAKEINTRESOURCE(IDB_RY)));
    m_RZ.SetBitmap(LoadBitmap(g_Inst,MAKEINTRESOURCE(IDB_RZ)));


	m_Clipper.SetBitmap(LoadBitmap(g_Inst,MAKEINTRESOURCE(IDB_CLIPPER)));
	m_Hollow.SetBitmap(LoadBitmap(g_Inst,MAKEINTRESOURCE(IDB_HOLLOW)));
	m_CsgSub.SetBitmap(LoadBitmap(g_Inst,MAKEINTRESOURCE(IDB_CSGSUB)));
	m_CsgMerge.SetBitmap(LoadBitmap(g_Inst,MAKEINTRESOURCE(IDB_CSGMERGE)));

	m_MoveEdge.SetBitmap(LoadBitmap(g_Inst,MAKEINTRESOURCE(IDB_MOVEEDGE)));
	m_MoveVertex.SetBitmap(LoadBitmap(g_Inst,MAKEINTRESOURCE(IDB_MOVEVERTEX)));

	m_TranslateCoords.SetBitmap(LoadBitmap(g_Inst,MAKEINTRESOURCE(IDB_TRCOORDS)));
	m_RotateCoords.SetBitmap(LoadBitmap(g_Inst,MAKEINTRESOURCE(IDB_ROCOORDS)));
	m_ScaleCoords.SetBitmap(LoadBitmap(g_Inst,MAKEINTRESOURCE(IDB_SCCOORDS)));

	//m_PathList.SetDroppedWidth(150);
	m_BuildIt.SetCheck(1);
    

	return TRUE;  // return TRUE  unless you set the focus to a control
}


/*
void CThumbnailDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}
*/
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CThumbnailDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

void CThumbnailDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);

}

void CThumbnailDlg::OnOK( )
{

}

void CThumbnailDlg::OnCancel( )
{

}

void CThumbnailDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	switch(nChar)
    {
    case VK_ESCAPE:
        dk->cSel->UnSelectAll(false);
        break;
    case VK_LSHIFT:

        break;


    }
	
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CThumbnailDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

void CThumbnailDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnClose();
}

void CThumbnailDlg::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnChar(nChar, nRepCnt, nFlags);
}

void CThumbnailDlg::OnHollow() 
{
	SetPluginActive();
	HollowSelectedObject();
	DrawViews();
}

void CThumbnailDlg::OnCsgmerge() 
{
	SetPluginActive();
	AddSelectedObject();
	DrawViews();
}

void CThumbnailDlg::OnCsgsub() 
{
	SetPluginActive();
	SubSelectedObject();
	DrawViews();
}


void CThumbnailDlg::OnClipper() 
{
	if (m_Clipper.GetCheck()==1)
	{
		
		TypeEdit=11;
	}
	else
		UnselectEdit();
	SetPluginActive();		
}

void CThumbnailDlg::OnRx() 
{
	SetPluginActive();
	RotateBuf(Vertex(1,0,0),90);
	DrawViews();
}

void CThumbnailDlg::OnSx() 
{
	SetPluginActive();
	Symetry(Vertex(1,0,0));
	DrawViews();
}

void CThumbnailDlg::OnRy() 
{
	SetPluginActive();
	RotateBuf(Vertex(0,1,0),90);
	DrawViews();
}

void CThumbnailDlg::OnSy() 
{
	SetPluginActive();
	Symetry(Vertex(0,1,0));
	DrawViews();
}

void CThumbnailDlg::OnRz() 
{
	SetPluginActive();
	RotateBuf(Vertex(0,0,1),90);
	DrawViews();
}

void CThumbnailDlg::OnSz() 
{
	SetPluginActive();
	Symetry(Vertex(0,0,1));
	DrawViews();
}

void CThumbnailDlg::UnselectEdit()
{
	TypeEdit=0;
	
	m_Clipper.SetCheck(0);
	
	m_MoveVertex.SetCheck(0);
	m_MoveEdge.SetCheck(0);
	m_Clipper.SetCheck(0);

	m_TranslateCoords.SetCheck(0);
	m_ScaleCoords.SetCheck(0);
	m_RotateCoords.SetCheck(0);

}

void CThumbnailDlg::OnMovevertex() 
{
	UnselectEdit();
	if (m_MoveVertex.GetCheck()==1)
	{
		
		TypeEdit=12;
	}
	else
		UnselectEdit();
	SetPluginActive();
}

void CThumbnailDlg::OnMoveedge() 
{
	UnselectEdit();
	if (m_MoveEdge.GetCheck()==1)
	{
		
		TypeEdit=13;
	}
	else
		UnselectEdit();
	SetPluginActive();		
}

void CThumbnailDlg::OnTranslatecoords() 
{
	
	if (m_TranslateCoords.GetCheck()==1)
	{
		UnselectEdit();
		m_TranslateCoords.SetCheck(1);
		TypeEdit=20;
	}
	else
		UnselectEdit();
	SetPluginActive();
}

void CThumbnailDlg::OnScalecoords() 
{
	
	if (m_ScaleCoords.GetCheck()==1)
	{
		UnselectEdit();
		m_ScaleCoords.SetCheck(1);
		TypeEdit=21;
	}
	else
		UnselectEdit();	
	SetPluginActive();
}

void CThumbnailDlg::OnRotatecoords() 
{
	
	if (m_RotateCoords.GetCheck()==1)
	{
		UnselectEdit();
		m_RotateCoords.SetCheck(1);
		TypeEdit=22;
	}
	else
		UnselectEdit();	
	SetPluginActive();
}

void CThumbnailDlg::OnBuildit() 
{
	m_BuildIt.SetCheck(1);
	SetPluginActive();
}

void CThumbnailDlg::UnActiveIt(void)
{
	m_BuildIt.SetCheck(0);
}
