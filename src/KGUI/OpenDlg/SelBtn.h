/////////////////////////////////////////////////////////////////////////////
// SelBtn.h : header file
// 
// Windows 2000 / Office 2000 style file dialog.
// 
// This WILL work on Win 95 / 98 / NT 4 / NT 5 (2000) / WinME
// 
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SELBTN_H__CAC12AC3_D491_11D3_8094_005004D6CF90__INCLUDED_)
#define AFX_SELBTN_H__CAC12AC3_D491_11D3_8094_005004D6CF90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelBtn.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// BXSelBtn window

class BXSelBtn : public CWnd
{
// Construction
public:
	BXSelBtn();

// Attributes
public:
  BOOL Create( LPCTSTR lpszCaption, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CImageList* pImage, UINT nPos );

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(BXSelBtn)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetState(BOOL bPressed);
	BOOL SetImage(UINT nId, COLORREF crMask);
	virtual ~BXSelBtn();
	CBitmap      m_btnImage;
	CImageList*   m_pIL;
	BOOL         m_bLoaded;
	BITMAP       m_bm;
	CWnd*        m_pParentWnd;
	BOOL		   m_Pressed;
	UINT         m_nPos;
	CString      m_strText;
	UINT         m_nID;

	BOOL			m_MouseOnButton;
	BOOL			m_DrawPressed;
	BOOL			m_Enabled;

	// Generated message map functions
protected:
	//{{AFX_MSG(BXSelBtn)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELBTN_H__CAC12AC3_D491_11D3_8094_005004D6CF90__INCLUDED_)
