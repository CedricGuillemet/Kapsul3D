#if !defined(__MYBAR_H__)
#define __MYBAR_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// mybar.h : header file
//
#include "TVTestDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CMyDeskBar window

#ifndef baseCMyDeskBar
#define baseCMyDeskBar CSizingControlBarG
#endif

class CMyDeskBar : public baseCMyDeskBar
{
// Construction
public:
	CMyDeskBar();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDeskBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyDeskBar();
	CTVTestDlg	m_cDialog;
//protected:
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CMyDeskBar)
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
