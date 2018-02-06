// KapsulDoc.cpp : implementation of the CKapsulDoc class
//

#include "stdafx.h"
#include "Kapsul.h"

#include "KapsulDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKapsulDoc

IMPLEMENT_DYNCREATE(CKapsulDoc, CDocument)

BEGIN_MESSAGE_MAP(CKapsulDoc, CDocument)
END_MESSAGE_MAP()


// CKapsulDoc construction/destruction

CKapsulDoc::CKapsulDoc()
{
	// TODO: add one-time construction code here

}

CKapsulDoc::~CKapsulDoc()
{
}

BOOL CKapsulDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CKapsulDoc serialization

void CKapsulDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CKapsulDoc diagnostics

#ifdef _DEBUG
void CKapsulDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CKapsulDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CKapsulDoc commands
