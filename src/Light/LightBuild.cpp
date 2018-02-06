// LightBuild.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "LightBuild.h"
#include "LightParam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLightBuild dialog


CLightBuild::CLightBuild(CWnd* pParent /*=NULL*/)
	: CDialog(CLightBuild::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLightBuild)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CLightBuild::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLightBuild)
	DDX_Control(pDX, IDC_CHECK1, m_BuildIt);
	DDX_Control(pDX, IDC_OMNI, m_Omni);
	DDX_Control(pDX, IDC_SPOT, m_Spot);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLightBuild, CDialog)
	//{{AFX_MSG_MAP(CLightBuild)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_OMNI, OnOmni)
	ON_BN_CLICKED(IDC_SPOT, OnSpot)
	ON_BN_CLICKED(IDC_NEON, OnNeon)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLightBuild message handlers
extern "C" int LightType;
extern CLightParam *m_ParamDiag;
//extern "C" CLight *CurrentLight;
BOOL CLightBuild::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_Omni.SetCheck(1);
	m_Spot.SetCheck(0);
	LightType=0;
	//m_ParamDiag->m_Spin1.SetRange(1.0f, 99999.0f);
	//CurrentLight=NULL;
	m_BuildIt.SetCheck(1);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLightBuild::OnCheck1() 
{
	m_Omni.SetCheck(1);
	m_Spot.SetCheck(0);
	LightType=0;
    SetPluginActive();
	//CurrentLight=NULL;
}

void CLightBuild::OnOmni() 
{
	//m_ParamDiag->m_Spin1.SetRange(1.0f, 99999.0f);
	LightType=0;
	//CurrentLight=NULL;
}

void CLightBuild::OnSpot() 
{
	//m_ParamDiag->m_Spin1.SetRange(1.0f, 180.0f);
	LightType=1;
	//CurrentLight=NULL;
}

void CLightBuild::OnOK() 
{
}

void CLightBuild::OnCancel() 
{
}

void CLightBuild::OnNeon() 
{
	LightType=2;
	//CurrentLight=NULL;
}
