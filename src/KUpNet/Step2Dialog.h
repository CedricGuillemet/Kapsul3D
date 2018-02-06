#if !defined(AFX_STEP2DIALOG_H__19EB5ED7_40A0_48E6_9270_31712B73A837__INCLUDED_)
#define AFX_STEP2DIALOG_H__19EB5ED7_40A0_48E6_9270_31712B73A837__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Step2Dialog.h : header file
//
#include "XListCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CStep2Dialog dialog

class CStep2Dialog : public CDialog
{
// Construction
public:
	CStep2Dialog(CWnd* pParent = NULL);   // standard constructor
	CWinThread*   m_pThread;
	static UINT _DownloadThread(LPVOID pParam);
	void ListPackages();
// Dialog Data
	//{{AFX_DATA(CStep2Dialog)
	enum { IDD = IDD_KUPNET_DIALOG1 };
	CStatic	m_AffStat;
	CProgressCtrl	m_Progress;
	CStatic	m_Lib2;
	CStatic	m_Lib1;
	CXListCtrl	m_List;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStep2Dialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CStep2Dialog)
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnNext();
	virtual void OnCancel();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STEP2DIALOG_H__19EB5ED7_40A0_48E6_9270_31712B73A837__INCLUDED_)
