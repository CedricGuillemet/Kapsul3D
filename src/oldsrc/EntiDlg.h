// EntiDlg.h : header file
//

#if !defined(AFX_ENTIDLG_H__E9148169_8516_419B_8745_7694DB064C7E__INCLUDED_)
#define AFX_ENTIDLG_H__E9148169_8516_419B_8745_7694DB064C7E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "EntityType.h"
#include "EntityProp.h"
/////////////////////////////////////////////////////////////////////////////
// CEntiDlg dialog

class CEntiDlg : public CDialog
{
// Construction
public:
	CEntiDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CEntiDlg)
	enum { IDD = IDD_ENTITYED };
	CEdit	m_Vals;
	CListBox	m_ListProps;
	CComboBox	m_EntType;
    CButton m_TypeEdit;
    CButton m_TypeCombo;
    CButton m_TypeFile;
    CButton m_TypeTrueFalse;
    CButton m_TypeColorPicker;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEntiDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
    CEntityType *CurEnt;
    CEntityProp *CurProp;

	// Generated message map functions
	//{{AFX_MSG(CEntiDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAddent();
	afx_msg void OnDelent();
	afx_msg void OnRenent();
	afx_msg void OnDestroy();
	afx_msg void OnAdd();
	afx_msg void OnDel();
	afx_msg void OnRen();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnSelchangeListprops();
	afx_msg void OnButton1();
	afx_msg void OnTypecolorpicker();
	afx_msg void OnTypecombo();
	afx_msg void OnTypeedit();
	afx_msg void OnTypefile();
	afx_msg void OnTypetruefalse();
	afx_msg void OnKillfocusCbvals();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENTIDLG_H__E9148169_8516_419B_8745_7694DB064C7E__INCLUDED_)
