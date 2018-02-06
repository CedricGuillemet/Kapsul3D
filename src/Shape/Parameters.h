#if !defined(AFX_PARAMETERS_H__2CBC6146_F728_48E6_8646_98B84A588D17__INCLUDED_)
#define AFX_PARAMETERS_H__2CBC6146_F728_48E6_8646_98B84A588D17__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Parameters.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CParameters dialog
#include "ModShape.h"

class CParameters : public CDialog
{
// Construction
public:
	CParameters(CWnd* pParent = NULL);   // standard constructor
	CKPluginShape *m_Plugin;

	void SetParam(float Min,float Max,float Steps,float Pos);
// Dialog Data
	//{{AFX_DATA(CParameters)
	enum { IDD = IDD_PARAM };
	CNumSpinCtrl	m_SpinSteps;
	CNumEdit	m_EditSteps;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParameters)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual void OnOK( );
	virtual void OnCancel( );

	// Generated message map functions
	//{{AFX_MSG(CParameters)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARAMETERS_H__2CBC6146_F728_48E6_8646_98B84A588D17__INCLUDED_)
