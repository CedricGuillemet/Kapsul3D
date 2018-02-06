// tpackshadDlg.h : header file
//

#pragma once

#include "afxcmn.h"
#include "FileTreeCtrl.h"
#include "afxwin.h"
#include "KThumbListView.h"
#include "BtnSt2.h"
#include "resource.h"

// CKFileDialog dialog
class Exts
{
public:
	CString ExtDesc;
	vector<CString> Wilds;
public:
	Exts(CString _ExtDesc) {ExtDesc=_ExtDesc; };
	Exts() {};
	~Exts() {};

};

class KAPSUL_DESC CKFileDialog : public CDialog
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
	vector<CString> BackList;
	

	DECLARE_MESSAGE_MAP()
public:
    CTreeFileCtrl m_TreeCtl;
    CKThumbListView m_ListFile;
    afx_msg void OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult);
    CButtonST2 m_ListDetails;
    CButtonST2 m_ListList;
    CButtonST2 m_ListLargeIcons;
    CButtonST2 m_Back;
    CButtonST2 m_Up;
	CButtonST2 m_BtOK;
	CButtonST2 m_BtCancel;
	CEdit m_FileName;
	CComboBox m_Extensions;
	CStatic m_StatFN,m_StatExt;

	vector<Exts> XTensions;
	

    afx_msg void OnBnClickedDetails();
    afx_msg void OnBnClickedList();
    afx_msg void OnBnClickedLargeicons();
    afx_msg void OnBnClickedNewrep();
	afx_msg void OnSize(UINT nType, int cx, int cy );
	afx_msg void OnBnClickedBack();
	afx_msg void OnBnClickedUp();
	afx_msg void OnSelchangeExts();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnClose();

	void SetTypes(CString Types);
	void SetInitialDir(CString InitialDir);
	void IsForOpen();
	void IsForSave();
	void SetSaveUsage(void);
	void SetExtensionsList(CString ExtList);
	int ExtInd;
	bool IsForSaving;
	CString BtOkStr;
	CString OpenedFile;

};
