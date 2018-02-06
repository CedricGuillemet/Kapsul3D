#if !defined CSKYVIEW_H_
#define CSKYVIEW_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestSt.h : header file
//
//#include "Material.h"
#include "headers.h"
/*
	enum InfoField {VENDOR,RENDERER,VERSION,ACCELERATION,EXTENSIONS};
	enum ColorsNumber{INDEXED,THOUSANDS,MILLIONS,MILLIONS_WITH_TRANSPARENCY};
	enum ZAccuracy{NORMAL,ACCURATE};
    */
/////////////////////////////////////////////////////////////////////////////
// CSkyView window

class CSkyView : public CButton
{
// Construction
public:
	CSkyView();
	DECLARE_DYNCREATE(CSkyView)

// Attributes
public:

    //Material *daMat;
    //CTexture *datex;
    CSkyBox *cb;
    Camera *dacam;

// Operations
public:
    Camera *VCam;
// Mouse cursor function
	void SetMouseCursor(HCURSOR mcursor=NULL);
// Attribute retrieval function
	double GetAspectRatio() {return m_dAspectRatio;};
// Rendering Context switching
	void BeginGLCommands();// use to issue GL commands outside Overridables
	void EndGLCommands();// i.e: in menu event handlers, button events handler etc.
// Overridables

    double ngx,ngy;
    bool moving;
    CPoint mypt;
    void PaintProcess();
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkyView)
	protected:
//	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

	// Implementation
public:
	virtual ~CSkyView();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSkyView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

public:
	CDC* m_pCDC;	// WinGDI Device Context
	HGLRC m_hRC;	// OpenGL Rendering Context
	HCURSOR m_hMouseCursor;	// mouse cursor handle for the view
	CRect m_ClientRect;    // client area size
	double m_dAspectRatio;    // aspect
	BOOL m_bInsideDispList;	// Disp List definition semaphore
	BOOL m_bExternGLCall;
	BOOL m_bExternDispListCall;
	BOOL bSetupPixelFormat();

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


#endif