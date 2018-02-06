#if !defined(AFX_COOLBTN_H__3A90681F_CE5F_11D3_808C_005004D6CF90__INCLUDED_)
#define AFX_COOLBTN_H__3A90681F_CE5F_11D3_808C_005004D6CF90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CoolBtn.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// BXCoolBtn window


class BXCoolBtn : public CButton
{
// Construction
public:
	BXCoolBtn();
  BOOL Create( LPCTSTR lpszCaption, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID );
  BOOL SetButtonImage(UINT nResourceId, COLORREF crMask);
  BOOL AddMenuItem(UINT nMenuId,const CString strMenu, UINT nFlags);
  BOOL AddMenuSeperator();

// Attributes
public:
  CMenu        m_menu;
  CBitmap      m_btnImage;
  CImageList   m_IL;
  BOOL         m_bPushed;
  BOOL         m_bMenuPushed;
  BOOL         m_bMenuLoaded;
  BOOL         m_bLoaded;
  BITMAP       m_bm;
  CWnd*        m_pParentWnd;
  int          m_nID;


// Operations
public:
protected:
  void DrawArrow(CDC* pDC,CPoint ArrowTip);
  BOOL HitMenuBtn(CPoint point);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(BXCoolBtn)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~BXCoolBtn();

	// Generated message map functions
protected:
	//{{AFX_MSG(BXCoolBtn)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSysColorChange();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COOLBTN_H__3A90681F_CE5F_11D3_808C_005004D6CF90__INCLUDED_)
