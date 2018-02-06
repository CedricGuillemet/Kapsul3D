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

 *
 * Code written by Brian Tischler 07/2000
 * Author e-mail : briandeb@telusplanet.net
 *
 * The source can be modified, reused & redistributed for non-profitable 
 * uses. Use for commercial purposes without author's permission prohibited.
 *
 *****************************************************************************/

// Particle.h: interface for the CParticle class.
//
//////////////////////////////////////////////////////////////////////
#include <windows.h>	// Header File For Windows

#if !defined(AFX_PARSYS_H__95B7E04A_E85B_11D3_8633_C60AC87D3859__INCLUDED_)
#define AFX_PARSYS_H__95B7E04A_E85B_11D3_8633_C60AC87D3859__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//where to draw the floor level
#define FLOOR -7.0f

//red green blue float vector for color
struct COLORVECTOR{
	float r,g,b;
};


//friend class CParticleSystem;

class CParticle 
{
public:

friend class CParticleSystem;

	//Called by the Particle System
	bool Update( float fTimeDelta );
	
	//CONSTRUCTOR
	CParticle();

	//DESTRUCTOR
	~CParticle();

	// Set ParticleSystem as parent of particle
	void		SetParent(CParticleSystem* Parent){ m_pParent = Parent;}

//MEMBER VARIABLES
//protected:

	float m_fAlpha;
	float m_fAge;
	float m_fLifetime;
	float m_fAlphaDelta;
	float m_fSizeDelta;
	float m_fSize;
	
	COLORVECTOR m_vColor;
	COLORVECTOR m_vColorDelta;

	POINTVECTOR m_vLocation;
	POINTVECTOR m_vPrevLocation;
	POINTVECTOR m_vVelocity;
	POINTVECTOR m_vParticleGravity;
	POINTVECTOR m_vGravityDelta;

private:
	// our parent
	CParticleSystem* m_pParent;

};

#endif // !defined(AFX_PARSYS_H__95B7E04A_E85B_11D3_8633_C60AC87D3859__INCLUDED_)

