// PathModDiag.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ModDiag.h"
#include "CalcTex.h"
#include "UVMapperDiag.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPathModDiag dialog


CPathModDiag::CPathModDiag(CWnd* pParent /*=NULL*/)
	: CDialog(CPathModDiag::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPathModDiag)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPathModDiag::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPathModDiag)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPathModDiag, CDialog)
	//{{AFX_MSG_MAP(CPathModDiag)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPathModDiag message handlers
CCalcTex m_CalcTex;
CUVMapperDiag m_Mapper;

extern CRollupCtrl *m_wndRollupCtrl;

BOOL CPathModDiag::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_CalcTex.Create(MAKEINTRESOURCE(IDD_CALCTEX),m_wndRollupCtrl);
    m_Mapper.Create(MAKEINTRESOURCE(IDD_UVEDIT),m_wndRollupCtrl);
    //m_Primitive.Create(MAKEINTRESOURCE(IDD_MODDIAG1),m_wndRollupCtrl);

    //m_wndRollupCtrl->InsertPage("Primitive",&m_Primitive);
    m_wndRollupCtrl->InsertPage("UV Mapper",&m_Mapper);
    m_wndRollupCtrl->InsertPage("UV Shapes",&m_CalcTex);

    //m_wndRollupCtrl->ExpandPage(0,TRUE);
    m_wndRollupCtrl->ExpandPage(0,TRUE);
    m_wndRollupCtrl->ExpandPage(1,TRUE);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
