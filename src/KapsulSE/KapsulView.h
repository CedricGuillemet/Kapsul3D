// KapsulView.h : interface of the CKapsulView class
//


#pragma once


class CKapsulView : public CView
{
protected: // create from serialization only
	CKapsulView();
	DECLARE_DYNCREATE(CKapsulView)

// Attributes
public:
	CKapsulDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view


virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CKapsulView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	// Generated message map functions
	//{{AFX_MSG(CTestProps)
	afx_msg int OnCreate( LPCREATESTRUCT lpCreateStruct );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in KapsulView.cpp
inline CKapsulDoc* CKapsulView::GetDocument() const
   { return reinterpret_cast<CKapsulDoc*>(m_pDocument); }
#endif

