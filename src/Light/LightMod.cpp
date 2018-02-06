// LightMod.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "LightMod.h"
#include "LightParam.h"
#include "LightBuild.h"
#include "PrecalcLight.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLightMod dialog
extern "C" CRollupCtrl __declspec(dllexport) *m_wndRollupCtrl;
CLightParam *m_ParamDiag;
CLightBuild *m_BuildDiag;
CPrecalcLight *m_PrecalcDiag;

CLightMod::CLightMod(CWnd* pParent /*=NULL*/)
	: CDialog(CLightMod::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLightMod)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CLightMod::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLightMod)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLightMod, CDialog)
	//{{AFX_MSG_MAP(CLightMod)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLightMod message handlers

BOOL CLightMod::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
		// TODO: Add extra initialization here


    m_wndRollupCtrl=new CRollupCtrl();
    m_wndRollupCtrl->Create(WS_VISIBLE|WS_CHILD, CRect(4,4,164,362), GetParent(), 2);	

	m_ParamDiag=new CLightParam;
	m_BuildDiag=new CLightBuild;
	m_PrecalcDiag=new CPrecalcLight;

	m_ParamDiag->Create(MAKEINTRESOURCE(IDD_PARAM),m_wndRollupCtrl);
    m_BuildDiag->Create(MAKEINTRESOURCE(IDD_BUILD),m_wndRollupCtrl);
	m_PrecalcDiag->Create(MAKEINTRESOURCE(IDD_PRECALC),m_wndRollupCtrl);

    m_wndRollupCtrl->InsertPage("Build",m_BuildDiag);
    m_wndRollupCtrl->InsertPage("Parameters",m_ParamDiag);
	m_wndRollupCtrl->InsertPage("Lightmaps",m_PrecalcDiag);

    m_wndRollupCtrl->ExpandPage(0,TRUE);
    m_wndRollupCtrl->ExpandPage(1,TRUE);
	m_wndRollupCtrl->ExpandPage(2,TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CLightMod::UnSetPlugin(void)
{
    m_BuildDiag->m_BuildIt.SetCheck(0);
}

void CLightMod::OnOK() 
{
}

void CLightMod::OnCancel() 
{
}

void CLightMod::OnDestroy() 
{
	CDialog::OnDestroy();
	
    m_wndRollupCtrl->DestroyWindow();
	delete m_wndRollupCtrl;
	
}
