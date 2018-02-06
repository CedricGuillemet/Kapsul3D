// InfosSel.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "InfosSel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInfosSel dialog


CInfosSel::CInfosSel(CWnd* pParent /*=NULL*/)
	: CDialog(CInfosSel::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInfosSel)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CInfosSel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInfosSel)
	DDX_Control(pDX, IDC_SKELETTON, m_Skeleton);
	DDX_Control(pDX, IDC_SHAPE, m_Shape);
	DDX_Control(pDX, IDC_SEGMENT, m_Segment);
	DDX_Control(pDX, IDC_PATCH, m_Patch);
	DDX_Control(pDX, IDC_OBJVERT, m_MeshVert);
	DDX_Control(pDX, IDC_OBJFACE, m_MeshFaces);
	DDX_Control(pDX, IDC_OBJ, m_Mesh);
	DDX_Control(pDX, IDC_ENTITIES, m_Entities);
	DDX_Control(pDX, IDC_CAMERA, m_Camera);
	DDX_Control(pDX, IDC_BONE, m_Bone);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInfosSel, CDialog)
	//{{AFX_MSG_MAP(CInfosSel)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInfosSel message handlers
