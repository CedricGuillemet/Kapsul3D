// TerrainEd.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
//#include "TerrainEd.h"
#include "TerrainEdDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


HINSTANCE g_Inst;

/*
    constants
*/

static char PluginName[]={"Terrain Editor"};
static char PluginInfos[]={"Terrain Editor"};

static AFX_EXTENSION_MODULE TerrainEDDLL = { NULL, NULL };


extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("TerrainED.DLL Initializing!\n");

		g_Inst=hInstance;
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(TerrainEDDLL, hInstance))
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

		new CDynLinkLibrary(TerrainEDDLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("TerrainED.DLL Terminating!\n");
		// Terminate the library before destructors are called
		AfxTermExtensionModule(TerrainEDDLL);
	}
	return 1;   // ok
}

extern CTerra m_Terra;
extern CTerraTex m_Texture;
bool TerrainModified=true;
#ifdef __cplusplus
    extern "C" {
#endif


unsigned int __declspec(dllexport) Process(unsigned long Msg,unsigned long wParam,unsigned long lParam);
void LMouseDown(int X,int Y,Vertex *Pos);
void LMouseUp(int X,int Y,Vertex *Pos);
void MouseMove(int X,int Y,Vertex *Pos);
void RMouseDown(int X,int Y,Vertex *Pos);
void RMouseUp(int X,int Y,Vertex *Pos);

/*
    Process message handler
*/
CBitmap m_Dib;
CWnd *tempo;
HWND Parent;
Desk *dk;
OGLView *View;
//CRollupCtrl __declspec(dllexport) *m_wndRollupCtrl;

CTerrainEdDlg *m_TerEd;
#pragma pack(1)
typedef struct
{
	float x,y,z;
	float u,v;
} TerrainVert;
#pragma pack(4)
TerrainVert avt[16384];
unsigned int strips[(128)*(128)*6];

CTexture deftex(NULL,NULL);
Object *TerrainObj=NULL;

void BuildObject(void)
{
	int x,y;
	if (TerrainObj!=NULL)
		dk->DelObject(TerrainObj);
//		delete TerrainObj;

	dk->AddObject();
	TerrainObj=dk->NextObject;
	TerrainObj->Property1|=PROP_FORCETRI;

	//TerrainObj=new Object(dk,NULL,NULL);

	TerrainObj->AllocatePoly(127*127*2,128*128);
	TerrainObj->AllocateUV(0,128*128);
	//TerrainObj->AllocateUV(1,128*128);

	LPBITMAPINFOHEADER BiDest=(LPBITMAPINFOHEADER)GlobalLock(m_Terra.m_hDib);			
    BYTE *lpBits = ((BYTE*)BiDest)+sizeof(BITMAPINFOHEADER);

	int av=1024/128;
    for (y=0;y<128;y++)
	{
		for (x=0;x<128;x++)
		{
			TerrainObj->pv[y*128+x].vx=x*16;
			TerrainObj->pv[y*128+x].vy=y*16;
			TerrainObj->pv[y*128+x].vz=lpBits[((y*av)*1024)*3+(x*av)*3+2];
			
			TerrainObj->puv[0][y*128+x].u=(float)(x)/128.0f;
			TerrainObj->puv[0][y*128+x].v=(float)(y)/128.0f;
			
		}
	}
    GlobalUnlock(BiDest);

	int plav=0;

    for (y=0;y<127;y++)
	{
		for (x=0;x<127;x++)
		{
			
			TerrainObj->pl[plav].Allocate(1,3);
			TerrainObj->pl[plav].nbvert[2]=x+(y*128);
			TerrainObj->pl[plav].nbvert[1]=x+((y+1)*128);
			TerrainObj->pl[plav].nbvert[0]=x+1+(y*128);
			TerrainObj->pl[plav].Tex[0][2]=x+(y*128);
			TerrainObj->pl[plav].Tex[0][1]=x+((y+1)*128);
			TerrainObj->pl[plav].Tex[0][0]=x+1+(y*128);

			plav++;
			
			TerrainObj->pl[plav].Allocate(1,3);
			TerrainObj->pl[plav].nbvert[0]=x+((y+1)*128);
			TerrainObj->pl[plav].nbvert[1]=x+1+(y*128);
			TerrainObj->pl[plav].nbvert[2]=x+1+((y+1)*128);
			TerrainObj->pl[plav].Tex[0][0]=x+((y+1)*128);
			TerrainObj->pl[plav].Tex[0][1]=x+1+(y*128);
			TerrainObj->pl[plav].Tex[0][2]=x+1+((y+1)*128);

			plav++;
			
		}
	}



}
void PrecalcTerrain(void)
{
	int x,y;

	LPBITMAPINFOHEADER BiDest=(LPBITMAPINFOHEADER)GlobalLock(m_Terra.m_hDib);			
    BYTE *lpBits = ((BYTE*)BiDest)+sizeof(BITMAPINFOHEADER);

	int av=1024/128;
    for (y=0;y<128;y++)
	{
		for (x=0;x<128;x++)
		{
			avt[y*128+x].x=x*16;
			avt[y*128+x].y=y*16;
			avt[y*128+x].z=lpBits[((y*av)*1024)*3+(x*av)*3+2];
			
			avt[y*128+x].u=(float)(x)/128.0f;
			avt[y*128+x].v=(float)(y)/128.0f;
			
		}
	}
    GlobalUnlock(BiDest);
/*
    for (y=0;y<127;y++)
	{
		for (x=0;x<128;x++)
		{
			strips[(y*256)+(x*2)]=x+(y*128);
			strips[(y*256)+(x*2)+1]=x+((y+1)*128);
		}
	}
	*/
	int strav=0;

    for (y=0;y<127;y++)
	{
		for (x=0;x<127;x++)
		{
			strips[strav]=(x)+(y*128);
			strips[strav+1]=(x)+((y+1)*128);
			strips[strav+2]=(x+1)+(y*128);

			strav+=3;

			strips[strav]=(x)+((y+1)*128);
			strips[strav+1]=(x+1)+((y)*128);
			strips[strav+2]=(x+1)+((y+1)*128);

			strav+=3;
		}
	}

	TerrainModified=false;
}

void DrawTerrain(void)
{
	int x,y;

	glEnable(GL_TEXTURE_2D);
	deftex.Bind();
/*
	for (y=0;y<127;y++)
	//y=0;
	{
		glBegin(GL_TRIANGLE_STRIP);
		for (x=0;x<256;x++)
		{
			int nb=strips[y*256+x];
			glTexCoord2f(avt[nb].u,avt[nb].v);
			glVertex3f(avt[nb].x,avt[nb].y,avt[nb].z);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
*/	
	//View->DrawObject(TerrainObj,1,0);

	glEnable(GL_VERTEX_ARRAY);
	glEnable(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3,GL_FLOAT,20,avt);
	glTexCoordPointer(2,GL_FLOAT,20,&avt[0].u);
/*
	for (y=0;y<127;y++)
	{
		glDrawElements(GL_TRIANGLE_STRIP,256,GL_UNSIGNED_INT,&strips[y*256]);
	}
*/

	glDrawElements(GL_TRIANGLES,128*128*2*3,GL_UNSIGNED_INT,strips);


	glDisable(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_VERTEX_ARRAY);
	glDisable(GL_TEXTURE_2D);
	/*
  GLenum mode,
  GLsizei count,
  GLenum type,
  const GLvoid *indices
);
*/
}
unsigned int __declspec(dllexport) Process(unsigned long Msg,unsigned long wParam,unsigned long lParam)
{
    unsigned int value=0;
    HINSTANCE tempinst=AfxGetInstanceHandle();
	AfxSetResourceHandle(g_Inst);

    switch (Msg)
    {
    case KM_OPEN:

        Parent=(HWND)wParam;
        tempo=CWnd::FromHandle((HWND)wParam);

        m_TerEd=new CTerrainEdDlg;
        m_TerEd->Create((unsigned int)IDD_TERRAINED_DIALOG,tempo);
        
        
        value=(unsigned int)m_TerEd->m_hWnd;

        break;
    case KM_CLOSE:
        m_TerEd->DestroyWindow();
		delete m_TerEd;
//        DestroyWindow(ShapeDiagHWND);
		SetPointer(0);
        break;
    case KM_GETNAME:
        value=(unsigned int)&PluginName;
        break;
    case KM_GETINFOS:
        value=(unsigned int)&PluginInfos;
        break;
    case KM_GETTYPE:
        value=PLUGIN_CREATION;
        break;
    case KM_GETSECONDARYTYPE:
        value=PLUGIN_SHAPE;
        break;
    case KM_ISPROPERTY:
        value=0;
        break;
    case KM_ISCREATING:
        value=false;//(CreateSeg||CreateSeg2);
        break;
    case KM_SETDESK:
        dk=(Desk*)wParam;
        break;
    case KM_GETBITMAP:
        m_Dib.LoadBitmap(IDB_BITMAP);
        value=(unsigned int)&m_Dib;
        break;
    case KM_DRAW:
		if (TerrainModified)
			PrecalcTerrain();
		DrawTerrain();
        value=PLUGIN_ALL;
        break;
    case KM_LMOUSEDOWN:
        LMouseDown(LOWORD(wParam),HIWORD(wParam),(Vertex *)(lParam));
        break;
    case KM_RMOUSEDOWN:
        RMouseDown(LOWORD(wParam),HIWORD(wParam),(Vertex *)(lParam));
        break;
    case KM_LMOUSEUP:
        LMouseUp(LOWORD(wParam),HIWORD(wParam),(Vertex *)(lParam));
        break;
    case KM_RMOUSEUP:
        RMouseUp(LOWORD(wParam),HIWORD(wParam),(Vertex *)(lParam));
        break;
    case KM_MOUSEMOVE:
        MouseMove(LOWORD(wParam),HIWORD(wParam),(Vertex *)(lParam));
        break;
    case KM_SETVIEW:
        View=(OGLView*)wParam;
        break;
    case KM_MOVEWINDOW:
//        m_wndRollupCtrl->MoveWindow(0,0,164,(int)lParam,TRUE);
        value=(int)lParam;
        break;
    case KM_UNSETPLUGIN:
//        m_Edit.UnSetPlugin();
        break;

    }

	AfxSetResourceHandle(tempinst);

    return value;
}


void LMouseDown(int X,int Y,Vertex *Pos)
{
}
void LMouseUp(int X,int Y,Vertex *Pos)
{
}
void MouseMove(int X,int Y,Vertex *Pos)
{
}
void RMouseDown(int X,int Y,Vertex *Pos)
{
}
void RMouseUp(int X,int Y,Vertex *Pos)
{
}

#ifdef __cplusplus
    }
#endif