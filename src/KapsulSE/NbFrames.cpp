// NbFrames.cpp : implementation file
//

#include "stdafx.h"

//#include "memmgr/mmgr.h"

#include "KapsulSE.h"
#include "NbFrames.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNbFrames dialog


CNbFrames::CNbFrames(CWnd* pParent /*=NULL*/)
	: CDialog(CNbFrames::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNbFrames)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CNbFrames::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNbFrames)
	DDX_Control(pDX, IDC_SPIN1, m_Spin);
	DDX_Control(pDX, IDC_EDIT1, m_NbFrames);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNbFrames, CDialog)
	//{{AFX_MSG_MAP(CNbFrames)
	ON_BN_CLICKED(IDC_RESCALE, OnRescale)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNbFrames message handlers

BOOL CNbFrames::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_Spin.SetBuddy(&m_NbFrames);
	m_Spin.SetRange(0, 9999.0f);
	m_Spin.SetPos(nbFrames);
//	m_Spin.SetDelta(1);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNbFrames::OnRescale() 
{
	Rescal=true;
	
}

void CNbFrames::OnRadio2() 
{
	Rescal=false;
}

void CNbFrames::OnDestroy() 
{
	CDialog::OnDestroy();
	
	nbFrames=m_Spin.GetPos();
	
}
