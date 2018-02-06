// TestGLDoc.h : interface of the CDeskDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTGLDOC_H__59CED134_E584_11D1_ACB3_E52ED8AC9002__INCLUDED_)
#define AFX_TESTGLDOC_H__59CED134_E584_11D1_ACB3_E52ED8AC9002__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CDeskDoc : public CDocument
{
protected: // create from serialization only
	CDeskDoc();
	DECLARE_DYNCREATE(CDeskDoc)

// Attributes
public:

// Operations
public:
	CKScene *m_Scene;
	CKRenderer *m_Renderer;
    CKFilePlugin *m_SavePlugin;
	bool IsNamed;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDeskDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDeskDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDeskDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTGLDOC_H__59CED134_E584_11D1_ACB3_E52ED8AC9002__INCLUDED_)
