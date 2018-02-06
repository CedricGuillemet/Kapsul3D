#if !defined(AFX_SKYBOXED_H__296F86F7_2278_46FC_9DAB_03F0923D3D47__INCLUDED_)
#define AFX_SKYBOXED_H__296F86F7_2278_46FC_9DAB_03F0923D3D47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SkyBoxEd.h : header file
//
#include "headers.h"
#include "resource.h"
#include "CSkyView.h"

/////////////////////////////////////////////////////////////////////////////
// CSkyBoxEd dialog

class CSkyBoxEd : public CDialog
{
// Construction
public:
	CSkyBoxEd(CWnd* pParent = NULL);   // standard constructor
    char filename[ _MAX_PATH ];
    char title[ _MAX_PATH ];
    char SkyBoxName[ _MAX_PATH ];
    char SkyBoxTitle[ _MAX_PATH ];
    bool LoadImgFile(void);
    CSkyView csv;
    bool Modified;
// Dialog Data
	//{{AFX_DATA(CSkyBoxEd)
	enum { IDD = IDD_SKYBOX };
	CButton	m_CL2UP;
	CButton	m_CL2RIGHT;
	CButton	m_CL2LEFT;
	CButton	m_CL2FRONT;
	CButton	m_CL2DOWN;
	CButton	m_CL2BACK;
	CStatic	m_SKYBOXNAME;
	CSliderCtrl	m_SLDSKY2;
	CSliderCtrl	m_SLDSKY1;
	CButton	m_CSKY2;
	CButton	m_CSKY1;
	CButton	m_SKY2;
	CButton	m_SKY1;
	CButton	m_ABACK;
	CButton	m_AFRONT;
	CButton	m_ARIGHT;
	CButton	m_ALEFT;
	CButton	m_ADOWN;
	CButton	m_AUP;
	CButton	m_CL1BACK;
	CButton	m_CL1FRONT;
	CButton	m_CL1RIGHT;
	CButton	m_CL1LEFT;
	CButton	m_CL1DOWN;
	CButton	m_CL1UP;
	CButton	m_L2BACK;
	CButton	m_L2FRONT;
	CButton	m_L2RIGHT;
	CButton	m_L2LEFT;
	CButton	m_L2DOWN;
	CButton	m_L2UP;
	CButton	m_L1BACK;
	CButton	m_L1FRONT;
	CButton	m_L1RIGHT;
	CButton	m_L1LEFT;
	CButton	m_L1DOWN;
	CButton	m_L1UP;
	CStatic	m_BackName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkyBoxEd)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSkyBoxEd)
	afx_msg void OnLoad();
	afx_msg void OnSave();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnL1UP();
	afx_msg void OnL1DOWN();
	afx_msg void OnL1LEFT();
	afx_msg void OnL1RIGHT();
	afx_msg void OnL1FRONT();
	afx_msg void OnL1BACK();
	afx_msg void OnL2UP();
	afx_msg void OnL2DOWN();
	afx_msg void OnL2LEFT();
	afx_msg void OnL2RIGHT();
	afx_msg void OnL2FRONT();
	afx_msg void OnL2BACK();
	afx_msg void OnCL1UP();
	afx_msg void OnCL1DOWN();
	afx_msg void OnCL1LEFT();
	afx_msg void OnCL1RIGHT();
	afx_msg void OnCL1FRONT();
	afx_msg void OnCL1BACK();
	afx_msg void OnCL2UP();
	afx_msg void OnCL2DOWN();
	afx_msg void OnCL2LEFT();
	afx_msg void OnCL2RIGHT();
	afx_msg void OnCL2FRONT();
	afx_msg void OnCL2BACK();
	afx_msg void OnAUP();
	afx_msg void OnADOWN();
	afx_msg void OnALEFT();
	afx_msg void OnARIGHT();
	afx_msg void OnAFRONT();
	afx_msg void OnABACK();
	afx_msg void OnCSKY2();
	afx_msg void OnCSKY1();
	afx_msg void OnSky1();
	afx_msg void OnSky2();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnNew();
	virtual void OnOK();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKYBOXED_H__296F86F7_2278_46FC_9DAB_03F0923D3D47__INCLUDED_)
