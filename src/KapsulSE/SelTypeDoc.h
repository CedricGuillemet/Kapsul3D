#pragma once
#include "afxwin.h"
#include "resource.h"

// CSelTypeDoc dialog

class CSelTypeDoc : public CDialog
{
	DECLARE_DYNAMIC(CSelTypeDoc)

public:
	CSelTypeDoc(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSelTypeDoc();

// Dialog Data
	enum { IDD = IDD_SELTYPEDOC };
	int TypeDoc;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CButton m_Desk;
	CButton m_Script;
	afx_msg void OnBnClickedDesk();
	afx_msg void OnBnClickedScript();
};
