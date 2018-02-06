#if !defined(AFX_OPTIONSEDITING_H__7C7177BD_FE2A_4DB6_9C45_6CB0E8A82A2D__INCLUDED_)
#define AFX_OPTIONSEDITING_H__7C7177BD_FE2A_4DB6_9C45_6CB0E8A82A2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsEditing.h : header file
//
#include "objInspector\ObjectInspector.h"

/////////////////////////////////////////////////////////////////////////////
// COptionsEditing dialog

class COptionsEditing : public CDialog
{
// Construction
public:
	COptionsEditing(CWnd* pParent = NULL);   // standard constructor
	void ValidateOptions(void);
// Dialog Data
	//{{AFX_DATA(COptionsEditing)
	enum { IDD = IDD_OPTIONS_EDITING };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	CObjectInspector m_Oi;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionsEditing)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString		m_szProp[60];
	float		m_fProp[60];
	int			m_iProp[60];
	COLORREF    m_clProp[60];
	CString		m_cbProp[60];
	CStringList m_cbListProp[60];
	CStringList m_initProp[60];
	bool		m_blProp[60];
	// Generated message map functions
	//{{AFX_MSG(COptionsEditing)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSEDITING_H__7C7177BD_FE2A_4DB6_9C45_6CB0E8A82A2D__INCLUDED_)
