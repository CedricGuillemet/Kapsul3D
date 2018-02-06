// KInstall.cpp: implementation of the CKInstall class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "kapsulse.h"
#include "KInstall.h"
#include <direct.h>
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CKPluginManager *GKPlugins;
extern CKapsulApp theApp;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

static char OptXml[]={"<?xml version=\"1.0\" standalone=\"yes\"?>"
"<body>\n"
"\n"
"<!-- \n"
"Description of All options \n"
"each name attribute inside GroupValues must be unique\n"
"-->\n"
"\n"
"<Options>\n"
"\n"
"<Group value=\"Colors\">\n"
"<Groupvalues name=\"Grid Color 1\" type=\"color\" default=\"535151\" />\n"
"<Groupvalues name=\"Grid Color 2\" type=\"color\" default=\"6d6b6b\" />\n"
"<Groupvalues name=\"Active View Back\" type=\"color\" default=\"858585\" />\n"
"<Groupvalues name=\"Non Active View Back\" type=\"color\" default=\"847c7b\" />\n"
"<Groupvalues name=\"Handles round\" type=\"color\" default=\"ffffff\" />\n"
"<Groupvalues name=\"Handles\" type=\"color\" default=\"ffffff\" />\n"
"<Groupvalues name=\"Centroid\" type=\"color\" default=\"ffffff\" />\n"
"</Group>\n"
"\n"
"<Group value=\"Automatic brush color\">\n"
"<Groupvalues name=\"Color 1\" type=\"color\" default=\"2aa5\" />\n"
"<Groupvalues name=\"Color 2\" type=\"color\" default=\"2068ff\" />\n"
"<Groupvalues name=\"Color 3\" type=\"color\" default=\"5badff\" />\n"
"<Groupvalues name=\"Color 4\" type=\"color\" default=\"d7ff\" />\n"
"<Groupvalues name=\"Color 5\" type=\"color\" default=\"8b\" />\n"
"<Groupvalues name=\"Color 6\" type=\"color\" default=\"9300\" />\n"
"<Groupvalues name=\"Color 7\" type=\"color\" default=\"e0ffff\" />\n"
"<Groupvalues name=\"Color 8\" type=\"color\" default=\"8b8368\" />\n"
"<Groupvalues name=\"Color 9\" type=\"color\" default=\"ffff\" />\n"
"<Groupvalues name=\"Color 10\" type=\"color\" default=\"800080\" />\n"
"</Group>\n"
"\n"
"<Group value=\"Edit\">\n"
"<Groupvalues name=\"Selection Precision\" type=\"slider\" value0=\"1\" value1=\"10\" default=\"3\" />\n"
"<Groupvalues name=\"Grid Spacing 1\" type=\"integer\" default=\"8\" />\n"
"<Groupvalues name=\"Grid Spacing 2\" type=\"integer\" default=\"16\" />\n"
"<Groupvalues name=\"Grid Spacing 3\" type=\"integer\" default=\"32\" />\n"
"<Groupvalues name=\"Grid Spacing 4\" type=\"integer\" default=\"64\" />\n"
"<Groupvalues name=\"Grid Spacing 5\" type=\"integer\" default=\"128\" />\n"
"<Groupvalues name=\"Angle Snap 1\" type=\"integer\" default=\"2\" />\n"
"<Groupvalues name=\"Angle Snap 2\" type=\"integer\" default=\"4\" />\n"
"<Groupvalues name=\"Angle Snap 3\" type=\"integer\" default=\"5\" />\n"
"<Groupvalues name=\"Angle Snap 4\" type=\"integer\" default=\"10\" />\n"
"<Groupvalues name=\"Angle Snap 5\" type=\"integer\" default=\"15\" />\n"
"<Groupvalues name=\"Activate View on Mouse Over\" type=\"bool\" default=\"0\" />\n"
"<Groupvalues name=\"Open an empty document at startup\" type=\"bool\" default=\"1\" />\n"
"<Groupvalues name=\"Grid behind all for iso views\" type=\"bool\" default=\"1\" />\n"
"<Groupvalues name=\"Grid behind all for camera views\" type=\"bool\" default=\"0\" />\n"
"<Groupvalues name=\"Auto generate UV coords by default\" type=\"bool\" default=\"1\" />\n"
"<Groupvalues name=\"Show handles in camera views\" type=\"bool\" default=\"1\" />\n"
"<Groupvalues name=\"Show grid in camera views\" type=\"bool\" default=\"1\" />\n"
"</Group>\n"
"\n"
"<Group value=\"Logs\">\n"
"<Groupvalues name=\"Write log to file\" type=\"bool\" default=\"0\" />\n"
"<Groupvalues name=\"Default spam level\" type=\"slider\" default=\"3\" value0=\"1\" value1=\"5\" />\n"
"<Groupvalues name=\"Show spam higher or equal\" type=\"slider\" default=\"3\" value0=\"1\" value1=\"5\" />\n"
"<Groupvalues name=\"Log file path\" type=\"string\" default=\"$KapsulLog.txt\" />\n"
"</Group>\n"
"\n"
"<Group value=\"Fly\">\n"
"<Groupvalues name=\"Invert Free Look\" type=\"bool\" default=\"1\" />\n"
"<Groupvalues name=\"Motion value\" type=\"integer\" default=\"50\" />\n"
"<Groupvalues name=\"Motion value inc\" type=\"slider\" default=\"2\" value0=\"1\" value1=\"100\" />\n"
"<Groupvalues name=\"Camera FOV\" type=\"slider\" default=\"60\" value0=\"1\" value1=\"180\" />\n"
"</Group>\n"
"\n"
"<Group value=\"Undos\">\n"
"<Groupvalues name=\"Undo levels\" type=\"integer\" default=\"10\" />\n"
"</Group>\n"
"\n"
"<Group value=\"Entities\">\n"
"<Groupvalues name=\"Entity.dll Location\" type=\"string\" default=\"$entity.dll\" />\n"
"<Groupvalues name=\"Entities.xml Location\" type=\"string\" default=\"$entities.xml\" />\n"
"</Group>\n"
"\n"
"<Group value=\"Misc\">\n"
"<Groupvalues name=\"Show splash at startup\" type=\"bool\" default=\"1\" />\n"
"<Groupvalues name=\"Solid label background\" type=\"bool\" default=\"0\" />\n"
"<Groupvalues name=\"Label color\" type=\"color\" default=\"0x00000000\" />\n"
"<Groupvalues name=\"Recursive prefabs folders\" type=\"bool\" default=\"1\" />\n"
"<Groupvalues name=\"Truetype Font\" type=\"string\" default=\"$$arial.ttf\" />\n"
"<Groupvalues name=\"Views name size\" type=\"slider\" default=\"12\" value0=\"10\" value1=\"20\" />\n"
"<Groupvalues name=\"Default texture\" type=\"string\" default=\"$DefaultTexture.bmp\" />\n"
"<Groupvalues name=\"Renderer\" type=\"string\" default=\"NULL\" />\n"
"</Group>\n"
"<Group value=\"Autosave\">\n"
"<Groupvalues name=\"Enable autosave\" type=\"bool\" default=\"0\" />\n"
"<Groupvalues name=\"Autosave directoy\" type=\"string\" default=\"$Autosaves\\\" />\n"
"<Groupvalues name=\"Autosave delay\" type=\"slider\" default=\"10\" value0=\"1\" value1=\"60\" />\n"
"</Group>\n"
"\n"
"</Options>\n"
"\n"
"<Paths>\n"
"<MapPaths>\n"
"<Value Pth=\"$\" />\n"
"<Value Pth=\"$Textures\" />\n"
"</MapPaths>\n"
"<PrefabPaths>\n"
"<Value Pth=\"$Examples\" />\n"
"</PrefabPaths>\n"
"</Paths>\n"
"</body>\n"};

CKInstall::CKInstall()
{

}

CKInstall::~CKInstall()
{

}

void CKInstall::WriteOptionsXML(void)
{
	char CurDir[512],fontdir[512];
	GetCurrentDirectory(512,CurDir);
	strcat(CurDir,"\\");

	GetWindowsDirectory(fontdir,512);
	strcat(fontdir,"\\Fonts\\");

	FILE *fp=fopen("Options.xml","wt");
	if (fp!=NULL)
	{
		for (int i=0;i<strlen(OptXml);i++)
		{
			if (OptXml[i]=='$')
			{
				if (OptXml[i+1]=='$')
					fwrite(fontdir,strlen(fontdir),1,fp);
				else
					if (OptXml[i-1]!='$')
						fwrite(CurDir,strlen(CurDir),1,fp);
			}
			else
			{
				fputc(OptXml[i],fp);
			}
		}
		fclose(fp);
	}
}

void CKInstall::RegisterFileTypes(void)
{
	int i;
	// register files ext
	for (i=0;i<GKPlugins->FilePlugins.size();i++)
	{
		CGCFileTypeAccess TheFTA;
		CString tmpext;

		tmpext=GKPlugins->FilePlugins[i]->GetFileExtension();
		if (tmpext.IsEmpty())
		{
			CString ErrorMsg;
			ErrorMsg.Format("KM_GETFILEXT message in plugin '%s' must return extension.\rKapsul will now exit.",GKPlugins->FilePlugins[i]->GetName());
			MessageBox(NULL,ErrorMsg,"Fatal error",MB_ICONERROR|MB_OK);
			//PostQuitMessage(0);
			exit(-1);
			return ;
		}
		tmpext=tmpext.Mid(1);

		// get full file path to program executable file
		TCHAR	szProgPath[MAX_PATH * 2];
		::GetModuleFileName(NULL, szProgPath, sizeof(szProgPath)/sizeof(TCHAR));
		//strcpy(szProgPath,"D:\\KapsulCVS\\src\\WorkSpace\\KapsulSE.exe.lnk");

		CString csTempText;

		TheFTA.SetExtension(tmpext);

		// just pass file path in quotes on command line
		csTempText  = szProgPath;
		csTempText += " %1";
		TheFTA.SetShellOpenCommand(csTempText);
		TheFTA.SetDocumentShellOpenCommand(csTempText);

		CString extDesc="Kapsul ";
		tmpext.MakeUpper();

		extDesc+=tmpext;
		extDesc+=" Document";
		TheFTA.SetDocumentDescription(extDesc);
		CString clsname="Kapsul.";
		clsname+=tmpext;

		TheFTA.SetDocumentClassName(clsname);

		// use first icon in program
		char buffer[_MAX_PATH];
		_getcwd( buffer, _MAX_PATH );
		
		
		GetModuleFileName(GKPlugins->FilePlugins[i]->m_hInst,buffer,_MAX_PATH);

		csTempText  = buffer;
		csTempText += ",0";
		TheFTA.SetDocumentDefaultIcon(csTempText);

		// set the necessary registry entries	
		TheFTA.RegSetAllInfo();

	}
	SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST,0,0);
}

void CKInstall::StoreProgramPath(void)
{
	char buffer[512];
	GetCurrentDirectory(512,buffer);
	theApp.WriteProfileString("Program","ProgramDir",buffer);
}

void CKInstall::SetProgramPath(void)
{
	//char buffer[512];
	CString path;
	path=theApp.GetProfileString("Program","ProgramDir",NULL);
	SetCurrentDirectory(path);	
}


