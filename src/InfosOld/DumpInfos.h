#if !defined(AFX_DUMPINFOS_H__A4074657_9EA2_4EB9_95A3_3A9B19FEB15E__INCLUDED_)
#define AFX_DUMPINFOS_H__A4074657_9EA2_4EB9_95A3_3A9B19FEB15E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DumpInfos.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDumpInfos dialog

class CDumpInfos : public CDialog
{
// Construction
public:
	CDumpInfos(CWnd* pParent = NULL);   // standard constructor

	void Info_DumpToFile(LPCSTR szFileName);

// Dialog Data
	//{{AFX_DATA(CDumpInfos)
	enum { IDD = IDD_MODDIAG };
	CEdit	m_ExtEDit;
	CEdit	m_RendererVersion;
	CEdit	m_RendererEdit;
	CEdit	m_VendorEdit;
	CStatic	m_Skeletton;
	CStatic	m_Shape;
	CStatic	m_Segment;
	CStatic	m_ObjVert;
	CStatic	m_ObjFace;
	CStatic	m_Obj;
	CStatic	m_Camera;
	CStatic	m_Bone;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDumpInfos)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDumpInfos)
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnDumpToFile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DUMPINFOS_H__A4074657_9EA2_4EB9_95A3_3A9B19FEB15E__INCLUDED_)
