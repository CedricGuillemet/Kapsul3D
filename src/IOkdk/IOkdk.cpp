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

static char PluginName[]={"Kapsul Desk IO"};
static char PluginInfos[]={"Kapsul Desk IO"};
static char PluginFileDesc[]={"Kapsul Desk"};
static char PluginFilter[]={"*.kdk"};

/*
    Exports symbols
*/

unsigned int __declspec(dllexport) Process(unsigned long Msg,unsigned long wParam,unsigned long lParam);
int  __declspec(dllexport)   Read(Desk *dk,char PathName[260]);
int  __declspec(dllexport)   Write(Desk *dk,char PathName[260]);

/*
    My functions
*/

enum {
    KDK_MAIN        = 0xFFFF0001,
    KDK_OBJECT      = 0xFFFF0010,

    KDK_VERTEX      = 0xFFFF0020,
    KDK_FACE        = 0xFFFF0028,

    KDK_NAME        = 0xFFFF0030,
    KDK_LINKNAME    = 0xFFFF0031,

    KDK_PATH        = 0xFFFF0040,

    KDK_PATHSCALE   = 0xFFFF0041,
    KDK_PATHFIT     = 0xFFFF0042,
    KDK_PATHTWIST   = 0xFFFF0043,
    KDK_PATHMAIN    = 0xFFFF0044,

    KDK_IK          = 0xFFFF0050,
    KDK_BONE        = 0xFFFF0058,
	KDK_BONEEND     = 0xFFFF0088,
    KDK_IKATTACH    = 0xFFFF0059,
	KDK_IKATTACHEND = 0xFFFFFF62,

    KDK_POLY        = 0xFFFF0060,

    KDK_SEGMENTLIST = 0xFFFF0061,

    KDK_CAMERA      = 0xFFFF0070,
    KDK_CAMERAVAL   = 0xFFFF0071,

    KDK_EMITTER     = 0xFFFF0090,
    KDK_EMITTERVAL  = 0xFFFF0091,

    KDK_LIGHT       = 0xFFFF0100,
    KDK_LIGHTVAL    = 0xFFFF0111,

    KDK_SHAPE       = 0xFFFF0080,
    KDK_SEGMENTLOOP = 0xFFFF0081,
    KDK_SEGMENT     = 0xFFFF0082,
    KDK_ENDSEGMENT  = 0xFFFF0083,
    KDK_SHAPEVAL    = 0xFFFF0084,

    KDK_PRIVATE     = 0xFFFF0200,

    KDK_VIEW        = 0xFFFF0300

};

#define KDKNAMELENGTH 20

Object *CurObj;

typedef unsigned char  byte;
typedef unsigned short word;
typedef unsigned long  dword;

typedef signed char  sbyte;
typedef signed short sword;
typedef signed long  sdword;


FILE *KDKFil;
int CurrentChunk;
int CurrentMainChunk;
int CurrentMainSecChunk;
Desk *dk;
bool Selected;
int nb2objv;

bool KDKReadVertList(void);
bool KDKReadFaceList(void);
bool KDKReadName(void);
void KDKWriteBoneList(Skeletton *daSkel);
bool KDKWriteAttachList(Bone *kdkbone);
bool KDKReadAttachList(Bone *kdkbone);

bool KDKReadBoneList(void);
bool KDKReadLinkName(void);


bool LoadKdK(char FileName[260]);
bool SaveKdK(char FileName[260]);

//---------------------------------------------------------------------------


#define KDKWRITECHUNK fwrite(&CurrentChunk,sizeof(int),1,KDKFil);
#define KDKREADCHUNK fread(&CurrentChunk,sizeof(int),1,KDKFil);
#define KDKBACKCHUNK fseek(KDKFil,ftell(KDKFil)-4,SEEK_SET);



bool KdkWriteVert(Vertex vt)
{
	
	if (fwrite(&vt.vx,sizeof(double),1,KDKFil)!=1) return false;   
	if (fwrite(&vt.vy,sizeof(double),1,KDKFil)!=1) return false;   
	if (fwrite(&vt.vz,sizeof(double),1,KDKFil)!=1) return false;  
	/*
	if (fwrite(&vt.u,sizeof(double),1,KDKFil)!=1) return false;    
	if (fwrite(&vt.v,sizeof(double),1,KDKFil)!=1) return false;    
	*/
	if (fwrite(&vt.Selected,sizeof(char),1,KDKFil)!=1) return false;

	return true;
}

bool KdkReadVert(Vertex *vt)
{
	if (fread(&vt->vx,sizeof(double),1,KDKFil)!=1) return false;   
	if (fread(&vt->vy,sizeof(double),1,KDKFil)!=1) return false;   
	if (fread(&vt->vz,sizeof(double),1,KDKFil)!=1) return false;   
	/*
	if (fread(&vt->u,sizeof(double),1,KDKFil)!=1) return false;    
	if (fread(&vt->v,sizeof(double),1,KDKFil)!=1) return false;    
	*/
	if (fread(&vt->Selected,sizeof(char),1,KDKFil)!=1) return false;

	return true;
}

void KdkWriteView(Desk *dk)
{
    int CamNom;

	fwrite(&dk->FullScreen,sizeof(bool),1,KDKFil);
    fwrite(&dk->Active,sizeof(int),1,KDKFil);

    for (int i=0;i<4;i++)
    {
        if (dk->cam[i]!=NULL) 
            CamNom=1;
        else
            CamNom=0;

        fwrite(&CamNom,1,sizeof(int),KDKFil);

        if (CamNom!=0)
	        fwrite(dk->cam[i]->Name,20,1,KDKFil);

        KdkWriteVert(dk->ViewNg[i]);
        KdkWriteVert(dk->ViewPos[i]);
        KdkWriteVert(dk->ViewSize[i]);
        KdkWriteVert(dk->tmppos[i]);
        KdkWriteVert(dk->tmpViewSize[i]);
        KdkWriteVert(dk->TmpViewNg[i]);

	    //Vertex *ViewNg,*ViewPos,*ViewSize,*tmppos,*tmpViewSize,*TmpViewNg;
        fwrite(&dk->ViewStart[i].x,sizeof(int),1,KDKFil);
        fwrite(&dk->ViewStart[i].y,sizeof(int),1,KDKFil);
        fwrite(&dk->ViewEnd[i].x,sizeof(int),1,KDKFil);
        fwrite(&dk->ViewEnd[i].y,sizeof(int),1,KDKFil);

        //POINT *ViewStart,*ViewEnd;
        fwrite(&dk->ViewType[i],sizeof(int),1,KDKFil);
        //int *ViewType;
    }
    

}

void KdkReadView(Desk *dk)
{
    int CamNom;

	fread(&dk->FullScreen,sizeof(bool),1,KDKFil);
    fread(&dk->Active,sizeof(int),1,KDKFil);

    for (int i=0;i<4;i++)
    {

        fread(&CamNom,1,sizeof(int),KDKFil);

        if (CamNom!=0)
            fread(dk->cam[i]->Name,20,1,KDKFil);

        
	    //fread(dk->cam[i]->Name,20,1,KDKFil);

        KdkReadVert(&dk->ViewNg[i]);
        KdkReadVert(&dk->ViewPos[i]);
        KdkReadVert(&dk->ViewSize[i]);
        KdkReadVert(&dk->tmppos[i]);
        KdkReadVert(&dk->tmpViewSize[i]);
        KdkReadVert(&dk->TmpViewNg[i]);

	    //Vertex *ViewNg,*ViewPos,*ViewSize,*tmppos,*tmpViewSize,*TmpViewNg;
        fread(&dk->ViewStart[i].x,sizeof(int),1,KDKFil);
        fread(&dk->ViewStart[i].y,sizeof(int),1,KDKFil);
        fread(&dk->ViewEnd[i].x,sizeof(int),1,KDKFil);
        fread(&dk->ViewEnd[i].y,sizeof(int),1,KDKFil);

        //POINT *ViewStart,*ViewEnd;
        fread(&dk->ViewType[i],sizeof(int),1,KDKFil);
        //int *ViewType;
    }
    dk->ComputeSize();
}
/*
bool KdkReadEmitter(Emitter *daEmit)
{
    if (fread(&daEmit->flags,sizeof(long),1,KDKFil)!=1) return false;   

    KdkReadVert(&daEmit->pos);

    if (fread(&daEmit->yaw,sizeof(float),1,KDKFil)!=1) return false;   
    if (fread(&daEmit->yawVar,sizeof(float),1,KDKFil)!=1) return false;   
    if (fread(&daEmit->pitch,sizeof(float),1,KDKFil)!=1) return false;   
    if (fread(&daEmit->pitchVar,sizeof(float),1,KDKFil)!=1) return false;   
    if (fread(&daEmit->speed,sizeof(float),1,KDKFil)!=1) return false;   
    if (fread(&daEmit->speedVar,sizeof(float),1,KDKFil)!=1) return false;  
    
    if (fread(&daEmit->totalParticles,sizeof(int),1,KDKFil)!=1) return false;   
    if (fread(&daEmit->particleCount,sizeof(int),1,KDKFil)!=1) return false;   
    if (fread(&daEmit->emitsPerFrame,sizeof(int),1,KDKFil)!=1) return false;   
    if (fread(&daEmit->emitVar,sizeof(int),1,KDKFil)!=1) return false;   
    if (fread(&daEmit->life,sizeof(int),1,KDKFil)!=1) return false;   
    if (fread(&daEmit->lifeVar,sizeof(int),1,KDKFil)!=1) return false;
    
    KdkReadVert(&daEmit->force);

    if (fread(&daEmit->Selected,sizeof(bool),1,KDKFil)!=1) return false;   

    return true;
}

bool KdkWriteEmitter(Emitter *daEmit)
{
    if (fwrite(&daEmit->flags,sizeof(long),1,KDKFil)!=1) return false;   

    KdkWriteVert(daEmit->pos);

    if (fwrite(&daEmit->yaw,sizeof(float),1,KDKFil)!=1) return false;   
    if (fwrite(&daEmit->yawVar,sizeof(float),1,KDKFil)!=1) return false;   
    if (fwrite(&daEmit->pitch,sizeof(float),1,KDKFil)!=1) return false;   
    if (fwrite(&daEmit->pitchVar,sizeof(float),1,KDKFil)!=1) return false;   
    if (fwrite(&daEmit->speed,sizeof(float),1,KDKFil)!=1) return false;   
    if (fwrite(&daEmit->speedVar,sizeof(float),1,KDKFil)!=1) return false;  
    
    if (fwrite(&daEmit->totalParticles,sizeof(int),1,KDKFil)!=1) return false;   
    if (fwrite(&daEmit->particleCount,sizeof(int),1,KDKFil)!=1) return false;   
    if (fwrite(&daEmit->emitsPerFrame,sizeof(int),1,KDKFil)!=1) return false;   
    if (fwrite(&daEmit->emitVar,sizeof(int),1,KDKFil)!=1) return false;   
    if (fwrite(&daEmit->life,sizeof(int),1,KDKFil)!=1) return false;   
    if (fwrite(&daEmit->lifeVar,sizeof(int),1,KDKFil)!=1) return false;
    
    KdkWriteVert(daEmit->force);

    if (fwrite(&daEmit->Selected,sizeof(bool),1,KDKFil)!=1) return false;   

    return true;

}
*/
bool KdkWriteLight(CLight *daLight)
{
    KdkWriteVert(daLight->Source);
    KdkWriteVert(daLight->Target);

    if (fwrite(&daLight->Type,sizeof(int),1,KDKFil)!=1) return false;   
    if (fwrite(&daLight->SpotType,sizeof(int),1,KDKFil)!=1) return false;

    if (fwrite(&daLight->Radius,sizeof(double),1,KDKFil)!=1) return false;
    if (fwrite(&daLight->TopWidth,sizeof(double),1,KDKFil)!=1) return false;
    if (fwrite(&daLight->TopHeight,sizeof(double),1,KDKFil)!=1) return false;
    if (fwrite(&daLight->BottomWidth,sizeof(double),1,KDKFil)!=1) return false;
    if (fwrite(&daLight->BottomHeight,sizeof(double),1,KDKFil)!=1) return false;

    if (fwrite(&daLight->Selected,sizeof(bool),1,KDKFil)!=1) return false;   

    if (fwrite(&daLight->r,sizeof(unsigned char),1,KDKFil)!=1) return false;   
    if (fwrite(&daLight->g,sizeof(unsigned char),1,KDKFil)!=1) return false;   
    if (fwrite(&daLight->b,sizeof(unsigned char),1,KDKFil)!=1) return false;   

    if (fwrite(&daLight->Brightness,sizeof(unsigned char),1,KDKFil)!=1) return false;   

    return true;
}

bool KdkReadLight(CLight *daLight)
{
    KdkReadVert(&daLight->Source);
    KdkReadVert(&daLight->Target);

    if (fread(&daLight->Type,sizeof(int),1,KDKFil)!=1) return false;   
    if (fread(&daLight->SpotType,sizeof(int),1,KDKFil)!=1) return false;

    if (fread(&daLight->Radius,sizeof(double),1,KDKFil)!=1) return false;
    if (fread(&daLight->TopWidth,sizeof(double),1,KDKFil)!=1) return false;
    if (fread(&daLight->TopHeight,sizeof(double),1,KDKFil)!=1) return false;
    if (fread(&daLight->BottomWidth,sizeof(double),1,KDKFil)!=1) return false;
    if (fread(&daLight->BottomHeight,sizeof(double),1,KDKFil)!=1) return false;

    if (fread(&daLight->Selected,sizeof(bool),1,KDKFil)!=1) return false;   

    if (fread(&daLight->r,sizeof(unsigned char),1,KDKFil)!=1) return false;   
    if (fread(&daLight->g,sizeof(unsigned char),1,KDKFil)!=1) return false;   
    if (fread(&daLight->b,sizeof(unsigned char),1,KDKFil)!=1) return false;   

    if (fread(&daLight->Brightness,sizeof(unsigned char),1,KDKFil)!=1) return false;   

    return true;
}

bool KdkWriteCamera(Camera *daCam)
{
    KdkWriteVert(daCam->Source);
    KdkWriteVert(daCam->Dest);
    KdkWriteVert(daCam->newpos);

    if (fwrite(&daCam->Length,sizeof(double),1,KDKFil)!=1) return false;
    if (fwrite(&daCam->Fov,sizeof(double),1,KDKFil)!=1) return false;
    
    if (fwrite(&daCam->Selected,sizeof(bool),1,KDKFil)!=1) return false;   
    if (fwrite(&daCam->SrcSelected,sizeof(bool),1,KDKFil)!=1) return false;   
    if (fwrite(&daCam->DstSelected,sizeof(bool),1,KDKFil)!=1) return false;   

    if (fwrite(&daCam->angle_a,sizeof(float),1,KDKFil)!=1) return false;   
    if (fwrite(&daCam->angle_b,sizeof(float),1,KDKFil)!=1) return false;   
    if (fwrite(&daCam->old_angle_a,sizeof(float),1,KDKFil)!=1) return false;   
    if (fwrite(&daCam->old_angle_b,sizeof(float),1,KDKFil)!=1) return false;   
    if (fwrite(&daCam->m_speed,sizeof(float),1,KDKFil)!=1) return false;   

    if (fwrite(&daCam->ResoX,sizeof(int),1,KDKFil)!=1) return false;   
    if (fwrite(&daCam->ResoY,sizeof(int),1,KDKFil)!=1) return false;   
    if (fwrite(&daCam->OldMx,sizeof(int),1,KDKFil)!=1) return false;   
    if (fwrite(&daCam->OldMy,sizeof(int),1,KDKFil)!=1) return false;   

    if (fwrite(&daCam->p,sizeof(POINT),1,KDKFil)!=1) return false;   

    return true;
}

bool KdkReadCamera(Camera *daCam)
{
    KdkReadVert(&daCam->Source);
    KdkReadVert(&daCam->Dest);
    KdkReadVert(&daCam->newpos);

    if (fread(&daCam->Length,sizeof(double),1,KDKFil)!=1) return false;
    if (fread(&daCam->Fov,sizeof(double),1,KDKFil)!=1) return false;
    
    if (fread(&daCam->Selected,sizeof(bool),1,KDKFil)!=1) return false;   
    if (fread(&daCam->SrcSelected,sizeof(bool),1,KDKFil)!=1) return false;   
    if (fread(&daCam->DstSelected,sizeof(bool),1,KDKFil)!=1) return false;   

    if (fread(&daCam->angle_a,sizeof(float),1,KDKFil)!=1) return false;   
    if (fread(&daCam->angle_b,sizeof(float),1,KDKFil)!=1) return false;   
    if (fread(&daCam->old_angle_a,sizeof(float),1,KDKFil)!=1) return false;   
    if (fread(&daCam->old_angle_b,sizeof(float),1,KDKFil)!=1) return false;   
    if (fread(&daCam->m_speed,sizeof(float),1,KDKFil)!=1) return false;   

    if (fread(&daCam->ResoX,sizeof(int),1,KDKFil)!=1) return false;   
    if (fread(&daCam->ResoY,sizeof(int),1,KDKFil)!=1) return false;   
    if (fread(&daCam->OldMx,sizeof(int),1,KDKFil)!=1) return false;   
    if (fread(&daCam->OldMy,sizeof(int),1,KDKFil)!=1) return false;   

    if (fread(&daCam->p,sizeof(POINT),1,KDKFil)!=1) return false;   

    return true;
}

bool KdkWriteSeg(Segment *daSeg,bool isLoop)
{
    unsigned char daLoop;

    CurrentChunk=KDK_SEGMENT;
    KDKWRITECHUNK

    daLoop=(isLoop? 0xff : 0x00);
    if (fwrite(&daSeg->Selected,sizeof(bool),1,KDKFil)!=1) return false;   
    
    KdkWriteVert(daSeg->Dot);

    if (fwrite(&daLoop,sizeof(unsigned char),1,KDKFil)!=1) return false;   

    return true;
}

unsigned char KdkReadSeg(Segment *daSeg)
{
    unsigned char daLoop;

    if (fread(&daSeg->Selected,sizeof(bool),1,KDKFil)!=1) return false;   
    
    KdkReadVert(&daSeg->Dot);

    if (fread(&daLoop,sizeof(unsigned char),1,KDKFil)!=1) return false;   

    return daLoop;
}

bool KdkWriteShape(Shape *daShape)
{
    char tmpch[KDKNAMELENGTH];
    Segment *daSeg;

    

    CurrentChunk=KDK_SHAPE;
    KDKWRITECHUNK

    CurrentChunk=KDK_NAME;
    KDKWRITECHUNK

    strcpy(tmpch,daShape->Name);
    if (fwrite(tmpch,sizeof(char),KDKNAMELENGTH,KDKFil)!=KDKNAMELENGTH) return false;

    CurrentChunk=KDK_SHAPEVAL;
    KDKWRITECHUNK

    if (fwrite(&daShape->Selected,sizeof(bool),1,KDKFil)!=1) return false;   

    daSeg=daShape->FirstSegment;

    while(daSeg!=NULL)
    {
        KdkWriteSeg(daSeg,(daSeg->Next==daShape->FirstSegment));

        daSeg=daSeg->Next;

        if (daSeg==daShape->FirstSegment) break;
    }

    CurrentChunk=KDK_ENDSEGMENT;
    KDKWRITECHUNK
    
    return true;
}

bool KdkReadShape(Shape *daShape)
{
    if (fread(&daShape->Selected,sizeof(bool),1,KDKFil)!=1) return false;   

    daShape->Selected=0; //MODIF

    KDKREADCHUNK

    while(CurrentChunk==KDK_SEGMENT)
    {
        daShape->AddSegment(Vertex(0,0,0));
        if (KdkReadSeg(daShape->NextSegment)==0xff)
            daShape->NextSegment->Next=daShape->FirstSegment;


        KDKREADCHUNK
    }
    return true;
}

void KdkWritePrivate(CPrivateData *pd)
{
    CurrentChunk=KDK_PRIVATE;
    KDKWRITECHUNK

    fwrite(pd->Name,sizeof(char),32,KDKFil);

    fwrite(&pd->AllocatedByte,sizeof(int),1,KDKFil);

    fwrite(pd->lpBits,1,pd->AllocatedByte,KDKFil);

}

void KdkReadPrivate(void)
{
    char tmpch[32];
    CPrivateData *pd;
    int AllocSize;

    fread(tmpch,sizeof(char),32,KDKFil);

    pd=dk->AddPrivate(tmpch);

    fread(&AllocSize,sizeof(int),1,KDKFil);

    pd->Allocate(AllocSize);

    fread(pd->lpBits,1,pd->AllocatedByte,KDKFil);
}

// -- KDK Load -----------------------------------------------------------------

bool LoadKdK(char FileName[260])
{

	glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();


    KDKFil=fopen(FileName,"rb");
    if (KDKFil!=NULL)
    {

        fread(&CurrentChunk,sizeof(int),1,KDKFil);
        if (CurrentChunk==KDK_MAIN)
        {
            while (fread(&CurrentChunk,sizeof(int),1,KDKFil)==1)
            {
                switch(CurrentChunk)
                {
                    // -- chunks primaires -----------------------------------------

                    case KDK_OBJECT:
                        CurrentMainChunk=KDK_OBJECT;
                        CurrentMainSecChunk=0;
                        (Desk*)dk->AddObject();
//						dk->NextObject->Mat=dk->FirstMat;
                        break;

                    case KDK_PATH:
                        CurrentMainChunk=KDK_PATH;
                        CurrentMainSecChunk=0;
                        dk->AddPath();
                        break;

                    case KDK_PATHSCALE:
                        CurrentMainChunk=KDK_PATHSCALE;
                        CurrentMainSecChunk=0;
                        break;

                    case KDK_PATHTWIST:
                        CurrentMainChunk=KDK_PATHTWIST;
                        CurrentMainSecChunk=0;
                        break;

                    case KDK_PATHFIT:
                        CurrentMainChunk=KDK_PATHFIT;
                        CurrentMainSecChunk=0;
                        break;

                    case KDK_IK:
                        CurrentMainChunk=KDK_IK;
                        CurrentMainSecChunk=0;
                        dk->AddSkel();
                        break;

                    case KDK_CAMERA:
                        CurrentMainChunk=KDK_CAMERA;
                        CurrentMainSecChunk=0;
                        dk->AddCam();
                        break;
                    case KDK_CAMERAVAL:
                        KdkReadCamera(dk->NextCam);
                        break;
                            /*
                    case KDK_EMITTER:
                        CurrentMainChunk=KDK_EMITTER;
                        dk->AddEmit();
                        break;

                    case KDK_EMITTERVAL:
                        KdkReadEmitter(dk->NextEmit);
                        break;
                        */
                    case KDK_LIGHT:
                        CurrentMainChunk=KDK_LIGHT;
                        CurrentMainSecChunk=0;
                        dk->AddLight();
                        break;
                    case KDK_LIGHTVAL:
                        KdkReadLight(dk->NextLight);
                        break;
                    case KDK_SHAPE:
                        CurrentMainChunk=KDK_SHAPE;
                        dk->AddShape();
                        break;

                    case KDK_PRIVATE:
                        KdkReadPrivate();
                        break;

                    case KDK_VIEW:
                        KdkReadView(dk);
                        break;

                    case KDK_SHAPEVAL:
                        KdkReadShape(dk->NextShape);
                        break;

                    // -- chunks secondaires -----------------------------------

                    case KDK_BONE:
                        CurrentMainSecChunk=KDK_BONE;
                        if (!KDKReadBoneList()) return false;
                        break;

                    // -- chunks tertiaires ------------------------------------

                    case KDK_VERTEX:
                        if (!KDKReadVertList()) return false;
                        break;

                    case KDK_FACE:
                        if (!KDKReadFaceList()) return false;
                        break;

                    case KDK_NAME:
                        if (!KDKReadName()) return false;
                        break;

                    case KDK_LINKNAME:
                        if (!KDKReadLinkName()) return false;
                        break;
/*
                    case KDK_BONE:
                        if (!KDKReadBoneList()) return false;
                        break;
*/
                    // -- chunk defaut -----------------------------------------

                    default:
                        //dk->NormalizeIKAttach();
                        fclose(KDKFil);
                        return false;
                }
            }

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    fclose(KDKFil);

    // -- Normalisation attach IK ----------------------------------------------
    //dk->NormalizeIKAttach();

    return true;

}


// -- KDK Save -----------------------------------------------------------------

bool SaveKdK(char FileName[260])
{
    int i,j,k;

    int nb2vertv;
    int nb2facev;
	/*
    int nb2segv;
    int nb2pathv;
    int nb2ikv;
*/
    char tmpch[KDKNAMELENGTH];

    long nbVertList;
    long nbFaceList;
//    long nbSegList;


    Object *daObj;

    KDKFil=fopen(FileName,"wb");
    if (KDKFil!=NULL)
    {

        // -- main chunk -------------------------------------------------------

        CurrentChunk=KDK_MAIN;
        KDKWRITECHUNK;

        // -- ecriture des objets ----------------------------------------------

        i=0;
        nb2objv=0;
        daObj=dk->FirstObject;

        while(daObj!=NULL)
        {
            nb2objv++;

            CurrentChunk=KDK_OBJECT;
            KDKWRITECHUNK

            CurrentChunk=KDK_NAME;
            KDKWRITECHUNK

            strcpy(tmpch,daObj->Name);
            if (fwrite(tmpch,sizeof(char),KDKNAMELENGTH,KDKFil)!=KDKNAMELENGTH) return false;

            // -- Vertex de l'objet ----------------------------------------

            CurrentChunk=KDK_VERTEX;
            KDKWRITECHUNK

            nbVertList=daObj->nb2vert;
            if (fwrite(&nbVertList,sizeof(long),1,KDKFil)!=1) return false;

            j=0;
            nb2vertv=0;

            while(nb2vertv<daObj->nb2vert)
            {
                if (daObj->pv[j]!=NULL)
                {
                    nb2vertv++;

                    KdkWriteVert((*daObj->pv[j]));
                }
                j++;

            }

            // -- Faces de l'objet -----------------------------------------

            CurrentChunk=KDK_FACE;
            KDKWRITECHUNK

            nbFaceList=daObj->nb2faces;
            if (fwrite(&nbFaceList,sizeof(long),1,KDKFil)!=1) return false;

            j=0;
            nb2facev=0;

            while(nb2facev<daObj->nb2faces)
            {
                if (daObj->pf[j]!=NULL)
                {
                    nb2facev++;

                    for (k=0;k<3;k++)
                    {
                        if (fwrite(&daObj->pf[j]->nbvert[k],sizeof(long),1,KDKFil)!=1) return false;
/*
                        if (fwrite(&daObj->pf[j]->u[k],sizeof(double),1,KDKFil)!=1) return false;
                        if (fwrite(&daObj->pf[j]->u[k],sizeof(double),1,KDKFil)!=1) return false;
*/
                    }

                    if (fwrite(&daObj->pf[j]->Selected,sizeof(bool),1,KDKFil)!=1) return false;

                }
                j++;

            }

            daObj=daObj->Next;
        }

        // -- IK ---------------------------------------------------------------

        i=0;
		Skeletton *dask;
		dask=dk->FirstSkel;
        while(dask!=NULL)
        {
            // -- Name et Link Name --------------------------------------------

            CurrentChunk=KDK_IK;
            KDKWRITECHUNK

            CurrentChunk=KDK_NAME;
            KDKWRITECHUNK

            strcpy(tmpch,dask->Name);
            if (fwrite(tmpch,sizeof(char),KDKNAMELENGTH,KDKFil)!=KDKNAMELENGTH) return false;

            CurrentChunk=KDK_LINKNAME;
            KDKWRITECHUNK

            strcpy(tmpch,dask->ObjName);
            if (fwrite(tmpch,sizeof(char),KDKNAMELENGTH,KDKFil)!=KDKNAMELENGTH) return false;


            // -- Bones --------------------------------------------------------

            CurrentChunk=KDK_BONE;
            KDKWRITECHUNK

            KDKWriteBoneList(dask);


            // -----------------------------------------------------------------

            dask=dask->Next;
        }

        // -- Fin IK -----------------------------------------------------------


        // -- Camera -----------------------------------------------------------
        Camera *daCam;

        daCam=dk->FirstCam;
        while(daCam!=NULL)
        {
            CurrentChunk=KDK_CAMERA;
            KDKWRITECHUNK

            CurrentChunk=KDK_NAME;
            KDKWRITECHUNK

            strcpy(tmpch,daCam->Name);
            if (fwrite(tmpch,sizeof(char),KDKNAMELENGTH,KDKFil)!=KDKNAMELENGTH) return false;

            CurrentChunk=KDK_CAMERAVAL;
            KDKWRITECHUNK

            KdkWriteCamera(daCam);

            daCam=daCam->Next;
        }

        // -- Fin Camera -------------------------------------------------------

        // -- Particle ---------------------------------------------------------
/*
        Emitter *daEmit;

        daEmit=dk->FirstEmit;
        while(daEmit!=NULL)
        {
            CurrentChunk=KDK_EMITTER;
            KDKWRITECHUNK

            CurrentChunk=KDK_NAME;
            KDKWRITECHUNK

            strcpy(tmpch,daEmit->Name);
            if (fwrite(tmpch,sizeof(char),KDKNAMELENGTH,KDKFil)!=KDKNAMELENGTH) return false;

            CurrentChunk=KDK_EMITTERVAL;
            KDKWRITECHUNK

            KdkWriteEmitter(daEmit);

            daEmit=daEmit->Next;
        }
*/
        // -- Fin Particle -----------------------------------------------------

        // -- Light ------------------------------------------------------------

        CLight *daLight;

        daLight=dk->FirstLight;
        while(daLight!=NULL)
        {
            CurrentChunk=KDK_LIGHT;
            KDKWRITECHUNK

            CurrentChunk=KDK_NAME;
            KDKWRITECHUNK

            strcpy(tmpch,daLight->Name);
            if (fwrite(tmpch,sizeof(char),KDKNAMELENGTH,KDKFil)!=KDKNAMELENGTH) return false;

            CurrentChunk=KDK_LIGHTVAL;
            KDKWRITECHUNK

            KdkWriteLight(daLight);

            daLight=daLight->Next;
        }

        // -- Fin Light --------------------------------------------------------

        // -- Shape ------------------------------------------------------------

        Shape *daShape;

        daShape=dk->FirstShape;
        while(daShape!=NULL)
        {
            if (daShape->FirstSegment!=NULL)
            {
                KdkWriteShape(daShape);
            }

            daShape=daShape->Next;
        }

        // -- Fin Shape --------------------------------------------------------


        // -- Private Data -----------------------------------------------------

        CPrivateData *pd;

        pd=dk->FirstData;
        while(pd!=NULL)
        {
            KdkWritePrivate(pd);

            pd=pd->Next;
        }

        // -- Fin Private Data -------------------------------------------------

        // -- View -------------------------------------------------------------

        CurrentChunk=KDK_VIEW;
        KDKWRITECHUNK

        KdkWriteView(dk);

        // -- Fin View ---------------------------------------------------------

        
    }
    else
    {
		
        return false;
    }

    // -- The end --------------------------------------------------------------

	fclose(KDKFil);
    return true;

}

// -- KDK Write - Bone list ----------------------------------------------------

void KDKWriteBone(Bone *daBone)
{
    Bone *daBone2;


	CurrentChunk=KDK_BONE;
	KDKWRITECHUNK

	KdkWriteVert(daBone->Pos);
	fwrite(daBone->Name,32,1,KDKFil);

	KDKWriteAttachList(daBone);

    daBone2=daBone->FirstBone;
    while(daBone2!=NULL)
    {
        KDKWriteBone(daBone2);
        daBone2=daBone2->Next;
    }

	CurrentChunk=KDK_BONEEND;
	KDKWRITECHUNK

}

void KDKWriteBoneList(Skeletton *daSkel)
{
	
    Bone *daBone;

	KdkWriteVert(daSkel->RootPos);
	KdkWriteVert(daSkel->bone->Pos);

	fwrite(daSkel->bone->Name,32,1,KDKFil);

    daBone=daSkel->bone->FirstBone;
    while(daBone!=NULL)
    {
        KDKWriteBone(daBone);
        daBone=daBone->Next;
    }

	CurrentChunk=KDK_BONEEND;
	KDKWRITECHUNK
	
}

Bone *CurrentBone;

void KDKReadBone(Bone *daBone)
{
    Bone *daBone2;
	bool Ok=true;

	dk->NextSkel->AddBone(daBone);

    daBone2=daBone->NextBone;

	KdkReadVert((Vertex*)&daBone2->Pos);
	fread(daBone2->Name,32,1,KDKFil);

	KDKReadAttachList(daBone2);

	while(Ok)
	{
		KDKREADCHUNK
		if (CurrentChunk==KDK_BONE)
		{
			KDKReadBone(daBone2);
		}
		else
		{
			if (CurrentChunk==KDK_BONEEND)
			{
				Ok=false;
			}
		}
	}

}

bool KDKReadBoneList(void)
{
    Bone *daBone;
	bool Ok;

	KdkReadVert((Vertex*)&dk->NextSkel->RootPos);
	dk->NextSkel->AddBone(NULL);
	KdkReadVert((Vertex*)&dk->NextSkel->bone->Pos);
	fread(dk->NextSkel->bone->Name,32,1,KDKFil);
/*
	dk->NextSkel->AddBone(dk->NextSkel->bone);

    daBone=dk->NextSkel->NextBone;
	*/
	daBone=dk->NextSkel->bone;
	
	

	Ok=true;
	while(Ok)
	{
		KDKREADCHUNK
		if (CurrentChunk==KDK_BONE)
		{
			KDKReadBone(daBone);
			
		}
		else
		{
			if (CurrentChunk==KDK_BONEEND)
			{
				Ok=false;
			}
		}
	}

	dk->NextSkel->BuildBase();
	return true;
}

bool KDKWriteAttachList(Bone *kdkbone)
{   
	BoneAttach *daBA;    


	CurrentChunk=KDK_IKATTACH;
	KDKWRITECHUNK


	daBA=kdkbone->FirstBA;
	while(daBA!=NULL)
	{
	    if (fwrite(&daBA->OriginIndex,sizeof(int),1,KDKFil)!=1) return false;

		daBA=daBA->Next;
	}

	CurrentChunk=KDK_IKATTACHEND;
	KDKWRITECHUNK
    
    return true;
}

// -- Read Bone list -----------------------------------------------------------

bool KDKReadAttachList(Bone *kdkbone)
{
	int tmp;

	KDKREADCHUNK

	while(CurrentChunk!=KDK_IKATTACHEND)
	{
		fread(&tmp,sizeof(int),1,KDKFil);
		if (tmp==KDK_IKATTACHEND) break;
		kdkbone->AddVert(CurObj->pv[tmp],tmp,1);
	}

    return true;
}

// -- KDK Load - Vertex list ---------------------------------------------------

bool KDKReadVertList(void)
{
    long nbVertList;
    int i;
    
    if (fread(&nbVertList,sizeof(long),1,KDKFil)!=1) return false;

    switch(CurrentMainChunk)
    {
        // -- chunks primaires -------------------------------------------------

        case KDK_SHAPE:
            break;

        case KDK_IK:
            break;

        case KDK_OBJECT:

            dk->NextObject->Allocate(0,nbVertList);

            for (i=0;i<nbVertList;i++)
            {

                KdkReadVert(dk->NextObject->pv[i]);
				//dk->NextObject->pv[i+nbVertList]=dk->NextObject->pv[i];
            }
            break;

        case KDK_CAMERA:
            if (nbVertList!=2) return false;

            KdkReadVert((Vertex*)&dk->NextCam->Source);

            KdkReadVert((Vertex*)&dk->NextCam->Dest);
            break;

        default:
            return false;
    }
    
    return true;
}

// -- KDK Load - Face list -----------------------------------------------------

bool KDKReadFaceList(void)
{
    long nbFaceList;
    long nbvert;
    double u,v;
    bool Selected;
    int i,j;

    if (fread(&nbFaceList,sizeof(long),1,KDKFil)!=1) return false;

    switch(CurrentMainChunk)
    {
        // -- chunks primaires -------------------------------------------------

        case KDK_OBJECT:
            dk->NextObject->Allocate(nbFaceList,0);

            for (i=0;i<nbFaceList;i++)
            {

                for (j=0;j<3;j++)
                {
                    if (fread(&nbvert,sizeof(int),1,KDKFil)!=1) return false;

                    dk->NextObject->pf[i]->nbvert[j]=nbvert;

                    if (fread(&u,sizeof(double),1,KDKFil)!=1) return false;
                    if (fread(&v,sizeof(double),1,KDKFil)!=1) return false;
/*
                    dk->NextObject->pf[i]->u[j]=u;
                    dk->NextObject->pf[i]->v[j]=v;
					*/
                }

                if (fread(&Selected,sizeof(bool),1,KDKFil)!=1) return false;
                dk->NextObject->pf[i]->Selected=Selected;

            }

            break;
        default:
            return false;
    }

    return true;
}

// -- KDK Load - Get Name ------------------------------------------------------

bool KDKReadName(void)
{
    char tmpch[KDKNAMELENGTH];


    if (fread(tmpch,sizeof(char),KDKNAMELENGTH,KDKFil)!=KDKNAMELENGTH) return false;

    switch(CurrentMainChunk)
    {
        // -- chunks primaires -------------------------------------------------

        case KDK_OBJECT:
            strcpy(dk->NextObject->Name,tmpch);
            break;
        case KDK_IK:
            strcpy(dk->NextSkel->Name,tmpch);
            break;
        case KDK_CAMERA:
            strcpy(dk->NextCam->Name,tmpch);
            break;
        case KDK_LIGHT:
            strcpy(dk->NextLight->Name,tmpch);
            break;
        case KDK_SHAPE:
            strcpy(dk->NextShape->Name,tmpch);
            break;
            /*
        case KDK_EMITTER:
            strcpy(dk->NextEmit->Name,tmpch);
            break;
*/
    }
	
	return true;
	
}

bool KDKReadLinkName(void)
{
    char tmpch[KDKNAMELENGTH];


    if (fread(tmpch,sizeof(char),KDKNAMELENGTH,KDKFil)!=KDKNAMELENGTH) return false;

    switch(CurrentMainChunk)
    {
        // -- chunks primaires -------------------------------------------------

        case KDK_OBJECT:
//            dk->Obj[dk->nb2obj-1]->Name=tmpch;
            break;
        case KDK_PATH:
//            dk->paths[dk->nb2paths-1]->Name=tmpch;
            break;
        case KDK_IK:
            strcpy(dk->NextSkel->ObjName,tmpch);
			CurObj=(Object*)dk->GetByName(tmpch,PLUGIN_OBJECT);
            dk->NextSkel->daObj=CurObj;
            break;
        case KDK_CAMERA:
//            dk->Cam[dk->nb2cam-1]->Name=tmpch;
            break;
    }
	return true;
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
    return LoadKdK(PathName);
}

int  __declspec(dllexport)   Write(Desk *dadk,char PathName[260])
{
    // Process here you write operation
    dk=dadk;
    return SaveKdK(PathName);
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


