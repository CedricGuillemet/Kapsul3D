// Spherize.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "Spherize.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpherize dialog


CSpherize::CSpherize(CWnd* pParent /*=NULL*/)
	: CDialog(CSpherize::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSpherize)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSpherize::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpherize)
	DDX_Control(pDX, IDC_SPIN1, m_SpinEdit);
	DDX_Control(pDX, IDC_EDIT1, m_Edit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSpherize, CDialog)
	//{{AFX_MSG_MAP(CSpherize)
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpherize message handlers

BOOL CSpherize::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_SpinEdit.SetBuddy(&m_Edit);
	m_SpinEdit.SetRange(-10000.0f, 10000.0f);
	m_SpinEdit.SetPos(0);
	m_SpinEdit.SetDelta(0.1f);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSpherize::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if (m_Plugin->LastAction!=ACTION_SPHERIZE)
	{
		m_Plugin->PutSelectedToBuf();
		m_Plugin->LastAction=ACTION_SPHERIZE;
		m_Plugin->m_Scene->GetNbSelectedMeshs();
		m_Plugin->m_Scene->SetSelectedToBeforeUndo("Modifier.dll",UNDO_MODIFY);

	}
	
	m_Plugin->Spherize(m_SpinEdit.GetPos());
	m_Plugin->m_Scene->SetSelectedToAfterUndoNoADD();

	DrawViews();	
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CSpherize::OnOK( )
{

}

void CSpherize::OnCancel( )
{

}