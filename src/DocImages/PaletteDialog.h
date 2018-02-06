#if !defined(AFX_PALETTEDIALOG_H__71BAB04D_6148_4371_8DB2_8726507A65B0__INCLUDED_)
#define AFX_PALETTEDIALOG_H__71BAB04D_6148_4371_8DB2_8726507A65B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PaletteDialog.h : header file
//
#include "SnapDialog.h"

#include "GTColorSelectorWnd.h"
#include "GTColorWellWnd.h"
#include "GTColorSliderWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CPaletteDialog dialog

class CPaletteDialog : public CSnapDialog
{
// Construction
public:
	CPaletteDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPaletteDialog)
	enum { IDD = IDD_PALETTE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaletteDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	GTColorSelectorWnd m_wndBulleted;
	GTColorWellWnd m_wndWell;
	GTColorSliderWnd m_wndSlider;

	// Generated message map functions
	//{{AFX_MSG(CPaletteDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	afx_msg void OnRadio4();
	afx_msg void OnRadio5();
	afx_msg void OnRadio6();
	afx_msg void OnGColorChanged(UINT wParam, LONG lParam);
	//}}AFX_MSG
	LRESULT OnColorChanged(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PALETTEDIALOG_H__71BAB04D_6148_4371_8DB2_8726507A65B0__INCLUDED_)
