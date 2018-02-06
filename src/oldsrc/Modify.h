#if !defined(AFX_MODIFY_H__BDFC1D47_C40B_472B_83C8_1977EBB577C4__INCLUDED_)
#define AFX_MODIFY_H__BDFC1D47_C40B_472B_83C8_1977EBB577C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Modify.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CModify dialog

class CModify : public CDialog
{
// Construction
public:
	CModify(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CModify)
	enum { IDD = IDD_MODIFY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModify)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CModify)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODIFY_H__BDFC1D47_C40B_472B_83C8_1977EBB577C4__INCLUDED_)
