// TextureSpacePacker.h: interface for the CTextureSpacePacker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXTURESPACEPACKER_H__C19D9EC9_24D5_4541_B221_FD00BFFA32F0__INCLUDED_)
#define AFX_TEXTURESPACEPACKER_H__C19D9EC9_24D5_4541_B221_FD00BFFA32F0__INCLUDED_

#include "TextureSpace.h"	// Added by ClassView

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class  __declspec(dllexport) CTextureSpacePacker  
{
public:
	void AddToDesk(Desk *dk,bool MapObject,int Canal);
	CTextureSpacePacker(int _SizeX,int _SizeY);
	void WriteRaw(void);
	void AddTextureFragment(int _SizeX,int _SizeY,BYTE *lpBits,int &TextureInd, float &tu, float &tv, float &stu, float &stv,bool Boxed);
	virtual ~CTextureSpacePacker();

protected:
	int SizeX;
    int SizeY;
    CTextureSpace *FirstTexture,*NextTexture;
};

#endif // !defined(AFX_TEXTURESPACEPACKER_H__C19D9EC9_24D5_4541_B221_FD00BFFA32F0__INCLUDED_)
