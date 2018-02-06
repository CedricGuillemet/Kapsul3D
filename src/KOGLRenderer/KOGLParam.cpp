// KOGLParam.cpp : implementation file
//

#include "stdafx.h"
#include "KOGLRenderer.h"
#include "KOGLParam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKOGLParam dialog


CKOGLParam::CKOGLParam(CWnd* pParent /*=NULL*/)
	: CDialog(CKOGLParam::IDD, pParent)
{
	//{{AFX_DATA_INIT(CKOGLParam)
	//}}AFX_DATA_INIT
}


void CKOGLParam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKOGLParam)
	DDX_Control(pDX, IDC_EXTLIST, m_ExtList);
	DDX_Control(pDX, IDC_RENDERER, m_Renderer);
	DDX_Control(pDX, IDC_GLVERSION, m_GLVersion);
	DDX_Control(pDX, IDC_GLUVERSION, m_GluVersion);
	DDX_Control(pDX, IDC_VENDOR, m_Vendor);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CKOGLParam, CDialog)
	//{{AFX_MSG_MAP(CKOGLParam)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKOGLParam message handlers

void CKOGLParam::OnOK() 
{
	
}

void CKOGLParam::OnCancel() 
{

}
/*
ew FXLabel(v_matrix,"Vendor: ",NULL,LABEL_NORMAL);
  new FXLabel(v_matrix,FXStringFormat("%s",glGetString(GL_VENDOR)),NULL,LABEL_NORMAL);

  new FXLabel(v_matrix,"Renderer: ",NULL,LABEL_NORMAL);
  new FXLabel(v_matrix,FXStringFormat("%s",glGetString(GL_RENDERER)),NULL,LABEL_NORMAL);

  new FXLabel(v_matrix,"GL Version: ",NULL,LABEL_NORMAL);
  new FXLabel(v_matrix,FXStringFormat("%s",glGetString(GL_VERSION)),NULL,LABEL_NORMAL);

  new FXLabel(v_matrix,"GLU Version: ",NULL,LABEL_NORMAL);
  new FXLabel(v_matrix,FXStringFormat("%s",gluGetString(GLU_VERSION)),NULL,LABEL_NORMAL);
  */

BOOL CKOGLParam::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	char *token,*text,*tmp;

	m_Renderer.SetWindowText((char*)glGetString(GL_RENDERER));
	m_GLVersion.SetWindowText((char*)glGetString(GL_VERSION));
	m_GluVersion.SetWindowText((char*)gluGetString(GLU_VERSION));
	m_Vendor.SetWindowText((char*)glGetString(GL_VENDOR));
	
	tmp=(char*)glGetString(GL_EXTENSIONS);
	if(tmp){
		text=strdup(tmp);
		token=strtok(text," ");
		while(token!=NULL){
			m_ExtList.AddString(token);
			token=strtok(NULL," ");
		}
		free(text);
    }
	
	// Get GLU extensions
#if defined(GLU_VERSION_1_1)
	tmp=(char*)gluGetString(GLU_EXTENSIONS);
	if(tmp){
		text=strdup(tmp);
		token=strtok(text," ");
		while(token!=NULL){
			m_ExtList.AddString(token);
			token=strtok(NULL," ");
		}
		free(text);
    }
#endif

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
