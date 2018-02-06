// TreeParam.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "TreeParam.h"
#include "Tree/tree/Tree.h"
#include "ModPrim3D.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTreeParam dialog
IMPLEMENT_DYNCREATE(CTreeParam, CDialog)

CTreeParam::CTreeParam(CWnd* pParent /*=NULL*/)
	: CDialog(CTreeParam::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTreeParam)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTreeParam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTreeParam)
	DDX_Control(pDX, IDC_TWIST, m_Twist);
	DDX_Control(pDX, IDC_THRESHOLD, m_Threshold);
	DDX_Control(pDX, IDC_LEAFSIZE, m_LeafSize);
	DDX_Control(pDX, IDC_BRANCHSIZE, m_BranchSize);
	DDX_Control(pDX, IDC_BRANCHNOISE, m_BranchNoise);
	DDX_Control(pDX, IDC_BRANCHBIAS, m_BranchBias);
	DDX_Control(pDX, IDC_BRANCH, m_Branch);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTreeParam, CDialog)
	//{{AFX_MSG_MAP(CTreeParam)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeParam message handlers

BOOL CTreeParam::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    m_LeafSize.SetRange(5,50);
    m_LeafSize.SetPos(2);

    m_BranchSize.SetRange(1,50);
    m_BranchSize.SetPos(10);

    m_Threshold.SetRange(2,50);
    m_Threshold.SetPos(40);

    m_Twist.SetRange(1,180);
    m_Twist.SetPos(90);

    m_Branch.SetRange(0,100);
    m_Branch.SetPos(70);

    m_BranchBias.SetRange(0,100);
    m_BranchBias.SetPos(75);

    m_BranchNoise.SetRange(0,100);
    m_BranchNoise.SetPos(50);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTreeParam::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
    float daval;

	

	if (m_Plugin->CurrentMesh!=NULL)
	{
		daval=m_LeafSize.GetPos();
		daval/=10;
		m_Plugin->mytree.setLeafSize(daval);
    
		daval=m_BranchSize.GetPos();
		daval/=100;
		m_Plugin->mytree.setBranchSize(daval);
    
		daval=m_Threshold.GetPos();
		daval/=100;
		m_Plugin->mytree.setThreshhold(daval);
    
		daval=m_BranchNoise.GetPos();
		daval/=100;
		m_Plugin->mytree.setBranchNoise(daval);
    
		daval=m_BranchBias.GetPos();
		daval/=100;
		m_Plugin->mytree.setBranchBias(daval);
    
		daval=m_Branch.GetPos();
		daval/=100;
		m_Plugin->mytree.setBranch(daval);
    
		daval=m_Twist.GetPos();
		m_Plugin->mytree.setTwist(daval);
    
		m_Plugin->mytree.build(m_Plugin->CurrentMesh,m_Plugin->LeafMesh,&m_Plugin->Remem);
		m_Plugin->CurrentMesh->UpdateMesh();
		m_Plugin->LeafMesh->UpdateMesh();

		DrawViews();
	}
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CTreeParam::OnOK( )
{

}

void CTreeParam::OnCancel( )
{

}