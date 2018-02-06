// Path.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "Path.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPath dialog

extern "C" int TypeEd;
extern "C" CKMesh *Mesh;
extern CKScene *GScene;

CPath::CPath(CWnd* pParent /*=NULL*/)
	: CDialog(CPath::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPath)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPath::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPath)
	DDX_Control(pDX, IDC_SHAPENAME, m_ShapeName);
	DDX_Control(pDX, IDC_PATHNAME, m_PathName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPath, CDialog)
	//{{AFX_MSG_MAP(CPath)
	ON_BN_CLICKED(IDC_GENERATE, OnGenerate)
	ON_BN_CLICKED(IDC_PATH, OnPath)
	ON_BN_CLICKED(IDC_SHAPE, OnShape)
	ON_BN_CLICKED(IDC_MOVESHAPE, OnMoveshape)
	ON_BN_CLICKED(IDC_ROTATE, OnRotate)
	ON_BN_CLICKED(IDC_SCALE, OnScale)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPath message handlers

void CPath::OnGenerate() 
{
	if (Mesh!=NULL)
	{
		GScene->AddMesh(Mesh);
	}
}

void CPath::OnPath() 
{
	TypeEd=2;
}

void CPath::OnShape() 
{
	// TODO: Add your control notification handler code here
	TypeEd=1;
}

void CPath::OnMoveshape() 
{
	// TODO: Add your control notification handler code here
	
}

void CPath::OnRotate() 
{
	// TODO: Add your control notification handler code here
	
}

void CPath::OnScale() 
{
	// TODO: Add your control notification handler code here
	
}
