#if !defined(AFX_MAPLIGHTEDIT_H__90477D0E_CE2D_4178_B678_3493D40795FB__INCLUDED_)
#define AFX_MAPLIGHTEDIT_H__90477D0E_CE2D_4178_B678_3493D40795FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MapLightEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMapLightEdit dialog

class CMapLightEdit : public CDialog
{
// Construction
public:
	CMapLightEdit(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMapLightEdit)
	enum { IDD = IDD_MAPEDIT };
	CButton	m_WaterBmp;
	CSliderCtrl	m_Sun;
	CSliderCtrl	m_Light;
	CSliderCtrl	m_Angle;
	CButton	m_Detail;
	CSliderCtrl	m_Slop;
	CSliderCtrl	m_Slid8;
	CSliderCtrl	m_Slid4;
	CSliderCtrl	m_Slid7;
	CSliderCtrl	m_Slid3;
	CSliderCtrl	m_Slid6;
	CSliderCtrl	m_Slid2;
	CSliderCtrl	m_Slid5;
	CButton	m_Tex8;
	CButton	m_Tex4;
	CButton	m_Tex7;
	CButton	m_Tex3;
	CButton	m_Tex6;
	CButton	m_Tex2;
	CButton	m_Tex5;
	CScrollBar	m_ScrollX2;
	CScrollBar	m_ScrollY2;
	CScrollBar	m_ScrollX1;
	CScrollBar	m_ScrollY1;
	CSliderCtrl	m_Slid1;
	CButton	m_Tex1;
	//}}AFX_DATA

    void GenerateTexMap(void);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapLightEdit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMapLightEdit)
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnBttex1();
	afx_msg void OnBttex2();
	afx_msg void OnBttex3();
	afx_msg void OnBttex4();
	afx_msg void OnBttex5();
	afx_msg void OnBttex6();
	afx_msg void OnBttex7();
	afx_msg void OnBttex8();
	afx_msg void OnPaint();
	afx_msg void OnReleasedcaptureSlop(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSun(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureLight(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDetail();
	afx_msg void OnReleasedcaptureAngle(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBlurlight();
	afx_msg void OnSavemap();
	afx_msg void OnWater();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPLIGHTEDIT_H__90477D0E_CE2D_4178_B678_3493D40795FB__INCLUDED_)
