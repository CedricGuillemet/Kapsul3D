#if !defined(AFX_OGLVIEWER_H__9F285C17_DDA4_425D_92D8_99EEF826DB57__INCLUDED_)
#define AFX_OGLVIEWER_H__9F285C17_DDA4_425D_92D8_99EEF826DB57__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OglViewer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COglViewer window

class COglViewer : public CWnd
{
// Construction
public:
	COglViewer();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COglViewer)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COglViewer();

	// Generated message map functions
protected:
	//{{AFX_MSG(COglViewer)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnEnterIdle(UINT nWhy, CWnd* pWho);
	//}}AFX_MSG
	CDC* m_pCDC;	// WinGDI Device Context
	HGLRC m_hRC;	// OpenGL Rendering Context
	HCURSOR m_hMouseCursor;	// mouse cursor handle for the view
	CRect m_ClientRect;    // client area size
	double m_dAspectRatio;    // aspect
	BOOL m_bInsideDispList;	// Disp List definition semaphore
	BOOL m_bExternGLCall;
	BOOL m_bExternDispListCall;
    double ngx,ngy;
    bool moving;
    CPoint mypt;
    bool IsAvancing;

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OGLVIEWER_H__9F285C17_DDA4_425D_92D8_99EEF826DB57__INCLUDED_)
