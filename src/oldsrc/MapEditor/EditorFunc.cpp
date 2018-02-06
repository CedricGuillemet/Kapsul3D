#include "stdafx.h"
#include "headers.h"
#include "MapEdUtils.h"

extern "C" Desk *dk;
extern "C" Object *CurrentObj;
extern "C" Vertex daNorm,Remem;
extern "C" int dx,dy,ngl,CreateSeg;
extern "C" OGLView *View;
extern "C" Plan dap;
extern "C" Vertex Min,Max;


extern "C" bool SomethingSel;
extern "C" int vtyp;
//extern "C" bool LShiftDown;
//extern "C" bool CtrlDown;
//extern "C" Vertex Snap;
//extern "C" int TypeEdit;
//extern "C" int ngl;
//extern "C" Plan dap;
//extern "C" int dx,dy;
//extern "C" Vertex Remem,Remem2;
//extern "C" Vertex Length;
//extern "C" Vertex Min,Max;
extern "C" MYPOINT PrjMin,PrjMax;

extern "C" Vertex MulScal;
extern "C" Vertex Center;
//extern "C" Vertex Startl,Endl;
extern "C" double lx,ly;
//extern "C" Vertex daNorm;
extern "C" Vertex CubeSize;
extern "C" MYPOINT pts;
extern "C" bool JustAddIt;
extern "C" bool IsMoving;
extern "C" CUndoRedo *CurrentUndo;

void SetSelectedToAfterUndo(void)
{
	int UndoAv=0;
	for (Object *daObj2=dk->FirstObject;daObj2!=NULL;daObj2=daObj2->Next)
	{
		if (daObj2->Selected)
		{
			CurrentUndo->SetAfterEntry(UndoAv,PLUGIN_OBJECT,daObj2);
			UndoAv++;
		}
	}
}

void SetSelectedToBeforeUndo(void)
{
	int UndoAv=0;
	for (Object *daObj2=dk->FirstObject;daObj2!=NULL;daObj2=daObj2->Next)
	{
		if (daObj2->Selected)
		{
			CurrentUndo->SetPrevEntry(UndoAv,PLUGIN_OBJECT,daObj2);
			UndoAv++;
		}
	}
}

void BeginCreateBox(int X,int Y,Vertex *Pos)
{
	// create cube

	CurrentObj=NULL;
	Remem=(*Pos);
	dx=X;
	dy=Y;

	CreateSeg=1;
}

void BeginRotate(int X,int Y,Vertex *Pos)
{
	// rotate

	Remem=(*Pos);
	dx=X;
	dy=Y;

	CreateSeg=1;

	MYPOINT Getng,Getng2;

	Getng=dk->cSel->Get2D(*Pos);

	Vertex Min=dk->GetMinBuf();
	Vertex Max=dk->GetMaxBuf();
	Vertex Center=(Min+((Max-Min)/2));

	Remem=Center;

	Getng2=dk->cSel->Get2D(Center);

	ngl=ng(Getng.x,Getng.y,Getng2.x,Getng2.y);
	dap.PlanOfView(View,dk->Active);

	//undo
	CurrentUndo=dk->AddUndo("MapEditor.dll",GetNbSelectedObjects());
	CurrentUndo->UndoType=UNDO_MODIFY;
	SetSelectedToBeforeUndo();
}

void RotateBuffer(int X,int Y,Vertex *Pos)
{
	dx=X;
	dy=Y;

	MYPOINT Getng,Getng2;

	Getng2=dk->cSel->Get2D(*Pos);

	Getng=dk->cSel->Get2D(Remem);

	int tempng=int(((ng(Getng.x,Getng.y,Getng2.x,Getng2.y)-ngl)*180)/PI);
	//LStatus("Angle %d",tempng);
	dap.MatrixRotateNormale(((tempng*PI)/180));
	dk->RotateBuf(&dap,Remem);

	CreateSeg=1;

	// undo
	SetSelectedToAfterUndo();
}

void ClickSelectObject(int X,int Y,Vertex *Pos)
{
    bool AddIt;
    int i;
    SomethingSel=false;
    Object *daObj=dk->cSel->GetObjectByTriangle(X,Y,false);
    if (daObj!=NULL)
    {
        AddIt=!daObj->Selected;
        daObj->Selected=AddIt;

        for (i=0;i<daObj->nb2vert;i++)
        {
            if ((!daObj->pv[i].Selected)&&(AddIt)) dk->AddBufVert(&daObj->pv[i],daObj);
            daObj->pv[i].Selected=AddIt;
        }
        dk->RemoveBufUnselected();
    }
    
    daObj=dk->FirstObject;
    while(daObj!=NULL)
    {
        SomethingSel|=daObj->Selected;
        daObj=daObj->Next;
    }
}

void BeginCutter(int X,int Y,Vertex *Pos)
{
	// Cliper
	Remem=(*Pos);
	dx=X;
	dy=Y;

	CreateSeg=1;
	// undo
	CurrentUndo=dk->AddUndo("MapEditor.dll",GetNbSelectedObjects());
	CurrentUndo->UndoType=UNDO_MODIFY;
	SetSelectedToBeforeUndo();
}

void ScaleBuffer(int X,int Y,Vertex *Pos)
{ 
	Vertex ScaleVal;
	
	Object *daObj;
	
	daObj=dk->FirstObject;
	while (daObj!=NULL)
	{
		if (daObj->Selected)
		{
			MulScal.vx=0;
			MulScal.vy=0;
			MulScal.vz=0;
			
			Min=dk->GetMinBuf();
			Max=dk->GetMaxBuf();
			
			PrjMin=dk->cSel->Get2D(Min);
			PrjMax=dk->cSel->Get2D(Max);
			
			CreateSeg=1;
			
			
			
			Vertex UnproMin,UnproMax;
			Vertex daMulX,daMulY;
			


			vtyp=GetView();
			switch(vtyp)
			{
			case 1:
				lx=Max.vx-Min.vx;
				ly=Max.vy-Min.vy;
				daMulX=Vertex(1,0,0);
				daMulY=Vertex(0,1,0);
				break;
			case 2:
				lx=Max.vx-Min.vx;
				ly=Max.vz-Min.vz;
				daMulX=Vertex(1,0,0);
				daMulY=Vertex(0,0,1);
				Max.vy=Max.vz;
				Min.vy=Min.vz;

				break;
			case 3:
				lx=Max.vy-Min.vy;
				ly=Max.vz-Min.vz;
				daMulX=Vertex(0,1,0);
				daMulY=Vertex(0,0,1);
				Max.vx=Max.vy;
				Min.vx=Min.vy;

				Max.vy=Max.vz;
				Min.vy=Min.vz;
				break;
			case 4:
				lx=Max.vx-Min.vx;
				ly=Max.vy-Min.vy;
				daMulX=Vertex(1,0,0);
				daMulY=Vertex(0,1,0);
				break;
			case 5:
				lx=Max.vx-Min.vx;
				ly=Max.vz-Min.vz;
				daMulX=Vertex(1,0,0);
				daMulY=Vertex(0,0,1);
				Max.vy=Max.vz;
				Min.vy=Min.vz;

				break;
			case 6:
				lx=Max.vy-Min.vy;
				ly=Max.vz-Min.vz;
				daMulX=Vertex(0,1,0);
				daMulY=Vertex(0,0,1);
				Max.vx=Max.vy;
				Min.vx=Min.vy;

				Max.vy=Max.vz;
				Min.vy=Min.vz;

				break;
			}
			
			UnproMin=View->GetIsoCoord(PrjMin.x,PrjMin.y,dk->Active);
			UnproMax=View->GetIsoCoord(PrjMax.x,PrjMax.y,dk->Active);
			
			// Y ONLY
			
			if (((pts.x>PrjMin.x)&&(pts.x<PrjMax.x))||((pts.x<PrjMin.x)&&(pts.x>PrjMax.x)))
			{
				OutputDebugString("\nNew Y ------\n");

				if (fabs(PrjMin.y-pts.y)>fabs(PrjMax.y-pts.y))
				{
					Center=Min;
					MulScal.vy=1;
					OutputDebugString("Center=Min;MulScal.vy=1;\n");
				}
				else
				{
					Center=Max;
					MulScal.vy=-1;
					OutputDebugString("Center=Max;MulScal.vy=-1;\n");
				}
			}
			else
			// X ONLY
			if (((pts.y>PrjMin.y)&&(pts.y<PrjMax.y))||((pts.y<PrjMin.y)&&(pts.y>PrjMax.y)))
			{
				OutputDebugString("\nNew X ------\n");

				if (fabs(PrjMin.x-pts.x)>fabs(PrjMax.x-pts.x))
				{
					Center=Min;
					MulScal.vx=1;
					OutputDebugString("Center=Min;MulScal.vx=1;\n");
				}
				else
				{
					Center=Max;
					MulScal.vx=-1;
					OutputDebugString("Center=Max;MulScal.vx=-1;\n");
				}
			}
			else
				// ALL
			{
				OutputDebugString("\nNew XY ------\n");
				Center.vx=0;
				Center.vy=0;
				Center.vz=0;

				if (fabs(PrjMin.x-pts.x)>abs(PrjMax.x-pts.x))
				{
					Center.vx=Min.vx;
					MulScal.vx=1;
					OutputDebugString("Center.vx=Min.vx;MulScal.vx=1;\n");
				}
				else
				{
					Center.vx=Max.vx;
					MulScal.vx=-1;
					OutputDebugString("Center.vx=Max.vx;MulScal.vx=-1;\n");
				}
				
				
				if (fabs(PrjMin.y-pts.y)>abs(PrjMax.y-pts.y))
				{
					Center.vy=Min.vy;
					MulScal.vy=1;
					OutputDebugString("Center.vy=Min.vy;MulScal.vy=1;\n");
				}
				else
				{
					Center.vy=Max.vy;
					MulScal.vy=-1;
					OutputDebugString("Center.vy=Max.vy;MulScal.vy=-1;\n");
				}
				
			}
			
			// reset center
			vtyp=GetView();
			switch(vtyp)
			{
				case 4:
			case 1:
				break;
			case 5:
			case 2:
				Center.vz=Center.vy;
				break;
			case 6:
			case 3:
				Center.vz=Center.vy;
				Center.vy=Center.vx;
				break;
			}



			MYPOINT ptsn=dk->cSel->Get2D(Max);
			MYPOINT ptsnb=dk->cSel->Get2D(Min);
			ptsn.x-=ptsnb.x;
			ptsn.y-=ptsnb.y;
			
			
			double ndx= (ptsn.x+((float)X-(float)dx)*MulScal.vx)/ptsn.x;
			double ndy= (ptsn.y+((float)dy-(float)Y)*MulScal.vy)/ptsn.y;
			
			ScaleVal.vx=ndx;
			ScaleVal.vy=ndy;
			
			
			
			
			double nlx=lx*ScaleVal.vx;
			double nly=ly*ScaleVal.vy;
			
			if ((nlx)<8.0f) 
			{
				ScaleVal.vx=8/lx;
			}
			else
			{
				double tmpmod=fmod(nlx,8);
				if (tmpmod!=0.0f)
				{
					nlx-=tmpmod;
					if (tmpmod>=4) nlx+=8;
					if (tmpmod<=-4) nlx-=8;
					ScaleVal.vx=nlx/lx;
				}
				
			}
			
			
			if ((nly)<8.0f) 
			{
				ScaleVal.vy=8/ly;
			}
			else
			{
				double tmpmod=fmod(nly,8);
				if (tmpmod!=0.0f)
				{
					nly-=tmpmod;
					if (tmpmod>=4) nly+=8;
					if (tmpmod<=-4) nly-=8;
					ScaleVal.vy=nly/ly;
				}
				
			}
			
			//ScaleVal*=MulScal;
			//
			//ScaleVal.vy=1.0f;
			ScaleVal.vz=1.0f;
			
			//if (ScaleVal.vx.
			dap.ScaleMatrix();
			dk->ScaleBuf(&dap,Center,ScaleVal);
			char Buf[500];
			sprintf(Buf,"CX:%5.2f CY:%5.2f CZ:%5.2f | SX:%5.2f SY:%5.2f SZ:%5.2f\n",Center.vx,Center.vy,Center.vz,ScaleVal.vx,ScaleVal.vy,ScaleVal.vz);
			OutputDebugString(Buf);

			MYPOINT tmpuv;
			tmpuv.x=daObj->puv[0][daObj->pl[0].Tex[0][0]].u;
			tmpuv.y=daObj->puv[0][daObj->pl[0].Tex[0][0]].v;
			
			daObj->CalcTexCoord(128,128,daObj->pv[daObj->pl[0].nbvert[0]],tmpuv.x,tmpuv.y);
		}
		daObj=daObj->Next;
	}
	// undo
	SetSelectedToAfterUndo();
}

void ValidateCutter(int X,int Y,Vertex *Pos)
{
	Object *daObj=BuildCutter(Remem,*Pos);
	daObj->CalcAllPlanes();
	UpdateBspTree(daObj);

//	dk->InitAllObjectsTag(0);
	for (Object *daObj2=dk->FirstObject;daObj2!=NULL;daObj2=daObj2->Next)
	{
		if (daObj2->Selected)
		{
			UpdateBspTree(daObj2);
			SubObject(daObj2,daObj);
			daObj2->Tag=1;
		}
	}
	dk->DeleteBufVert();
	dk->cSel->UnSelectAll(false);
	SomethingSel=false;

	for (daObj2=dk->FirstObject;daObj2!=NULL;daObj2=daObj2->Next)
	{
		if (daObj2->Tag)
		{
			dk->cSel->SingleObject(daObj2,true);
			daObj2->Selected=true;
		}
	}

	//dk->AddObject(daObj);
	CreateSeg=0;
	DrawViews();
	//undo
	SetSelectedToAfterUndo();
}

bool BeginMoveBuffer(int X,int Y,Vertex *Pos)
{
    Object *daObj=dk->cSel->IsOverSelectedObject(X,Y);
    if (daObj!=NULL)
    {
        IsMoving=true;
        CreateSeg=1;
        Remem=*Pos;

		// undo
		CurrentUndo=dk->AddUndo("MapEditor.dll",GetNbSelectedObjects());
		CurrentUndo->UndoType=UNDO_MODIFY;
		SetSelectedToBeforeUndo();
		

		return true;
    }
    else
    {
		return false;
    }   
}

void MoveBuffer(int X,int Y,Vertex *Pos)
{
	// translate buf
	dk->TranslateBuf(*Pos-Remem);
	for (int i=0;i<48;i++)
		View->DrawHanks[i]=View->Hanks[i]+(*Pos-Remem);

}

void CreateBox(int X,int Y,Vertex *Pos)
{
	Vertex temp;

	if (CurrentObj==NULL)
	{
		dk->AddObject();
		CurrentObj=dk->NextObject;
		dk->NextObject->AllocatePoly(0,8);
		CurrentUndo=dk->AddUndo("MapEditor.dll",1);
		CurrentUndo->UndoType=UNDO_CREATE;
	}

//	CreateCube((*Pos),0,0,0);

	temp=(*Pos)-Remem;

	if (temp.vx==0) temp.vx=CubeSize.vx;
	if (temp.vy==0) temp.vy=CubeSize.vy;
	if (temp.vz==0) temp.vz=CubeSize.vz;

	Vertex daStart,daLength;

	if (temp.vx<0)
	{
		daStart.vx=Pos- >vx;
		temp.vx=-temp.vx;
	}
	else
		daStart.vx=Remem.vx;

	if (temp.vy<0)
	{
		daStart.vy=Pos->vy;
		temp.vy=-temp.vy;
	}
	else
		daStart.vy=Remem.vy;

	if (temp.vz<0)
	{
		daStart.vz=Pos->vz;
		temp.vz=-temp.vz;
	}
	else
		daStart.vz=Remem.vz;

	CreateCube(daStart,temp.vx,temp.vy,temp.vz);//svgX,svgY,0);


	CurrentObj=dk->NextObject;
	CurrentObj->CalcTexCoord(128,128,daStart,0,0);

	// Undo

	CurrentUndo->SetAfterEntry(0,PLUGIN_OBJECT,CurrentObj);

	CubeSize=temp;
	JustAddIt=true;
}

void BeginScale(int X,int Y,Vertex *Pos)
{
    dx=X;
    dy=Y;
    dap.PlanOfView(View,dk->Active);
    CreateSeg=1;
	pts=dk->cSel->Get2D(View->GetIsoCoord(X,Y,dk->Active));
	// undo
	CurrentUndo=dk->AddUndo("MapEditor.dll",GetNbSelectedObjects());
	CurrentUndo->UndoType=UNDO_MODIFY;
	SetSelectedToBeforeUndo();
}

    
void BeginMoveVertex(int X,int Y,Vertex *Pos)
{
	dk->cSel->UnSelectAll(false);
	dk->DeleteBufVert();

	//dk->cSel->SingleObjVert(X,Y,true);
	dk->cSel->SelectObject(dx,dy,X,Y,NULL,true,true,SELECT_SINGLE,SELECT_VERTEX);
//	dk->cSel->SinglePatchVert(X,Y,true);
	Remem=*Pos;
	CreateSeg=1;
	IsMoving=true;
	// undo
	CurrentUndo=dk->AddUndo("MapEditor.dll",GetNbSelectedObjects());
	CurrentUndo->UndoType=UNDO_MODIFY;
	SetSelectedToBeforeUndo();
}

void InitMappingObject(void)
{
	for (Object *daObj=dk->FirstObject;daObj!=NULL;daObj=daObj->Next)
	{
		if (daObj->Tag==1)
		{
			MYPOINT tmpuv;
			tmpuv.x=daObj->puv[0][daObj->pl[0].Tex[0][0]].u;
			tmpuv.y=daObj->puv[0][daObj->pl[0].Tex[0][0]].v;
			
			daObj->CalcTexCoord(128,128,daObj->pv[daObj->pl[0].nbvert[0]],tmpuv.x,tmpuv.y);
		}
	}
}

void MoveVertex(int X,int Y,Vertex *Pos)
{
//	dk->InitAllObjectsTag(0);
/*
	for (VertBuf *daBufVert=dk->FirstBufVert;daBufVert!=NULL;daBufVert=daBufVert->Next)
	{
		if (daBufVert->Obj!=NULL)
		{
			daBufVert->Obj->TranslateVertex(daBufVert->VertIndex,daBufVert->AncVal+(*Pos-Remem));
			daBufVert->Obj->Tag=1;
		}
		else
		{
			if (daBufVert->Patch!=NULL)
			{
				daBufVert->Patch->pv[daBufVert->VertIndex]=daBufVert->AncVal+(*Pos-Remem);
				daBufVert->Patch->Build(daBufVert->Patch->Tesselate);

			}
		}
	}

	InitMappingObject();
	DrawViews();
	// undo
	SetSelectedToAfterUndo();
	*/
}
 
void BeginMoveEdge(int X,int Y,Vertex *Pos)
{
	dk->cSel->UnSelectAll(false);
	dk->DeleteBufVert();

	dk->cSel->SingleObjEdge(X,Y,true);
	Remem=*Pos;
	CreateSeg=1;
	IsMoving=true;
	// undo
	CurrentUndo=dk->AddUndo("MapEditor.dll",GetNbSelectedObjects());
	CurrentUndo->UndoType=UNDO_MODIFY;
	SetSelectedToBeforeUndo();
}

void MoveEdge(int X,int Y,Vertex *Pos)
{
	/*
	dk->InitAllObjectsTag(0);

	//dk->TranslateBuf(*Pos-Remem);
	
	for (VertBuf *daBufVert=dk->FirstBufVert;daBufVert!=NULL;daBufVert=daBufVert->Next)
	{
		if (daBufVert->Obj!=NULL)
		{
			daBufVert->Obj->TranslateVertex(daBufVert->VertIndex,daBufVert->AncVal+(*Pos-Remem));
			daBufVert->Obj->Tag=1;
		}
	}

	InitMappingObject();
	// undo
	SetSelectedToAfterUndo();
	*/
}

void BeginTranslatecoords(int X,int Y,Vertex *Pos)
{
	Remem=*Pos;
	dx=X;
	dy=Y;
	CreateSeg=1;
	IsMoving=true;

	// undo
	CurrentUndo=dk->AddUndo("MapEditor.dll",GetNbSelectedObjects());
	CurrentUndo->UndoType=UNDO_MODIFY;
	SetSelectedToBeforeUndo();
}

void Translatecoords(int X,int Y,Vertex *Pos)
{
	for (Object *daObj=dk->FirstObject;daObj!=NULL;daObj=daObj->Next)
	{
		if (daObj->Selected)
		{
			for (int i=0;i<daObj->nbTexCoords[0];i++)
			{
				float temp;
				temp=daObj->puv[0][i].u;
				temp+=(float)(dx)/100.0f;
				temp-=(float)(X)/100.0f;
				daObj->puv[0][i].u=temp;

				temp=daObj->puv[0][i].v;
				temp-=(float)(dy)/100.0f;
				temp+=(float)(Y)/100.0f;
				daObj->puv[0][i].v=temp;
			}
		}
	}
	dx=X;
	dy=Y;
	// undo
	SetSelectedToAfterUndo();
}

double OldFactX,OldFactY;

void BeginScalecoords(int X,int Y,Vertex *Pos)
{
	Remem=*Pos;
	dx=X;
	dy=Y;
	CreateSeg=1;
	IsMoving=true;
	OldFactX=1;
	OldFactY=1;

	// undo
	CurrentUndo=dk->AddUndo("MapEditor.dll",GetNbSelectedObjects());
	CurrentUndo->UndoType=UNDO_MODIFY;
	SetSelectedToBeforeUndo();
}


void Scalecoords(int X,int Y,Vertex *Pos) 
{
	double NewfX,NewfY;

	NewfX=(X-dx);
	NewfX=(NewfX==0)?1:( (NewfX<0)?(1.0f-((-NewfX)*0.01f)):(1+(NewfX/10.0f)) );
	int tmpr=(NewfX*100.0f);
	NewfX=tmpr;
	NewfX/=100.0f;

	NewfY=(Y-dy);
	NewfY=(NewfY==0)?1:( (NewfY<0)?(1.0f-((-NewfY)*0.01f)):(1+(NewfY/10.0f)) );

	tmpr=(NewfY*100.0f);
	NewfY=tmpr;
	NewfY/=100.0f;

	for (Object *daObj=dk->FirstObject;daObj!=NULL;daObj=daObj->Next)
	{
		if (daObj->Selected)
		{
			for (int i=0;i<daObj->nbTexCoords[0];i++)
			{
				float temp;
				temp=daObj->puv[0][i].u;
				temp/=OldFactX;
				temp*=NewfX;
				daObj->puv[0][i].u=temp;

				temp=daObj->puv[0][i].v;
				temp/=OldFactY;
				temp*=NewfY;
				daObj->puv[0][i].v=temp;

			}
		}
	}

	OldFactX=NewfX;
	OldFactY=NewfY;
	LStatus("Scale X: %5.4f Y: %5.4f ",OldFactX,OldFactY);
	// undo
	SetSelectedToAfterUndo();

}
double OldRot=0,NewRot=0;

void BeginRotatecoords(int X,int Y,Vertex *Pos) 
{
	Remem=*Pos;
	dx=X;
	dy=Y;
	CreateSeg=1;
	IsMoving=true;
	OldRot=0;

	// undo
	CurrentUndo=dk->AddUndo("MapEditor.dll",GetNbSelectedObjects());
	CurrentUndo->UndoType=UNDO_MODIFY;
	SetSelectedToBeforeUndo();

}

void Rotatecoords(int X,int Y,Vertex *Pos) 
{
	double cs1=cos(OldRot),sn1=sin(OldRot);

	NewRot=ng(dx,dy,X,Y);

	double cs2=cos(NewRot),sn2=sin(NewRot);

	for (Object *daObj=dk->FirstObject;daObj!=NULL;daObj=daObj->Next)
	{
		if (daObj->Selected)
		{
			for (int i=0;i<daObj->nbTexCoords[0];i++)
			{
				float tempx,tempy;
				tempx=daObj->puv[0][i].u;
				tempy=daObj->puv[0][i].v;

				daObj->puv[0][i].u=tempx*cs1-tempy*sn1;
				daObj->puv[0][i].v=tempx*sn1+tempy*cs1;

				tempx=daObj->puv[0][i].u;
				tempy=daObj->puv[0][i].v;

				daObj->puv[0][i].u=tempx*cs2-tempy*sn2;
				daObj->puv[0][i].v=tempx*sn2+tempy*cs2;

			/*
				xp=x cos  - y sin
				yp=x sin + y cos
				*/

			}
		}
	}
	OldRot=-NewRot;

	LStatus("Rotate  %5.4f deg",(NewRot*180.0f)/PI);
	// undo
	SetSelectedToAfterUndo();
}

#include "stdafx.h"
#include <headers.h>

 // temp
/*
    dk->AddObject();
    CurrentObj=dk->NextObject;
    CurrentObj->Allocate(0,2*10);
	CreateCube(Vertex(-32,-32,-32),64,64,64);
    CalcTexCoord(CurrentObj,128,128,*Pos,0,0);
	CurrentObj->CalcAllPlanes();

	CurrentObj->BSPTree=new CBSPTree;
	CurrentObj->BSPTree->InitPolygons(CurrentObj,1,FALSE);

	Object *TempCut=BuildCutter();

	SubObject(CurrentObj,TempCut);
*/
	//dk->AddObject(BuildCutter(Vertex(128,64,0),Vertex(16,32,0)));

	/* WORKING 
    dk->AddObject();
    CurrentObj=dk->NextObject;
    CurrentObj->Allocate(0,2*10);
	//CreateCube(Vertex(0,0,0),64,64,64);
	CreateNGon(Vertex(0,0,0),64,8,Vertex(1,0,0),Vertex(0,1,0),Vertex(0,0,1),10);
    CalcTexCoord(CurrentObj,128,128,*Pos,0,0);
	CurrentObj->CalcAllPlanes();


	CurrentObj->BSPTree=new CBSPTree;
	CurrentObj->BSPTree->InitPolygons(CurrentObj,1,FALSE);


    dk->AddObject();
    CurrentObj=dk->NextObject;
    CurrentObj->Allocate(0,2*10);
	//CreateCube(Vertex(48,16,16),32,32,32);
	
	CreateNGon(Vertex(48,48,0),64,8,Vertex(1,0,0),Vertex(0,1,0),Vertex(0,0,1),10);
    CalcTexCoord(CurrentObj,128,128,*Pos,0,0);
	CurrentObj->CalcAllPlanes();

	CurrentObj->BSPTree=new CBSPTree;
	CurrentObj->BSPTree->InitPolygons(CurrentObj,1,FALSE);

	SubObject(dk->FirstObject,dk->FirstObject->Next);
*/
	//dk->DelObject(dk->FirstObject->Next);

	//HollowObject(CurrentObj);

 
/*
	
    dk->AddObject();
    CurrentObj=dk->NextObject;
    //CurrentObj->Allocate(0,8);
	CurrentObj->Allocate(0,(2*10));
	//CreateCubeSpecial(Vertex(48,16,16),64,64,64);
	CreateNGon(Vertex(48,48,0),64,64,Vertex(1,0,0),Vertex(0,1,0),Vertex(0,0,1),10);
    CalcTexCoord(CurrentObj,128,128,*Pos,0,0);
	CurrentObj->CalcAllPlanes();

	CurrentObj->BSPTree=new CBSPTree;
	CurrentObj->BSPTree->InitPolygons(CurrentObj,1,FALSE);

	//SubObject(dk->FirstObject,dk->FirstObject->Next);

	//dk->DelObject(dk->FirstObject->Next);

	HollowObject(CurrentObj);
*/
	//dk->DelObject(CurrentObj);


// temp

#include "MapEdUtils.h"

extern "C" Desk *dk;
extern "C" Object *CurrentObj;
extern "C" Plan dap;
extern "C" OGLView *View;

#define CSG_NONE				0
#define CSG_DIFFERENCE			1
#define CSG_INTERSECTION		2
#define CSG_UNION				3

int g_iCSGMode=CSG_INTERSECTION;

int GetView()
{
    int ViewInd=dk->Active;
	if ((dk->ViewNg[ViewInd].vx==0)&&(dk->ViewNg[ViewInd].vy==0)&&(dk->ViewNg[ViewInd].vz==0)) return 1;//TEXT("Top");
	if ((dk->ViewNg[ViewInd].vx==-90)&&(dk->ViewNg[ViewInd].vy==0)&&(dk->ViewNg[ViewInd].vz==0)) return 2;//TEXT("Front");
	if ((dk->ViewNg[ViewInd].vx==-90)&&(dk->ViewNg[ViewInd].vy==0)&&(dk->ViewNg[ViewInd].vz==90)) return 3;//TEXT("Right");

	if ((dk->ViewNg[ViewInd].vx==0)&&(dk->ViewNg[ViewInd].vy==180)&&(dk->ViewNg[ViewInd].vz==180)) return 4;//TEXT("Bottom");
	if ((dk->ViewNg[ViewInd].vx==90)&&(dk->ViewNg[ViewInd].vy==180)&&(dk->ViewNg[ViewInd].vz==0)) return 5;//TEXT("Back");
	if ((dk->ViewNg[ViewInd].vx==270)&&(dk->ViewNg[ViewInd].vy==0)&&(dk->ViewNg[ViewInd].vz==270)) return 6;//TEXT("Left");

	return 999;
}


void UnionObject(Object *Obj1,Object *Obj2)
{
	int		  f;
	BOOL	  ClipSolid1 = FALSE, ClipSolid2 = FALSE;
	CBSPTree *CSGTree = NULL, *TGTTree = NULL, *CPYTree = NULL;

	ClipSolid1 = FALSE; ClipSolid2 = FALSE; 

	CSGTree = ((CBSPTree*)Obj1->BSPTree);
	
	// Store target tree for easy access
	TGTTree = ((CBSPTree*)Obj2->BSPTree);
	// Clip the tree against the CSG Tree
	CSGTree->ClipTree( CSGTree->RootNode, NULL, 0, TGTTree, ClipSolid1, TRUE );
	// First Make a copy of the CSG brush and manipulate this, instead
	// of the actual CSG brush, remember that we may need to add polys to several
	// intersecting brushes.
	CPYTree = CSGTree->CopyTree();
	TGTTree->ClipTree( TGTTree->RootNode, NULL, 0, CPYTree, ClipSolid2, FALSE);
	// Add all surviving polygons to the target tree
	for ( f = 0; f < CPYTree->PolyCount; f++ )
	{
		if ( !CPYTree->PolygonDeleted[f] ) TGTTree->AddPolygonEX( &CPYTree->Polygons[f] );
	} // Next f
	// Free Up the Copy of the CSG Tree
	//delete CPYTree; CPYTree = NULL;

}

void SubObject(Object *Obj2,Object *Obj1)
{
	int		  f;
	BOOL	  ClipSolid1 = FALSE, ClipSolid2 = FALSE;
	CBSPTree *CSGTree = NULL, *TGTTree = NULL, *CPYTree = NULL;

	ClipSolid1 = TRUE; ClipSolid2 = FALSE; 

	CSGTree = ((CBSPTree*)Obj1->BSPTree);

	// Store target tree for easy access
	TGTTree = ((CBSPTree*)Obj2->BSPTree);
	// Clip the tree against the CSG Tree
	CSGTree->ClipTree( CSGTree->RootNode, NULL, 0, TGTTree, ClipSolid1, TRUE );
	// First Make a copy of the CSG brush and manipulate this, instead
	// of the actual CSG brush, remember that we may need to add polys to several
	// intersecting brushes.
	CPYTree = CSGTree->CopyTree();
	TGTTree->ClipTree( TGTTree->RootNode, NULL, 0, CPYTree, ClipSolid2, FALSE);
	// When in Difference Mode Invert The Copied Trees polygons
	CPYTree->InvertPolys();
	// Add all surviving polygons to the target tree
	for ( f = 0; f < CPYTree->PolyCount; f++ )
	{
		if ( !CPYTree->PolygonDeleted[f] ) TGTTree->AddPolygonEX( &CPYTree->Polygons[f] );
	} // Next f
	// Free Up the Copy of the CSG Tree
	//delete CPYTree; CPYTree = NULL;
	//TGTTree->RenderBSPPolys(0);

	TGTTree->Commit(Obj2);
	Obj2->CalcTexCoord(128,128,Vertex(0,0,0),0,0);
}


bool AddObject(Object *Obj2,Object *Obj1)
{
	BOOL	  ClipSolid1 = FALSE, ClipSolid2 = FALSE;
	CBSPTree *CSGTree = NULL, *TGTTree = NULL, *CPYTree = NULL;

	int Oldnbf1,Oldnbf2;

	Oldnbf1=Obj1->nb2poly;
	Oldnbf2=Obj2->nb2poly;

	((CBSPTree*)Obj1->BSPTree)->ClipTree( ((CBSPTree*)Obj1->BSPTree)->RootNode, NULL, 0, ((CBSPTree*)Obj2->BSPTree), TRUE, TRUE);
	((CBSPTree*)Obj2->BSPTree)->ClipTree( ((CBSPTree*)Obj2->BSPTree)->RootNode, NULL, 0, ((CBSPTree*)Obj1->BSPTree), TRUE, FALSE);



	if ( (Obj1->BSPTree->PolyCount!=Oldnbf1)&&(Obj2->BSPTree->PolyCount!=Oldnbf2) )
	{
		Obj1->BSPTree->Commit(Obj1);
		Obj2->BSPTree->Commit(Obj2);//AddTo(Obj1);
		return true;
	}
	else
   
	{
		Obj1->BSPTree->Commit(Obj1);
		Obj2->BSPTree->Commit(Obj2);
		return false;
	}
	//dk->DelObject(daObj);
}

void UpdateBSPTrees( )
{
	int		  f;
	BOOL	  ClipSolid1 = FALSE, ClipSolid2 = FALSE;
	CBSPTree *CSGTree = NULL, *TGTTree = NULL, *CPYTree = NULL;
/*
	// Compile Mini-BSP Trees.
	for ( b = 0; b < BrushCount; b++ ){
		// Clear previously created tree
		if ( Brushes[b].BSPTree ) {
			delete ((CBSPTree*)Brushes[b].BSPTree);
			Brushes[b].BSPTree = NULL;
		} // End If
		if ( Brushes[b].BSPTree == NULL ) Brushes[b].BSPTree = new CBSPTree;
		((CBSPTree*)Brushes[b].BSPTree)->InitPolygons( &Brushes[b], 1, FALSE );
	} // Next Brush
*/
	Object *daObj;
	for (daObj=dk->FirstObject;daObj!=NULL;daObj=daObj->Next)
	{
		if (daObj->BSPTree)
		{
			delete daObj->BSPTree;
			daObj->BSPTree=NULL;
		}

		if (daObj->BSPTree==NULL)
			daObj->BSPTree=new CBSPTree;

		daObj->BSPTree->InitPolygons(daObj,1,FALSE);
	}

	
	// Setup our solid clipping flags
	switch ( g_iCSGMode ) 
	{
		case CSG_DIFFERENCE:
			ClipSolid1 = TRUE; ClipSolid2 = FALSE; 
			break;
		case CSG_INTERSECTION:
			ClipSolid1 = FALSE; ClipSolid2 = FALSE; 
			break;
	} // End Switch

/*
	if ( g_iCSGMode != CSG_NONE ) {
		// Store CSG Brush for easy access
		CSGTree = ((CBSPTree*)Brushes[g_iCSGBrush].BSPTree);
		// Perform op with CSG brush on each normal brush
		for ( b = 0; b < BrushCount; b++ ) {
			if ( b == g_iCSGBrush ) continue;
			if ( !BoundingBoxesIntersect(Brushes[g_iCSGBrush].Bounds, Brushes[b].Bounds) ) continue;
			// Store target tree for easy access
			TGTTree = ((CBSPTree*)Brushes[b].BSPTree);
			// Clip the tree against the CSG Tree
			CSGTree->ClipTree( CSGTree->RootNode, NULL, 0, TGTTree, ClipSolid1, TRUE );
			// First Make a copy of the CSG brush and manipulate this, instead
			// of the actual CSG brush, remember that we may need to add polys to several
			// intersecting brushes.
			CPYTree = CSGTree->CopyTree();
			TGTTree->ClipTree( TGTTree->RootNode, NULL, 0, CPYTree, ClipSolid2, FALSE);
			// When in Difference Mode Invert The Copied Trees polygons
			if ( g_iCSGMode == CSG_DIFFERENCE ) CPYTree->InvertPolys();
			// Add all surviving polygons to the target tree
			for ( f = 0; f < CPYTree->PolyCount; f++ ){
				if ( !CPYTree->PolygonDeleted[f] ) TGTTree->AddPolygonEX( &CPYTree->Polygons[f] );
			} // Next f
			// Free Up the Copy of the CSG Tree
			delete CPYTree; CPYTree = NULL;
			if ( g_iCSGMode == CSG_INTERSECTION) TGTTree->InitPolygons( &Brushes[b], 1, TRUE);
		} // Next Brush
	} // End if CSG Mode != CSG_NONE
*/
	if ( g_iCSGMode != CSG_NONE ) 
	{
		// Store CSG Brush for easy access
		CSGTree = ((CBSPTree*)dk->FirstObject->BSPTree);
		// Perform op with CSG brush on each normal brush
		for ( daObj=dk->FirstObject->Next; daObj!=NULL; daObj=daObj->Next) 
		{
			//if ( b == g_iCSGBrush ) continue;
			//if ( !BoundingBoxesIntersect(Brushes[g_iCSGBrush].Bounds, Brushes[b].Bounds) ) continue;

			// Store target tree for easy access
			TGTTree = ((CBSPTree*)daObj->BSPTree);
			// Clip the tree against the CSG Tree
			CSGTree->ClipTree( CSGTree->RootNode, NULL, 0, TGTTree, ClipSolid1, TRUE );
			// First Make a copy of the CSG brush and manipulate this, instead
			// of the actual CSG brush, remember that we may need to add polys to several
			// intersecting brushes.
			CPYTree = CSGTree->CopyTree();
			TGTTree->ClipTree( TGTTree->RootNode, NULL, 0, CPYTree, ClipSolid2, FALSE);
			// When in Difference Mode Invert The Copied Trees polygons
			if ( g_iCSGMode == CSG_DIFFERENCE ) CPYTree->InvertPolys();
			// Add all surviving polygons to the target tree
			for ( f = 0; f < CPYTree->PolyCount; f++ ){
				if ( !CPYTree->PolygonDeleted[f] ) TGTTree->AddPolygonEX( &CPYTree->Polygons[f] );
			} // Next f
			// Free Up the Copy of the CSG Tree
			delete CPYTree; CPYTree = NULL;
			TGTTree->RenderBSPPolys(0);
			//if ( g_iCSGMode == CSG_INTERSECTION) TGTTree->InitPolygons( daObj, 1, TRUE);
			//TGTTree->RenderBSPPolys(0);
		} // Next Brush
	} // End if CSG Mode != CSG_NONE


	/*
	// Now perform a union on all the resulting Trees.
	// THIS is how we perform pre-compile Hidden Surface removal.
	for ( b = 0; b < BrushCount; b++ ) {
		if ( b == g_iCSGBrush && g_iCSGMode != CSG_NONE) continue;
		((CBSPTree*)Brushes[b].BSPTree)->m_bMisc = FALSE;
		for ( int o = 0; o < BrushCount; o++ ) {
			if ( o == b || (o == g_iCSGBrush && g_iCSGMode != CSG_NONE)) continue;
			if (((CBSPTree*)Brushes[o].BSPTree)->m_bMisc == TRUE) continue;
			if ( BoundingBoxesIntersect(Brushes[o].Bounds, Brushes[b].Bounds) == TRUE ) {
				((CBSPTree*)Brushes[o].BSPTree)->ClipTree( ((CBSPTree*)Brushes[o].BSPTree)->RootNode, NULL, 0, ((CBSPTree*)Brushes[b].BSPTree), TRUE, TRUE);
				((CBSPTree*)Brushes[b].BSPTree)->ClipTree( ((CBSPTree*)Brushes[b].BSPTree)->RootNode, NULL, 0, ((CBSPTree*)Brushes[o].BSPTree), TRUE, FALSE);
			} //End If Bound Boxes Intersect
			// Because we do a role reversal for each brush in the tree
			// the below line ensures that each tree is only clipped once.
			((CBSPTree*)Brushes[b].BSPTree)->m_bMisc = TRUE;
		} // End For o
	} // End For b
*/

	Object *g_iCSGBrush=dk->FirstObject;

	// Now perform a union on all the resulting Trees.
	// THIS is how we perform pre-compile Hidden Surface removal.
	for ( daObj=dk->FirstObject; daObj!=NULL; daObj=daObj->Next ) 
	{
		if ( daObj == g_iCSGBrush && g_iCSGMode != CSG_NONE) continue;
		((CBSPTree*)daObj->BSPTree)->m_bMisc = FALSE;
		for ( Object *daO=dk->FirstObject; daO!=NULL; daO=daO->Next ) 
		{
			if ( daO == daObj || (daO == g_iCSGBrush && g_iCSGMode != CSG_NONE)) continue;
			if (((CBSPTree*)daO->BSPTree)->m_bMisc == TRUE) continue;

			//if ( BoundingBoxesIntersect(Brushes[o].Bounds, Brushes[b].Bounds) == TRUE ) 
			{
				((CBSPTree*)daO->BSPTree)->ClipTree( ((CBSPTree*)daO->BSPTree)->RootNode, NULL, 0, ((CBSPTree*)daObj->BSPTree), TRUE, TRUE);
				((CBSPTree*)daObj->BSPTree)->ClipTree( ((CBSPTree*)daObj->BSPTree)->RootNode, NULL, 0, ((CBSPTree*)daO->BSPTree), TRUE, FALSE);
			} //End If Bound Boxes Intersect
			// Because we do a role reversal for each brush in the tree
			// the below line ensures that each tree is only clipped once.
			((CBSPTree*)daObj->BSPTree)->m_bMisc = TRUE;
		} // End For o
	} // End For b

	/*
	// Compile final BSP if enabled
	if (g_bCompileFinal ) {	
		// Delete the CSG Brush as we must not include
		// this brush in the final BSP Compile process.
		if ( g_iCSGMode != CSG_NONE ) {
			delete (CBSPTree*)Brushes[g_iCSGBrush].BSPTree;
			Brushes[g_iCSGBrush].BSPTree = NULL;
		} // End If
		if ( FinalBSP == NULL ) FinalBSP = new CBSPTree;
		// Do the final compile
		FinalBSP->InitPolygons( Brushes, BrushCount, TRUE);
	} // End If
	*/
}

void HollowObject(Object *Obj)
{
	int i,j,k;


	Obj->CalcAllPlanes();


	if (Obj->BSPTree==NULL)
	{
		Obj->BSPTree=new CBSPTree;
		Obj->BSPTree->InitPolygons(Obj,1,FALSE);
	}

    //i=0;
	for (i=0;i<Obj->nb2poly;i++)
	{
		dk->AddObject();
		dk->NextObject->AllocatePoly(0,Obj->pl[i].nb2vert*2);

		int nb2Poly=2+Obj->pl[i].nb2vert;//+(2*(Obj->pl[i].nb2vert-2));

		dk->NextObject->AllocatePoly(nb2Poly,0);

		int nSide=Obj->pl[i].nb2vert;
		dk->NextObject->AllocateUV(0,(nSide*2)+(nSide*4));

		

		// caping
		dk->NextObject->pl[0].Allocate(dk->NextObject,1,nSide);
		dk->NextObject->pl[1].Allocate(dk->NextObject,1,nSide);
		int TexAv=0;

		for (j=0;j<nSide;j++)
		{
			dk->NextObject->pl[0].nbvert[nSide-j-1]=(nSide-1-j)*2;
			dk->NextObject->pl[0].Tex[0][nSide-j-1]=TexAv++;

			dk->NextObject->pl[1].nbvert[nSide-j-1]=(j*2)+1;
			dk->NextObject->pl[1].Tex[0][nSide-j-1]=TexAv++;

		}

		// get center of polygon
		Vertex PolyCenter;

		for (j=0;j<nSide;j++)
		{
			PolyCenter+=Obj->pv[Obj->pl[i].nbvert[j]];
		}
		PolyCenter/=nSide;

		// extruding 

		for (j=0;j<nSide;j++)
		{
			dk->NextObject->pl[j+2].Allocate(dk->NextObject,1,4);

			dk->NextObject->pv[j*2]=(Obj->pv[Obj->pl[i].nbvert[j]]-PolyCenter);
			dk->NextObject->pv[j*2].vx*=3;
			dk->NextObject->pv[j*2].vy*=3;
			dk->NextObject->pv[j*2].vz*=3;

			dk->NextObject->pv[j*2+1]=dk->NextObject->pv[j*2];

			dk->NextObject->pv[j*2]+=PolyCenter;
			

			//*dk->NextObject->pv[j*2+1]=(*Obj->pv[Obj->pl[i].nbvert[j]]-PolyCenter);
			//*dk->NextObject->pv[j*2+1]*=100.0f;
			dk->NextObject->pv[j*2+1]-=(Obj->pl[i].Normale*8.0f);
			dk->NextObject->pv[j*2+1]+=PolyCenter;

				
			dk->NextObject->pl[j+2].nbvert[3]=(j*2);
			dk->NextObject->pl[j+2].nbvert[2]=((j*2)+2)%(nSide*2);
			dk->NextObject->pl[j+2].nbvert[1]=((j*2)+3)%(nSide*2);
			dk->NextObject->pl[j+2].nbvert[0]=((j*2)+1)%(nSide*2);

			for (k=0;k<4;k++)
				dk->NextObject->pl[j+2].Tex[0][k]=TexAv++;//k+(nSide*2)+(j*nSide);
		}

		//CalcTexCoord(dk->NextObject,128,128,*dk->NextObject->pv[0],0,0);

        dk->NextObject->CalcAllPlanes();
        Obj->CalcAllPlanes();

		dk->NextObject->BSPTree=new CBSPTree;
		dk->NextObject->BSPTree->InitPolygons(dk->NextObject,1,FALSE);

		UnionObject(Obj,dk->NextObject);
        //AddObject(dk->NextObject,Obj);
		dk->NextObject->BSPTree->Commit(dk->NextObject);
        //Obj->BSPTree->Commit(Obj);
		if (Obj->pl[0].Maps[0]!=NULL)
			dk->NextObject->ApplyTexture(Obj->pl[0].Maps[0]);
		else
			dk->NextObject->ApplyTexture(Obj->Tex1);
	    dk->NextObject->CalcTexCoord(128,128,Vertex(0,0,0),0,0);

	}
	dk->DelObject(Obj);
}

void CreateCube(Vertex Start,double X,double Y,double Z,bool Snap)
{
    Vertex End;
    Object *Obj;
    int i;
    double Valu=X/128.0f;
    double Valv=Y/128.0f;
//    double Valw=Z/128.0f;

    if (CurrentObj==NULL) Obj=dk->NextObject;
        else Obj=CurrentObj;

	Obj->pv[0]=Vertex(0,0,0)+Start;
	Obj->pv[1]=Vertex(X,0,0)+Start;
	Obj->pv[2]=Vertex(X,Y,0)+Start;
	Obj->pv[3]=Vertex(0,Y,0)+Start;
	Obj->pv[4]=Vertex(0,0,Z)+Start;
	Obj->pv[5]=Vertex(X,0,Z)+Start;
	Obj->pv[6]=Vertex(X,Y,Z)+Start;
	Obj->pv[7]=Vertex(0,Y,Z)+Start;
    for (i=0;i<8;i++)
    {
        Obj->pv[i].Snap(Vertex(8,8,8));

    }

    Obj->AllocateUV(0,24);
    for (i=0;i<24;i++)
    {
        Obj->puv[0][i].u=0;
        Obj->puv[0][i].v=0;
    }
    Obj->AllocatePoly(6,0);
    for (i=0;i<6;i++)
    {
        Obj->pl[i].Allocate(dk->NextObject,1,4);
        Obj->pl[i].Tex[0][0]=0;
        Obj->pl[i].Tex[0][1]=0;
        Obj->pl[i].Tex[0][2]=0;
        Obj->pl[i].Tex[0][3]=0;
    }
    // bottom
    Obj->pl[0].nbvert[0]=3;
    Obj->pl[0].nbvert[1]=2;
    Obj->pl[0].nbvert[2]=1;
    Obj->pl[0].nbvert[3]=0;
    // top
    Obj->pl[1].nbvert[0]=4;
    Obj->pl[1].nbvert[1]=5;
    Obj->pl[1].nbvert[2]=6;
    Obj->pl[1].nbvert[3]=7;
    // front
    Obj->pl[2].nbvert[0]=7;
    Obj->pl[2].nbvert[1]=3;
    Obj->pl[2].nbvert[2]=0;
    Obj->pl[2].nbvert[3]=4;
    // back
    Obj->pl[3].nbvert[0]=1;
    Obj->pl[3].nbvert[1]=2;
    Obj->pl[3].nbvert[2]=6;
    Obj->pl[3].nbvert[3]=5;
    // left  
    Obj->pl[4].nbvert[0]=6;
    Obj->pl[4].nbvert[1]=2;
    Obj->pl[4].nbvert[2]=3;
    Obj->pl[4].nbvert[3]=7;
    // right
    Obj->pl[5].nbvert[0]=0;
    Obj->pl[5].nbvert[1]=1;
    Obj->pl[5].nbvert[2]=5;
    Obj->pl[5].nbvert[3]=4;

    //CalcTexCoord(Obj,128,128,Start,tmpuv);
    Obj->Selected=true;
}

void CreateCubeSpecial(Vertex Start,double X,double Y,double Z,bool Snap)
{
    Vertex End;
    Object *Obj;
    int i;
    double Valu=X/128.0f;
    double Valv=Y/128.0f;
//    double Valw=Z/128.0f;

    if (CurrentObj==NULL) Obj=dk->NextObject;
        else Obj=CurrentObj;

	Obj->pv[0]=Vertex(0,0,0)+Start;
	Obj->pv[1]=Vertex(X,0,0)+Start;
	Obj->pv[2]=Vertex(X,Y,0)+Start;
	Obj->pv[3]=Vertex(0,Y,0)+Start;

	Obj->pv[4]=Vertex(0,0,Z)+Start;
	Obj->pv[5]=Vertex((X/2),0,Z)+Start;
	Obj->pv[6]=Vertex((X/2),(Y/2),Z)+Start;
	Obj->pv[7]=Vertex(0,(Y/2),Z)+Start;

    for (i=0;i<8;i++)
    {
        Obj->pv[i].Snap(Vertex(8,8,8));

    }

    Obj->AllocateUV(0,24);

    for (i=0;i<24;i++)
    {
        Obj->puv[0][i].u=0;
        Obj->puv[0][i].v=0;
    }

    Obj->AllocatePoly(6,0);

    for (i=0;i<6;i++)
    {
        Obj->pl[i].Allocate(dk->NextObject,1,4);
        Obj->pl[i].Tex[0][0]=0;
        Obj->pl[i].Tex[0][1]=0;
        Obj->pl[i].Tex[0][2]=0;
        //Obj->pl[i].Tex[0][3]=0;
    }

    // bottom
    Obj->pl[0].nbvert[0]=3;
    Obj->pl[0].nbvert[1]=2;
    Obj->pl[0].nbvert[2]=1;
    Obj->pl[0].nbvert[3]=0;
    // top
    Obj->pl[1].nbvert[0]=4;
    Obj->pl[1].nbvert[1]=5;
    Obj->pl[1].nbvert[2]=6;
    Obj->pl[1].nbvert[3]=7;
    // front
    Obj->pl[2].nbvert[0]=7;
    Obj->pl[2].nbvert[1]=3;
    Obj->pl[2].nbvert[2]=0;
    Obj->pl[2].nbvert[3]=4;
    // back
    Obj->pl[3].nbvert[0]=1;
    Obj->pl[3].nbvert[1]=2;
    Obj->pl[3].nbvert[2]=6;
    Obj->pl[3].nbvert[3]=5;
    // left  
    Obj->pl[4].nbvert[0]=6;
    Obj->pl[4].nbvert[1]=2;
    Obj->pl[4].nbvert[2]=3;
    Obj->pl[4].nbvert[3]=7;
    // right
    Obj->pl[5].nbvert[0]=0;
    Obj->pl[5].nbvert[1]=1;
    Obj->pl[5].nbvert[2]=5;
    Obj->pl[5].nbvert[3]=4;

    Obj->Selected=true;
}

void CreateNGon(Vertex Start,double Length,double Height,Vertex mX,Vertex mY,Vertex mZ,int nSide)
{
    Vertex End;
    Object *Obj;
    int i,j;

    if (CurrentObj==NULL) Obj=dk->NextObject;
        else Obj=CurrentObj;

    for (i=0;i<nSide;i++)
    {
        double tx=(cos(((2*PI)/nSide)*i)*Length);
        double ty=(sin(((2*PI)/nSide)*i)*Length);

        Vertex tmp=(mX*tx)+(mY*ty)+Start;
	    Obj->pv[i*2]=tmp;

	    tmp=(mX*tx)+(mY*ty)+(mZ*Height)+Start;
        Obj->pv[i*2+1]=tmp;
    }

    Obj->AllocateUV(0,(nSide*2)+(4*nSide));

    Obj->AllocatePoly(2+nSide,0);

    Obj->pl[0].Allocate(dk->NextObject,1,nSide);
    Obj->pl[1].Allocate(dk->NextObject,1,nSide);

    for (i=0;i<nSide;i++)
    {
        Obj->pl[2+i].Allocate(dk->NextObject,1,4);

        Obj->pl[0].nbvert[i]=(nSide-1-i)*2;
        Obj->pl[0].Tex[0][i]=i;

        Obj->pl[1].nbvert[i]=(i*2)+1;
        Obj->pl[1].Tex[0][i]=i+nSide;
    }

    for (i=0;i<nSide;i++)
    {
        Obj->pl[i+2].nbvert[0]=(i*2);
        Obj->pl[i+2].nbvert[1]=((i*2)+2)%(nSide*2);
        Obj->pl[i+2].nbvert[2]=((i*2)+3)%(nSide*2);
        Obj->pl[i+2].nbvert[3]=((i*2)+1)%(nSide*2);

        for (j=0;j<4;j++)
            Obj->pl[i+2].Tex[0][j]=j+(nSide*2)+(i*nSide);
    }

    Obj->Selected=true;
}



void SetSelectedNGon(int nbSide)
{
	int i;

	dk->DeleteBufVert();

	Object *daObj=dk->FirstObject;
	while (daObj!=NULL)
	{
		if (daObj->Selected)
		{
			CurrentObj=daObj;

			Vertex daMin,daMax,daCenter;
			Vertex VX,VY,VZ;

			daMin=daObj->Min;
			daMax=daObj->Max;
			daCenter=(daMin+((daMax-daMin))/2.0f);

			double Length,Height;

			switch(GetView())
			{
			
			case 1:
				VX=Vertex(1,0,0);
				VY=Vertex(0,1,0);
				VZ=Vertex(0,0,1);
				Length=Pythagore(daMax.vx-daMin.vx,daMax.vy-daMin.vy)/2;
				Height=daMax.vz-daMin.vz;
				daCenter.vz=0;
				break;
			case 2:
				VX=Vertex(1,0,0);
				VY=Vertex(0,0,-1);
				VZ=Vertex(0,1,0);
				Length=Pythagore(daMax.vx-daMin.vx,daMax.vz-daMin.vz)/2;
				Height=daMax.vy-daMin.vy;
				daCenter.vy=0;
				break;
			case 3:
				VX=Vertex(0,-1,0);
				VY=Vertex(0,0,-1);
				VZ=Vertex(1,0,0);
				Length=Pythagore(daMax.vx-daMin.vx,daMax.vy-daMin.vy)/2;
				Height=daMax.vy-daMin.vy;
				daCenter.vy=0;
				break;
			case 4:
				VX=Vertex(-1,0,0);
				VY=Vertex(0,-1,0);
				VZ=Vertex(0,0,-1);
				Length=Pythagore(daMax.vx-daMin.vx,daMax.vy-daMin.vy)/2;
				Height=daMax.vz-daMin.vz;
				daCenter.vz=0;
				break;
			case 5:
				VX=Vertex(-1,0,0);
				VY=Vertex(0,0,1);
				VZ=Vertex(0,-1,0);
				Length=Pythagore(daMax.vx-daMin.vx,daMax.vy-daMin.vy)/2;
				Height=daMax.vz-daMin.vz;
				daCenter.vz=0;
				break;
			case 6:
				VX=Vertex(0,1,0);
				VY=Vertex(0,0,1);
				VZ=Vertex(-1,0,0);
				Length=Pythagore(daMax.vx-daMin.vx,daMax.vy-daMin.vy)/2;
				Height=daMax.vz-daMin.vz;
				daCenter.vz=0;
				break;
			default:
				VX=Vertex(1,0,0);
				VY=Vertex(0,1,0);
				VZ=Vertex(0,0,1);
				Length=Pythagore(daMax.vx-daMin.vx,daMax.vy-daMin.vy)/2;
				Height=daMax.vz-daMin.vz;
				daCenter.vz=0;
				break;


			}
			Length/=1.4142135623730950488016887242097f; //sqrt(2)


			//CurrentObj->AllocatePoly(nbSide+2,2*nbSide);
			daObj->AllocatePoly(0,2*nbSide);
			CreateNGon(daCenter,Length,Height,VX,VY,VZ,nbSide);
			CurrentObj->CalcTexCoord(128,128,CurrentObj->pv[CurrentObj->pl[0].nbvert[0]],0,0);

			// add vertex to buffer

			for (i=0;i<daObj->nb2vert;i++)
			{
				dk->AddBufVert(&daObj->pv[i],daObj);
				daObj->pv[i].Selected=true;
			}

		}
		daObj=daObj->Next;
	}

}

void Symetry(Vertex value)
{

	Vertex daMin,daMax,daCenter;
	Vertex VX,VY,VZ;

	daCenter=dk->cSel->GetCenterOfSel(&daMin,&daMax);
/*
	daMin=daObj->GetMinOf();
	daMax=daObj->GetMaxOf();
	daCenter=(daMin+((daMax-daMin))/2.0f);
*/
    VertBuf *daBufVert;
	Vertex temp,temp2;

    daBufVert=dk->FirstBufVert;
    while(daBufVert!=NULL)
    {
		temp=daBufVert->AncVal;
		temp2=temp;
		
		if (value.vx==1) temp2.vx=temp.vx+2*(daCenter.vx-temp.vx);
		if (value.vy==1) temp2.vy=temp.vy+2*(daCenter.vy-temp.vy);
		if (value.vz==1) temp2.vz=temp.vz+2*(daCenter.vz-temp.vz);

        daBufVert->IsNow(temp2);

        daBufVert=daBufVert->Next;
    }

	dk->UpdateBuf();
}


void RotateBuf(Vertex Vect,double ng)
{
	Vertex daMin,daMax,daCenter;
	Vertex value,value2;
    double nx2,ny2,nz2;
    double m1,m2,m3,m4,m5,m6,m7,m8,m9;


	daCenter=dk->cSel->GetCenterOfSel(&daMin,&daMax);
	/*
	daMin=dk->cSel->get
	daMax=daObj->GetMaxOf();
	daCenter=(daMin+((daMax-daMin))/2.0f);
*/
	ng*=PI;
	ng/=180;

    nx2=(Vect.vx*Vect.vx);
    ny2=(Vect.vy*Vect.vy);
    nz2=(Vect.vz*Vect.vz);

    m1=(nx2+((1-nx2)*cos(ng)));
    m2=((Vect.vx*Vect.vy*(1-cos(ng)))-(Vect.vz*sin(ng)));
    m3=((Vect.vx*Vect.vz*(1-cos(ng)))+(Vect.vy*sin(ng)));
    m4=((Vect.vx*Vect.vy*(1-cos(ng)))+(Vect.vz*sin(ng)));
    m5=(ny2+((1-ny2)*cos(ng)));
    m6=((Vect.vy*Vect.vz*(1-cos(ng)))-(Vect.vx*sin(ng)));
    m7=((Vect.vx*Vect.vz*(1-cos(ng)))-(Vect.vy*sin(ng)));
    m8=((Vect.vy*Vect.vz*(1-cos(ng)))+(Vect.vx*sin(ng)));
    m9=(nz2+((1-nz2)*cos(ng)));

	VertBuf *daVert;

	daVert=dk->FirstBufVert;
	while(daVert!=NULL)
	{
		value=(daVert->AncVal-daCenter);

		value2.vx=value.vx*m1+value.vy*m2+value.vz*m3;
		value2.vy=value.vx*m4+value.vy*m5+value.vz*m6;
		value2.vz=value.vx*m7+value.vy*m8+value.vz*m9;

		daVert->IsNow((value2+daCenter));

		daVert=daVert->Next;
	}

	dk->UpdateBuf();
}

void HollowSelectedObject(void)
{
	for (Object *daObj=dk->FirstObject;daObj!=NULL;daObj)
	{
		Object *daNext=daObj->Next;

		UpdateBspTree(daObj);

		if (daObj->Selected)
			HollowObject(daObj);

		daObj=daNext;
	}

	dk->cSel->UnSelectAll(false);
	dk->DeleteBufVert();
}

void UpdateBspTree(Object *daObj)
{
	daObj->CalcAllPlanes();

	if (daObj->BSPTree)
	{
		delete daObj->BSPTree;
		daObj->BSPTree=NULL;
	}

	if (daObj->BSPTree==NULL)
		daObj->BSPTree=new CBSPTree;

	daObj->BSPTree->InitPolygons(daObj,1,FALSE);
}
void SubSelectedObject(void)
{
	for (Object *daObj=dk->FirstObject;daObj!=NULL;daObj=daObj->Next)
	{
		Object *daNext=daObj->Next;

		if (daObj->Selected)
		{
			for (Object *daObj2=dk->FirstObject;daObj2!=NULL;daObj2=daObj2->Next)
			{
				if (daObj!=daObj2)
				{
					UpdateBspTree(daObj);
					UpdateBspTree(daObj2);

					SubObject(daObj2,daObj);
					//daObj2->BSPTree->Commit(daObj2);
				}
			}
		}
	}

	dk->cSel->UnSelectAll(false);
	dk->DeleteBufVert();
}

void AddSelectedObject(void)
{
	for (Object *daObj=dk->FirstObject;daObj!=NULL;)
	{
		Object *ObjTmp=daObj->Next;
		Object *daNext=daObj->Next;

		if (daObj->Selected)
		{
			Object *daObj2=daObj->Next;
			for (;daObj2!=NULL;daObj2=daObj2->Next)
			{
				if (daObj2->Selected)
				{
					UpdateBspTree(daObj);
					UpdateBspTree(daObj2);

					if (AddObject(daObj,daObj2))
					{
						// addition successfull
						//dk->DelObject(daObj);
						break;
					}
					else
					{
						// no addition at all

					}
				}
			}
		}
		daObj=ObjTmp;
	}

	dk->cSel->UnSelectAll(false);
	dk->DeleteBufVert();
}

void ApplyTexture(char *TexName)
{
	for (Object *daObj=dk->FirstObject;daObj!=NULL;daObj=daObj->Next)
	{
		if (daObj->Selected)
		{
			CTexture *daTex;
			daTex=dk->AddTex(TexName);
			daTex->Type=TEXTURE_FILE;
			daTex->Load();
//			strcpy(daObj->TexName1,TexName);
			daObj->Tex1=daTex;

		}
	}

}

Object *BuildCutter(Vertex v1,Vertex v2)
{

    Vertex End;
    Object *Obj;
    int i;

	Vertex Dif=v2-v1;
	Vertex Zd;

	dap.PlanOfView(View,dk->Active);
	/*

	if (Dif.vx==0) Zd.vx=10;
	if (Dif.vy==0) Zd.vy=10;
	if (Dif.vz==0) Zd.vz=10;
*/
	Zd=dap.pZ;
	Vertex Start(0,0,0);
	Zd.vx*=1000;
	Zd.vy*=1000;
	Zd.vz*=1000;



	Obj=new Object();
	Obj->AllocatePoly(0,8);

	Dif.vx*=100;
	Dif.vy*=100;
	Dif.vz*=100;

	Obj->pv[0]=v1-(Zd)-(Dif);
	Obj->pv[1]=v1+(Zd)-(Dif);
	Obj->pv[2]=v2+(Zd)+(Dif);
	Obj->pv[3]=v2-(Zd)+(Dif);

	Vertex Normale;
	Vertex *dpv=Obj->pv;

	Normale.Cross(dpv[1]-dpv[0], dpv[2]-dpv[0]);
	Normale.Normalize();

	Normale.vx*=1000;
	Normale.vy*=1000;
	Normale.vz*=1000;

	Obj->pv[4]=v1-Zd-(Normale)-(Dif);
	Obj->pv[5]=v1+Zd-(Normale)-(Dif);
	Obj->pv[6]=v2+Zd-(Normale)+(Dif);
	Obj->pv[7]=v2-Zd-(Normale)+(Dif);


    Obj->AllocateUV(0,24);
    for (i=0;i<24;i++)
    {
        Obj->puv[0][i].u=0;
        Obj->puv[0][i].v=0;
    }
    Obj->AllocatePoly(6,0);
    for (i=0;i<6;i++)
    {
        Obj->pl[i].Allocate(dk->NextObject,1,4);
        Obj->pl[i].Tex[0][0]=0;
        Obj->pl[i].Tex[0][1]=0;
        Obj->pl[i].Tex[0][2]=0;
        Obj->pl[i].Tex[0][3]=0;
    }
    // bottom
    Obj->pl[0].nbvert[0]=3;
    Obj->pl[0].nbvert[1]=2;
    Obj->pl[0].nbvert[2]=1;
    Obj->pl[0].nbvert[3]=0;
    // top
    Obj->pl[1].nbvert[0]=4;
    Obj->pl[1].nbvert[1]=5;
    Obj->pl[1].nbvert[2]=6;
    Obj->pl[1].nbvert[3]=7;
    // front
    Obj->pl[2].nbvert[0]=7;
    Obj->pl[2].nbvert[1]=3;
    Obj->pl[2].nbvert[2]=0;
    Obj->pl[2].nbvert[3]=4;
    // back
    Obj->pl[3].nbvert[0]=1;
    Obj->pl[3].nbvert[1]=2;
    Obj->pl[3].nbvert[2]=6;
    Obj->pl[3].nbvert[3]=5;
    // left  
    Obj->pl[4].nbvert[0]=6;
    Obj->pl[4].nbvert[1]=2;
    Obj->pl[4].nbvert[2]=3;
    Obj->pl[4].nbvert[3]=7;
    // right
    Obj->pl[5].nbvert[0]=0;
    Obj->pl[5].nbvert[1]=1;
    Obj->pl[5].nbvert[2]=5;
    Obj->pl[5].nbvert[3]=4;

    //CalcTexCoord(Obj,128,128,Start,tmpuv);
    Obj->Selected=true;

	Obj->CalcAllPlanes();
	Obj->BSPTree=new CBSPTree;
	Obj->BSPTree->InitPolygons(Obj,1,FALSE);

	return Obj;
}

int GetNbSelectedObjects(void)
{
	int nbObjSel=0;

	for (Object *daObj2=dk->FirstObject;daObj2!=NULL;daObj2=daObj2->Next)
		if (daObj2->Selected) nbObjSel++;

	return nbObjSel;
}
