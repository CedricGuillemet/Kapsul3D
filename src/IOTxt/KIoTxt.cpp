// KIoTxt.cpp: implementation of the CKIoTxt class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <Kapsul3D.h>
#include "KIoTxt.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



CKIoTxt::CKIoTxt()
{
	nBufSize=512;
}

CKIoTxt::~CKIoTxt()
{

}

void CKIoTxt::ReadBone(CKBone *daBone,FILE *fp)
{
	
	
	sscanf(temp,"%s \n",daBone->Name);

	fgets(temp,nBufSize,fp);
	sscanf(temp,"%f %f %f\n",&v1,&v2,&v3);
	daBone->Pos.x=v1;
	daBone->Pos.y=v2;
	daBone->Pos.z=v3;
	
	fgets(temp,nBufSize,fp); // weights {
	fgets(temp,nBufSize,fp); 
	while(strcmp(temp,"}\n")!=0)
	{
		
		float weight;
		int ind;
		sscanf(temp,"%d %f \n",&ind,&weight);
		daBone->AddVert(&CurSkel->m_Mesh->pv[ind],ind,weight);

		fgets(temp,nBufSize,fp); // weights {
	}

	fgets(temp,nBufSize,fp);
	while (strcmp(temp,"End\n")!=0)
	{
		CKBone *dab=CurSkel->AddBone(daBone);
		ReadBone(dab,fp);
		fgets(temp,nBufSize,fp);
	}
}
bool CKIoTxt::Read(CKScene *pScene,CString FullFilePath)
{
	FILE *fp;
	CKMesh *daMesh;
	CKCamera *dacam;
	int i,j,k,l,m;
	int nbvert,nbpolys;
	int counto,countl,countc,counte,counts,countp,counten,countsh,counttex;
	CKTexture **alltex;
	int t1,t2,t3,t4;
	CKEntity *daEntity;
	CKPatch *daPatch;

	m_Option=(CKOption*)GetGOption();

	fp=fopen(FullFilePath.GetBuffer(0),"rt");
	if (fp!=NULL)
	{
		// Meshs

		//while(fgets(temp,nBufSize,fp)!=NULL)
		//{
		fgets(temp,nBufSize,fp);
		if (strcmp(temp,"Kapsul Text Export\n")!=NULL)
		{
			fclose(fp);
			return false;
		}


		fgets(temp,nBufSize,fp);
		sscanf(temp,"%d Meshs\n",&counto);
		fgets(temp,nBufSize,fp);
		sscanf(temp,"%d Cameras\n",&countc);
		fgets(temp,nBufSize,fp);
		sscanf(temp,"%d Skeletons\n",&counts);
		fgets(temp,nBufSize,fp);
		sscanf(temp,"%d Patches\n",&countp);
		fgets(temp,nBufSize,fp);
		sscanf(temp,"%d Entities\n",&counten);
		fgets(temp,nBufSize,fp);
		sscanf(temp,"%d Shapes\n",&countsh);
		fgets(temp,nBufSize,fp);
		sscanf(temp,"%d Textures\n",&counttex);

		alltex=new CKTexture*[counttex];

		// -- Textures -------------------------------------------------------
		int txav=0;
		for (k=0;k<counttex;k++)
		{
			char tmpTex[MAX_PATH];
			fgets(temp,nBufSize,fp);
			sscanf(temp,"Filename %s\n",tmpTex);
			CString FullTexPath=GetFullPath(tmpTex);
			if (strcmp(FullTexPath,"DefaultTexture")!=0)
			{
				alltex[txav]=pScene->AddTex(FullTexPath);
				alltex[txav]->Type=TEXTURE_FILE;
				txav++;
			}
			else
			{
				// if texture is not found is texture path, set the default texture.
				alltex[k]=pScene->FirstTexture;
			}
		}

		// -- Meshs --------------------------------------------------------

		for (k=0;k<counto;k++)
		{
			// name


			pScene->AddMesh();
			daMesh=pScene->NextMesh;

			/*
			fgets(temp,nBufSize,fp);
			sscanf(temp,"Mesh %s\n",daMesh->Name);
			*/
			daMesh->m_Table.ReadFromDisk(fp,daMesh,PLUGIN_MESH);

			// textures canals
			fgets(temp,nBufSize,fp);
			sscanf(temp,"%d Canals\n",&m/*daMesh->nbTexCanals*/);
			

			for (i=0;i<m;i++)
			{
				
				fgets(temp,nBufSize,fp);

				//NB: default texture can only appear in first canal.
				
				switch(i)
				{
				case 0:
					sscanf(temp,"Tex %s ",temp2);
					if (strcmp(temp2,"DefaultTexture")!=0)
					{
						
						
//						strcpy(daMesh->TexName1,temp2);
						daMesh->Tex1=pScene->AddTex(GetFullPath(temp2));
						daMesh->Tex1->Type=TEXTURE_FILE;
					}
					break;
				case 1:
					sscanf(temp,"Tex %s ",temp2);

					daMesh->Tex2=pScene->AddTex(GetFullPath(temp2));
					daMesh->Tex2->Type=TEXTURE_FILE;
					break;
				case 2:
					sscanf(temp,"Tex %s ",temp2);
					daMesh->Tex3=pScene->AddTex(GetFullPath(temp2));
					daMesh->Tex3->Type=TEXTURE_FILE;
					break;
				case 3:
					sscanf(temp,"Tex %s ",temp2);
					daMesh->Tex4=pScene->AddTex(GetFullPath(temp2));
					daMesh->Tex4->Type=TEXTURE_FILE;
					break;
				}
				

				// uv
				fgets(temp,nBufSize,fp);
				sscanf(temp,"%d UVs\n",&l);
				daMesh->AllocateUV(i,l);
				

				for (j=0;j<daMesh->nbTexCoords[i];j++)
				{
					fgets(temp,nBufSize,fp);
					sscanf(temp,"%f %f",&v1,&v2);
					daMesh->puv[i][j].u=v1;
					daMesh->puv[i][j].v=v2;
				}

			}

			// vertex 
			fgets(temp,nBufSize,fp);
			sscanf(temp,"%d Vertex\n",&nbvert);
			daMesh->AllocatePoly(0,nbvert);
			for (i=0;i<nbvert;i++)
			{
				fgets(temp,nBufSize,fp);
				sscanf(temp,"%f %f %f\n",&v1,&v2,&v3);
				daMesh->pv[i].x=v1;
				daMesh->pv[i].y=v2;
				daMesh->pv[i].z=v3;
			}

    		// faces
			fgets(temp,nBufSize,fp);
			sscanf(temp,"%d Polys\n",&nbvert);
			daMesh->AllocatePoly(nbvert,0);
			for (i=0;i<nbvert;i++)
			{
				fgets(temp,nBufSize,fp);
				sscanf(temp,"%d %d %d %d %d\n",&nbpolys,&t1,&t2,&t3,&t4);

				daMesh->pl[i].Maps[0]=((t1==-1)?NULL:alltex[t1]);
				daMesh->pl[i].Maps[1]=((t2==-1)?NULL:alltex[t2]);
				daMesh->pl[i].Maps[2]=((t3==-1)?NULL:alltex[t3]);
				daMesh->pl[i].Maps[3]=((t4==-1)?NULL:alltex[t4]);

				//for (j=0;j<daMesh->nbTexCanals;j++)
				daMesh->pl[i].Allocate(daMesh,daMesh->nbTexCanals,nbpolys);

				for (j=0;j<daMesh->pl[i].nb2vert;j++)
				{
					fgets(temp,nBufSize,fp);

					switch(daMesh->nbTexCanals)
					{
					case 1:
						sscanf(temp,"I %d UV %d \n",&daMesh->pl[i].nbvert[j],&daMesh->pl[i].Tex[0][j]);
						break;
					case 2:
						sscanf(temp,"I %d UV %d %d \n",&daMesh->pl[i].nbvert[j],&daMesh->pl[i].Tex[0][j],&daMesh->pl[i].Tex[1][j]);
						break;
					case 3:
						sscanf(temp,"I %d UV %d %d %d \n",&daMesh->pl[i].nbvert[j],&daMesh->pl[i].Tex[0][j],&daMesh->pl[i].Tex[1][j],&daMesh->pl[i].Tex[2][j]);
						break;
					case 4:
						sscanf(temp,"I %d UV %d %d %d %d \n",&daMesh->pl[i].nbvert[j],&daMesh->pl[i].Tex[0][j],&daMesh->pl[i].Tex[1][j],&daMesh->pl[i].Tex[2][j],&daMesh->pl[i].Tex[3][j]);
						break;
					}
					//sscanf(temp,"I %d UV %d\n",&daMesh->pl[i]->nbvert[j],&daMesh->pl[i]->Tex[0][j]);
				}
			}
			daMesh->UpdateMesh();
		}

		delete [] alltex;
		// Camera
		for (k=0;k<countc;k++)
		{
			pScene->AddCam();
			dacam=pScene->NextCam;

			dacam->m_Table.ReadFromDisk(fp,dacam,PLUGIN_CAMERA);

			fgets(temp,nBufSize,fp);
			sscanf(temp,"%f %f %f\n",&v1,&v2,&v3);
			dacam->Source.x=v1;
			dacam->Source.y=v2;
			dacam->Source.z=v3;
			fgets(temp,nBufSize,fp);
			sscanf(temp,"%f %f %f\n",&v1,&v2,&v3);
			dacam->Dest.x=v1;
			dacam->Dest.y=v2;
			dacam->Dest.z=v3;
			
			fgets(temp,nBufSize,fp);
			sscanf(temp,"%f \n",&v1);
			dacam->Fov=v1;

			fgets(temp,nBufSize,fp);
			sscanf(temp,"%d %d \n",&dacam->ResoX,&dacam->ResoY);
		}
		// -- Skeleton -------------------------------------------------------

		for (k=0;k<counts;k++)
		{
			pScene->AddSkel();
			CurSkel=pScene->NextSkel;

			CurSkel->m_Table.ReadFromDisk(fp,CurSkel,PLUGIN_SKELETON);

            // -- Name et Link Name --------------------------------------------
			fgets(temp,nBufSize,fp);
            sscanf(temp,"Link with %s\n",CurSkel->ObjName);
			CurSkel->m_Mesh=(CKMesh*)pScene->GetByName(CurSkel->ObjName,PLUGIN_MESH);
			

            // -- Bones --------------------------------------------------------
			/*
			fgets(temp,nBufSize,fp);
			sscanf(temp,"%s \n",CurSkel->bone->Name);
*/
			fgets(temp,nBufSize,fp);
			sscanf(temp,"%f %f %f\n",&v1,&v2,&v3);
			CurSkel->RootPos.x=v1;
			CurSkel->RootPos.y=v2;
			CurSkel->RootPos.z=v3;
			
			//for (Bone *daBone=daSkel->bone->FirstBone;daBone!=NULL;daBone=daBone->Next)
			CurSkel->AddBone(NULL);
			fgets(temp,nBufSize,fp);
			ReadBone(CurSkel->bone,fp);
			CurSkel->BuildBase();
			fgets(temp,nBufSize,fp);

			//fputs("End\n",fp);	
        }

		// -- Shape -----------------------------------------------------------------

		for (k=0;k<countsh;k++)
		{
			int countseg;
			CKShape *CurShape=pScene->AddShape();

			CurShape->m_Table.ReadFromDisk(fp,CurShape,PLUGIN_SHAPE);

			fgets(temp,nBufSize,fp);
			sscanf(temp,"%d segs\n",&countseg);

			for (m=0;m<countseg;m++)
			{
				fgets(temp,nBufSize,fp);
				sscanf(temp,"%f %f %f\n",&v1,&v2,&v3);
				if ((v1<=-99999.9999)&&(v2<=-99999.9999)&&(v3<=-99999.9999))
				{
					CurShape->NextSegment->Next=CurShape->FirstSegment;
				}
				else
				{
					CurShape->AddSegment(v1,v2,v3);
				}
			}
		}

		// -- Entities -----------------------------------------------------------

		for (k=0;k<counten;k++)
		{
			
			//daEntity->dk=dk;

			fgets(temp,nBufSize,fp);
			
			//int zob=strlen(temp);
			temp[strlen(temp)-1]=0;
			//daEntity->EntType=temp;

			daEntity=pScene->AddEntity(GetLib()->CreateEntityInterface(temp));
			daEntity->m_Scene=pScene;
			daEntity->EntType=temp;

			//daEntity->UpdateDLLLink();

			daEntity->m_Table.ReadFromDisk(fp);
			daEntity->SetProperties();
		}

		// -- Patch -----------------------------------------------------------

		for (k=0;k<countp;k++)
		{
			daPatch=pScene->AddPatch();

			daPatch->m_Table.ReadFromDisk(fp,daPatch,PLUGIN_PATCH);

			// textures canals
			fgets(temp,nBufSize,fp);
			sscanf(temp,"%d Canals\n",&m/*daMesh->nbTexCanals*/);
			

			for (i=0;i<m;i++)
			{
				
				fgets(temp,nBufSize,fp);

				//NB: default texture can only appear in first canal.
				
				switch(i)
				{
				case 0:
					sscanf(temp,"Tex %s ",temp2);
					if (strcmp(temp2,"DefaultTexture")!=0)
					{
						daPatch->Tex1=pScene->AddTex(GetFullPath(temp2));
						daPatch->Tex1->Type=TEXTURE_FILE;
					}
					break;
				case 1:
					sscanf(temp,"Tex %s ",temp2);
					daPatch->Tex2=pScene->AddTex(GetFullPath(temp2));
					daPatch->Tex2->Type=TEXTURE_FILE;
					break;
				case 2:
					sscanf(temp,"Tex %s ",temp2);
					daPatch->Tex3=pScene->AddTex(GetFullPath(temp2));
					daPatch->Tex3->Type=TEXTURE_FILE;
					break;
				case 3:
					sscanf(temp,"Tex %s ",temp2);
					daPatch->Tex4=pScene->AddTex(GetFullPath(temp2));
					daPatch->Tex4->Type=TEXTURE_FILE;
					break;
				}
				

				// uv
				fgets(temp,nBufSize,fp);
				sscanf(temp,"%d UVs\n",&l);
				daPatch->AllocateUV(i,l);
				

				for (j=0;j<daPatch->nbTexCoords[i];j++)
				{
					fgets(temp,nBufSize,fp);
					sscanf(temp,"%f %f",&v1,&v2);
					daPatch->puv[i][j].u=v1;
					daPatch->puv[i][j].v=v2;
				}

			}

			// vertex 

			fgets(temp,nBufSize,fp);
			sscanf(temp,"%d Vertex\n",&nbvert);
			daPatch->Allocate(0,nbvert);
			for (i=0;i<nbvert;i++)
			{
				fgets(temp,nBufSize,fp);
				sscanf(temp,"%f %f %f\n",&v1,&v2,&v3);
				daPatch->pv[i].x=v1;
				daPatch->pv[i].y=v2;
				daPatch->pv[i].z=v3;
			}

			// opt & ctrl pt

			int m_Tes;
			fgets(temp,nBufSize,fp);
			sscanf(temp,"%d Patches %d Ctrl pts %d Tesselate\n",&daPatch->nb2patch,&m,&m_Tes);

			daPatch->Allocate(m,0);
			for (i=0;i<daPatch->nb2pt;i++)
			{
				fgets(temp,nBufSize,fp);
				sscanf(temp,"%d\n",&daPatch->CtrlsPt[i]);
			}
			daPatch->Build(m_Tes);


		}

		// end !
		fclose(fp);
		return true;
	}

	return false;
}


void CKIoTxt::WriteBone(CKBone *daBone,FILE *fp)
{
	sprintf(temp,"%s \n",daBone->Name);
	fputs(temp,fp);

	sprintf(temp,"%5.4f %5.4f %5.4f\n",daBone->Pos.x,daBone->Pos.y,daBone->Pos.z);
	fputs(temp,fp);

	// Attach list
	fputs("Weights {\n",fp);
	for (CKBoneAttach *daBA=daBone->FirstBA;daBA!=NULL;daBA=daBA->Next)
	{
		sprintf(temp,"%d %5.4f \n",daBA->OriginIndex,daBA->Weight);
		fputs(temp,fp);
	}
	fputs("}\n",fp);
	// recurse bone
	for (CKBone *daBone2=daBone->FirstBone;daBone2!=NULL;daBone2=daBone2->Next)
        WriteBone(daBone2,fp);

	fputs("End\n",fp);
}
bool CKIoTxt::Write(CKScene *pScene,CString FullFilePath)
{
	FILE *fp;
	CKMesh *daMesh;
	CKCamera *dacam;
	CKSkeleton *daSkel;
	CKShape *daShp;
	CKTexture *daTex;
	CKEntity *daEntity;
	CKPatch *daPatch;
	int t1,t2,t3,t4;

	char temp[512],temp2[512];
	int i,j;//,counto=0,countl=0,countc=0;
	int counto=0,countc=0,counts=0,countp=0,counten=0,countsh=0,counttex=0;


	fp=fopen(FullFilePath.GetBuffer(0),"wt");
	if (fp!=NULL)
	{
		for (daMesh=pScene->FirstMesh;daMesh!=NULL;daMesh=daMesh->Next)
			counto++;
		for (dacam=pScene->FirstCam;dacam!=NULL;dacam=dacam->Next)
			countc++;
		for (daSkel=pScene->FirstSkel;daSkel!=NULL;daSkel=daSkel->Next)
			counts++;
		for (daShp=pScene->FirstShape;daShp!=NULL;daShp=daShp->Next)
			countsh++;
		for (daTex=pScene->FirstTexture;daTex!=NULL;daTex=daTex->Next)
			counttex++;
		for (daEntity=pScene->FirstEntity;daEntity!=NULL;daEntity=daEntity->Next)
			counten++;
		for (daPatch=pScene->FirstPatch;daPatch!=NULL;daPatch=daPatch->Next)
			countp++;

		fputs("Kapsul Text Export\n",fp);

		sprintf(temp,"%d Meshs\n",counto);
		fputs(temp,fp);
		sprintf(temp,"%d Cameras\n",countc);
		fputs(temp,fp);
		sprintf(temp,"%d Skeletons\n",counts);
		fputs(temp,fp);
		sprintf(temp,"%d Patches\n",countp);
		fputs(temp,fp);
		sprintf(temp,"%d Entities\n",counten);
		fputs(temp,fp);
		sprintf(temp,"%d Shapes\n",countsh);
		fputs(temp,fp);
		sprintf(temp,"%d Textures\n",counttex);
		fputs(temp,fp);

//		pScene->RecalcTextureIndices();

		// -- Textures --------------------------------------------------------

		char fname[_MAX_FNAME];
		char ext[_MAX_EXT];

		for (daTex=pScene->FirstTexture;daTex!=NULL;daTex=daTex->Next)
		{
			_splitpath(daTex->FileName,NULL,NULL,fname,ext);
			strcat(fname,ext);
			sprintf(temp,"Filename %s\n",fname);
			fputs(temp,fp);
		}

		// -- Meshs ---------------------------------------------------------

		for (daMesh=pScene->FirstMesh;daMesh!=NULL;daMesh=daMesh->Next)
		{
			/*
			sprintf(temp,"Mesh %s\n",daMesh->Name);
			fputs(temp,fp);
			*/
			daMesh->m_Table.WriteToDisk(fp,daMesh,PLUGIN_MESH);

			// textures canals

			sprintf(temp,"%d Canals\n",daMesh->nbTexCanals);
			fputs(temp,fp);

			for (i=0;i<daMesh->nbTexCanals;i++)
			{
				switch(i)
				{
				case 0:
					strcpy(temp2,daMesh->Tex1->FileName);
					break;
				case 1:
					strcpy(temp2,daMesh->Tex2->FileName);
					break;
				case 2:
					strcpy(temp2,daMesh->Tex3->FileName);
					break;
				case 3:
					strcpy(temp2,daMesh->Tex4->FileName);
					break;
				}
				char temp3[MAX_PATH],temp4[MAX_PATH];
				_splitpath(temp2,NULL,NULL,temp3,temp4);
				strcat(temp3,temp4);
				sprintf(temp,"Tex %s \n",temp3);

				fputs(temp,fp);

				// NB
				// Access lightmaps via daMesh->TexN->lpBits
				// size are daMesh->TexN->RawSizeX and daMesh->TexN->RawSizeY

				// uv

				sprintf(temp,"%d UVs\n",daMesh->nbTexCoords[i]);
				fputs(temp,fp);

				for (j=0;j<daMesh->nbTexCoords[i];j++)
				{
					sprintf(temp,"%5.4f %5.4f \n",daMesh->puv[i][j].u,daMesh->puv[i][j].v);
					fputs(temp,fp);
				}

			}

			// vertex 

			sprintf(temp,"%d Vertex\n",daMesh->nb2vert);
			fputs(temp,fp);

			for (i=0;i<daMesh->nb2vert;i++)
			{
				sprintf(temp,"%5.4f %5.4f %5.4f\n",daMesh->pv[i].x,daMesh->pv[i].y,daMesh->pv[i].z);
				fputs(temp,fp);
			}

			// faces

			sprintf(temp,"%d Polys\n",daMesh->nb2poly);
			fputs(temp,fp);

			for (i=0;i<daMesh->nb2poly;i++)
			{
				t1=((daMesh->pl[i].Maps[0]==NULL)?-1:daMesh->pl[i].Maps[0]->Indice);
				t2=((daMesh->pl[i].Maps[1]==NULL)?-1:daMesh->pl[i].Maps[1]->Indice);
				t3=((daMesh->pl[i].Maps[2]==NULL)?-1:daMesh->pl[i].Maps[2]->Indice);
				t4=((daMesh->pl[i].Maps[3]==NULL)?-1:daMesh->pl[i].Maps[3]->Indice);

				sprintf(temp,"%d %d %d %d %d\n",daMesh->pl[i].nb2vert,t1,t2,t3,t4);
				fputs(temp,fp);
				for (j=0;j<daMesh->pl[i].nb2vert;j++)
				{


					switch(daMesh->nbTexCanals)
					{
					case 1:
						sprintf(temp,"I %d UV %d \n",daMesh->pl[i].nbvert[j],daMesh->pl[i].Tex[0][j]);
						break;
					case 2:
						sprintf(temp,"I %d UV %d %d \n",daMesh->pl[i].nbvert[j],daMesh->pl[i].Tex[0][j],daMesh->pl[i].Tex[1][j]);
						break;
					case 3:
						sprintf(temp,"I %d UV %d %d %d \n",daMesh->pl[i].nbvert[j],daMesh->pl[i].Tex[0][j],daMesh->pl[i].Tex[1][j],daMesh->pl[i].Tex[2][j]);
						break;
					case 4:
						sprintf(temp,"I %d UV %d %d %d %d \n",daMesh->pl[i].nbvert[j],daMesh->pl[i].Tex[0][j],daMesh->pl[i].Tex[1][j],daMesh->pl[i].Tex[2][j],daMesh->pl[i].Tex[3][j]);
						break;
					}
					
					fputs(temp,fp);
				}
			}


		}

		// -- Camera ----------------------------------------------------------

		for (dacam=pScene->FirstCam;dacam!=NULL;dacam=dacam->Next)
		{
			dacam->m_Table.WriteToDisk(fp,dacam,PLUGIN_CAMERA);

			sprintf(temp,"%f %f %f\n",dacam->Source.x,dacam->Source.y,dacam->Source.z);
			fputs(temp,fp);

			sprintf(temp,"%f %f %f\n",dacam->Dest.x,dacam->Dest.y,dacam->Dest.z);
			fputs(temp,fp);

			sprintf(temp,"%f \n",dacam->Fov);
			fputs(temp,fp);

			sprintf(temp,"%d %d \n",dacam->ResoX,dacam->ResoY);
			fputs(temp,fp);
		}

		// -- Skeleton -------------------------------------------------------

		for (daSkel=pScene->FirstSkel;daSkel!=NULL;daSkel=daSkel->Next)
		{
            // -- Name et Link Name --------------------------------------------

			daSkel->m_Table.WriteToDisk(fp,daSkel,PLUGIN_SKELETON);

            sprintf(temp,"Link with %s\n",daSkel->ObjName);
			fputs(temp,fp);

            // -- Bones --------------------------------------------------------
			sprintf(temp,"%5.4f %5.4f %5.4f\n",daSkel->RootPos.x,daSkel->RootPos.y,daSkel->RootPos.z);
			fputs(temp,fp);

			WriteBone(daSkel->bone,fp);

			fputs("End\n",fp);	
        }

		// -- Shape -----------------------------------------------------------

		CKSegment *daSeg;
		for (daShp=pScene->FirstShape;daShp!=NULL;daShp=daShp->Next)
		{
			daShp->m_Table.WriteToDisk(fp,daShp,PLUGIN_CAMERA);

			int countseg=0;

			daSeg=daShp->FirstSegment;
	        while(daSeg!=NULL)
		    {
				countseg++;
				daSeg=daSeg->Next;
				if (daSeg==daShp->FirstSegment)
				{
					countseg++;
					break;
				}
			}

			sprintf(temp,"%d segs\n",countseg);
			fputs(temp,fp);

			daSeg=daShp->FirstSegment;
	        while(daSeg!=NULL)
		    {
				sprintf(temp,"%5.4f %5.4f %5.4f\n",daSeg->Dot.x,daSeg->Dot.y,daSeg->Dot.z);
				fputs(temp,fp);

				daSeg=daSeg->Next;

				if (daSeg==daShp->FirstSegment)
				{
					sprintf(temp,"%5.4f %5.4f %5.4f\n",-99999.9999,-99999.9999,-99999.9999);
					fputs(temp,fp);
					break;
				}

			}
		}

		// -- Entities -----------------------------------------------------------

		for (daEntity=pScene->FirstEntity;daEntity!=NULL;daEntity=daEntity->Next)
		{
			fputs(daEntity->EntType,fp);
			fputs("\n",fp);
			daEntity->m_Table.WriteToDisk(fp);
		}

		// -- Patch -----------------------------------------------------------

		for (daPatch=pScene->FirstPatch;daPatch!=NULL;daPatch=daPatch->Next)
		{

			daPatch->m_Table.WriteToDisk(fp,daPatch,PLUGIN_PATCH);


			sprintf(temp,"%d Canals\n",daPatch->nbTexCanals);
			fputs(temp,fp);

			for (i=0;i<daPatch->nbTexCanals;i++)
			{
				switch(i)
				{
				case 0:
					strcpy(temp2,daPatch->Tex1->FileName);
					break;
				case 1:
					strcpy(temp2,daPatch->Tex2->FileName);
					break;
				case 2:
					strcpy(temp2,daPatch->Tex3->FileName);
					break;
				case 3:
					strcpy(temp2,daPatch->Tex4->FileName);
					break;
				}
				char temp3[MAX_PATH],temp4[MAX_PATH];
				_splitpath(temp2,NULL,NULL,temp3,temp4);
				strcat(temp3,temp4);
				sprintf(temp,"Tex %s \n",temp3);

				fputs(temp,fp);

				// NB
				// Access lightmaps via daMesh->TexN->lpBits
				// size are daMesh->TexN->RawSizeX and daMesh->TexN->RawSizeY

				// uv

				sprintf(temp,"%d UVs\n",daPatch->nbTexCoords[i]);
				fputs(temp,fp);

				for (j=0;j<daPatch->nbTexCoords[i];j++)
				{
					sprintf(temp,"%5.4f %5.4f \n",daPatch->puv[i][j].u,daPatch->puv[i][j].v);
					fputs(temp,fp);
				}
			}

			// vertex 

			sprintf(temp,"%d Vertex\n",daPatch->nb2vert);
			fputs(temp,fp);

			for (i=0;i<daPatch->nb2vert;i++)
			{
				sprintf(temp,"%5.4f %5.4f %5.4f\n",daPatch->pv[i].x,daPatch->pv[i].y,daPatch->pv[i].z);
				fputs(temp,fp);
			}

			// opt & ctrl pt

			sprintf(temp,"%d Patches %d Ctrl pts %d Tesselate\n",daPatch->nb2patch,daPatch->nb2pt,daPatch->Tesselate);
			fputs(temp,fp);

			for (i=0;i<daPatch->nb2pt;i++)
			{
				sprintf(temp,"%d\n",daPatch->CtrlsPt[i]);
				fputs(temp,fp);
			}
		}

		// end !
		fclose(fp);
		return true;
	}

	return false;

}

CString CKIoTxt::GetName()
{
	return "Kapsul Desk Text IO";
}

CString CKIoTxt::GetInfos()
{
	return "Kapsul Desk Text IO";
}

CString CKIoTxt::GetFilter()
{
	return "*.ktx";
}

CString CKIoTxt::GetFileDescription()
{
	return "Kapsul Text file";
}

CString CKIoTxt::GetFileExtension()
{
	return ".ktx";
}

bool CKIoTxt::SupportReading()
{
	return true;
}

bool CKIoTxt::SupportWriting()
{
	return true;
}