#if !defined(AFX_HEIGHTDESIGN_H__8AF5AAB1_7B87_497A_8D70_3800B2B2D5F2__INCLUDED_)
#define AFX_HEIGHTDESIGN_H__8AF5AAB1_7B87_497A_8D70_3800B2B2D5F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HeightDesign.h : header file
//
#include "AffImage.h"
#include "resource.h"
#include "PaintZone.h"
#include "kSlid.h"
/////////////////////////////////////////////////////////////////////////////
// CHeightDesign dialog

class CHeightDesign : public CDialog
{
// Construction
public:
	CHeightDesign(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHeightDesign)
	enum { IDD = IDD_HEIGHTDESIGN };
	CSliderCtrl	m_WaterLevel;
	CSliderCtrl	m_Strength;
	CPaintZone	m_PaintZone;
	CScrollBar	m_ScrollX;
	CScrollBar	m_ScrollY;
	//}}AFX_DATA
    CAffImage m_Height;
    CKSlid   m_dbls;
	void Init();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHeightDesign)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHeightDesign)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnGenerate();
	afx_msg void OnGenerate2();
	afx_msg void OnGenerate3();
	afx_msg void OnReleasedcaptureWater(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBlurlightmap2();
	afx_msg void OnImport();
	afx_msg void OnExport();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HEIGHTDESIGN_H__8AF5AAB1_7B87_497A_8D70_3800B2B2D5F2__INCLUDED_)
