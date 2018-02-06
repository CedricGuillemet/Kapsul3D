#if !defined(AFX_LATHE_H__E18AE345_BC1B_465D_90FC_BC5F646C0AE7__INCLUDED_)
#define AFX_LATHE_H__E18AE345_BC1B_465D_90FC_BC5F646C0AE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Lathe.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLathe dialog

class CLathe : public CDialog
{
// Construction
public:
	CLathe(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLathe)
	enum { IDD = IDD_LATHE };
	CStatic	m_ShapeName;
	CNumSpinCtrl	m_SpinEdit;
	CNumEdit	m_Edit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLathe)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
public:
	CKPluginModifier *m_Plugin;
	CKUndoRedo *m_CurrentUndo;
// Implementation
protected:
	virtual void OnOK( );
	virtual void OnCancel( );
	// Generated message map functions
	//{{AFX_MSG(CLathe)
	afx_msg void OnShape();
	virtual BOOL OnInitDialog();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LATHE_H__E18AE345_BC1B_465D_90FC_BC5F646C0AE7__INCLUDED_)
