// Subdiv.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "Subdiv.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSubdiv dialog


CSubdiv::CSubdiv(CWnd* pParent /*=NULL*/)
	: CDialog(CSubdiv::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSubdiv)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSubdiv::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSubdiv)
	DDX_Control(pDX, IDC_SPIN1, m_Spin);
	DDX_Control(pDX, IDC_EDIT1, m_Edit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSubdiv, CDialog)
	//{{AFX_MSG_MAP(CSubdiv)
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSubdiv message handlers

void CSubdiv::OnOK( )
{
}

void CSubdiv::OnCancel( )
{
}

BOOL CSubdiv::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_Spin.SetBuddy(&m_Edit);
	m_Spin.SetRange(0.0f, 3.0f);
	m_Spin.SetPos(0);
	m_Spin.SetDelta(1.0f);	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSubdiv::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if (m_Plugin->LastAction!=ACTION_SUBDIVIDE)
	{
		/*
		m_Plugin->m_Scene->GetNbSelectedMeshs();
		m_Plugin->m_Scene->SetSelectedToBeforeUndo("Modifier.dll",UNDO_MODIFY);
		*/

		m_Plugin->PutSelectedToBuf();
		m_Plugin->DelSelectedMesh();
		m_Plugin->LastAction=ACTION_SUBDIVIDE;
		//CurrentUndo=m_Plugin->m_Scene->AddUndo(
	}

	m_Plugin->SubDivide(m_Spin.GetPos());

	DrawViews();

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}
