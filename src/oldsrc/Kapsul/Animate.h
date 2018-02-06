#if !defined(AFX_ANIMATE_H__35AA10BA_4FC1_45B6_8FF8_F468EF7AC879__INCLUDED_)
#define AFX_ANIMATE_H__35AA10BA_4FC1_45B6_8FF8_F468EF7AC879__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Animate.h : header file
//
#include "NbFrames.h"
/////////////////////////////////////////////////////////////////////////////
// CAnimate dialog

class CAnimate : public CDialog
{
// Construction
public:
	CAnimate(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAnimate)
	enum { IDD = IDD_ANIM };
	CNumSpinCtrl	m_FrameSpin;
	CNumEdit	m_FrameNb;
	CStatic	m_Slash;
	CButton	m_KillFrame;
	CSliderCtrl	m_Slider;
	CButton	m_PrevKey;
	CButton	m_PrevFrame;
	CButton	m_Play;
	CButton	m_Pause;
	CButton	m_NextKey;
	CButton	m_NextFrame;
	CButton	m_NbFrames;
	//}}AFX_DATA

    bool IsPlaying;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnimate)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual void OnOK( );
	virtual void OnCancel( );

    CNbFrames m_nbf;
	// Generated message map functions
	//{{AFX_MSG(CAnimate)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnPrevframe();
	afx_msg void OnPlaystop();
	afx_msg void OnPause();
	afx_msg void OnNextframe();
	afx_msg void OnKillkf();
	afx_msg void OnPrevkey();
	afx_msg void OnNextkey();
	afx_msg void OnNbframes();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANIMATE_H__35AA10BA_4FC1_45B6_8FF8_F468EF7AC879__INCLUDED_)
