// tpackshadDlg.h : header file
//

#pragma once
//#include "Kapsul3D.h"

#include "afxcmn.h"
//#include "FileTreeCtrl.h"
#include "afxwin.h"
#include "KThumbListView.h"
#include "BtnSt2.h"
#include "resource.h"


class Exts2
{
public:
	CString ExtDesc;
	vector<CString> Wilds;
public:
	Exts2(CString _ExtDesc) {ExtDesc=_ExtDesc; };
	Exts2() {};
	~Exts2() {};

};

class CKFileDialog2 : public CDialog
{
// Construction
public:
	CKFileDialog2(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CKFileDialog2)
	enum { IDD = IDD_TPACKSHAD_DIALOG };
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKFileDialog2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

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

	vector<Exts2> XTensions;
	
	// Generated message map functions
	//{{AFX_MSG(CKFileDialog2)
    afx_msg void OnBnClickedDetails();
    afx_msg void OnBnClickedList();
    afx_msg void OnBnClickedLargeicons();
    afx_msg void OnBnClickedNewrep();
	afx_msg void OnSize(UINT nType, int cx, int cy );
	afx_msg void OnBnClickedBack();
	afx_msg void OnBnClickedUp();
	afx_msg void OnSelchangeExts2();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnGetMinMaxInfo( MINMAXINFO FAR* lpMMI );
	//}}AFX_MSG

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
