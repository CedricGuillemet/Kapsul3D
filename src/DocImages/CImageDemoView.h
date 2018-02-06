// CImageDemoView.h : interface of the CCImageDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CIMAGEDEMOVIEW_H__CD874C10_8ADC_11D2_9D51_02608C7A0EC4__INCLUDED_)
#define AFX_CIMAGEDEMOVIEW_H__CD874C10_8ADC_11D2_9D51_02608C7A0EC4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CCImageDemoView : public CScrollView
{
protected: // create from serialization only
	CCImageDemoView();
	DECLARE_DYNCREATE(CCImageDemoView)

// Attributes
public:
	CCImageDemoDoc* GetDocument();

// Operations
public:
	CScrollBar m_sbHorz,m_sbVert;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCImageDemoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCImageDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CBrush m_Brush;
	float m_Scale;
// Generated message map functions
protected:
	//{{AFX_MSG(CCImageDemoView)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CImageDemoView.cpp
inline CCImageDemoDoc* CCImageDemoView::GetDocument()
   { return (CCImageDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CIMAGEDEMOVIEW_H__CD874C10_8ADC_11D2_9D51_02608C7A0EC4__INCLUDED_)
