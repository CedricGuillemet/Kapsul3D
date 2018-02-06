//-----------------------------------------------------------------------------
// File: CSG.h
//
// Desc: Constructive Solid Geometry and Hidden Surface Removal Tutorial
//
// Copyright (c) 2000-2001. Adam Hoult & Gary Simmons. All rights reserved.
//-----------------------------------------------------------------------------


#ifndef _CSG_H_
#define _CSG_H_

//-----------------------------------------------------------------------------
// Application Includes
//-----------------------------------------------------------------------------
/*
#include <d3dx8.h>
#include <stdio.h>					
#include <d3d8.h>
#include <d3dx8math.h>
/*
#include <mmsystem.h>
#include <time.h>
*/

#include <stdio.h>					
//#include <d3dx8math.h>

//-----------------------------------------------------------------------------
// Miscellaneous Application Definitions and constants
//-----------------------------------------------------------------------------
#define SCREENWIDTH				640
#define SCREENHEIGHT			480
#define VIEWMODE_FIRSTPERSON	0
#define VIEWMODE_TOPDOWN		1

#define CSG_NONE				0
#define CSG_DIFFERENCE			1
#define CSG_INTERSECTION		2
#define CSG_UNION				3

#define D3DFVF_VERTEX ( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 )

#define CHUNK_BEGINMESHES		0x4000
#define CHUNK_MESHDETAILS		0x4001
#define CHUNK_POLYS				0x4002
#define CHUNK_VERTEXCOORDS		0x4010
#define CHUNK_VERTEXDIFFUSE		0x4011
#define CHUNK_VERTEXTEXCOORDS	0x4012
#define CHUNK_INDICES			0x4030
#define	CHUNK_ENDMESHES			0x4040
#define CHUNK_TEXTURELUT		0x4050
#define CHUNK_ENTITIES			0x4055
#define CHUNK_EOF				0x4100

const FLOAT g_PI       =  3.14159265358979323846f; // Pi
const FLOAT g_DEGTORAD =  0.01745329251994329547f; // Degrees to Radians
const FLOAT g_EPSILON  =  0.001f;				   // Float Tolerance

//-----------------------------------------------------------------------------
// Application Structures
//-----------------------------------------------------------------------------
/*
typedef struct {							// IWF File Header
	DWORD	Identifier;						// File identifier (should always be 'IIWF' )
	FLOAT	Version;						// File Version Number
	DWORD	dwDummy;						// Dummy DWORD
}IWFFILEHEADER;

struct D3DVERTEX							// Our Pre-Lit Multi-TexCoord Vertex Structure
{
    float		x, y, z;					// Vertex Position
	D3DXVECTOR3 Normal;						// Vertex Normal
	float		tu , tv;					// Base Texture Coordinates	
};


struct POLYGON								// Actual Polygon storage structure
{
	D3DVERTEX	*Vertices;					// Pointer to List of vertices.
	WORD		*Indices;					// Actual index buffer
	WORD		VertexCount;				// Number of vertices stored
	WORD		IndexCount;					// Number of indices stored
	D3DXVECTOR3 Normal;						// Polygons Normal Vector
	int			TextureIndex;				// Index into texture array
};

struct BBOX {								// Bounding Box Structure
	D3DXVECTOR3 Min;						// Bounds Min Vector
	D3DXVECTOR3 Max;						// Bounds Max Vector
};

struct BRUSH								// Stores the brush data
{
	BBOX		Bounds;						// Brushes Bounding Box
	POLYGON		*Faces;						// Polygon Data
	ULONG		FaceCount;					// Face Count
	D3DXMATRIX	Matrix;						// Brushes Translation Matrix
	class CBSPTree *BSPTree;				// Brushes BSP Tree (each brush has one)
};
*/
//-----------------------------------------------------------------------------
// Extern Variables
//-----------------------------------------------------------------------------
/*
extern LPDIRECT3DTEXTURE8		lpTextureSurface[3];
extern LPDIRECT3DDEVICE8		lpDevice;
*/
extern BOOL						g_bCompileFinal;
extern BOOL						g_bSafeTransform;
extern BOOL						g_bWireFrame;
extern int						g_iLastTexture;
extern int						g_iCSGBrush;
extern int						g_iCSGMode;	
extern int						NumberOfTextures;

//-----------------------------------------------------------------------------
// Shared Functions
//-----------------------------------------------------------------------------
/*
D3DXVECTOR3 CalculatePolyNormal( D3DVERTEX v1, D3DVERTEX v2, D3DVERTEX v3, D3DXMATRIX *Matrix );
BOOL		EpsilonCompareVector( D3DXVECTOR3 Vec1, D3DXVECTOR3 Vec2 ) ;
*/

#endif // _CSG_H_
