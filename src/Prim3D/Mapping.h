#if !defined(AFX_MAPPING_H__7D622A66_8702_43CE_955C_7E21912F836D__INCLUDED_)
#define AFX_MAPPING_H__7D622A66_8702_43CE_955C_7E21912F836D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Mapping.h : header file
//

#include "modPrim3D.h"
class CKPluginPrim3D;
/////////////////////////////////////////////////////////////////////////////
// CMapping dialog

class CMapping : public CDialog
{
    DECLARE_DYNCREATE(CMapping)

// Construction
public:
	CMapping(CWnd* pParent = NULL);   // standard constructor
	CKPluginPrim3D *m_Plugin;
// Dialog Data
	//{{AFX_DATA(CMapping)
	enum { IDD = IDD_MODDIAG4 };
	CNumSpinCtrl	m_SpinV;
	CNumSpinCtrl	m_SpinU;
	CNumEdit	m_EditV;
	CNumEdit	m_EditU;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapping)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
// Implementation
protected:
	virtual void OnOK( );
	virtual void OnCancel( );

	// Generated message map functions
	//{{AFX_MSG(CMapping)
	virtual BOOL OnInitDialog();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPPING_H__7D622A66_8702_43CE_955C_7E21912F836D__INCLUDED_)
