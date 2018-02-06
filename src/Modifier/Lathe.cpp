// Lathe.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "Lathe.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLathe dialog


CLathe::CLathe(CWnd* pParent /*=NULL*/)
	: CDialog(CLathe::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLathe)
	//}}AFX_DATA_INIT
}


void CLathe::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLathe)
	DDX_Control(pDX, IDC_SHAPENAME, m_ShapeName);
	DDX_Control(pDX, IDC_SPIN1, m_SpinEdit);
	DDX_Control(pDX, IDC_EDIT1, m_Edit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLathe, CDialog)
	//{{AFX_MSG_MAP(CLathe)
	ON_BN_CLICKED(IDC_SHAPE, OnShape)
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLathe message handlers

void CLathe::OnShape() 
{
	m_Plugin->LastAction=ACTION_LATHE;
	
}

BOOL CLathe::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_SpinEdit.SetBuddy(&m_Edit);
	m_SpinEdit.SetRange(3.0f, 10000.0f);
	m_SpinEdit.SetPos(3.0f);
	m_SpinEdit.SetDelta(1.0f);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLathe::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if (m_Plugin->LastAction!=ACTION_LATHE)
	{
		m_Plugin->ApplyModifs();
	}

	m_Plugin->CurLatheMesh->Lathing(m_Plugin->CurLatheShp,m_SpinEdit.GetPos(),m_UVParam.m_SpinU.GetPos(),m_UVParam.m_SpinV.GetPos());
	m_CurrentUndo->SetAfterEntry(0,PLUGIN_MESH,m_Plugin->CurLatheMesh);
	DrawViews();
	

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CLathe::OnOK( )
{

}

void CLathe::OnCancel( )
{

}