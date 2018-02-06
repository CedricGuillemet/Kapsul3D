// DumpInfos.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "DumpInfos.h"

#include <atlbase.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define INFO_SYSTEM_INFO "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0"

/////////////////////////////////////////////////////////////////////////////
// CDumpInfos dialog


CDumpInfos::CDumpInfos(CWnd* pParent /*=NULL*/)
	: CDialog(CDumpInfos::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDumpInfos)
	//}}AFX_DATA_INIT
}


void CDumpInfos::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDumpInfos)
	DDX_Control(pDX, IDC_EXT_EDIT, m_ExtEDit);
	DDX_Control(pDX, IDC_VERSION_EDIT, m_RendererVersion);
	DDX_Control(pDX, IDC_RENDERER_EDIT, m_RendererEdit);
	DDX_Control(pDX, IDC_VENDOR_EDIT, m_VendorEdit);
	DDX_Control(pDX, IDC_SKELETTON, m_Skeletton);
	DDX_Control(pDX, IDC_SHAPE, m_Shape);
	DDX_Control(pDX, IDC_SEGMENT, m_Segment);
	DDX_Control(pDX, IDC_OBJVERT, m_ObjVert);
	DDX_Control(pDX, IDC_OBJFACE, m_ObjFace);
	DDX_Control(pDX, IDC_OBJ, m_Obj);
	DDX_Control(pDX, IDC_CAMERA, m_Camera);
	DDX_Control(pDX, IDC_BONE, m_Bone);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDumpInfos, CDialog)
	//{{AFX_MSG_MAP(CDumpInfos)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_DUMP_TO_FILE, OnDumpToFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

extern "C" int obj,objvert,objface,camera,shape,segment,spot,omni,skeletton,bone,emitter;
extern "C" CString szVendor,szVersion,szRenderer,szSupportedExt;

/////////////////////////////////////////////////////////////////////////////
// CDumpInfos message handlers

void CDumpInfos::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	char tmpStr[64];

	m_Bone.SetWindowText(itoa(bone,tmpStr,10));
	m_Camera.SetWindowText(itoa(camera,tmpStr,10));
	m_Obj.SetWindowText(itoa(obj,tmpStr,10));
	m_ObjFace.SetWindowText(itoa(objface,tmpStr,10));
	m_ObjVert.SetWindowText(itoa(objvert,tmpStr,10));
	m_Shape.SetWindowText(itoa(shape,tmpStr,10));
	m_Segment.SetWindowText(itoa(segment,tmpStr,10));
	m_Skeletton.SetWindowText(itoa(skeletton,tmpStr,10));
	m_VendorEdit.SetWindowText(szVendor);
	m_RendererVersion.SetWindowText(szVersion);
	m_RendererEdit.SetWindowText(szRenderer);
}

BOOL CDumpInfos::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDumpInfos::Info_DumpToFile(LPCSTR szFileName)
{
 FILE *p = fopen(szFileName,"wt+");
 if(p)
 {
  fprintf(p,"----------------------------------------");
  fprintf(p,"\n esque software's Kapsul debug output");
  fprintf(p,"\n----------------------------------------");


  fprintf(p,"\n\nKapsul's current session details:\n");

  CString temp;
  

  // -> Dump kapsul's desktop info
  m_Bone.GetWindowText(temp);
  fprintf(p,"\n Bones : %s",temp.GetBuffer(1));

  m_Camera.GetWindowText(temp);
  fprintf(p,"\n Cameras : %s",temp.GetBuffer(1));

  m_Obj.GetWindowText(temp);
  fprintf(p,"\n Objects : %s",temp.GetBuffer(1));

  m_ObjFace.GetWindowText(temp);
  fprintf(p,"\n\t Faces : %s",temp.GetBuffer(1));

  m_ObjVert.GetWindowText(temp);
  fprintf(p,"\n\t Vertices : %s",temp.GetBuffer(1));

  m_Shape.GetWindowText(temp);
  fprintf(p,"\n Shapes : %s",temp.GetBuffer(1));

  m_Segment.GetWindowText(temp);
  fprintf(p,"\n\t Segments : %s",temp.GetBuffer(1));

  m_Skeletton.GetWindowText(temp);
  fprintf(p,"\n Skeleton : %s",temp.GetBuffer(1));


  // -> Dump OGL driver shit
  fprintf(p,"\n\nOpenGL driver information:\n");

  m_VendorEdit.GetWindowText(temp);
  fprintf(p,"\n Hardware Vendor : %s",temp.GetBuffer(1));

  m_RendererEdit.GetWindowText(temp);
  fprintf(p,"\n Renderer : %s",temp.GetBuffer(1));

  m_RendererVersion.GetWindowText(temp);
  fprintf(p,"\n Driver Version : %s",temp.GetBuffer(1));


  // -> Dump System info
  fprintf(p,"\n\nSystem Information:\n");

  CRegKey rkUserSetting;

  if(rkUserSetting.Open(HKEY_LOCAL_MACHINE,INFO_SYSTEM_INFO, KEY_QUERY_VALUE) == ERROR_SUCCESS)
  {
	char szCPUInfo[255];
    DWORD dwMhz = 0L,dwCount = 255;

    if(rkUserSetting.QueryValue(szCPUInfo,"ProcessorNameString",&dwCount) != ERROR_SUCCESS)
		fprintf(p,"\nCPU ID : Unable to determine CPU ID String.");
	else
		fprintf(p,"\nCPU ID : %s", szCPUInfo);

    if(rkUserSetting.QueryValue(dwMhz,"~MHz") != ERROR_SUCCESS)
		fprintf(p,"\nCPU Speed : Unable to determine CPU speed.");
	else
		fprintf(p,"\nCPU Speed : %i Mhz",(int)dwMhz);



    rkUserSetting.Close();
  }
  else
  {
   fprintf(p,"\n Kapsul has not been able to retrieve information about the system");
  }


  // -> Dump footer (date)
  COleDateTime dtDate;
  dtDate = COleDateTime::GetCurrentTime();


  fprintf(p,"\n\n----------------------------------------");
  fprintf(p,"\n Creted on %s",dtDate.Format(_T("%A, %B %d, %Y")).GetBuffer(1));

  fclose(p);
 }else
  MessageBox("There was an error while creating the file","info.dll error",MB_OK);

}

void CDumpInfos::OnDumpToFile() 
{
  // Dump some usefull info to file	
  static char szSaveFilter[] = "Text File (*.txt)|*.txt|All Files (*.*)|*.*||";

  CFileDialog dlg(FALSE,".txt","info.txt",OFN_OVERWRITEPROMPT|OFN_CREATEPROMPT,szSaveFilter,this);
  if(dlg.DoModal() == IDOK)
  {
	Info_DumpToFile(dlg.GetPathName());
  }
}

