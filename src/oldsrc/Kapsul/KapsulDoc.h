// KapsulDoc.h : interface of the CKapsulDoc class
//


#pragma once

class CKapsulDoc : public CDocument
{
protected: // create from serialization only
	CKapsulDoc();
	DECLARE_DYNCREATE(CKapsulDoc)

// Attributes
public:

// Operations
public:

// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CKapsulDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


