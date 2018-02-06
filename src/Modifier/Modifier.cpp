// Modifier.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModifier dialog

extern HINSTANCE g_Inst;

CModifier::CModifier(CWnd* pParent /*=NULL*/)
	: CDialog(CModifier::IDD, pParent)
{
	//{{AFX_DATA_INIT(CModifier)
	//}}AFX_DATA_INIT
}


void CModifier::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModifier)
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


BEGIN_MESSAGE_MAP(CModifier, CDialog)
	//{{AFX_MSG_MAP(CModifier)
	ON_BN_CLICKED(IDC_FLIPNORMALS, OnFlipnormals)
	ON_BN_CLICKED(IDC_UNIFYNORMALS, OnUnifynormals)
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
	ON_BN_CLICKED(IDC_SPHERIZE, OnSpherize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModifier message handlers

void CModifier::OnFlipnormals() 
{
    m_Plugin->FlipNormalFaces();	
}


void CModifier::OnUnifynormals() 
{
	m_Plugin->UnifyNormalFaces();
}

BOOL CModifier::OnInitDialog() 
{
	CDialog::OnInitDialog();

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
	/*
	m_Slid1.SetRange(0,100);
	m_Slid1.SetPos(0);
	*/
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CModifier::OnOK( )
{

}

void CModifier::OnCancel( )
{

}


void CModifier::OnHollow() 
{
	//SetPluginActive();
	m_Plugin->HollowSelectedObject();
	m_Plugin->m_Scene->UpdateSmthSel();
	DrawViews();
}

void CModifier::OnCsgmerge() 
{
	//SetPluginActive();
	m_Plugin->AddSelectedObject();
	m_Plugin->m_Scene->UpdateSmthSel();
	DrawViews();
}

void CModifier::OnCsgsub() 
{
	//SetPluginActive();
	m_Plugin->SubSelectedObject();
	m_Plugin->m_Scene->UpdateSmthSel();
	DrawViews();
}


void CModifier::OnClipper() 
{
	m_Clipper.SetCheck(1);
	if (m_Clipper.GetCheck()==1)
	{
		m_Plugin->TypeEdit=11;
		SetPluginActive();
	}
	else
	{
		m_Plugin->TypeEdit=0;
	}
}

void CModifier::OnRx() 
{
	//SetPluginActive();
	m_Plugin->RotateBuf(Vertex(1,0,0),90);
	DrawViews();
}

void CModifier::OnSx() 
{
	//SetPluginActive();
	m_Plugin->Symetry(Vertex(1,0,0));
	DrawViews();
}

void CModifier::OnRy() 
{
	//SetPluginActive();
	m_Plugin->RotateBuf(Vertex(0,1,0),90);
	DrawViews();
}

void CModifier::OnSy() 
{
	//SetPluginActive();
	m_Plugin->Symetry(Vertex(0,1,0));
	DrawViews();
}

void CModifier::OnRz() 
{
	//SetPluginActive();
	m_Plugin->RotateBuf(Vertex(0,0,1),90);
	DrawViews();
}

void CModifier::OnSz() 
{
	//SetPluginActive();
	m_Plugin->Symetry(Vertex(0,0,1));
	DrawViews();
}

void CModifier::OnSpherize()
{
	m_Plugin->m_Scene->UpdateBuf();
}
/*
void CModifier::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	float daval=((float)m_Slid1.GetPos()/100.0f);
	m_Plugin->Spherize(daval);
	DrawViews();
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CModifier::OnButton1() 
{
	// TODO: Add your control notification handler code here
	
	

}
*/
