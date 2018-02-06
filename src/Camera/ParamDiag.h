#if !defined(AFX_PARAMDIAG_H__B6425812_4A78_4629_A765_13B6AD4EECC7__INCLUDED_)
#define AFX_PARAMDIAG_H__B6425812_4A78_4629_A765_13B6AD4EECC7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ParamDiag.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CParamDiag dialog
#include "resource.h"

class CParamDiag : public CDialog
{
// Construction
public:
	CParamDiag(CWnd* pParent = NULL);   // standard constructor
	CKCamera *CurrentCam;
// Dialog Data
	//{{AFX_DATA(CParamDiag)
	enum { IDD = IDD_MOD };
	CNumSpinCtrl	m_SpinY;
	CNumSpinCtrl	m_SpinX;
	CNumSpinCtrl	m_SpinFov;
	CNumEdit	m_EditY;
	CNumEdit	m_EditX;
	CNumEdit	m_EditFov;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParamDiag)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL


// Implementation
protected:
	virtual void OnOK( );
	virtual void OnCancel( );
	

	// Generated message map functions
	//{{AFX_MSG(CParamDiag)
	virtual BOOL OnInitDialog();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARAMDIAG_H__B6425812_4A78_4629_A765_13B6AD4EECC7__INCLUDED_)
