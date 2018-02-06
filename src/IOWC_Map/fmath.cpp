//*****************************************
//@NOME FILE: FMath.cpp
//@DESCRIZIONE: Funzioni delle classi matematiche
//@PROGRAMMATO DA: Alvio Costantini
//@APPUNTI: v.1
//******************************************

#include "fmath.h"

//Funsioni per le matrici

//class CMATRIX

CMATRIX::CMATRIX()
{

	ZeroMatrix();
}

/******************************/
/*Metodo che azzera la matrice*/
/******************************/

void CMATRIX::ZeroMatrix(void)
{
	//Azzero la matrice
	mat[0][0]=mat[0][1]=mat[0][2]=mat[0][3]=0;
	mat[1][0]=mat[1][1]=mat[1][2]=mat[1][3]=0;
	mat[2][0]=mat[2][1]=mat[2][2]=mat[2][3]=0;
	mat[3][0]=mat[3][1]=mat[3][2]=mat[3][3]=0;
}

/**************************************/
/*Metodo che crea una matrice identità*/
/**************************************/

void CMATRIX::IdentityMatrix(void)
{
	//Azzero la matrice
	mat[0][1]=mat[0][2]=mat[0][3]=0;
	mat[1][0]=mat[1][2]=mat[1][3]=0;
	mat[2][0]=mat[2][1]=mat[2][3]=0;
	mat[3][0]=mat[3][1]=mat[3][2]=0;

	//Creo la matrice identità
	mat[0][0]=mat[1][1]=mat[2][2]=mat[3][3]=1;
}

/****************************************/
/*Definizione del metodo di assegnamento*/
/****************************************/

CMATRIX& CMATRIX::operator =(CMATRIX &m)
{
	//Copio la matrice destinazione nella matrice di questa classe
	mat[0][0]=m.mat[0][0];
	mat[0][1]=m.mat[0][1];
	mat[0][2]=m.mat[0][2];
	mat[0][3]=m.mat[0][3];
	mat[1][0]=m.mat[1][0];
	mat[1][1]=m.mat[1][1];
	mat[1][2]=m.mat[1][2];
	mat[1][3]=m.mat[1][3];
	mat[2][0]=m.mat[2][0];
	mat[2][1]=m.mat[2][1];
	mat[2][2]=m.mat[2][2];
	mat[2][3]=m.mat[2][3];
	mat[3][0]=m.mat[3][0];
	mat[3][1]=m.mat[3][1];
	mat[3][2]=m.mat[3][2];
	mat[3][3]=m.mat[3][3];

	return *this;
}


/************************************************/
/*Definizione del metodo di assegnamento e somma*/
/************************************************/

CMATRIX& CMATRIX::operator +=(CMATRIX &m)
{
	//Sommo la matrice sorgente alla matrice di questa classe
	mat[0][0]+=m.mat[0][0];
	mat[0][1]+=m.mat[0][1];
	mat[0][2]+=m.mat[0][2];
	mat[0][3]+=m.mat[0][3];
	mat[1][0]+=m.mat[1][0];
	mat[1][1]+=m.mat[1][1];
	mat[1][2]+=m.mat[1][2];
	mat[1][3]+=m.mat[1][3];
	mat[2][0]+=m.mat[2][0];
	mat[2][1]+=m.mat[2][1];
	mat[2][2]+=m.mat[2][2];
	mat[2][3]+=m.mat[2][3];
	mat[3][0]+=m.mat[3][0];
	mat[3][1]+=m.mat[3][1];
	mat[3][2]+=m.mat[3][2];
	mat[3][3]+=m.mat[3][3];

	return *this;
}


/*******************************************************/
/*Definizione del metodo di assegnamento e prodotto    */
/*NOTA:																							   */
/*Il prodotto si fa moltiplicando una riga della prima */ 
/*matrice con tutta la rispettiva colonna della seconda*/
/*******************************************************/

CMATRIX& CMATRIX::operator *=(CMATRIX &m)
{
	register int i,j;
	register float temp[4][4];

	//Faccio il prodotto tra le due matrici
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			temp[i][j]=mat[i][0]*m.mat[0][j]+mat[i][1]*m.mat[1][j]+
							mat[i][2]*m.mat[2][j]+mat[i][3]*m.mat[3][j];

	//Assegno la mtrice creata alla matrice membro della classe
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			mat[i][j]=temp[i][j];

	return *this;
}


/*******************************************************/
/*Definizione del metodo di prodotto                   */
/*NOTA:																							   */
/*Il prodotto si fa moltiplicando una riga della prima */ 
/*matrice con tutta la rispettiva colonna della seconda*/
/*******************************************************/

CMATRIX operator *(CMATRIX &m1, CMATRIX &m2){

	register int i,j;
	register CMATRIX temp;

	//Faccio il prodotto tra le due matrici
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			temp.mat[i][j]=m1.mat[i][0]*m2.mat[0][j]+m1.mat[i][1]*m2.mat[1][j]+
							m1.mat[i][2]*m2.mat[2][j]+m1.mat[i][3]*m2.mat[3][j];

	return temp;
}

//*************************
float CMATRIX::FindDet2x2(float a1, float a2, float b1, float b2)
{	
	return a1*b2 - b1*a2;
}

float CMATRIX::FindDet3x3(float a1, float a2, float a3, float b1, float b2, float b3, float c1, float c2, float c3)
{
	return a1*FindDet2x2(b2, b3, c2, c3) - b1*FindDet2x2(a2, a3, c2, c3) + c1*FindDet2x2(a2, a3, b2, b3);
}

CMATRIX CMATRIX::InverseMatrix(void)
{
	float det,detInv;

  CMATRIX m;

  m.mat[0][0]=FindDet3x3(mat[1][1], mat[2][1], mat[3][1], mat[1][2], mat[2][2], mat[3][2], mat[1][3], mat[2][3], mat[3][3]);
	m.mat[0][1]=-FindDet3x3(mat[0][1], mat[2][1], mat[3][1], mat[0][2], mat[2][2], mat[3][2], mat[0][3], mat[2][3], mat[3][3]);
	m.mat[0][2]=FindDet3x3(mat[0][1], mat[1][1], mat[3][1], mat[0][2], mat[1][2], mat[3][2], mat[0][3], mat[1][3], mat[3][3]);
	m.mat[0][3]=-FindDet3x3(mat[0][1], mat[1][1], mat[2][1], mat[0][2], mat[1][2], mat[2][2], mat[0][3], mat[1][3], mat[2][3]);

	m.mat[1][0]=-FindDet3x3(mat[1][0], mat[2][0], mat[3][0], mat[1][2], mat[2][2], mat[3][2], mat[1][3], mat[2][3], mat[3][3]);
  m.mat[1][1]=FindDet3x3(mat[0][0], mat[2][0], mat[3][0], mat[0][2], mat[2][2], mat[3][2], mat[0][3], mat[2][3], mat[3][3]);
	m.mat[1][2]=-FindDet3x3(mat[0][0], mat[1][0], mat[3][0], mat[0][2], mat[1][2], mat[3][2], mat[0][3], mat[1][3], mat[3][3]);
	m.mat[1][3]=FindDet3x3(mat[0][0], mat[1][0], mat[2][0], mat[0][2], mat[1][2], mat[2][2], mat[0][3], mat[1][3], mat[2][3]);
 
	m.mat[2][0]=FindDet3x3(mat[1][0], mat[2][0], mat[3][0], mat[1][1], mat[2][1], mat[3][1], mat[1][3], mat[2][3], mat[3][3]);
  m.mat[2][1]=-FindDet3x3(mat[0][0], mat[2][0], mat[3][0], mat[0][1], mat[2][1], mat[3][1], mat[0][3], mat[2][3], mat[3][3]);
	m.mat[2][2]=FindDet3x3(mat[0][0], mat[1][0], mat[3][0], mat[0][1], mat[1][1], mat[3][1], mat[0][3], mat[1][3], mat[3][3]);
	m.mat[2][3]=-FindDet3x3(mat[0][0], mat[1][0], mat[2][0], mat[0][1], mat[1][1], mat[2][1], mat[0][3], mat[1][3], mat[2][3]);

	m.mat[3][0]=-FindDet3x3(mat[1][0], mat[2][0], mat[3][0], mat[1][1], mat[2][1], mat[3][1], mat[1][2], mat[2][2], mat[3][2]);
  m.mat[3][1]=FindDet3x3(mat[0][0], mat[2][0], mat[3][0], mat[0][1], mat[2][1], mat[3][1], mat[0][2], mat[2][2], mat[3][2]);
  m.mat[3][2]=-FindDet3x3(mat[0][0], mat[1][0], mat[3][0], mat[0][1], mat[1][1], mat[3][1], mat[0][2], mat[1][2], mat[3][2]);
  m.mat[3][3]=FindDet3x3(mat[0][0], mat[1][0], mat[2][0], mat[0][1], mat[1][1], mat[2][1], mat[0][2], mat[1][2], mat[2][2]);

  det=(mat[0][0] * m.mat[0][0]) + (mat[0][1] * m.mat[1][0]) + (mat[0][2] * m.mat[2][0]) + (mat[0][3] * m.mat[3][0]);

  detInv=1.0f/det;

	for(int row=0;row<4;row++)
		for(int col=0;col<4;col++)
			m.mat[row][col]*=detInv;

  return m;
}

void CMATRIX::BuildFromEuler(CV3 &vectAngles)
{
  float a=cosf(vectAngles.x/RADIANTS);
  float b=sinf(vectAngles.x/RADIANTS);
  float c=cosf(vectAngles.y/RADIANTS);
  float d=sinf(vectAngles.y/RADIANTS);
  float e=cosf(vectAngles.z/RADIANTS);
  float f=sinf(vectAngles.z/RADIANTS);

  float ad=a*d;
  float bd=b*d;

  mat[0][0]=c*e;
  mat[0][1]=-c*f;
	mat[0][2]=d;
  
	mat[1][0]=bd*e + a*f;
  mat[1][1]=-bd*f + a*e;
	mat[1][2]=-b*c;
  
  mat[2][0]=-ad*e + b*f;
	mat[2][1]=ad*f + b*e;
  mat[2][2]=a*c;

  mat[3][0]=mat[3][1]=mat[3][2]=mat[0][3]=mat[1][3]=mat[2][3]=0;
  mat[3][3]=1;
}

int CMATRIX::ConvertToEuler(CV3 &vectAngles)
{
    float c;
    int retValue=0;
    vectAngles.x=(float)(asin(mat[0][2]));
    c=cosf(vectAngles.x);
    vectAngles.x*=RADIANTS;

    if(fabsf(c)>0.005f)
    {
			vectAngles.x = atan2f(-mat[1][2],mat[2][2])*RADIANTS;
			vectAngles.z = atan2f(-mat[0][1],mat[0][0])*RADIANTS;
    }
    else
    {
			retValue=-1;
	    vectAngles.x=0.f;
	    vectAngles.z=atan2f(mat[1][0],mat[1][1])*RADIANTS;
    }
  
    vectAngles.x=ClampValue(vectAngles.x,0,360);
    vectAngles.y=ClampValue(vectAngles.y,0,360);
    vectAngles.z=ClampValue(vectAngles.z,0,360);

    return retValue;
}

void CMATRIX::Transpose(void)
{
	SwapValue(mat[0][1],mat[1][0]);
  SwapValue(mat[0][2],mat[2][0]);
  SwapValue(mat[0][3],mat[3][0]);
  SwapValue(mat[1][2],mat[2][1]);
  SwapValue(mat[1][3],mat[3][1]);
  SwapValue(mat[2][3],mat[3][2]);
}

/*************************************************************/
/* Setta la matrice in modo che si ruoti di xr, yr, zr gradi */
/*************************************************************/

void CMATRIX::SetRotation(float xr, float yr, float zr){

	float sinTemp,cosTemp;
	CMATRIX m1,m2,m3;

	m1.IdentityMatrix();
	m2.IdentityMatrix();
	m3.IdentityMatrix();

	if(xr)
	{
		//Calcolo il seno e il coseno dell'angolo xr
		sinTemp=sinf(xr);
		cosTemp=cosf(xr);

		m1.mat[1][1]=cosTemp;
		m1.mat[1][2]=sinTemp;

		m1.mat[2][1]=-sinTemp;
		m1.mat[2][2]=cosTemp;
	}

	if(yr)
	{
		//Calcolo il seno e il coseno dell'angolo yr
		sinTemp=sinf(yr);
		cosTemp=cosf(yr);

		m2.mat[0][0]=cosTemp;
		m2.mat[0][2]=-sinTemp;

		m2.mat[2][0]=sinTemp;
		m2.mat[2][2]=cosTemp;
	}

	if(zr)
	{
		//Calcolo il seno e il coseno dell'angolo zr
		sinTemp=sinf(zr);
		cosTemp=cosf(zr);

		m3.mat[0][0]=cosTemp;
		m3.mat[0][1]=sinTemp;

		m3.mat[1][0]=-sinTemp;
		m3.mat[1][1]=cosTemp;

	}
	*this=*this*m1*m2*m3;
}

void CMATRIX::SetPosition(float xr, float yr, float zr)
{
	this->mat[3][0]=xr;
	this->mat[3][1]=yr;
	this->mat[3][2]=zr;
}

void CMATRIX::SetScale(float scaleX, float scaleY, float scaleZ)
{
	this->mat[0][0]*=scaleX;
	this->mat[1][1]*=scaleY;
	this->mat[2][2]*=scaleZ;
}

//Funsioni per i vettori

//class CV3
void CV3::VectorSet(CV3 &pv1, CV3 &pv2, CV3 &ris)
{
	ris.x = pv1.x - pv2.x;
	ris.y = pv1.y - pv2.y;
	ris.z = pv1.z - pv2.z;
}

void CV3::VectorAdd(const CV3 &pv1,const CV3 &pv2,CV3 &ris)
{
	ris.x = pv1.x + pv2.x;
	ris.y = pv1.y + pv2.y;
	ris.z = pv1.z + pv2.z;
}

void CV3::VectorDivide(const CV3 &pv, float pfs, CV3 &ris)
{
	ris.x = pv.x / pfs;
	ris.y = pv.y / pfs;
	ris.z = pv.z / pfs;
}

void CV3::VectorSub(const CV3 &pv1,const CV3 &pv2, CV3 &ris)
{
	ris.x = pv1.x - pv2.x;
	ris.y = pv1.y - pv2.y;
	ris.z = pv1.z - pv2.z;
}

void CV3::VectorScale(const CV3 &pv1,const float scale, CV3 &ris)
{
 ris.x = pv1.x * scale;
 ris.y = pv1.y * scale;
 ris.z = pv1.z * scale;
}

void CV3::VectorMultiply(const CV3 &pv, float pfs, CV3 &ris)
{
	ris.x = pv.x * pfs;
	ris.y = pv.y * pfs;
	ris.z = pv.z * pfs;
}


CV3 CV3::VectorNormalize(const CV3 &pv,CV3 &ris)
{
  float l;
  
  l=sqrtf((pv.x * pv.x) + (pv.y * pv.y) + (pv.z * pv.z));
  if (l!=0)
	{
    ris.x = pv.x / l;
    ris.y = pv.y / l;
    ris.z = pv.z / l;
  }else 
	{
    ris.x = 1;
    ris.y = 1;
    ris.z = 1;
  }
	return ris;
}


void CV3::VectorCross(const CV3 &pv1,const CV3 &pv2,CV3 &pNormale)
{
	pNormale.x = (pv1.y * pv2.z) - (pv1.z * pv2.y);
	pNormale.y = (pv1.z * pv2.x) - (pv1.x * pv2.z);
	pNormale.z = (pv1.x * pv2.y) - (pv1.y * pv2.x);

//	glog->Printf("VC():(%f %f %f)x(%f %f %f)=(%f %f %f)\n", pv1.x,pv1.y,pv1.z, pv2.x,pv2.y,pv2.z,pNormale.x,pNormale.y,pNormale.z);
}



float CV3::VectorDot(const CV3 &pv1,const CV3 &pv2)
{
	return (pv1.x * pv2.x + pv1.y * pv2.y + pv1.z * pv2.z);
}


float CV3::VectorLength(const CV3 &pv)
{
	return sqrtf((pv.x * pv.x) + (pv.y * pv.y) + (pv.z * pv.z));
}

void CV3::VectorCopy(CV3 &pV1,CV3 &pV2)
{
	pV2.x=pV1.x;
	pV2.y=pV1.y;
	pV2.z=pV1.z;
}



//class CV2

void CV2::VectorSet(CV2 &pv1, CV2 &pv2, CV2 &ris)
{
	ris.x = pv1.x - pv2.x;
	ris.z = pv1.z - pv2.z;
}

void CV2::VectorAdd(const CV2 &pv1,const CV2 &pv2,CV2 &ris)
{
	ris.x = pv1.x + pv2.x;
	ris.z = pv1.z + pv2.z;
}

void CV2::VectorDivide(const CV2 &pv, float pfs, CV2 &ris)
{
	ris.x = pv.x / pfs;
	ris.z = pv.z / pfs;
}

void CV2::VectorSub(const CV2 &pv1,const CV2 &pv2, CV2 &ris)
{
	ris.x = pv1.x - pv2.x;
	ris.z = pv1.z - pv2.z;
}


void CV2::VectorMultiply(const CV2 &pv, float pfs, CV2 &ris)
{
	ris.x = pv.x * pfs;
	ris.z = pv.z * pfs;
}


CV2 CV2::VectorNormalize(const CV2 &pv,CV2 &ris)
{
  float l;
  
  l=sqrtf((pv.x * pv.x) + (pv.z * pv.z));
  if (l!=0)
	{
		ris.x = pv.x / l;
    ris.z = pv.z / l;
  }else 
	{
    ris.x = 1;
    ris.z = 1;
  }
	return ris;
}


float CV2::VectorDot(const CV2 &pv1,const CV2 &pv2)
{
	return (pv1.x * pv2.x + pv1.z * pv2.z);
}


float CV2::VectorLength(const CV2 &pv)
{
	return sqrtf((pv.x * pv.x) + (pv.z * pv.z));
}

void CV2::VectorCopy(CV2 &pV1,CV2 &pV2)
{
	pV2.x=pV1.x;
	pV2.z=pV1.z;
}

void CQUATERNION::Set(float w,float x,float y,float z)
{
 m_W = w;
 m_X = x;
 m_Y = y;
 m_Z = z;

 Normalize();
}

void CQUATERNION::Set(const float x,const float y,const float z)
{
	SetEulerAngles(x,y,z);
}

void CQUATERNION::SetSumIdentity()
{
 m_W = m_X = m_Y = m_Z = 0.0f;
}

void CQUATERNION::SetMulIdentity()
{
 m_W = 1;
 m_X = m_Y = m_Z = 0.0f;
}

void CQUATERNION::Normalize()
{
 //TODO: Add error check
 double dNorm = sqrt((m_W * m_W) + (m_X * m_X) + (m_Y * m_Y) + (m_Z * m_Z));

 m_W /= (float)dNorm;
 m_X /= (float)dNorm;
 m_Y /= (float)dNorm;
 m_Z /= (float)dNorm;
}

CV3 CQUATERNION::GetDirection()
{
 CV3 vDir;
 vDir.Set((float)(2.0 * (m_X * m_Z - m_W * m_Y)),
				  (float)(2.0 * (m_Y * m_Z + m_W * m_X)),
					(float)(1.0 - 2.0 * (m_X * m_X + m_Y * m_Y)));

 return vDir;
}

CQUATERNION CQUATERNION::GetInverse()
{
 CQUATERNION q;
 q.Set(m_W,-m_X,-m_Y,-m_Z);
 return q;
}

void CQUATERNION::SetEulerAngles(const float x,const float y,const float z)
{
 //TODO: Optimize
 CQUATERNION qX,qY,qZ;

 qX.Set((float)cos(x/2),(float)sin(x/2),0,0);
 qY.Set((float)cos(y/2),0,(float)sin(y/2),0);
 qZ.Set((float)cos(z/2),0,0,(float)sin(z/2));

 *this = qX * qY * qZ;
}

void CQUATERNION::GetAxisAngle(float &angle,CV3 &vAxis)
{
 //TODO : add error check
 float dScale = (float)sqrt((m_X * m_X) + (m_Y * m_Y) + (m_Z * m_Z));

 if(dScale == 0.0f)
 {
  angle = 0.0f;
	vAxis.Set(0.0f,0.0f,1.0f);
	return;
 }

 vAxis.Set((m_X / dScale),(m_Y / dScale),(m_Z / dScale));
 vAxis.Normalize();

 angle = 2 * (float)acos(m_W);
}

CQUATERNION& CQUATERNION::operator = (const CQUATERNION &q)
{
 m_W = q.m_W;
 m_X = q.m_X;
 m_Y = q.m_Y;
 m_Z = q.m_Z;

 return (*this);
}

CQUATERNION	 CQUATERNION::operator * (const CQUATERNION &q)
{
 register CQUATERNION temp;

 double w = q.m_W*m_W - q.m_X*m_X - q.m_Y*m_Y - q.m_Z*m_Z;
 double x = q.m_W*m_X + q.m_X*m_W + q.m_Y*m_Z - q.m_Z*m_Y;
 double y = q.m_W*m_Y + q.m_Y*m_W + q.m_Z*m_X - q.m_X*m_Z;
 double z = q.m_W*m_Z + q.m_Z*m_W + q.m_X*m_Y - q.m_Y*m_X;

 temp.Set((float)w,(float)x,(float)y,(float)z);

 return temp;
}

CQUATERNION& CQUATERNION::operator *= (const CQUATERNION &q)
{
 *this = *this * q;

 return (*this);
}
