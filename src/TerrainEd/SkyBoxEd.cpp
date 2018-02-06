// SkyBoxEd.cpp : implementation file
//

#include "stdafx.h"
#include "SkyBoxEd.h"
#include "TerrainEdDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkyBoxEd dialog

extern CTerrainEdDlg *MainWind;

CSkyBoxEd::CSkyBoxEd(CWnd* pParent /*=NULL*/)
	: CDialog(CSkyBoxEd::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSkyBoxEd)
	//}}AFX_DATA_INIT
}


void CSkyBoxEd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSkyBoxEd)
	DDX_Control(pDX, IDC_CL2UP, m_CL2UP);
	DDX_Control(pDX, IDC_CL2RIGHT, m_CL2RIGHT);
	DDX_Control(pDX, IDC_CL2LEFT, m_CL2LEFT);
	DDX_Control(pDX, IDC_CL2FRONT, m_CL2FRONT);
	DDX_Control(pDX, IDC_CL2DOWN, m_CL2DOWN);
	DDX_Control(pDX, IDC_CL2BACK, m_CL2BACK);
	DDX_Control(pDX, IDC_SKYBOXNAME, m_SKYBOXNAME);
	DDX_Control(pDX, IDC_SLIDERZ2, m_SLDSKY2);
	DDX_Control(pDX, IDC_SLIDERZ1, m_SLDSKY1);
	DDX_Control(pDX, IDC_CHECK20, m_CSKY2);
	DDX_Control(pDX, IDC_CHECK19, m_CSKY1);
	DDX_Control(pDX, IDC_BUTTON7, m_SKY2);
	DDX_Control(pDX, IDC_BUTTON14, m_SKY1);
	DDX_Control(pDX, IDC_CHECK18, m_ABACK);
	DDX_Control(pDX, IDC_CHECK17, m_AFRONT);
	DDX_Control(pDX, IDC_CHECK16, m_ARIGHT);
	DDX_Control(pDX, IDC_CHECK15, m_ALEFT);
	DDX_Control(pDX, IDC_CHECK14, m_ADOWN);
	DDX_Control(pDX, IDC_CHECK13, m_AUP);
	DDX_Control(pDX, IDC_CHECK6, m_CL1BACK);
	DDX_Control(pDX, IDC_CHECK5, m_CL1FRONT);
	DDX_Control(pDX, IDC_CHECK4, m_CL1RIGHT);
	DDX_Control(pDX, IDC_CHECK3, m_CL1LEFT);
	DDX_Control(pDX, IDC_CHECK2, m_CL1DOWN);
	DDX_Control(pDX, IDC_CHECK1, m_CL1UP);
	DDX_Control(pDX, IDC_BUTTON13, m_L2BACK);
	DDX_Control(pDX, IDC_BUTTON12, m_L2FRONT);
	DDX_Control(pDX, IDC_BUTTON11, m_L2RIGHT);
	DDX_Control(pDX, IDC_BUTTON10, m_L2LEFT);
	DDX_Control(pDX, IDC_BUTTON9, m_L2DOWN);
	DDX_Control(pDX, IDC_BUTTON8, m_L2UP);
	DDX_Control(pDX, IDC_BUTTON6, m_L1BACK);
	DDX_Control(pDX, IDC_BUTTON5, m_L1FRONT);
	DDX_Control(pDX, IDC_BUTTON4, m_L1RIGHT);
	DDX_Control(pDX, IDC_BUTTON3, m_L1LEFT);
	DDX_Control(pDX, IDC_BUTTON2, m_L1DOWN);
	DDX_Control(pDX, IDC_BUTTON1, m_L1UP);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSkyBoxEd, CDialog)
	//{{AFX_MSG_MAP(CSkyBoxEd)
	ON_BN_CLICKED(IDC_LOAD, OnLoad)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, OnL1UP)
	ON_BN_CLICKED(IDC_BUTTON2, OnL1DOWN)
	ON_BN_CLICKED(IDC_BUTTON3, OnL1LEFT)
	ON_BN_CLICKED(IDC_BUTTON4, OnL1RIGHT)
	ON_BN_CLICKED(IDC_BUTTON5, OnL1FRONT)
	ON_BN_CLICKED(IDC_BUTTON6, OnL1BACK)
	ON_BN_CLICKED(IDC_BUTTON8, OnL2UP)
	ON_BN_CLICKED(IDC_BUTTON9, OnL2DOWN)
	ON_BN_CLICKED(IDC_BUTTON10, OnL2LEFT)
	ON_BN_CLICKED(IDC_BUTTON11, OnL2RIGHT)
	ON_BN_CLICKED(IDC_BUTTON12, OnL2FRONT)
	ON_BN_CLICKED(IDC_BUTTON13, OnL2BACK)
	ON_BN_CLICKED(IDC_CHECK1, OnCL1UP)
	ON_BN_CLICKED(IDC_CHECK2, OnCL1DOWN)
	ON_BN_CLICKED(IDC_CHECK3, OnCL1LEFT)
	ON_BN_CLICKED(IDC_CHECK4, OnCL1RIGHT)
	ON_BN_CLICKED(IDC_CHECK5, OnCL1FRONT)
	ON_BN_CLICKED(IDC_CHECK6, OnCL1BACK)
	ON_BN_CLICKED(IDC_CHECK7, OnCL2UP)
	ON_BN_CLICKED(IDC_CHECK8, OnCL2DOWN)
	ON_BN_CLICKED(IDC_CHECK9, OnCL2LEFT)
	ON_BN_CLICKED(IDC_CHECK10, OnCL2RIGHT)
	ON_BN_CLICKED(IDC_CHECK11, OnCL2FRONT)
	ON_BN_CLICKED(IDC_CHECK12, OnCL2BACK)
	ON_BN_CLICKED(IDC_CHECK13, OnAUP)
	ON_BN_CLICKED(IDC_CHECK14, OnADOWN)
	ON_BN_CLICKED(IDC_CHECK15, OnALEFT)
	ON_BN_CLICKED(IDC_CHECK16, OnARIGHT)
	ON_BN_CLICKED(IDC_CHECK17, OnAFRONT)
	ON_BN_CLICKED(IDC_CHECK18, OnABACK)
	ON_BN_CLICKED(IDC_CHECK20, OnCSKY2)
	ON_BN_CLICKED(IDC_CHECK19, OnCSKY1)
	ON_BN_CLICKED(IDC_BUTTON14, OnSky1)
	ON_BN_CLICKED(IDC_BUTTON7, OnSky2)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_NEW, OnNew)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkyBoxEd message handlers
bool CSkyBoxEd::LoadImgFile(void)
{
    char        ReadFilter[]={"All supported Format\0*.jpg;*.bmp;*.tga;*.gif;*.pcx;*.tif\0\0"};
    CFileDialog *m_FileDiag;

	m_FileDiag=new CFileDialog(TRUE);
	m_FileDiag->m_ofn.lpstrFilter=ReadFilter;
	if (m_FileDiag->DoModal()==IDOK)
	{
        char ext[_MAX_PATH];
        strcpy(filename,m_FileDiag->m_ofn.lpstrFile);
        

		_splitpath( filename, NULL, NULL, title, ext );
		strcat( title, ext );
        Modified=true;

        return true;
    }

    return false;
}

void CSkyBoxEd::OnLoad() 
{
    char        ReadFilter[]={"Skybox\0*.skk\0\0"};
    CFileDialog *m_FileDiag;
    char daName[_MAX_PATH],daExt[_MAX_PATH];

	m_FileDiag=new CFileDialog(TRUE);
	m_FileDiag->m_ofn.lpstrFilter=ReadFilter;
	if (m_FileDiag->DoModal()==IDOK)
	{
        OnNew();

        char ext[_MAX_PATH];
        strcpy(SkyBoxName,m_FileDiag->m_ofn.lpstrFile);
        csv.cb->Load((unsigned char*)SkyBoxName);
        if (csv.cb->Layer1[0]->TexID!=-1) 
        {
            _splitpath(csv.cb->Layer1[0]->FileName,NULL,NULL,daName,daExt);
            strcat(daName,daExt);
            m_L1BACK.SetWindowText(daName);
            m_CL1BACK.SetCheck(TRUE);
        }
        if (csv.cb->Layer1[1]->TexID!=-1) 
        {
            _splitpath(csv.cb->Layer1[1]->FileName,NULL,NULL,daName,daExt);
            strcat(daName,daExt);
            m_L1FRONT.SetWindowText(daName);
            m_CL1FRONT.SetCheck(TRUE);
        }
        if (csv.cb->Layer1[2]->TexID!=-1) 
        {
            _splitpath(csv.cb->Layer1[2]->FileName,NULL,NULL,daName,daExt);
            strcat(daName,daExt);
            m_L1UP.SetWindowText(daName);
            m_CL1UP.SetCheck(TRUE);
        }
        if (csv.cb->Layer1[3]->TexID!=-1) 
        {
            _splitpath(csv.cb->Layer1[3]->FileName,NULL,NULL,daName,daExt);
            strcat(daName,daExt);
            m_L1DOWN.SetWindowText(daName);
            m_CL1DOWN.SetCheck(TRUE);
        }
        if (csv.cb->Layer1[4]->TexID!=-1) 
        {
            _splitpath(csv.cb->Layer1[4]->FileName,NULL,NULL,daName,daExt);
            strcat(daName,daExt);
            m_L1LEFT.SetWindowText(daName);
            m_CL1LEFT.SetCheck(TRUE);
        }
        if (csv.cb->Layer1[5]->TexID!=-1) 
        {
            _splitpath(csv.cb->Layer1[5]->FileName,NULL,NULL,daName,daExt);
            strcat(daName,daExt);
            m_L1RIGHT.SetWindowText(daName);
            m_CL1RIGHT.SetCheck(TRUE);
        }

        if (csv.cb->Layer2[0]->TexID!=-1) 
        {
            _splitpath(csv.cb->Layer2[0]->FileName,NULL,NULL,daName,daExt);
            strcat(daName,daExt);
            m_L2BACK.SetWindowText(daName);
            m_CL2BACK.SetCheck(TRUE);
            m_ABACK.SetCheck(csv.cb->Layer2[0]->ComputeAlpha);
        }
        if (csv.cb->Layer2[1]->TexID!=-1) 
        {
            _splitpath(csv.cb->Layer2[1]->FileName,NULL,NULL,daName,daExt);
            strcat(daName,daExt);
            m_L2FRONT.SetWindowText(daName);
            m_CL2FRONT.SetCheck(TRUE);
            m_AFRONT.SetCheck(csv.cb->Layer2[1]->ComputeAlpha);
        }
        if (csv.cb->Layer2[2]->TexID!=-1) 
        {
            _splitpath(csv.cb->Layer2[2]->FileName,NULL,NULL,daName,daExt);
            strcat(daName,daExt);
            m_L2UP.SetWindowText(daName);
            m_CL2UP.SetCheck(TRUE);
            m_AUP.SetCheck(csv.cb->Layer2[2]->ComputeAlpha);
        }
        if (csv.cb->Layer2[3]->TexID!=-1) 
        {
            _splitpath(csv.cb->Layer2[3]->FileName,NULL,NULL,daName,daExt);
            strcat(daName,daExt);
            m_L2DOWN.SetWindowText(daName);
            m_CL2DOWN.SetCheck(TRUE);
            m_ADOWN.SetCheck(csv.cb->Layer2[3]->ComputeAlpha);
        }
        if (csv.cb->Layer2[4]->TexID!=-1) 
        {
            _splitpath(csv.cb->Layer2[4]->FileName,NULL,NULL,daName,daExt);
            strcat(daName,daExt);
            m_L2LEFT.SetWindowText(daName);
            m_CL2LEFT.SetCheck(TRUE);
            m_ALEFT.SetCheck(csv.cb->Layer2[4]->ComputeAlpha);
        }
        if (csv.cb->Layer2[5]->TexID!=-1) 
        {
            _splitpath(csv.cb->Layer2[5]->FileName,NULL,NULL,daName,daExt);
            strcat(daName,daExt);
            m_L2RIGHT.SetWindowText(daName);
            m_CL2RIGHT.SetCheck(TRUE);
            m_ARIGHT.SetCheck(csv.cb->Layer2[5]->ComputeAlpha);
        }

        if (csv.cb->Sky1->TexID!=-1) 
        {
            _splitpath(csv.cb->Sky1->FileName,NULL,NULL,daName,daExt);
            strcat(daName,daExt);
            m_SKY1.SetWindowText(daName);
            m_CSKY1.SetCheck(TRUE);
            float tmp=csv.cb->Sky1av*200000.0f;
            m_SLDSKY1.SetPos((int)(tmp));
        }

        if (csv.cb->Sky2->TexID!=-1) 
        {
            _splitpath(csv.cb->Sky2->FileName,NULL,NULL,daName,daExt);
            strcat(daName,daExt);
            m_SKY2.SetWindowText(daName);
            m_CSKY2.SetCheck(TRUE);
            float tmp=csv.cb->Sky2av*200000.0f;
            m_SLDSKY2.SetPos((int)(tmp));
        }

        Modified=false;
        
		_splitpath( SkyBoxName, NULL, NULL, SkyBoxTitle, ext );
        m_SKYBOXNAME.SetWindowText(SkyBoxTitle);
		strcat( SkyBoxTitle, ext );
    }
}

void CSkyBoxEd::OnSave() 
{
    char        ReadFilter[]={"Skybox\0*.skk\0\0"};
    CFileDialog *m_FileDiag;
    char temp[1024],drive[_MAX_PATH],dapath[_MAX_PATH],daname[_MAX_PATH],daext[_MAX_PATH];
    
    m_SKYBOXNAME.GetWindowText(temp,1024);
    if (strcmp(temp,"")==0)
    {
	    m_FileDiag=new CFileDialog(FALSE);
	    m_FileDiag->m_ofn.lpstrFilter=ReadFilter;
	    if (m_FileDiag->DoModal()==IDOK)
	    {
            char ext[_MAX_PATH];
            _splitpath( m_FileDiag->m_ofn.lpstrFile, drive, dapath, daname, daext );
            if (strcmp(daext,"")==0) 
                strcat(m_FileDiag->m_ofn.lpstrFile,".skk");

            strcpy(SkyBoxName,m_FileDiag->m_ofn.lpstrFile);
            csv.cb->Save((unsigned char*)SkyBoxName);

		    _splitpath( SkyBoxName, NULL, NULL, SkyBoxTitle, ext );
            m_SKYBOXNAME.SetWindowText(SkyBoxTitle);
		    strcat( SkyBoxTitle, ext );
            Modified=false;
        }
    }	
    else
    {
        csv.cb->Save((unsigned char*)SkyBoxName);
        Modified=false;
    }
}

const RECT rc1={20,30,30+516,30+290};


BOOL CSkyBoxEd::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

    
    csv.CreateEx(WS_EX_CLIENTEDGE,"STATIC",_T("Yep"),WS_CHILD|WS_VISIBLE|SS_LEFT ,rc1,this,102101);
    SetTimer(1,10,NULL);

    m_SLDSKY1.SetRange(0,100);
    m_SLDSKY2.SetRange(0,100);

    csv.cb->Sky1av=0;
    csv.cb->Sky2av=0;
    Modified=false;
    m_SKYBOXNAME.SetWindowText("");
    
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSkyBoxEd::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	csv.Invalidate(FALSE);
	CDialog::OnTimer(nIDEvent);
}

void CSkyBoxEd::OnL1UP() 
{
	// TODO: Add your control notification handler code here

    if (LoadImgFile())
    {
        m_L1UP.SetWindowText(title);
        strcpy(csv.cb->Layer1[2]->FileName,filename);
        csv.cb->Layer1[2]->Type=TEXTURE_FILE;
        csv.cb->Layer1[2]->Load();
        m_CL1UP.SetCheck(TRUE);
    }

}

void CSkyBoxEd::OnL1DOWN() 
{
    if (LoadImgFile())
    {
        m_L1DOWN.SetWindowText(title);
        strcpy(csv.cb->Layer1[3]->FileName,filename);
        csv.cb->Layer1[3]->Type=TEXTURE_FILE;
        csv.cb->Layer1[3]->Load();
        m_CL1DOWN.SetCheck(TRUE);
    }
	
}

void CSkyBoxEd::OnL1LEFT() 
{
    if (LoadImgFile())
    {
        m_L1LEFT.SetWindowText(title);
        strcpy(csv.cb->Layer1[4]->FileName,filename);
        csv.cb->Layer1[4]->Type=TEXTURE_FILE;
        csv.cb->Layer1[4]->Load();
        m_CL1LEFT.SetCheck(TRUE);
    }
	
}

void CSkyBoxEd::OnL1RIGHT() 
{
    if (LoadImgFile())
    {
        m_L1RIGHT.SetWindowText(title);
        strcpy(csv.cb->Layer1[5]->FileName,filename);
        csv.cb->Layer1[5]->Type=TEXTURE_FILE;
        csv.cb->Layer1[5]->Load();
        m_CL1RIGHT.SetCheck(TRUE);
    }
	
}

void CSkyBoxEd::OnL1FRONT() 
{
    if (LoadImgFile())
    {
        m_L1FRONT.SetWindowText(title);
        strcpy(csv.cb->Layer1[1]->FileName,filename);
        csv.cb->Layer1[1]->Type=TEXTURE_FILE;
        csv.cb->Layer1[1]->Load();
        m_CL1FRONT.SetCheck(TRUE);
    }
	
}

void CSkyBoxEd::OnL1BACK() 
{
    if (LoadImgFile())
    {
        m_L1BACK.SetWindowText(title);
        strcpy(csv.cb->Layer1[0]->FileName,filename);
        csv.cb->Layer1[0]->Type=TEXTURE_FILE;
        csv.cb->Layer1[0]->Load();
        m_CL1BACK.SetCheck(TRUE);
    }
}

void CSkyBoxEd::OnL2UP() 
{
    if (LoadImgFile())
    {
        m_L2UP.SetWindowText(title);
        strcpy(csv.cb->Layer2[2]->FileName,filename);
        csv.cb->Layer2[2]->Type=TEXTURE_FILE;
        csv.cb->Layer2[2]->Load();
        m_CL2UP.SetCheck(TRUE);
    }
	
}

void CSkyBoxEd::OnL2DOWN() 
{
    if (LoadImgFile())
    {
        m_L2DOWN.SetWindowText(title);
        strcpy(csv.cb->Layer2[3]->FileName,filename);
        csv.cb->Layer2[3]->Type=TEXTURE_FILE;
        csv.cb->Layer2[3]->Load();
        m_CL2DOWN.SetCheck(TRUE);
    }
	
}

void CSkyBoxEd::OnL2LEFT() 
{
    if (LoadImgFile())
    {
        m_L2LEFT.SetWindowText(title);
        strcpy(csv.cb->Layer2[4]->FileName,filename);
        csv.cb->Layer2[4]->Type=TEXTURE_FILE;
        csv.cb->Layer2[4]->Load();
        m_CL2LEFT.SetCheck(TRUE);
    }
}

void CSkyBoxEd::OnL2RIGHT() 
{
    if (LoadImgFile())
    {
        m_L2RIGHT.SetWindowText(title);
        strcpy(csv.cb->Layer2[5]->FileName,filename);
        csv.cb->Layer2[5]->Type=TEXTURE_FILE;
        csv.cb->Layer2[5]->Load();
        m_CL2RIGHT.SetCheck(TRUE);
    }
	
}

void CSkyBoxEd::OnL2FRONT() 
{
    if (LoadImgFile())
    {
        m_L2FRONT.SetWindowText(title);
        strcpy(csv.cb->Layer2[1]->FileName,filename);
        csv.cb->Layer2[1]->Type=TEXTURE_FILE;
        csv.cb->Layer2[1]->Load();
        m_CL2FRONT.SetCheck(TRUE);
    }
	
}

void CSkyBoxEd::OnL2BACK() 
{
    if (LoadImgFile())
    {
        m_L2BACK.SetWindowText(title);
        strcpy(csv.cb->Layer2[0]->FileName,filename);
        csv.cb->Layer2[0]->Type=TEXTURE_FILE;
        csv.cb->Layer2[0]->Load();
        m_CL2BACK.SetCheck(TRUE);
    }
	
}

void CSkyBoxEd::OnCL1UP() 
{
    if (m_CL1UP.GetCheck())
        OnL1UP();
    else
    {
        m_L1UP.SetWindowText("None");
        csv.cb->Layer1[2]->UnLoad();
    }
    Modified=true;
}

void CSkyBoxEd::OnCL1DOWN() 
{
    if (m_CL1DOWN.GetCheck())
        OnL1DOWN();
    else
    {
        m_L1DOWN.SetWindowText("None");
        csv.cb->Layer1[3]->UnLoad();
    }
    Modified=true;
	
}

void CSkyBoxEd::OnCL1LEFT() 
{
    if (m_CL1LEFT.GetCheck())
        OnL1LEFT();
    else
    {
        m_L1LEFT.SetWindowText("None");
        csv.cb->Layer1[4]->UnLoad();
    }
    Modified=true;
	
}

void CSkyBoxEd::OnCL1RIGHT() 
{
    if (m_CL1RIGHT.GetCheck())
        OnL1RIGHT();
    else
    {
        m_L1RIGHT.SetWindowText("None");
        csv.cb->Layer1[5]->UnLoad();
    }
    Modified=true;
	
}

void CSkyBoxEd::OnCL1FRONT() 
{
    if (m_CL1FRONT.GetCheck())
        OnL1FRONT();
    else
    {
        m_L1FRONT.SetWindowText("None");
        csv.cb->Layer1[1]->UnLoad();
    }
    Modified=true;
	
}

void CSkyBoxEd::OnCL1BACK() 
{
    if (m_CL1BACK.GetCheck())
        OnL1BACK();
    else
    {
        m_L1BACK.SetWindowText("None");
        csv.cb->Layer1[0]->UnLoad();
    }
    Modified=true;
	
}

void CSkyBoxEd::OnCL2UP() 
{
    if (m_CL2UP.GetCheck())
        OnL2UP();
    else
    {
        m_L2UP.SetWindowText("None");
        csv.cb->Layer2[2]->UnLoad();
    }
    Modified=true;
	
}

void CSkyBoxEd::OnCL2DOWN() 
{
    if (m_CL2DOWN.GetCheck())
        OnL2DOWN();
    else
    {
        m_L2DOWN.SetWindowText("None");
        csv.cb->Layer2[3]->UnLoad();
    }
    Modified=true;
	
}

void CSkyBoxEd::OnCL2LEFT() 
{
    if (m_CL2LEFT.GetCheck())
        OnL2LEFT();
    else
    {
        m_L2LEFT.SetWindowText("None");
        csv.cb->Layer2[4]->UnLoad();

    }
	Modified=true;
}

void CSkyBoxEd::OnCL2RIGHT() 
{
    if (m_CL2RIGHT.GetCheck())
        OnL2RIGHT();
    else
    {
        m_L2RIGHT.SetWindowText("None");
        csv.cb->Layer2[5]->UnLoad();

    }
    Modified=true;
	
}

void CSkyBoxEd::OnCL2FRONT() 
{
    if (m_CL2FRONT.GetCheck())
        OnL2FRONT();
    else
    {
        m_L2FRONT.SetWindowText("None");
        csv.cb->Layer2[1]->UnLoad();

    }
    Modified=true;
	
}

void CSkyBoxEd::OnCL2BACK() 
{
    if (m_CL2BACK.GetCheck())
        OnL2BACK();
    else
    {
        m_L2BACK.SetWindowText("None");
        csv.cb->Layer2[0]->UnLoad();

    }
    Modified=true;
	
}

void CSkyBoxEd::OnAUP() 
{
    csv.cb->Layer2[2]->ComputeAlpha=m_AUP.GetCheck();
    csv.cb->Layer2[2]->Load();
    Modified=true;
}

void CSkyBoxEd::OnADOWN() 
{
    csv.cb->Layer2[3]->ComputeAlpha=m_ADOWN.GetCheck();
    csv.cb->Layer2[3]->Load();
	Modified=true;
}

void CSkyBoxEd::OnALEFT() 
{
    csv.cb->Layer2[4]->ComputeAlpha=m_ALEFT.GetCheck();
    csv.cb->Layer2[4]->Load();
    Modified=true;
	
}

void CSkyBoxEd::OnARIGHT() 
{
    csv.cb->Layer2[5]->ComputeAlpha=m_ARIGHT.GetCheck();
    csv.cb->Layer2[5]->Load();
    Modified=true;
}

void CSkyBoxEd::OnAFRONT() 
{
    csv.cb->Layer2[1]->ComputeAlpha=m_AFRONT.GetCheck();
    csv.cb->Layer2[1]->Load();
    Modified=true;
}

void CSkyBoxEd::OnABACK() 
{
    csv.cb->Layer2[0]->ComputeAlpha=m_ABACK.GetCheck();
    csv.cb->Layer2[0]->Load();
    Modified=true;
}

void CSkyBoxEd::OnCSKY2() 
{
    if (m_CSKY2.GetCheck())
        OnSky2();
    else
    {
        m_SKY2.SetWindowText("None");
        csv.cb->Sky2->UnLoad();

    }
}

void CSkyBoxEd::OnCSKY1() 
{
    if (m_CSKY1.GetCheck())
        OnSky1();
    else
    {
        m_SKY1.SetWindowText("None");
        csv.cb->Sky1->UnLoad();

    }
}

void CSkyBoxEd::OnSky1() 
{
    if (LoadImgFile())
    {
        m_SKY1.SetWindowText(title);
        strcpy(csv.cb->Sky1->FileName,filename);
        csv.cb->Sky1->Type=TEXTURE_FILE;
        csv.cb->Sky1->Load();
        m_CSKY1.SetCheck(TRUE);
    }
}

void CSkyBoxEd::OnSky2() 
{
    if (LoadImgFile())
    {
        m_SKY2.SetWindowText(title);
        strcpy(csv.cb->Sky2->FileName,filename);
        csv.cb->Sky2->Type=TEXTURE_FILE;
        csv.cb->Sky2->Load();
        m_CSKY2.SetCheck(TRUE);
    }
	
}

void CSkyBoxEd::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
    csv.cb->Sky1av=(double)m_SLDSKY1.GetPos()/200000.0f;
    csv.cb->Sky2av=(double)m_SLDSKY2.GetPos()/200000.0f;
    Modified=true;
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CSkyBoxEd::OnNew() 
{
    if (Modified)
    {
        switch(MessageBox("Do you want to save your changes?","Quit",MB_ICONQUESTION|MB_YESNOCANCEL))
        {
        case IDYES:
            OnSave();
            break;
        case IDNO:
            break;
        case IDCANCEL:
            return;
        }
    }

	m_SKYBOXNAME.SetWindowText("");
    Modified=false;

    m_SKY2.SetWindowText("None");
    csv.cb->Sky2->UnLoad();
    m_CSKY2.SetCheck(FALSE);

    m_SKY1.SetWindowText("None");
    csv.cb->Sky1->UnLoad();
    m_CSKY1.SetCheck(FALSE);

    for (int i=0;i<6;i++)
    {
        csv.cb->Layer1[i]->UnLoad();
        csv.cb->Layer2[i]->UnLoad();
    }

    m_L2BACK.SetWindowText("None");
    m_CL2BACK.SetCheck(FALSE);
    m_ABACK.SetCheck(FALSE);

    m_L1BACK.SetWindowText("None");
    m_CL1BACK.SetCheck(FALSE);

    m_L2FRONT.SetWindowText("None");
    m_CL2FRONT.SetCheck(FALSE);
    m_AFRONT.SetCheck(FALSE);

    m_L2UP.SetWindowText("None");
    m_CL2UP.SetCheck(FALSE);
    m_AUP.SetCheck(FALSE);

    m_L2LEFT.SetWindowText("None");
    m_CL2LEFT.SetCheck(FALSE);
    m_ALEFT.SetCheck(FALSE);

    m_L2RIGHT.SetWindowText("None");
    m_CL2RIGHT.SetCheck(FALSE);
    m_ARIGHT.SetCheck(FALSE);

    m_L2DOWN.SetWindowText("None");
    m_CL2DOWN.SetCheck(FALSE);
    m_ADOWN.SetCheck(FALSE);

    m_L1FRONT.SetWindowText("None");
    m_CL1FRONT.SetCheck(FALSE);

    m_L1LEFT.SetWindowText("None");
    m_CL1LEFT.SetCheck(FALSE);

    m_L1RIGHT.SetWindowText("None");
    m_CL1RIGHT.SetCheck(FALSE);

    m_L1UP.SetWindowText("None");
    m_CL1UP.SetCheck(FALSE);

    m_L1DOWN.SetWindowText("None");
    m_CL1DOWN.SetCheck(FALSE);

    m_SLDSKY1.SetPos(0);
    m_SLDSKY2.SetPos(0);
}

void CSkyBoxEd::OnOK() 
{
    if (Modified)
    {
        switch(MessageBox("Do you want to save your changes?","Quit",MB_ICONQUESTION|MB_YESNOCANCEL))
        {
        case IDYES:
            OnSave();
            CDialog::OnOK();
            break;
        case IDNO:
            CDialog::OnOK();
            break;
        }
    }
    else
        CDialog::OnOK();

}


void CSkyBoxEd::OnClose() 
{
    
    MainWind->m_SkyboxWin.SetCheck(MainWind->m_SkyboxWin.GetCheck()?0:1);
    MainWind->OnSkybox();
	
	//CDialog::OnClose();
}
