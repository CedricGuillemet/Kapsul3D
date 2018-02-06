// Divide.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "Divide.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDivide dialog


CDivide::CDivide(CWnd* pParent /*=NULL*/)
	: CDialog(CDivide::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDivide)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDivide::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDivide)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDivide, CDialog)
	//{{AFX_MSG_MAP(CDivide)
	ON_BN_CLICKED(IDC_DIV2, OnDiv2)
	ON_BN_CLICKED(IDC_DIV3, OnDiv3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDivide message handlers

void CDivide::OnDiv2() 
{
	
	m_Plugin->m_Scene->GetNbSelectedMeshs();
	m_Plugin->m_Scene->SetSelectedToBeforeUndo("Modifier.dll",UNDO_MODIFY);
	
	for (CKMesh *daMesh=m_Plugin->m_Scene->FirstMesh;daMesh!=NULL;daMesh=daMesh->Next)
	{
		daMesh->DivideTriBy3();
	}
	m_Plugin->m_Scene->SetSelectedToAfterUndoNoADD();
	DrawViews();
}

void CDivide::OnDiv3() 
{
	m_Plugin->m_Scene->GetNbSelectedMeshs();
	m_Plugin->m_Scene->SetSelectedToBeforeUndo("Modifier.dll",UNDO_MODIFY);
	for (CKMesh *daMesh=m_Plugin->m_Scene->FirstMesh;daMesh!=NULL;daMesh=daMesh->Next)
	{
		daMesh->DivideTriBy4();
	}
	m_Plugin->m_Scene->SetSelectedToAfterUndoNoADD();
	DrawViews();

}

void CDivide::OnOK( )
{

}

void CDivide::OnCancel( )
{

}