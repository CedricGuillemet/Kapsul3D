// SkyBox.h: Interface of the class CSkyBox.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKYBOX_H__13E56EA1_AEAF_11D4_8103_000021269F9A__INCLUDED_)
#define AFX_SKYBOX_H__13E56EA1_AEAF_11D4_8103_000021269F9A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/*
#include <shlwapi.h>
#include "Texture.h"
#include "Camera.h"
#include "ProgressWindow.h"
*/
//#include "Material.h"
//#include "Camera.h"
//#include "Texture.h"

#include "Kapsul3D.h"

// Sun placement attributes
#define SUN_DISTANCE -10.0f

// Define this if there is no need to draw a ground
// #define NO_GROUND

// Array indexes for the six skybox textures
#define TEX_FRONT	0
#define TEX_BACK	1
#define TEX_UP		2
#define TEX_DOWN	3
#define TEX_LEFT	4
#define TEX_RIGHT	5

class __declspec( dllexport ) CSkyBox  
{
public:
	void Draw(Camera *pCamera, unsigned int iFOV, float fAspect);

	void SetSunHeight(float fHeight) { m_fSunHeight = fHeight; };
	void SetSunSize(float fSize) { m_fSunSize = fSize; };
	CSkyBox();
	virtual ~CSkyBox();

public:
	float m_fSunHeight;
	float m_fSunSize;
    /*
	Material **m_cTextures;
	Material *m_cSunBaseTexture;
    */
    CTexture **Layer1;
    CTexture **Layer2;

    CTexture *Sky1,*Sky2;
    double Sky1av,Sky2av;
    double Sky1pos,Sky2pos;
    char SkyBoxName[_MAX_PATH];
	void UnLoad(void);

	void Project2D(const float fU, const float fV, const float fPlane,
				   const unsigned int iFOV, float fAspect, float fVertex3DOut[3]);

    void Save(unsigned char * FullPath);
    void Load(unsigned char * FullPath);
	void DrawSun(Camera *pCamera);
};

#endif // !defined(AFX_SKYBOX_H__13E56EA1_AEAF_11D4_8103_000021269F9A__INCLUDED_)
