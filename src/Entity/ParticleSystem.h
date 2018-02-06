/*****************************************************************************
 *
 * 
 * Parts of routine, class concept and particle theory
 * originally written by Richard Benson

	** Go here for the BEST tutorial on particle physics
http://home.earthlink.net/~rbenson/ParticleHTML/Particles_files/frame.htm

	** Go here for Particle Chamber, a DX7 app where you also have real time particle 
changing abilities and full source code.
http://www.particlesystems.com/html/pchamber.html

 * Code written by Brian Tischler 07/2000
 * Author e-mail : briandeb@telusplanet.net
 *
 * The source can be modified, reused & redistributed for non-profitable 
 * uses. Use for commercial purposes without author's permission prohibited.
 *
 *****************************************************************************/
// ParticleSystem.h: interface for the CParticleSystem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARTICLESYSTEM_H__34526DC1_EECD_11D3_8633_A28C034A8AB4__INCLUDED_)
#define AFX_PARTICLESYSTEM_H__34526DC1_EECD_11D3_8633_A28C034A8AB4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include <gl\gl.h>		// Header File For The OpenGL32 Library
#include <gl\glu.h>		// Header File For The GLu32 Library

#include "ParticleElt.h"

//if your computer can only draw 1000 particles at 5 fps, lower this value
#define MAX_PARTICLES 5000

//A number between 0.0000 and 1.00000
#define RANDOM_NUM (static_cast<float>(rand())/static_cast<float>(RAND_MAX))

// some defines for our ParticleSystem.   This makes it easy to change settings
// by using defines and putting them all in one place
#define MIN_SPEED			0.0f	// in world units / sec
#define MIN_LIFETIME	0.1f	// in seconds
#define MIN_SPREAD		0.01f	// in degrees
#define MIN_EMISSION	1.0f	// in particles / sec
#define MIN_SIZE			0.1f	// in world units
#define MIN_GRAVITY		-0.5f	// as a multiple of normal gravity 
#define MIN_ALPHA			0.0f	// as a ratio 

#define MAX_SPEED			25.0f	// in world units / sec
#define MAX_LIFETIME	15.0f	// in seconds
#define MAX_SPREAD		180.0f	// in degrees
#define MAX_EMISSION  1000.0f	// in particles / sec
#define MAX_SIZE			4.0f	// in world units
#define MAX_GRAVITY		0.5f	// as a multiple of normal gravity 
#define MAX_ALPHA			1.0f	// as a ratio 
#define GRAVITY				9.8f //Just what gravity would be

// useful macro to guarantee that values are within a given range
#define Clamp(x, min, max)  x = (x<min  ? min : x<max ? x : max);

//inherited from CParticle class
class CParticleSystem : public CParticle 
{

public:

	//update the particle system parameters based on hotspot info
	HotSpotParamsUpdate(int iTheSpot, POINT m_pspt);
	
	//draw the particles based on the parameters set
	Draw(float,float);

	//change the parameters based on set criteria
	Update(float fTime);

	//constructor
	CParticleSystem();

	//destrcutor
	virtual ~CParticleSystem();

	//called by main to see if floor is on
	bool IsColliding();

	//member variables
	float m_fTimeLastUpdate;

	bool m_bIsColliding;
	bool m_bIsMoving;

	//initialized by application in initparticlesystem
	float m_fLifeTime;
	float m_fLifeVar;
	float m_fAlphaStart;
	float m_fAlphaEnd;
	float m_fAlphaVar;
	float m_fSizeStart;
	float m_fSizeEnd;
	float m_fSizeVar;
	float m_fSpeed;
	float m_fGravityVar;
	float m_fSpeedVar;
	float m_fTheta;
	float m_fBoing;

	bool m_bIsSuppressed;
	bool m_bIsFloor;


	Vertex m_vPrevLocation;
	Vertex m_vLocation;
	Vertex m_vGravityStart;
	Vertex m_vGravityEnd;

	COLORVECTOR m_vColorStart;
	COLORVECTOR m_vColorEnd;
	COLORVECTOR m_vColorVar;
	unsigned int m_uParticlesPerSec;
	unsigned int m_uParticlesAlive;

//protected:
	CParticle m_rParticles[MAX_PARTICLES];

private:
	float fColorArray[4];
	float m_fEmissionResidue;
	float fVarHoriz;
	float fVarz;
	float fVarx;
	POINTVECTOR m_vTempVelocity;
	
};

#endif // !defined(AFX_PARTICLESYSTEM_H__34526DC1_EECD_11D3_8633_A28C034A8AB4__INCLUDED_)
