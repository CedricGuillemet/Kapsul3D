// io3ds.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
//---------------------------------------------------------------------------

#include "Desk.h"
#include "Kapsul3D.h"
#include "Q3BSP.h"

Desk *dadk;

#ifdef __cplusplus
    extern "C" {
#endif


void __declspec(dllexport)   Type(int *TypeVal);
void __declspec(dllexport)   SecondaryType(int *TypeVal);
void __declspec(dllexport)   Infos(char *Infos);
void __declspec(dllexport)   GetParams(char *FileDesc,char *Filter);
int  __declspec(dllexport)   ReadSupport(void);
int  __declspec(dllexport)   WriteSupport(void);
int  __declspec(dllexport)   Read(Desk *dk,char PathName[260]);
int  __declspec(dllexport)   Write(Desk *dk,char PathName[260]);
void __declspec(dllexport)   Name(char *daName);
void __declspec(dllexport)   Close(void);


void __declspec(dllexport)   Close(void)
{
}




//------------------------------------------------------------------------------

void __declspec(dllexport)   Infos(char *Infos)
{
    strcpy(Infos,TEXT("Quake3 bsp map Importer.\0"));
}
void __declspec(dllexport)   GetParams(char *FileDesc,char *Filter)
{
    strcpy(FileDesc,TEXT("Quake3 bsp.\0"));
    strcpy(Filter,TEXT("*.BSP\0"));
}
int  __declspec(dllexport)   ReadSupport(void)
{
    return 1;
}

int  __declspec(dllexport)   WriteSupport(void)
{
    return 0;
}

int  __declspec(dllexport)   Read(Desk *dk,char PathName[260])
{
    dadk=dk;
    Quake3BSP q(PathName, TEXT("a") );

    VertexMesh *mesh = q.GetVertexMesh();
    //mesh->SaveVRML("a",true);
    return 1;

}
int  __declspec(dllexport)   Write(Desk *dk,char PathName[260])
{
    return 0;
}



// -- Typage du plug-in --------------------------------------------------------

void __declspec(dllexport)    Type(int *TypeVal)
{
    (*TypeVal)=PLUGIN_FILE;
}

void __declspec(dllexport)    SecondaryType(int *TypeVal)
{
    (*TypeVal)=0;
}

void __declspec(dllexport)    Name(char *daName)
{
    strcpy(daName,"Quake3 bsp files.\0");
}

#ifdef __cplusplus
    }
#endif



//---------------------------------------------------------------------------

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

