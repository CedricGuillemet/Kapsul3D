#if !defined(AFX_LIGHTMOD_H__18DD2933_70B0_44C7_BD2B_58F9091311DB__INCLUDED_)
#define AFX_LIGHTMOD_H__18DD2933_70B0_44C7_BD2B_58F9091311DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LightMod.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLightMod dialog

class CLightMod : public CDialog
{
// Construction
public:
	CLightMod(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLightMod)
	enum { IDD = IDD_MODDIAG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLightMod)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
public:
    void UnSetPlugin(void);
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLightMod)
	virtual BOOL OnInitDialog();
	virtual void OnOK( ); 
	virtual void OnCancel( ); 
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LIGHTMOD_H__18DD2933_70B0_44C7_BD2B_58F9091311DB__INCLUDED_)
