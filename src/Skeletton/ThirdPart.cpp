#include "stdafx.h"

#include "ThirdPart.h"


// -- Implementation ----------------------------------------------------------

AnimatKF::AnimatKF(AnimatKF *daPrev,AnimatKF *daNext)
{
	//Name=new char [32];
	//SkelName=new char [32];
	Prev=daPrev;
	Next=daNext;
	FirstKF=NULL;
	NextKF=NULL;
	nbFrames=0;
	nbKF=0;
};

AnimatKF::~AnimatKF() 
{
	//delete [] SkelName;
	//delete [] Name;
};


void AnimatKF::AddKF(void)
{        
	if (FirstKF==NULL)
    {
        FirstKF=new (KF)(NULL,NULL);
        NextKF=FirstKF;
    }
    else
    {
        NextKF->Next=new (KF)(NextKF,NULL);
        NextKF=NextKF->Next;
    }
	nbKF++;
}


void AnimatKF::DelKF(KF *daKF)
{
    if (daKF==FirstKF)
        FirstKF=FirstKF->Next;

    if (daKF==NextKF)
        NextKF=NextKF->Prev;

    if (daKF->Next!=NULL)
        daKF->Next->Prev=daKF->Prev;

    if (daKF->Prev!=NULL)
        daKF->Prev->Next=daKF->Next;

	nbKF--;

    delete daKF;
}

void AnimatKF::DelKFAtFrame(int daFrame)
{
	KF *daKF,*daKF2;

	daKF=FirstKF;
	while (daKF!=NULL)
	{
		daKF2=daKF->Next;

		if (daKF->Key==daFrame)
			DelKF(daKF);

		daKF=daKF2;
	}
}

int AnimatKF::FindKFBefore(int daFrame)
{
	KF *daKF;
	int PrevKF=0;

	daKF=FirstKF;
	while (daKF!=NULL)
	{
		if ((daKF->Key<daFrame)&&(daKF->Key>PrevKF))
			PrevKF=daKF->Key;

		daKF=daKF->Next;
	}
	return PrevKF;
}

int AnimatKF::FindKFAfter(int daFrame)
{
	KF *daKF;
	int NextKF=nbFrames;

	daKF=FirstKF;
	while (daKF!=NULL)
	{
		if ((daKF->Key>daFrame)&&(daKF->Key<NextKF))
			NextKF=daKF->Key;

		daKF=daKF->Next;
	}
	return NextKF;
}

void AnimatKF::RescaleAndSet(int daFrame)
{
	KF *daKF;
	int NextKF=nbFrames;
	float Factor=nbFrames;
	float cFact;
	Factor/=(float)daFrame;


	daKF=FirstKF;
	while (daKF!=NULL)
	{
		cFact=daKF->Key;
		cFact/=Factor;
		daKF->Key=cFact;

		daKF=daKF->Next;
	}
	nbFrames=daFrame;
}


Vertex AnimatKF::FindRot(CKBone *dabone,int Frame)
{
	Vertex value;
	KF *daKF;
	Vertex BeforeRot,AfterRot;
	//double bfrx,bfry,bfrz,afrx,afry,afrz;
	int BeforeKey=-1,AfterKey=99999;

	daKF=FirstKF;
	while (daKF!=NULL)
	{
		
		if (daKF->BDest==dabone)
		{
			// exact key
			if (daKF->Key==Frame)
				return Vertex(daKF->rx,daKF->ry,daKF->rz);

			// before key
			if ((daKF->Key>BeforeKey)&&(daKF->Key<=Frame))
			{
				BeforeKey=daKF->Key;
				//BeforeRot=daKF->Rot;
				BeforeRot.x=daKF->rx;
				BeforeRot.y=daKF->ry;
				BeforeRot.z=daKF->rz;

			}

			// after key

			if ((daKF->Key<AfterKey)&&(daKF->Key>=Frame))
			{
				AfterKey=daKF->Key;
				//AfterRot=daKF->Rot;
				AfterRot.x=daKF->rx;
				AfterRot.y=daKF->ry;
				AfterRot.z=daKF->rz;
			}

		}

		daKF=daKF->Next;
	}

	// linear interpolate

	if (AfterKey==99999)
	{
		//AfterRot=BeforeRot;
		return BeforeRot;
	}

	if (BeforeKey==-1)
	{
		BeforeKey=0;
	}

	value=BeforeRot+(((AfterRot-BeforeRot)/(AfterKey-BeforeKey))*(Frame-BeforeKey));


	return value;
}

void AnimatKF::UpdateKeyFrame(int daKey,CKBone *daBone,Vertex ng)
{
	KF *daKF;
	bool HasFound=false;

	daKF=FirstKF;
	while(daKF!=NULL)
	{
		
		if ((daKF->Key==daKey)&&(daKF->BDest==daBone))
		{
			HasFound=true;

//			daKF->Rot=ng;
			daKF->rx=ng.x;
			daKF->ry=ng.y;
			daKF->rz=ng.z;

		}

		daKF=daKF->Next;
	}

	if (!HasFound)
	{
		AddKF();
		strcpy(NextKF->BoneName,daBone->Name);
		NextKF->Key=daKey;
		NextKF->BDest=daBone;
		//NextKF->Rot=ng;
		NextKF->rx=ng.x;
		NextKF->ry=ng.y;
		NextKF->rz=ng.z;
	}
	
}

void AnimatKF::RenderFrame(int Frame)
{
	for (int i=0;i<daSkel->BoneCount;i++)
	{
		daSkel->pbs[i]->Rot=FindRot(daSkel->pbs[i],Frame);

	}

	daSkel->BuildMatrix(1);
}

void AnimatKF::SetSkelName(CString daSkelName)
{
	SkelName=daSkelName;
}

void AnimatKF::SetName(CString daName)
{
	Name=daName;
}