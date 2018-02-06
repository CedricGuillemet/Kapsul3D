#if !defined(AFX_PREVIEW_H__0F1E157F_9951_47BC_B239_622EDC2B30BA__INCLUDED_)
#define AFX_PREVIEW_H__0F1E157F_9951_47BC_B239_622EDC2B30BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Preview.h : header file
//
#include "OglViewer.h"

/////////////////////////////////////////////////////////////////////////////
// CPreview dialog

class CPreview : public CDialog
{
// Construction
public:
	CPreview(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPreview)
	enum { IDD = IDD_PREVIEW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPreview)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    COglViewer m_View;
	// Generated message map functions
	//{{AFX_MSG(CPreview)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PREVIEW_H__0F1E157F_9951_47BC_B239_622EDC2B30BA__INCLUDED_)
