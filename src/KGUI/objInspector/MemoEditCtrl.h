#if !defined(AFX_MEMOEDITCTRL_H__1E6B239E_D5A6_443F_BD6D_C5C4ECC4AFF3__INCLUDED_)
#define AFX_MEMOEDITCTRL_H__1E6B239E_D5A6_443F_BD6D_C5C4ECC4AFF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MemoEditCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMemoEditCtrl window

class CMemoEditCtrl : public CEdit
{
// Construction
public:
	CMemoEditCtrl();

// Attributes
public:

private:
	CRect            m_rcButtonRect;
    int              m_nButtonState;        
    int              m_nButtonWidth;      

// Operations
public:
	void DrawButton(int nButtonState = 0); 
    void DrawDots(CDC *pDC, COLORREF CR, int nOffset = 0); 
	void Redraw(BOOL Flat);
    BOOL ScreenPointInButtonRect(CPoint point); 
	void ButtonClicked();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMemoEditCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMemoEditCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMemoEditCtrl)
    afx_msg void OnEnable(BOOL bEnable);
    afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
    afx_msg void OnNcPaint();
	afx_msg void OnLButtonUp(UINT nFlags,CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags,CPoint point);
	afx_msg void OnMouseMove(UINT nFlags,CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEMOEDITCTRL_H__1E6B239E_D5A6_443F_BD6D_C5C4ECC4AFF3__INCLUDED_)
