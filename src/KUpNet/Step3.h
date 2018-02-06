#if !defined(AFX_STEP3_H__9B9BECBF_E47E_4A21_A90E_F63CB5EAB35D__INCLUDED_)
#define AFX_STEP3_H__9B9BECBF_E47E_4A21_A90E_F63CB5EAB35D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Step3.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStep3 dialog

class CStep3 : public CDialog
{
// Construction
public:
	CStep3(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStep3)
	enum { IDD = IDD_KUPNET_DIALOG2 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStep3)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CStep3)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STEP3_H__9B9BECBF_E47E_4A21_A90E_F63CB5EAB35D__INCLUDED_)
