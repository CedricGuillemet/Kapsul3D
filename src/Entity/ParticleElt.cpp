/*****************************************************************************
 *
 * 
 * Parts of routine, class concept and particle theory
 * originally written by Richard Benson
 *
 * Code written by Brian Tischler 07/2000
 * Author e-mail : briandeb@telusplanet.net
 *
 * The source can be modified, reused & redistributed for non-profitable 
 * uses. Use for commercial purposes without author's permission prohibited.
 *
 *****************************************************************************/
// ParSys.cpp: implementation of the CParSys class.
//
//////////////////////////////////////////////////////////////////////

#include "Particle.h"
#include "ParticleSystem.h"


//////////////////////////////////////////////////////////////////////
// Construction
//////////////////////////////////////////////////////////////////////
CParticle::CParticle()
{
		m_vLocation.x = 0.0f;
		m_vLocation.y = 0.0f;
		m_vLocation.z = 0.0f;

		m_vPrevLocation.x = 0.0f;
		m_vPrevLocation.y = 0.0f;
		m_vPrevLocation.z = 0.0f;

		m_vParticleGravity.x      = 1.0f;
		m_vGravityDelta.x = 1.0f;
		m_vParticleGravity.y      = 1.0f;
		m_vGravityDelta.y = 1.0f;
		m_vParticleGravity.z      = 1.0f;
		m_vGravityDelta.z = 1.0f;

		m_vVelocity.x = 0.0f;
		m_vVelocity.y = 0.0f;
		m_vVelocity.z = 0.0f;

		m_vColor.r = 0.3f;
		m_vColor.g = 0.3f;
		m_vColor.b = 0.3f;

		m_vColorDelta.r = 0.0f;
		m_vColorDelta.g = 0.0f;
		m_vColorDelta.b = 0.0f;

		m_fAge      = -1.0f;
		m_fLifetime = -1.0f;

		m_fAlpha      = 0.0f;
		m_fAlphaDelta = 0.0f;

		m_fSizeDelta  = 1.0f;
		m_fSize			  = 1.0f;
}

//////////////////////////////////////////////////////////////////////
// Destruction
//////////////////////////////////////////////////////////////////////
CParticle::~CParticle()
{
}

bool CParticle::Update( float fTimeDelta )
{

	// Some systems may have particles with no Lifetime
	// i.e. they could have to collide with terrain 
	// or they could just always be alive if the system
	// had a fixed # of particles alive
	if ( m_fAge + fTimeDelta >= m_fLifetime ) 
	{
		m_fAge = -1.0f;
		return FALSE;
	}
	else
	{

		// everything ages so add the time elapsed
		m_fAge += fTimeDelta;

		// Our current location will be our previous location next frame
		m_vPrevLocation.x = m_vLocation.x;
		m_vPrevLocation.y = m_vLocation.y;
		m_vPrevLocation.z = m_vLocation.z;

		// this moves the particle using the last known velocity and the time that has passed
		m_vLocation.x += m_vVelocity.x * fTimeDelta;
		m_vLocation.y += m_vVelocity.y * fTimeDelta;
		m_vLocation.z += m_vVelocity.z * fTimeDelta;


		// whether or not our parent system allows ground plane collision.
		// this really should be a per particle setting, not an attribute of the parent system
		// This isn't how you would normally do collision.  This snaps any particle below the 
		// ground plane up to ground level.  Ground collision is just to show what a fountain
		// or other effects might look like 
		if ( m_pParent->IsColliding() )
		{
			if ( m_vLocation.y < FLOOR ) 
			{
				// if they are moving at a decent rate vertically reflect them
				if ( m_vVelocity.y > -5.0f )  // -5.0f <= velocity.y <= 0.0f
				{
					m_vLocation.y = FLOOR;
					m_vVelocity.y = 0.0f;
				}
				// otherwise, let them rest on the ground plane
				else
				{
					m_vLocation.y = m_vPrevLocation.y; 
					m_vVelocity.y = -m_vVelocity.y*m_pParent->m_fBoing;
				}
			}
			/*
			//Roof
			if ( m_vLocation.y > -(FLOOR) ) 
			{
					m_vLocation.y = m_vPrevLocation.y; 
					m_vVelocity.y = -m_vVelocity.y*m_pParent->m_fBoing;
			}
				
			//negative x Wall*3.0f
			if ( m_vLocation.x < FLOOR*3.0f ) 
			{
					m_vLocation.x = m_vPrevLocation.x; 
					m_vVelocity.x = -m_vVelocity.x*m_pParent->m_fBoing;
			}

			//positive x FLOOR*3.0f
			if ( m_vLocation.x > -(FLOOR*3.0f) ) 
			{
					m_vLocation.x = m_vPrevLocation.x; 
					m_vVelocity.x = -m_vVelocity.x*m_pParent->m_fBoing;
			}
	
			//negative z FLOOR*3.0f
			if ( m_vLocation.z < FLOOR*3.0f ) 
			{
					m_vLocation.z = m_vPrevLocation.z; 
					m_vVelocity.z = -m_vVelocity.z*m_pParent->m_fBoing;
			}

			//positive z FLOOR*3.0f
			if ( m_vLocation.z > -(FLOOR*3.0f) ) 
			{
					m_vLocation.z = m_vPrevLocation.z; 
					m_vVelocity.z = -m_vVelocity.z*m_pParent->m_fBoing;
			}
			*/
		}//end if colliding

		// Gravity is vector per particle system
		// to simulate a crosswinds etc.
		m_vVelocity.x += (9.8f * m_vParticleGravity.x * fTimeDelta );
		m_vVelocity.y += (9.8f *  m_vParticleGravity.y * fTimeDelta );
		m_vVelocity.z += (9.8f *  m_vParticleGravity.z * fTimeDelta );

		//Attraction

		// adjust current Alpha
		m_fAlpha += m_fAlphaDelta * fTimeDelta;

		// adjust current Color from calculated Deltas and time elapsed.
		m_vColor.r += m_vColorDelta.r * fTimeDelta;
		m_vColor.g += m_vColorDelta.g * fTimeDelta;
		m_vColor.b += m_vColorDelta.b * fTimeDelta;

		// adjust current Size
		m_fSize += m_fSizeDelta * fTimeDelta;

		// adjust current Gravity 
		m_vParticleGravity.x += m_vGravityDelta.x * fTimeDelta;
		m_vParticleGravity.y += m_vGravityDelta.y * fTimeDelta;
		m_vParticleGravity.z += m_vGravityDelta.z * fTimeDelta;
	}

	// if we got this far, everything is probably cool
	return TRUE;
}

/*
				// if this particle's parent system supports Attraction
		if (1)//( m_pParent->IsAttractive() )
		{

			POINTVECTOR AttractLocation;
			
			// Find out where our Parent is located so we can track it
			//m_pParent->GetLocation(AttractLocation);

			// The attractors could be points in space to create some cool effects.
			AttractLocation.x = 0.0f;
			AttractLocation.y = 0.0f;
			AttractLocation.z = 0.0f;

			// calculate the vector between the particle and the attractor
			POINTVECTOR AttractDir; 
			AttractDir.x = AttractLocation.x - m_vLocation.x; 
			AttractDir.y = AttractLocation.y - m_vLocation.y; 
			AttractDir.z = AttractLocation.z - m_vLocation.z; 
			// We can turn off attraction for certain axes 
			// AttractDir.y = 0; // this would simulate a cyclone type effect
			
			// note that this is NOT accurate gravitation.   We don't even look at the distance
			// between the 2 locations !!!    But what can I say, it looks good. You can find the 
			// formula for Gravitation in any good physics book.  It uses the masses of the 2 objects
			// the distance between them and the Gravitational constant

			// if you decide to use this simple method you really should use a variable multiplier
			// instead of a hardcoded value like 25.0f
			m_vVelocity.x += AttractDir.x *10.0f *fTimeDelta;
			m_vVelocity.y += AttractDir.y *10.0f* fTimeDelta;
			m_vVelocity.z += AttractDir.z *10.0f* fTimeDelta;
		
		}


		// if this particle's parent system supports Attraction
		if ( m_pParent->IsAttractive() )
		{

			D3DVECTOR AttractLocation;
			
			// Find out where our Parent is located so we can track it
			m_pParent->GetLocation(AttractLocation);

			// The attractors could be points in space to create some cool effects.
			//AttractLocation = D3DVECTOR(50,50,50);

			// calculate the vector between the particle and the attractor
			D3DVECTOR AttractDir = AttractLocation - m_d3dvLocation; 
			
			// We can turn off attraction for certain axes 
			// AttractDir.y = 0; // this would simulate a cyclone type effect
			
			// note that this is NOT accurate gravitation.   We don't even look at the distance
			// between the 2 locations !!!    But what can I say, it looks good. You can find the 
			// formula for Gravitation in any good physics book.  It uses the masses of the 2 objects
			// the distance between them and the Gravitational constant

			// if you decide to use this simple method you really should use a variable multiplier
			// instead of a hardcoded value like 25.0f
			m_d3dvVelocity += Normalize(AttractDir) * 25.0f * fTimeDelta;
		
		}

*/