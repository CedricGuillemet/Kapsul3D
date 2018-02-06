#pragma once
#include "afxwin.h"


// CObjProps dialog

class CObjProps : public CDialog
{
	DECLARE_DYNAMIC(CObjProps)

public:
	CObjProps(CWnd* pParent = NULL);   // standard constructor
	virtual ~CObjProps();

// Dialog Data
	enum { IDD = IDD_OBJPROPS };
	CKMesh *m_Mesh;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CEdit m_EditName;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedSetname();
	virtual BOOL OnInitDialog();
};
