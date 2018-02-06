#if !defined(__MYSTATUSBAR_H__)
#define __MYSTATUSBAR_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// mybar.h : header file
//
#include "KStatusBar.h"

/////////////////////////////////////////////////////////////////////////////
// CMyStatusBar window

#ifndef baseCMyStatusBar
#define baseCMyStatusBar CSizingControlBarG
#endif

class CMyStatusBar : public baseCMyStatusBar
{
// Construction
public:
	CMyStatusBar();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyStatusBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyStatusBar();
	CKStatusBar	m_cDialog;
//protected:
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CMyStatusBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(__MYBAR_H__)
