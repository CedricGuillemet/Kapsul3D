// KapsulView.cpp : implementation of the CKapsulView class
//

#include "stdafx.h"
#include "Kapsul.h"

#include "KapsulDoc.h"
#include "KapsulView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKapsulView

IMPLEMENT_DYNCREATE(CKapsulView, CView)

BEGIN_MESSAGE_MAP(CKapsulView, CView)
END_MESSAGE_MAP()

// CKapsulView construction/destruction

CKapsulView::CKapsulView()
{
	// TODO: add construction code here

}

CKapsulView::~CKapsulView()
{
}

BOOL CKapsulView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CKapsulView drawing

void CKapsulView::OnDraw(CDC* /*pDC*/)
{
	CKapsulDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}


// CKapsulView diagnostics

#ifdef _DEBUG
void CKapsulView::AssertValid() const
{
	CView::AssertValid();
}

void CKapsulView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKapsulDoc* CKapsulView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKapsulDoc)));
	return (CKapsulDoc*)m_pDocument;
}
#endif //_DEBUG


// CKapsulView message handlers
