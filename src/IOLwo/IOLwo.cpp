//********************************************************************************
//
// module Name: IOLwo.CPP
//
// Description: Handle LWO file (Lightwave object) for the Kapsul editor
//
//Creation: March 04th 2003 by GROUMF
// Thanks too Antonio Lattanzio	(D3stY) for is LWO2 Loader Prototype
//
//
//********************************************************************************

#include "stdafx.h"
#include <Kapsul3D.h>
#include "IOLwo.h"
#include "..\common\3DObjectStuff.h"

// Specific Lightwave format definition
#define TYPE_UNKNOW	0
#define TYPE_LWOB	1
#define TYPE_LWO2	2

//Some Inverted Tags x IFF format
#define LWO_FORM 'MROF'	//FROM

#define LWO_LWOB 'BOWL'	//LWOB
#define LWO_LWO2 '2OWL'	//LWO2

#define LWO_TAGS 'SGAT'	//TAGS
#define LWO_LAYR 'RYAL'	//LAYR
#define LWO_PNTS 'STNP'	//PNTS
#define	LWO_POLS 'SLOP'	//POLS
#define	LWO_FACE 'ECAF'	//FACE
#define	LWO_VMAP 'PAMV'	//VMAP
#define	LWO_TXUV 'VUXT'	//TXUV
#define	LWO_SURF 'FRUS'	//SURF
#define LWO_WGHT 'THGW'	//WGHT
#define LWO_PTAG 'GATP'	//PTAG

//====================================================================
// Constructor / Destructor
//====================================================================

CKIoLWO::CKIoLWO()
{
	m_pObj = NULL;
	m_iLWOType = TYPE_UNKNOW;
}

CKIoLWO::~CKIoLWO()
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

CString CKIoLWO::GetName()
{
	return "Ligthwave I/O";
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

CString CKIoLWO::GetInfos()
{
	return "Ligthwave I/O";
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

CString CKIoLWO::GetFilter()
{
	return "*.lwo";
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

CString CKIoLWO::GetFileDescription()
{
	return "Ligthwave Object";
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

CString CKIoLWO::GetFileExtension()
{
	return ".lwo";
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

bool CKIoLWO::SupportReading()
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

bool CKIoLWO::SupportWriting()
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

bool CKIoLWO::Read(CKScene *pScene,CString FullFilePath)
{
	m_pScene = pScene;
	m_pMesh=NULL;
	curTexMatIndex = -1;
	CleanUp();

	m_Option = (CKOption*)GetGOption();	//To be used for texture path

	if (IsFormatValid(FullFilePath.GetBuffer(0)) == false)
		return false;

	return LoadLWO(FullFilePath.GetBuffer(0));		
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
bool CKIoLWO::Write(CKScene *pScene,CString FullFilePath)
{
	m_pScene = pScene;
	m_pMesh=NULL;
	curTexMatIndex = -1;
	CleanUp();

	return SaveLWO(FullFilePath.GetBuffer(0)); //Did everything went right ?
}

//====================================================================
//--- IMPORTANT ---
// This func should be called to clean up before a new loading occurs
//====================================================================
//====================================================================
void CKIoLWO::CleanUp()
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

bool CKIoLWO::IsFormatValid(char* filename)
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

	//Test to see if it's a real LWO file
	long chunkid = *(long*)(Buffer);
	long chunklength;

	invert4bytes( (char*)(Buffer+4), (char*)&chunklength );

	if ( chunkid == LWO_FORM)
		{
		int i = 8;
		chunklength = LoadFORMChunk(Buffer,chunklength,&i);
		if ( (m_iLWOType!=TYPE_LWOB) &&  (m_iLWOType!=TYPE_LWO2) )
			{
			return false;
			}
		return true;
		}

return false;
}

//=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
// This is now the specific part for the LWO object file format
//=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=

//====================================================================
// Load a Ligthwave object from file and fill the Kapsul scene with it
//
// Input:
//	char* filename - The full path name of the file
//
// Output:
//	bool - true if everything is ok, false otherwise
//
//====================================================================

bool CKIoLWO::LoadLWO( char* filename)
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


	// start recursive parsing
	GetChunk(memfile,m_pObj);

	//Delete file memory buffer
	delete memfile;

	//if we have no triangle or no points then return an error
	if (m_pObj->nummeshes==0||m_pObj->numverts==0)
		{
		ReturnValue = false;
		}

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
// Save a Kapsul scene in a file
//
// Input:
//	char* filename - The full path name of the file to save
//
// Output:
//	bool - true if everything is ok, false otherwise
//
//====================================================================

bool CKIoLWO::SaveLWO( char* filename)
{
	return TRUE;

}

//====================================================================
// Read chunks recursively
//
// Input:
//	char* buffer - A pointer to a memory buffer that contain the
//		entire file
//	
//	t_3Dobject *g_obj - The object in wich we are loading the 3D data
//
// Output:
//	long - Length of the chunk
//
//====================================================================

long CKIoLWO::GetChunk(char* buffer,t_3Dobject *g_obj)
{
long chunkid = *(long*)(buffer);
long chunklength;

	invert4bytes( (char*)(buffer+4), (char*)&chunklength );

	int i = 8;

	switch (chunkid)
		{
		case LWO_FORM:
			{
			chunklength = LoadFORMChunk(buffer,chunklength,&i);
			}
		break;

		case LWO_PNTS:	//get all points from that mesh
			{
			chunklength = LoadPNTSChunk(buffer,chunklength,&i);
			}
		break;
		
		case LWO_POLS:	//get all polys from that mesh
			{
			chunklength = LoadPOLSChunk(buffer,chunklength,&i);
			}
		break;

		case LWO_VMAP:
			{
			chunklength = LoadVMAPChunk(buffer,chunklength,&i);
			}
		break;


		case LWO_SURF:
			{
			chunklength = LoadSURFChunk(buffer,chunklength,&i);
			}
		break;

		case LWO_PTAG:
			{
			chunklength = LoadPTAGChunk(buffer,chunklength,&i);
			}
		break;


		default:
			i = chunklength;	// ignoring other chunks ... we can easly add more code here!
		break;
		}

	while (i < chunklength) i += GetChunk(buffer+i,g_obj)+8;
    
return chunklength;
}

//====================================================================
// Read FORM chunks (file type)
//
// Input:
//	char* buffer - The A pointer to a memory buffer that contain the
//		entire file
//	long ChunkLength - The length of the chunk
//	int *Indice - The actual position in the buffer (may be modified
// in this function)
//
// Output:
//	long - Length of the chunk
//
//====================================================================

long CKIoLWO::LoadFORMChunk(char* buffer,long ChunkLength,int *Indice)
{
char str[255];
int x=0;

	memset(str,0,255);
	while (x<4) {str[x]=buffer[(*Indice)++];x++;}

	if ( strcmp(str,"LWOB")==0 )
		m_iLWOType = TYPE_LWOB;

	if ( strcmp(str,"LWO2")==0 )
		m_iLWOType = TYPE_LWO2;

	if ( (m_iLWOType!=TYPE_LWOB) &&  (m_iLWOType!=TYPE_LWO2) )
		{
//		MessageBox(NULL,"This is not a Lightwave File Object","Sorry",MB_OK);
		*Indice=ChunkLength;
		}

return ChunkLength;
}

//====================================================================
// Read PNTS chunks - Points description
//
// Input:
//	char* buffer - The A pointer to a memory buffer that contain the
//		entire file
//	long ChunkLength - The length of the chunk
//	int *Indice - The actual position in the buffer (may be modified
// in this function)
//
// Output:
//	long - Length of the chunk
//
//====================================================================

long CKIoLWO::LoadPNTSChunk(char* buffer,long ChunkLength,int *Indice)
{
o_mesh *c_mesh=NULL;
int j;

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

	m_pActualMesh = c_mesh;

	if (c_mesh->numverts == NULL)
		{
		c_mesh->numverts = ChunkLength/12;
		c_mesh->verts	= new o_vert3f[c_mesh->numverts];
		for (j=0;j<c_mesh->numverts;j++)
			{
			invert4bytes( buffer+(*Indice), (char*)&c_mesh->verts[j].x );(*Indice) += 4;
			invert4bytes( buffer+(*Indice), (char*)&c_mesh->verts[j].y );(*Indice) += 4;
			invert4bytes( buffer+(*Indice), (char*)&c_mesh->verts[j].z );(*Indice) += 4;
			}
		m_pObj->numverts+=c_mesh->numverts;
		}
	else
		{
		*Indice = ChunkLength;
		}

return ChunkLength;
}

//====================================================================
// Read POLS chunks - Polygons description
//
// Input:
//	char* buffer - The A pointer to a memory buffer that contain the
//		entire file
//	long ChunkLength - The length of the chunk
//	int *Indice - The actual position in the buffer (may be modified
// in this function)
//
// Output:
//	long - Length of the chunk
//
//====================================================================

long CKIoLWO::LoadPOLSChunk(char* buffer,long ChunkLength,int *Indice)
{
//o_mesh *c_mesh=m_pObj->meshes;
o_mesh *c_mesh=m_pActualMesh;
o_poly *c_poly=c_mesh->polys;


	if (m_iLWOType == TYPE_LWO2)
		{
		if (*(long*)(buffer+(*Indice))==LWO_FACE)
			{
			byte *IntegerBuffer = (byte *)(buffer+(*Indice)+4);
			long i=0;
			long NumberofPolygons = ChunkLength/8;	//if there is only triangles (the maximum)
			
			do
				{
				int Value;

				//Read the number of vertex for this polygon
				ReadINTEGERfromBuffer(Value,IntegerBuffer);
				i += 2;

				Value &= 0x03FF;	//masking the 6 high order bits
				
				if (Value > MAX_NUMBER_OF_VERTEX_PER_POLY)
					{
					char str[255];
					sprintf(str," Polygon N° %d - Number of vertex = %d Max Number : %d\n",c_mesh->numpolys,Value,MAX_NUMBER_OF_VERTEX_PER_POLY);
					OutputDebugString(str);
					break;
					}

				c_mesh->numpolys++;

				//First triangle Entry
				if (c_poly==NULL)
					{
					c_poly = c_mesh->polys = new o_poly[NumberofPolygons];
					memset(c_poly,0,NumberofPolygons*sizeof(o_poly));
					}
				
				c_poly->NumofVertex = Value;

				//fill the vertex indice buffer
				for (int j=0; j < c_poly->NumofVertex; j++)
					{
					ReadINTEGERfromBuffer(Value,IntegerBuffer);
					i += 2;
					c_poly->verts[j] = Value;
					}


				//Set the surface indice
				c_poly->Surface = -1;
				c_poly++;
				}
			while (i < ChunkLength);

			c_mesh->numpolys--;	//last polygon seems to be "ugly"
			}
		}

	if (m_iLWOType == TYPE_LWOB)
		{
		byte *IntegerBuffer = (byte *)(buffer+(*Indice));
		long i=0;

		long NumberofPolygons = ChunkLength/10;	//if there is only triangles

		do
			{
			int Value;

			//Read the number of vertex for this polygon
			ReadINTEGERfromBuffer(Value,IntegerBuffer);
			i += 2;

			if (Value > MAX_NUMBER_OF_VERTEX_PER_POLY)
				{
				char str[255];
				sprintf(str," Polygon N° %d - Number of vertex = %d Max Number : %d\n",c_mesh->numpolys,Value,MAX_NUMBER_OF_VERTEX_PER_POLY);
				OutputDebugString(str);
				break;
				}

			c_mesh->numpolys++;

			//First triangle Entry
			if (c_poly==NULL)
				{
				c_poly = c_mesh->polys = new o_poly[NumberofPolygons];
				memset(c_poly,0,NumberofPolygons*sizeof(o_poly));
				}
				
			c_poly->NumofVertex = Value;

			//fill the vertex indice buffer
			for (int j=0; j < c_poly->NumofVertex; j++)
				{
				ReadINTEGERfromBuffer(Value,IntegerBuffer);
				i += 2;
				c_poly->verts[j] = Value;
				}

			//Read the surface indice
			ReadINTEGERfromBuffer(Value,IntegerBuffer);
			i += 2;
			c_poly->Surface = Value;
			c_poly++;
			}
		while (i < ChunkLength);
		}

	(*Indice) = ChunkLength;

return ChunkLength;
}

//====================================================================
// Read VMAP chunks - UV mapping coordinates description
//
// Input:
//	char* buffer - The A pointer to a memory buffer that contain the
//		entire file
//	long ChunkLength - The length of the chunk
//	int *Indice - The actual position in the buffer (may be modified
// in this function)
//
// Output:
//	long - Length of the chunk
//
//====================================================================

long CKIoLWO::LoadVMAPChunk(char* buffer,long ChunkLength,int *Indice)
{
o_uvmap	*c_uvmap=m_pObj->uvmap;
o_wmap	*c_wmap=m_pObj->wmap;

int j = 0;
UINT vmode = *(long*)(buffer+(*Indice));


	if ( vmode==LWO_TXUV||vmode==LWO_WGHT )
		{
		j+=4;
		short entries = *(char*)(buffer+(*Indice)+j+1) + (*(char*)(buffer+(*Indice)+j)<<8);
		j+=2;
		UINT strlen=0;
		while (buffer[(*Indice)+j]!=0) {j++;strlen++;}
		if (strlen%2!=0) j++;else j+=2;

		int tot = (ChunkLength-j)/(entries*4+2);
		int vnum=0;

		if (vmode==LWO_TXUV)
			{
			if (m_pObj->uvmap==NULL)
				{
				c_uvmap = m_pObj->uvmap = new o_uvmap;
				memset(c_uvmap,0,sizeof(o_uvmap));
				m_pObj->numuvmaps++;
				}
			else
				{
				o_uvmap *tuv=m_pObj->uvmap;
				while (tuv->next) tuv=tuv->next;
				c_uvmap = new o_uvmap;
				memset(c_uvmap,0,sizeof(o_uvmap));
				tuv->next = c_uvmap;
				tuv->next->prev = tuv;
				m_pObj->numuvmaps++;
				}

			c_uvmap->name = new char[strlen+1];
			strcpy(c_uvmap->name,buffer+(*Indice)+6);
			c_uvmap->u = new float[tot];
			c_uvmap->v = new float[tot];
			c_uvmap->index = new UINT[tot];

			while (j<ChunkLength)
				{
				float u=0,v=0;
				BYTE v1 = *(char*)(buffer+(*Indice)+j+1);
				BYTE v2 = *(char*)(buffer+(*Indice)+j);

				unsigned short vert = v1+v2*0xff;j+=2;//*(char*)(buffer+i+j+1) + (*(char*)(buffer+i+j)<<8);j+=2;
				invert4bytes( buffer+(*Indice)+j, (char*)&u );j+=4;
				invert4bytes( buffer+(*Indice)+j, (char*)&v );j+=4;

				c_uvmap->u[vnum] = u;
				c_uvmap->v[vnum] = v;
				c_uvmap->index[vnum] = vert;
				vnum++;
				}
			}
		else
			{
			if (vmode==LWO_WGHT)
				{
				if (m_pObj->wmap==NULL)
					{
					c_wmap = m_pObj->wmap = new o_wmap;
					memset(c_wmap,0,sizeof(o_wmap));
					m_pObj->numwmaps++;
					}
				else
					{
					o_wmap *tw=m_pObj->wmap;
					while (tw->next) tw=tw->next;
					c_wmap = new o_wmap;
					memset(c_wmap,0,sizeof(o_wmap));
					tw->next = c_wmap;
					tw->next->prev = tw;
					m_pObj->numwmaps++;
					}

				c_wmap->name = new char[strlen+1];
				strcpy(c_wmap->name,buffer+(*Indice)+6);
				c_wmap->w = new float[tot];
				c_wmap->index = new UINT[tot];

				while (j<ChunkLength)
					{
					float power=0;
					BYTE v1 = *(char*)(buffer+(*Indice)+j+1);
					BYTE v2 = *(char*)(buffer+(*Indice)+j);
					unsigned short vert = v1+v2*0xff;j+=2;
					invert4bytes( buffer+(*Indice)+j, (char*)&power );j+=4;

					c_wmap->w[vnum] = power;
					c_wmap->index[vnum] = vert;
					vnum++;
					}
				}
			}
		}

			(*Indice) = ChunkLength;

return ChunkLength;
}

//====================================================================
// Read SURF chunks - UV mapping coordinates description
//
// Input:
//	char* buffer - The A pointer to a memory buffer that contain the
//		entire file
//	long ChunkLength - The length of the chunk
//	int *Indice - The actual position in the buffer (may be modified
// in this function)
//
// Output:
//	long - Length of the chunk
//
//====================================================================

long CKIoLWO::LoadSURFChunk(char* buffer,long ChunkLength,int *Indice)
{
o_surf	*c_surf=m_pObj->surf;
UINT j=0;
UINT strlen=0;

	while (buffer[(*Indice)+j]!=0)
		{
		j++;
		strlen++;
		}
		
	if (strlen%2!=0)
		j++;
	else
		j+=2;

	if (m_pObj->surf==NULL)
		{
		c_surf = m_pObj->surf = new o_surf;
		memset(c_surf,0,sizeof(o_surf));
		m_pObj->numsurfs++;
		}
	else
		{
		o_surf *ts=m_pObj->surf;
		while (ts->next) ts=ts->next;
		c_surf = new o_surf;
		memset(c_surf,0,sizeof(o_surf));
		ts->next = c_surf;
		ts->next->prev = ts;
		m_pObj->numsurfs++;
		}

	c_surf->name = new char[strlen+1];
	strcpy(c_surf->name,buffer+(*Indice));

	(*Indice) = ChunkLength;

return ChunkLength;
}

//====================================================================
// Read PTAG chunks -texture index description
//
// Input:
//	char* buffer - The A pointer to a memory buffer that contain the
//		entire file
//	long ChunkLength - The length of the chunk
//	int *Indice - The actual position in the buffer (may be modified
// in this function)
//
// Output:
//	long - Length of the chunk
//
//====================================================================

long CKIoLWO::LoadPTAGChunk(char* buffer,long ChunkLength,int *Indice)
{
min_plist	*c_plist=m_pObj->plist;
int j=4;
UINT vmode = *(long*)(buffer+(*Indice));

	if (vmode==LWO_SURF)
		{
		UINT plnum = (ChunkLength-4)/4;

		if (m_pObj->plist==NULL)
			{
			c_plist = m_pObj->plist = new min_plist;
			memset(c_plist,0,sizeof(min_plist));
			m_pObj->numplists++;
			}
		else
			{
			min_plist *tpl=m_pObj->plist;
			while (tpl->next) tpl=tpl->next;
			
			c_plist = new min_plist;
			memset(c_plist,0,sizeof(min_plist));
			tpl->next = c_plist;
			tpl->next->prev = tpl;
			m_pObj->numplists++;
			}

		c_plist->list = new UINT[plnum];

		UINT vnum=0;
		while (j<ChunkLength)
			{
			short val = (short)(((BYTE)buffer[(*Indice)+j])+(BYTE)buffer[(*Indice)+j+1]);j+=2;
			short sur = (short)(((BYTE)buffer[(*Indice)+j])+(BYTE)buffer[(*Indice)+j+1]);j+=2;

			//invert4bytes( buffer+i+j, (char*)&val );j+=4;
					
			c_plist->list[vnum++] = val;
			}

		}

	(*Indice) = ChunkLength;

return ChunkLength;
}

