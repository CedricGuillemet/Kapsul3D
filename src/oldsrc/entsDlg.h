// entsDlg.h : header file
//

#if !defined(AFX_ENTSDLG_H__E6250C55_05AE_407A_9946_DCDACBF8B2D2__INCLUDED_)
#define AFX_ENTSDLG_H__E6250C55_05AE_407A_9946_DCDACBF8B2D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <vector>
using namespace std;

class CEntityParam
{
public :
	CEntityParam(char *daName,int daType)
	{
		strcpy(Name,daName);
		Type=daType;
	};
	~CEntityParam() {};

	char Name[64];
	int Type;
};


class CEntityGroup
{
public :
	CEntityGroup(char *daName)
	{
		strcpy(Name,daName);
	};
	~CEntityGroup() {};

	char Name[64];
	vector<CEntityParam*> m_Params;
};


class CEntityType
{
public :
	CEntityType(char *daName)
	{
		//Name=new char [64]; 
		strcpy(Name,daName);
	};
	~CEntityType() {};

	char Name[64];
	vector<CEntityGroup*> m_Groups;
};


/////////////////////////////////////////////////////////////////////////////
// CEntsDlg dialog
#include "objInspector\ObjectInspector.h"

class CEntsDlg : public CDialog
{
// Construction
public:
	CEntsDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CEntsDlg)
	enum { IDD = IDD_ENTS_DIALOG };
	CEdit	m_Edit;
	CComboBox m_List;
	CObjectInspector m_OI;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEntsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CString		m_szProp[20];
	float		m_fProp[20];
	int			m_iProp[20];
	COLORREF    m_clProp[20];
	CString		m_cbProp[20];
	CStringList m_cbListProp[20];

	

	CString     m_szPropertyHeader;
	CString     m_szValueHeader;
	CString		m_szBorderStyle;
	CStringList m_slBorderStyles;
	bool        m_bHotTrack;
	bool		m_b3dFocus;
	COLORREF    m_clBackColor;
	COLORREF    m_clVTColor;
	COLORREF    m_clPTColor;
	COLORREF    m_clGridLineColor;
	COLORREF    m_clFocusLineColor;

	int         m_nMinPropertyColWidth;
	int         m_nMinValueColWidth;
	int         m_nStyle;
public:
	void UpdatePropList(CEntityType *daTyp);
	void UpdateControl();
	void ResetAllValues(void);
	void BuildXmlProps(CString &EntProp);
	// Generated message map functions
	//{{AFX_MSG(CEntsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeCb1();
	afx_msg void OnNotifyProp(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENTSDLG_H__E6250C55_05AE_407A_9946_DCDACBF8B2D2__INCLUDED_)

