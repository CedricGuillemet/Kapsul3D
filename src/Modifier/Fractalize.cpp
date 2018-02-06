// Fractalize.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "Fractalize.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFractalize dialog


CFractalize::CFractalize(CWnd* pParent /*=NULL*/)
	: CDialog(CFractalize::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFractalize)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CFractalize::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFractalize)
	DDX_Control(pDX, IDC_SPIN1, m_Spin);
	DDX_Control(pDX, IDC_EDIT1, m_Edit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFractalize, CDialog)
	//{{AFX_MSG_MAP(CFractalize)
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_NEWSEED, OnNewseed)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFractalize message handlers

BOOL CFractalize::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_Spin.SetBuddy(&m_Edit);
	m_Spin.SetRange(-10000.0f, 100000.0f);
	m_Spin.SetPos(0);
	m_Spin.SetDelta(0.1f);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFractalize::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if (m_Plugin->LastAction!=ACTION_FRACTALIZE)
	{
		m_Plugin->LastAction=ACTION_FRACTALIZE;

		m_Plugin->ApplyModifs();

		m_Plugin->m_Scene->GetNbSelectedMeshs();
		m_Plugin->m_Scene->SetSelectedToBeforeUndo("Modifier.dll",UNDO_MODIFY);

		
	}
	m_Plugin->Fractalize();
	DrawViews();
	m_Plugin->m_Scene->SetSelectedToAfterUndoNoADD();

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CFractalize::OnNewseed() 
{
	m_Plugin->m_Seed=(unsigned)time( NULL );
	m_Plugin->Fractalize();
	DrawViews();	
}

void CFractalize::OnOK( )
{

}

void CFractalize::OnCancel( )
{

}