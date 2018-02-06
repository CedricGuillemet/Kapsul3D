// TextureSpacePacker.h: interface for the CTextureSpacePacker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXTURESPACEPACKER_H__C19D9EC9_24D5_4541_B221_FD00BFFA32F0__INCLUDED_)
#define AFX_TEXTURESPACEPACKER_H__C19D9EC9_24D5_4541_B221_FD00BFFA32F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class KAPSUL_DESC CKTextureSpacePacker  
{
public:
	void AddToScene(CKScene *Scene,bool MapObject,int Canal);
	CKTextureSpacePacker(int _SizeX,int _SizeY);
	void WriteRaw(void);
	void AddTextureFragment(int _SizeX,int _SizeY,BYTE *lpBits,int &TextureInd, float &tu, float &tv, float &stu, float &stv,bool Boxed);
	virtual ~CKTextureSpacePacker();

protected:
	int SizeX;
    int SizeY;
    CKTextureSpace *FirstTexture,*NextTexture;
};

#endif // !defined(AFX_TEXTURESPACEPACKER_H__C19D9EC9_24D5_4541_B221_FD00BFFA32F0__INCLUDED_)
