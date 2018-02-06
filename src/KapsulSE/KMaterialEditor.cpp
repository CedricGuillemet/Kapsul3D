// KMaterialEditor.cpp : implementation file
//

#include "stdafx.h"
#include "kapsulse.h"
#include "KMaterialEditor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKMaterialEditor dialog


CKMaterialEditor::CKMaterialEditor(CWnd* pParent /*=NULL*/)
	: CDialog(CKMaterialEditor::IDD, pParent)
{
	//{{AFX_DATA_INIT(CKMaterialEditor)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CKMaterialEditor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKMaterialEditor)
	DDX_Control(pDX, IDC_SELECTRENDERER, m_SelectRenderer);
	DDX_Control(pDX, IDC_PREVIEW, m_Preview);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CKMaterialEditor, CDialog)
	//{{AFX_MSG_MAP(CKMaterialEditor)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKMaterialEditor message handlers
