/*

  IOIOmd2.CPP
  
*/

#include "stdafx.h"
#include <Kapsul3D.h>
#include <stdio.h>
#include <io.h>
#include "iomd2.h"

Vertex GEKQ2NORMALS[162] =
{Vertex(-0.525731f,  0.000000f,  0.850651f), Vertex(-0.442863f,  0.238856f,  0.864188f), Vertex(-0.295242f,  0.000000f,  0.955423f), 
Vertex(-0.309017f,  0.500000f,  0.809017f), Vertex(-0.162460f,  0.262866f,  0.951056f), Vertex( 0.000000f,  0.000000f,  1.000000f), 
Vertex( 0.000000f,  0.850651f,  0.525731f), Vertex(-0.147621f,  0.716567f,  0.681718f), Vertex( 0.147621f,  0.716567f,  0.681718f), 
Vertex( 0.000000f,  0.525731f,  0.850651f), Vertex( 0.309017f,  0.500000f,  0.809017f), Vertex( 0.525731f,  0.000000f,  0.850651f), 
Vertex( 0.295242f,  0.000000f,  0.955423f), Vertex( 0.442863f,  0.238856f,  0.864188f), Vertex( 0.162460f,  0.262866f,  0.951056f),
Vertex(-0.681718f,  0.147621f,  0.716567f), Vertex(-0.809017f,  0.309017f,  0.500000f), Vertex(-0.587785f,  0.425325f,  0.688191f), 
Vertex(-0.850651f,  0.525731f,  0.000000f), Vertex(-0.864188f,  0.442863f,  0.238856f), Vertex(-0.716567f,  0.681718f,  0.147621f), 
Vertex(-0.688191f,  0.587785f,  0.425325f), Vertex(-0.500000f,  0.809017f,  0.309017f), Vertex(-0.238856f,  0.864188f,  0.442863f), 
Vertex(-0.425325f,  0.688191f,  0.587785f), Vertex(-0.716567f,  0.681718f, -0.147621f), Vertex(-0.500000f,  0.809017f, -0.309017f), 
Vertex(-0.525731f,  0.850651f,  0.000000f), Vertex( 0.000000f,  0.850651f, -0.525731f), Vertex(-0.238856f,  0.864188f, -0.442863f), 
Vertex( 0.000000f,  0.955423f, -0.295242f), Vertex(-0.262866f,  0.951056f, -0.162460f), Vertex( 0.000000f,  1.000000f,  0.000000f), 
Vertex( 0.000000f,  0.955423f,  0.295242f), Vertex(-0.262866f,  0.951056f,  0.162460f), Vertex( 0.238856f,  0.864188f,  0.442863f), 
Vertex( 0.262866f,  0.951056f,  0.162460f), Vertex( 0.500000f,  0.809017f,  0.309017f), Vertex( 0.238856f,  0.864188f, -0.442863f), 
Vertex( 0.262866f,  0.951056f, -0.162460f), Vertex( 0.500000f,  0.809017f, -0.309017f), Vertex( 0.850651f,  0.525731f,  0.000000f), 
Vertex( 0.716567f,  0.681718f,  0.147621f), Vertex( 0.716567f,  0.681718f, -0.147621f), Vertex( 0.525731f,  0.850651f,  0.000000f), 
Vertex( 0.425325f,  0.688191f,  0.587785f), Vertex( 0.864188f,  0.442863f,  0.238856f), Vertex( 0.688191f,  0.587785f,  0.425325f), 
Vertex( 0.809017f,  0.309017f,  0.500000f), Vertex( 0.681718f,  0.147621f,  0.716567f), Vertex( 0.587785f,  0.425325f,  0.688191f), 
Vertex( 0.955423f,  0.295242f,  0.000000f), Vertex( 1.000000f,  0.000000f,  0.000000f), Vertex( 0.951056f,  0.162460f,  0.262866f), 
Vertex( 0.850651f, -0.525731f,  0.000000f), Vertex( 0.955423f, -0.295242f,  0.000000f), Vertex( 0.864188f, -0.442863f,  0.238856f), 
Vertex( 0.951056f, -0.162460f,  0.262866f), Vertex( 0.809017f, -0.309017f,  0.500000f), Vertex( 0.681718f, -0.147621f,  0.716567f), 
Vertex( 0.850651f,  0.000000f,  0.525731f), Vertex( 0.864188f,  0.442863f, -0.238856f), Vertex( 0.809017f,  0.309017f, -0.500000f), 
Vertex( 0.951056f,  0.162460f, -0.262866f), Vertex( 0.525731f,  0.000000f, -0.850651f), Vertex( 0.681718f,  0.147621f, -0.716567f), 
Vertex( 0.681718f, -0.147621f, -0.716567f), Vertex( 0.850651f,  0.000000f, -0.525731f), Vertex( 0.809017f, -0.309017f, -0.500000f), 
Vertex( 0.864188f, -0.442863f, -0.238856f), Vertex( 0.951056f, -0.162460f, -0.262866f), Vertex( 0.147621f,  0.716567f, -0.681718f), 
Vertex( 0.309017f,  0.500000f, -0.809017f), Vertex( 0.425325f,  0.688191f, -0.587785f), Vertex( 0.442863f,  0.238856f, -0.864188f), 
Vertex( 0.587785f,  0.425325f, -0.688191f), Vertex( 0.688191f,  0.587785f, -0.425325f), Vertex(-0.147621f,  0.716567f, -0.681718f), 
Vertex(-0.309017f,  0.500000f, -0.809017f), Vertex( 0.000000f,  0.525731f, -0.850651f), Vertex(-0.525731f,  0.000000f, -0.850651f), 
Vertex(-0.442863f,  0.238856f, -0.864188f), Vertex(-0.295242f,  0.000000f, -0.955423f), Vertex(-0.162460f,  0.262866f, -0.951056f), 
Vertex( 0.000000f,  0.000000f, -1.000000f), Vertex( 0.295242f,  0.000000f, -0.955423f), Vertex( 0.162460f,  0.262866f, -0.951056f), 
Vertex(-0.442863f, -0.238856f, -0.864188f), Vertex(-0.309017f, -0.500000f, -0.809017f), Vertex(-0.162460f, -0.262866f, -0.951056f), 
Vertex( 0.000000f, -0.850651f, -0.525731f), Vertex(-0.147621f, -0.716567f, -0.681718f), Vertex( 0.147621f, -0.716567f, -0.681718f), 
Vertex( 0.000000f, -0.525731f, -0.850651f), Vertex( 0.309017f, -0.500000f, -0.809017f), Vertex( 0.442863f, -0.238856f, -0.864188f), 
Vertex( 0.162460f, -0.262866f, -0.951056f), Vertex( 0.238856f, -0.864188f, -0.442863f), Vertex( 0.500000f, -0.809017f, -0.309017f), 
Vertex( 0.425325f, -0.688191f, -0.587785f), Vertex( 0.716567f, -0.681718f, -0.147621f), Vertex( 0.688191f, -0.587785f, -0.425325f), 
Vertex( 0.587785f, -0.425325f, -0.688191f), Vertex( 0.000000f, -0.955423f, -0.295242f), Vertex( 0.000000f, -1.000000f,  0.000000f), 
Vertex( 0.262866f, -0.951056f, -0.162460f), Vertex( 0.000000f, -0.850651f,  0.525731f), Vertex( 0.000000f, -0.955423f,  0.295242f), 
Vertex( 0.238856f, -0.864188f,  0.442863f), Vertex( 0.262866f, -0.951056f,  0.162460f), Vertex( 0.500000f, -0.809017f,  0.309017f), 
Vertex( 0.716567f, -0.681718f,  0.147621f), Vertex( 0.525731f, -0.850651f,  0.000000f), Vertex(-0.238856f, -0.864188f, -0.442863f), 
Vertex(-0.500000f, -0.809017f, -0.309017f), Vertex(-0.262866f, -0.951056f, -0.162460f), Vertex(-0.850651f, -0.525731f,  0.000000f), 
Vertex(-0.716567f, -0.681718f, -0.147621f), Vertex(-0.716567f, -0.681718f,  0.147621f), Vertex(-0.525731f, -0.850651f,  0.000000f), 
Vertex(-0.500000f, -0.809017f,  0.309017f), Vertex(-0.238856f, -0.864188f,  0.442863f), Vertex(-0.262866f, -0.951056f,  0.162460f), 
Vertex(-0.864188f, -0.442863f,  0.238856f), Vertex(-0.809017f, -0.309017f,  0.500000f), Vertex(-0.688191f, -0.587785f,  0.425325f), 
Vertex(-0.681718f, -0.147621f,  0.716567f), Vertex(-0.442863f, -0.238856f,  0.864188f), Vertex(-0.587785f, -0.425325f,  0.688191f), 
Vertex(-0.309017f, -0.500000f,  0.809017f), Vertex(-0.147621f, -0.716567f,  0.681718f), Vertex(-0.425325f, -0.688191f,  0.587785f), 
Vertex(-0.162460f, -0.262866f,  0.951056f), Vertex( 0.442863f, -0.238856f,  0.864188f), Vertex( 0.162460f, -0.262866f,  0.951056f), 
Vertex( 0.309017f, -0.500000f,  0.809017f), Vertex( 0.147621f, -0.716567f,  0.681718f), Vertex( 0.000000f, -0.525731f,  0.850651f), 
Vertex( 0.425325f, -0.688191f,  0.587785f), Vertex( 0.587785f, -0.425325f,  0.688191f), Vertex( 0.688191f, -0.587785f,  0.425325f), 
Vertex(-0.955423f,  0.295242f,  0.000000f), Vertex(-0.951056f,  0.162460f,  0.262866f), Vertex(-1.000000f,  0.000000f,  0.000000f), 
Vertex(-0.850651f,  0.000000f,  0.525731f), Vertex(-0.955423f, -0.295242f,  0.000000f), Vertex(-0.951056f, -0.162460f,  0.262866f), 
Vertex(-0.864188f,  0.442863f, -0.238856f), Vertex(-0.951056f,  0.162460f, -0.262866f), Vertex(-0.809017f,  0.309017f, -0.500000f), 
Vertex(-0.864188f, -0.442863f, -0.238856f), Vertex(-0.951056f, -0.162460f, -0.262866f), Vertex(-0.809017f, -0.309017f, -0.500000f), 
Vertex(-0.681718f,  0.147621f, -0.716567f), Vertex(-0.681718f, -0.147621f, -0.716567f), Vertex(-0.850651f,  0.000000f, -0.525731f),
Vertex(-0.688191f,  0.587785f, -0.425325f), Vertex(-0.587785f,  0.425325f, -0.688191f), Vertex(-0.425325f,  0.688191f, -0.587785f), 
Vertex(-0.425325f, -0.688191f, -0.587785f), Vertex(-0.587785f, -0.425325f, -0.688191f), Vertex(-0.688191f, -0.587785f, -0.425325f)};

CKIomd2::CKIomd2()
{
}
CKIomd2::~CKIomd2()
{
}

CString CKIomd2::GetName()
{
	return "Quake2 models importer";
}
CString CKIomd2::GetInfos()
{
	return "Quake2 models importer";
}
CString CKIomd2::GetFilter()
{
	return "*.md2";
}
CString CKIomd2::GetFileDescription()
{
	return "Quake2 model";
}
CString CKIomd2::GetFileExtension()
{
	return ".md2";
}
bool CKIomd2::SupportReading()
{
	return true;
}
bool CKIomd2::SupportWriting()
{
	return false;
}

bool CKIomd2::Read(CKScene *pScene,CString FullFilePath)
{
	DWORD Position = 0, Length = 0;
	FILE *File = NULL;
    char temp[50];
    int tempav;
    char *tempptr;
	
	//	if(Archive != NULL) File = Archive->Seek(FileName, &Position, &Length);
	if(File == NULL)
	{
		File = fopen(FullFilePath, "rb");
		if(File != NULL) Length = filelength(fileno(File));
	}
	if(File == NULL) return false;
	
	BYTE *FileData = (BYTE *)malloc(Length);
	if(FileData == NULL)
	{
		fclose(File);
		return false;
	}
	
	fread(FileData, 1, Length, File);
	fclose(File);
	
    // header
	
	memcpy(&Header, FileData, sizeof(GEKMD2HEADER));
	if(/*(Header.dwID != _FOURCC('I', 'D', 'P', '2'))&&*/
		(Header.dwVersion != 8)) return false;
	
    if (Header.dwNumSkins==1)
    {
        tempav=0;
        tempptr=(char*)FileData;
        tempptr+=sizeof(GEKMD2HEADER);
        
        //pScene->AddMat();
        while((*tempptr)!=0)
        {
            if (((*tempptr)=='\\')||((*tempptr)=='/'))
            {
                tempav=0;
                tempptr++;
            }
			
            temp[tempav]=(*tempptr);
            tempptr++;
            tempav++;
        }
        temp[tempav]=0;
        /*
        strcpy(pScene->NextMat->Name,temp);
        strcpy(pScene->NextMat->Map1Name,temp);
		*/
		
    }
	
    pScene->AddMesh();
	//    pScene->NextMesh->Mat=pScene->GetMaterial(temp);
    pScene->NextMesh->AllocatePoly(Header.dwNumTriangles,Header.dwNumVertices/**Header.dwNumFrames*/);
	pScene->NextMesh->AllocateUV(0,Header.dwNumTriangles*3);
    pScene->NextMesh->nb2vert=Header.dwNumVertices;
    
	WORD *MD2TexCoords = (WORD *)(FileData + Header.dwOffST);
	
	DWORD NumIndices = (Header.dwNumTriangles * 3);
	//lpIndices = (WORD *)malloc(sizeof(WORD) * NumIndices);
	//if(lpIndices == NULL) return false;
	
	
    /*
	lpTexCoords = (GEKTEXCOORD *)malloc(sizeof(GEKTEXCOORD) * NumIndices);
	if(lpTexCoords == NULL) return false;
    */
	
	short *MD2Triangles = (short *)(FileData + Header.dwOffTris);
    int FaceAv=0;
	int UVAv=0;
	
	for(DWORD Indice = 0; Indice < NumIndices; Indice += 3)
	{
		
		
        short tmp;
		
		pScene->NextMesh->pl[FaceAv].Allocate(pScene->NextMesh,1,3);
		
        tmp=(*MD2Triangles++);
		pScene->NextMesh->pl[FaceAv].nbvert[2]= tmp;
		pScene->NextMesh->pl[FaceAv].Tex[0][2]= UVAv+2;
        tmp=(*MD2Triangles++);
		pScene->NextMesh->pl[FaceAv].nbvert[1]= tmp;
		pScene->NextMesh->pl[FaceAv].Tex[0][1]= UVAv+1;
        tmp=(*MD2Triangles++);
		pScene->NextMesh->pl[FaceAv].nbvert[0]= tmp;
		pScene->NextMesh->pl[FaceAv].Tex[0][0]= UVAv;
		
        //MD2Triangles+=3;
		
		DWORD Index = (*MD2Triangles);
		MD2Triangles++;
		pScene->NextMesh->puv[0][UVAv+2].u = ((float)MD2TexCoords[(Index * 2) + 0] / (float)Header.dwSkinWidth);
		pScene->NextMesh->puv[0][UVAv+2].v = 1-((float)MD2TexCoords[(Index * 2) + 1] / (float)Header.dwSkinHeight);
		
		Index = Index = (*MD2Triangles);
		MD2Triangles++;
		//pScene->NextMesh->pv[pScene->NextMesh->pf[FaceAv].nbvert[1]].u = ((float)MD2TexCoords[(Index * 2) + 0] / (float)Header.dwSkinWidth);
		//pScene->NextMesh->pv[pScene->NextMesh->pf[FaceAv].nbvert[1]].v = 1-((float)MD2TexCoords[(Index * 2) + 1] / (float)Header.dwSkinHeight);
		pScene->NextMesh->puv[0][UVAv+1].u = ((float)MD2TexCoords[(Index * 2) + 0] / (float)Header.dwSkinWidth);
		pScene->NextMesh->puv[0][UVAv+1].v = 1-((float)MD2TexCoords[(Index * 2) + 1] / (float)Header.dwSkinHeight);
		
		Index = Index = (*MD2Triangles);
		MD2Triangles++;
		//pScene->NextMesh->pv[pScene->NextMesh->pf[FaceAv].nbvert[0]].u = ((float)MD2TexCoords[(Index * 2) + 0] / (float)Header.dwSkinWidth);
		//pScene->NextMesh->pv[pScene->NextMesh->pf[FaceAv].nbvert[0]].v = 1-((float)MD2TexCoords[(Index * 2) + 1] / (float)Header.dwSkinHeight);
		pScene->NextMesh->puv[0][UVAv].u = ((float)MD2TexCoords[(Index * 2) + 0] / (float)Header.dwSkinWidth);
		pScene->NextMesh->puv[0][UVAv].v = 1-((float)MD2TexCoords[(Index * 2) + 1] / (float)Header.dwSkinHeight);
		
        FaceAv++;
		UVAv+=3;
	}
	
    //Header.dwNumFrames=1;
	
	lpVertices = (Vertex **)malloc(sizeof(Vertex *) * Header.dwNumFrames);
	if(lpVertices == NULL) return false;
	
	
	lpNormals = (Vertex **)malloc(sizeof(Vertex *) * Header.dwNumFrames);
	if(lpNormals == NULL) return false;
	
	BYTE *AliasMalloc = (BYTE *)malloc(Header.dwFrameSize);
	if(AliasMalloc == NULL) return false;
	
    
	BYTE *Frames = (BYTE *)(FileData + Header.dwOffFrames);
	for(DWORD Frame = 0; Frame < 1/*Header.dwNumFrames*/; Frame++)
	{
		
		GEKMD2ALIASFRAME *AliasFrame = (GEKMD2ALIASFRAME *)AliasMalloc;
		memcpy(AliasFrame, Frames, Header.dwFrameSize);
        
		Frames += Header.dwFrameSize;
		
		lpVertices[Frame] = (Vertex *)malloc(sizeof(Vertex) * Header.dwNumVertices);
		lpNormals[Frame] = (Vertex *)malloc(sizeof(Vertex) * Header.dwNumVertices);
		if((lpVertices[Frame] == NULL)||(lpNormals[Frame] == NULL))
		{
			free(AliasMalloc);
			return false;
		}
		
		Vertex Scale(AliasFrame->sfX, AliasFrame->sfY, AliasFrame->sfZ);
		Vertex Translate(AliasFrame->tfX, AliasFrame->tfY, AliasFrame->tfZ);
		
		for(DWORD Ind = 0; Ind < Header.dwNumVertices; Ind++)
		{
			Vertex Vector(AliasFrame->lpTriangles[Ind].lpVertices[0],
				AliasFrame->lpTriangles[Ind].lpVertices[1],
				AliasFrame->lpTriangles[Ind].lpVertices[2]);
			pScene->NextMesh->pv[Ind+(Frame*Header.dwNumVertices)].x = Vector.x; //(((Vector * Scale) + Translate) * 0.01f);
            pScene->NextMesh->pv[Ind+(Frame*Header.dwNumVertices)].y = Vector.y; //(((Vector * Scale) + Translate) * 0.01f);
            pScene->NextMesh->pv[Ind+(Frame*Header.dwNumVertices)].z = Vector.z; //(((Vector * Scale) + Translate) * 0.01f);
            
            pScene->NextMesh->pv[Ind+(Frame*Header.dwNumVertices)].x*=Scale.x;
			pScene->NextMesh->pv[Ind+(Frame*Header.dwNumVertices)].y*=Scale.y;
			pScene->NextMesh->pv[Ind+(Frame*Header.dwNumVertices)].z*=Scale.z;
            
			
			pScene->NextMesh->pv[Ind+(Frame*Header.dwNumVertices)] +=Translate;//(*pScene->NextMesh->pv[Ind+(Frame*Header.dwNumVertices)])+Translate;
            
			pScene->NextMesh->pv[Ind+(Frame*Header.dwNumVertices)].x*=100;
            pScene->NextMesh->pv[Ind+(Frame*Header.dwNumVertices)].y*=100;
            pScene->NextMesh->pv[Ind+(Frame*Header.dwNumVertices)].z*=100;
			//Vertex Normal = GEKQ2NORMALS[AliasFrame->lpTriangles[Vertex].bNormal];
			//lpNormals[Frame][Vertex] = Vertex(Normal.fX, Normal.fZ, Normal.fY);
		}
	}
	
	free(AliasMalloc);
	free(FileData);
	return true;
	
}
bool CKIomd2::Write(CKScene *pScene,CString FullFilePath)
{
	return false;
}