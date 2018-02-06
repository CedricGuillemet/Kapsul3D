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

static char PluginName[]={"Nate BspConv IO"};
static char PluginInfos[]={"Nate BspConv IO IO"};
static char PluginFileDesc[]={"Nate BspConv file"};
static char PluginFilter[]={"*.geom"};

/*
    Exports symbols
*/

unsigned int __declspec(dllexport) Process(unsigned long Msg,unsigned long wParam,unsigned long lParam);
int  __declspec(dllexport)   Read(Desk *dk,char PathName[260]);
int  __declspec(dllexport)   Write(Desk *dk,char PathName[260]);

Desk *dk;

/*
    My functions
*/


int ReadGeom(char *Filename,Object *daObj)
{
	//KPolygon * &dap,Vertex * &dav,
	int nbPol,nbVert;
    char temp[512];
    float tmp1,tmp2,tmp3,tmp4,tmp5,tmp6,tmp7;
    int i,j;
    int ind,nbind;
	

    FILE *fp=fopen(Filename,"rt");
    if (fp!=NULL)
    {
        fgets(temp,512,fp);
        nbVert=atoi(temp);
        fgets(temp,512,fp);
        nbPol=atoi(temp);

        fgets(temp,512,fp);
        fgets(temp,512,fp);

		daObj->AllocatePoly(nbPol,nbVert);
		/*
        dap=new KPolygon[nbPol];
        dav=new Vertex[nbVert];
*/
        for (i=0;i<nbVert;i++)
        {
            fgets(temp,512,fp);
            sscanf(temp,"(%f %f) (%f %f) (%f %f %f)",&tmp1,&tmp2,&tmp3,&tmp4,&tmp5,&tmp6,&tmp7);
            daObj->pv[i]->vx=tmp5;
            daObj->pv[i]->vy=tmp7;
            daObj->pv[i]->vz=tmp6;
        }

        for (i=0;i<nbPol;i++)
        {
            fgets(temp,512,fp);
            sscanf(temp,"%d %d",&ind,&nbind);
            daObj->pl[i]->Allocate(0,nbind);
            for (j=0;j<nbind;j++)
            {
                daObj->pl[i]->nbvert[j]=ind+j;
            }
        }

        fclose(fp);
		return 1;
    }
	return 0;
}

void ReadLight(char *Filename)
{
	//,Light *dal,int &nbl

    char temp[512];
    int i,j;
    int v1,v2,v3;
    float f1=255,f2=128,f3=0;

//    nbl=-1;


    FILE *fp=fopen(Filename,"rt");
    if (fp!=NULL)
    {
        while (fgets(temp,512,fp)!=NULL)
        {
            if (temp[0]=='{')
            {
				dk->AddLight();
                //nbl++;
                dk->NextLight->r=255;
                dk->NextLight->g=255;
                dk->NextLight->b=255;
            }

            if (strstr(temp,"\"light\"")!=NULL)
            {
                sscanf(temp,"\"light\" \"%d\"",&v1);
                dk->NextLight->Radius=v1;

				dk->NextLight->Radius2=1;//0;//dal[i].Radius*0.10;
				dk->NextLight->tanRad1=tan((dk->NextLight->Radius*PI)/180.0f);
				dk->NextLight->tanRad2=tan((dk->NextLight->Radius2*PI)/180.0f);
				dk->NextLight->Type=0;
            }
            if (strstr(temp,"\"origin\"")!=NULL)
            {
                sscanf(temp,"\"origin\" \"%d %d %d\"",&v1,&v2,&v3);
                dk->NextLight->Source.vx=v1;
                dk->NextLight->Source.vy=v2;
                dk->NextLight->Source.vz=v3;
            }
            if (strstr(temp,"\"_color\"")!=NULL)
            {
                
                sscanf(temp,"\"_color\" \"%f %f %f\"",&f1,&f2,&f3);
                f1*=255.0f;
                f2*=255.0f;
                f3*=255.0f;
				f1=255;
				f2=255;
				f3=255;

                dk->NextLight->r=f1;
                dk->NextLight->g=f2;
                dk->NextLight->b=f3;
                
            }
        }
        fclose(fp);
    }
}


/*
bool LoadTxt(char *FileName)
{
	
	FILE *fp;
	Object *daObj;
	CLight *dalight;
	char temp[512];
	int i,j,k;
	int nbvert,nbpolys;
	int nBufSize=512;
	int counto,countl;


	fp=fopen(FileName,"rt");
	if (fp!=NULL)
	{
		// Objects

		//while(fgets(temp,nBufSize,fp)!=NULL)
		//{
		fgets(temp,nBufSize,fp);
		sscanf(temp,"%d Objects\n",&counto);
		fgets(temp,nBufSize,fp);
		sscanf(temp,"%d Lights\n",&countl);

		for (k=0;k<counto;k++)
		{
			// name


			dk->AddObject();
			daObj=dk->NextObject;

			fgets(temp,nBufSize,fp);
			sscanf(temp,"Object %s\n",daObj->Name);

			// vertex 
			fgets(temp,nBufSize,fp);
			sscanf(temp,"%d Vertex\n",&nbvert);
			daObj->Allocate(0,nbvert);
			for (i=0;i<nbvert;i++)
			{
				fgets(temp,nBufSize,fp);
				sscanf(temp,"%f %f %f\n",&daObj->pv[i]->vx,&daObj->pv[i]->vy,&daObj->pv[i]->vz);
			}

			// uv

			fgets(temp,nBufSize,fp);
			sscanf(temp,"%d UVs\n",&nbvert);
			daObj->AllocateUV(0,nbvert);
			for (i=0;i<nbvert;i++)
			{
				fgets(temp,nBufSize,fp);
				sscanf(temp,"%f %f\n",&daObj->puv[0][i]->u,&daObj->puv[0][i]->v);
			}


    		// faces
			fgets(temp,nBufSize,fp);
			sscanf(temp,"%d Polys\n",&nbvert);
			daObj->AllocatePoly(nbvert,0);
			for (i=0;i<nbvert;i++)
			{
				fgets(temp,nBufSize,fp);
				sscanf(temp,"%d\n",&nbpolys);
				daObj->pl[i]->Allocate(0,nbpolys);

				for (j=0;j<daObj->pl[i]->nb2vert;j++)
				{
					fgets(temp,nBufSize,fp);
					sscanf(temp,"I %d UV %d\n",&daObj->pl[i]->nbvert[j],&daObj->pl[i]->Tex[j]);
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
				sscanf(temp,"%f %f %f\n",&dalight->Source.vx,&dalight->Source.vy,&dalight->Source.vz);
				fgets(temp,nBufSize,fp);
				sscanf(temp,"%f \n",&dalight->Radius);
			}
			else
			{
				//spot
				fgets(temp,nBufSize,fp);
				sscanf(temp,"%f %f %f\n",&dalight->Source.vx,&dalight->Source.vy,&dalight->Source.vz);
				fgets(temp,nBufSize,fp);
				sscanf(temp,"%f %f %f\n",&dalight->Target.vx,&dalight->Target.vy,&dalight->Target.vz);
				fgets(temp,nBufSize,fp);
				sscanf(temp,"%f \n",&dalight->Radius);
			}

			fgets(temp,nBufSize,fp);
			sscanf(temp,"%d %d %d\n",&dalight->r,&dalight->g,&dalight->b);

		}
		// end !
		fclose(fp);
		return true;
	}

	return false;
}

*/
bool SaveTxt(char *FileName)
{
	/*
	FILE *fp;
	Object *daObj;
	CLight *dalight;
	char temp[512];
	int i,j,counto=0,countl=0;


	fp=fopen(FileName,"wt");
	if (fp!=NULL)
	{
		for (daObj=dk->FirstObject;daObj!=NULL;daObj=daObj->Next)
			counto++;
		for (dalight=dk->FirstLight;dalight!=NULL;dalight=dalight->Next)
			countl++;

		sprintf(temp,"%d Objects\n",counto);
		fputs(temp,fp);
		sprintf(temp,"%d Lights\n",countl);
		fputs(temp,fp);

		// Objects

		for (daObj=dk->FirstObject;daObj!=NULL;daObj=daObj->Next)
		{
			sprintf(temp,"Object %s\n",daObj->Name);
			fputs(temp,fp);

			// vertex 

			sprintf(temp,"%d Vertex\n",daObj->nb2vert);
			fputs(temp,fp);

			for (i=0;i<daObj->nb2vert;i++)
			{
				sprintf(temp,"%5.4f %5.4f %5.4f\n",daObj->pv[i]->vx,daObj->pv[i]->vy,daObj->pv[i]->vz);
				fputs(temp,fp);
			}

			// uv

			sprintf(temp,"%d UVs\n",daObj->nbTexCoords[0]);
			fputs(temp,fp);

			for (i=0;i<daObj->nbTexCoords[0];i++)
			{
				sprintf(temp,"%5.4f %5.4f \n",daObj->puv[0][i]->u,daObj->puv[0][i]->v);
				fputs(temp,fp);
			}

			// faces

			sprintf(temp,"%d Polys\n",daObj->nb2poly);
			fputs(temp,fp);

			for (i=0;i<daObj->nb2poly;i++)
			{
				sprintf(temp,"%d\n",daObj->pl[i]->nb2vert);
				fputs(temp,fp);
				for (j=0;j<daObj->pl[i]->nb2vert;j++)
				{
					sprintf(temp,"I %d UV %d\n",daObj->pl[i]->nbvert[j],daObj->pl[i]->Tex[j]);
					fputs(temp,fp);
				}
			}


		}
		// lights
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

		// end !
		fclose(fp);
		return true;
	}
*/
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
        value=0;
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
	dk->AddObject();
	ReadLight("q3dm17.light");
    return ReadGeom(PathName,dk->NextObject);
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


