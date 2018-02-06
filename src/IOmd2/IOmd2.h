// KIOmd2.h: interface for the CKIOmd2 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KIOmd2_H__F6539E57_4BF5_45B5_95B6_D4D8499AE4EE__INCLUDED_)
#define AFX_KIOmd2_H__F6539E57_4BF5_45B5_95B6_D4D8499AE4EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct GEKMD2HEADER
{
	DWORD dwID;
	DWORD dwVersion;
	
	DWORD dwSkinWidth;
	DWORD dwSkinHeight;
	DWORD dwFrameSize;
	
	DWORD dwNumSkins;
	DWORD dwNumVertices;
	DWORD dwNumST;
	DWORD dwNumTriangles;
	DWORD dwNumGLCmds;
	DWORD dwNumFrames;
	
	DWORD dwOffSkins;
	DWORD dwOffST;
	DWORD dwOffTris;
	DWORD dwOffFrames;
	DWORD dwOffGLCmds;
	DWORD dwOffEnd;
};

struct GEKMD2ALIASFRAME
{
    float sfX, sfY, sfZ;
    float tfX, tfY, tfZ;
	
	//Vertex vScale, vTranslate;
	char strName[16];
	struct GEKMD3ALIASTRIANGLE
	{
		BYTE lpVertices[3];
		BYTE bNormal;
	} lpTriangles[1];
};

//#include <pshpack2.h>

enum EQUAKE2BSPLUMPS
{
	Q2BSP_Entities					= 0,
		Q2BSP_Planes					= 1,
		Q2BSP_Vertices					= 2,
		Q2BSP_Visibility				= 3,
		Q2BSP_Nodes						= 4,
		Q2BSP_TexInfo					= 5,
		Q2BSP_Faces						= 6,
		Q2BSP_Lighting					= 7,
		Q2BSP_Leaves					= 8,
		Q2BSP_LeafFaces					= 9,
		Q2BSP_LeafBrushes				= 10,
		Q2BSP_Edges						= 11,
		Q2BSP_SurfaceEdges				= 12,
		Q2BSP_Models					= 13,
		Q2BSP_Brushes					= 14,
		Q2BSP_BrushSides				= 15,
		Q2BSP_Pop						= 16,
		Q2BSP_Areas						= 17,
		Q2BSP_AreaPortals				= 18,
		Q2BSP_NumLumps					= 19,
};

#define	Q2TEX_LIGHT					0x1
#define	Q2TEX_SLICK					0x2
#define	Q2TEX_SKY					0x4
#define	Q2TEX_WARP					0x8
#define	Q2TEX_TRANS33				0x10
#define	Q2TEX_TRANS66				0x20
#define	Q2TEX_FLOWING				0x40
#define	Q2TEX_NODRAW				0x80
#define	Q2TEX_HINT					0x100
#define	Q2TEX_SKIP					0x200

#define	Q2CONTENT_SOLID				1
#define	Q2CONTENT_WINDOW			2
#define	Q2CONTENT_AUX				4
#define	Q2CONTENT_LAVA				8
#define	Q2CONTENT_SLIME				16
#define	Q2CONTENT_WATER				32
#define	Q2CONTENT_MIST				64
#define	Q2CONTENT_AREAPORTAL		0x8000
#define	Q2CONTENT_PLAYERCLIP		0x10000
#define	Q2CONTENT_MONSTERCLIP		0x20000
#define	Q2CONTENT_CURRENT_0			0x40000
#define	Q2CONTENT_CURRENT_90		0x80000
#define	Q2CONTENT_CURRENT_180		0x100000
#define	Q2CONTENT_CURRENT_270		0x200000
#define	Q2CONTENT_CURRENT_UP		0x400000
#define	Q2CONTENT_CURRENT_DOWN		0x800000
#define	Q2CONTENT_ORIGIN			0x1000000
#define	Q2CONTENT_MONSTER			0x2000000
#define	Q2CONTENT_DEADMONSTER		0x4000000
#define	Q2CONTENT_DETAIL			0x8000000
#define	Q2CONTENT_TRANSLUCENT		0x10000000
#define	Q2CONTENT_LADDER			0x20000000

#define	Q2MASK_ALL					(-1)
#define	Q2MASK_SOLID				(Q2CONTENT_SOLID|Q2CONTENT_WINDOW)
#define	Q2MASK_PLAYERSOLID			(Q2CONTENT_SOLID|Q2CONTENT_PLAYERCLIP|Q2CONTENT_WINDOW|Q2CONTENT_MONSTER)
#define	Q2MASK_DEADSOLID			(Q2CONTENT_SOLID|Q2CONTENT_PLAYERCLIP|Q2CONTENT_WINDOW)
#define	Q2MASK_MONSTERSOLID			(Q2CONTENT_SOLID|Q2CONTENT_MONSTERCLIP|Q2CONTENT_WINDOW|Q2CONTENT_MONSTER)
#define	Q2MASK_WATER				(Q2CONTENT_WATER|Q2CONTENT_LAVA|Q2CONTENT_SLIME)
#define	Q2MASK_OPAQUE				(Q2CONTENT_SOLID|Q2CONTENT_SLIME|Q2CONTENT_LAVA)
#define	Q2MASK_SHOT					(Q2CONTENT_SOLID|Q2CONTENT_MONSTER|Q2CONTENT_WINDOW|Q2CONTENT_DEADMONSTER)
#define Q2MASK_CURRENT				(Q2CONTENT_CURRENT_0|Q2CONTENT_CURRENT_90|Q2CONTENT_CURRENT_180|Q2CONTENT_CURRENT_270|Q2CONTENT_CURRENT_UP|Q2CONTENT_CURRENT_DOWN)

class CKIomd2 : public CKFilePlugin
{
public:
	CKIomd2();
	virtual ~CKIomd2();

	CString GetName();
	CString GetInfos();
	CString GetFilter();
	CString GetFileDescription();
	CString GetFileExtension();
	bool SupportReading();
	bool SupportWriting();
	bool Read(CKScene *pScene,CString FullFilePath);
	bool Write(CKScene *pScene,CString FullFilePath);
private:
	GEKMD2HEADER Header;

	WORD *lpIndices;
	Vertex **lpVertices;
	Vertex **lpNormals;
};

#endif // !defined(AFX_KIOmd2_H__F6539E57_4BF5_45B5_95B6_D4D8499AE4EE__INCLUDED_)
