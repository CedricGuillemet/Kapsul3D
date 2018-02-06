#if !defined(AFX_DIVIDE_H__A3E7DFBC_B899_4ADC_B27B_A231B4722DE9__INCLUDED_)
#define AFX_DIVIDE_H__A3E7DFBC_B899_4ADC_B27B_A231B4722DE9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Divide.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDivide dialog

class CDivide : public CDialog
{
// Construction
public:
	CDivide(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDivide)
	enum { IDD = IDD_DIVIDE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDivide)
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
	//{{AFX_MSG(CDivide)
	afx_msg void OnDiv2();
	afx_msg void OnDiv3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIVIDE_H__A3E7DFBC_B899_4ADC_B27B_A231B4722DE9__INCLUDED_)
