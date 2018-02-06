#if !defined(AFX_SUBDIV_H__98CDE46F_1795_43FE_BE8D_375D3FA68D11__INCLUDED_)
#define AFX_SUBDIV_H__98CDE46F_1795_43FE_BE8D_375D3FA68D11__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Subdiv.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSubdiv dialog

class CSubdiv : public CDialog
{
// Construction
public:
	CSubdiv(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSubdiv)
	enum { IDD = IDD_SUBDIVIDE };
	CNumSpinCtrl	m_Spin;
	CNumEdit	m_Edit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSubdiv)
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
	//{{AFX_MSG(CSubdiv)
	virtual BOOL OnInitDialog();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUBDIV_H__98CDE46F_1795_43FE_BE8D_375D3FA68D11__INCLUDED_)
