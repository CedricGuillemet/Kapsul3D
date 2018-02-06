// Mapping.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "Mapping.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapping dialog

IMPLEMENT_DYNCREATE(CMapping, CDialog)

CMapping::CMapping(CWnd* pParent /*=NULL*/)
	: CDialog(CMapping::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMapping)
	//}}AFX_DATA_INIT
}


void CMapping::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMapping)
	DDX_Control(pDX, IDC_SPIN2, m_SpinV);
	DDX_Control(pDX, IDC_SPIN1, m_SpinU);
	DDX_Control(pDX, IDC_EDIT3, m_EditV);
	DDX_Control(pDX, IDC_EDIT1, m_EditU);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMapping, CDialog)
	//{{AFX_MSG_MAP(CMapping)
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapping message handlers

BOOL CMapping::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_SpinU.SetBuddy(&m_EditU);
	m_SpinU.SetRange(0.0f, 10000.0f);
	m_SpinU.SetPos(1.0f);
	m_SpinU.SetDelta(0.1f);

	m_SpinV.SetBuddy(&m_EditV);
	m_SpinV.SetRange(0.0f, 10000.0f);
	m_SpinV.SetPos(1.0f);
	m_SpinV.SetDelta(0.1f);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMapping::OnOK( )
{

}

void CMapping::OnCancel( )
{

}

void CMapping::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{

	m_Plugin->m_Gen.Valu=m_SpinU.GetPos();
	m_Plugin->m_Gen.Valv=m_SpinV.GetPos();

	m_Plugin->UpdateCurrentPrimitive();

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}
