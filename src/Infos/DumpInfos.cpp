// DumpInfos.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "DumpInfos.h"
#include "InfosScene.h"
#include "InfosSel.h"

#include <atlbase.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CRollupCtrl *m_wndRollupCtrl;
extern CInfosScene *m_InfoScene;
extern CInfosSel *m_InfoSel;

/////////////////////////////////////////////////////////////////////////////
// CDumpInfos dialog


CDumpInfos::CDumpInfos(CWnd* pParent /*=NULL*/)
	: CDialog(CDumpInfos::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDumpInfos)
	//}}AFX_DATA_INIT
}


void CDumpInfos::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDumpInfos)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDumpInfos, CDialog)
	//{{AFX_MSG_MAP(CDumpInfos)
	ON_WM_PAINT()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDumpInfos message handlers

void CDumpInfos::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
}

BOOL CDumpInfos::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_InfoScene=new CInfosScene;
	m_InfoSel=new CInfosSel;

	m_InfoScene->Create(MAKEINTRESOURCE(IDD_INFOSSCENE),m_wndRollupCtrl);
	m_InfoSel->Create(MAKEINTRESOURCE(IDD_INFOSSEL),m_wndRollupCtrl);

    m_wndRollupCtrl->InsertPage("Scene",m_InfoScene);
	m_wndRollupCtrl->InsertPage("Selection",m_InfoSel);

    m_wndRollupCtrl->ExpandPage(0,TRUE);
	m_wndRollupCtrl->ExpandPage(1,TRUE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDumpInfos::OnDestroy() 
{
	CDialog::OnDestroy();
	
	m_wndRollupCtrl->DestroyWindow();

	delete m_wndRollupCtrl;	
}
