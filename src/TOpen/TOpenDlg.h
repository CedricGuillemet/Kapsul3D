// TOpenDlg.h : header file
//

#if !defined(AFX_TOPENDLG_H__1ACB8CDC_594D_489F_9A12_D33BFCD4EE1B__INCLUDED_)
#define AFX_TOPENDLG_H__1ACB8CDC_594D_489F_9A12_D33BFCD4EE1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTOpenDlg dialog

class CTOpenDlg : public CDialog
{
// Construction
public:
	CTOpenDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTOpenDlg)
	enum { IDD = IDD_TOPEN_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTOpenDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTOpenDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOPENDLG_H__1ACB8CDC_594D_489F_9A12_D33BFCD4EE1B__INCLUDED_)
