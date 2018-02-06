// TVTestDlg.h : header file
//

#if !defined(AFX_TVTESTDLG_H__1C43C720_F407_437A_A801_D38E6E4ADCC8__INCLUDED_)
#define AFX_TVTESTDLG_H__1C43C720_F407_437A_A801_D38E6E4ADCC8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DirTreeCtrl.h"
#include "mltitree.h"
/////////////////////////////////////////////////////////////////////////////
// CTVTestDlg dialog

class CTVTestDlg : public CDialog
{
// Construction
public:
	CTVTestDlg(CWnd* pParent = NULL);	// standard constructor
	void UpdateHiding(void);

// Dialog Data
	//{{AFX_DATA(CTVTestDlg)
	enum { IDD = IDD_TVTEST_DIALOG };
	CTreeCtrl	m_Projects;
	CMultiTree	m_Hierar;
	CDirTreeCtrl	m_TVFileView;
	CTabCtrl	m_Tabs;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTVTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

	void RecCalcBone(Bone *daBone,HTREEITEM &hItem);
	void UpdateHierTree(Desk *dk);
	bool RecurseHide(HTREEITEM dait,bool Hidden);
	bool SetItemHiding(HTREEITEM dait,bool Hidden);
	
// Implementation
protected:

	HICON m_hIcon;
	CImageList imgl;
	CBitmap bmp1;
	Desk *dadk;
	void UpdateDeskTree(void);
	HTREEITEM daRoot;

	// Generated message map functions
	//{{AFX_MSG(CTVTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSize(UINT nType,int cx,int cy);
	LRESULT OnSelChanged(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	afx_msg LRESULT OnWmUpdate(WPARAM wParam, LPARAM lParam) ;
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TVTESTDLG_H__1C43C720_F407_437A_A801_D38E6E4ADCC8__INCLUDED_)
