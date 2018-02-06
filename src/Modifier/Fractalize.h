#if !defined(AFX_FRACTALIZE_H__9EB7E12E_BFA2_491E_A142_53EC196DF026__INCLUDED_)
#define AFX_FRACTALIZE_H__9EB7E12E_BFA2_491E_A142_53EC196DF026__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Fractalize.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFractalize dialog

class CFractalize : public CDialog
{
// Construction
public:
	CFractalize(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFractalize)
	enum { IDD = IDD_FRACTALIZE };
	CNumSpinCtrl	m_Spin;
	CNumEdit	m_Edit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFractalize)
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
	//{{AFX_MSG(CFractalize)
	virtual BOOL OnInitDialog();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnNewseed();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRACTALIZE_H__9EB7E12E_BFA2_491E_A142_53EC196DF026__INCLUDED_)
