// KSelectRenderer.cpp : implementation file
//

#include "stdafx.h"
#include "kapsulse.h"
#include "KSelectRenderer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CKPluginManager *GKPlugins;
extern CKOption *KOption;
/////////////////////////////////////////////////////////////////////////////
// CKSelectRenderer dialog


CKSelectRenderer::CKSelectRenderer(CWnd* pParent /*=NULL*/)
	: CDialog(CKSelectRenderer::IDD, pParent)
{
	//{{AFX_DATA_INIT(CKSelectRenderer)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CKSelectRenderer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKSelectRenderer)
	DDX_Control(pDX, IDC_SELECTRENDERER, m_SelectRenderer);
	DDX_Control(pDX, IDC_CONTAINER, m_Container);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CKSelectRenderer, CDialog)
	//{{AFX_MSG_MAP(CKSelectRenderer)
	ON_CBN_SELCHANGE(IDC_SELECTRENDERER, OnSelchangeSelectrenderer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKSelectRenderer message handlers

BOOL CKSelectRenderer::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	for (int i=0;i<GKPlugins->RendererPlugins.size();i++)
	{
		m_SelectRenderer.AddString(GKPlugins->RendererPlugins[i]->GetRendererName());
	}
	
	itRnd=m_SelectRenderer.FindStringExact(0,KOption->GetRenderer());
	if (itRnd==CB_ERR)
		itRnd=0;

	m_LasthWnd=NULL;
	m_SelectRenderer.SetCurSel(itRnd);

	OnSelchangeSelectrenderer();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CKSelectRenderer::OnSelchangeSelectrenderer() 
{
	
	if (m_LasthWnd!=NULL)
		::DestroyWindow(m_LasthWnd);

	m_LasthWnd=GKPlugins->RendererPlugins[m_SelectRenderer.GetCurSel()]->CreateConfigWindow(m_Container.m_hWnd);
}

void CKSelectRenderer::OnOK() 
{
	if (m_LasthWnd!=NULL)
		::DestroyWindow(m_LasthWnd);
	if (itRnd!=m_SelectRenderer.GetCurSel())
	{
		// select new renderer
		char temp[MAX_PATH];

		if (GetModuleFileName(GKPlugins->RendererPlugins[m_SelectRenderer.GetCurSel()]->m_hInst,temp,MAX_PATH)!=0)
		{
			CString sRet;
			char FileName[MAX_PATH],FileExt[32];
			_splitpath(temp,NULL,NULL,FileName,FileExt);
			sRet=KOption->m_AppDir;
			sRet+="plugins\\";
			sRet+=FileName;
			sRet+=FileExt;
			strcpy(KOption->m_Renderer,sRet.GetBuffer(1));
			KOption->WriteOptions();
		}


	}

	CDialog::OnOK();
}

void CKSelectRenderer::OnCancel()
{

}
