#if !defined(AFX_UVPARAM_H__125BA380_CECD_41C9_A096_CDCFFE5AD3B4__INCLUDED_)
#define AFX_UVPARAM_H__125BA380_CECD_41C9_A096_CDCFFE5AD3B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UVParam.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUVParam dialog

class CUVParam : public CDialog
{
// Construction
public:
	CUVParam(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUVParam)
	enum { IDD = IDD_UVPARAM };
	CNumSpinCtrl	m_SpinV;
	CNumSpinCtrl	m_SpinU;
	CNumEdit	m_EditV;
	CNumEdit	m_EditU;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUVParam)
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
	//{{AFX_MSG(CUVParam)
	virtual BOOL OnInitDialog();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UVPARAM_H__125BA380_CECD_41C9_A096_CDCFFE5AD3B4__INCLUDED_)
