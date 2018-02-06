#if !defined(AFX_ENTITYNAME_H__D31714AA_2BD9_42E6_9B5D_8FE007147F2F__INCLUDED_)
#define AFX_ENTITYNAME_H__D31714AA_2BD9_42E6_9B5D_8FE007147F2F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EntityName.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEntityName dialog

class CEntityName : public CDialog
{
// Construction
public:
	CEntityName(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEntityName)
	enum { IDD = IDD_ENTITYNAME };
	CEdit	m_Name;
	//}}AFX_DATA

    char Name[32];
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEntityName)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEntityName)
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENTITYNAME_H__D31714AA_2BD9_42E6_9B5D_8FE007147F2F__INCLUDED_)
