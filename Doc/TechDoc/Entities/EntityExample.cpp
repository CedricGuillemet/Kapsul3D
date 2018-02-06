/* 
Includes
*/
#include "stdafx.h"
#include "Kapsul3D.h"
#include "Entities\Light.h"

CKEntity *LCurEntity;
CLight *CurLight;
bool LIsCreating=false;
int LSyncCreate;
CString lxmlDatas,ltmpxml;
CKDrawScene *LGDrawScene;
MYPOINT Lspt,Lspt2,Lsdeb;
CKSelectionInfos *LCurSel;
bool LdaAddIt;
CKMinMaxEnt Lm_MinMax;
int CreateSeg=0;
double tmpradius;
extern MYPOINT sdeb;
MYPOINT sfin;
bool HasBeenSel=false;
extern bool daAddIt;
bool daAddIt1,daAddIt2;
CKScene *GScene;

/*
Forward declaration
*/
void LMouseDown(int X,int Y,Vertex *Pos);
void LMouseUp(int X,int Y,Vertex *Pos);
void MouseMove(int X,int Y,Vertex *Pos);
void RMouseDown(int X,int Y,Vertex *Pos);
void RMouseUp(int X,int Y,Vertex *Pos);


UINT __declspec(dllexport) Process_Light(unsigned long Msg,unsigned long wParam,unsigned long lParam)
{
UINT value=0;
switch(Msg)
{
/*
This message is sent to tell you what is the entity you have to work on. This message arrives very often (before drawing, to retrieve its values,before KM_GETSINGLE,KM_SELECTSINGLE,...). The entity sent in parameters is called the current entity.
It works the same way for every entity.
Check CompilData member of the entity instance (wParam is a pointer to the entity instance).
If that member is NULL, you create your object instance and set the pointer in CompilData.
If not, your instance is already in 'CompilData' so set the 'working-on' pointer.
*/
case KM_SETENTITY:
if (((CKEntity*)wParam)->CompilData==NULL)
{
((CKEntity*)wParam)->CompilData=new CLight;
LSyncCreate=0;
LIsCreating=true;
}

CurLight=(CLight*)((CKEntity*)wParam)->CompilData;
LCurEntity=(CKEntity*)wParam;

break;
/*
KM_FREEENTITY is called to free your class. Simply delete your instance is CompilData is not NULL.
*/
case KM_FREEENTITY:
if ( ((CKEntity*)wParam)->CompilData!=NULL) delete (CLight*)((CKEntity*)wParam)->CompilData;
break;
/*
Called to draw your stuff. An entity belongs to 1 and only 1 Scene. To retrieve the scene info (rendering parameters,...) Get the Scene pointer
Thru the entity and call your draw member from your class.
*/
case KM_DRAW:
GScene=LCurEntity->m_Scene;
CurLight->Draw(*LCurEntity->m_Scene->ViewSize,lParam,0);
break;
/*
KM_ISCREATING report kapsul when you are building an entity. The light entity needs 2 mouse click to achieve construction.
So , at the first click, we set the CreateSeg value to TRUE.
When we receive mouse move message, if we are creating (CreateSeg is TRUE), we update our entity based on mouse position
At the second click, we set CreateSeg to FALSE.
That CreateSeg value helps us synchronize the built and we must return it to Kapsul otherwise, Kapsul won't know if we are building or not.
By example, you can change the active view when an entity is being built.
*/
case KM_ISCREATING:
value=CreateSeg;
break;

/*
Mouse message. see below

/*/
case KM_LMOUSEDOWN:
LMouseDown(LOWORD(wParam),HIWORD(wParam),(Vertex *)(lParam));
break;
case KM_RMOUSEDOWN:
RMouseDown(LOWORD(wParam),HIWORD(wParam),(Vertex *)(lParam));
break;
case KM_LMOUSEUP:
LMouseUp(LOWORD(wParam),HIWORD(wParam),(Vertex *)(lParam));
break;
case KM_RMOUSEUP:
RMouseUp(LOWORD(wParam),HIWORD(wParam),(Vertex *)(lParam));
break;
case KM_MOUSEMOVE:
MouseMove(LOWORD(wParam),HIWORD(wParam),(Vertex *)(lParam));
break;
/*
KM_GETXML and KM_SETXML are very important. They translate respectively from class member values to string and from string to class member values.
The table where the properties are stored is wParam. You have to cast it.
*/
case KM_GETXML:
{
CKHashTable *table=(CKHashTable *)wParam;

table->SetEntry("Name",CurLight->Name);
table->SetEntry("PositionX",CurLight->Source.vx);
table->SetEntry("PositionY",CurLight->Source.vy);
table->SetEntry("PositionZ",CurLight->Source.vz);
table->SetEntry("Color",(DWORD)(CurLight->r*65536+CurLight->g*256+CurLight->b));

switch(CurLight->Type)
{
case 0:
table->SetEntry("Type","Omni");
break;
case 1:
table->SetEntry("Type","Spot");
break;
case 2:
table->SetEntry("Type","Neon");
break;
}

switch(CurLight->SpotType)
{
case 0:
table->SetEntry("SpotType","Rectangular");
break;
case 1:
table->SetEntry("SpotType","Circular");
break;
}

table->SetEntry("TargetX",CurLight->Target.vx );
table->SetEntry("TargetY",CurLight->Target.vy );
table->SetEntry("TargetZ",CurLight->Target.vz );

table->SetEntry("Radius",CurLight->Radius);

}
break;
/*
Add DrawViews() call at the end of the method to update your the MDI views. Don't call your rendering code directly.
*/
case KM_SETXML:
{
CKHashTable *table=(CKHashTable *)wParam;

CurLight->Name=table->GetString("Name");

CurLight->Source.vx=table->GetFloat("PositionX");
CurLight->Source.vy=table->GetFloat("PositionY");
CurLight->Source.vz=table->GetFloat("PositionZ");
DWORD tmpcolor=table->GetDWord("Color");
CurLight->r=((float)((tmpcolor&0xff0000)>>16));
CurLight->g=((float)((tmpcolor&0xff00)>>8));
CurLight->b=((float)(tmpcolor&0xff));

CString tmptype=table->GetString("Type");

if (tmptype=="Omni")
CurLight->Type = 0;
else
if (tmptype=="Spot")
CurLight->Type = 1;
else
CurLight->Type = 2;

tmptype=table->GetString("SpotType");


if (tmptype=="Rectangular") 
CurLight->SpotType = 0;
else
CurLight->SpotType = 1;

CurLight->Target.vx=table->GetFloat("TargetX");
CurLight->Target.vy=table->GetFloat("TargetY");
CurLight->Target.vz=table->GetFloat("TargetZ");
CurLight->Radius=table->GetFloat("Radius");

DrawViews();

}
break;
/*
Return 1 to this message if your current entity is near the mouse click(mouse position is MAKELONG(X,Y) and set in wParam.
Use the same code to retrieve screen coordinates(projection) from the entity and compare it to the mouse position (called Pythagore function to 
get distance between).
return 0 if the entity is too far.
*/
case KM_GETSINGLE:
// Get a X/Y coordinates and you must return an entity if you have 1 close to it.
// we seek & project for the current entity
LGDrawScene=(CKDrawScene*)lParam;
Lspt=LCurEntity->m_Scene->cSel->Get2D(LGDrawScene->GetIsoCoord(LOWORD(wParam),HIWORD(wParam),LCurEntity->m_Scene->Active));

Lspt2=LCurEntity->m_Scene->cSel->Get2D(CurLight->Source);

if (Pythagore(Lspt2.x-Lspt.x,Lspt2.y-Lspt.y)<7)
{
value=1;
}
else
{
value=0;
}

break;
/*
this message is called to Select/Unselect the current entity. wParam is TRUE for selecting and FALSE for unselecting.
That function always return 1.
If you have to select the current entity, push all the entity vertex in the vertex modification buffer with the 
AddBufVert function. The 1st parameter is the pointer to the vertex. The 2nd is the pointer to the entity (not the CompilData member).3rd parameter is 0.
Don't Forget to set the Selected member of the Vertex to wParam. Tag the Selected member of the current entity too.


*/
case KM_SELECTSINGLE:
value=1;

if ((bool)wParam) 
{
if (CurLight->Type==0)
{
LCurEntity->m_Scene->AddBufVert(&CurLight->Source,LCurEntity,0); 
}
else
{
LCurEntity->m_Scene->AddBufVert(&CurLight->Source,LCurEntity,0); 
LCurEntity->m_Scene->AddBufVert(&CurLight->Target,LCurEntity,0); 
}
}

CurLight->Source.Selected=(bool)wParam;
CurLight->Target.Selected=(bool)wParam;
LCurEntity->Selected=(bool)wParam;
break;
/*
That message is simple: tag to false the selected member of Entity and of class.
*/
case KM_UNSELECT:
CurLight->Selected=false;
LCurEntity->Selected=false;
break;

/*
this message is sent when the user perfom a selection in the document. The selections can be select by rectangle/circle/fence/single. All the selection parameters are stored in the wParam value. Cast it to a CKSelectionInfos *. That structure contains the type of selection, the Min/Max position for a rectangle selection, the center and radius for a circle selection. Please note that a selection can also be used to remove items from selection (selection with CTRL down. Watch the selection user manual). 


*/
case KM_SELECTION:
LCurSel=(CKSelectionInfos *)wParam;

sdeb=LCurEntity->m_Scene->cSel->Get2D(CurLight->Source);
sfin=LCurEntity->m_Scene->cSel->Get2D(CurLight->Target);

daAddIt1=false;
daAddIt2=false;

if (CurLight->Type==0)
{
// omni
switch(LCurSel->TypeSel)
{
case SELECT_SINGLE:
daAddIt1=(Pythagore((sdeb.x-LCurSel->spt2.x),(sdeb.y-LCurSel->spt2.y))<3);
break;
case SELECT_CIRCLE:
daAddIt1=(Pythagore((sdeb.x-LCurSel->spt.x),(sdeb.y-LCurSel->spt.y))<LCurSel->Length);
break;
case SELECT_QUAD:
daAddIt1=( (((sdeb.x>=LCurSel->spt.x)&&(sdeb.x<=LCurSel->spt2.x))||((sdeb.x<=LCurSel->spt.x)&&(sdeb.x>=LCurSel->spt2.x)))&&
(((sdeb.y>=LCurSel->spt.y)&&(sdeb.y<=LCurSel->spt2.y))||((sdeb.y<=LCurSel->spt.y)&&(sdeb.y>=LCurSel->spt2.y))) );
break;
case SELECT_FENCE:
daAddIt1=LCurSel->daSh->IsVertInShape(CurLight->Source,LCurSel->View);
break;
}
}
else
{
// spot
switch(LCurSel->TypeSel)
{
case SELECT_SINGLE:
if (LCurSel->WholeSelect==SELECT_WHOLE) 
{
daAddIt1=(SegDistance(sdeb,sfin,LCurSel->spt2)<3);
daAddIt2=daAddIt1;
}
if (LCurSel->WholeSelect==SELECT_VERTEX) 
{
daAddIt1=(Pythagore((sdeb.x-LCurSel->spt2.x),(sdeb.y-LCurSel->spt2.y))<3);
daAddIt2=(Pythagore((sfin.x-LCurSel->spt2.x),(sfin.y-LCurSel->spt2.y))<3);
}
break;
case SELECT_CIRCLE:
daAddIt1=(Pythagore((sdeb.x-LCurSel->spt.x),(sdeb.y-LCurSel->spt.y))<LCurSel->Length);
daAddIt2=(Pythagore((sfin.x-LCurSel->spt.x),(sfin.y-LCurSel->spt.y))<LCurSel->Length);
break;
case SELECT_QUAD:
daAddIt1=( (((sdeb.x>=LCurSel->spt.x)&&(sdeb.x<=LCurSel->spt2.x))||((sdeb.x<=LCurSel->spt.x)&&(sdeb.x>=LCurSel->spt2.x)))&&
(((sdeb.y>=LCurSel->spt.y)&&(sdeb.y<=LCurSel->spt2.y))||((sdeb.y<=LCurSel->spt.y)&&(sdeb.y>=LCurSel->spt2.y))) );
daAddIt2=( (((sfin.x>=LCurSel->spt.x)&&(sfin.x<=LCurSel->spt2.x))||((sfin.x<=LCurSel->spt.x)&&(sfin.x>=LCurSel->spt2.x)))&&
(((sfin.y>=LCurSel->spt.y)&&(sfin.y<=LCurSel->spt2.y))||((sfin.y<=LCurSel->spt.y)&&(sfin.y>=LCurSel->spt2.y))) );
break;
case SELECT_FENCE:
daAddIt1=LCurSel->daSh->IsVertInShape(CurLight->Source,LCurSel->View);
daAddIt2=LCurSel->daSh->IsVertInShape(CurLight->Target,LCurSel->View);
break;
}
}

if (LCurSel->WholeSelect==SELECT_WHOLE) 
{
if (CurLight->Type==0)
{
if (daAddIt1)
{
if ((!CurLight->Source.Selected)&&(LCurSel->AddIt)) 
LCurEntity->m_Scene->AddBufVert(&CurLight->Source,LCurEntity,0); 
CurLight->Source.Selected=LCurSel->AddIt;
} 

CurLight->Selected=daAddIt1;
LCurEntity->Selected=daAddIt1;

}
else
{
if (LCurSel->Crossing) daAddIt=daAddIt1 || daAddIt2;
else daAddIt=daAddIt1 && daAddIt2;

// Add it if OK!
if (daAddIt)
{
if ((!CurLight->Source.Selected)&&(LCurSel->AddIt)) 
LCurEntity->m_Scene->AddBufVert(&CurLight->Source,LCurEntity,0); 
CurLight->Source.Selected=LCurSel->AddIt;

if ((!CurLight->Target.Selected)&&(LCurSel->AddIt)) 
LCurEntity->m_Scene->AddBufVert(&CurLight->Target,LCurEntity,0); 
CurLight->Target.Selected=LCurSel->AddIt;

CurLight->Selected=LCurSel->AddIt;
LCurEntity->Selected=LCurSel->AddIt;

}
}
}
else
{
if (daAddIt1)
{
if ((!CurLight->Source.Selected)&&(LCurSel->AddIt)) 
LCurEntity->m_Scene->AddBufVert(&CurLight->Source,LCurEntity,0); 
CurLight->Source.Selected=LCurSel->AddIt;
}

if (daAddIt2) 
{
if ((!CurLight->Target.Selected)&&(LCurSel->AddIt)) 
LCurEntity->m_Scene->AddBufVert(&CurLight->Target,LCurEntity,0); 
CurLight->Target.Selected=LCurSel->AddIt;
}
}
break;
/*
when receiving this message, fill a CKMinMaxEnt structure and return a pointer to it. So, you need to declare that structure in a global manner.
That structure is used to build a bounding box for frustum culling. It's very important to fill it carrefully or your stuff won't be visible correctly. 
*/
case KM_GETMINMAX:
Lm_MinMax.Min=CurLight->GetMinOf()-Vertex(CurLight->Radius,CurLight->Radius,CurLight->Radius);
Lm_MinMax.Max=CurLight->GetMaxOf()+Vertex(CurLight->Radius,CurLight->Radius,CurLight->Radius);
value=(int)&Lm_MinMax;
break; 

default:
break;
}

return value;
}

/*
Watch CreateSeg info above. 
*/

void LMouseDown(int X,int Y,Vertex *Pos)
{
if (CreateSeg==0)
{
CurLight->Source=*Pos;
CurLight->Target=Vertex(0,0,0);
CurLight->Radius=1;
CreateSeg=1;
}
else
{
if ((CreateSeg==1)&&(CurLight->Type==0))
{
CreateSeg=0;
LIsCreating=0;
}
else
{
if (CreateSeg==2)
{
CreateSeg=0;
LIsCreating=0;
}
else
CreateSeg=2;

}
}

}

void LMouseUp(int X,int Y,Vertex *Pos)
{

}

/*
If CreateSeg!=0, we are creating a light. Depending on Type of light (omni,spot,neon), we update the radius/target position of light.
We use LStatus and RStatus to display string in the status bar.

*/

void MouseMove(int X,int Y,Vertex *Pos)
{
if (CreateSeg!=0)
{
switch (CurLight->Type)
{
case 0:
CurLight->Radius=Pythagore3D(CurLight->Source,(*Pos));
RStatus("Omni light radius : %d",(int)(CurLight->Radius));
LStatus("Click to end omni light creation.");
break;
case 1:
if (CreateSeg==1)
{
CurLight->Target=*Pos;
CurLight->Radius=1;
LStatus("Click to set spot light target.");
}
else
{
CurLight->Radius=Pythagore3D(CurLight->Target,(*Pos));
CurLight->Radius/=2;
RStatus("Spot light radius : %5.2f",CurLight->Radius);
LStatus("Click to end spot light creation.");
}
break;
case 2:
if (CreateSeg==1)
{
CurLight->Target=*Pos;
CurLight->Radius=1;
LStatus("Click to set neon light end.");
}
else
{
CurLight->Radius=Pythagore3D(CurLight->Target,(*Pos));
RStatus("Neon light radius : %5.2",CurLight->Radius);
LStatus("Click to end neon light creation.");
}
break;
}
tmpradius=CurLight->Radius;
DrawViews();
}
else
{
LStatus("Click to set light source.");
}

}

void RMouseDown(int X,int Y,Vertex *Pos)
{
}

/*
when user is right clicking, Stop the current build process. CreateSeg=0.
*/

void RMouseUp(int X,int Y,Vertex *Pos)
{
if (CurLight!=NULL)
{
CurLight=NULL;
CreateSeg=0;
LIsCreating=0;
}

}
