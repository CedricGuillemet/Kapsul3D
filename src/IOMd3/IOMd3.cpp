//********************************************************************************
//
// module Name: IOMd3.CPP
//
// Description: Handle MD3 file (Quake3 Model for the Kapsul editor
//
//Creation: March 11th 2003 by GROUMF
//
//********************************************************************************

#include "stdafx.h"
#include <Kapsul3D.h>
#include "IOMd3.h"
#include "..\common\3DObjectStuff.h"

//Useful for the animation stuff
#include "..\common\mathlib.h"
#include "..\common\quat.h"


//====================================================================
// Constructor / Destructor
//====================================================================

CKIoMD3::CKIoMD3()
{
	m_pObj = NULL;
}

CKIoMD3::~CKIoMD3()
{
}

//====================================================================
// Get the name of the module
//
// Input: None
//
// Output:
//	CString - The internal name of this module
//
//====================================================================

CString CKIoMD3::GetName()
{
	return "Quake3 Model (MD3) I/O";
}

//====================================================================
// Get module info
//
// Input: None
//
// Output:
//	CString - A string information on this module
//
//====================================================================

CString CKIoMD3::GetInfos()
{
	return "Quake3 Model (MD3) I/O";
}

//====================================================================
// Get file filter string to be used in the filedialog box
//
// Input: None
//
// Output:
//	CString - The filter string (may have semicolon)
//
//====================================================================

CString CKIoMD3::GetFilter()
{
	return "*.md3";
}

//====================================================================
// Get supported I/O file Desciption
//
// Input: None
//
// Output:
//	CString - The description of the kind of file we handle
//
//====================================================================

CString CKIoMD3::GetFileDescription()
{
	return "Quake3 Model (MD3)";
}

//====================================================================
// Get supported I/O file file extension
//
// Input: None
//
// Output:
//	CString - Standard file extension
//
//====================================================================

CString CKIoMD3::GetFileExtension()
{
	return ".md3";
}

//====================================================================
// Are we supporting import ?
//
// Input: None
//
// Output:
//	bool - true if we are supporting import, false otherwise
//
//====================================================================

bool CKIoMD3::SupportReading()
{
	return true;
}

//====================================================================
// Are we supporting export ?
//
// Input: None
//
// Output:
//	bool - true if we are supporting export, false otherwise
//
//====================================================================

bool CKIoMD3::SupportWriting()
{
	return false;
}

//====================================================================
// Importing a scene
//
// Input:
//	CKScene *pScene - Pointer to a CKScene to load the object into
//	CString FullFilePath - The full path to the file
//
// Output:
//	bool - true if everything is ok, false otherwise
//
//====================================================================

bool CKIoMD3::Read(CKScene *pScene,CString FullFilePath)
{
	m_pScene = pScene;
	m_pMesh=NULL;
	curTexMatIndex = -1;
	CleanUp();

	m_Option = (CKOption*)GetGOption();	//To be used for texture path

	if (IsFormatValid(FullFilePath.GetBuffer(0)) == false)
		return false;

	return LoadMD3(FullFilePath.GetBuffer(0));		
}

//====================================================================
// Exporting a scene
//
// Input:
//	CKScene *pScene - Pointer to a CKScene to save
//	CString FullFilePath - The full path to the file
//
// Output:
//	bool - true if everything is ok, false otherwise
//
//====================================================================
bool CKIoMD3::Write(CKScene *pScene,CString FullFilePath)
{
	m_pScene = pScene;
	m_pMesh=NULL;
	curTexMatIndex = -1;
	CleanUp();

	return SaveMD3(FullFilePath.GetBuffer(0)); //Did everything went right ?
}

//====================================================================
//--- IMPORTANT ---
// This func should be called to clean up before a new loading occurs
//====================================================================
//====================================================================
void CKIoMD3::CleanUp()
{
 value			= false;
 f				= NULL;
 p				= 0;
 currentObject  = -1;
 curTexMatIndex = -1;
 ind			= 0;
 szTmpNameContainer.Empty();

 matArray.SetSize(0);
 matArray.FreeExtra();
}

//====================================================================
// Test if the file is of a valid format
//
// Input:
//	char* filename - The full path name of the file
//
// Output:
//	bool - true if it's a file we can handle
//
//====================================================================

bool CKIoMD3::IsFormatValid(char* filename)
{
FILE *file;
int flength = 0;
char Buffer[255];

	memset(Buffer,0,200);

	//No path ?
	if (filename==NULL)
		return false;

	//Open the file
	file = fopen(filename,"rb");
	if (!file)
		return false;

	//Retrieve the file length
	fseek(file,0,SEEK_END);
	flength = ftell(file);

	//Copy the entire file in our memory buffer
	rewind(file);
	fread(Buffer, 1,10,file);
	fclose(file);

	//Test to see if it's a real MD3 file
	char *Test1 = strstr(Buffer,"IDP3");	//specific MD3 ID

	if (Test1 != NULL)
		return true;
	else
		return false;
}
//=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
// This is now the specific part for the MD3 object file format
//=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=

//====================================================================
// Load an object from an MD3 file and fill the Kapsul scene with it
//
// Input:
//	char* filename - The full path name of the file
//
// Output:
//	bool - true if everything is ok, false otherwise
//
//====================================================================

bool CKIoMD3::LoadMD3( char* filename)
{
char *memfile = NULL;
int flength = 0;
bool loaded = false;
FILE *file;
bool ReturnValue = true;

	//No path ?
	if (filename==NULL)
		return false;
	
	//Reset the object pointer
	if (m_pObj != NULL)
		{
		m_pObj->Delete();
		m_pObj = NULL;
		delete (m_pObj); 
		}
	m_pObj = new t_3Dobject;
	memset(m_pObj,0,sizeof(t_3Dobject));

	//Loading the first file
	//Open the file
	file = fopen(filename,"rb");
	if (!file)
		return FALSE;

	//Retrieve the file length
	fseek(file,0,SEEK_END);
	flength = ftell(file);

	//Allocate buffer large enough to copy the entire file in it
	memfile = new char[flength];

	//Copy the entire file in our memory buffer
	rewind(file);
	fread(memfile, 1,flength,file);
	fclose(file);

	// start file parsing
	m_lFileLenght = flength;
	ReadMD3File(memfile);

	//Delete file memory buffer
	delete memfile;

	//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	//Scanning for the other and load them
	ALL_PATH_STRUCT AllFilename;
	AllFilename.NumberOfPath = 0;
	EnumerateFile(filename, &AllFilename);

	for (int i=0; i<AllFilename.NumberOfPath; i++)
		{
		//Open the file
		file = fopen(AllFilename.Path[i],"rb");
		if (!file)
			return FALSE;

		//Retrieve the file length
		fseek(file,0,SEEK_END);
		flength = ftell(file);

		//Allocate buffer large enough to copy the entire file in it
		memfile = new char[flength];

		//Copy the entire file in our memory buffer
		rewind(file);
		fread(memfile, 1,flength,file);
		fclose(file);

		// start file parsing
		m_lFileLenght = flength;
		ReadMD3File(memfile);

		//Delete file memory buffer
		delete memfile;
		}
	//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

	//if we have no triangle or no points then return an error
//	if (m_pObj->nummeshes==0||m_pObj->numverts==0)
//		ReturnValue = false;
	if (m_pObj->nummeshes !=0)
		ReturnValue = true;

	Compute3DObject_to_KapsulScene(m_pObj,m_pScene);

	//Reset the object pointer
	if (m_pObj != NULL)
		{
		m_pObj->Delete();
		m_pObj = NULL;
		delete (m_pObj); 
		}

return ReturnValue;
}

//====================================================================
// Enumerate all the MD3 files that are present in the directorie
//
// Input:
//	char* filename - The full path name of the file
//
// Output:
//	bool - true if everything is ok, false otherwise
//
//====================================================================

bool CKIoMD3::EnumerateFile(char *Filename, ALL_PATH_STRUCT *AllFilename)
{
char DirectoryPath[1024];
char SearchPath[1024];
int flength = 0;
bool loaded = false;
bool ReturnValue = true;

	//No path ?
	if (Filename==NULL)
		return false;

	//First Extract the directory 
	char *PString;
	PString	= strrchr(Filename,0x2F);	//looking for the last "/"

	if (PString == NULL)
		{
		PString = strrchr(Filename,0x5C);	//looking for the last "\"
		if (PString == NULL)
			return false;
		}

	//We have a valid path so copy it
	int DirectoryPathLength = PString - Filename;

	PString +=1;	//skip the first character

	memset(SearchPath,0,1024);
	strncpy(SearchPath,Filename,DirectoryPathLength+1);
	strcpy(DirectoryPath,SearchPath);
	strcat(SearchPath,"*.md3");

	// read all entries in the directory
	BOOL bMore;
	long filesize;
	BOOL bIsDir;
	LPSTR name;  
	WIN32_FIND_DATA finddata;

	HANDLE hFind = FindFirstFile(SearchPath, &finddata);
	
	bMore = (hFind != (HANDLE) -1);
//	LocalUnlock(LocalHandle ( (PSTR) DirectoryPath));
//	LocalFree(LocalHandle ( (PSTR) DirectoryPath));
	
	while (bMore)
		{
		bIsDir = (finddata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
		name = (LPSTR) &finddata.cFileName;
		filesize = finddata.nFileSizeLow;
		if (bIsDir == 0)
			{
			// We have found a file so copy it's path
//			AllFilename->Path[AllFilename->NumberOfPath] = new char[1024];
			if (strcmp(name,PString) != 0)
				{
				memset(&AllFilename->Path[AllFilename->NumberOfPath][0],0,1024);
				strcpy(&AllFilename->Path[AllFilename->NumberOfPath][0],DirectoryPath);
				strcat(&AllFilename->Path[AllFilename->NumberOfPath][0],name);
				AllFilename->NumberOfPath++;
				}
			}
		bMore = FindNextFile(hFind, &finddata);
		}

	FindClose(hFind);
	
return ReturnValue;
}

//====================================================================
// Save a Kapsul scene in a file
//
// Input:
//	char* filename - The full path name of the file to save
//
// Output:
//	bool - true if everything is ok, false otherwise
//
//====================================================================

bool CKIoMD3::SaveMD3( char* filename)
{
	return TRUE;

}

//====================================================================
// Read the memory buffer and fill up the 3DObject
//
// Input:
//	char* buffer - A memory buffer that contain our file
//
// Output:
//	bool - true if everything is ok, false otherwise
//
//====================================================================

bool CKIoMD3::ReadMD3File(char* Buffer)
{
bool ReturnValue = false;

	m_pFrames = NULL;
	m_pTags = NULL;
	m_pMeshes = NULL;

   if (LoadMinimumData(Buffer) == MD3ErrorNone)
	{
	if (LoadMeshes(Buffer) == MD3ErrorNone)
      ReturnValue = true;
	}

   //Clean up everything
//   if (m_pMeshes != NULL)
//	   delete (m_pMeshes);

   if (m_pFrames != NULL)
	   delete (m_pFrames);

   if (m_pTags != NULL)
	   delete (m_pTags);


return ReturnValue;
}


//====================================================================
// Load the minimum information from the file so we can allocate what
// we have to allocate
//
// Input:
//	char* buffer - A memory buffer that contain our file
//
// Output:
//	bool - true if everything is ok, false otherwise
//
//====================================================================

int CKIoMD3::LoadMinimumData(char* Buffer)
{
MD3FileHeader *header = (MD3FileHeader *) Buffer;
  
	// Check the md3 ident
	if (header->ident != MD3_IDENT)
		return MD3ErrorIdent;

	// Check the md3 version
	if (header->version != MD3_VERSION)
		return MD3ErrorVersion;

	m_iNumFrames = header->numFrames;
	m_iNumTags = header->numTags;
	m_iNumMeshes = header->numSurfaces;
	m_iNumSkins = header->numSkins;

	if (m_iNumFrames > MD3_MAX_FRAMES)
		return MD3ErrorMaxFrames;

	if (m_iNumMeshes > MD3_MAX_SURFACES)
		return MD3ErrorMaxSurfaces;

	if (m_iNumTags > MD3_MAX_TAGS)
		return MD3ErrorMaxTags;

	// Allocate memory for the md3 bones frames frames
	if (m_iNumFrames && !(m_pFrames = new MD3FileFrame[m_iNumFrames]))
		return MD3ErrorFatal;

	// Copy the bone frames
	memcpy(m_pFrames,(void *)(Buffer + header->ofsFrames),(m_iNumFrames)*sizeof(MD3FileFrame));

	// Allocate memory for all of the md3 tag links
	if (m_iNumTags && !(m_pTags = new MD3FileTag[m_iNumTags * m_iNumFrames]))
		return MD3ErrorFatal;

	// Copy the tags
	memcpy(m_pTags,Buffer + header->ofsTags,(m_iNumTags * m_iNumFrames)*sizeof(MD3FileTag));


return MD3ErrorNone;
}

//====================================================================
// Load all the meshes from the MD3 file
//
// Input:
//	byte *Buffer - A memory buffer that contain our file
//
// Output:
//	bool - true if everything is ok, false otherwise
//
//====================================================================
int CKIoMD3::LoadMeshes(char* Buffer)
{
int i = 0;
o_mesh *c_mesh=NULL;
o_poly *c_poly=NULL;
byte *TempPointer;

   // Allocate memory for the surfaces of the model
   if (m_iNumMeshes == 0)
      return MD3ErrorFatal;

   MD3FileHeader *pHeader = (MD3FileHeader *) Buffer;
   TempPointer = ((byte *) (Buffer)) + pHeader->ofsMeshes;
   MD3FileMesh *pMeshes = (MD3FileMesh *) (TempPointer);
   // Position the buffer pointer to the start of the first mesh
   MD3FileMesh *pActualPos = (MD3FileMesh *)pMeshes;
 

	// Load all the meshes
	for (i = 0; i < m_iNumMeshes; ++i)
		{
		//First Mesh Entry
		if (m_pObj->meshes==NULL)
			{
			c_mesh = m_pObj->meshes = new o_mesh;
			memset(c_mesh,0,sizeof(o_mesh));
			m_pObj->nummeshes++;
			}
		else
			{
			o_mesh *tm=m_pObj->meshes;
			while (tm->next) tm=tm->next;
			c_mesh = new o_mesh;
			memset(c_mesh,0,sizeof(o_mesh));
			tm->next = c_mesh;
			tm->next->prev = tm;
			m_pObj->nummeshes++;
			}

		// copy the name of the mesh
		strncpy(c_mesh->name, pActualPos->name,MAX_QPATH);

		c_mesh->numverts = pActualPos->numVerts;
		c_mesh->numvertsperframe = pActualPos->numVerts;
		c_mesh->numFrames = pActualPos->numFrames;
		c_mesh->numpolys = pActualPos->numTriangles;
		c_mesh->numTextCoordinates = pActualPos->numVerts;
		c_mesh->numofTextureLayer=1;


		if (c_mesh->numverts > MD3_MAX_VERTS)
			return MD3ErrorMaxVerts;


		//***** Shaders not yet implemented *****
//		if (c_mesh->numshaders > MD3_MAX_SHADERS)
//			return MD3ErrorMaxShaders;
		// Jump to the shaders in the file
//		MD3FileShader *fs = (MD3FileShader *) (pActualPos + pActualPos->ofsShaders);
		//***** Shaders not yet implemented *****

      
		//It's time to read the triangles coordinates
		if (c_mesh->numpolys > MD3_MAX_TRIANGLES)
			return MD3ErrorMaxTriangles;

		//First triangle Entry
		c_poly=c_mesh->polys;

		if (c_poly==NULL)
			{
			c_poly = c_mesh->polys = new o_poly[c_mesh->numpolys];
			memset(c_poly,0,(c_mesh->numpolys)*sizeof(o_poly));
			}


		// Jump to the triangles in the buffer
		TempPointer = ((byte *)(pActualPos)) + pActualPos->ofsTrianglesStart;
		MD3FileTriangle *ft = (MD3FileTriangle *) (TempPointer);

		// This loop converts the triangles in the md3 buffer into our o_poly structure.
		for (int t = 0; t < pActualPos->numTriangles; ++t)
			{
			c_poly[t].NumofVertex = 3;	//triangle
			c_poly[t].verts[0] = ft[t].indexes[2];
			c_poly[t].verts[1] = ft[t].indexes[1];
			c_poly[t].verts[2] = ft[t].indexes[0];
			}

		//Now we have to read and copy the vertex

		// Pointer to the vertex in the file
		TempPointer = ((byte *)(pActualPos)) + pActualPos->ofsVertexStart;
		MD3FileVertex *fv = (MD3FileVertex *) (TempPointer);
		// Pointer to the texture coordinates in the file
		TempPointer = ((byte *)(pActualPos)) + pActualPos->ofsTextureCoordStart;
		MD3FileTextureCoordinate *ftex = (MD3FileTextureCoordinate *) (TempPointer);

		// We have numVerts * numFrames since we need a vertex for each frame 
		// That the model has.  
		if (pActualPos->numVerts && pActualPos->numFrames)
			{
			c_mesh->numverts = pActualPos->numVerts * pActualPos->numFrames;
			c_mesh->verts = new o_vert3f[c_mesh->numverts];

			if (!c_mesh->verts)
				return MD3ErrorFatal;
			}

		// Texture coordinates never change!  So we only need numVerts texture
		// coordinates.
		if (c_mesh->numvertsperframe)
			{
			c_mesh->numTextCoordinates = c_mesh->numvertsperframe;
			c_mesh->mappingCoordinates[0] = new o_vert2f[c_mesh->numTextCoordinates];

			if (!c_mesh->mappingCoordinates)
				return MD3ErrorFatal;
			}

		// Read texture coordinates
		for (int uv = 0; uv < c_mesh->numvertsperframe; uv++)
			{
			c_mesh->mappingCoordinates[0][uv].u = ftex[uv].st[0];
			c_mesh->mappingCoordinates[0][uv].v = 1 - ftex[uv].st[1];
			}

		// This is a constant scale factor that is used to convert the md3
		// model verts from shorts to floats.
		const float MD3Scale = (1.0f / 64.0f);

		unsigned char *n = 0;

		// Convert the verts in the md3 buffer to our format
		for (int j = 0; j < c_mesh->numverts; ++j)
			{
			// Scale the verts by the scale factor to get them to floats
			c_mesh->verts[j].x = fv[j].xyz[0] * MD3Scale;
			c_mesh->verts[j].y = fv[j].xyz[1] * MD3Scale;
			c_mesh->verts[j].z = fv[j].xyz[2] * MD3Scale;

			//convert the normal from spherical to cartesian coordinates
			//No need to optimize in size
			n = (unsigned char *) &fv[j].normal;
			// Index into the normal table
//			surfaces[i].verts[j].norm.Set(norms[n[0]][n[1]]);
			}

      // Next mesh
	TempPointer = ((byte *)(pActualPos)) + pActualPos->ofsEnd;
	pActualPos = (MD3FileMesh *)TempPointer;
	}

return MD3ErrorNone;
}

/*
//====================================================================
// CalculateNormals
//	The normals in the md3 file are stored as 2 bytes, the first byte
// is longitude and the second is latitude.These are spherical
// coordinates, so we just convert them to the 3 float normals
// we normally use.
//
// Input:
//	byte *Buffer - A memory buffer that contain our file
//
// Output:
//	bool - true if everything is ok, false otherwise
//
//====================================================================

void CKIoMD3::CalculateNormals(void)
{
float longitude;
float latitude;

	for (int i = 0; i < 129; ++i)
		{
		longitude = (i / 255.0f) * (float) mLibTwoPi;

		for (int j = 0; j < 256; ++j)
			{
			latitude = (j / 255.0f) * (float) mLibTwoPi;
         
			norms[i][j].Set(
				(float) (cos(latitude) * sin(longitude)),
				(float) (sin(latitude) * sin(longitude)),
				(float) cos(longitude)
				);
			}
		}

normsCalc = 1;
}*/