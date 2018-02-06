#if !defined(AFX_OPTIONSMAPPATHS_H__698176DD_02BC_4E8D_A113_AD3CF8A66020__INCLUDED_)
#define AFX_OPTIONSMAPPATHS_H__698176DD_02BC_4E8D_A113_AD3CF8A66020__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsMapPaths.h : header file
//
//#include "shBrowseDlg.h"
//#include "alistbox.h"


/////////////////////////////////////////////////////////////////////////////
// COptionsMapPaths dialog

class COptionsMapPaths : public CDialog
{
// Construction
public:
	COptionsMapPaths(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COptionsMapPaths)
	enum { IDD = IDD_OPTIONS_MAPPATHS };
	CMyListBoxEx	m_ListBoxEx;
	//}}AFX_DATA

	CListBoxExBuddy m_ListBoxExBuddy;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionsMapPaths)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COptionsMapPaths)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSMAPPATHS_H__698176DD_02BC_4E8D_A113_AD3CF8A66020__INCLUDED_)
