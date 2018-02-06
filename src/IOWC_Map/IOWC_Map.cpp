/*

	IOWC_Map.CPP
	Conversion Notes:
		- Every brush bind to WorldSpawn entity shouldnt be bind to an entity in Kapsul
		- Every brush bind to any entity except WorldSpawn should be bind to an entity in kapsul

    ToDo: - Texture rotation? CTexture/KPoly doesnt support it
		  - Say "You_are_my_master" to griz
		  - lacrapul's Vertex or CV3 should be used? (Vertex used as a vector in Polygon/Normale)
		    CV3 should be defined/typedef as 'Vertex'
*/

#include "stdafx.h"
#include <stdio.h>
#include "BrushConverter.h"
#include "IOWC_Map.h"



static char *szExtArray[] = 
{ 
 ".jpg",".png",".tif",".bmp"
};

static char toSkip[] = " \t\n\"";
static bool bInitialized = false;   
static char *pToken = NULL;

static CBrushConverter * pConverter = new CBrushConverter();





CKIOWC_Map::CKIOWC_Map()
{
}
CKIOWC_Map::~CKIOWC_Map()
{
}

CString CKIOWC_Map::GetName()
{
	return "WorldCraft map I/O";
}
CString CKIOWC_Map::GetInfos()
{
	return "WorldCraft map I/O";
}
CString CKIOWC_Map::GetFilter()
{
	return "*.map";
}
CString CKIOWC_Map::GetFileDescription()
{
	return "WorldCraft map";
}
CString CKIOWC_Map::GetFileExtension()
{
	return ".map";
}
bool CKIOWC_Map::SupportReading()
{
	return 1;
}
bool CKIOWC_Map::SupportWriting()
{
	return 1;
}
bool CKIOWC_Map::Read(CKScene *pScene,CString FullFilePath)
{
	m_Scene = pScene;

	return LoadFile(FullFilePath.GetBuffer(0)); 
}

bool CKIOWC_Map::Write(CKScene *pScene,CString FullFilePath)
{
	m_Scene = pScene;

	return SaveFile(FullFilePath.GetBuffer(0)); //Did everything went right ?
}

/*
    My Functions
*/

void CKIOWC_Map::CreatePlaneByPoly(SFACE *face, CKMesh *obj, int poly_num)
{
	face->vPlanePts[0].x=obj->pv[obj->pl[poly_num].nbvert[0]].x;
	face->vPlanePts[0].y=obj->pv[obj->pl[poly_num].nbvert[0]].y;
	face->vPlanePts[0].z=obj->pv[obj->pl[poly_num].nbvert[0]].z;

	face->vPlanePts[1].x=obj->pv[obj->pl[poly_num].nbvert[1]].x;
	face->vPlanePts[1].y=obj->pv[obj->pl[poly_num].nbvert[1]].y;
	face->vPlanePts[1].z=obj->pv[obj->pl[poly_num].nbvert[1]].z;

	face->vPlanePts[2].x=obj->pv[obj->pl[poly_num].nbvert[2]].x;
	face->vPlanePts[2].y=obj->pv[obj->pl[poly_num].nbvert[2]].y;
	face->vPlanePts[2].z=obj->pv[obj->pl[poly_num].nbvert[2]].z;

	pConverter->Face_BuildPlane(face);
}

BOOL CKIOWC_Map::AreFacePlanesEqual(SFACE *plane1, SFACE *plane2)
{
	if (plane1->sFacePlane.fDist==plane2->sFacePlane.fDist && plane1->sFacePlane.vNormal==plane2->sFacePlane.vNormal)
		return TRUE;
	return FALSE;
}

#define CURRENT_POLY obj->pl[i]

#define POLY_VERTEX(which_vertex, xyz) /*(long)*/obj->pv[CURRENT_POLY.nbvert[which_vertex]].xyz
#define POLY_VERTU(which_vertex) obj->puv[0][CURRENT_POLY.nbvert[which_vertex]].u
#define POLY_VERTV(which_vertex) obj->puv[0][CURRENT_POLY.nbvert[which_vertex]].v

void CKIOWC_Map::WriteObject(CKMesh *obj, FILE *f, int objnum)
{
	int i,j;
	SPLANE current,temp;
	CV3 vPointsOnPlane[3];

	SFACE *planes=new SFACE[obj->nb2poly];

	//glog->Printf("\t==== Processing object 0x%08x... ====\n",obj);

	//glog->Printf("\t==== CreatePlaneByPoly (nb2poly==%d)... ====\n",obj->nb2poly);

	for (i=0;i<obj->nb2poly;i++)
		CreatePlaneByPoly(&planes[i], obj, i);

	for (i=0;i<obj->nb2poly;i++)
		{
			//glog->Printf("\t\t==== Processing poly %d... ====\n",i);

			if (obj->pl[i].nb2vert<3)
			{
				//glog->Printf("WriteObject(): ERROR: poly has less than 3 vertices\n");
				continue;
			}

			char *s, *TexName=NULL, temp[MAX_PATH];

			if (obj->pl[i].Maps[0])
			{
				strcpy(temp,obj->pl[i].Maps[0]->FileName);
				s=temp;
				//glog->Printf("Original filename==%s\n",s);
				s+=strlen(s)-1;
				while (s>obj->pl[i].Maps[0]->FileName)
				{
					--s;
					if (*s=='\\' || *s=='/')
					{
						++s;
						break;
					}
				}

				TexName=new char[strlen(s)+1]; // +1 for \0

				strcpy(TexName,s);

				//glog->Printf("TexName==%s\n", TexName);

				s=TexName+strlen(s)-1;
				while (s>TexName)
				{
					--s;
					if (*s=='.')
					{
						*s=NULL;
						break;
					}
				}

				//glog->Printf("UjTexName==%s\n", TexName);
			}

			CV3 v[3], tempvec[3], tempvec2[3], axisU, axisV;
			float uv[3];
			
			v[0].x=POLY_VERTEX(0,x);v[0].y=POLY_VERTEX(0,y);v[0].z=POLY_VERTEX(0,z);
			v[1].x=POLY_VERTEX(1,x);v[1].y=POLY_VERTEX(1,y);v[1].z=POLY_VERTEX(1,z);
			v[2].x=POLY_VERTEX(2,x);v[2].y=POLY_VERTEX(2,y);v[2].z=POLY_VERTEX(2,z);

			// Calculating Us

			float change[2], dist; // dist: distance between line1<-->line2 ( they are parallel and not equal, so != 0 )
			CV3 vch[2], // each 'vch[x]' causes 'change[x]' amount change in U/V
				line1[2], line2[2]; // line1: where u/v==uv[0] line2: where u/v==uv[0]+1

			//glog->Printf2("\n*****************************************************\n\n***************\n\tUj U szamolas\n***************\n");
#define ABS(x) ((x)>=0)?(x):(-(x))
			uv[0]=POLY_VERTU(0);uv[1]=POLY_VERTU(1);uv[2]=POLY_VERTU(2);
			tempvec[0]=v[0];tempvec[1]=v[1];tempvec[2]=v[2]; // kesobb tempvec[]/uv[] -ben ne legyen egyezo U v V!!

			//glog->Printf("tempvec[0]=(%f %f %f)  \tU: %f\n", tempvec[0].x, tempvec[0].y, tempvec[0].z, uv[0]);
			//glog->Printf("tempvec[1]=(%f %f %f)  \tU: %f\n", tempvec[1].x, tempvec[1].y, tempvec[1].z, uv[1]);
			//glog->Printf("tempvec[2]=(%f %f %f)  \tU: %f\n", tempvec[2].x, tempvec[2].y, tempvec[2].z, uv[2]);
			//glog->Printf("\n");
			//glog->Printf("\nuv[0]-uv[1] == %f\nuv[0]-uv[2] == %f\nuv[1]-uv[2] == %f\n", ABS(uv[0]-uv[1]),ABS(uv[0]-uv[2]),ABS(uv[1]-uv[2]));
			if ((ABS(uv[0]-uv[1]))<0.001f)
			{
				line1[0]=tempvec[0];
				//glog->Printf("0 es 1 = ABS( %f - %f )==%f < 0.001f\n", uv[0],uv[1],ABS(uv[0]-uv[1]));
				line1[1]=tempvec[1];
			}
			else if ((ABS(uv[0]-uv[2]))<0.001f)
			{
				line1[0]=tempvec[0];
				//glog->Printf("0 es 2 =\n");
				line1[1]=tempvec[2];
			}
			else if ((ABS(uv[1]-uv[2]))<0.001f)
			{
				//glog->Printf("2 es 1 =\n");
				line1[0]=tempvec[2];
				line1[1]=tempvec[1];
			}
			else
			{
				vch[0]=tempvec[1]-tempvec[0];	// VCH[0] = tempvec[0]-->tempvec[1]
				change[0]=uv[1]-uv[0];

				vch[1]=tempvec[2]-tempvec[0];	// VCH[1] = tempvec[0]-->tempvec[2]
				change[1]=uv[2]-uv[0];

				//glog->Printf("vch[0]=(%f %f %f) change[0]=%f\n",vch[0].x,vch[0].y,vch[0].z,change[0]);
				//glog->Printf("vch[1]=(%f %f %f) change[1]=%f\n",vch[1].x,vch[1].y,vch[1].z,change[1]);
				//glog->Printf("\n");

				if (change[0]>0.01f || change[0]<-0.01f)
				{
					//glog->Printf("Line: change[0] megfelelo meretu\n");
					//glog->Printf("\tline1=tempvec1(%f %f %f), line0=tempvec0+vch[1](%f %f %f)*((%f / change[0] ))\n", tempvec[1].x, tempvec[1].y, tempvec[1].z, vch[1].x, vch[1].y, vch[1].z, uv[2]-uv[0]);
					line1[0]=tempvec[0]+vch[1]*((uv[1]-uv[0])/change[1]);
					line1[1]=tempvec[1];
					//glog->Printf("line1[0]==%f %f %f tempvec[0]==%f %f %f line1[1]==%f %f %f tempvec[1]== %f %f %f \n",line1[0].x,line1[0].y,line1[0].z,tempvec[0].x,tempvec[0].y,tempvec[0].z,line1[1].x,line1[1].y,line1[1].z,tempvec[1].x,tempvec[1].y,tempvec[1].z);
				}
				else if (change[1]>0.01f || change [1] < -0.01f)
				{
					//glog->Printf("Line: change[1] megfelelo meretu\n");
					//glog->Printf("\tline0=tempvec0(%f %f %f), line1=tempvec1+vch[1](%f %f %f)*((%f / change[1] ))\n", tempvec[0].x, tempvec[0].y, tempvec[0].z, vch[1].x, vch[1].y, vch[1].z, uv[0]-uv[1]);
					line1[1]=tempvec[1]+vch[1]*((uv[0]-uv[1])/change[1]);
					line1[0]=tempvec[0];
				}
				else {
					//glog->Printf("*** tulkicsi a change: change0 = %f change1 = %f", change[0], change[1]);

					line1[1]=tempvec[1];
					line1[0]=tempvec[0];
				}
			}

			//glog->Printf("line1: ( %f %f %f ) -- ( %f %f %f)\n", line1[0].x, line1[0].y, line1[0].z, line1[1].x, line1[1].y, line1[1].z);
			tempvec2[0].VectorCross(line1[0]-line1[1], planes[i].sFacePlane.vNormal, axisU);
			axisU=axisU.Normalize();

			//glog->Printf("******** ---> AxisU == ( %f %f %f )\n", axisU.x, axisU.y, axisU.z);

			uv[0]=POLY_VERTV(0);uv[1]=POLY_VERTV(1);uv[2]=POLY_VERTV(2);

			//glog->Printf2("***************\n\tUj V szamolas\n***************\n");
			//glog->Printf("tempvec[0]=(%f %f %f)\t  V: %f\n", tempvec[0].x, tempvec[0].y, tempvec[0].z, uv[0]);
			//glog->Printf("tempvec[1]=(%f %f %f)\t  V: %f\n", tempvec[1].x, tempvec[1].y, tempvec[1].z, uv[1]);
			//glog->Printf("tempvec[2]=(%f %f %f)\t  V: %f\n", tempvec[2].x, tempvec[2].y, tempvec[2].z, uv[2]);
			//glog->Printf("\n");

			//glog->Printf("\nuv[0]-uv[1] == %f\nuv[0]-uv[2] == %f\nuv[1]-uv[2] == %f\n", ABS(uv[0]-uv[1]),ABS(uv[0]-uv[2]),ABS(uv[1]-uv[2]));

			if ((ABS(uv[0]-uv[1]))<0.001f)
			{
				//glog->Printf("0 es 1 =\n");
				line1[0]=tempvec[0];
				line1[1]=tempvec[1];
			}
			else if ((ABS(uv[0]-uv[2]))<0.001f)
			{
				//glog->Printf("0 es 2 =\n");
				line1[0]=tempvec[0];
				line1[1]=tempvec[2];
			}
			else if ((ABS(uv[1]-uv[2]))<0.001f)
			{
				//glog->Printf("1 es 2 =\n");
				line1[0]=tempvec[2];
				line1[1]=tempvec[1];
			}
			else
			{
				vch[0]=tempvec[1]-tempvec[0];	// VCH[0] = tempvec[0]-->tempvec[1]
				change[0]=uv[1]-uv[0];

				vch[1]=tempvec[2]-tempvec[1];	// VCH[1] = tempvec[0]-->tempvec[2]
				change[1]=uv[2]-uv[0];
				
				//glog->Printf("vch[0]=(%f %f %f) change[0]=%f\n",vch[0].x,vch[0].y,vch[0].z,change[0]);
				//glog->Printf("vch[1]=(%f %f %f) change[1]=%f\n",vch[1].x,vch[1].y,vch[1].z,change[1]);
				//glog->Printf("\n");

				line1[0]=tempvec[0];
				line1[1]=tempvec[1]+vch[1]*((uv[1]-uv[0])/change[1]);
			}

			tempvec2[0].VectorCross(line1[0]-line1[1], planes[i].sFacePlane.vNormal, axisV);
			axisV=axisV.Normalize();

			//glog->Printf("line1: ( %f %f %f ) -- ( %f %f %f)\n", line1[0].x, line1[0].y, line1[0].z, line1[1].x, line1[1].y, line1[1].z);
			//glog->Printf("******** ---> axisV: ( %f %f %f )\n", axisV.x, axisV.y, axisV.z);
			// dunno

			tempvec[0]=v[0]-v[1];
			tempvec[0]*=10.0f;

			v[1]+=tempvec[0];

			if (!strcmp(TexName, "DefaultTexture")) strcpy(TexName, "BLACK");

			fprintf(f,"( %ld %ld %ld ) ( %ld %ld %ld ) ( %ld %ld %ld ) %s [ %f %f %f 0 ] [ %f %f %f 0 ] 0 1 1\n",
						(long)v[0].x, (long)v[0].y, (long)v[0].z,
						(long)v[1].x, (long)v[1].y, (long)v[1].z,
						(long)v[2].x, (long)v[2].y, (long)v[2].z,
						(TexName)?TexName:"BLACK",axisU.x, axisU.y, axisU.z, axisV.x, axisV.y, axisV.z);

			if (TexName) delete[]TexName;
		}
	delete[] planes;
}

BOOL CKIOWC_Map::IsMap(char *szBuffer)
{
 if(strstr(szBuffer,"mapversion"))
	 return TRUE;

 return FALSE;
}

/*
 Parser
*/
char *CKIOWC_Map::GetToken(char *m_pData)
{
 if(!m_pData)
 {
	 //AfxMessageBox("GetToken() failed.");
	 return NULL;
 }

 if(bInitialized == FALSE)
 {
	pToken = strtok(m_pData,toSkip);
	bInitialized = TRUE;
 }
 else
	pToken = strtok(NULL,toSkip);

 return pToken;
}

bool CKIOWC_Map::LoadWcBrush(char *m_pData)
{
 /*
	That's how a brush is stored in .map file:

	{
	 ( x y z ) ( x y z ) ( x y z ) TEXTURE*TEX [ 0 0 0 0 ] [ 0 0 0 0 ] 0 0 0
	 [...]
	}

	where each line represents a brush face. ( x y z ) is a point that makes
	the face, we have to write 3 points and compute the fourth on loading. After
	it comes texture name, position x,y and rotation,scaling. so:
 */

 m_Option = (CKOption*)GetGOption();

 CBrushConverter::CBrushRaw *pBrush = NULL;
 char  *pToken = NULL;
 SFACE *pFaces = NULL, *pTemp=NULL;
 int   iNumFaces = 0;
 int iCurStep=0;

 do
 {
  pToken = GetToken(m_pData);
  if(!pToken)
	  break;

  if(strcmp(pToken,"}") == 0)
		break;

  // read 3 points for each plane on which face lays on

  for (int i=0;i<3;i++)
  {
	  if (!strcmp(pToken,"("))
	  { // new face
		  if (!i) // needs to be done before first point
		  {
			  if (!(iNumFaces%ALLOC_STEP)) // new allocation needed
			  {
				  pTemp=pFaces;
				  pFaces=new SFACE[iCurStep+=ALLOC_STEP];
				  if (pTemp)
				  {
					  memcpy(pFaces,pTemp,sizeof(SFACE)*iNumFaces);
					  delete[]pTemp;
				  }
			  }

			  pFaces[iNumFaces].sFaceWinding=NULL;
		  }

		  pFaces[iNumFaces].vPlanePts[i].x = (float)atof(GetToken(m_pData));
		  pFaces[iNumFaces].vPlanePts[i].y = (float)atof(GetToken(m_pData));
		  pFaces[iNumFaces].vPlanePts[i].z = (float)atof(GetToken(m_pData));
		  pToken = GetToken(m_pData);
	      if(strcmp(pToken,")") != 0)
		  {
			  //MessageBox(NULL,"LoadWcBrush found a missing ')' in map file! Brush not loaded.","iowc_map.dll",MB_OK);
			  delete [] pFaces;
			  return false;
		  }
	  }
	  else
	  {
		  delete[]pFaces;
		  return false;
	  }

	  pToken=GetToken(m_pData);
  }

  // We read texture name
  pFaces[iNumFaces].sFaceTexture.Name = pToken;

  pToken = GetToken(m_pData);
  if(strcmp(pToken,"[") == 0)
  {
   pFaces[iNumFaces].vAxisU.x=atof(GetToken(m_pData));
   pFaces[iNumFaces].vAxisU.y=atof(GetToken(m_pData));
   pFaces[iNumFaces].vAxisU.z=atof(GetToken(m_pData));
   pFaces[iNumFaces].sFaceTexture.Shift[0]=atof(GetToken(m_pData));

	 	
   pToken = GetToken(m_pData);
   if(strcmp(pToken,"]") != 0)
   {
	//MessageBox(NULL,"LoadWcBrush found a missing ']' in map file! Brush not loaded.","iowc_map.dll",MB_OK);
	delete [] pFaces;
	return false;
   }
  }else
  {
   delete [] pFaces;
   return false;
  }

  pToken = GetToken(m_pData);
  if(strcmp(pToken,"[") == 0)
  {
   pFaces[iNumFaces].vAxisV.x=atof(GetToken(m_pData));
   pFaces[iNumFaces].vAxisV.y=atof(GetToken(m_pData));
   pFaces[iNumFaces].vAxisV.z=atof(GetToken(m_pData));
   pFaces[iNumFaces].sFaceTexture.Shift[1]=atof(GetToken(m_pData));
	 	
   pToken = GetToken(m_pData);
   if(strcmp(pToken,"]") != 0)
   {
    //MessageBox(NULL,"LoadWcBrush found a missing ']' in map file! Brush not loaded.","iowc_map.dll",MB_OK);
    delete [] pFaces;
    return false;
   }
  }else
  {
   delete [] pFaces;
   return false;
  }

  // We init texture rotation, hscale and vscale
  pFaces[iNumFaces].sFaceTexture.Rotate	  = (float)atof(GetToken(m_pData));
  pFaces[iNumFaces].sFaceTexture.Scale[0] = (float)atof(GetToken(m_pData));
  pFaces[iNumFaces].sFaceTexture.Scale[1] = (float)atof(GetToken(m_pData));

  ++iNumFaces;
 }
 while(1);

 if (iNumFaces%ALLOC_STEP)
 {
	 pTemp=new SFACE[iNumFaces];
	 memcpy(pTemp, pFaces, sizeof(SFACE)*iNumFaces);
	 delete pFaces;
	 pFaces=pTemp;
 }

 pBrush = new CBrushConverter::CBrushRaw();
 pBrush->s_Faces  = pFaces;
 pBrush->m_nFaces = iNumFaces;

 //glog->Printf("Processing Object %d...\n", objcount++);

 pConverter->m_nLoadedBrushes++;
 pConverter->Brush_BuildWinding(pBrush);

 return pConverter->Desk_Import(m_Scene,pBrush);
}

bool CKIOWC_Map::LoadWcEntity(char *m_pData)
{
  /*
	That's how an entity is stored in the .map file:
	{
	 "classname" "entity_class_name"
	 [...] Options
	 {
	 (brush face)
	 }
	}

	so ,for saving:
	-> we first open brackets 
	-> we write the classname 
	-> we write options
	-> we write brushes (if it's a solid entity)
	-> we close entity bracket
 */

 char	 * pToken  = NULL;
 CKEntity * pEntity = NULL;
 CString   szEntityName;

 pToken = GetToken(m_pData);
 if(!pToken)
	 return false;

 if(strcmp(pToken,"{") != 0)
	 return false;


 do
 {
  pToken = GetToken(m_pData);
  if(!pToken)
  {
   //MessageBox(NULL,"LoadWcEntity couldn't find next token in entity definition. Map file is probably damaged","iowc_map.dll",MB_OK);
   return false;
  }

  if(strcmp(pToken,"}") == 0)
		break;

  if(strcmp(pToken,"{") == 0)
  {
   if(LoadWcBrush(m_pData))
   {
	// We found a valid brush
   }else
	 break;
  }else
  {
   if(strstr(pToken,"classname"))
   {
    // We set entity class name and create an instance of entity here.
	// as it is called once on entity load before brushes so we can 
	// differentiate worldspawn brushes from others

	if (!strstr(pToken,"worldspawn"))
		ALLOC_STEP=64; 
	else ALLOC_STEP=4;

    szEntityName = GetToken(m_pData);
    //pEntity = new CEntity(m_Scene,NULL,NULL,szEntityName);

	pConverter->m_nProcessedEntities++;
   }else if(strstr(pToken,"mapversion"))
   {
    GetToken(m_pData);
	continue;
   }else
   {
	// Read properties
    GetToken(m_pData); //propdata
   }
  }
 }
 while(1);


 return true;
}

void CKIOWC_Map::LoadWcMap(char *pBuf)
{
 while(1)
 {
  if(!LoadWcEntity(pBuf))
	  break;
 }

 //pConverter->PrintStatistics(); // annoying for me - uncomment if you like it (griz)
}

bool CKIOWC_Map::SaveFile(char *fname)
{
	FILE *f=fopen(fname, "wt");
	int objnum=0;

	//glog->Printf2("\n\t**** Saving world to file %s ****\n\n", fname);

	CKMesh *obj=m_Scene->FirstMesh;

	fputs("{\n\"classname\" \"worldspawn\"\n\"mapversion\" \"220\"\n",f);

	while (obj)
	{
		//glog->Printf("Processing object %d...\n", objnum);
		fputs("{\n",f);

		WriteObject(obj, f, objnum++);

		obj=obj->Next;
		fputs("}\n",f);
	}

	fputs("}\n",f);

	fclose(f);

	//glog->Printf2("\n\t**** Saving completed ****\n\n");
	return true;
}

/*
 Main load function
*/ 
bool CKIOWC_Map::LoadFile(char *FileName)
{
 FILE *fFile = fopen(FileName,"rt");

 //glog->Printf2("\n\t**** Loading world from file %s ****\n\n", FileName);

 objcount=0;

 if(fFile)
 {
  // If we loaded multiple maps, then we reset our internal shit
  pConverter->m_nLoadedBrushes = pConverter->m_nProcessedBrushes = pConverter->m_nProcessedEntities = 0;
  bInitialized = FALSE;

  int iStart = 0,iEnd = 0;
  iStart  = ftell (fFile);
  fseek (fFile, 0, SEEK_END);
  iEnd = ftell (fFile);
  fseek (fFile, iStart, SEEK_SET);

  char * pBuff = new char[iEnd+1];
  ((char*)pBuff)[iEnd] = 0;
  if(!pBuff)
  {
	return false;
  }

  // We read our text buffer ready to be parsed
  fread(pBuff,1,iEnd,fFile);
  fclose(fFile);

  if(IsMap(pBuff))	
  {
	//We parse our text buffer and read our shit in
    LoadWcMap(pBuff);
  }else
  {
	//MessageBox(NULL,"That's not a valid .map file.","iowc_map.dll",MB_OK);
	return FALSE;
  }


  // We release text buffer memory
  delete [] pBuff;
  pBuff = NULL;

  //glog->Printf2("\n\t**** Loading completed ****\n\n");

  return true;
 }
 
 return false;
}

