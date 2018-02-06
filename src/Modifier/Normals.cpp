// Normals.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "Normals.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNormals dialog


CNormals::CNormals(CWnd* pParent /*=NULL*/)
	: CDialog(CNormals::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNormals)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CNormals::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNormals)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNormals, CDialog)
	//{{AFX_MSG_MAP(CNormals)
	ON_BN_CLICKED(IDC_FLIPNORMALS, OnFlipnormals)
	ON_BN_CLICKED(IDC_UNIFYNORMALS, OnUnifynormals)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNormals message handlers

void CNormals::OnFlipnormals() 
{
	m_Plugin->m_Scene->GetNbSelectedMeshs();
	m_Plugin->m_Scene->SetSelectedToBeforeUndo("Modifier.dll",UNDO_MODIFY);
	m_Plugin->FlipNormalFaces();
	m_Plugin->m_Scene->SetSelectedToAfterUndoNoADD();
}

void CNormals::OnUnifynormals() 
{
	m_Plugin->m_Scene->GetNbSelectedMeshs();
	m_Plugin->m_Scene->SetSelectedToBeforeUndo("Modifier.dll",UNDO_MODIFY);
	m_Plugin->UnifyNormalFaces();
	m_Plugin->m_Scene->SetSelectedToAfterUndoNoADD();

}

BOOL CNormals::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNormals::OnOK( )
{

}

void CNormals::OnCancel( )
{

}