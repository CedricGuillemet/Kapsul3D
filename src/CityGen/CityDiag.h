#if !defined(AFX_DUMPINFOS_H__A4074657_9EA2_4EB9_95A3_3A9B19FEB15E__INCLUDED_)
#define AFX_DUMPINFOS_H__A4074657_9EA2_4EB9_95A3_3A9B19FEB15E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DumpInfos.h : header file
//
class Assigns
{
public:
    Assigns(char * _Name,bool _UseBase,bool _UseMedian,bool _UseEnd)
    {
        strcpy(Name,_Name);
        UseBase=_UseBase;
        UseMedian=_UseMedian;
        UseEnd=_UseEnd;
    };

    char Name[32];
    bool UseBase;
    bool UseMedian;
    bool UseEnd;
};
/////////////////////////////////////////////////////////////////////////////
// CCityDiag dialog

class CCityDiag : public CDialog
{
// Construction
public:
	CCityDiag(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCityDiag)
	enum { IDD = IDD_MODDIAG };
	CComboBox	m_MapsDir;
	CStatic	m_ShapeName;
	CButton	m_Median;
	CButton	m_End;
	CButton	m_Base;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCityDiag)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual void OnOK( );
	virtual void OnCancel( );

	// Generated message map functions
	//{{AFX_MSG(CCityDiag)
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnGetshape();
	afx_msg void OnNew();
	afx_msg void OnGenerate();
	afx_msg void OnPlus();
	afx_msg void OnMoins();
	afx_msg void OnBase();
	afx_msg void OnEnd();
	afx_msg void OnMedian();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DUMPINFOS_H__A4074657_9EA2_4EB9_95A3_3A9B19FEB15E__INCLUDED_)
