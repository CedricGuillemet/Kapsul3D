#if !defined(AFX_PATHMODDIAG_H__19A8D8F5_4CA6_45FA_90CC_E450F3AFA094__INCLUDED_)
#define AFX_PATHMODDIAG_H__19A8D8F5_4CA6_45FA_90CC_E450F3AFA094__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PathModDiag.h : header file
//
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CPathModDiag dialog

class CPathModDiag : public CDialog
{
// Construction
public:
	CPathModDiag(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPathModDiag)
	enum { IDD = IDD_MODDIAG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPathModDiag)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPathModDiag)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PATHMODDIAG_H__19A8D8F5_4CA6_45FA_90CC_E450F3AFA094__INCLUDED_)
