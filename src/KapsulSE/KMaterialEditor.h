#if !defined(AFX_KMATERIALEDITOR_H__6E93ED05_7A21_4F5D_B410_C1FDC1A41CD9__INCLUDED_)
#define AFX_KMATERIALEDITOR_H__6E93ED05_7A21_4F5D_B410_C1FDC1A41CD9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// KMaterialEditor.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CKMaterialEditor dialog

class CKMaterialEditor : public CDialog
{
// Construction
public:
	CKMaterialEditor(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CKMaterialEditor)
	enum { IDD = IDD_MATERIALEDITOR };
	CComboBox	m_SelectRenderer;
	CStatic	m_Preview;
	CTabCtrl	m_Tab;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKMaterialEditor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CKMaterialEditor)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KMATERIALEDITOR_H__6E93ED05_7A21_4F5D_B410_C1FDC1A41CD9__INCLUDED_)
