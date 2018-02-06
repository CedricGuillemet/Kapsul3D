// Texture.h: interface for the CTexture class.
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

class __declspec( dllexport ) CTexture  
{
public:
    char *FileName;
    int Type;   //TEXTURE_XXX
    int ResID;
    char *PluginData;
    int TexID;
    unsigned char *RawData;
    unsigned long RawSizeX,RawSizeY;
    bool ComputeAlpha;
    

    CTexture *Next,*Prev;

    CImage *daImg;
	int BlurFunc;
	bool UseBGR;
public:
	void Load();
    void UnLoad();
	void Bind(void);
	CTexture(CTexture *daPrev,CTexture *daNext);
	virtual ~CTexture();
    unsigned char * AllocateRawData(unsigned long RSX,unsigned RSY);

};

#endif // !defined(AFX_TEXTURE_H__F1BD4CAE_6B83_4DE7_8CD4_0771D66F5B80__INCLUDED_)
