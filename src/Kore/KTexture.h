// Texture.h: interface for the CKTexture class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXTURE_H__F1BD4CAE_6B83_4DE7_8CD4_0771D66F5B80__INCLUDED_)
#define AFX_TEXTURE_H__F1BD4CAE_6B83_4DE7_8CD4_0771D66F5B80__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define TEXTURE_FILE 1
#define TEXTURE_PLUGIN 2
#define TEXTURE_RESSOURCE 3
#define TEXTURE_RAW 4
#define TEXTURE_IMAGE 5

#include "Kapsul3D.h"
class CKRenderer;

class KAPSUL_DESC CKTexture  
{
public:
    CString FileName;
	CString ShortName;
    int Type;   //TEXTURE_XXX
    int ResID;
    char *PluginData;
    unsigned int TexID;
    unsigned char *RawData;
    unsigned long RawSizeX,RawSizeY;
	int SizeX,SizeY;
    bool ComputeAlpha;
	CKScene *m_Scene;
	CKRenderer *m_Renderer;
    

    CKTexture *Next,*Prev;

    CKImage *daImg;
	int BlurFunc;
	bool UseBGR;
	int Indice;
public:
	void Load();
    void UnLoad();
	void Bind(void);
	CKTexture(CKScene *pScene=NULL,CKTexture *daPrev=NULL,CKTexture *daNext=NULL);
	virtual ~CKTexture();
    unsigned char * AllocateRawData(unsigned long RSX,unsigned RSY);

};

#endif // !defined(AFX_TEXTURE_H__F1BD4CAE_6B83_4DE7_8CD4_0771D66F5B80__INCLUDED_)
