#if !defined(AFX_MAPPING_H__E6FEFE6F_8259_4F90_8B70_B36D95DA8752__INCLUDED_)
#define AFX_MAPPING_H__E6FEFE6F_8259_4F90_8B70_B36D95DA8752__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Mapping.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMapping dialog

class CMapping : public CDialog
{
// Construction
public:
	CMapping(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMapping)
	enum { IDD = IDD_MAPPING };
	CSliderCtrl	m_SlidV;
	CSliderCtrl	m_SlidU;
	CStatic	m_TextV;
	CStatic	m_TextU;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapping)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	void SetTextV(float Value);
	void SetTextU(float Value);


// Implementation
protected:
	virtual void OnOK( );
	virtual void OnCancel( );

	// Generated message map functions
	//{{AFX_MSG(CMapping)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPPING_H__E6FEFE6F_8259_4F90_8B70_B36D95DA8752__INCLUDED_)
