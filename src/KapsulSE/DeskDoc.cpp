// TestGLDoc.cpp : implementation of the CDeskDoc class
//

#include "stdafx.h"
//#include "TestGL.h"
#include "Kapsul3D.h"
//#include "memmgr/mmgr.h"

#include "DeskDoc.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CKPluginManager *GKPlugins;
//extern CKDrawScene *GDrawScene;
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
	m_Scene=new CKScene();
	m_Renderer=GKPlugins->CreateRenderInterface(m_Scene);
	m_Scene->SetRenderer(m_Renderer);
	m_Scene->InitDefaultTexture();

	SetModifiedFlag(true);
	m_SavePlugin=NULL;

    /*
	m_Scene->AddCam();
	m_Scene->NextCam->SetSource(Vertex(64,64,64));
	m_Scene->NextCam->SetDest(Vertex(128,128,128));
*/
	IsNamed=false;
}

CDeskDoc::~CDeskDoc()
{
	delete m_Scene;
	delete m_Renderer;
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

	//MessageBox(NULL,"Yop","",MB_OK);

	if (ar.IsStoring())
	{

        //KLibs->WriteGen[ar.GetFile()->IsKindOf()-1]->Write(m_Scene,ar.GetFile()->GetFilePath( ).GetBuffer (MAX_PATH));

	}
	else
	{
		for (i=0;i<GKPlugins->FilePlugins.size();i++)
		{
			if (GKPlugins->FilePlugins[i]->Read(m_Scene,ar.GetFile()->GetFilePath( ).GetBuffer (MAX_PATH)))
			{
                m_SavePlugin=GKPlugins->FilePlugins[i];
				i=GKPlugins->FilePlugins.size();
				SetPathName(ar.GetFile()->GetFilePath( ).GetBuffer (MAX_PATH));
				SetTitle(ar.GetFile()->GetFilePath( ).GetBuffer (MAX_PATH));
				IsNamed=true;
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
