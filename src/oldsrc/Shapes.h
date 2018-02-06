#if !defined(AFX_SHAPES_H__91EEE940_2D33_41FC_BF2D_24FB2DE7CACE__INCLUDED_)
#define AFX_SHAPES_H__91EEE940_2D33_41FC_BF2D_24FB2DE7CACE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Shapes.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CShapes dialog

class CShapes : public CDialog
{
// Construction
public:
	CShapes(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CShapes)
	enum { IDD = IDD_SHAPES };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShapes)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CShapes)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHAPES_H__91EEE940_2D33_41FC_BF2D_24FB2DE7CACE__INCLUDED_)
