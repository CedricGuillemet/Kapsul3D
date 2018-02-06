// KUpNetDlg.h : header file
//

#if !defined(AFX_KUPNETDLG_H__937C9A4E_BDA5_41A6_A0E5_318D7E2A6AB4__INCLUDED_)
#define AFX_KUPNETDLG_H__937C9A4E_BDA5_41A6_A0E5_318D7E2A6AB4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CKUpNetDlg dialog

class CKUpNetDlg : public CDialog
{
// Construction
public:
	CKUpNetDlg(CWnd* pParent = NULL);	// standard constructor
	CWinThread*   m_pThread;
	static UINT _DownloadThread(LPVOID pParam);
// Dialog Data
	//{{AFX_DATA(CKUpNetDlg)
	enum { IDD = IDD_KUPNET_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKUpNetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CKUpNetDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnCancel();
	afx_msg void OnNext();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KUPNETDLG_H__937C9A4E_BDA5_41A6_A0E5_318D7E2A6AB4__INCLUDED_)
