// Parameters.cpp : implementation file
//

#include "stdafx.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CParameters dialog

CParameters::CParameters(CWnd* pParent /*=NULL*/)
	: CDialog(CParameters::IDD, pParent)
{
	//{{AFX_DATA_INIT(CParameters)
	//}}AFX_DATA_INIT
}


void CParameters::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CParameters)
	DDX_Control(pDX, IDC_SPIN1, m_SpinSteps);
	DDX_Control(pDX, IDC_EDIT1, m_EditSteps);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CParameters, CDialog)
	//{{AFX_MSG_MAP(CParameters)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParameters message handlers

void CParameters::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CParameters::OnOK( )
{

}

void CParameters::OnCancel( )
{

}

void CParameters::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
switch (m_Plugin->TypeEdit)
	{
		case 5:
			m_Plugin->nbSegStar=m_SpinSteps.GetPos();
			m_Plugin->nbSegStar&=0xfffffffe;
			m_SpinSteps.SetPos(m_Plugin->nbSegStar);
			break;
		case 4:
			m_Plugin->nbSegArc=m_SpinSteps.GetPos();
			break;
		case 2:
			m_Plugin->nbSegNGon=m_SpinSteps.GetPos();
			break;
    }
	m_Plugin->UpdateShape();

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

BOOL CParameters::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_SpinSteps.SetBuddy(&m_EditSteps);
	m_SpinSteps.SetRange(3.0f, 100.0f);
	m_SpinSteps.SetPos(3);
	m_SpinSteps.SetDelta(1.0f);	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CParameters::SetParam(float Min,float Max,float Steps,float Pos)
{
	m_SpinSteps.SetRange(Min,Max);
	m_SpinSteps.SetPos(Pos);
	m_SpinSteps.SetDelta(Steps);	
}
