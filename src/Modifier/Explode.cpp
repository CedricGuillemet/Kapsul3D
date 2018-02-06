// Explode.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "Explode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExplode dialog


CExplode::CExplode(CWnd* pParent /*=NULL*/)
	: CDialog(CExplode::IDD, pParent)
{
	//{{AFX_DATA_INIT(CExplode)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CExplode::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExplode)
	DDX_Control(pDX, IDC_SPIN1, m_SpinEdit);
	DDX_Control(pDX, IDC_EDIT1, m_Edit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CExplode, CDialog)
	//{{AFX_MSG_MAP(CExplode)
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExplode message handlers

BOOL CExplode::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_SpinEdit.SetBuddy(&m_Edit);
	m_SpinEdit.SetRange(-10000.0f, 10000.0f);
	m_SpinEdit.SetPos(0);
	m_SpinEdit.SetDelta(0.1f);	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CExplode::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if (m_Plugin->LastAction!=ACTION_EXPLODE)
	{
		m_Plugin->m_Scene->GetNbSelectedMeshs();
		m_Plugin->m_Scene->SetSelectedToBeforeUndo("Modifier.dll",UNDO_MODIFY);

		m_Plugin->PutSelectedToBuf();
		m_Plugin->DelSelectedMesh();
		m_Plugin->LastAction=ACTION_EXPLODE;
		//CurrentUndo=m_Plugin->m_Scene->AddUndo(
	}
	
	m_Plugin->Explode(m_SpinEdit.GetPos());

	m_Plugin->m_Scene->GetNbSelectedMeshs();
	m_Plugin->m_Scene->SetSelectedToAfterUndoNoADD();

	DrawViews();

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}
void CExplode::OnOK( )
{

}

void CExplode::OnCancel( )
{

}