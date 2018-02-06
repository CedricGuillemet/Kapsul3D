#if !defined(AFX_SPHERIZE_H__B7D7DBB6_8BF9_4CB5_ADFE_8875616D9DC6__INCLUDED_)
#define AFX_SPHERIZE_H__B7D7DBB6_8BF9_4CB5_ADFE_8875616D9DC6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Spherize.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSpherize dialog

class CSpherize : public CDialog
{
// Construction
public:
	CSpherize(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSpherize)
	enum { IDD = IDD_SPHERIZE };
	CNumSpinCtrl	m_SpinEdit;
	CNumEdit	m_Edit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpherize)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
public:
	CKPluginModifier *m_Plugin;
// Implementation
protected:
	virtual void OnOK( );
	virtual void OnCancel( );
	// Generated message map functions
	//{{AFX_MSG(CSpherize)
	virtual BOOL OnInitDialog();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPHERIZE_H__B7D7DBB6_8BF9_4CB5_ADFE_8875616D9DC6__INCLUDED_)
