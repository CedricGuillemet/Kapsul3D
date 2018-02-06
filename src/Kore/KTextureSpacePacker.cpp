// TextureSpacePacker.cpp: implementation of the CKTextureSpacePacker class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
/*
#include "TextureSpacePacker.h"

#include <stdio.h>
*/
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CKTextureSpace *Entry;

CKTextureSpacePacker::~CKTextureSpacePacker()
{
    CKTextureSpace *datex=FirstTexture;
    while (datex!=NULL)
    {
        CKTextureSpace *tmp=datex->Next;
        delete datex;
        datex=tmp;
    }
}

void CKTextureSpacePacker::AddTextureFragment(int _SizeX,int _SizeY, BYTE *lpBits, int &TextureInd, float &tu, float &tv, float &stu, float &stv,bool Boxed)
{
	int tmpInd=0;

    TextureInd=-1;


    for (CKTextureSpace *datex=FirstTexture;datex;datex=datex->Next)
    {
        if (datex->FindPlace(_SizeX,_SizeY,lpBits,tu,tv,stu,stv,Boxed))
		{
			TextureInd=tmpInd;
            return;
		}
		tmpInd++;
    }

    // add new texture
    if (FirstTexture==NULL)
    {
        FirstTexture=new CKTextureSpace(SizeX,SizeY);
        NextTexture=FirstTexture;
    }
    else
    {
        NextTexture->Next=new CKTextureSpace(SizeX,SizeY);
        NextTexture=NextTexture->Next;
    }
    
    NextTexture->FindPlace(_SizeX,_SizeY,lpBits,tu,tv,stu,stv,Boxed);
	TextureInd=tmpInd;
}

void CKTextureSpacePacker::WriteRaw()
{
    char temp[512];
    int i=0;

    for (CKTextureSpace *datex=FirstTexture;datex;datex=datex->Next)
    {
        sprintf(temp,"LightMap%d.bmp",i++);
        datex->WriteToFile(temp);
    }
}

CKTextureSpacePacker::CKTextureSpacePacker(int _SizeX, int _SizeY)
{
    SizeX=_SizeX;
    SizeY=_SizeY;

    FirstTexture=NULL;
    NextTexture=NULL;

}

void CKTextureSpacePacker::AddToScene(CKScene *Scene, bool MapObject,int Canal)
{
    char temp[512];
    int i;
	CKMesh *daMesh;
	vector<CKTexture*> m_AllTx;

	i=0;
    for (CKTextureSpace *datex=FirstTexture;datex;datex=datex->Next)
    {
        sprintf(temp,"LightMap%d.bmp",i++);
		CKTexture *tmptex=Scene->GetTexByShortName(temp);

		if (tmptex!=NULL)
		{
			//tmptex->
			if (tmptex->TexID!=-1)
			{
				Scene->m_Renderer->FreeTexture(&tmptex->TexID);
			}
			datex->Tex=tmptex;
		}
		else
		{
			
			datex->Tex=Scene->AddTex(temp);
			datex->Tex->BlurFunc=1;
			datex->Tex->UseBGR=true;
			datex->CopyBitsTo(datex->Tex->AllocateRawData(SizeX,SizeY));
		}

		m_AllTx.push_back(datex->Tex);

	}

	// map with TAG
	//i=0;
	if (MapObject)
	{
		for (daMesh=Scene->FirstMesh;daMesh!=NULL;daMesh=daMesh->Next)
		{
			for (i=0;i<daMesh->nb2poly;i++)
			{
				switch (Canal)
				{
				case 0:
//						strcpy(daObj->TexName1,datex->Tex->FileName);
					daMesh->pl[i].Maps[0]=m_AllTx[daMesh->pl[i].Tag];
					//daMesh->Tex1->Type=TEXTURE_FILE;
					

					break;
				case 1:
					//strcpy(daObj->TexName2,datex->Tex->FileName);
					daMesh->pl[i].Maps[1]=m_AllTx[daMesh->pl[i].Tag];
					daMesh->Tex2=daMesh->pl[i].Maps[1];
					//daMesh->Tex2->Type=TEXTURE_RAW;
					break;
				}
			}
		}
	}
	m_AllTx.erase(m_AllTx.begin(),m_AllTx.end());
	
	/*
	if (MapObject)
	{
	    for (CKTextureSpace *datex=FirstTexture;datex;datex=datex->Next)
		{
			for (daMesh=Scene->FirstMesh;daMesh!=NULL;daMesh=daMesh->Next)
			{
				if (daMesh->Tag==i)
				{
					switch (Canal)
					{
					case 0:
//						strcpy(daObj->TexName1,datex->Tex->FileName);
						daMesh->Tex1=datex->Tex;
						//daMesh->Tex1->Type=TEXTURE_FILE;
						

						break;
					case 1:
						//strcpy(daObj->TexName2,datex->Tex->FileName);
						daMesh->Tex2=datex->Tex;
						//daMesh->Tex2->Type=TEXTURE_RAW;
						break;
					}
				}
			}
			i++;
		}
	}
	*/
}
