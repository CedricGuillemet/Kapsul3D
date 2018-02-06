// TextureSpace.h: interface for the CKTextureSpace class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXTURESPACE_H__C8F2771D_97F8_4621_8EE3_DFC4DE9ECF43__INCLUDED_)
#define AFX_TEXTURESPACE_H__C8F2771D_97F8_4621_8EE3_DFC4DE9ECF43__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class  KAPSUL_DESC CKTextureSpaceEntry  
{
public:
	inline CKTextureSpaceEntry(int _x,int _y,int _sx,int _sy)
    {
        x=_x;
        y=_y;
        sx=_sx;
        sy=_sy;

        Down=NULL;
        Left=NULL;
        Other=NULL;
    }

	virtual ~CKTextureSpaceEntry()
    {
        if (Left!=NULL) delete Left;
        if (Down!=NULL) delete Down;
        if (Other!=NULL) delete Other;
    }

public:
	CKTextureSpaceEntry *Left;
    CKTextureSpaceEntry *Down;
    CKTextureSpaceEntry *Other;
    int x,y,sx,sy;
};


class KAPSUL_DESC CKTextureSpace  
{
public:
	void CopyBitsTo(BYTE *Dest);
	CKTextureSpace *Next;
	void WriteToFile(char *FileName);
	bool FindPlace(int _SizeX,int _SizeY,BYTE *Bits,float &tu,float &tv,float &stu,float &stv,bool Boxed);

	CKTextureSpace(int _SizeX,int _SizeY);
	virtual ~CKTextureSpace();
	CKTexture *Tex;
protected:
	int Surface;
	inline void CopyBits(CKTextureSpaceEntry *Node,BYTE *bits,bool Boxed);
	inline bool RecursFindPlace(CKTextureSpaceEntry *Node,int _SizeX,int _SizeY,BYTE *Bits,/*float &tu,float &tv,float &stu,float &stv,*/int dax,int day,int dasx,int dasy,bool Boxed);
	CKTextureSpaceEntry *Entry;
	BYTE *lpBits;
	int SizeX;
	int SizeY;
    float Currentstv,Currentstu;
    float Currenttv,Currenttu;

};

#endif // !defined(AFX_TEXTURESPACE_H__C8F2771D_97F8_4621_8EE3_DFC4DE9ECF43__INCLUDED_)
