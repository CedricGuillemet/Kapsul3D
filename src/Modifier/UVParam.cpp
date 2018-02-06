// UVParam.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "UVParam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUVParam dialog


CUVParam::CUVParam(CWnd* pParent /*=NULL*/)
	: CDialog(CUVParam::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUVParam)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CUVParam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUVParam)
	DDX_Control(pDX, IDC_SPIN2, m_SpinV);
	DDX_Control(pDX, IDC_SPIN1, m_SpinU);
	DDX_Control(pDX, IDC_EDIT3, m_EditV);
	DDX_Control(pDX, IDC_EDIT1, m_EditU);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUVParam, CDialog)
	//{{AFX_MSG_MAP(CUVParam)
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUVParam message handlers

BOOL CUVParam::OnInitDialog() 
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

void CUVParam::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if (m_Plugin->LastAction==ACTION_LATHE)
	{
		if (m_Plugin->CurLatheMesh!=NULL)
		{
			m_Plugin->CurLatheMesh->Lathing(m_Plugin->CurLatheShp,m_Lathe.m_SpinEdit.GetPos(),m_SpinU.GetPos(),m_SpinV.GetPos());
		}
	}
	if ((m_Plugin->SPath!=NULL)&&(m_Plugin->SShape!=NULL))
	{
		m_Plugin->GenerateObject();
		DrawViews();
	}
	
	
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CUVParam::OnOK( )
{

}

void CUVParam::OnCancel( )
{

}