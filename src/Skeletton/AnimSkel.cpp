// AnimSkel.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "AnimSkel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnimSkel dialog


CAnimSkel::CAnimSkel(CWnd* pParent /*=NULL*/)
	: CDialog(CAnimSkel::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAnimSkel)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAnimSkel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAnimSkel)
	DDX_Control(pDX, IDC_LISTANIMS, m_ListAnims);
	DDX_Control(pDX, IDC_MOVEBONE, m_MoveBone);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAnimSkel, CDialog)
	//{{AFX_MSG_MAP(CAnimSkel)
	ON_BN_CLICKED(IDC_ADDANIM, OnAddanim)
	ON_BN_CLICKED(IDC_RENANIM, OnRenanim)
	ON_BN_CLICKED(IDC_DELANIM, OnDelanim)
	ON_BN_CLICKED(IDC_MOVEBONE, OnMovebone)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnimSkel message handlers

void CAnimSkel::OnAddanim() 
{
	// TODO: Add your control notification handler code here
	
}

void CAnimSkel::OnRenanim() 
{
	// TODO: Add your control notification handler code here
	
}

void CAnimSkel::OnDelanim() 
{
	// TODO: Add your control notification handler code here
	
}

void CAnimSkel::OnMovebone() 
{
	// TODO: Add your control notification handler code here
	
}
