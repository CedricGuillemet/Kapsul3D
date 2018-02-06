// Option.cpp: implementation of the CKOption class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

//#include "memmgr/mmgr.h"
#include <Shlwapi.h>
#include "KOption.h"

RGB CKOption::m_GridColor1;
RGB CKOption::m_GridColor2;
RGB CKOption::m_ActiveBackColor;
RGB CKOption::m_NActiveBackColor;
RGB CKOption::m_HandlesRoundColor;
RGB CKOption::m_HandlesColor;
RGB CKOption::m_ColorMesh1;
RGB CKOption::m_ColorMesh2;
RGB CKOption::m_ColorMesh3;
RGB CKOption::m_ColorMesh4;
RGB CKOption::m_ColorMesh5;
RGB CKOption::m_ColorMesh6;
RGB CKOption::m_ColorMesh7;
RGB CKOption::m_ColorMesh8;
RGB CKOption::m_ColorMesh9;
RGB CKOption::m_ColorMesh10;
int CKOption::m_Precision;
int CKOption::m_GridSpace1;
int CKOption::m_GridSpace2;
int CKOption::m_GridSpace3;
int CKOption::m_GridSpace4;
int CKOption::m_GridSpace5;
int CKOption::m_Angle1;
int CKOption::m_Angle2;
int CKOption::m_Angle3;
int CKOption::m_Angle4;
int CKOption::m_Angle5;
bool CKOption::m_ActivateMouseOver;
bool CKOption::m_OpenEmpty;
bool CKOption::m_GridBehindIso;
bool CKOption::m_GridBehindCamera;
int CKOption::m_DefaultSpamLevel;
int CKOption::m_MinimumSpamLevel;
bool CKOption::m_LogToFile;
char CKOption::m_LogFileName[MAX_PATH];
bool CKOption::m_InvertedFly;
int CKOption::m_MotionValue;
int CKOption::m_MotionIncValue;
int CKOption::m_NbUndos;
char CKOption::m_EntityXMLLocation[MAX_PATH];
bool CKOption::m_ShowSplash;
bool CKOption::m_DrawFontBack;
RGB CKOption::m_FontBackColor;
char CKOption::m_EntityDLLLocation[MAX_PATH];
bool CKOption::m_GenerateUV;
int CKOption::m_CameraFov;
bool CKOption::m_RecursePrefab;
char CKOption::m_TTFFont[MAX_PATH];
int CKOption::m_FontSize;
bool CKOption::m_ShowHandlesCamera;
bool CKOption::m_ShowGridCamera;
bool CKOption::m_EnableAutoSave;
char CKOption::m_AutoSaveDir[MAX_PATH];
int CKOption::m_AutoSaveDelay;
RGB CKOption::m_Centroid;
char CKOption::m_DefTex[MAX_PATH];
char CKOption::m_Renderer[MAX_PATH];

#define NB_OPTIONS 57
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
OptEntry CKOption::OptValues[NB_OPTIONS]={  
	{"Grid Color 1",OPT_COLOR,&CKOption::m_GridColor1},
	{"Grid Color 2",OPT_COLOR,&CKOption::m_GridColor2}, 
	{"Active View Back",OPT_COLOR,&CKOption::m_ActiveBackColor},
	{"Non Active View Back",OPT_COLOR,&CKOption::m_NActiveBackColor},
	{"Handles round",OPT_COLOR,&CKOption::m_HandlesRoundColor},
	{"Handles",OPT_COLOR,&CKOption::m_HandlesColor},
	{"Color 1",OPT_COLOR,&CKOption::m_ColorMesh1},
	{"Color 2",OPT_COLOR,&CKOption::m_ColorMesh2},
	{"Color 3",OPT_COLOR,&CKOption::m_ColorMesh3},
	{"Color 4",OPT_COLOR,&CKOption::m_ColorMesh4},
	{"Color 5",OPT_COLOR,&CKOption::m_ColorMesh5},
	{"Color 6",OPT_COLOR,&CKOption::m_ColorMesh6},
	{"Color 7",OPT_COLOR,&CKOption::m_ColorMesh7},
	{"Color 8",OPT_COLOR,&CKOption::m_ColorMesh8},
	{"Color 9",OPT_COLOR,&CKOption::m_ColorMesh9},
	{"Color 10",OPT_COLOR,&CKOption::m_ColorMesh10},
	{"Selection Precision",OPT_INT,&CKOption::m_Precision},
	{"Grid Spacing 1",OPT_INT,&CKOption::m_GridSpace1},
	{"Grid Spacing 2",OPT_INT,&CKOption::m_GridSpace2},
	{"Grid Spacing 3",OPT_INT,&CKOption::m_GridSpace3},
	{"Grid Spacing 4",OPT_INT,&CKOption::m_GridSpace4},
	{"Grid Spacing 5",OPT_INT,&CKOption::m_GridSpace5},
	{"Activate View on Mouse Over",OPT_BOOL,&CKOption::m_ActivateMouseOver},
	{"Open an empty document at startup",OPT_BOOL,&CKOption::m_OpenEmpty},
	{"Grid behind all for iso views",OPT_BOOL,&CKOption::m_GridBehindIso},
	{"Grid behind all for camera views",OPT_BOOL,&CKOption::m_GridBehindCamera},
	{"Default spam level",OPT_INT,&CKOption::m_DefaultSpamLevel},
	{"Show spam higher or equal",OPT_INT,&CKOption::m_MinimumSpamLevel},
	{"Write log to file",OPT_BOOL,&CKOption::m_LogToFile},
	{"Log file path",OPT_STRING,&CKOption::m_LogFileName},
	{"Invert Free Look",OPT_BOOL,&CKOption::m_InvertedFly},
	{"Motion value",OPT_INT,&CKOption::m_MotionValue},
	{"Motion value inc",OPT_INT,&CKOption::m_MotionIncValue},
	{"Undo levels",OPT_INT,&CKOption::m_NbUndos},
	{"Entities.xml Location",OPT_STRING,&CKOption::m_EntityXMLLocation},
	{"Show splash at startup",OPT_BOOL,&CKOption::m_ShowSplash},
	{"Solid label background",OPT_BOOL,&CKOption::m_DrawFontBack},
	{"Label color",OPT_COLOR,&CKOption::m_FontBackColor},
	{"Entity.dll Location",OPT_STRING,&CKOption::m_EntityDLLLocation},
	{"Auto generate UV coords by default",OPT_BOOL,&CKOption::m_GenerateUV},
	{"Camera FOV",OPT_INT,&CKOption::m_CameraFov},
	{"Recursive prefabs folders",OPT_BOOL,&CKOption::m_RecursePrefab},
	{"Truetype Font",OPT_STRING,&CKOption::m_TTFFont},
	{"Views name size",OPT_INT,&CKOption::m_FontSize},
	{"Show handles in camera views",OPT_BOOL,&CKOption::m_ShowHandlesCamera},
	{"Show grid in camera views",OPT_BOOL,&CKOption::m_ShowGridCamera},
	{"Enable autosave",OPT_BOOL,&CKOption::m_EnableAutoSave},
	{"Autosave directory",OPT_STRING,&CKOption::m_AutoSaveDir},
	{"Autosave delay",OPT_INT,&CKOption::m_AutoSaveDelay},
	{"Centroid",OPT_COLOR,&CKOption::m_Centroid},
	{"Default texture",OPT_STRING,&CKOption::m_DefTex},
	{"Renderer",OPT_STRING,&CKOption::m_Renderer},
	{"Angle Snap 1",OPT_INT,&CKOption::m_Angle1},
	{"Angle Snap 2",OPT_INT,&CKOption::m_Angle2},
	{"Angle Snap 3",OPT_INT,&CKOption::m_Angle3},
	{"Angle Snap 4",OPT_INT,&CKOption::m_Angle4},
	{"Angle Snap 5",OPT_INT,&CKOption::m_Angle5},
	};				

DWORD CKOption::GetDWORDColor(RGB *Dest)
{
	return ((Dest->bRed<<16)+(Dest->bGreen<<8)+Dest->bBlue);

}

void CKOption::ReadColor(char *Value,RGB *Dest)
{
	UINT tmp;
	sscanf(Value,"%x",&tmp);
	Dest->bRed=(tmp&0xff0000)>>16;
	Dest->bGreen=(tmp&0xff00)>>8;
	Dest->bBlue=(tmp&0xff);
}

void CKOption::ReadInt(char *Value,int *Dest)
{
	sscanf(Value,"%d",Dest);
	
}

void CKOption::ReadString(char *Value,char *Dest)
{
	strcpy(Dest,Value);
}

void CKOption::ReadBool(char *Value,bool *Dest)
{
	int tmp;
	sscanf(Value,"%d",&tmp);
	*Dest=(tmp!=0);
}


int CKOption::FindByName(char *Name)
{
	int i;
	for (i=0;i<NB_OPTIONS;i++)
	{
		// Search IS NOT case-sensitive
		if (StrCmpI(Name,OptValues[i].Name)==0)
		{
			return i;
		}
	}
	return -1;
}

void CKOption::ReadUserFileValue(char *Name,char *Value)
{
	int nb=FindByName(Name);
	if (nb!=-1)
	{
		switch (OptValues[nb].Type)
		{
		case OPT_BOOL:
			ReadBool(Value,(bool*)OptValues[nb].Dest);
			break;
		case OPT_STRING:
			ReadString(Value,(char*)OptValues[nb].Dest);
			break;
		case OPT_INT:
			ReadInt(Value,(int*)OptValues[nb].Dest);
			break;
		case OPT_COLOR:
			ReadColor(Value,(RGB*)OptValues[nb].Dest);
			break;
		}
	}
}


int CKOption::GetInt(char *Name)
{
	int nb=FindByName(Name);
	if (nb!=-1)
		return (*(int*)OptValues[nb].Dest);
	return 0;
}

DWORD CKOption::GetColor(char *Name)
{
	int nb=FindByName(Name);
	if (nb!=-1)
		return GetDWORDColor((RGB*)OptValues[nb].Dest);
	return 0;
}

bool CKOption::GetBool(char *Name)
{
	int nb=FindByName(Name);
	if (nb!=-1)
		return (*(bool*)OptValues[nb].Dest);
	return false;
}

char* CKOption::GetString(char *Name)
{
	int nb=FindByName(Name);
	if (nb!=-1)
		return (char*)(OptValues[nb].Dest);
	return NULL;
}


void CKOption::BuildXmlOptions(CString &Target)
{
	CString tmp,Fmt;
	Target="<?xml version=\"1.0\" standalone=\"yes\"?>\n<body>\n<!-- \n		Description of User options \n    -->\n";

	int i;

	// standards

	for (i=0;i<NB_OPTIONS;i++)
	{
		switch (OptValues[i].Type)
		{
		case OPT_BOOL:
			tmp.Format("<Groupvalues name=\"%s\" value=\"%d\" />\n",OptValues[i].Name,(*(bool*)OptValues[i].Dest));
			break;
		case OPT_STRING:
			tmp.Format("<Groupvalues name=\"%s\" value=\"%s\" />\n",OptValues[i].Name,(char*)(OptValues[i].Dest));
			break;
		case OPT_INT:
			tmp.Format("<Groupvalues name=\"%s\" value=\"%d\" />\n",OptValues[i].Name,(*(int*)OptValues[i].Dest));
			break;
		case OPT_COLOR:
			tmp.Format("<Groupvalues name=\"%s\" value=\"%x\" />\n",OptValues[i].Name,GetDWORDColor((RGB*)OptValues[i].Dest));
			break;
		}
		Target+=tmp;
	}
	// Map paths

	Target+="<Paths>\n";
	Target+="<MapPaths>\n";

	for (i=0;i<GetnbMapDir();i++)
	{
		tmp.Format("<Value Pth=\"%s\" />\n",GetMapDir(i));
		Target+=tmp;
	}

	Target+="</MapPaths>\n";
	
	// Prefab paths
	Target+="<PrefabPaths>\n";
	for (i=0;i<GetnbPrefabDir();i++)
	{
		tmp.Format("<Value Pth=\"%s\" />\n",GetPrefabDir(i));
		Target+=tmp;
	}

	Target+="</PrefabPaths>\n";


	Target+="</Paths>\n";

	// end
	Target+="</body>\n";
}
void CKOption::WriteOptions(void)
{
	CString daOpts;
	BuildXmlOptions(daOpts);
	CString OptUserName;

	OptUserName=m_AppDir;
	OptUserName+="UserOptions.xml";
	FILE *fp=fopen(OptUserName.GetBuffer(0),"wt");
	if (fp!=NULL)
	{
		fputs(daOpts,fp);
		fclose(fp);
	}
	else
		DMPOutputString("Unable to save user options.\r\n");
}

CKOption::CKOption(CWinApp *theApp)
{
    int i=0;
    CString temp,temp2;
    
	// MAP Paths
	char value[256],value2[256];
	char CurDir[512];
	nbMapDir=0;
	nbPrefabDir=0;

	GetCurrentDirectory(512,CurDir);
	m_AppDir=CurDir;
	m_AppDir+="\\";


	/*
    temp.Format("MapPath%d",i);
	temp2=theApp->GetProfileString("MapPath",temp);
	while(temp2!="")
	{
		AddMapDir(temp2);
		i++;
		temp.Format("MapPath%d",i);
		temp2=theApp->GetProfileString("MapPath",temp);
	}

	i=0;

	temp.Format("PrefabPath%d",i);
	temp2=theApp->GetProfileString("PrefabPath",temp);
	while(temp2!="")
	{
		AddPrefabDir(temp2);
		i++;
		temp.Format("PrefabPath%d",i);
		temp2=theApp->GetProfileString("PrefabPath",temp);
	}
	*/
	// Default Options
	{
		init init;
		tree_parser parser("options.xml");

		if (!parser) 
			MessageBox(NULL,"Options.xml is corrupted.\r\nPlease Reinstall Kapsul.","Fatal Error",MB_ICONERROR|MB_OK);
		else
		{
		
			node &root = parser.get_root_node();

			node::const_iterator child(root.begin()), child_end(root.end());
			for (; child != child_end; ++child) 
			{
				if (child->is_text()) continue;


				// standards options
				if (strcmp(child->get_name() ,"Options")==0)
				{
					node::const_iterator child2(child->begin()), child_end(child->end());
					for (; child2 != child_end; ++child2) 
					{
						if (child2->is_text()) continue;
							
						if (strcmp(child2->get_name() ,"Group")==0)
						{
							node::const_iterator child3(child2->begin()), child_end(child2->end());
							for (; child3 != child_end; ++child3) 
							{
								if (child3->is_text()) continue;

								if (strcmp(child3->get_name() ,"Groupvalues")==0)
								{
									
									child3->get_attr("name",value);
									child3->get_attr("default",value2);
									ReadUserFileValue(value,value2);
								}
							}
						}
					}
				}
				// paths
				if (strcmp(child->get_name() ,"Paths")==0)
				{
					node::const_iterator child2(child->begin()), child_end(child->end());
					for (; child2 != child_end; ++child2) 
					{
						if (child2->is_text()) continue;
							
						// MapPaths
						if (strcmp(child2->get_name() ,"MapPaths")==0)
						{
							node::const_iterator child3(child2->begin()), child_end(child2->end());
							for (; child3 != child_end; ++child3) 
							{
								if (child3->is_text()) continue;
								if (strcmp(child3->get_name() ,"Value")==0)
								{
									child3->get_attr("Pth",value);
									AddMapDir(CString(value));
								}
							}
						}
						// PrefabPaths
						if (strcmp(child2->get_name() ,"PrefabPaths")==0)
						{
							node::const_iterator child3(child2->begin()), child_end(child2->end());
							for (; child3 != child_end; ++child3) 
							{
								if (child3->is_text()) continue;
								if (strcmp(child3->get_name() ,"Value")==0)
								{
									child3->get_attr("Pth",value);
									AddPrefabDir(CString(value));
								}
							}
						}
					}
				}
			}
		}
	}
	// Current User Options
	{
		init init;
		tree_parser parser("UserOptions.xml");

		if (!parser) 
			;//DMPOutputString("UserOptions.xml is corrupted.\r\nPlease go to the option dialog to update it.\r\nDefault options are loaded.\r\n");
		else
		{
			DelAllMapDir();
			DelAllPrefabDir();

			node &root = parser.get_root_node();

			node::const_iterator child(root.begin()), child_end(root.end());
			for (; child != child_end; ++child) 
			{
				if (child->is_text()) continue;

				if (strcmp(child->get_name() ,"Groupvalues")==0)
				{
					child->get_attr("name",value);
					child->get_attr("value",value2);
					ReadUserFileValue(value,value2);
				}

				if (strcmp(child->get_name() ,"Paths")==0)
				{
					node::const_iterator child2(child->begin()), child_end(child->end());
					for (; child2 != child_end; ++child2) 
					{
						if (child2->is_text()) continue;
							
						// MapPaths
						if (strcmp(child2->get_name() ,"MapPaths")==0)
						{
							node::const_iterator child3(child2->begin()), child_end(child2->end());
							for (; child3 != child_end; ++child3) 
							{
								if (child3->is_text()) continue;
								if (strcmp(child3->get_name() ,"Value")==0)
								{
									child3->get_attr("Pth",value);
									AddMapDir(CString(value));
								}
							}
						}
						// PrefabPaths
						if (strcmp(child2->get_name() ,"PrefabPaths")==0)
						{
							node::const_iterator child3(child2->begin()), child_end(child2->end());
							for (; child3 != child_end; ++child3) 
							{
								if (child3->is_text()) continue;
								if (strcmp(child3->get_name() ,"Value")==0)
								{
									child3->get_attr("Pth",value);
									AddPrefabDir(CString(value));
								}
							}
						}
					}
				}
			}
		}
	}


}

CKOption::~CKOption()
{
    DelAllMapDir();
}

// -- Maps Dirs -----------------------------------------------------------------

void CKOption::AddMapDir(CString daMapDir)
{
    OptMapDirs.push_back(daMapDir);
	nbMapDir++;
}

void CKOption::DelAllMapDir(void)
{
    OptMapDirs.erase(OptMapDirs.begin(),OptMapDirs.end());
	nbMapDir=0;
}

int CKOption::GetnbMapDir(void)
{
    return nbMapDir;//OptMapDirs.size();
}

CString CKOption::GetMapDir(int Number)
{
    if (Number<nbMapDir)
    {
        return OptMapDirs[Number];
    }
    return "";
}

// -- Prefab dirs  -----------------------------------------------------------------

void CKOption::AddPrefabDir(CString daPrefabDir)
{
    PrefabDirs.push_back(daPrefabDir);
	nbPrefabDir++;
}

void CKOption::DelAllPrefabDir(void)
{
    PrefabDirs.erase(PrefabDirs.begin(),PrefabDirs.end());
	nbPrefabDir=0;
}

int CKOption::GetnbPrefabDir(void)
{
    return nbPrefabDir;//PrefabDirs.size();
}

CString CKOption::GetPrefabDir(int Number)
{
    if (Number<nbPrefabDir)
    {
        return PrefabDirs[Number];
    }
    return "";
}

// retrieves Methods

bool CKOption::OpenEmpty()
{ 
	return m_OpenEmpty;
}

RGB *CKOption::GridColor1()
{
	return &m_GridColor1;
}
RGB *CKOption::GridColor2()
{
	return &m_GridColor2;
}
RGB *CKOption::ActiveBackColor()
{
	return &m_ActiveBackColor;
}
RGB *CKOption::NActiveBackColor()
{
	return &m_NActiveBackColor;
}
RGB *CKOption::HandlesRoundColor()
{
	return &m_HandlesRoundColor;
}
RGB *CKOption::HandlesColor()
{
	return &m_HandlesColor;
}
RGB *CKOption::ColorMesh(int MeshNb)
{
	switch (MeshNb)
	{
	case 0:
		return &m_ColorMesh1;
		break;
	case 1:
		return &m_ColorMesh2;
		break;
	case 2:
		return &m_ColorMesh3;
		break;
	case 3:
		return &m_ColorMesh4;
		break;
	case 4:
		return &m_ColorMesh5;
		break;
	case 5:
		return &m_ColorMesh6;
		break;
	case 6:
		return &m_ColorMesh7;
		break;
	case 7:
		return &m_ColorMesh8;
		break;
	case 8:
		return &m_ColorMesh9;
		break;
	case 9:
		return &m_ColorMesh10;
		break;

	}
	return &m_ColorMesh1;
}

int CKOption::Precision()
{
	return m_Precision;
}
int CKOption::GridSpace(int GridSnapNb)
{
	switch (GridSnapNb)
	{
	case 0:
		return m_GridSpace1;
		break;
	case 1:
		return m_GridSpace2;
		break;
	case 2:
		return m_GridSpace3;
		break;
	case 3:
		return m_GridSpace4;
		break;
	case 4:
		return m_GridSpace5;
		break;
	}
	return m_GridSpace1;
}

int CKOption::AngleSnap(int AngleSnapNb)
{
	switch (AngleSnapNb)
	{
	case 0:
		return m_Angle1;
		break;
	case 1:
		return m_Angle2;
		break;
	case 2:
		return m_Angle3;
		break;
	case 3:
		return m_Angle4;
		break;
	case 4:
		return m_Angle5;
		break;
	}
	return m_Angle1;
}

bool CKOption::ActivateMouseOver()
{
	return m_ActivateMouseOver;
}
bool CKOption::GridBehindIso()
{
	return m_GridBehindIso;
}
bool CKOption::GridBehindCamera()
{
	return m_GridBehindCamera;
}
int CKOption::DefaultSpamLevel()
{
	return m_DefaultSpamLevel;
}
int CKOption::MinimumSpamLevel()
{
	return m_MinimumSpamLevel;
}
bool CKOption::LogToFile()
{
	return m_LogToFile;
}
char* CKOption::LogFileName()
{
	return m_LogFileName;
}
bool CKOption::InvertedFly()
{
	return m_InvertedFly;
}
int CKOption::MotionValue()
{
	return m_MotionValue;
}
int CKOption::MotionIncValue()
{
	return m_MotionIncValue;
}
int CKOption::NbUndos()
{
	return m_NbUndos;
}
char *CKOption::EntityXMLLocation()
{
	return m_EntityXMLLocation;
}
bool CKOption::ShowSplash()
{
	return m_ShowSplash;
}
bool CKOption::DrawFontBack()
{
	return m_DrawFontBack;
}
RGB *CKOption::FontBackColor()
{
	return &m_FontBackColor;
}
char *CKOption::EntityDLLLocation()
{
	return m_EntityDLLLocation;
}
bool CKOption::GenerateUV()
{
	return m_GenerateUV;
}
bool CKOption::RecursePrefab()
{
	return m_RecursePrefab;
}
int CKOption::CameraFov()
{
	return m_CameraFov;
}

char *CKOption::GetFont()
{
	return m_TTFFont;
}

int CKOption::GetFontSize()
{
	return m_FontSize;
}

bool CKOption::GetShowHandlesCamera()
{
	return m_ShowHandlesCamera;
}

bool CKOption::GetShowGridCamera()
{
	return m_ShowGridCamera;
}

bool CKOption::GetEnableAutoSave()
{
	return m_EnableAutoSave;
}

char *CKOption::GetAutoSaveDir()
{
	return m_AutoSaveDir;
}

int CKOption::GetAutoSaveDelay()
{
	return m_AutoSaveDelay;
}

RGB *CKOption::GetCentroid()
{
	return &m_Centroid;
}

char *CKOption::GetDefaultTexture()
{
	return m_DefTex;
}

char *CKOption::GetRenderer()
{
	return m_Renderer;
}
