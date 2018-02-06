#if !defined(AFX_BACKWORLDCAP_H__2E0875F1_D164_442C_B354_2292A9A05CBA__INCLUDED_)
#define AFX_BACKWORLDCAP_H__2E0875F1_D164_442C_B354_2292A9A05CBA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BackWorldCap.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBackWorldCap dialog

class CBackWorldCap : public CDialog
{
// Construction
public:
	CBackWorldCap(CWnd* pParent = NULL);   // standard constructor

	CKScene *m_Scene;
// Dialog Data
	//{{AFX_DATA(CBackWorldCap)
	enum { IDD = IDD_BACKIMAGE };
	CNumSpinCtrl	m_TopSY;
	CNumSpinCtrl	m_TopSX;
	CNumEdit	m_TopSizeY;
	CNumEdit	m_TopSizeX;
	CNumSpinCtrl	m_TopOY;
	CNumSpinCtrl	m_TopOX;
	CNumEdit	m_TopOriginY;
	CNumEdit	m_TopOriginX;
	CSliderCtrl	m_TopOPA;
	CButton	m_TopKeep;
	CNumEdit	m_TopEdit;
	CButton	m_TopBottom;
	CStatic	m_TopAff;
	CNumSpinCtrl	m_SZ;
	CNumSpinCtrl	m_SY;
	CNumSpinCtrl	m_SX;
	CNumEdit	m_SizeZ;
	CNumEdit	m_SizeY;
	CNumEdit	m_SizeX;
	CNumSpinCtrl	m_OZ;
	CNumSpinCtrl	m_OY;
	CNumSpinCtrl	m_OX;
	CNumEdit	m_OriginZ;
	CNumEdit	m_OriginX;
	CNumEdit	m_OriginY;
	CButton	m_LibTopWorld;
	CStatic	m_LibTopSize;
	CStatic	m_LibTopOrigin;
	CButton	m_LibTopOpacity;
	CStatic	m_LibTopFile;
	CButton	m_LibLeftWorld;
	CStatic	m_LibLeftSize;
	CStatic	m_LibLeftOrigin;
	CButton	m_LibLeftOpacity;
	CStatic	m_LibLeftFile;
	CButton	m_LibFrontWorld;
	CStatic	m_LibFrontSize;
	CStatic	m_LibFrontOrigin;
	CButton	m_LibFrontOPA;
	CStatic	m_LibFrontFile;
	CStatic	m_LibCapSize;
	CStatic	m_LibCapOrigin;
	CNumSpinCtrl	m_LeftSY;
	CNumSpinCtrl	m_LeftSX;
	CNumEdit	m_LeftSizeY;
	CNumEdit	m_LeftSizeX;
	CButton	m_LeftRight;
	CNumSpinCtrl	m_LeftOY;
	CNumSpinCtrl	m_LeftOX;
	CNumEdit	m_LeftOriginY;
	CNumEdit	m_LeftOriginX;
	CSliderCtrl	m_LeftOPA;
	CButton	m_LeftKeep;
	CNumEdit	m_LeftEdit;
	CStatic	m_LeftAff;
	CNumSpinCtrl	m_FrontSY;
	CNumSpinCtrl	m_FrontSX;
	CNumEdit	m_FrontSizeY;
	CNumEdit	m_FrontSizeX;
	CNumSpinCtrl	m_FrontOY;
	CNumSpinCtrl	m_FrontOX;
	CNumEdit	m_FrontOriginY;
	CNumEdit	m_FrontOriginX;
	CSliderCtrl	m_FrontOPA;
	CButton	m_FrontKeep;
	CNumEdit	m_FrontEdit;
	CButton	m_FrontBack;
	CStatic	m_FrontAff;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBackWorldCap)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual void OnOK();
	float TopProp,LeftProp,FrontProp;
	// Generated message map functions
	//{{AFX_MSG(CBackWorldCap)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBrowsefront();
	afx_msg void OnBrowseleft();
	afx_msg void OnBrowsetop();
	afx_msg void OnTopkeep();
	afx_msg void OnLeftkeep();
	afx_msg void OnFrontkeep();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BACKWORLDCAP_H__2E0875F1_D164_442C_B354_2292A9A05CBA__INCLUDED_)
