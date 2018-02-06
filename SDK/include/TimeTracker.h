#if !defined(AFX_TIMETRACKER_H__95B7C8B8_49C4_46F5_A7D0_DFDEB97AFBFF__INCLUDED_)
#define AFX_TIMETRACKER_H__95B7C8B8_49C4_46F5_A7D0_DFDEB97AFBFF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TimeTracker.h : header file
//
#include "Memdc.h"
typedef struct 
{
    double Start;
    double Length;
    int Type;
    int Row;
} TimeEntry;

/////////////////////////////////////////////////////////////////////////////
// CTimeTracker window

class __declspec( dllexport ) CTimeTracker : public CWnd
{
// Construction
public:
	CTimeTracker();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimeTracker)
	public:
	virtual BOOL Create(const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTimeTracker();

	// Generated message map functions


        double Factor;
    double StartTime;
    double TimePos;
    int DecalX;

    int nbRows;
    CString Rows[10];
    bool MovingPos;
    bool MovingTe;
    bool StartStretch;
    bool EndStretch;
    int teInd;
    POINT Remem;

    TimeEntry te[10];
    int nb2te;

    int Right,Down;
    CMemDC * myDC;

protected:
    void PaintKey(double Start,double Length,int y,int Type);
	//{{AFX_MSG(CTimeTracker)
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIMETRACKER_H__95B7C8B8_49C4_46F5_A7D0_DFDEB97AFBFF__INCLUDED_)
