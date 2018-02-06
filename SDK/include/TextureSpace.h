// TextureSpace.h: interface for the CTextureSpace class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXTURESPACE_H__C8F2771D_97F8_4621_8EE3_DFC4DE9ECF43__INCLUDED_)
#define AFX_TEXTURESPACE_H__C8F2771D_97F8_4621_8EE3_DFC4DE9ECF43__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Texture.h"
class  __declspec(dllexport) CTextureSpaceEntry  
{
public:
	inline CTextureSpaceEntry(int _x,int _y,int _sx,int _sy)
    {
        x=_x;
        y=_y;
        sx=_sx;
        sy=_sy;

        Down=NULL;
        Left=NULL;
        Other=NULL;
    }

	virtual ~CTextureSpaceEntry()
    {
        if (Left!=NULL) delete Left;
        if (Down!=NULL) delete Down;
        if (Other!=NULL) delete Other;
    }

public:
	CTextureSpaceEntry *Left;
    CTextureSpaceEntry *Down;
    CTextureSpaceEntry *Other;
    int x,y,sx,sy;
};


class  __declspec(dllexport) CTextureSpace  
{
public:
	void CopyBitsTo(BYTE *Dest);
	CTextureSpace *Next;
	void WriteToFile(char *FileName);
	bool FindPlace(int _SizeX,int _SizeY,BYTE *Bits,float &tu,float &tv,float &stu,float &stv,bool Boxed);

	CTextureSpace(int _SizeX,int _SizeY);
	virtual ~CTextureSpace();
	CTexture *Tex;
protected:
	int Surface;
	inline void CopyBits(CTextureSpaceEntry *Node,BYTE *bits,bool Boxed);
	inline bool RecursFindPlace(CTextureSpaceEntry *Node,int _SizeX,int _SizeY,BYTE *Bits,/*float &tu,float &tv,float &stu,float &stv,*/int dax,int day,int dasx,int dasy,bool Boxed);
	CTextureSpaceEntry *Entry;
	BYTE *lpBits;
	int SizeX;
	int SizeY;
    float Currentstv,Currentstu;
    float Currenttv,Currenttu;

};

#endif // !defined(AFX_TEXTURESPACE_H__C8F2771D_97F8_4621_8EE3_DFC4DE9ECF43__INCLUDED_)
