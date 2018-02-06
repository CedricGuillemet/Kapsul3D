#if !defined(AFX_NORMALS_H__063E71F7_F8E5_43F9_8DB2_9A2F2ADC91CB__INCLUDED_)
#define AFX_NORMALS_H__063E71F7_F8E5_43F9_8DB2_9A2F2ADC91CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Normals.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNormals dialog

class CNormals : public CDialog
{
// Construction
public:
	CNormals(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNormals)
	enum { IDD = IDD_NORMALS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNormals)
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
	//{{AFX_MSG(CNormals)
	afx_msg void OnFlipnormals();
	afx_msg void OnUnifynormals();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NORMALS_H__063E71F7_F8E5_43F9_8DB2_9A2F2ADC91CB__INCLUDED_)
