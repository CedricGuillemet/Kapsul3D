#if !defined(AFX_MOPTIONS_H__9EA8D20E_ECF9_4199_872C_9D10F86E90C3__INCLUDED_)
#define AFX_MOPTIONS_H__9EA8D20E_ECF9_4199_872C_9D10F86E90C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Options.h : header file
//
#include "OptionsEditing.h"
#include "OptionsIncPaths.h"
#include "OptionsMapPaths.h"
#include "OptionsPrefabPaths.h"

/////////////////////////////////////////////////////////////////////////////
// MOptions dialog

class MOptions : public CDialog
{
// Construction
public:
	MOptions(CWnd* pParent = NULL);   // standard constructor


// Dialog Data
	//{{AFX_DATA(MOptions)
	enum { IDD = IDD_OPTIONS };
	CTabCtrl	m_Tab;
	//}}AFX_DATA

	COptionsEditing OptEdit;
	COptionsIncPaths OptIncPaths;
	COptionsMapPaths OptMapPaths;
	COptionsPrefabPaths OptPrefabPaths;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MOptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual void OnOK( );
	virtual void OnCancel( );

	// Generated message map functions
	//{{AFX_MSG(MOptions)
	afx_msg void OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONS_H__9EA8D20E_ECF9_4199_872C_9D10F86E90C3__INCLUDED_)
