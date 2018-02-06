#include "stdafx.h"
#include <Kapsul3D.h>

#include "resource.h"
#include <commctrl.h>
#include "zip_src/ZipArchive.h"

#include <io.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>


// call in C only, Mfc in plugins are hard to implement.


HINSTANCE g_Inst;

static AFX_EXTENSION_MODULE PackZipDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove t his if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);
 
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("PackZip.DLL Initializing!\n");

		g_Inst=hInstance;
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(PackZipDLL, hInstance))
			return 0;

		// Insert this DLL into the resource chain
		// NOTE: If this Extension DLL is being implicitly linked to by
		//  an MFC Regular DLL (such as an ActiveX Control)
		//  instead of an MFC application, then you will want to
		//  remove this line from DllMain and put it in a separate
		//  function exported from this Extension DLL.  The Regular DLL
		//  that uses this Extension DLL should then explicitly call that
		//  function to initialize this Extension DLL.  Otherwise,
		//  the CDynLinkLibrary object will not be attached to the
		//  Regular DLL's resource chain, and serious problems will
		//  result.

		new CDynLinkLibrary(PackZipDLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("PackZip.DLL Terminating!\n");
		// Terminate the library before destructors are called
		AfxTermExtensionModule(PackZipDLL);
	}
	return 1;   // ok
}

#ifdef __cplusplus
    extern "C" {
#endif

/* 
    Plugins structure and private datas
*/

HWND Parent;

HINSTANCE myHinst;
bool IsCreating;
//Desk *dk;
//OGLView *View;

/*
    My datas
*/

// put here your datas
CString szRenderer,szVersion,szVendor,szSupportedExt;

/*
    constants
*/

static char PluginName[]={"PackZip"};
static char PluginInfos[]={"PackZip"};
static char PluginExt[]={"zip;pk3"};

/*
    My stuffs
*/


/*
    Exports symbols
    Add here all the symbol which can be use anywhere else (exports)
*/


unsigned int __declspec(dllexport) Process(unsigned long Msg,unsigned long wParam,unsigned long lParam);

/*
    Process message handler
*/
CZipArchive daZip;
unsigned int Length;
unsigned int nbEnts;
vector<CZipFileHeader> Entries;
vector<int> FileListInds;
PackListFiles KEnts;
char Archive[MAX_PATH];


void SetResource(char *ResName)
{
	if (ResName!=NULL)
    {
        if (strcmp(ResName,Archive)==0) return ;
        daZip.Close();
        strcpy(Archive,ResName);
        
    }
    FILE *tmpf=fopen(ResName,"rb");
	//ftell(
    if (tmpf==NULL)
    {
        daZip.Open(Archive,CZipArchive::create);
    }
    else
    {
        fclose(tmpf);
        daZip.Open(Archive,CZipArchive::open);
    }
    nbEnts=daZip.GetNoEntries();
    Entries.erase(Entries.begin(), Entries.end());
	for (int i = 0; i < nbEnts; i++)
	{
		CZipFileHeader fh;
        daZip.GetFileInfo(fh, (WORD)i);
        Entries.push_back(fh);
    }
	//MessageBox(NULL,Entries[45].GetFileName(),"a",MB_OK);
}
int CountLevel(char *rep)
{
    int value=0;

    for (int i=0;i<strlen(rep);i++)
    {
        if (rep[i]=='\\')
        {
            value++;
        }
    }

    return value;
}

bool CheckBegining(char *src,char *str)
{
	if (strlen(src)<=strlen(str)) return false;

	for (int i=0;i<strlen(str);i++)
	{
		if (src[i]!=str[i]) return false;

	}
	return true;
}
int ListFiles(char *Rep)
{
	int nbrfiles=0;
	int CurLevel=CountLevel(Rep);

	FileListInds.erase(FileListInds.begin(), FileListInds.end());
	
	for (int i = 0; i < nbEnts; i++)
	{
		CString datmpn=Entries[i].GetFileName();
		if (CheckBegining(datmpn.GetBuffer(0),Rep))
		{
			if ( (CurLevel==CountLevel(datmpn.GetBuffer(0))) ||
				( ((CurLevel+1)==CountLevel(datmpn.GetBuffer(0))) &&
				(datmpn[datmpn.GetLength()-1]=='\\') ))

			{
				FileListInds.push_back(i);
				nbrfiles++;
			}
		}
	}

	return nbrfiles;
}

bool IsDirectory(CString Path)
{
	return (Path[Path.GetLength()-1]=='\\');
}

CString RemovePath(CString CompletePath)
{
	CString value="";
	char ext[MAX_PATH];
	char filename[MAX_PATH];

	if (IsDirectory(CompletePath))
	{
		int Level=CountLevel(CompletePath.GetBuffer(0));
		int dalel=0;
		for (int i=0;i<CompletePath.GetLength();i++)
		{
			if (CompletePath[i]=='\\') dalel++;
			if (dalel==(Level-1))
			{
				if (CompletePath[i]=='\\') i++;
				for (int j=(i);j<(CompletePath.GetLength()-1);j++)
				{
					value+=CompletePath[j];
				}

				return value;
			}
		}
	}
	else
	{
		_splitpath(CompletePath.GetBuffer(0),NULL,NULL,filename,ext);

		value=filename;
		value+=ext;
	}
	return value;
}

bool ContainSubdir(char *Path)
{
	int CurLevel=CountLevel(Path);

	for (int i = 0; i < nbEnts; i++)
	{
		CString datmpn=Entries[i].GetFileName();
		if (CheckBegining(datmpn.GetBuffer(0),Path))
		{
			if  (CurLevel<CountLevel(datmpn.GetBuffer(0))) 
			{
				return true;
			}
		}
	}
	return false;
}

CZipArchive *CurrentZip;

int GetFileIndex(char *daName)
{
    CString cfn;
    for (int i = 0; i < nbEnts; i++)
	{
		CZipFileHeader fh;
        CurrentZip->GetFileInfo(fh, (WORD)i);

        cfn=fh.GetFileName();
        if (strcmp(cfn.GetBuffer(1),daName)==0)
        {
            return i;
        }
    }
    return -1;
}

unsigned int __declspec(dllexport) Process(unsigned long Msg,unsigned long wParam,unsigned long lParam)
{
    unsigned int value=0;
	//HINSTANCE tempinst=AfxGetInstanceHandle();
	//AfxSetResourceHandle(g_Inst);

    switch (Msg)
    {
    case KM_GETNAME:
        value=(unsigned int)&PluginName;
        break;
    case KM_GETINFOS:
        value=(unsigned int)&PluginInfos;
        break;
    case KM_GETTYPE:
        value=PLUGIN_RESOURCE;
        break;
    case KM_GETSECONDARYTYPE:
        value=PLUGIN_RESOURCE;
        break;
	case KM_GETEXTENSIONS:
		value=(unsigned int)&PluginExt;
		break;
	case KM_GETREADSUPPORT:
		value=1;
		break;
	case KM_GETWRITESUPPORT:
		value=1;
		break;
	case KM_SETRESOURCE:
		SetResource((char*)wParam);
		break;

	case KM_LISTFILES:
		// dir1\dir2\(*.*)
		value=(UINT)ListFiles((char*)wParam);
		break;
	case KM_LISTFILEENTRY:
		
		KEnts.FileName=Entries[FileListInds[wParam]].GetFileName();
		KEnts.Size=Entries[FileListInds[wParam]].m_uUncomprSize;

		// entry is a directory if its name finish with '\'
		KEnts.IsFile=!IsDirectory(KEnts.FileName);

		KEnts.Date=Entries[FileListInds[wParam]].GetTime();

		if (lParam==1) // remove path, keep file name only
		{
			KEnts.FileName=RemovePath(KEnts.FileName);
		}

		value=(UINT)&KEnts;
		break;
	case KM_CONTAINSUBDIR:
		value=ContainSubdir((char*)wParam);
		break;
	case KM_SETRESOURCEHANDLE:
		CurrentZip=(CZipArchive*)wParam;
		break;
	case KM_RESOURCEOPEN:
		{
			CZipArchive *MyZip;

			MyZip=new CZipArchive;
			CurrentZip=MyZip;

			FILE *tmpf=fopen((char*)wParam,"rb");
			//ftell(
			if (tmpf==NULL)
			{
				MyZip->Open((char*)wParam,CZipArchive::create);
			}
			else
			{
				fclose(tmpf);
				MyZip->Open((char*)wParam,CZipArchive::open);
			}

			int fInd=GetFileIndex((char*)lParam);
			if (fInd!=-1)
			{
				MyZip->CurrentFileInd=fInd;

				MyZip->OpenFile(fInd);
				//daZip.ReadFile(Dest,Entries[fInd].m_uUncomprSize);
				value=(UINT)MyZip;
			}
			else
				value=0;	//bad job!
		}
		break;
	case KM_RESOURCESEEK:
		break;
	case KM_RESOURCEREAD:
		{
			CurrentZip=(CZipArchive*)wParam;
			CZipFileHeader fh;
			CurrentZip->GetFileInfo(fh, (WORD)CurrentZip->CurrentFileInd);

			CurrentZip->ReadFile((BYTE*)lParam,fh.m_uUncomprSize);
		}
		break;
	case KM_RESOURCEWRITE:
		break;
	case KM_RESOURCECLOSE:
		((CZipArchive*)wParam)->CloseFile();
		((CZipArchive*)wParam)->Close();
		break;
	case KM_RESOURCEGETFILESIZE:
		{
			CurrentZip=(CZipArchive*)wParam;
			CZipFileHeader fh;
			CurrentZip->GetFileInfo(fh, (WORD)CurrentZip->CurrentFileInd);
			value=fh.GetSize();
		}
		break;
	case KM_CLOSERESOURCE:
		daZip.Close();
		break;

    }
	//AfxSetResourceHandle(tempinst);
    return value;
}

/*
    Functions used by this plugin
*/




#ifdef __cplusplus
    }
#endif
