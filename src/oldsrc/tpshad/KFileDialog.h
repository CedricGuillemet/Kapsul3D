// tpackshadDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "FileTreeCtrl.h"
#include "afxwin.h"
#include "ThumbListView.h"
#include "BtnSt.h"

// CKFileDialog dialog
class CKFileDialog : public CDialog
{
// Construction
public:
	CKFileDialog(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TPACKSHAD_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
    void ChangeFileStyle(DWORD dwView);

	DECLARE_MESSAGE_MAP()
public:
    CTreeFileCtrl m_TreeCtl;
    CComboBox m_FileListCtl;
    CThumbListView m_ListFile;
    afx_msg void OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult);
    CButtonST m_NewRep;
    CButtonST m_ListDetails;
    CButtonST m_ListList;
    CButtonST m_ListLargeIcons;
    CButtonST m_Back;
    CButtonST m_Up;
	CButtonST m_BtOK;
	CButtonST m_BtCancel;
	CButtonST m_SynchFolder;
	CEdit m_FileName;
	CComboBox m_Extensions;
	CStatic m_StatFN,m_StatExt;

	

    afx_msg void OnBnClickedDetails();
    afx_msg void OnBnClickedList();
    afx_msg void OnBnClickedLargeicons();
    afx_msg void OnBnClickedNewrep();
	afx_msg void OnSize(UINT nType, int cx, int cy );


	void SetSaveUsage(void);
	void SetExtensionsList(CString ExtList);

};
