//********************************************************************************
//
// module Name: IOAsc.CPP
//
// Description: Handle ASC file (3DS) for the Kapsul editor
//
//Creation: March 06th 2003 by GROUMF
//
//********************************************************************************

#include "stdafx.h"
#include <Kapsul3D.h>
#include "IOAsc.h"
#include "..\common\3DObjectStuff.h"

//--------------------------------------------------------------------
// ASC file format specific define
//--------------------------------------------------------------------
int ReadLine(char* lpDestStr, byte *Buffer);
void Line_Process_Ambient_Light(char *line,float *ambientR,float *ambientG,float *ambientB);
void Line_Process_Object_Name(char *line,char *ObjectName);
void Line_Process_Vertex(char *line,float *vptrX,float *vptrY,float *vptrZ);
void Line_Process_Tri_Mesh(char *line, int *NumVertices, int *Numfaces);
void Line_Process_Face(char *line,int *FaceNum,int *iA,int *iB,int *iC,int *iAB,int *iBC,int *iCA);
void Line_Process_Material(char *line,int *red, int *green, int *blue, int *alpha);
void Line_Process_Smoothing(char *line,int *SmoothValue);

//====================================================================
// Constructor / Destructor
//====================================================================

CKIoASC::CKIoASC()
{
	m_pObj = NULL;
}

CKIoASC::~CKIoASC()
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

CString CKIoASC::GetName()
{
	return "ASCII (3DS) I/O";
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

CString CKIoASC::GetInfos()
{
	return "ASCII (3DS) I/O";
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

CString CKIoASC::GetFilter()
{
	return "*.asc";
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

CString CKIoASC::GetFileDescription()
{
	return "ASCII Object (3DS)";
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

CString CKIoASC::GetFileExtension()
{
	return ".asc";
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

bool CKIoASC::SupportReading()
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

bool CKIoASC::SupportWriting()
{
	return true;
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

bool CKIoASC::Read(CKScene *pScene,CString FullFilePath)
{
	m_pScene = pScene;
	m_pMesh=NULL;
	curTexMatIndex = -1;
	CleanUp();

	m_Option = (CKOption*)GetGOption();	//To be used for texture path

	if (IsFormatValid(FullFilePath.GetBuffer(0)) == false)
		return false;

	return LoadASC(FullFilePath.GetBuffer(0));		
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
bool CKIoASC::Write(CKScene *pScene,CString FullFilePath)
{
	m_pScene = pScene;
	m_pMesh=NULL;
	curTexMatIndex = -1;
	CleanUp();

	return SaveASC(FullFilePath.GetBuffer(0)); //Did everything went right ?
}

//====================================================================
//--- IMPORTANT ---
// This func should be called to clean up before a new loading occurs
//====================================================================
//====================================================================
void CKIoASC::CleanUp()
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

bool CKIoASC::IsFormatValid(char* filename)
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
	fread(Buffer, 1,200,file);
	fclose(file);

	//Test to see if it's a real ASC file
	char *Test1 = strstr(Buffer,"Ambient");
	char *Test2 = strstr(Buffer,"Named");

	if ((Test1 == NULL) && (Test2 == NULL) )
		return false;
	else
		return true;
}

//=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
// This is now the specific part for the ASC object file format
//=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=

//====================================================================
// Load an object from an ASC file and fill the Kapsul scene with it
//
// Input:
//	char* filename - The full path name of the file
//
// Output:
//	bool - true if everything is ok, false otherwise
//
//====================================================================

bool CKIoASC::LoadASC( char* filename)
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
	
	//Open the file
	file = fopen(filename,"rb");
	if (!file)
		return false;

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
	ReadASCFile(memfile);

	//Delete file memory buffer
	delete memfile;

	//if we have no triangle or no points then return an error
	if ((m_pObj->nummeshes !=0) || (m_pObj->numverts!=0))
		{
		Compute3DObject_to_KapsulScene(m_pObj,m_pScene);
		}
	else
		{
		ReturnValue = false;
		}

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
// Save a Kapsul scene in a file
//
// Input:
//	char* filename - The full path name of the file to save
//
// Output:
//	bool - true if everything is ok, false otherwise
//
//====================================================================

bool CKIoASC::SaveASC( char* filename)
{

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
	

	//Compute the Kapsul scene to fit our needs
	ComputeKapsulScene_to_3DObject(m_pScene,m_pObj);

	//Save too asc file format
	WriteASCFile(filename);

	//Reset the object pointer
	if (m_pObj != NULL)
		{
		m_pObj->Delete();
		m_pObj = NULL;
		delete (m_pObj); 
		}


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

bool CKIoASC::ReadASCFile(char* buffer)
{
bool ReturnValue = true;
char StringBuffer[255];
int ReturnLineLength;
byte *pBuffer = (byte *)buffer;

long TotalSizeRead = 0;

float flt1,flt2,flt3;
int NumFace=0,SmoothValue,i1,i2,i3,i4,i5,i6;
char ObjectName[1023];

o_mesh *c_mesh=NULL;
o_poly *c_poly=NULL;
long NumberofFaceforActualMesh=0;
long NumberofVertexforActualMesh=0;

	for (;;)
		{
		if (TotalSizeRead >= m_lFileLenght-1)
			break;

		ReturnLineLength = ReadLine(&StringBuffer[0],pBuffer);
		pBuffer += ReturnLineLength;
		TotalSizeRead += ReturnLineLength;


		if (!strncmp(&StringBuffer[0], "Ambient light color", 19))
			{
			Line_Process_Ambient_Light(&StringBuffer[0],&flt1,&flt2,&flt3);
			}

		if (!strncmp(&StringBuffer[0], "Named object: ", 14))
			{
			Line_Process_Object_Name(&StringBuffer[0],&ObjectName[0]);
			}

//		if (!strncmp(&StringBuffer[0], "Vertex list", 11))
//			;
//		if (!strncmp(&StringBuffer[0], "Face list", 9))
//			;

		if (!strncmp(&StringBuffer[0], "Tri-mesh", 8))
			{
			Line_Process_Tri_Mesh(&StringBuffer[0],&i1,&i2);

			//We have a new object, so create a new mesh in our object

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

			//Allocate Vertex buffer and indice buffer
			if (c_mesh->numverts == NULL)
				{
				c_mesh->numverts = i1;
				c_mesh->verts	= new o_vert3f[c_mesh->numverts];
				}

			//First triangle Entry
			c_poly=c_mesh->polys;

			if (c_poly==NULL)
				{
				c_mesh->numpolys = i2;
				c_poly = c_mesh->polys = new o_poly[c_mesh->numpolys];
				memset(c_poly,0,(c_mesh->numpolys)*sizeof(o_poly));
				}

			NumberofFaceforActualMesh=0;
			NumberofVertexforActualMesh=0;
			}

		if (!strncmp(&StringBuffer[0], "Vertex ", 7))
			{
			if ((strncmp(&StringBuffer[0], "Vertex list", 11) != 0) && (strncmp(&StringBuffer[0], "Vertex List", 11) != 0))
				{
				Line_Process_Vertex(&StringBuffer[0],&flt1,&flt2,&flt3);
				if (NumberofVertexforActualMesh < c_mesh->numverts)
					{
					c_mesh->verts[NumberofVertexforActualMesh].x = flt1;
					c_mesh->verts[NumberofVertexforActualMesh].y = flt2;
					c_mesh->verts[NumberofVertexforActualMesh].z = flt3;
					}
				NumberofVertexforActualMesh++;
				}
			}

		if (!strncmp(&StringBuffer[0], "Face ", 5))
			{
			if ( (strncmp(&StringBuffer[0], "Face list", 9) != 0) && (strncmp(&StringBuffer[0], "Face List", 9) != 0))
				{
				Line_Process_Face(&StringBuffer[0],&NumFace,&i1,&i2,&i3,&i4,&i5,&i6);
				if (NumberofFaceforActualMesh < c_mesh->numpolys)
					{
					c_mesh->polys[NumberofFaceforActualMesh].NumofVertex = 3;
					c_mesh->polys[NumberofFaceforActualMesh].verts[0] = i1;
					c_mesh->polys[NumberofFaceforActualMesh].verts[1] = i2;
					c_mesh->polys[NumberofFaceforActualMesh].verts[2] = i3;
					}
				NumberofFaceforActualMesh++;
				}
			}

		if (!strncmp(&StringBuffer[0], "Material", 8))
			{
			Line_Process_Material(&StringBuffer[0],&i1,&i2,&i3,&i4);
			}

		if (!strncmp(&StringBuffer[0], "Smoothing", 9))
			{
			Line_Process_Smoothing(&StringBuffer[0],&SmoothValue);

			//A small test to see if we are near the end of the file
			//May cause a crash otherwise
			if (NumberofFaceforActualMesh >= c_mesh->numpolys)
				{
				if (TotalSizeRead >= m_lFileLenght-10)
					break;
				}
			}
 		}

return ReturnValue;
}

//====================================================================
// Save our 3D Object inside a ASC (3DS) file
//
// Input:
//	char* buffer - A memory buffer that contain our file
//
// Output:
//	bool - true if everything is ok, false otherwise
//
//====================================================================

bool CKIoASC::WriteASCFile(char* filename)
{
bool ReturnValue = true;
//char StringBuffer[255];
FILE *file;

o_mesh *c_mesh=NULL;
o_poly *c_poly=NULL;
long i=0,j=0,k=0;

	//Open the file (create it if needed)
	file = fopen(filename,"wb");
	if (!file)
		return FALSE;

	//The first lines
//	float *ambientR = 0.2f,*ambientG = 0.2f,*ambientB = 0.2f;
//	fprintf(file, "Ambient light color: Red=%f Green=%f Blue=%f\r\n", ambientR, ambientG, ambientB);
	fprintf(file, "Ambient light color: Red=%f Green=%f Blue=%f\r\n", 0.2f, 0.2f, 0.2f);
	fprintf(file, "\r\n");

	c_mesh = m_pObj->meshes;

	//Looping throught the meshes
	for (k=0;k<m_pObj->nummeshes;k++)
		{
		long NumberOfTriangles = 0;
		fprintf(file, "Named object: %c",char(34));
		fprintf(file, "Object_Name%d%c",k,char(34));
		fprintf(file, "\r\n");

		//First scan one time trought the array of polygones to see How many triangle we have
		for (j=0;j<c_mesh->numpolys;j++)
			{
			NumberOfTriangles += c_mesh->polys[j].NumofVertex - 2;
			}

//		fprintf(file, "Tri-mesh, Vertices: %d     Faces: %d\r\n",c_mesh->numverts,c_mesh->numpolys);
		fprintf(file, "Tri-mesh, Vertices: %d     Faces: %d\r\n",c_mesh->numverts,NumberOfTriangles);
		fprintf(file, "Vertex list\r\n");

		//Write vertex lines
		for (j=0;j<c_mesh->numverts;j++)
			{
			fprintf(file, "Vertex %d:  X:%f     Y:%f     Z:%f\r\n",j, c_mesh->verts[j].x, c_mesh->verts[j].y, c_mesh->verts[j].z);
			}

		fprintf(file, "Face list");
		fprintf(file, "\r\n");

		long StartIndice = 0;

		//Write faces lines
		for (j=0;j<c_mesh->numpolys;j++)
			{
			StartIndice = CreateTriangleFanFromPolygon(file,&c_mesh->polys[j],StartIndice);
			}

		c_mesh = c_mesh->next;
		}

	fclose(file);

return ReturnValue;
}

//====================================================================
// Create a triangleFan from a polygon and write it directly to the
// ASC file
//
// Input:
//	FILE *file - the file to write too
//	o_poly *p_poly - The polygonobject we have to compute
//	long StartFaceIndice - The strating indice of the triangles
//
// Output:
//	long - The final triangle indice
//
//====================================================================

long CKIoASC::CreateTriangleFanFromPolygon(FILE *file,o_poly *p_poly, long StartFaceIndice)
{
long i=0, j=0;

	for (j = 0; j < p_poly->NumofVertex - 2;j++)
		{
		//Faces lines
		fprintf(file, "Face %d:  A:%d B:%d C:%d AB:1 BC:1 CA:1\r\n", StartFaceIndice + j, p_poly->verts[0],p_poly->verts[j+1], p_poly->verts[j+2]);
		//Material Line
		fprintf(file, "Material:%c",char(34));	// char(34) is for the quote caracter
		fprintf(file, "r%dg%db%da%d%c",255,255,255,0,char(34));
		fprintf(file, "\r\n");
		//Smoothing line
		fprintf(file, "Smoothing:  %d\r\n",1);
		}

return StartFaceIndice + j;
}

//-----------------------------------------------------------------------------
// Read the next line of text from the filebuffer
// (after skipping all whitespace), place it into the given string,
// and return its length (not including null-terminator).
//
// Input:
//	char* lpDestStr - The returned string
//	char* buffer - A memory buffer that contain our file
//
// Output:
//	bool - true if everything is ok, false otherwise
//
//-----------------------------------------------------------------------------
int ReadLine(char* lpDestStr, byte *Buffer)
{
int initFilepos,Position = 0;
byte *pBuffer = Buffer;
byte c;

	// skip whitespace
	c = *(byte*)(pBuffer);
	while (c == 13 || c == 10 || c == 32 || c == 9 ) //looking for blank space/bakspace
		{
		Position++;
		c = *(byte*)(pBuffer+Position);
		}

	// copy the line
	initFilepos = Position;
	while ( c != 13 && c != 10 )	//looking for the end of line
		{
		*lpDestStr = c;
		Position++;
		lpDestStr++;
		c = *(byte*)(pBuffer+Position);
		}

	Position++;
	*lpDestStr = (BYTE)0;

//return Position - initFilepos;
return Position;
}
//-----------------------------------------------------------------------------
// Convert the ambient light line
//-----------------------------------------------------------------------------
void Line_Process_Ambient_Light(char *line,float *ambientR,float *ambientG,float *ambientB)
{
	sscanf(line, "Ambient light color: Red=%f Green=%f Blue=%f", ambientR, ambientG, ambientB);
}

//-----------------------------------------------------------------------------
// Convert the named object line
//-----------------------------------------------------------------------------
void Line_Process_Object_Name(char *line,char *ObjectName)
{
	sscanf(line, "Named object: %s", ObjectName);
}

//-----------------------------------------------------------------------------
// Convert a vertex line
//-----------------------------------------------------------------------------
void Line_Process_Vertex(char *line,float *vptrX,float *vptrY,float *vptrZ)
{
	sscanf(line, "Vertex %*d:  X:%f     Y:%f     Z:%f", vptrX, vptrY, vptrZ);
}

//-----------------------------------------------------------------------------
// Convert the tri-mesh line
//-----------------------------------------------------------------------------
void Line_Process_Tri_Mesh(char *line, int *NumVertices, int *Numfaces)
{
	sscanf(line, "Tri-mesh, Vertices: %d     Faces: %d", NumVertices, Numfaces);
}

//-----------------------------------------------------------------------------
// Convert a face line
//-----------------------------------------------------------------------------
void Line_Process_Face(char *line,int *FaceNum,int *iA,int *iB,int *iC,int *iAB,int *iBC,int *iCA)
{
	sscanf(line, "Face %d:    A:%d B:%d C:%d AB:%d BC:%d CA:%d", FaceNum, iA, iB, iC, iAB, iBC, iCA);
}

//-----------------------------------------------------------------------------
// Convert the material line
//-----------------------------------------------------------------------------
void Line_Process_Material(char *line,int *red, int *green, int *blue, int *alpha)
{
char Buffer[50];

	sscanf(line, "Material:%s", &Buffer[0]);
	
	// Delete first and last caracters (double quote) very dirty way
	long StringLength = strlen(&Buffer[0]);
	strncpy(&Buffer[0],&Buffer[1],StringLength - 2);
	Buffer[StringLength - 2] = 0;

	sscanf(&Buffer[0], "r%dg%db%da%d",red,green,blue,alpha);
}

//-----------------------------------------------------------------------------
// Convert a smooth line
//-----------------------------------------------------------------------------
void Line_Process_Smoothing(char *line,int *SmoothValue)
{
	sscanf(line, "Smoothing: %d", SmoothValue);
}