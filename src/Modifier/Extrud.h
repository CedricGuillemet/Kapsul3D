#if !defined(AFX_EXTRUD_H__5633C75D_5521_4A46_9112_4016B7E9FE5E__INCLUDED_)
#define AFX_EXTRUD_H__5633C75D_5521_4A46_9112_4016B7E9FE5E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Extrud.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExtrud dialog

class CExtrud : public CDialog
{
// Construction
public:
	CExtrud(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CExtrud)
	enum { IDD = IDD_EXTRUD };
	CNumEdit	m_EditSteps;
	CNumSpinCtrl	m_SpinSteps;
	CNumSpinCtrl	m_SpinScale;
	CNumSpinCtrl	m_SpinLength;
	CNumEdit	m_EditScale;
	CNumEdit	m_EditLenght;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExtrud)
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
	//{{AFX_MSG(CExtrud)
	virtual BOOL OnInitDialog();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXTRUD_H__5633C75D_5521_4A46_9112_4016B7E9FE5E__INCLUDED_)
