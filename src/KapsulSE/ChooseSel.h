#if !defined(AFX_CHOOSESEL_H__10EA6F15_566D_47B7_A429_947207FC3EB9__INCLUDED_)
#define AFX_CHOOSESEL_H__10EA6F15_566D_47B7_A429_947207FC3EB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChoosePrim.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChooseSel dialog
//#include "FOToolBar.h"
class CChooseSel : public CDialog
{
// Construction
public:
	CChooseSel(CWnd* pParent = NULL);   // standard constructor
	~CChooseSel();
// Dialog Data
	//{{AFX_DATA(CChooseSel)
	enum { IDD = IDD_SELECTION };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChooseSel)
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
	//{{AFX_MSG(CChooseSel)
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
