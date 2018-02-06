#if !defined(AFX_CHOOSEMODE_H__10EA6F15_566D_47B7_A429_947207FC3EB9__INCLUDED_)
#define AFX_CHOOSEMODE_H__10EA6F15_566D_47B7_A429_947207FC3EB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChoosePrim.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChooseMode dialog
//#include "FOToolBar.h"
class CChooseMode : public CDialog
{
// Construction
public:
	CChooseMode(CWnd* pParent = NULL);   // standard constructor
	~CChooseMode();
// Dialog Data
	//{{AFX_DATA(CChooseMode)
	enum { IDD = IDD_MODE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChooseMode)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
	public:
		CImageList* m_NormalList,*m_HotList;
		CToolBarCtrl *daParent;
protected:
	CButtonST *Buttons[4];
	CBitmap Bmp[4];
	CBitmap bmpg;
	BYTE *dump;
public:
	void SetButton(int nbBt);

	
// Generated message map functions
	//{{AFX_MSG(CChooseMode)
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
