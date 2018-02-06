//*****************************************
//@NOME FILE: fmath.h
//@DESCRIZIONE: Classi matematiche
//@AUTORE: Alvio Costantini
//@APPUNTI: v.1
//******************************************

#ifndef FMATH_H
#define FMATH_H

#include <math.h>
//#include <../src/glog/glog.h>

#define PIGRECO  3.14159265358f
#define HPIGRECO 1.57079632679f
#define DEGTORAD(A)	(((A) * PIGRECO) / 180.0f)
#define RADTODEG(A)	(((A) * 180.0f) / PIGRECO)
#define RADIANTS 57.29577951f
#define MAX(a,b) (((a) > (b)) ? (a) : (b))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))

class CV3;

class CMATRIX{
	
public:
	float mat[4][4];

public:

	CMATRIX();											

	void ZeroMatrix(void);											//Metodo che azzera la matrice
	void IdentityMatrix(void);									//Metodo che inizializza la matrice identità
	
	float FindDet2x2(float a1, float a2, float b1, float b2);
	float FindDet3x3(float a1, float a2, float a3, float b1, float b2, float b3, float c1, float c2, float c3);
	CMATRIX InverseMatrix(void);
	void BuildFromEuler(CV3 &vectAngles);
	int ConvertToEuler(CV3 &vectAngles);
	void Transpose(void);
	

	CMATRIX& operator=(CMATRIX &v);							
	CMATRIX& operator+=(CMATRIX &v);						
	CMATRIX& operator*=(CMATRIX &v);						
	friend CMATRIX operator*(CMATRIX &m1,CMATRIX &m2);	
	friend CV3 operator*(CV3 &v,CMATRIX &m);

	void SetPosition(float xr, float yr, float zr);
	void SetRotation(float xr, float yr, float zr);				//Setta la matrice in modo che si ruoti di xr, yr, zr gradi
	void SetScale(float scaleX, float scaleY, float scaleZ);
};

class CV3
{
public:
	float x,y,z;

public:
	//Costruttori
	CV3 (void) {x=y=z=0;}
	CV3 (float pfx,float pfy,float pfz) { x = pfx; y = pfy; z = pfz; }
	
	//Metodi
	void Reset(void) {x=y=z=0.f;}
	float VectorLength(const CV3 &pv);
	void VectorCopy(CV3 &pv1,CV3 &pv2);
	float VectorDot(const CV3 &pv1,const CV3 &pv2);
	CV3 VectorNormalize(const CV3 &pv, CV3 &ris);
	void VectorNegate(const CV3 &pv1,const CV3 &ris);
	void VectorSet(CV3 &pv1, CV3 &pv2, CV3 &ris);
	void VectorAdd(const CV3 &pv1,const CV3 &pv2, CV3 &ris);
	void VectorSub(const CV3 &pv1,const CV3 &pv2, CV3 &ris);
	void VectorScale(const CV3 &pv1,const float scale, CV3 &ris);
	void Set(float pfx,float pfy,float pfz) { x = pfx; y = pfy; z = pfz; }
	static void VectorDivide(const CV3 &pv, float pfs, CV3 &ris);
	static void VectorMultiply(const CV3 &pv, float pfs, CV3 &ris);
	void VectorCross(const CV3 &pv1,const CV3 &pv2,CV3 &pNormale);
	
	//Overloading
	inline CV3 operator=(CV3 pft)				 {x=pft.x; y=pft.y; z=pft.z; return *this; }
	inline bool operator==(const CV3& ptemp) {return (x == ptemp.x && y == ptemp.y && z == ptemp.z); }
	inline bool operator!=(const CV3& ptemp) {return !(*this == ptemp); }
	
	inline CV3& operator*=(float pfScalar)			  {VectorMultiply(*this,pfScalar,*this); return *this; }
	inline CV3& operator/=(float pfScalar)				{VectorDivide(*this,pfScalar,*this); return *this; }
	inline CV3& operator+=(const CV3& ptemp)	{VectorAdd(*this,ptemp,*this); return *this; }
	inline CV3& operator-=(const CV3& ptemp)	{VectorSub(*this,ptemp,*this); return *this; }
	inline CV3& operator^=(const CV3& ptemp)	{VectorCross(*this,ptemp,*this); return *this; }

	

	inline CV3 operator-()																							 {CV3 ris; VectorNegate(*this,ris); return ris;}
	inline CV3 operator+(const CV3& ptemp)												 {CV3 ris; VectorAdd(*this,ptemp,ris); return ris;}
	inline CV3 operator-(const CV3& ptemp)												 {CV3 ris; VectorSub(*this,ptemp,ris); return ris;}
	inline CV3 operator^(const CV3& ptemp)												 {CV3 ris; VectorCross(*this,ptemp,ris); return ris;}
	inline friend CV3 operator*(const CV3& ptemp, float pfScalar) {CV3 ris; VectorMultiply(ptemp,pfScalar,ris); return ris;}
	inline friend CV3 operator*(float pfScalar, const CV3& ptemp) {CV3 ris; VectorMultiply(ptemp,pfScalar,ris); return ris;}
	inline friend CV3 operator/(const CV3& ptemp, float pfScalar) {CV3 ris; VectorDivide(ptemp,pfScalar,ris); return ris;}

	
	inline float Length(void)															{return VectorLength(*this); }
	inline CV3 Normalize(void)													{return VectorNormalize(*this,*this); } 
	inline CV3 GetNormalized(void)									    {CV3 ris; VectorNormalize(*this,ris); return ris; }; 
	inline float Dot( const CV3& ptemp)								{return VectorDot(*this,ptemp); }
	inline CV3 Cross(const CV3& ptemp)					  {CV3 ris; VectorCross(*this,ptemp,ris); return ris; }
	inline float Distance(const CV3 &ptemp)					  {return (*this-ptemp).Length();}
	inline CV3 CrossNormalized(const CV3& ptemp)	{CV3 ris; VectorCross(*this,ptemp,ris); VectorNormalize(ris,ris); return ris; }
	inline void Scale(const CV3 &tmp, const float scale) { VectorScale(tmp,scale,*this); }
};


class CV2
{
float x,y,z;

public:
	//Costruttori
	CV2 (void) {x=y=z=0;};
	CV2 (float pfx,float pfy,float pfz) { x = pfx; y = pfy; z = pfz; }
	
	//Metodi
	void Reset(void) {x=y=z=0.f;}
	float VectorLength(const CV2 &pv);
	void VectorCopy(CV2 &pv1,CV2 &pv2);
	float VectorDot(const CV2 &pv1,const CV2 &pv2);
	void VectorNegate(const CV2 &pv1,const CV2 &ris);
	CV2 VectorNormalize(const CV2 &pv, CV2 &ris);
	void VectorSet(CV2 &pv1, CV2 &pv2, CV2 &ris);
	void Set(float pfx,float pfy,float pfz) {x = pfx; y = pfy; z = pfz;}
	void VectorAdd(const CV2 &pv1,const CV2 &pv2, CV2 &ris);
	void VectorSub(const CV2 &pv1,const CV2 &pv2, CV2 &ris);
	static void VectorDivide(const CV2 &pv, float pfs, CV2 &ris);
	static void VectorMultiply(const CV2 &pv, float pfs, CV2 &ris);

	//Overloading
	inline CV2 operator=(CV2 pft)	  		{x=pft.x; y=pft.y; z=pft.z; return *this; }
	inline bool operator==(const CV2& ptemp)	{return (x == ptemp.x && y == ptemp.y && z == ptemp.z); }
	inline bool operator!=(const CV2& ptemp)  {return !(*this == ptemp); }
	
	inline CV2& operator*=(float pfScalar)					{VectorMultiply(*this,pfScalar,*this); return *this; }
	inline CV2& operator/=(float pfScalar)					{VectorDivide(*this,pfScalar,*this); return *this; }
	inline CV2& operator+=(const CV2& ptemp)	{VectorAdd(*this,ptemp,*this); return *this; }
	inline CV2& operator-=(const CV2& ptemp)	{VectorSub(*this,ptemp,*this); return *this; }
		
	inline CV2 operator-()																								 {CV2 ris; VectorNegate(*this,ris); return ris;}
	inline CV2 operator+(const CV2& ptemp)												 {CV2 ris; VectorAdd(*this,ptemp,ris); return ris;}
	inline CV2 operator-(const CV2& ptemp)												 {CV2 ris; VectorSub(*this,ptemp,ris); return ris;}
	inline friend CV2 operator*(const CV2& ptemp, float pfScalar) {CV2 ris; VectorMultiply(ptemp,pfScalar,ris); return ris;}
	inline friend CV2 operator*(float pfScalar, const CV2& ptemp) {CV2 ris; VectorMultiply(ptemp,pfScalar,ris); return ris;}
	inline friend CV2 operator/(const CV2& ptemp, float pfScalar) {CV2 ris; VectorDivide(ptemp,pfScalar,ris); return ris;}

	inline float Length(void)																	{return VectorLength(*this); }
	inline CV2 Normalize(void)														{return VectorNormalize(*this,*this); } 
	inline CV2 GetNormalized(void)										    {CV2 ris; VectorNormalize(*this,ris); return ris; }; 
	inline float Dot( const CV2& ptemp)									{return VectorDot(*this,ptemp); }
	inline float Distance(const CV2 &ptemp)						  {return (*this-ptemp).Length();}
	
};

class CQUATERNION  
{
public:
	CQUATERNION(){};
	~CQUATERNION(){};

	// Setup funcs
	void Set(float w,float x,float y,float z);						//Set up quaternion from given values
	void Set(const float x,const float y,const float z);	//Set up quaternion from given euler angles

	// Identity Quaternions (Sum defines an identity quaternion to be used to sum, mult to multiplicate)
	void SetSumIdentity();		
	void SetMulIdentity();

	// Normalize
	void Normalize();

	// GetDirection\GetInverse(Conjugate)
	CV3 GetDirection();
	CQUATERNION GetInverse();

	//Conversions
	void SetEulerAngles(const float x,const float y,const float z);
	void GetAxisAngle(float &angle,CV3 &vAxis);

	//Operators overloading
	CQUATERNION& operator =		(const CQUATERNION &q);
	CQUATERNION	 operator *		(const CQUATERNION &q);
	CQUATERNION& operator *=	(const CQUATERNION &q);

private:
	float m_W;
	float m_X,m_Y,m_Z;
};

inline CV3 MultMatrix(CV3 &v,CMATRIX &m)
{
	register CV3 temp;
	//Procedo per colonne
	temp.x=v.x*m.mat[0][0]+v.y*m.mat[1][0]+v.z*m.mat[2][0];
	temp.y=v.x*m.mat[0][1]+v.y*m.mat[1][1]+v.z*m.mat[2][1];
	temp.z=v.x*m.mat[0][2]+v.y*m.mat[1][2]+v.z*m.mat[2][2];
	return temp;
}	


static void RotateVector(CV3 &vect,float angolo,bool ruotaX,bool ruotaY,bool ruotaZ)
{
	angolo=(angolo * 3.1415f) / 180.0f;
	if (ruotaX)
	{
	float y,z;
	for (int i=0;i<3;i++)
		{
		y=vect.y;
		z=vect.z;
		vect.y= y	* (cosf(angolo)) +	z * (sinf(angolo));
		vect.z= y * (-sinf(angolo))+ z * cosf(angolo);
		}
	}
	if (ruotaY)
	{
	float x,z;
	for (int i=0;i<3;i++)
		{
		x=vect.x;
		z=vect.z;
		vect.x=x*cosf(angolo)+z*(-sinf(angolo));
		vect.z=x*sinf(angolo)+z*cosf(angolo);
		}
	}
	if (ruotaZ)
	{
	float x,y;
	for (int i=0;i<3;i++)
		{
		x=vect.x;
		y=vect.y;
		vect.x=x*cosf(angolo)+y*sinf(angolo);
		vect.y=x*(-sinf(angolo))+y*cosf(angolo);
		}
	}
}

inline void TranslateVector(CV3 &vect,float x,float y,float z)
{
	vect.x+=x;
	vect.y+=y;
	vect.z+=z;
}
inline float ClampValue(float value, float min, float max)
{
  if(value>max) value-=(max-min);
  if(value<min)	value+=(max-min);
  if((value>max) || (value<min)) value=ClampValue(value,min,max);

  return value;
}

inline void SwapValue(float &a, float &b)
{
	float t;
	t = a;
	a = b;
	b = t;
}


#endif