/*

	IOWC_Map.CPP
	Conversion Notes:
		- Every brush bind to WorldSpawn entity shouldnt be bind to an entity in Kapsul
		- Every brush bind to any entity except WorldSpawn should be bind to an entity in kapsul
*/

#include "stdafx.h"
#include <Kapsul3D.h>
#include <headers.h>
#include <stdio.h>
#include <io.h>
#include "BrushConverter.h"

#ifdef __cplusplus
    extern "C" {
#endif


/*
    constants
*/

static char PluginName[]={"WorldCraft map I/O"};
static char PluginInfos[]={"WorldCraft map I/O"};
static char PluginFileDesc[]={"WorldCraft map"};
static char PluginFilter[]={"*.map"};

// Parser
static char toSkip[] = " \t\n\"";
static bool bInitialized = false;   
static char *pToken = NULL;

static CBrushConverter * pConverter = new CBrushConverter();

/*
    Exports symbols
*/

unsigned int __declspec(dllexport) Process(unsigned long Msg,unsigned long wParam,unsigned long lParam);
int  __declspec(dllexport)   Read(Desk *dk,char PathName[260]);
int  __declspec(dllexport)   Write(Desk *dk,char PathName[260]);

/*
    My Functions
*/
Desk *dadk;

/*
 Parser
*/
char *GetToken(char *m_pData)
{
 if(!m_pData)
 {
	 AfxMessageBox("GetToken() failed.");
	 return NULL;
 }

 if(bInitialized == FALSE)
 {
	pToken = strtok(m_pData,toSkip);
	bInitialized = TRUE;
 }
 else
	pToken = strtok(NULL,toSkip);

 return pToken;
}

bool LoadWcBrush(char *m_pData)
{
 /*
	That's how a brush is stored in .map file:

	{
	 ( x y z ) ( x y z ) ( x y z ) TEXTURE*TEX [ 0 0 0 0 ] [ 0 0 0 0 ] 0 0 0
	 [...]
	}

	where each line represents a brush face. ( x y z ) is a point that makes
	the face, we have to write 3 points and compute the fourth on loading. After
	it comes texture name, position x,y and rotation,scaling. so:
 */

 CBrushConverter::CBrushRaw *pBrush = NULL;
 char  *pToken = NULL;
 SFACE *pFaces = NULL;
 int   iNumFaces = 0;

 do
 {
  pToken = GetToken(m_pData);
  if(!pToken)
	  break;

  if(strcmp(pToken,"}") == 0)
		break;

  // read 3 points for each plane on which face lays on
  if(strcmp(pToken,"(") == 0)
  {
   // we found a new face
   iNumFaces += 1;
   if(iNumFaces == 1)
		pFaces = new SFACE;
   else
   {
	SFACE *pTemp = pFaces;
	pFaces = new SFACE[iNumFaces];
	memcpy(pFaces,pTemp,sizeof(SFACE)*(iNumFaces-1));
	delete [] pTemp;
   }
	 
   // we reset face windings
   pFaces[iNumFaces - 1].sFaceWinding = NULL;

   pFaces[iNumFaces - 1].vPlanePts[0].x = (float)atof(GetToken(m_pData));
   pFaces[iNumFaces - 1].vPlanePts[0].y = (float)atof(GetToken(m_pData));
   pFaces[iNumFaces - 1].vPlanePts[0].z = (float)atof(GetToken(m_pData));

   pToken = GetToken(m_pData);
   if(strcmp(pToken,")") != 0)
   {
	MessageBox(NULL,"LoadWcBrush found a missing ')' in map file! Brush not loaded.","iowc_map.dll",MB_OK);
	delete [] pFaces;
	return false;
   }
  }else
  {
   delete [] pFaces;
   return false;
  }

  pToken = GetToken(m_pData);
  if(strcmp(pToken,"(") == 0)
  {
   pFaces[iNumFaces - 1].vPlanePts[1].x = (float)atof(GetToken(m_pData));
   pFaces[iNumFaces - 1].vPlanePts[1].y = (float)atof(GetToken(m_pData));
   pFaces[iNumFaces - 1].vPlanePts[1].z = (float)atof(GetToken(m_pData));

   pToken = GetToken(m_pData);
   if(strcmp(pToken,")") != 0)
   {
	MessageBox(NULL,"LoadWcBrush found a missing ')' in map file! Brush not loaded.","iowc_map.dll",MB_OK);
	delete [] pFaces;
	return false;
   }
  }else
  {
   delete [] pFaces;
   return false;
  }

  pToken = GetToken(m_pData);
  if(strcmp(pToken,"(") == 0)
  {
   pFaces[iNumFaces - 1].vPlanePts[2].x = (float)atof(GetToken(m_pData));
   pFaces[iNumFaces - 1].vPlanePts[2].y = (float)atof(GetToken(m_pData));
   pFaces[iNumFaces - 1].vPlanePts[2].z = (float)atof(GetToken(m_pData));

   pToken = GetToken(m_pData);
   if(strcmp(pToken,")") != 0)
   {
	MessageBox(NULL,"LoadWcBrush found a missing ')' in map file! Brush not loaded.","iowc_map.dll",MB_OK);
	delete [] pFaces;
	return false;
   }
  }else
  {
   delete [] pFaces;
   return false;
  }

  // We read texture name
  pFaces[iNumFaces - 1].sFaceTexture.Name = GetToken(m_pData);

  pToken = GetToken(m_pData);
  if(strcmp(pToken,"[") == 0)
  {
   pToken = GetToken(m_pData);
   pToken = GetToken(m_pData);
   pToken = GetToken(m_pData);
   pToken = GetToken(m_pData);

	 	
   pToken = GetToken(m_pData);
   if(strcmp(pToken,"]") != 0)
   {
	MessageBox(NULL,"LoadWcBrush found a missing ']' in map file! Brush not loaded.","iowc_map.dll",MB_OK);
	delete [] pFaces;
	return false;
   }
  }else
  {
   delete [] pFaces;
   return false;
  }

  pToken = GetToken(m_pData);
  if(strcmp(pToken,"[") == 0)
  {
   pToken = GetToken(m_pData);
   pToken = GetToken(m_pData);
   pToken = GetToken(m_pData);
   pToken = GetToken(m_pData);

	 	
   pToken = GetToken(m_pData);
   if(strcmp(pToken,"]") != 0)
   {
    MessageBox(NULL,"LoadWcBrush found a missing ']' in map file! Brush not loaded.","iowc_map.dll",MB_OK);
    delete [] pFaces;
    return false;
   }
  }else
  {
   delete [] pFaces;
   return false;
  }

  // We init texture rotation, hscale and vscale
  pFaces[iNumFaces - 1].sFaceTexture.Rotate	  = (float)atof(GetToken(m_pData));
  pFaces[iNumFaces - 1].sFaceTexture.Scale[0] = (float)atof(GetToken(m_pData));
  pFaces[iNumFaces - 1].sFaceTexture.Scale[1] = (float)atof(GetToken(m_pData));
 }
 while(1);

 pBrush = new CBrushConverter::CBrushRaw();
 pBrush->s_Faces  = pFaces;
 pBrush->m_nFaces = iNumFaces;

 pConverter->m_nLoadedBrushes++;
 pConverter->Brush_BuildWinding(pBrush);

 return pConverter->Desk_Import(dadk,pBrush);
}

bool LoadWcEntity(char *m_pData)
{
  /*
	That's how an entity is stored in the .map file:
	{
	 "classname" "entity_class_name"
	 [...] Options
	 {
	 (brush face)
	 }
	}

	so ,for saving:
	-> we first open brackets 
	-> we write the classname 
	-> we write options
	-> we write brushes (if it's a solid entity)
	-> we close entity bracket
 */

 char	 * pToken  = NULL;
 CEntity * pEntity = NULL;
 CString   szEntityName;

 pToken = GetToken(m_pData);
 if(!pToken)
	 return false;

 if(strcmp(pToken,"{") != 0)
	 return false;


 do
 {
  pToken = GetToken(m_pData);
  if(!pToken)
  {
   MessageBox(NULL,"LoadWcEntity couldn't find next token in entity definition. Map file is probably damaged","iowc_map.dll",MB_OK);
   return false;
  }

  if(strcmp(pToken,"}") == 0)
		break;

  if(strcmp(pToken,"{") == 0)
  {
   if(LoadWcBrush(m_pData))
   {
	// We found a valid brush
   }else
	 break;
  }else
  {
   if(strstr(pToken,"classname"))
   {
    // We set entity class name and create an instance of entity here.
	// as it is called once on entity load before brushes so we can 
	// differentiate worldspawn brushes from others

    szEntityName = GetToken(m_pData);
    //pEntity = new CEntity(dadk,NULL,NULL,szEntityName);

	pConverter->m_nProcessedEntities++;
   }else if(strstr(pToken,"mapversion"))
   {
    GetToken(m_pData);
	continue;
   }else
   {
	// Read properties
    GetToken(m_pData); //propdata
   }
  }
 }
 while(1);


 return true;
}

void LoadWcMap(char *pBuf)
{
 while(1)
 {
  if(!LoadWcEntity(pBuf))
	  break;
 }

 pConverter->PrintStatistics();
}

/*
 Main load function
*/ 
bool LoadFile(char *FileName)
{
 FILE *fFile = fopen(FileName,"rt");
 if(fFile)
 {
  // If we loaded multiple maps, then we reset our internal shit
  pConverter->m_nLoadedBrushes = pConverter->m_nProcessedBrushes = pConverter->m_nProcessedEntities = 0;
  bInitialized = FALSE;

  int iStart = 0,iEnd = 0;
  iStart  = ftell (fFile);
  fseek (fFile, 0, SEEK_END);
  iEnd = ftell (fFile);
  fseek (fFile, iStart, SEEK_SET);

  char * pBuff = new char[iEnd+1];
  ((char*)pBuff)[iEnd] = 0;
  if(!pBuff)
  {
	return false;
  }

  // We read our text buffer ready to be parsed
  fread(pBuff,1,iEnd,fFile);
  fclose(fFile);

  // We parse our text buffer and read our shit in
  LoadWcMap(pBuff);

  // We release text buffer memory
  delete [] pBuff;
  pBuff = NULL;

  return true;
 }
 
 return false;
}

/*
    Process message handler
*/

unsigned int __declspec(dllexport) Process(unsigned long Msg,unsigned long wParam,unsigned long lParam)
{
    unsigned int value=0;

    switch (Msg)
    {
    case KM_OPEN:
        break;
    case KM_CLOSE:
        break;
    case KM_GETNAME:
        value=(unsigned int)&PluginName;
        break;
    case KM_GETINFOS:
        value=(unsigned int)&PluginInfos;
        break;
    case KM_GETTYPE:
        value=PLUGIN_FILE;
        break;
    case KM_GETSECONDARYTYPE:
        value=0;
        break;
    case KM_GETFILTER:
        value=(unsigned int)&PluginFilter;
        break;
    case KM_GETFILEDESC:
        value=(unsigned int)&PluginFileDesc;
        break;
    case KM_GETREADSUPPORT:
        value=1;
        break;
    case KM_GETWRITESUPPORT:
        value=1;
        break;
    case KM_WRITEFILE:
        value=Write((Desk*)wParam,(char*)lParam);
        break;
    case KM_READFILE:
        value=Read((Desk*)wParam,(char*)lParam);
        break;

    }

    return value;
}

/*
    Process Read and Write
*/

int  __declspec(dllexport)   Read(Desk *dk,char PathName[260])
{
    // Process here you read operation

    dadk = dk;
    return LoadFile(PathName);
}

int  __declspec(dllexport)   Write(Desk *dk,char PathName[260])
{
    // Process here you write operation
	dadk = dk;

    return true; //Did everything went right ?
}

#ifdef __cplusplus
    }
#endif

/*
    DLL entrypoint
*/

class CPluginApp : public CWinApp
{
public:
	CPluginApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKoreApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CKoreApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CPluginApp, CWinApp)
	//{{AFX_MSG_MAP(CPluginApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKoreApp construction

CPluginApp theApp;

CPluginApp::CPluginApp()
{
}

BOOL CPluginApp::InitInstance() 
{
	return CWinApp::InitInstance();
}



