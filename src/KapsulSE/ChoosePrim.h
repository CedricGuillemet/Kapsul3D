#if !defined(AFX_CHOOSEPRIM_H__10EA6F15_566D_47B7_A429_947207FC3EB9__INCLUDED_)
#define AFX_CHOOSEPRIM_H__10EA6F15_566D_47B7_A429_947207FC3EB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChoosePrim.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChoosePrim dialog
//#include "FOToolBar.h"
class CChoosePrim : public CDialog
{
// Construction
public:
	CChoosePrim(CWnd* pParent = NULL);   // standard constructor
	~CChoosePrim();
// Dialog Data
	//{{AFX_DATA(CChoosePrim)
	enum { IDD = IDD_PRIMITIVES };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChoosePrim)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
	public:
		CImageList* m_NormalList,*m_HotList;
		CToolBarCtrl *daParent;
public:
	CButtonST *Buttons[100];
	int nbButtons;
	CBitmap Bmp[100];
	CBitmap bmpg;
	int Indices[100];
	CKScenePlugin *m_Plugins[100];
	BYTE *dump;
public:
	void SetButton(int nbBt);
	void Init(void);
	void SetDaPrime(int nbBt);
	
// Generated message map functions
	//{{AFX_MSG(CChoosePrim)
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	virtual BOOL OnInitDialog();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHOOSEPRIM_H__10EA6F15_566D_47B7_A429_947207FC3EB9__INCLUDED_)
