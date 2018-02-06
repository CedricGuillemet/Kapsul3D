// Texture.cpp: implementation of the CKTexture class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
//#include "memmgr/mmgr.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern HINSTANCE ghInstDLL;



CKTexture::CKTexture(CKScene *pScene,CKTexture *daPrev,CKTexture *daNext)
{
	m_Scene=pScene;
	m_Renderer=pScene->m_Renderer;
    Type=TEXTURE_RESSOURCE;
    ResID=0;
    TexID=-1;
    RawData=NULL;
    RawSizeX=0;
    RawSizeY=0;
    ComputeAlpha=false;
	BlurFunc=0;
	UseBGR=false;

    Next=daNext;
    Prev=daPrev;
	
}

CKTexture::~CKTexture()
{
    if (RawData!=NULL) delete [] RawData;
    if (TexID!=-1)
    {
        //glDeleteTextures(1,(const unsigned int*)&TexID);
		m_Renderer->FreeTexture(&TexID);
    }

}

void CKTexture::Bind()
{
    if (TexID!=-1)
        //glBindTexture(GL_TEXTURE_2D,TexID);			// Select Our Texture
		m_Renderer->BindTexture((void*)&TexID);
	else
	{
		Load();
		if (TexID!=-1)
			//glBindTexture(GL_TEXTURE_2D,TexID);			// Select Our Texture
			m_Renderer->BindTexture((void*)&TexID);
	}
}

void CKTexture::Load()
{
    if (TexID!=-1)
    {
        //glDeleteTextures(1,(const unsigned int*)&TexID);
		m_Renderer->FreeTexture(&TexID);
    }

	m_Renderer->LoadTexture(FileName,&TexID,SizeX,SizeY);
/*
    switch(Type)
    {
    case TEXTURE_PLUGIN:
        break;
    case TEXTURE_FILE:
		
        break;
    case TEXTURE_RESSOURCE: // only used once! and internal use ;-))
        daImg=new CKImage;
        daImg->LoadFromRessource(ghInstDLL,MAKEINTRESOURCE(IDR_TEXTURE), IMG_FORMAT_BMPWIN, "IMAGES");
        TexID=daImg->Upload(0,UseBGR);
		SizeX=daImg->GetWidth();
		SizeY=daImg->GetHeight();
        delete daImg;
        break;
    case TEXTURE_RAW:
        if (RawData!=NULL)
        {
            daImg=new CKImage;
            daImg->InitRaw(RawSizeX,RawSizeY);

    	    LPBITMAPINFOHEADER BiDest=(LPBITMAPINFOHEADER)GlobalLock(daImg->m_hDib);			
            BYTE *lpBits = ((BYTE*)BiDest)+sizeof(BITMAPINFOHEADER);
            memcpy(lpBits,RawData,(RawSizeX*RawSizeY*3));

			//if (BlurFunc)
				//daImg->Effect24MatrixFilter(FILTER_BLUR_MEAN_3x3);

            if (!ComputeAlpha) TexID=daImg->Upload(0,UseBGR);
                else TexID=daImg->UploadAlpha(0,UseBGR);

			SizeX=daImg->GetWidth();
			SizeY=daImg->GetHeight();

            delete daImg;
        }
        else
        {
            Type=TEXTURE_RESSOURCE;
            Load();
        }
        break;
	case TEXTURE_IMAGE:
		daImg->TexId=-1;
		if (!ComputeAlpha) TexID=daImg->Upload(0,UseBGR);
                else TexID=daImg->UploadAlpha(0,UseBGR);
		break;

    default:
        break;

    }
*/
}

unsigned char * CKTexture::AllocateRawData(unsigned long RSX, unsigned int RSY)
{
	Type=TEXTURE_RAW;
    RawData=new unsigned char [RSX*RSY*3];
    RawSizeX=RSX;
    RawSizeY=RSY;

    return RawData;
}

void CKTexture::UnLoad()
{
    if (TexID!=-1)
    {
        //glDeleteTextures(1,(const unsigned int*)&TexID);
		m_Renderer->FreeTexture(&TexID);
        TexID=-1;
    }
}
