// ParamDiag.cpp : implementation file
//

#include "stdafx.h"
//#include "aglmfc.h"
#include "resource.h"
#include "ParamDiag.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CParamDiag dialog

extern "C" CKCamera *CurrentCam;
CParamDiag::CParamDiag(CWnd* pParent /*=NULL*/)
	: CDialog(CParamDiag::IDD, pParent)
{
	//{{AFX_DATA_INIT(CParamDiag)
	//}}AFX_DATA_INIT
}


void CParamDiag::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CParamDiag)
	DDX_Control(pDX, IDC_SPINY, m_SpinY);
	DDX_Control(pDX, IDC_SPINX, m_SpinX);
	DDX_Control(pDX, IDC_SPINFOV, m_SpinFov);
	DDX_Control(pDX, IDC_EDITY, m_EditY);
	DDX_Control(pDX, IDC_EDITX, m_EditX);
	DDX_Control(pDX, IDC_EDITFOV, m_EditFov);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CParamDiag, CDialog)
	//{{AFX_MSG_MAP(CParamDiag)
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParamDiag message handlers

BOOL CParamDiag::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_SpinX.SetBuddy(&m_EditX);
	m_SpinX.SetRange(320.0f, 1920.0f);
	m_SpinX.SetPos(1024);
	m_SpinX.SetDelta(1.0f);	

	m_SpinY.SetBuddy(&m_EditY);
	m_SpinY.SetRange(200.0f, 1536.0f);
	m_SpinY.SetPos(768);
	m_SpinY.SetDelta(1.0f);	

	m_SpinFov.SetBuddy(&m_EditFov);
	m_SpinFov.SetRange(15.0f, 270.0f);
	m_SpinFov.SetPos(60);
	m_SpinFov.SetDelta(1.0f);	


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CParamDiag::OnOK( )
{

}

void CParamDiag::OnCancel( )
{

}

void CParamDiag::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if (CurrentCam!=NULL)
    {
	    CurrentCam->ResoX=m_SpinX.GetPos();
	    CurrentCam->ResoY=m_SpinY.GetPos();
	    CurrentCam->Fov=m_SpinFov.GetPos();
        DrawViews();
    }

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}
