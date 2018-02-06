// TVTestDlg.h : header file
//

#if !defined(AFX_TVTESTDLG_H__1C43C720_F407_437A_A801_D38E6E4ADCC8__INCLUDED_)
#define AFX_TVTESTDLG_H__1C43C720_F407_437A_A801_D38E6E4ADCC8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "mltitree.h"
#include "ProjectTree.h"
#include "TScrollDlg.h"
#include "MatBrowser.h"
#include "BtnSt2.h"
#include "TweakUV.h"
#include <vector>
using std::vector;
#include "CKProject.h"

/////////////////////////////////////////////////////////////////////////////
// CTVTestDlg dialog

class CTVTestDlg : public CDialog
{
// Construction
public:
	CTVTestDlg(CWnd* pParent = NULL);	// standard constructor
	void UpdateHiding(void);
	void UpdatePrefabTree(void);
	CKScene *m_Scene;


	// Project
	//CKProject m_Prj;

// Dialog Data
	//{{AFX_DATA(CTVTestDlg)
	enum { IDD = IDD_TVTEST_DIALOG };
	CStatic	m_TweakUV;
	CStatic m_LayerString;
	CButtonST2	m_HideTweakUV;
	CKProject m_Project;
	CMultiTree	m_Prefabs;
	CButton	m_ClickApplyPoly;
	CButton	m_ClickApplyObject;
	CMultiTree	m_Hierar;
	CButtonST2 m_Tabs1;
	CButtonST2 m_Tabs2;
	CButtonST2 m_Tabs3;
	CButtonST2 m_Tabs4;
	CButtonST2 m_Tabs5;
	CButton m_Layer1;
	CButton m_Layer2;
	CButton m_Layer3;
	CButton m_Layer4;
	//}}AFX_DATA

	void ShowMappingTool(bool ShowIt);
	CTScrollDlg		m_cDialog;
	CMatBrowser		m_Browser;
	CTweakUV		m_TweakUVDiag;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTVTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

	void RecCalcBone(CKBone *daBone,HTREEITEM &hItem);
	void UpdateHierTree(CKScene *_Scene);
	bool RecurseHide(HTREEITEM dait,bool Hidden);
	bool SetItemHiding(HTREEITEM dait,bool Hidden);
	
// Implementation
protected:

	HICON m_hIcon;
	CImageList imgl,imgpref,prjList;
	CBitmap bmp1;
	
	void UpdateDeskTree(void);
	HTREEITEM daRoot;
	bool p1Hiden,p2Hiden;
	bool RecurseFindPrefabs(CTreeCtrl *pTree,HTREEITEM Parent,CString Path,CString DispPath);
public:
	// Generated message map functions
	//{{AFX_MSG(CTVTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSize(UINT nType,int cx,int cy);
	afx_msg LRESULT OnSelChanged(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBtTab1Clicked();
	afx_msg void OnBtTab2Clicked();
	afx_msg void OnBtTab3Clicked();
	afx_msg void OnBtTab4Clicked();
	afx_msg void OnBtTab5Clicked();
	afx_msg void OnClickapplyobj();
	afx_msg void OnClickapplypoly();
	afx_msg void OnLayer1();
	afx_msg void OnLayer2();
	afx_msg void OnLayer3();
	afx_msg void OnLayer4();
	afx_msg void OnHidetweakuv();
	//}}AFX_MSG
	afx_msg LRESULT OnWmUpdate(WPARAM wParam, LPARAM lParam) ;
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TVTESTDLG_H__1C43C720_F407_437A_A801_D38E6E4ADCC8__INCLUDED_)
