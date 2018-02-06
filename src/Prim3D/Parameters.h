#if !defined(AFX_PARAMETERS_H__6007E6E5_B5C9_4D80_B8CE_CE09355E2409__INCLUDED_)
#define AFX_PARAMETERS_H__6007E6E5_B5C9_4D80_B8CE_CE09355E2409__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Parameters.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CParameters dialog
class CKPluginPrim3D;
class CParameters : public CDialog
{
    DECLARE_DYNCREATE(CParameters)

// Construction
public:
	CParameters(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CParameters)
	enum { IDD = IDD_MODDIAG3 };
	CNumSpinCtrl	m_Spin3;
	CNumEdit	m_Edit3;
	CNumSpinCtrl	m_Spin2;
	CNumSpinCtrl	m_Spin1;
	CNumEdit	m_Edit2;
	CNumEdit	m_Edit1;
	CButton	m_AutoUV;
	//}}AFX_DATA

	void SetAutoUV(bool _checked);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParameters)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
    
public:
    void SetParams(bool B1Enabled,bool B2Enabled,float B1Min,float B1Max,float B2Min,float B2Max,
		float B1Delta,float B2Delta,float B1Pos,float B2Pos,
		bool B3Enabled=false,float B3Min=1,float B3Max=10,float B3Delta=1,float B3Pos=1);
	CKPluginPrim3D *m_Plugin;
// Implementation
protected:
	virtual void OnOK( );
	virtual void OnCancel( );

	// Generated message map functions
	//{{AFX_MSG(CParameters)
	virtual BOOL OnInitDialog();
	afx_msg void OnAutouv();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARAMETERS_H__6007E6E5_B5C9_4D80_B8CE_CE09355E2409__INCLUDED_)
