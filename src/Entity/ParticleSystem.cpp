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
// ParticleSystem.cpp: implementation of the CParticleSystem class.
//
//////////////////////////////////////////////////////////////////////

#include "HotSpot.h"
#include "ParticleSystem.h"
#include <math.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CParticleSystem::CParticleSystem()
{
	m_fEmissionResidue = 0.0f;
	m_bIsSuppressed = FALSE;
	fVarx = 0.8f;
}

CParticleSystem::~CParticleSystem()
{

}
//-----------------------------------------------------------------------------
//
//	CParticleSystem::IsColliding
//
//-----------------------------------------------------------------------------
bool CParticleSystem::IsColliding()
{
	return m_bIsColliding;
}



//////////////////////////////////////////////////
CParticleSystem::Update(float fTime)
{


	// fTime is absolute time.  So we need to calculate the relative time displacement or fTimeDelta that has elapesed
	float fTimeDelta = fTime - m_fTimeLastUpdate;

	m_fTimeLastUpdate = fTime;

	//TODO
	//set location of system here
	// sort of a hack (or nice screen saver effect) to test out a moving particle system
	if (m_bIsMoving)
	{
		static float fThetaHoriz = 0.0f;
		static float fThetaVert = 180.0f;

		fThetaHoriz += 25.0f * fTimeDelta;
		fThetaVert += 35.0f * fTimeDelta*fVarx;

		if ( fThetaHoriz > 359.0f ) 
		{
			fThetaHoriz = 0.0f;
		}
		if ( fThetaVert > 359.0f ) 
		{
			fVarx = RANDOM_NUM*1.0f+1.0f;
			fThetaVert = 0.0f;
		}

		m_vLocation.x = 20.0f * (float)cos( fThetaHoriz * 0.01745f );//*0.75f;
		m_vLocation.y =  7.0f * (float)sin( fThetaVert * 0.01745f );//*0.75f;
		m_vLocation.z = 20.0f * (float)sin( fThetaHoriz * 0.01745f )*(float)sin( fThetaVert * 0.01745f );//*0.75f;
		
	}
	else
	{
		// this will reset it every frame, but most importantly it will reset it to the origin if it isn't Moving
		m_vLocation.x = 0.0f;
		m_vLocation.y = 0.0f;
		m_vLocation.z = 0.0f;
		
	}

	// clear our counter variable before counting how many particles are alive
	m_uParticlesAlive = 0;

	// update all particles that we own
	for ( int i=0; i<MAX_PARTICLES; i++)
	{
		if (m_rParticles[i].m_fAge >= 0.0f )
			if ( m_rParticles[i].Update( fTimeDelta )) // update function returns FALSE if the m_rParticles died
				m_uParticlesAlive++;
	}

	// calculate how many particles we should create from ParticlesPerSec and time elapsed taking the 
	// previous frame's EmissionResidue into account.
	float fParticlesNeeded = m_uParticlesPerSec * fTimeDelta + m_fEmissionResidue;
	
	// cast the float fparticlesNeeded to a INT to see how many particles we really need to create.
	unsigned int uParticlesCreated = (unsigned int)fParticlesNeeded;

	if ( !m_bIsSuppressed )	
	{
		// remember the difference between what we wanted to create and how many we created.
		m_fEmissionResidue = fParticlesNeeded - uParticlesCreated;
	}	
	else	
	{		
		m_fEmissionResidue = 0.0f;		
		uParticlesCreated = 0;	
	}

	// see if actually have any to create
	if ( uParticlesCreated > 0 )
	{
		// loop through all the particles to see if any are available
		for ( i=0; i<MAX_PARTICLES; i++ )
		{
			// if created enough particles, this value will be 0 and so skip the rest
			if ( !uParticlesCreated )
				break;

			// if the age is -1.0f then this Particles is not in use
			if ( m_rParticles[i].m_fAge < 0.0f ) 
			{
				// New Particle so it's age is 0.0f 
				// Actually should be some randomization of fTimeDelta since in a perfect world
				// particles would have been created between our last update and now.
				m_rParticles[i].m_fAge = 0.0f;
				m_rParticles[i].m_fLifetime = m_fLifeTime+RANDOM_NUM * m_fLifeVar;
				Clamp( m_rParticles[i].m_fLifetime, MIN_LIFETIME, MAX_LIFETIME ); 

				// Calculate our Alpha from the system's AlphaStart and AlphaVar
				m_rParticles[i].m_fAlpha = m_fAlphaStart + RANDOM_NUM * m_fAlphaVar;
				// clamp any overflow
				Clamp( m_rParticles[i].m_fAlpha, MIN_ALPHA, MAX_ALPHA );
				// calculate a delta so that by the time the m_rParticles dies, it will have reached it's "AlphaEnd"
				m_rParticles[i].m_fAlphaDelta = (m_fAlphaEnd - m_rParticles[i].m_fAlpha) / m_rParticles[i].m_fLifetime;

				// our start color is going to be the System's StartColor + the System's color variation
				m_rParticles[i].m_vColor.r = m_vColorStart.r+ RANDOM_NUM * m_vColorVar.r;
				m_rParticles[i].m_vColor.g = m_vColorStart.g + RANDOM_NUM * m_vColorVar.g;
				m_rParticles[i].m_vColor.b = m_vColorStart.b + RANDOM_NUM * m_vColorVar.b;

				// clamp any overflow
				Clamp( m_rParticles[i].m_vColor.r, 0.0f, 1.0f );
				Clamp( m_rParticles[i].m_vColor.g, 0.0f, 1.0f );
				Clamp( m_rParticles[i].m_vColor.b, 0.0f, 1.0f );

				// calculate a delta so that by the time the m_rParticles dies, it will have reached it's "ColorEnd"
				m_rParticles[i].m_vColorDelta.r = ((m_vColorEnd.r+ RANDOM_NUM * m_vColorVar.r) - m_rParticles[i].m_vColor.r) / m_rParticles[i].m_fLifetime;
				m_rParticles[i].m_vColorDelta.g = ((m_vColorEnd.g+ RANDOM_NUM * m_vColorVar.g) - m_rParticles[i].m_vColor.g) / m_rParticles[i].m_fLifetime;
				m_rParticles[i].m_vColorDelta.b = ((m_vColorEnd.b+ RANDOM_NUM * m_vColorVar.b) - m_rParticles[i].m_vColor.b) / m_rParticles[i].m_fLifetime;
				
				//Start Size and End Size then delta and clamping
				m_rParticles[i].m_fSize = m_fSizeStart + RANDOM_NUM * m_fSizeVar;
				Clamp( m_rParticles[i].m_fSize, MIN_SIZE, MAX_SIZE );
				m_rParticles[i].m_fSizeDelta = (m_fSizeEnd - m_rParticles[i].m_fSize) / m_rParticles[i].m_fLifetime;
				
				//GRAVITY
				// It's a percentage of normal gravity.
					m_rParticles[i].m_vParticleGravity.x = 	m_vGravityStart.x * GRAVITY + RANDOM_NUM * m_fGravityVar*GRAVITY;
					Clamp( m_rParticles[i].m_vParticleGravity.x, MIN_GRAVITY*GRAVITY, MAX_GRAVITY*GRAVITY );

					m_rParticles[i].m_vGravityDelta.x = 
									( m_vGravityEnd.x*GRAVITY - m_rParticles[i].m_vParticleGravity.x ) / m_rParticles[i].m_fLifetime;

					m_rParticles[i].m_vParticleGravity.y = 	m_vGravityStart.y * GRAVITY + RANDOM_NUM * m_fGravityVar*GRAVITY;
					Clamp( m_rParticles[i].m_vParticleGravity.y, MIN_GRAVITY*GRAVITY, MAX_GRAVITY*GRAVITY );

					m_rParticles[i].m_vGravityDelta.y = 
									( m_vGravityEnd.y*GRAVITY - m_rParticles[i].m_vParticleGravity.y ) / m_rParticles[i].m_fLifetime;

					m_rParticles[i].m_vParticleGravity.z = 	m_vGravityStart.z * GRAVITY + RANDOM_NUM * m_fGravityVar*GRAVITY;
					Clamp( m_rParticles[i].m_vParticleGravity.z, MIN_GRAVITY*GRAVITY, MAX_GRAVITY*GRAVITY );

					m_rParticles[i].m_vGravityDelta.z = 
									( m_vGravityEnd.z*GRAVITY - m_rParticles[i].m_vParticleGravity.z ) / m_rParticles[i].m_fLifetime;

	/*				m_rParticles[i].m_fGravity = 	m_fGravityStart*GRAVITY;// + RANDOM_NUM * m_fGravityVar*GRAVITY;
					Clamp( m_rParticles[i].m_fGravity, MIN_GRAVITY*GRAVITY, MAX_GRAVITY*GRAVITY );

					m_rParticles[i].m_fGravityDelta = 
									( m_fGravityEnd*GRAVITY - m_rParticles[i].m_fGravity ) / m_rParticles[i].m_fLifetime;
*/
				// since Velocity is a change in position over time, 
				// calculate a Velocity the Particles would have to 
				// have travelled to move from PrevLocation to Location in fTimeDelta seconds.
				// Then calculate points in that linear path by passing in different Time deltas 
				m_vTempVelocity.x = (m_vLocation.x - m_vPrevLocation.x)/fTimeDelta;
				m_vTempVelocity.y = (m_vLocation.y - m_vPrevLocation.y)/fTimeDelta;
				m_vTempVelocity.z = (m_vLocation.z - m_vPrevLocation.z)/fTimeDelta;
				
				// Emit the particles from a location between the last known location and the current location
				m_rParticles[i].m_vLocation.x = m_vPrevLocation.x;// + m_vTempVelocity.x * RANDOM_NUM * fTimeDelta;
				m_rParticles[i].m_vLocation.y = m_vPrevLocation.y;// + m_vTempVelocity.y * RANDOM_NUM * fTimeDelta;
				m_rParticles[i].m_vLocation.z = m_vPrevLocation.z;// + m_vTempVelocity.z * RANDOM_NUM * fTimeDelta;

				// Update the previous location so the next update we can remember where we were
				m_rParticles[i].m_vPrevLocation.x = m_rParticles[i].m_vLocation.x;
				m_rParticles[i].m_vPrevLocation.y = m_rParticles[i].m_vLocation.y;
				m_rParticles[i].m_vPrevLocation.z = m_rParticles[i].m_vLocation.z;

				// The emitter has a Direction.  This code adds some randomness to that direction so
				// that we don't emit a Line of particles.  
				float RandomYaw = RANDOM_NUM * 3.14159f * 2.0f;
				float RandomPitch = RANDOM_NUM * m_fTheta * 3.14159f ;/// 180.0f ;

				//this uses spherical coordinates to randomize the velocity vector ( or the direction ) of the m_rParticles
				m_rParticles[i].m_vVelocity.y = static_cast<float>(cos( RandomPitch ));
				m_rParticles[i].m_vVelocity.x = static_cast<float>(sin(RandomPitch) * cos(RandomYaw));
				m_rParticles[i].m_vVelocity.z = static_cast<float>(sin(RandomPitch) * sin(RandomYaw));

				/*
				// Velocity at this point is just a direction (normalized vector ) and needs to be multiplied by 
				// the speed component to be a true velocity
				float fNewSpeed = m_fSpeed + RANDOM_NUM * m_fSpeedVar;
				Clamp( fNewSpeed, MIN_SPEED, MAX_SPEED );
				*/

				// Multiply Velocity by speed
				m_rParticles[i].m_vVelocity.x *= m_fSpeed ;
				m_rParticles[i].m_vVelocity.y *= m_fSpeed ;
				m_rParticles[i].m_vVelocity.z *= m_fSpeed ;


/*
				m_rParticles[i].m_vVelocity.y = (0.5f-RANDOM_NUM)* RANDOM_NUM;// * m_fSpeedVar;
				m_rParticles[i].m_vVelocity.x = (0.5f-RANDOM_NUM)* RANDOM_NUM;// * m_fSpeedVar;
				m_rParticles[i].m_vVelocity.z = (0.5f-RANDOM_NUM)* RANDOM_NUM;// * m_fSpeedVar;

				m_rParticles[i].m_vVelocity.x *= m_fSpeed ;
				m_rParticles[i].m_vVelocity.y *= m_fSpeed ;
				m_rParticles[i].m_vVelocity.z *= m_fSpeed ;

*/
				// let the m_rParticles know who it's Daddy is
				m_rParticles[i].SetParent(this);
				
				// decrement the number of needed particles
				uParticlesCreated--;
			}
		}
	}

	///set prevlocation to current location so next frame we know where we were
	m_vPrevLocation = m_vLocation;	

    //return TRUE;


}


CTexture *datex=NULL;

//this draws the particle system in the ogl window
CParticleSystem::Draw(float x_Rot,float y_Rot)
{
int loop;




	if (datex==NULL)
	{
		datex=new CTexture(NULL,NULL);
		strcpy(datex->FileName,"smoke.bmp");
		datex->Type=TEXTURE_FILE;
	}

	
	
    





	float modelview[16];
	int i,j;

	glEnable(GL_TEXTURE_2D);
	datex->Bind();
	// save the current modelview matrix
	glPushMatrix();

	// bill board for camera/perspective

	if (CurEntity->dk->ViewType[WichOne]!=0)
	{
		glGetFloatv(GL_MODELVIEW_MATRIX , modelview);
		for( i=0; i<3; i++ ) 
			for( j=0; j<3; j++ ) {
			if ( i==j )
				modelview[i*4+j] = 1.0;
			else
				modelview[i*4+j] = 0.0;
			}

		// set the modelview with no rotations
		glLoadMatrixf(modelview);
	}


	glDisable(GL_DEPTH_TEST);

	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	glEnable(GL_BLEND);
	
    glBegin(GL_QUADS);

	glColor4f(0.5,0.5,0.5,0.5);

	int bsize=10;
    if (particle != NULL)
    {
        tparticle = particle;
        // DON'T ANTIALIAS FIRST FRAME
        while (tparticle!=NULL && tparticle->life > 0)
        {
			  glTexCoord2f(0.0f, 0.0f); 
			  glVertex3f(tparticle->pos.vx,tparticle->pos.vz,tparticle->pos.vy);
				glTexCoord2f(0.0f, 1.0f); 
				glVertex3f(tparticle->pos.vx,tparticle->pos.vz+bsize,tparticle->pos.vy);
				glTexCoord2f(1.0f, 1.0f); 
				glVertex3f(tparticle->pos.vx+bsize,tparticle->pos.vz+bsize,tparticle->pos.vy);

				glTexCoord2f(1.0f, 0.0f); 
				glVertex3f(tparticle->pos.vx+bsize,tparticle->pos.vz,tparticle->pos.vy);
            
			
            tparticle = tparticle->next;
        }
    }

}

glBegin(GL_LINES);
    glVertex3f(pos.vx,pos.vy,pos.vz+speed*10);
    glVertex3f(pos.vx-speed*5,pos.vy-speed*5,pos.vz);

    glVertex3f(pos.vx,pos.vy,pos.vz+speed*10);
    glVertex3f(pos.vx+speed*5,pos.vy+speed*5,pos.vz);

    glVertex3f(pos.vx,pos.vy,pos.vz+speed*10);
    glVertex3f(pos.vx-speed*5,pos.vy+speed*5,pos.vz);

    glVertex3f(pos.vx,pos.vy,pos.vz+speed*10);
    glVertex3f(pos.vx+speed*5,pos.vy-speed*5,pos.vz);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(pos.vx,pos.vy,pos.vz-speed*10);
    glVertex3f(pos.vx-speed*5,pos.vy-speed*5,pos.vz);

    glVertex3f(pos.vx,pos.vy,pos.vz-speed*10);
    glVertex3f(pos.vx+speed*5,pos.vy+speed*5,pos.vz);

    glVertex3f(pos.vx,pos.vy,pos.vz-speed*10);
    glVertex3f(pos.vx-speed*5,pos.vy+speed*5,pos.vz);

    glVertex3f(pos.vx,pos.vy,pos.vz-speed*10);
    glVertex3f(pos.vx+speed*5,pos.vy-speed*5,pos.vz);
    glEnd();



    glBegin(GL_LINE_LOOP);
    glVertex3f(pos.vx-speed*5,pos.vy-speed*5,pos.vz);
    glVertex3f(pos.vx+speed*5,pos.vy-speed*5,pos.vz);
    glVertex3f(pos.vx+speed*5,pos.vy+speed*5,pos.vz);
    glVertex3f(pos.vx-speed*5,pos.vy+speed*5,pos.vz);
    glEnd();

// draw parts
	for (loop = 0; loop < MAX_PARTICLES; loop++)
	{
		//if the particle is still alive, draw it
		if (m_rParticles[loop].m_fAge >= 0.0f)
		{
			glColor4f(m_rParticles[loop].m_vColor.r,m_rParticles[loop].m_vColor.g,
								m_rParticles[loop].m_vColor.b,m_rParticles[loop].m_fAlpha);

			glPushMatrix();
			glTranslatef(m_rParticles[loop].m_vLocation.x,
										m_rParticles[loop].m_vLocation.y,
											m_rParticles[loop].m_vLocation.z);
			
			//bring the bitmap into view, pointing the cam
			glRotatef(y_Rot,0.0f,1.0f,0.0f);
			glRotatef(x_Rot,1.0f,0.0f,0.0f);

			// Build Quad From A Triangle Strip
			glBegin(GL_TRIANGLE_STRIP);						
			  glTexCoord2f(1.0f, 1.0f); glVertex3f( m_rParticles[loop].m_fSize, m_rParticles[loop].m_fSize, 0.0f); // Top Right
				glTexCoord2f(0.0f, 1.0f); glVertex3f(-m_rParticles[loop].m_fSize, m_rParticles[loop].m_fSize, 0.0f); // Top Left
				glTexCoord2f(1.0f, 0.0f); glVertex3f( m_rParticles[loop].m_fSize,-m_rParticles[loop].m_fSize, 0.0f); // Bottom Right
				glTexCoord2f(0.0f, 0.0f); glVertex3f(-m_rParticles[loop].m_fSize,-m_rParticles[loop].m_fSize, 0.0f);// Bottom Left
			glEnd();									
			
			glPopMatrix();
		}
	}

    glEnd();
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
    
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

/*
	//Draw the floor if its enabled
	if(	m_bIsColliding)
	{
		glPushAttrib(GL_TEXTURE_BIT);
		
		//disable the texture so a solid color can be drawn
		glDisable(GL_TEXTURE_2D);
		glLineWidth(1.0f);
		glColor4f(0.4f,0.6f,0.6f,0.9f);

		//this is the little stick which shows the particles emitted
		glBegin(GL_LINES);
				glVertex3f( m_vLocation.x,m_vLocation.y-m_fSizeStart*0.5f,m_vLocation.z);
				glVertex3f( m_vLocation.x,m_vLocation.y-m_fSizeStart*3.0f,m_vLocation.z);
		glEnd();

		//now draw the floor
		glTranslatef(0.0f,FLOOR,0.0f);
		glColor4f(0.0f,0.3f,0.3f,0.7f);
		glBegin(GL_LINE_STRIP);
				glVertex3f(-20.0f,-0.0f,-20.0f);
				glVertex3f(-20.0f,-0.0f, 20.0f);
				glVertex3f( 20.0f,-0.0f, 20.0f);
				glVertex3f( 20.0f,-0.0f,-20.0f);
				glVertex3f(-20.0f,-0.0f,-20.0f);
		glEnd();
		glBegin(GL_LINE_STRIP);
				glVertex3f(-10.0f,-0.0f,-10.0f);
				glVertex3f(-10.0f,-0.0f, 10.0f);
				glVertex3f( 10.0f,-0.0f, 10.0f);
				glVertex3f( 10.0f,-0.0f,-10.0f);
				glVertex3f(-10.0f,-0.0f,-10.0f);
		glEnd();
		
		glPopAttrib();
	}
	*/
}


//when the user move a bar on the pad the particle system params
//must be updated. Called from doparametercalcs
CParticleSystem::HotSpotParamsUpdate(int iTheSpot, POINT m_pspt)
{

			//Determined by HS.OnHotSpot, which spot was changed
			//the new mouse position sets how much to change the parameter
			//Max and Mins are set in the header ParticleSystem.h
			if (iTheSpot == HS_BOING)
			{
				if( IsColliding())
				{
					 m_fBoing = ((float)m_pspt.x - 45.0f)/100.0f;
					if( m_fBoing < 0.1f)  m_fBoing = 0.1f;
					if( m_fBoing > 1.0f)  m_fBoing = 1.0f;
				}
			}

			if (iTheSpot == HS_THETA)
			{
				m_fTheta = ((float)m_pspt.x - 45.0f)/100.0f;
				if(m_fTheta < 0.02f) m_fTheta = 0.02f;
				if(m_fTheta > 1.0f) m_fTheta = 1.0f;
			}
			
			//Gravity Start.x
			if (iTheSpot == HS_GRAV_START_X)
			{
				 m_vGravityStart.x = (((float)m_pspt.x - 95.0f)/50.0f)*MAX_GRAVITY;
				if (( m_vGravityStart.x > MAX_GRAVITY)||( m_vGravityStart.x < MIN_GRAVITY))
					 m_vGravityStart.x = 0.0f;
			}

			//Gravity End.x
			if (iTheSpot == HS_GRAV_END_X)
			{
				 m_vGravityEnd.x = (((float)m_pspt.x - 95.0f)/50.0f)*MAX_GRAVITY;
				if (( m_vGravityEnd.x  > MAX_GRAVITY)||( m_vGravityEnd.x  < MIN_GRAVITY))
					 m_vGravityEnd.x  = 0.0f;
			}
			
			//Gravity Start.y
			if (iTheSpot == HS_GRAV_START_Y)
			{
				 m_vGravityStart.y = (((float)m_pspt.x - 95.0f)/50.0f)*MAX_GRAVITY;
				if (( m_vGravityStart.y > MAX_GRAVITY)||( m_vGravityStart.y < MIN_GRAVITY))
					 m_vGravityStart.y = 0.0f;
			}

			//Gravity End.y
			if (iTheSpot == HS_GRAV_END_Y)
			{
				 m_vGravityEnd.y = (((float)m_pspt.x - 95.0f)/50.0f)*MAX_GRAVITY;
				if (( m_vGravityEnd.y  > MAX_GRAVITY)||( m_vGravityEnd.y  < MIN_GRAVITY))
					 m_vGravityEnd.y  = 0.0f;
			}
			
			//Gravity Start.z
			if (iTheSpot == HS_GRAV_START_Z)
			{
				 m_vGravityStart.z = (((float)m_pspt.x - 95.0f)/50.0f)*MAX_GRAVITY;
				if (( m_vGravityStart.z > MAX_GRAVITY)||( m_vGravityStart.z < MIN_GRAVITY))
					 m_vGravityStart.z = 0.0f;
			}

			//Gravity End.z
			if (iTheSpot == HS_GRAV_END_Z)
			{
				 m_vGravityEnd.z = (((float)m_pspt.x - 95.0f)/50.0f)*MAX_GRAVITY;
				if (( m_vGravityEnd.z  > MAX_GRAVITY)||( m_vGravityEnd.z  < MIN_GRAVITY))
					 m_vGravityEnd.z  = 0.0f;
			}
			
			//Alpha Start
			if (iTheSpot == HS_ALPHA_START)
			{
				 m_fAlphaStart = ((float)m_pspt.x - 45.0f)/100.0f;
				if( m_fAlphaStart  > 1.0f)  m_fAlphaStart =1.0f;
				if( m_fAlphaStart  < 0.02f)  m_fAlphaStart = 0.02f;
			}

			//Alpha End
			if (iTheSpot == HS_ALPHA_END)
			{
				 m_fAlphaEnd = ((float)m_pspt.x - 45.0f)/100.0f;
				if( m_fAlphaEnd  > 1.0f)  m_fAlphaEnd =1.0f;
				if( m_fAlphaEnd  < 0.02f)  m_fAlphaEnd = 0.02f;
			}

			//Red Start
			if (iTheSpot == HS_RED_START)
			{
				 m_vColorStart.r = ((float)m_pspt.x - 45.0f)/100.0f;
				if( m_vColorStart.r > 0.96f)  m_vColorStart.r = 0.96f;
				if( m_vColorStart.r < 0.04f)  m_vColorStart.r = 0.04f;
			}

			//Red End
			if (iTheSpot == HS_RED_END)
			{
				 m_vColorEnd.r = ((float)m_pspt.x - 45.0f)/100.0f;
				if( m_vColorEnd.r > 0.96f)  m_vColorEnd.r = 0.96f;
				if( m_vColorEnd.r < 0.04f)  m_vColorEnd.r = 0.04f;
			}

			//Grn Start
			if (iTheSpot == HS_GREEN_START)
			{
				 m_vColorStart.g = ((float)m_pspt.x - 45.0f)/100.0f;
				if( m_vColorStart.g > 0.96f)  m_vColorStart.g = 0.96f;
				if( m_vColorStart.g < 0.04f)  m_vColorStart.g = 0.04f;
			}

			//Grn End
			if (iTheSpot == HS_GREEN_END)
			{
				 m_vColorEnd.g = ((float)m_pspt.x - 45.0f)/100.0f;
				if( m_vColorEnd.g > 0.96f)  m_vColorEnd.g = 0.96f;
				if( m_vColorEnd.g < 0.04f)  m_vColorEnd.g = 0.04f;
			}

			//Blu Start
			if (iTheSpot == HS_BLUE_START)
			{
				 m_vColorStart.b = ((float)m_pspt.x - 45.0f)/100.0f;
				if( m_vColorStart.b > 0.96f)  m_vColorStart.b = 0.96f;
				if( m_vColorStart.b < 0.04f)  m_vColorStart.b = 0.04f;
			}

			//Blu End
			if (iTheSpot == HS_BLUE_END)
			{
				 m_vColorEnd.b = ((float)m_pspt.x - 45.0f)/100.0f;
				if( m_vColorEnd.b > 0.96f)  m_vColorEnd.b = 0.96f;
				if( m_vColorEnd.b < 0.04f)  m_vColorEnd.b = 0.04f;
			}
			
			//Size Start
			if (iTheSpot == HS_SIZE_START)
			{
				 m_fSizeStart = (((float)m_pspt.x - 45.0f)/100.0f)*MAX_SIZE;
				if( m_fSizeStart > MAX_SIZE)  m_fSizeStart = MAX_SIZE;
				if( m_fSizeStart < MIN_SIZE)  m_fSizeStart = MIN_SIZE;
			}

			//Size End
			if (iTheSpot == HS_SIZE_END)
			{
				 m_fSizeEnd = (((float)m_pspt.x - 45.0f)/100.0f)*MAX_SIZE;
				if( m_fSizeEnd > MAX_SIZE)  m_fSizeEnd = MAX_SIZE;
				if( m_fSizeEnd < MIN_SIZE)  m_fSizeEnd = MIN_SIZE;
			}

			//Particles Per Second
				//EMISSION
			if (iTheSpot == HS_EMMISION)
			{
				if ((float)m_pspt.x < 45.0f) m_pspt.x = 45L;
				 m_uParticlesPerSec = (unsigned int)((((float)m_pspt.x - 45.0f)/100.0f)*MAX_EMISSION);
				if( m_uParticlesPerSec  >= (unsigned int)MAX_EMISSION)  m_uParticlesPerSec = (unsigned int)MAX_EMISSION;
				if( m_uParticlesPerSec <= (unsigned int)MIN_EMISSION)  m_uParticlesPerSec = (unsigned int)MIN_EMISSION;
			}

			//Speed
			if (iTheSpot == HS_SPEED)
			{
				 m_fSpeed = (((float)m_pspt.x - 45.0f)/100.0f)*MAX_SPEED;
				if( m_fSpeed > MAX_SPEED)  m_fSpeed = MAX_SPEED;
				if( m_fSpeed < MIN_SPEED)  m_fSpeed = MIN_SPEED;
			}
			
			//LifeTime
			if (iTheSpot == HS_LIFE)
			{
				 m_fLifeTime = (((float)m_pspt.x - 45.0f)/100.0f)*MAX_LIFETIME;
				if( m_fLifeTime > MAX_LIFETIME)  m_fLifeTime = MAX_LIFETIME;
				if( m_fLifeTime < MIN_LIFETIME)  m_fLifeTime = MIN_LIFETIME;
			}

			//VAR Alpha
			if (iTheSpot == HS_VAR_ALPHA)
			{
				 m_fAlphaVar = ((float)m_pspt.x - 45.0f)/100.0f;
				if( m_fAlphaVar > 0.96f)  m_fAlphaVar = 0.96f;
				if( m_fAlphaVar < 0.01f)  m_fAlphaVar = 0.01f;
			}
			
			//VAR color
			if (iTheSpot == HS_VAR_COLOR)
			{
				 m_vColorVar.r = ((float)m_pspt.x - 45.0f)/100.0f;
				if( m_vColorVar.r > 0.96f)  m_vColorVar.r = 0.96f;
				if( m_vColorVar.r < 0.01f)  m_vColorVar.r = 0.01f;
				 m_vColorVar.g =  m_vColorVar.r;
				 m_vColorVar.b =  m_vColorVar.r;
			}

			//VAR Size
			if (iTheSpot == HS_VAR_SIZE)
			{
				 m_fSizeVar = ((float)m_pspt.x - 45.0f)/100.0f*MAX_SIZE;
				if( m_fSizeVar > MAX_SIZE)  m_fSizeVar = MAX_SIZE;
				if( m_fSizeVar < MIN_SIZE)  m_fSizeVar = MIN_SIZE;
			}
			
			//VAR Life
			if (iTheSpot == HS_VAR_LIFE)
			{
				 m_fLifeVar = ((float)m_pspt.x - 45.0f)/100.0f*MAX_LIFETIME;
				if( m_fLifeVar > MAX_LIFETIME)  m_fLifeVar = MAX_LIFETIME;
				if( m_fLifeVar < MIN_LIFETIME)  m_fLifeVar = MIN_LIFETIME;
			}
			
			//VAR Speed
			if (iTheSpot == HS_VAR_SPEED)
			{
				 m_fSpeedVar = ((float)m_pspt.x - 45.0f)/100.0f*MAX_SPEED;
				if( m_fSpeedVar > MAX_SPEED)  m_fSpeedVar = MAX_SPEED;
				if( m_fSpeedVar < MIN_SPEED)  m_fSpeedVar = MIN_SPEED;
			}			

				//If Floor is selected for toggle for collision on off
			if (iTheSpot == HS_FLOOR)
					if (IsColliding()) m_bIsColliding = FALSE;
						else m_bIsColliding = TRUE;
				
				
				//If Moving is selected for toggle on off
			if (iTheSpot == HS_MOVING)
					if (m_bIsMoving) m_bIsMoving = FALSE;
						else m_bIsMoving = TRUE;

}
