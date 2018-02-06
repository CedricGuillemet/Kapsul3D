// ChildFrm.cpp : implementation of the CSampleChildFrame class
//

#include "stdafx.h"
//#include "Sample.h"
#include "SampleChildFrm.h"
#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSampleChildFrame

IMPLEMENT_DYNCREATE(CSampleChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CSampleChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CSampleChildFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSampleChildFrame construction/destruction

CSampleChildFrame::CSampleChildFrame()
{
	// TODO: add member initialization code here
	
}

CSampleChildFrame::~CSampleChildFrame()
{
}

BOOL CSampleChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CMDIChildWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSampleChildFrame diagnostics

#ifdef _DEBUG
void CSampleChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CSampleChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSampleChildFrame message handlers

BOOL CSampleChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	return m_wndSplitter.Create(this, 2, 2, CSize(30, 30), pContext);
}
