#if !defined(AFX_EXPLODE_H__22911ABE_B612_4728_B7DD_8B01D29023FB__INCLUDED_)
#define AFX_EXPLODE_H__22911ABE_B612_4728_B7DD_8B01D29023FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Explode.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExplode dialog

class CExplode : public CDialog
{
// Construction
public:
	CExplode(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CExplode)
	enum { IDD = IDD_EXPLODE };
	CNumSpinCtrl	m_SpinEdit;
	CNumEdit	m_Edit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExplode)
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
	//{{AFX_MSG(CExplode)
	virtual BOOL OnInitDialog();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXPLODE_H__22911ABE_B612_4728_B7DD_8B01D29023FB__INCLUDED_)
