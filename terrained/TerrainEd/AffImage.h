#if !defined(AFX_AFFIMAGE_H__BCCBC2A7_F61B_4B21_B5B1_9DFF52C5220E__INCLUDED_)
#define AFX_AFFIMAGE_H__BCCBC2A7_F61B_4B21_B5B1_9DFF52C5220E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AffImage.h : header file
//
#include <headers.h>
/////////////////////////////////////////////////////////////////////////////
// CAffImage window
#include "Terra.h"
class CAffImage : public CWnd
{
// Construction
public:
	CAffImage();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAffImage)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAffImage();
    CTerra *m_img;
    int PosY,PosX;
    CPaintZone *m_Zone;
    float m_Strengh;
    bool m_Down;
    int daFact;
    LPBITMAPINFOHEADER BmDest;
    void PaintIt(CPoint point,int Factor);
	// Generated message map functions
protected:
	//{{AFX_MSG(CAffImage)
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AFFIMAGE_H__BCCBC2A7_F61B_4B21_B5B1_9DFF52C5220E__INCLUDED_)
