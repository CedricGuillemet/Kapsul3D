#if !defined(THIRDPART_H_)
#define THIRDPART_H_
// -- Class KF ----------------------------------------------------------------

class KF
{
public:
	KF(KF *daPrev,KF *daNext) 
	{
		Prev=daPrev;
		Next=daNext;
		//BoneName=new char [32];
	};

	~KF() 
	{
		//delete [] BoneName;
	};


	int Key;
	CKBone *BDest;

	//Vertex Rot;
	double rx,ry,rz;
	char BoneName[32];

	KF *PIdem,*NIdem;
	KF *Prev,*Next;
};

// -- Class AnimatKF ----------------------------------------------------------

class AnimatKF
{
public:
	//
	AnimatKF(AnimatKF *daPrev,AnimatKF *daNext);
	~AnimatKF();

	//

	void AddKF(void);
	Vertex FindRot(CKBone *dabone,int Frame);
	void RenderFrame(int Frame);
	void UpdateKeyFrame(int daKey,CKBone *daBone,Vertex ng);
	void SetSkelName(CString daSkelName);
	void SetName(CString daName);
	void DelKF(KF *daKF);
	void DelKFAtFrame(int daFrame);
	int FindKFBefore(int daFrame);
	int FindKFAfter(int daFrame);
	void RescaleAndSet(int daFrame);

	// datas
	int nbKF;
	CKSkeleton *daSkel;
	CString SkelName;
	CString Name;
	AnimatKF *Prev,*Next;
	KF *FirstKF,*NextKF;
	int nbFrames;
};

#endif