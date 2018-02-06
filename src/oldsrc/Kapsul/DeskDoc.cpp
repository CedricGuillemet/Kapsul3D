// TestGLDoc.cpp : implementation of the CDeskDoc class
//

#include "stdafx.h"
//#include "TestGL.h"
#include "headers.h"
//#include "memmgr/mmgr.h"

#include "DeskDoc.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern LibContainer *KLibs;
extern OGLView *View;
/////////////////////////////////////////////////////////////////////////////
// CDeskDoc

IMPLEMENT_DYNCREATE(CDeskDoc, CDocument)

BEGIN_MESSAGE_MAP(CDeskDoc, CDocument)
	//{{AFX_MSG_MAP(CDeskDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDeskDoc construction/destruction

CDeskDoc::CDeskDoc()
{
	// TODO: add one-time construction code here
	dk=new Desk(NULL,NULL);

	dk->cSel=new Selection(dk,View);
	SetModifiedFlag(true);

    /*
	dk->AddCam();
	dk->NextCam->SetSource(Vertex(64,64,64));
	dk->NextCam->SetDest(Vertex(128,128,128));
*/
	IsNamed=false;
}

CDeskDoc::~CDeskDoc()
{
	delete dk;
}

BOOL CDeskDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

    
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDeskDoc serialization

void CDeskDoc::Serialize(CArchive& ar)
{
	int i;

	if (ar.IsStoring())
	{

        //KLibs->WriteGen[ar.GetFile()->IsKindOf()-1]->Write(dk,ar.GetFile()->GetFilePath( ).GetBuffer (MAX_PATH));

	}
	else
	{
		for (i=0;i<KLibs->nb2FilesLib;i++)
		{
			if (KLibs->FilesLib[i]->Read(dk,ar.GetFile()->GetFilePath( ).GetBuffer (MAX_PATH)))
			{
                genSave=KLibs->FilesLib[i];
				i=KLibs->nb2FilesLib;
				SetTitle(ar.GetFile()->GetFilePath( ).GetBuffer (MAX_PATH));
				//HasGood=true;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDeskDoc diagnostics

#ifdef _DEBUG
void CDeskDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDeskDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDeskDoc commands
