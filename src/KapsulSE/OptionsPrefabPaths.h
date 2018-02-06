#if !defined(AFX_OPTIONSPREFABPATHS_H__698176DD_02BC_4E8D_A113_AD3CF8A66020__INCLUDED_)
#define AFX_OPTIONSPREFABPATHS_H__698176DD_02BC_4E8D_A113_AD3CF8A66020__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsMapPaths.h : header file
//
//#include "shBrowseDlg.h"
//#include "alistbox.h"
#include "PathDropList.h"

/////////////////////////////////////////////////////////////////////////////
// COptionsPrefabPaths dialog

class COptionsPrefabPaths : public CDialog
{
// Construction
public:
	COptionsPrefabPaths(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COptionsPrefabPaths)
	enum { IDD = IDD_OPTIONS_MAPPATHS };
	CEdit	m_FolderEdit;
	//}}AFX_DATA

	//CListBoxExBuddy m_ListBoxExBuddy;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionsPrefabPaths)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CPathDropList m_PrefabList;
	// Generated message map functions
	//{{AFX_MSG(COptionsPrefabPaths)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnDelselected();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnAddpath();
	afx_msg void OnBrowsebt();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSMAPPATHS_H__698176DD_02BC_4E8D_A113_AD3CF8A66020__INCLUDED_)
