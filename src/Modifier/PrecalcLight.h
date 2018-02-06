#if !defined(AFX_PRECALCLIGHT_H__F7D00ECB_D266_49AD_AAA1_AADCA5A98805__INCLUDED_)
#define AFX_PRECALCLIGHT_H__F7D00ECB_D266_49AD_AAA1_AADCA5A98805__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PrecalcLight.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPrecalcLight dialog

class CPrecalcLight : public CDialog
{
// Construction
public:
	CPrecalcLight(CWnd* pParent = NULL);   // standard constructor
	CKPluginModifier *m_Plugin;
// Dialog Data
	//{{AFX_DATA(CPrecalcLight)
	enum { IDD = IDD_PRECALC };
	CButton	m_WriteRaw;
	CButton	m_Round;
	CComboBox	m_Density;
	CComboBox	m_Size;
	CProgressCtrl	m_Progress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrecalcLight)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual void OnOK( );
	virtual void OnCancel( );

	// Generated message map functions
	//{{AFX_MSG(CPrecalcLight)
	afx_msg void OnCalculate();
	virtual BOOL OnInitDialog();
	afx_msg void OnAmbiant();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRECALCLIGHT_H__F7D00ECB_D266_49AD_AAA1_AADCA5A98805__INCLUDED_)
