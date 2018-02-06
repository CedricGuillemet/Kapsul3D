// Preview.cpp : implementation file
//

#include "stdafx.h"
#include "TerrainEd.h"
#include "Preview.h"
#include <vector>
//using std::vector;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include <headers.h>
#include "SceneGraph.h"
#include "TerraTex.h"
#include "Terra.h"
#include "../Prim3D/tree/tree/tree.h"
extern CSkyBox daSkyb;
extern CImage DetailTex,WaterTex;
int WaterTexID=-1;
PFNGLACTIVETEXTUREARBPROC glActiveTextureARB=NULL;
PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2fARB=NULL;
PFNGLCLIENTACTIVETEXTUREARBPROC glClientActiveTextureARB=NULL;
/////////////////////////////////////////////////////////////////////////////
// CPreview dialog

extern "C" 
{
extern "C" int nAvgFrames ;
extern "C" CTexture *tertex;
extern "C" CTexture *pTexSkyBox[5];
//extern "C" CSkyBox csb;
extern "C" Camera *VCam;
}


            


CPreview::CPreview(CWnd* pParent /*=NULL*/)
	: CDialog(CPreview::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPreview)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPreview::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPreview)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPreview, CDialog)
	//{{AFX_MSG_MAP(CPreview)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPreview message handlers

extern CTerraTex m_Texture;
extern CTerra m_Terra;
extern unsigned char *gHeightMaster;
Object *daTrees[1024];
Object *daLeaf[1024];
Vertex Pos[1024];
Desk *dk;
CTexture *m_ecorce;
CTexture *m_feuille;

BOOL CPreview::OnInitDialog() 
{
	CDialog::OnInitDialog();
	RECT rc;

    GetClientRect(&rc);
    m_View.Create(NULL,NULL,WS_VISIBLE|WS_CHILD,rc,this,54151);

    VCam = new Camera(NULL,NULL);
    VCam->SetSource(Vertex(500,512,256));
    VCam->SetDest(Vertex(0,0,0));
    //m_Terra.
    


    gAnimating = 1;
	///loadTerrain(MAP_SIZE, &gHeightMap);
/*
            void loadTerrain(int size, unsigned char **dest)
            {
*/

    LPBITMAPINFOHEADER BiTerrain=(LPBITMAPINFOHEADER)GlobalLock(m_Terra.m_hDib);

    BYTE *lpBitsTer = ((BYTE*)BiTerrain)+sizeof(BITMAPINFOHEADER);


                int size=1024;
                unsigned char *dest,*dest2;
    
	            FILE *fp;
	            //char fileName[30];
/*
                BYTE *pdest=&gHeightMap;
                BYTE *pdest2;

                pdest2=pdest;
*/
	            // Optimization:  Add an extra row above and below the height map.
	            //   - The extra top row contains a copy of the last row in the height map.
	            //   - The extra bottom row contains a copy of the first row in the height map.
	            // This simplifies the wrapping of height values to a trivial case. 
	            gHeightMaster = (unsigned char *)malloc( size * size * sizeof(unsigned char) + size * 2 );
	            
	            // Give the rest of the application a pointer to the actual start of the height map.
	            dest = gHeightMaster + size;
                dest2=dest;

                //gHeightMaster + =size;
                for (int x=0;x<(1024*1024);x++)
                {
                    (*dest++)=(*lpBitsTer);
                    lpBitsTer+=3;

                }
	            //fread(gHeightMaster + size, 1, (size * size), fp);
	            //fclose(fp);

	            // Copy the last row of the height map into the extra first row.
	            memcpy( gHeightMaster, gHeightMaster + size * size, size );




    GlobalUnlock(m_Terra.m_hDib);

    dk=new Desk(NULL,NULL);


	
	roamInit(gHeightMaster);

	gCameraMode++;
	if ( gCameraMode > FLY_MODE )
		gCameraMode = FOLLOW_MODE;

	// Turn animation back on...
	if (gCameraMode == FOLLOW_MODE)
		gAnimating = 1;


            glEnable(GL_TEXTURE_2D);

            tertex=new (CTexture)(NULL,NULL);
            strcpy(tertex->FileName,"terrain-texture3.bmp");
    
            
            //tertex->Type=TEXTURE_FILE;
            tertex->TexID=m_Texture.Upload(0,false);

            WaterTexID=WaterTex.Upload(0,false);
            //tertex->Load();

/*
            for (int i=0;i<5;i++)
            {
                char temp[50];
                wsprintf(temp,"skybox%d.bmp",i);
                pTexSkyBox[i]=dk->AddTex(temp);
                pTexSkyBox[i]->Type=TEXTURE_FILE;
                pTexSkyBox[i]->Load();
            }
*/            

/*
            CImage daImg;
            daImg.LoadFromRessource(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_ECORCE),IMG_FORMAT_JPEG,"IMAGES");
            m_ecorce=new (CTexture)(NULL,NULL);
            strcpy(m_ecorce->FileName,"water.bmp");
            m_ecorce->TexID=daImg.Upload(0);
            

            daImg.TexId=-1;
            daImg.LoadFromRessource(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_FEUILLES),IMG_FORMAT_BMPWIN,"IMAGES");
            m_feuille=new (CTexture)(NULL,NULL);
            strcpy(m_feuille->FileName,"water.bmp");
            m_feuille->TexID=daImg.UploadAlpha(0);
            

*/
/*
            WaterTex=new (CTexture)(NULL,NULL);
            WaterTex->Type=TEXTURE_FILE;
            strcpy(WaterTex->FileName,"water.bmp");
            WaterTex->Load();
*/


            daSkyb.Load((unsigned char*)daSkyb.SkyBoxName);
            DetailTex.Upload(0,false);
            SetParams(	Vertex(0,0,0),			// origin
						Vertex(1000,1000,256),	// dimensions
						0.4f,					// patch density (0..1)
						0.3f);					// water height


    if (!glActiveTextureARB || !glMultiTexCoord2fARB || !glClientActiveTextureARB)
    {
	    glActiveTextureARB = (PFNGLCLIENTACTIVETEXTUREARBPROC) 
		    wglGetProcAddress("glActiveTextureARB");
        glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC) 
		    wglGetProcAddress("glMultiTexCoord2fARB");
        glClientActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC) 
		    wglGetProcAddress("glClientActiveTextureARB");

	    // Verify pointers
	    if (!glActiveTextureARB || !glMultiTexCoord2fARB || !glClientActiveTextureARB)
		    return FALSE;
    }
	    // Activate texturing, leave first TMU activated
        glEnable(GL_TEXTURE_2D);
	    glActiveTextureARB(GL_TEXTURE1_ARB); 
	    glEnable(GL_TEXTURE_2D);
	    glActiveTextureARB(GL_TEXTURE0_ARB);
	    glEnable(GL_TEXTURE_2D);

//            csb.Load((unsigned char*)"Skybox/planet/planet.skk");

/*
    Tree mytree;
    Vertex tmpv(0,0,0);//
    
    for (int i=0;i<128;i++)
    {
        daTrees[i]=new Object(dk,NULL,NULL);
        daLeaf[i]=new Object(dk,NULL,NULL);

        float tomp;
        tomp=(rand()&15);
        mytree.setThreshhold(0.15f+(tomp/10.0f));

        tomp=(rand()&15);
        mytree.setLeafSize(1.0f+(tomp/10.0f));

        tomp=(rand()&15);
        mytree.setBranchSize(0.1f);

        tomp=(rand()&15);
        mytree.setBranchNoise((tomp/10.0f));


        tomp=(rand()&31);
        mytree.setTwist(45.0f+tomp);


        mytree.build(daTrees[i],daLeaf[i],&tmpv);
        Pos[i].vx=(rand()&1023);
        Pos[i].vy=(rand()&1023);
        Pos[i].vz=m_Terra.FindHeightAt(Pos[i].vx,Pos[i].vy);
        //512,512,m_Terra.FindHeightAt(512,512));
    }
   */ 
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPreview::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
    tertex->UnLoad();
    glDeleteTextures(1,&DetailTex.TexId);
    glDeleteTextures(1,(unsigned int*)&WaterTexID);
	CDialog::OnClose();
}
