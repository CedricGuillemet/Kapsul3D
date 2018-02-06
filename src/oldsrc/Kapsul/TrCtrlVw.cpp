// TrCtrlVw.cpp : implementation file
//
//This shows one method of how to use your own
// CTreeCtrl class in a CTreeView derived class


#include "stdafx.h"
#include "TrCtrlVw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTreeControlView

IMPLEMENT_DYNCREATE(CTreeControlView, CTreeControlView_BASE)

CTreeControlView::CTreeControlView()
{
	m_pTree = NULL;
}

CTreeControlView::~CTreeControlView()
{
	if (m_pTree) {
		m_pTree->m_hWnd = NULL;
		delete m_pTree;
	}
}

#define CTreeView	CTreeControlView_BASE
BEGIN_MESSAGE_MAP(CTreeControlView, CTreeView)
#undef CTreeView
	//{{AFX_MSG_MAP(CTreeControlView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeControlView diagnostics

#ifdef _DEBUG
void CTreeControlView::AssertValid() const
{
	CTreeControlView_BASE::AssertValid();
}

void CTreeControlView::Dump(CDumpContext& dc) const
{
	CTreeControlView_BASE::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTreeControlView message handlers

BOOL CTreeControlView::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style |= TVS_HASBUTTONS|TVS_HASLINES|TVS_SHOWSELALWAYS|TVS_LINESATROOT;// | TVS_INFOTIP;
	return CTreeControlView_BASE::PreCreateWindow(cs);
}

int CTreeControlView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTreeControlView_BASE::OnCreate(lpCreateStruct) == -1)
		return -1;

	AllocEmbeddedTree();

	//force tree to use this
	m_pTree->m_hWnd = m_hWnd;
	m_pTree->m_pfnSuper = m_pfnSuper;
	m_pTree->PreSubclassWindow();
	return 0;
}

void CTreeControlView::AllocEmbeddedTree()
{
	//over-ride this virtual to allocate your own
	// CTreeCtrl class
	ASSERT(!m_pTree);		//don't call base if over-ridden
	m_pTree = new CTC;
}

/////////////////////////////////////////////////////////////////////////////
// Fancy stuff for giving us the ability to use our
// own derived CTreeCtrl

LRESULT CTreeControlView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	LRESULT lResult = 0;
	if (!OnWndMsg(message, wParam, lParam, &lResult))
		if (!m_pTree || !m_pTree->OnWndMsg(message, wParam, lParam, &lResult))
			lResult = DefWindowProc(message, wParam, lParam);
	return lResult;
}

BOOL CTreeControlView::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult) 
{
	if (CTreeControlView_BASE::OnChildNotify(message, wParam, lParam, pLResult))
		return TRUE;
	return m_pTree && m_pTree->OnChildNotify(message, wParam, lParam, pLResult);
}

BOOL CTreeControlView::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	if (CTreeControlView_BASE::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;
	return m_pTree && m_pTree->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}
