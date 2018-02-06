/*

	IOIOkdk.CPP

*/

#include "stdafx.h"
#include "Kapsul3D.h"
#include "Headers.h"
#include <stdio.h>

#ifdef __cplusplus
    extern "C" {
#endif


/*
    constants
*/

static char PluginName[]={"Kapsul Desk Text IO"};
static char PluginInfos[]={"Kapsul Desk Text IO"};
static char PluginFileDesc[]={"Kapsul Text file"};
static char PluginFilter[]={"*.txt"};

COption *KOption;

/*
    Exports symbols
*/

unsigned int __declspec(dllexport) Process(unsigned long Msg,unsigned long wParam,unsigned long lParam);
int  __declspec(dllexport)   Read(Desk *dk,char PathName[260]);
int  __declspec(dllexport)   Write(Desk *dk,char PathName[260]);

Desk *dk;
Skeletton *CurSkel;
char temp[512],temp2[512];
int nBufSize=512;
float v1,v2,v3;

/*
    My functions
*/

bool GetFullPath(char *FileName)
{

	char temp[512];
	FILE *fp;

	GetCurrentDirectory(512,temp);
	if (temp[strlen(temp)-1]!='\\')
		strcat(temp,"\\");

	strcat(temp,FileName);

	fp=fopen(temp,"rb");
	if (fp!=NULL)
	{
		fclose(fp);
		strcpy(FileName,temp);
		return true;
	}

    for (int i=0;i<KOption->GetnbMapDir();i++)
    {
        strcpy(temp,KOption->GetMapDir(i));
		if ((temp[strlen(temp)-1])!='\\')
			strcat(temp,"\\");

		strcat(temp,FileName);

		fp=fopen(temp,"rb");
		if (fp!=NULL)
		{
			fclose(fp);
			strcpy(FileName,temp);
			return true;
		}
    }
	return false;
}


void ReadBone(Bone *daBone,FILE *fp)
{
	
	
	sscanf(temp,"%s \n",daBone->Name);

	fgets(temp,nBufSize,fp);
	sscanf(temp,"%f %f %f\n",&v1,&v2,&v3);
	daBone->Pos.vx=v1;
	daBone->Pos.vy=v2;
	daBone->Pos.vz=v3;
	
	fgets(temp,nBufSize,fp); // weights {
	fgets(temp,nBufSize,fp); 
	while(strcmp(temp,"}\n")!=0)
	{
		
		float weight;
		int ind;
		sscanf(temp,"%d %5.4f \n",&ind,&weight);
		daBone->AddVert(&CurSkel->daObj->pv[ind],ind,weight);

		fgets(temp,nBufSize,fp); // weights {
	}

	fgets(temp,nBufSize,fp);
	while (strcmp(temp,"End\n")!=0)
	{
		Bone *dab=CurSkel->AddBone(daBone);
		ReadBone(dab,fp);
		fgets(temp,nBufSize,fp);
	}
}

bool LoadTxt(char *FileName)
{
	FILE *fp;
	Object *daObj;
	CLight *dalight;
	Camera *dacam;
	int i,j,k,l,m;
	int nbvert,nbpolys;
	int counto,countl,countc,counte,counts,countp,counten,countsh;


	KOption=(COption*)GetGOption();

	fp=fopen(FileName,"rt");
	if (fp!=NULL)
	{
		// Objects

		//while(fgets(temp,nBufSize,fp)!=NULL)
		//{
		fgets(temp,nBufSize,fp);
		if (strcmp(temp,"Kapsul Text Export\n")!=NULL)
		{
			fclose(fp);
			return false;
		}

		fgets(temp,nBufSize,fp);
		sscanf(temp,"%d Objects\n",&counto);
		fgets(temp,nBufSize,fp);
		sscanf(temp,"%d Lights\n",&countl);
		fgets(temp,nBufSize,fp);
		sscanf(temp,"%d Cameras\n",&countc);
		fgets(temp,nBufSize,fp);
		sscanf(temp,"%d Skelettons\n",&counts);
		fgets(temp,nBufSize,fp);
		sscanf(temp,"%d Emitter\n",&counte);
		fgets(temp,nBufSize,fp);
		sscanf(temp,"%d Patches\n",&countp);
		fgets(temp,nBufSize,fp);
		sscanf(temp,"%d Entities\n",&counten);
		fgets(temp,nBufSize,fp);
		sscanf(temp,"%d Shapes\n",&countsh);

		for (k=0;k<counto;k++)
		{
			// name


			dk->AddObject();
			daObj=dk->NextObject;

			fgets(temp,nBufSize,fp);
			sscanf(temp,"Object %s\n",daObj->Name);

			fgets(temp,nBufSize,fp);
			sscanf(temp,"Prop 0x%x\n",&daObj->Property1);

			// textures canals
			fgets(temp,nBufSize,fp);
			sscanf(temp,"%d Canals\n",&m/*daObj->nbTexCanals*/);
			

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
						GetFullPath(temp2);
						dk->AddTex(temp2);
						strcpy(daObj->TexName1,temp2);
						daObj->Tex1=dk->NextTexture;
						daObj->Tex1->Type=TEXTURE_FILE;
					}
					break;
				case 1:
					sscanf(temp,"Tex %s ",temp2);
					GetFullPath(temp2);
					dk->AddTex(temp2);
					strcpy(daObj->TexName2,temp2);
					daObj->Tex2=dk->NextTexture;
					daObj->Tex2->Type=TEXTURE_FILE;
					break;
				case 2:
					sscanf(temp,"Tex %s ",temp2);
					GetFullPath(temp2);
					dk->AddTex(temp2);
					strcpy(daObj->TexName3,temp2);
					daObj->Tex3=dk->NextTexture;
					daObj->Tex3->Type=TEXTURE_FILE;
					break;
				case 3:
					sscanf(temp,"Tex %s ",temp2);
					GetFullPath(temp2);
					dk->AddTex(temp2);
					strcpy(daObj->TexName4,temp2);
					daObj->Tex4=dk->NextTexture;
					daObj->Tex4->Type=TEXTURE_FILE;
					break;
				}
				

				// uv
				fgets(temp,nBufSize,fp);
				sscanf(temp,"%d UVs\n",&l);
				daObj->AllocateUV(i,l);
				

				for (j=0;j<daObj->nbTexCoords[i];j++)
				{
					fgets(temp,nBufSize,fp);
					sscanf(temp,"%f %f",&v1,&v2);
					daObj->puv[i][j].u=v1;
					daObj->puv[i][j].v=v2;
				}

			}

			// vertex 
			fgets(temp,nBufSize,fp);
			sscanf(temp,"%d Vertex\n",&nbvert);
			daObj->AllocatePoly(0,nbvert);
			for (i=0;i<nbvert;i++)
			{
				fgets(temp,nBufSize,fp);
				sscanf(temp,"%f %f %f\n",&v1,&v2,&v3);
				daObj->pv[i].vx=v1;
				daObj->pv[i].vy=v2;
				daObj->pv[i].vz=v3;
			}

    		// faces
			fgets(temp,nBufSize,fp);
			sscanf(temp,"%d Polys\n",&nbvert);
			daObj->AllocatePoly(nbvert,0);
			for (i=0;i<nbvert;i++)
			{
				fgets(temp,nBufSize,fp);
				sscanf(temp,"%d\n",&nbpolys);

				//for (j=0;j<daObj->nbTexCanals;j++)
				daObj->pl[i].Allocate(daObj->nbTexCanals,nbpolys);

				for (j=0;j<daObj->pl[i].nb2vert;j++)
				{
					fgets(temp,nBufSize,fp);

					switch(daObj->nbTexCanals)
					{
					case 1:
						sscanf(temp,"I %d UV %d\n",&daObj->pl[i].nbvert[j],&daObj->pl[i].Tex[0][j]);
						break;
					case 2:
						sscanf(temp,"I %d UV %d %d\n",&daObj->pl[i].nbvert[j],&daObj->pl[i].Tex[0][j],&daObj->pl[i].Tex[1][j]);
						break;
					case 3:
						sscanf(temp,"I %d UV %d %d %d\n",&daObj->pl[i].nbvert[j],&daObj->pl[i].Tex[0][j],&daObj->pl[i].Tex[1][j],&daObj->pl[i].Tex[2][j]);
						break;
					case 4:
						sscanf(temp,"I %d UV %d %d %d %d\n",&daObj->pl[i].nbvert[j],&daObj->pl[i].Tex[0][j],&daObj->pl[i].Tex[1][j],&daObj->pl[i].Tex[2][j],&daObj->pl[i].Tex[3][j]);
						break;
					}
					//sscanf(temp,"I %d UV %d\n",&daObj->pl[i]->nbvert[j],&daObj->pl[i]->Tex[0][j]);
				}
			}
		}
		// lights
		for (k=0;k<countl;k++)
		{
			// name


			dk->AddLight();
			dalight=dk->NextLight;

			fgets(temp,nBufSize,fp);
			sscanf(temp,"Light %s\n",&dalight->Name);
				
			fgets(temp,nBufSize,fp);
			sscanf(temp,"Type %d\n",&dalight->Type);

			if (dalight->Type==0)
			{
				//omni
				fgets(temp,nBufSize,fp);
				sscanf(temp,"%f %f %f\n",&v1,&v2,&v3);
				dalight->Source.vx=v1;
				dalight->Source.vy=v2;
				dalight->Source.vz=v3;
			}
			else
			{
				//spot
				fgets(temp,nBufSize,fp);
				sscanf(temp,"%f %f %f\n",&v1,&v2,&v3);
				dalight->Source.vx=v1;
				dalight->Source.vy=v2;
				dalight->Source.vz=v3;
				fgets(temp,nBufSize,fp);
				sscanf(temp,"%f %f %f\n",&v1,&v2,&v3);
				dalight->Target.vx=v1;
				dalight->Target.vy=v2;
				dalight->Target.vz=v3;
			}
			fgets(temp,nBufSize,fp);
			sscanf(temp,"%f \n",&v1);
			dalight->Radius=v1;

			fgets(temp,nBufSize,fp);
			sscanf(temp,"%d %d %d\n",&dalight->r,&dalight->g,&dalight->b);

		}
		// Camera
		for (k=0;k<countc;k++)
		{
			dk->AddCam();
			dacam=dk->NextCam;

			fgets(temp,nBufSize,fp);
			sscanf(temp,"Camera %s\n",dacam->Name);
				
			fgets(temp,nBufSize,fp);
			sscanf(temp,"%f %f %f\n",&v1,&v2,&v3);
			dacam->Source.vx=v1;
			dacam->Source.vy=v2;
			dacam->Source.vz=v3;
			fgets(temp,nBufSize,fp);
			sscanf(temp,"%f %f %f\n",&v1,&v2,&v3);
			dacam->Dest.vx=v1;
			dacam->Dest.vy=v2;
			dacam->Dest.vz=v3;
			
			fgets(temp,nBufSize,fp);
			sscanf(temp,"%f \n",&v1);
			dacam->Fov=v1;

			fgets(temp,nBufSize,fp);
			sscanf(temp,"%d %d \n",&dacam->ResoX,&dacam->ResoY);
		}
		// -- Skeletton -------------------------------------------------------

		for (k=0;k<counts;k++)
		{
			dk->AddSkel();
			CurSkel=dk->NextSkel;
            // -- Name et Link Name --------------------------------------------
			fgets(temp,nBufSize,fp);
            sscanf(temp,"Skeletton %s\n",CurSkel->Name);
			fgets(temp,nBufSize,fp);
            sscanf(temp,"Link with %s\n",CurSkel->ObjName);
			CurSkel->daObj=(Object*)dk->GetByName(CurSkel->ObjName,PLUGIN_OBJECT);
			

            // -- Bones --------------------------------------------------------
			/*
			fgets(temp,nBufSize,fp);
			sscanf(temp,"%s \n",CurSkel->bone->Name);
*/
			fgets(temp,nBufSize,fp);
			sscanf(temp,"%f %f %f\n",&v1,&v2,&v3);
			CurSkel->RootPos.vx=v1;
			CurSkel->RootPos.vy=v2;
			CurSkel->RootPos.vz=v3;
			
			//for (Bone *daBone=daSkel->bone->FirstBone;daBone!=NULL;daBone=daBone->Next)
			CurSkel->AddBone(NULL);
			fgets(temp,nBufSize,fp);
			ReadBone(CurSkel->bone,fp);
			CurSkel->BuildBase();

			//fputs("End\n",fp);	
        }

		// -- Shape -----------------------------------------------------------------

		for (k=0;k<countsh;k++)
		{
			int countseg;
			Shape *CurShape=dk->AddShape();
			fgets(temp,nBufSize,fp);
            sscanf(temp,"Shape %s\n",CurShape->Name);

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
		// end !
		fclose(fp);
		return true;
	}

	return false;
}


void WriteBone(Bone *daBone,FILE *fp)
{
	sprintf(temp,"%s \n",daBone->Name);
	fputs(temp,fp);

	sprintf(temp,"%5.4f %5.4f %5.4f\n",daBone->Pos.vx,daBone->Pos.vy,daBone->Pos.vz);
	fputs(temp,fp);

	// Attach list
	fputs("Weights {\n",fp);
	for (BoneAttach *daBA=daBone->FirstBA;daBA!=NULL;daBA=daBA->Next)
	{
		sprintf(temp,"%d %5.4f \n",daBA->OriginIndex,daBA->Weight);
		fputs(temp,fp);
	}
	fputs("}\n",fp);
	// recurse bone
	for (Bone *daBone2=daBone->FirstBone;daBone2!=NULL;daBone2=daBone2->Next)
        WriteBone(daBone2,fp);

	fputs("End\n",fp);
}

bool SaveTxt(char *FileName)
{
	FILE *fp;
	Object *daObj;
	CLight *dalight;
	Camera *dacam;
	Skeletton *daSkel;
	Shape *daShp;

	char temp[512],temp2[512];
	int i,j;//,counto=0,countl=0,countc=0;
	int counto=0,countl=0,countc=0,counte=0,counts=0,countp=0,counten=0,countsh=0;


	fp=fopen(FileName,"wt");
	if (fp!=NULL)
	{
		for (daObj=dk->FirstObject;daObj!=NULL;daObj=daObj->Next)
			counto++;
		for (dalight=dk->FirstLight;dalight!=NULL;dalight=dalight->Next)
			countl++;
		for (dacam=dk->FirstCam;dacam!=NULL;dacam=dacam->Next)
			countc++;
		for (daSkel=dk->FirstSkel;daSkel!=NULL;daSkel=daSkel->Next)
			counts++;
		for (daShp=dk->FirstShape;daShp!=NULL;daShp=daShp->Next)
			countsh++;

		fputs("Kapsul Text Export\n",fp);

		sprintf(temp,"%d Objects\n",counto);
		fputs(temp,fp);
		sprintf(temp,"%d Lights\n",countl);
		fputs(temp,fp);
		sprintf(temp,"%d Cameras\n",countc);
		fputs(temp,fp);
		sprintf(temp,"%d Skelettons\n",counts);
		fputs(temp,fp);
		sprintf(temp,"%d Emitter\n",counte);
		fputs(temp,fp);
		sprintf(temp,"%d Patches\n",countp);
		fputs(temp,fp);
		sprintf(temp,"%d Entities\n",counten);
		fputs(temp,fp);
		sprintf(temp,"%d Shapes\n",countsh);
		fputs(temp,fp);

		// -- Objects ---------------------------------------------------------

		for (daObj=dk->FirstObject;daObj!=NULL;daObj=daObj->Next)
		{
			sprintf(temp,"Object %s\n",daObj->Name);
			fputs(temp,fp);

			sprintf(temp,"Prop 0x%x\n",daObj->Property1);
			fputs(temp,fp);
			// textures canals

			sprintf(temp,"%d Canals\n",daObj->nbTexCanals);
			fputs(temp,fp);

			for (i=0;i<daObj->nbTexCanals;i++)
			{
				switch(i)
				{
				case 0:
					strcpy(temp2,daObj->Tex1->FileName);
					break;
				case 1:
					strcpy(temp2,daObj->Tex2->FileName);
					break;
				case 2:
					strcpy(temp2,daObj->Tex3->FileName);
					break;
				case 3:
					strcpy(temp2,daObj->Tex4->FileName);
					break;
				}
				char temp3[MAX_PATH],temp4[MAX_PATH];
				_splitpath(temp2,NULL,NULL,temp3,temp4);
				strcat(temp3,temp4);
				sprintf(temp,"Tex %s \n",temp3);

				fputs(temp,fp);

				// NB
				// Access lightmaps via daObj->TexN->lpBits
				// size are daObj->TexN->RawSizeX and daObj->TexN->RawSizeY

				// uv

				sprintf(temp,"%d UVs\n",daObj->nbTexCoords[i]);
				fputs(temp,fp);

				for (j=0;j<daObj->nbTexCoords[i];j++)
				{
					sprintf(temp,"%5.4f %5.4f \n",daObj->puv[i][j].u,daObj->puv[i][j].v);
					fputs(temp,fp);
				}

			}

			// vertex 

			sprintf(temp,"%d Vertex\n",daObj->nb2vert);
			fputs(temp,fp);

			for (i=0;i<daObj->nb2vert;i++)
			{
				sprintf(temp,"%5.4f %5.4f %5.4f\n",daObj->pv[i].vx,daObj->pv[i].vy,daObj->pv[i].vz);
				fputs(temp,fp);
			}

			// faces

			sprintf(temp,"%d Polys\n",daObj->nb2poly);
			fputs(temp,fp);

			for (i=0;i<daObj->nb2poly;i++)
			{
				sprintf(temp,"%d\n",daObj->pl[i].nb2vert);
				fputs(temp,fp);
				for (j=0;j<daObj->pl[i].nb2vert;j++)
				{
					switch(daObj->nbTexCanals)
					{
					case 1:
						sprintf(temp,"I %d UV %d\n",daObj->pl[i].nbvert[j],daObj->pl[i].Tex[0][j]);
						break;
					case 2:
						sprintf(temp,"I %d UV %d %d\n",daObj->pl[i].nbvert[j],daObj->pl[i].Tex[0][j],daObj->pl[i].Tex[1][j]);
						break;
					case 3:
						sprintf(temp,"I %d UV %d %d %d\n",daObj->pl[i].nbvert[j],daObj->pl[i].Tex[0][j],daObj->pl[i].Tex[1][j],daObj->pl[i].Tex[2][j]);
						break;
					case 4:
						sprintf(temp,"I %d UV %d %d %d %d\n",daObj->pl[i].nbvert[j],daObj->pl[i].Tex[0][j],daObj->pl[i].Tex[1][j],daObj->pl[i].Tex[2][j],daObj->pl[i].Tex[3][j]);
						break;
					}
					
					fputs(temp,fp);
				}
			}


		}

		// -- lights ----------------------------------------------------------

		for (dalight=dk->FirstLight;dalight!=NULL;dalight=dalight->Next)
		{
			sprintf(temp,"Light %s\n",dalight->Name);
			fputs(temp,fp);

			sprintf(temp,"Type %d\n",dalight->Type);
			fputs(temp,fp);

			if (dalight->Type==0)
			{
				//omni
				sprintf(temp,"%5.4f %5.4f %5.4f\n",dalight->Source.vx,dalight->Source.vy,dalight->Source.vz);
				fputs(temp,fp);
				sprintf(temp,"%5.4f \n",dalight->Radius);
				fputs(temp,fp);
			}
			else
			{
				//spot
				sprintf(temp,"%5.2f %5.2f %5.2f\n",dalight->Source.vx,dalight->Source.vy,dalight->Source.vz);
				fputs(temp,fp);
				sprintf(temp,"%5.2f %5.2f %5.2f\n",dalight->Target.vx,dalight->Target.vy,dalight->Target.vz);
				fputs(temp,fp);
				sprintf(temp,"%5.2f \n",dalight->Radius);
				fputs(temp,fp);
			}

			sprintf(temp,"%d %d %d\n",dalight->r,dalight->g,dalight->b);
			fputs(temp,fp);
		}

		// -- Camera ----------------------------------------------------------

		for (dacam=dk->FirstCam;dacam!=NULL;dacam=dacam->Next)
		{
			sprintf(temp,"Camera %s\n",dacam->Name);
			fputs(temp,fp);				

			sprintf(temp,"%f %f %f\n",dacam->Source.vx,dacam->Source.vy,dacam->Source.vz);
			fputs(temp,fp);

			sprintf(temp,"%f %f %f\n",dacam->Dest.vx,dacam->Dest.vy,dacam->Dest.vz);
			fputs(temp,fp);

			sprintf(temp,"%f \n",dacam->Fov);
			fputs(temp,fp);

			sprintf(temp,"%d %d \n",dacam->ResoX,dacam->ResoY);
			fputs(temp,fp);
		}

		// -- Skeletton -------------------------------------------------------

		for (daSkel=dk->FirstSkel;daSkel!=NULL;daSkel=daSkel->Next)
		{
            // -- Name et Link Name --------------------------------------------

            sprintf(temp,"Skeletton %s\n",daSkel->Name);
			fputs(temp,fp);
            sprintf(temp,"Link with %s\n",daSkel->ObjName);
			fputs(temp,fp);

            // -- Bones --------------------------------------------------------
			sprintf(temp,"%5.4f %5.4f %5.4f\n",daSkel->RootPos.vx,daSkel->RootPos.vy,daSkel->RootPos.vz);
			fputs(temp,fp);

			WriteBone(daSkel->bone,fp);

			fputs("End\n",fp);	
        }

		// -- Shape -----------------------------------------------------------

		Segment *daSeg;
		for (daShp=dk->FirstShape;daShp!=NULL;daShp=daShp->Next)
		{
            sprintf(temp,"Shape %s\n",daShp->Name);
			fputs(temp,fp);
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
				sprintf(temp,"%5.4f %5.4f %5.4f\n",daSeg->Dot.vx,daSeg->Dot.vy,daSeg->Dot.vz);
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

		// end !
		fclose(fp);
		return true;
	}

	return false;

}
/*
    Process message handler
*/

unsigned int __declspec(dllexport) Process(unsigned long Msg,unsigned long wParam,unsigned long lParam)
{
    unsigned int value=0;

    switch (Msg)
    {
    case KM_OPEN:
        break;
    case KM_CLOSE:
        break;
    case KM_GETNAME:
        value=(unsigned int)&PluginName;
        break;
    case KM_GETINFOS:
        value=(unsigned int)&PluginInfos;
        break;
    case KM_GETTYPE:
        value=PLUGIN_FILE;
        break;
    case KM_GETSECONDARYTYPE:
        value=0;
        break;
    case KM_GETFILTER:
        value=(unsigned int)&PluginFilter;
        break;
    case KM_GETFILEDESC:
        value=(unsigned int)&PluginFileDesc;
        break;
    case KM_GETREADSUPPORT:
        value=1;
        break;
    case KM_GETWRITESUPPORT:
        value=1;
        break;
    case KM_WRITEFILE:
        value=Write((Desk*)wParam,(char*)lParam);
        break;
    case KM_READFILE:
        value=Read((Desk*)wParam,(char*)lParam);
        break;

    }

    return value;
}

/*
    Process Read and Write
*/

int  __declspec(dllexport)   Read(Desk *dadk,char PathName[260])
{
    // Process here you read operation
    dk=dadk;
    return LoadTxt(PathName);
}

int  __declspec(dllexport)   Write(Desk *dadk,char PathName[260])
{
    // Process here you write operation
    dk=dadk;
    return SaveTxt(PathName);
}

#ifdef __cplusplus
    }
#endif

/*
    DLL entrypoint
*/

class CPluginApp : public CWinApp
{
public:
	CPluginApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKoreApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CKoreApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CPluginApp, CWinApp)
	//{{AFX_MSG_MAP(CPluginApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKoreApp construction

CPluginApp theApp;

CPluginApp::CPluginApp()
{
}

BOOL CPluginApp::InitInstance() 
{
	return CWinApp::InitInstance();
}


