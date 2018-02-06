#if !defined(AFX_UVEDITDIAG_H__D4DDAEDC_D0BE_4949_B5F9_2AF13E0ADAB0__INCLUDED_)
#define AFX_UVEDITDIAG_H__D4DDAEDC_D0BE_4949_B5F9_2AF13E0ADAB0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UVEditDiag.h : header file
//
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CUVEditDiag dialog

class CUVEditDiag : public CDialog
{
// Construction
public:
	CUVEditDiag(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUVEditDiag)
	enum { IDD = IDD_UVEDITDIAG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUVEditDiag)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUVEditDiag)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UVEDITDIAG_H__D4DDAEDC_D0BE_4949_B5F9_2AF13E0ADAB0__INCLUDED_)
