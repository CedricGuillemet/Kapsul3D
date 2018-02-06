#if !defined(AFX_DUMPINFOS_H__A4074657_9EA2_4EB9_95A3_3A9B19FEB15E__INCLUDED_)
#define AFX_DUMPINFOS_H__A4074657_9EA2_4EB9_95A3_3A9B19FEB15E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DumpInfos.h : header file
//
#include "objInspector\ObjectInspector.h"

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
// CEntPlg dialog
#include "resource.h"

class CEntPlg : public CDialog
{
// Construction
public:
	CEntPlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEntPlg)
	enum { IDD = IDD_MODDIAG };
	CComboBox	m_EntsTypes;
	
	//}}AFX_DATA

CObjectInspector m_Oi;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEntPlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
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

	virtual void OnOK( );
	virtual void OnCancel( );
	
	void UpdateControl();
	void ResetAllValues(void);
	void BuildXmlProps(CString &EntProp);
public:
	void UpdatePropList(CEntityType *daTyp);
	void UpdatePropsFromEntity(void);
	void OnNotifyProp(void);
	CEntityType* FindEntityTypeByName(char *EntName,int &ListNb);

	// Generated message map functions
	//{{AFX_MSG(CEntPlg)
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchangeCb1();
	afx_msg void OnNotifyProp(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DUMPINFOS_H__A4074657_9EA2_4EB9_95A3_3A9B19FEB15E__INCLUDED_)
