#if !defined(AFX_KSELECTRENDERER_H__752EF0CA_EA34_4F10_9FAB_DBA0EA3AD896__INCLUDED_)
#define AFX_KSELECTRENDERER_H__752EF0CA_EA34_4F10_9FAB_DBA0EA3AD896__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// KSelectRenderer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CKSelectRenderer dialog

class CKSelectRenderer : public CDialog
{
// Construction
public:
	CKSelectRenderer(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CKSelectRenderer)
	enum { IDD = IDD_SELECTRENDERER };
	CComboBox	m_SelectRenderer;
	CStatic	m_Container;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKSelectRenderer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HWND m_LasthWnd;
	int itRnd;
	// Generated message map functions
	//{{AFX_MSG(CKSelectRenderer)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeSelectrenderer();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KSELECTRENDERER_H__752EF0CA_EA34_4F10_9FAB_DBA0EA3AD896__INCLUDED_)
