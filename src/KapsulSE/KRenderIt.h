#if !defined(AFX_KRENDERIT_H__E10ABAE4_5EDA_4164_A442_35BCBC338443__INCLUDED_)
#define AFX_KRENDERIT_H__E10ABAE4_5EDA_4164_A442_35BCBC338443__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// KRenderIt.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CKRenderIt dialog

class CKRenderIt : public CDialog
{
// Construction
public:
	CKRenderIt(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CKRenderIt)
	enum { IDD = IDD_RENDER };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKRenderIt)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CKRenderIt)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KRENDERIT_H__E10ABAE4_5EDA_4164_A442_35BCBC338443__INCLUDED_)
