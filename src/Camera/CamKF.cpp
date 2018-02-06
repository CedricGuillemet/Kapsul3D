// CamKF.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "CamKF.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCamKF dialog


CCamKF::CCamKF(CWnd* pParent /*=NULL*/)
	: CDialog(CCamKF::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCamKF)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCamKF::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCamKF)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCamKF, CDialog)
	//{{AFX_MSG_MAP(CCamKF)
	ON_BN_CLICKED(IDC_DESTROYLINK, OnDestroylink)
	ON_BN_CLICKED(IDC_LINKTOCAMDST, OnLinktocamdst)
	ON_BN_CLICKED(IDC_LINKTOCAMSRC, OnLinktocamsrc)
	ON_BN_CLICKED(IDC_LINKTOSHAPE, OnLinktoshape)
	ON_BN_CLICKED(IDC_MOVEPT, OnMovept)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCamKF message handlers

void CCamKF::OnDestroylink() 
{
	// TODO: Add your control notification handler code here
	
}

void CCamKF::OnLinktocamdst() 
{
	// TODO: Add your control notification handler code here
	
}

void CCamKF::OnLinktocamsrc() 
{
	// TODO: Add your control notification handler code here
	
}

void CCamKF::OnLinktoshape() 
{
	// TODO: Add your control notification handler code here
	
}

void CCamKF::OnMovept() 
{
	// TODO: Add your control notification handler code here
	
}
