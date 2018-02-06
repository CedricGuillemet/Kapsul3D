
#include "stdafx.h"
#include "resource.h"
#include "UVMapperDiag.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CUVMapperDiag dialog


CUVMapperDiag::CUVMapperDiag(CWnd* pParent /*=NULL*/)
	: CDialog(CUVMapperDiag::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUVMapperDiag)
	//}}AFX_DATA_INIT
}


void CUVMapperDiag::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUVMapperDiag)
	DDX_Control(pDX, IDC_CBVIEW, m_CBView);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUVMapperDiag, CDialog)
	//{{AFX_MSG_MAP(CUVMapperDiag)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_SELOBJECT, OnSelobject)
	ON_BN_CLICKED(IDC_LOADMAP, OnLoadmap)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_SAVEBMP, OnSavebmp)
	ON_CBN_SELCHANGE(IDC_CBVIEW, OnSelchangeCbview)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUVMapperDiag message handlers

void CUVMapperDiag::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

}

BOOL CUVMapperDiag::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_CBView.ResetContent();
	m_CBView.AddString("None");
	m_CBView.AddString("1");
	m_CBView.AddString("2");
	m_CBView.AddString("3");
	m_CBView.AddString("4");
	m_CBView.SetCurSel(0);
	m_OldSelectView=-1;


		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CUVMapperDiag::OnOK( )
{

}

void CUVMapperDiag::OnCancel( )
{

}

void CUVMapperDiag::OnSelobject() 
{
	// TODO: Add your control notification handler code here
	
}

void CUVMapperDiag::OnLoadmap() 
{
	 char        ReadFilter[]={"All supported Format\0*.jpg;*.bmp;*.tga;*.gif;*.pcx;*.tif\0\0"};
    CFileDialog *m_FileDiag;
	char filename[MAX_PATH];
	m_FileDiag=new CFileDialog(TRUE);
	m_FileDiag->m_ofn.lpstrFilter=ReadFilter;
	if (m_FileDiag->DoModal()==IDOK)
	{
		/*
        char ext[_MAX_PATH];
        strcpy(filename,m_FileDiag->m_ofn.lpstrFile);
        
		strcpy(csv.cb->Layer1[2]->FileName,filename);
        csv.cb->Layer1[2]->Type=TEXTURE_FILE;
        csv.cb->Layer1[2]->Load();
		*/
	}

	//MapTex
	
}

void CUVMapperDiag::OnCheck1() 
{
	
}

void CUVMapperDiag::OnSavebmp() 
{
	CKImage *daImg;
	int i,j;
	bool loadsuc;
	CKScene *GScene=m_Plugin->m_Scene;
	

	if (GScene->FirstMesh->Tex1->FileName=="DefaultTexture")
	{
		daImg=GetDefaultImage();
		loadsuc=(daImg!=NULL);
	}
	else
	{
		daImg=new CKImage;
		loadsuc=daImg->LoadFile(GScene->FirstMesh->Tex1->FileName);
	}

    if (loadsuc)
    {
		int SizeX,SizeY;
		SizeX=daImg->GetWidth();
		SizeY=daImg->GetHeight();


		for (CKMesh *daMesh=GScene->FirstMesh;daMesh!=NULL;daMesh=daMesh->Next)
		{
			if (daMesh->Selected)
			{
				for (i=0;i<daMesh->nb2poly;i++)
				{
					for (j=0;j<(daMesh->pl[i].nb2vert-1);j++)
					{
						daImg->DrawLine(daMesh->puv[0][daMesh->pl[i].Tex[0][j]].u*SizeX,
							daMesh->puv[0][daMesh->pl[i].Tex[0][j]].v*SizeY,
							daMesh->puv[0][daMesh->pl[i].Tex[0][j+1]].u*SizeX,
							daMesh->puv[0][daMesh->pl[i].Tex[0][j+1]].v*SizeY,255,255,255);
					}
				}
			}
			else
			{
				for (i=0;i<daMesh->nb2poly;i++)
				{
					if (daMesh->pl[i].Selected)
					{
						for (j=0;j<(daMesh->pl[i].nb2vert-1);j++)
						{
							daImg->DrawLine(daMesh->puv[0][daMesh->pl[i].Tex[0][j]].u*SizeX,
								daMesh->puv[0][daMesh->pl[i].Tex[0][j]].v*SizeY,
								daMesh->puv[0][daMesh->pl[i].Tex[0][j+1]].u*SizeX,
								daMesh->puv[0][daMesh->pl[i].Tex[0][j+1]].v*SizeY,255,255,255);

						}
					}
				}
			}
		}
		daImg->Save(this->m_hWnd);
		//daImg->SaveFile("c:\\uvmapper.bmp");
    }

	
    delete daImg;
}

void CUVMapperDiag::OnSelchangeCbview() 
{
	CKScene *GScene=m_Plugin->m_Scene;

	if (m_OldSelectView!=-1)
	{
		GScene->ViewType[m_OldSelectView]=m_OldViewType;
		
	}

	int CurSelType=m_CBView.GetCurSel();
	if (CurSelType!=0)
	{
		m_OldSelectView=CurSelType;
		m_OldViewType=GScene->ViewType[m_OldSelectView];
		GScene->ViewType[CurSelType]=VIEWTYPE_UV;
		GScene->SelectedToUVBuffer(0);
	}
	else
	{
		m_OldSelectView=-1;
		GScene->SelectedToUVBuffer(0);
	}

	GScene->EnableUVSelectionUpdate(true);
	DrawViews();
}
