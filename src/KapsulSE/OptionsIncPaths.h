#if !defined(AFX_OPTIONSINCPATHS_H__D7320A8D_960D_4ED9_8F09_62D8124C73DD__INCLUDED_)
#define AFX_OPTIONSINCPATHS_H__D7320A8D_960D_4ED9_8F09_62D8124C73DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// COptionsIncPaths dialog
#include "PathDropList.h"

class COptionsIncPaths : public CDialog
{
// Construction
public:
	COptionsIncPaths(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COptionsIncPaths)
	enum { IDD = IDD_OPTIONS_INCPATHS };
	CPathDropList	m_ListBoxEx;
	//}}AFX_DATA

	//CListBoxExBuddy m_ListBoxExBuddy;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionsIncPaths)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COptionsIncPaths)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSINCPATHS_H__D7320A8D_960D_4ED9_8F09_62D8124C73DD__INCLUDED_)
