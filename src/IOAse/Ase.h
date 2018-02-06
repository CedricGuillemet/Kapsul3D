#ifndef _ASE_H
#define _ASE_H

//#include "Main.h"

// Below are a all the important tag defines for reading in a .Ase file.
// I added the normal ones just in case you want to you read them in instead
// of calculate them yourself.

#define OBJECT				"*GEOMOBJECT"			// An object tag for new objects
#define NUM_VERTEX			"*MESH_NUMVERTEX"		// The number of vertices tag
#define NUM_FACES			"*MESH_NUMFACES"		// The number of faces tag
#define NUM_TVERTEX			"*MESH_NUMTVERTEX"		// The number of texture coordinates
#define VERTEX				"*MESH_VERTEX"			// The list of vertices tag
#define FACE				"*MESH_FACE"			// The list of faces tag
#define NORMALS				"*MESH_NORMALS"			// The list of normals tag (If you want)
#define FACE_NORMAL			"*MESH_FACENORMAL"		// The face normal for the current index
#define NVERTEX				"*MESH_VERTEXNORMAL"	// The list of vertex normals
#define TVERTEX				"*MESH_TVERT"			// The texture coordinate index tag
#define TFACE				"*MESH_TFACE"			// The vertex index tag
#define TEXTURE				"*BITMAP"				// The file name for the object's texture map
#define UTILE				"*UVW_U_TILING"			// The U tiling ratio tag
#define VTILE				"*UVW_V_TILING"			// The V tiling ratio tag
#define UOFFSET				"*UVW_U_OFFSET"			// The U tile offset tag
#define VOFFSET				"*UVW_V_OFFSET"			// The V tile offset tag
#define MATERIAL_ID			"*MATERIAL_REF"			// The material ID tag
#define MATERIAL_COUNT      "*MATERIAL_COUNT"		// The material count tag
#define MATERIAL			"*MATERIAL"				// The material tag
#define MATERIAL_NAME		"*MATERIAL_NAME"		// The material name tag
#define MATERIAL_COLOR		"*MATERIAL_DIFFUSE"		// The material color tag

struct tMaterialInfo
{
	char  strName[255];			// The texture name
	char  strFile[255];			// The texture file name (If this is set it's a texture map)
	BYTE  color[3];				// The color of the object (R, G, B) from 0 to 255
	float fColor[3];			// The color of the object (R, G, B) from 0 to 1
	int   texureId;				// the texture ID
	float uTile;				// u tiling of texture  (Currently not used)
	float vTile;				// v tiling of texture	(Currently not used)
	float uOffset;			    // u offset of texture	(Currently not used)
	float vOffset;				// v offset of texture	(Currently not used)
} ;
/*
struct t3DModel 
{
	int numOfObjects;					// The number of objects in the model
	int numOfMaterials;					// The number of materials for the model
	vector<tMaterialInfo> pMaterials;	// The list of material information (Textures and colors)
	vector<t3DObject> pObject;			// The object list for our model
};

*/
// This class holds all the data and function for loading in a .Ase file.
class CLoadASE 
{

public:

	// This is the only function the client needs to call to load the .ase file
	bool ImportASE(Desk *dk, char *strFileName);

	// This is the main loop that parses the .ase file
	void ReadAseFile(Desk *dk);

	// This returns the number of objects in the .ase file
	int GetObjectCount();

	// This returns the number of materials in the .ase file
	int GetMaterialCount();

	// This fills in the texture information for a desired texture
	void GetTextureInfo (tMaterialInfo *pTexture, int desiredMaterial);

	// This moves our file pointer to the desired object
	void MoveToObject (int desiredObject);

	// This reads in a float from the file
	float ReadFloat();

	// This reads a desired object's information (face, vertex and texture coord counts)
	void ReadObjectInfo(Object *pObject, int desiredObject);

	// This gets the name of the texture
	void GetTextureName (tMaterialInfo  *pTexture);

	// This gets the name of the material
	void GetMaterialName(tMaterialInfo *pTexture);

	// This loads all the data for the desired object
	void ReadObjectData(Object *pObject, int desiredObject);

	// This is the main load loop inside of ReadObjectData() that calls smaller load functions
	void GetData(Object *pObject, char *strDesiredData, int desiredObject);

	// This reads in a vertice from the file
	void ReadVertex(Object *pObject);

	// This reads in a texture coordinate from the file
	void ReadTextureVertex(Object *pObject, tMaterialInfo *texture);

	// This reads in the vertex indices for a face
	void ReadFace(Object *pObject);

	// This reads in texture coordinate indices for a face
	void ReadTextureFace(Object *pObject);

	// This computes the vertex normals for our objects
	//void ComputeNormals(t3DModel *pModel);

private:
	
	// This is our file pointer to load the .ase file
	FILE *m_FilePointer;
};

#endif


/////////////////////////////////////////////////////////////////////////////////
//
// * QUICK NOTES * 
//
// This file holds the class and defines to load a .Ase file.  The .Ase file is
// created by 3D Studio Max, but isn't as nice as the .3DS file format.
//
// 
// 
// Ben Humphrey (DigiBen)
// Game Programmer
// DigiBen@GameTutorials.com
// Co-Web Host of www.GameTutorials.com
//
//