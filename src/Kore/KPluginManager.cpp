//------------------------------------------------------------------------------
#include "stdafx.h"

// -- Register -----------------------------------------------------------------
CKPluginManager::CKPluginManager(bool InitPlugins)
{
	if (InitPlugins)
	{
		m_Option=(CKOption*)GetGOption();
		RegisterFilePlugs("plugins\\");
		RegisterPlugs("plugins\\");
		hInstRenderer=NULL;
		InitEntityInterface(m_Option->EntityDLLLocation());
	}
}


CKPluginManager::~CKPluginManager()
{
	if (hInstRenderer!=NULL)
		FreeLibrary(hInstRenderer);
	
}
bool CKPluginManager::IsRendererValid(char *RendererName)
{
	if (RendererName==NULL)
		return false;

	HINSTANCE TemphInstRenderer=LoadLibrary(RendererName);
    if (TemphInstRenderer==NULL) return false;

    CreateRenderInterface=(CKRenderer * (*)(CKScene*))GetProcAddress(TemphInstRenderer,"CreateRenderInterface");

	FreeLibrary(TemphInstRenderer);

	if (CreateRenderInterface==NULL) return false;

	return true;

}

bool CKPluginManager::RegisterPlugs(char *PlugDir)
{
	CString tempo;
	struct _finddata_t fileinfo;
	int done;
	long handle;

    // -- Creation -------------------------------------------------------------


	memset((void*)&fileinfo,0,sizeof(fileinfo));

	tempo=PlugDir;
	tempo+="*.dll";
	
    handle = _findfirst(tempo,&fileinfo);
	if (handle!=-1)
	{
		done=0;
		while (!done)
		{
			tempo=PlugDir;
			tempo+=fileinfo.name;

			HINSTANCE LoadInstance=LoadLibrary(tempo);
			if (LoadInstance!=NULL) 
			{
				
				// Operation Plugin

				CreateSceneInterface=(CKScenePlugin * (*)())GetProcAddress(LoadInstance,"CreateSceneInterface");
				if (CreateSceneInterface!=NULL)
				{
					CKScenePlugin *tmpScenePlugins=CreateSceneInterface();
					tmpScenePlugins->m_hInst=LoadInstance;
					if (tmpScenePlugins->ScenePluginType()==PLUGIN_PRIMITIVE)
						PrimitivePlugins.push_back(tmpScenePlugins);
					else
						OperationPlugins.push_back(tmpScenePlugins);
				}
				else
				{
					// rendering interface
					CreateRenderInterface=(CKRenderer * (*)(CKScene*))GetProcAddress(LoadInstance,"CreateRenderInterface");
					if (CreateRenderInterface!=NULL)
					{
						CKRenderer *tmpRendererPlugins=CreateRenderInterface(NULL);
						tmpRendererPlugins->m_hInst=LoadInstance;
						RendererPlugins.push_back(tmpRendererPlugins);
					}
				}
			
			}

			done = _findnext(handle,&fileinfo);
		}
	}
    return true;
}

bool CKPluginManager::RegisterFilePlugs(char *PlugDir)
{
	CString tempo;
	struct _finddata_t fileinfo;
	int done;
	long handle;

    // -- Creation -------------------------------------------------------------

	memset((void*)&fileinfo,0,sizeof(fileinfo));

	tempo=PlugDir;
	tempo+="*.dll";
	
    handle = _findfirst(tempo,&fileinfo);
	if (handle!=-1)
	{
		done=0;
		while (!done)
		{
			tempo=PlugDir;
			tempo+=fileinfo.name;

			HINSTANCE LoadInstance=LoadLibrary(tempo);
			if (LoadInstance!=NULL) 
			{
				// File Interface

				CreateFileInterface=(CKFilePlugin * (*)())GetProcAddress(LoadInstance,"CreateFileInterface");
				if (CreateFileInterface!=NULL)
				{
					CKFilePlugin *tmpFilePlugins=CreateFileInterface();
					tmpFilePlugins->m_hInst=LoadInstance;
					if (tmpFilePlugins->SupportWriting()) WriteGen.push_back(tmpFilePlugins);
					FilePlugins.push_back(tmpFilePlugins);
				}
			}

			done = _findnext(handle,&fileinfo);
		}
	}
    return true;
}
CKFilePlugin * CKPluginManager::GetFilePluginByName(CString Name)
{
	int i;

	for (i=0;i<FilePlugins.size(); i++)
		if (FilePlugins[i]->GetName()==Name) return FilePlugins[i];

	return NULL;
}

CKScenePlugin * CKPluginManager::GetScenePluginByName(CString Name)
{
	int i;

	for (i=0;i<OperationPlugins.size(); i++)
		if (OperationPlugins[i]->GetName()==Name) return OperationPlugins[i];

	for (i=0;i<PrimitivePlugins.size(); i++)
		if (PrimitivePlugins[i]->GetName()==Name) return PrimitivePlugins[i];

    return NULL;
}

inline CKPlugin * CKPluginManager::GetSupportedResManager(CString Path,CString &Dest,CString &ZipRep)
{
	/*
	int i,j;
	CString Seeker;

	for (i=0;i<ResourcePlugs.size();i++)
	{
		for (j=0;j<ResourcePlugs[i]->ResExtensions.size();j++)
		{
			Seeker="."+ResourcePlugs[i]->ResExtensions[j];

			int star=Path.Find(Seeker);
			if (star!=-1)
			{
				// dest = path+res name
				star+=Seeker.GetLength();
				Dest=Path.Mid(0,star);
				if ((star+1)>=Path.GetLength())
					ZipRep="";
				else
					ZipRep=Path.Mid(star+1);
				return ResourcePlugs[i];
			}
		}
	}
	*/
	return NULL;
}

//	CKRenderer *(*CreateInterface)(HWND window);
void CKPluginManager::InitRendererInterface(CString PluginName)
{
	
    hInstRenderer=LoadLibrary(PluginName);
    if (hInstRenderer==NULL) return ;

    CreateRenderInterface=(CKRenderer * (*)(CKScene*))GetProcAddress(hInstRenderer,"CreateRenderInterface");
}

PrimBmp* CKPluginManager::EntityBitmaps()
{

	return NULL;
}

void CKPluginManager::InitEntityInterface(CString PluginName)
{
	hInstEntity=LoadLibrary(PluginName);
    if (hInstEntity==NULL) return ;

    CreateEntityInterface=(CKEntity * (*)(CString))GetProcAddress(hInstEntity,"CreateEntityInterface");
	FillEntityPrimInterface=(PrimBmp* (*)())GetProcAddress(hInstEntity,"FillEntityPrimitives");
}