// KIoMd3.h: interface for the CKIoTxt class.
//
//////////////////////////////////////////////////////////////////////
#include "..\common\3dtypes.h"

#if !defined(_KIOMD3_INCLUDED_)
#define _KIOMD3_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef unsigned char  byte;
typedef unsigned short word;
typedef unsigned long  dword;

typedef signed char  sbyte;
typedef signed short sword;
typedef signed long  sdword;

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//-----------------------------------------------------------------
// A very simple multiple path structure 
// Use to load multiple MD3 file
//-----------------------------------------------------------------
#define MAX_NUMBER_OF_PATH	10
struct ALL_PATH_STRUCT
{
	int NumberOfPath;
	char Path[MAX_NUMBER_OF_PATH][1024];
};

//--------------------------------------------------------------------
//	Some specific stuff to the MD3 file format
//--------------------------------------------------------------------
// Various errors
enum MD3Error
{
   MD3ErrorNone = 0,
   MD3ErrorFatal,
   MD3ErrorFileNotFound,
   MD3ErrorIdent,
   MD3ErrorVersion,
   MD3ErrorMaxFrames,
   MD3ErrorMaxSurfaces,
   MD3ErrorMaxTriangles,
   MD3ErrorMaxVerts,
   MD3ErrorMaxShaders,
   MD3ErrorMaxTags
};

//--------------------------------------------------------------------
// Taken from qfiles.h from the Quake3 tools source code
//--------------------------------------------------------------------
enum
{
   MAX_QPATH         = 64,
   MD3_IDENT         = (('3' << 24) + ('P' << 16) + ('D' << 8) + 'I'),
   MD3_VERSION       = 15,

   MD3_MAX_LODS      = 4,
   MD3_MAX_TRIANGLES = 8192,	// per surface
   MD3_MAX_VERTS     = 4096,	// per surface
   MD3_MAX_SHADERS   = 256,		// per surface
   MD3_MAX_FRAMES    = 1024,	// per model
   MD3_MAX_SURFACES  = 32,		// per model
   MD3_MAX_TAGS      = 16,		// per frame
};

struct MD3FileHeader	//108 bytes long
{
	int	ident;
	int	version;

	char	name[MAX_QPATH];	// model name

	int	flags;	

	int	numFrames;	//Number of bone frames
	int	numTags;	//Number of tags
	int	numSurfaces;	//Number of meshes

	int	numSkins;

	int	ofsFrames;		// Offset for first frame = MD3FileHeader size
	int	ofsTags;		// Offset of first tag (numFrames * numTags)
	int	ofsMeshes;	// Offset of first Mesh, others follow

	int	ofsEnd;			// end of file - file size
};


struct MD3FileFrame	//56 bytes long
{
	o_vert3f	bounds[2];		//Bounding box
	o_vert3f	localOrigin;	//Position of the bone frame
	float	radius;				//radius of the bone frame
	char	name[16];			//Creator string
};

struct MD3FileTag	//112 bytes long
{
	char	name[MAX_QPATH];	// tag name
	o_vert3f	origin;
	o_vert3f	axis[3];
};

//--------------------------------------------------------------------
// MD3FileMesh
//
// CHUNK		SIZE
// header		sizeof( MD3FileMesh )
// shaders		sizeof( MD3FileShader ) * numShaders
// triangles[0]	sizeof( MD3FileTriangle ) * numTriangles
// st			sizeof( MD3FileSt ) * numVerts
// XyzNormals	sizeof( MD3FileXyzNormal ) * numVerts * numFrames
//--------------------------------------------------------------------

struct MD3FileMesh
{
	int	ident;	// 

	char	name[MAX_QPATH];	// polyset name

	int	flags;

	int	numFrames;	// all surfaces in a model should have the same
	int	numShaders;	// all surfaces in a model should have the same
	int	numVerts;
	int	numTriangles;

	int	ofsTrianglesStart;
	int	ofsShadersStart;				// offset from start of md3Surface_t
	int	ofsTextureCoordStart;	// texture coords are common for all frames
	int	ofsVertexStart;			// numVerts * numFrames

	int	ofsEnd;			// next surface follows
};

struct MD3FileShader
{
	char	name[MAX_QPATH];
	int	shaderIndex;	// for in-game use
};

struct MD3FileTriangle
{
	int	indexes[3];
};

struct MD3FileTextureCoordinate
{
	float	st[2];
};

struct MD3FileVertex
{
	short	xyz[3];
	short	normal;
};

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

//==============================================================
// Our Material class
//==============================================================

class CTmpMaterial
{
public:
	CTmpMaterial(){ pTexture = NULL; szMatName.Empty();};
	~CTmpMaterial(){ pTexture = NULL; szMatName.Empty();};

	CKTexture *pTexture;
	CString  szMatName;
};

//==============================================================
// Our MD3 file plugin class
//==============================================================

class CKIoMD3 : public CKFilePlugin
{
public:
	CKIoMD3();
	virtual ~CKIoMD3();

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
	//Data members
	char temp[512];
	CKOption *m_Option;
	CKMesh  *m_pMesh;
	CKScene *m_pScene;
	CObArray matArray;
	int	curTexMatIndex;
	CString szTmpNameContainer;	
	FILE *f;
	long m_lFileLenght;
	int ind;
	long p;
	int currentObject;
	bool value;

	//Internal 3D object related
	t_3Dobject *m_pObj;	//Our internal 3DObject
	o_mesh *m_pActualMesh;	//The actual mesh we are working on

	//** Important **
	bool IsFormatValid(char* filename);
	
	//MD3 specific
	int m_iNumFrames;   // Number of frames
	int m_iNumTags;	  // Number of tags
	int m_iNumMeshes; // Number of Meshes
	int m_iNumSkins;    // Number of skins

	MD3FileTag *m_pTags;
	MD3FileFrame *m_pFrames;
	MD3FileMesh *m_pMeshes;

	bool ReadMD3File(char *Buffer);
	int LoadMinimumData(char *Buffer);
	int LoadMeshes(char* buffer);

	//Functions members

	void CleanUp();
	bool LoadMD3(char *FileName);
	bool SaveMD3(char *FileName);

	bool EnumerateFile(char *Filename, ALL_PATH_STRUCT *AllFilename);
};

#endif // !defined(_KIOMD3_INCLUDED_)
