#if !defined(AFX_MODDIAG_H__E3AF07C9_9F8E_4F6F_8ECC_42B763B11294__INCLUDED_)
#define AFX_MODDIAG_H__E3AF07C9_9F8E_4F6F_8ECC_42B763B11294__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModDiag.h : header file
//
#include "ParamDiag.h"
/////////////////////////////////////////////////////////////////////////////
// CModDiag dialog

class CModDiag : public CDialog
{
// Construction
public:
	CModDiag(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CModDiag)
	enum { IDD = IDD_MODDIAG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModDiag)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
public:
    void UnSetPlugin(void);
	CParamDiag *m_ParamDiag;
// Implementation
protected:
	virtual void OnOK( );
	virtual void OnCancel( );

	// Generated message map functions
	//{{AFX_MSG(CModDiag)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODDIAG_H__E3AF07C9_9F8E_4F6F_8ECC_42B763B11294__INCLUDED_)
