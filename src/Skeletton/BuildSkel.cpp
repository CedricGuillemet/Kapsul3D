// BuildSkel.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "BuildSkel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBuildSkel dialog


CBuildSkel::CBuildSkel(CWnd* pParent /*=NULL*/)
	: CDialog(CBuildSkel::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBuildSkel)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CBuildSkel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBuildSkel)
	DDX_Control(pDX, IDC_MOVEDOT, m_MoveDot);
	DDX_Control(pDX, IDC_DELBONE, m_DelBone);
	DDX_Control(pDX, IDC_ADDROOT, m_AddRoot);
	DDX_Control(pDX, IDC_ADDBONE, m_AddBone);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBuildSkel, CDialog)
	//{{AFX_MSG_MAP(CBuildSkel)
	ON_BN_CLICKED(IDC_ADDBONE, OnAddbone)
	ON_BN_CLICKED(IDC_ADDROOT, OnAddroot)
	ON_BN_CLICKED(IDC_DELBONE, OnDelbone)
	ON_BN_CLICKED(IDC_MOVEDOT, OnMovedot)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBuildSkel message handlers

void CBuildSkel::OnAddbone() 
{
	m_MoveDot.SetCheck(0);
    m_DelBone.SetCheck(0);
    m_AddRoot.SetCheck(0);
    m_AddBone.SetCheck(1);
    m_Plugin->TypeEdit=2;
    SetPluginActive();
}

void CBuildSkel::OnAddroot() 
{
	m_MoveDot.SetCheck(0);
    m_DelBone.SetCheck(0);
    m_AddRoot.SetCheck(1);
    m_AddBone.SetCheck(0);
    m_Plugin->TypeEdit=1;
    SetPluginActive();
}

void CBuildSkel::OnDelbone() 
{
	m_MoveDot.SetCheck(0);
    m_DelBone.SetCheck(1);
    m_AddRoot.SetCheck(0);
    m_AddBone.SetCheck(0);
    m_Plugin->TypeEdit=9;
    SetPluginActive();
}

void CBuildSkel::OnMovedot() 
{
	m_MoveDot.SetCheck(1);
    m_DelBone.SetCheck(0);
    m_AddRoot.SetCheck(0);
    m_AddBone.SetCheck(0);
    m_Plugin->TypeEdit=6; //prev 7
    SetPluginActive();
}

void CBuildSkel::UnSetPlugin(void)
{
	m_MoveDot.SetCheck(0);
    m_DelBone.SetCheck(0);
    m_AddRoot.SetCheck(0);
    m_AddBone.SetCheck(0);
    m_Plugin->TypeEdit=0;
    SetPluginActive();
}
