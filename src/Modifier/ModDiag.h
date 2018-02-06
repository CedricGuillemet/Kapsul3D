#if !defined(AFX_MODDIAG_H__F1A665BE_34CA_40BB_9A39_2E614FC06164__INCLUDED_)
#define AFX_MODDIAG_H__F1A665BE_34CA_40BB_9A39_2E614FC06164__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModDiag.h : header file
//
class CKPluginModifier;
#include "ModModifier.h"

/////////////////////////////////////////////////////////////////////////////
// CModDiag dialog

class CModDiag : public CDialog
{
// Construction
public:
	CModDiag(CWnd* pParent = NULL);   // standard constructor
	CKPluginModifier *m_Plugin;
// Dialog Data
	//{{AFX_DATA(CModDiag)
	enum { IDD = IDD_MODDIAG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModDiag)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
public:
    void UnSetPlugin(void);
	void HideAllPages();
// Implementation
protected:

	virtual void OnOK( );
	virtual void OnCancel( );
	// Generated message map functions
	//{{AFX_MSG(CModDiag)
	virtual BOOL OnInitDialog();
	afx_msg void OnObsp();
	afx_msg void OnOdivide();
	afx_msg void OnOexplode();
	afx_msg void OnOextrud();
	afx_msg void OnOfractalize();
	afx_msg void OnOlathe();
	afx_msg void OnOnormals();
	afx_msg void OnOpath();
	afx_msg void OnOspherize();
	afx_msg void OnOtesselate();
	afx_msg void OnOuvmapping();
	afx_msg void OnLightmap();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODDIAG_H__F1A665BE_34CA_40BB_9A39_2E614FC06164__INCLUDED_)
