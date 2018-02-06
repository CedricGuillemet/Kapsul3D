// CImageDemoView.cpp : implementation of the CCImageDemoView class
//

#include "stdafx.h"
#include "CImageDemo.h"

#include "CImageDemoDoc.h"
#include "CImageDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCImageDemoView
#define SBWIDTH 14
IMPLEMENT_DYNCREATE(CCImageDemoView, CScrollView)

BEGIN_MESSAGE_MAP(CCImageDemoView, CScrollView)
	//{{AFX_MSG_MAP(CCImageDemoView)
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCImageDemoView construction/destruction


CCImageDemoView::CCImageDemoView()
{
	SetScrollSizes(MM_TEXT,CSize(1000,1000));
	m_Brush.CreateSolidBrush(RGB(0,0,0));
	m_Scale=1;
}

CCImageDemoView::~CCImageDemoView()
{
}

BOOL CCImageDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCImageDemoView drawing

void CCImageDemoView::OnDraw(CDC* pDC)
{
	CCImageDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	RECT rc;

	int stx=0,sty=0;
	int m_ImgSX=pDoc->m_Image.GetWidth()*m_Scale,m_ImgSY=pDoc->m_Image.GetHeight()*m_Scale;
	SetScrollSizes(MM_TEXT,CSize(m_ImgSX,m_ImgSY));

	GetClientRect(&rc);
	
	if (rc.right>m_ImgSX)
		stx=(rc.right-m_ImgSX)/2;

	if (rc.bottom>m_ImgSY)
		sty=(rc.bottom-m_ImgSY)/2;

	if (stx!=0)
	{
		GetDC()->FillRect(CRect(0,0,stx,rc.bottom),&m_Brush);
		GetDC()->FillRect(CRect(m_ImgSX+stx,0,rc.right,rc.bottom),&m_Brush);
	}

	if (sty!=0)
	{
		GetDC()->FillRect(CRect(0,0,rc.right,sty),&m_Brush);
		GetDC()->FillRect(CRect(0,m_ImgSY+sty,rc.right,rc.bottom),&m_Brush);
	}


	DWORD dwFlags = DIB_DRAW_SETPALETTE|DIB_DRAW_STRETCH_EXPANDX|DIB_DRAW_STRETCH_EXPANDY|DIB_DRAW_STRETCH_REDUCEX|
		DIB_DRAW_STRETCH_REDUCEY|DIB_DRAW_KEEP_RATIO|DIB_DRAW_USE_GDI|DIB_DRAW_CLIP;
	/*
	if(pDoc->m_bAffTransparent)
		dwFlags |= DIB_DRAW_TRANSPARENT;
*/
	pDoc->m_Image.Draw(pDC->m_hDC, CRect(stx,sty,stx+m_ImgSX,sty+m_ImgSY), dwFlags);
	//pDoc->m_Image.Draw(pDC, CRect(stx,sty,stx+rc.right,sty+rc.bottom), dwFlags,CRect(0,0,m_ImgSX*m_Scale,m_ImgSY*m_Scale));
	
}

/////////////////////////////////////////////////////////////////////////////
// CCImageDemoView printing

BOOL CCImageDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCImageDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCImageDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCImageDemoView diagnostics

#ifdef _DEBUG
void CCImageDemoView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CCImageDemoView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CCImageDemoDoc* CCImageDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCImageDemoDoc)));
	return (CCImageDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCImageDemoView message handlers

void CCImageDemoView::OnSetFocus(CWnd* pOldWnd) 
{
	CScrollView::OnSetFocus(pOldWnd);
	
	InvalidateRect(NULL, FALSE);	
}

BOOL CCImageDemoView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	
	bool RetVal=CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
	/*
	m_sbHorz.Create(SBS_HORZ | SBS_TOPALIGN | WS_CHILD, CRect(5, 5, 100, 30), this, 100);
    m_sbHorz.ShowScrollBar(true);
	m_sbVert.Create(SBS_VERT | SBS_TOPALIGN | WS_CHILD, CRect(5, 5, 30, 100), this, 101);
    m_sbVert.ShowScrollBar(true);
*/
    return RetVal;

}

void CCImageDemoView::OnSize(UINT nType, int cx, int cy) 
{
	CScrollView::OnSize(nType, cx, cy);

}

BOOL CCImageDemoView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return FALSE;
//	return CView::OnEraseBkgnd(pDC);
}
CPoint pt1,pt2;
int CreateSeg;
void CCImageDemoView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CreateSeg=0;
	ReleaseCapture();
	
	CScrollView::OnLButtonUp(nFlags, point);
}

void CCImageDemoView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CreateSeg=1;
	pt1=point;
	SetCapture();
	pt2=this->GetScrollPosition();
	
	CScrollView::OnLButtonDown(nFlags, point);
}

void CCImageDemoView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (CreateSeg)
	{
		CPoint das;
		das=pt2+(pt1-point);
		ScrollToPosition(das);
	}
	
	CScrollView::OnMouseMove(nFlags, point);
}

BOOL CCImageDemoView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	CCImageDemoDoc* pDoc = GetDocument();
	CString DocName;

	if (zDelta<0)
	{
		m_Scale*=3;
		m_Scale/=4;
		
		
		Invalidate(FALSE);
	}
	else
	{
		m_Scale*=4;
		m_Scale/=3;
		Invalidate(FALSE);
	}

	//CString tmps=pDoc->GetPathName( );
	DocName.Format("%s [%5.2f %%]",pDoc->GetPathName( ),m_Scale*100);
	pDoc->SetTitle(DocName);
	
	return CScrollView::OnMouseWheel(nFlags, zDelta, pt);
}
