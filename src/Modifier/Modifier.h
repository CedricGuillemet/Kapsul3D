#if !defined(AFX_MODIFIER_H__B9F300D3_4FBA_4746_A739_F0E8D2629ED1__INCLUDED_)
#define AFX_MODIFIER_H__B9F300D3_4FBA_4746_A739_F0E8D2629ED1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Modifier.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CModifier dialog

class CModifier : public CDialog
{
// Construction
public:
	CModifier(CWnd* pParent = NULL);   // standard constructor
	CKPluginModifier *m_Plugin;
// Dialog Data
	//{{AFX_DATA(CModifier)
	enum { IDD = IDD_MODIFIER };
	CButton	m_Clipper;
	CButton	m_Hollow;
	CButton	m_CsgSub;
	CButton	m_CsgMerge;
	CButton	m_SZ;
	CButton	m_SY;
	CButton	m_SX;
	CButton	m_RZ;
	CButton	m_RY;
	CButton	m_RX;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModifier)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual void OnOK( );
	virtual void OnCancel( );

	// Generated message map functions
	//{{AFX_MSG(CModifier)
	afx_msg void OnFlipnormals();
	afx_msg void OnUnifynormals();
	virtual BOOL OnInitDialog();
	afx_msg void OnHollow();
	afx_msg void OnCsgmerge();
	afx_msg void OnCsgsub();
	afx_msg void OnClipper();
	afx_msg void OnRx();
	afx_msg void OnSx();
	afx_msg void OnRy();
	afx_msg void OnSy();
	afx_msg void OnRz();
	afx_msg void OnSz();
	afx_msg void OnSpherize();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODIFIER_H__B9F300D3_4FBA_4746_A739_F0E8D2629ED1__INCLUDED_)
