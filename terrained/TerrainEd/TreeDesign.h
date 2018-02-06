#if !defined(AFX_TREEDESIGN_H__11692A0C_9B28_4E79_AD0E_AF121676436E__INCLUDED_)
#define AFX_TREEDESIGN_H__11692A0C_9B28_4E79_AD0E_AF121676436E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TreeDesign.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTreeDesign dialog

class CTreeDesign : public CDialog
{
// Construction
public:
	CTreeDesign(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTreeDesign)
	enum { IDD = IDD_TREEDESIGN };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeDesign)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTreeDesign)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREEDESIGN_H__11692A0C_9B28_4E79_AD0E_AF121676436E__INCLUDED_)
