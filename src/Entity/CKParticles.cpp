//---------------------------------------------------------------------------
#include "stdafx.h"

#include "emitter.h"

//extern CKEntity *CurEntity;

Emitter::Emitter()
{
	/*
    Prev=daPrev;
    Next=daNext;
*/
    int loop;
//    Maths=new(Math);
	id = 0;		// UNUSED
	
	//Name=TEXT("Emit01");
	flags = NULL;

	pos.x = 0.0f;					// XYZ POSITION
	pos.y = 0.0f;					// XYZ POSITION
	pos.z = 128.0f;					// XYZ POSITION
/* 
// jet d'eau
	yaw = PI/2;//DEGTORAD(0.0f);
	yawVar = (float)(PI/10); //DEGTORAD(360.0f);
	pitch = 0;//DEGTORAD(90.0f);
	pitchVar = (float)(PI/36);//DEGTORAD(40.0f);
	speed = 8;
	speedVar = 1;

	totalParticles	= 500;
	particleCount	= 0;
	emitsPerFrame	= 20;
	emitVar	= 2;
	life = 25;
	lifeVar = 5;
    Selected=false;
    
	startColor.r = 0.1f;
	startColor.g = 0.1f;
	startColor.b = 0.9f;
	startColor.a = 0.6f;
	startColorVar.r = 0.0f;
	startColorVar.g = 0.0f;
	startColorVar.b = 0.0f;
	startColorVar.a = 0.2f;
	endColor.r = 0.6f;
	endColor.g = 0.7f;
	endColor.b = 0.9f;
	endColor.a = 0.0f;
	endColorVar.r = 0.0f;
	endColorVar.g = 0.0f;
	endColorVar.b = 0.0f;
	endColorVar.a = 0.0f;
    
	startSize = 7;
	startSizeVar = 3;
	endSize = 30;
	endSizeVar = 2;

	startSwirl=0;
	startSwirlVar=0;
	endSwirl=0;
	endSwirlVar=0;

	force.x = 0.000f;
	force.y = -0.0f;
	force.z = -0.38f;
*/
/*
	yaw = 0;//DEGTORAD(0.0f);
	yawVar = (float)(PI*2);//DEGTORAD(360.0f);
	pitch = 0;//DEGTORAD(90.0f);
	pitchVar = (float)(PI*2);//DEGTORAD(40.0f);
	speed = 8;
	speedVar = 1;

	totalParticles	= 20;
	particleCount	= 0;
	emitsPerFrame	= 10;
	emitVar	= 0;
	life = 30;
	lifeVar = 0;
    Selected=false;
    
	startColor.r = 0.9f;
	startColor.g = 0.6f;
	startColor.b = 0.6f;
	startColor.a = 0.9f;
	startColorVar.r = 0.0f;
	startColorVar.g = 0.0f;
	startColorVar.b = 0.0f;
	startColorVar.a = 0.0f;
	endColor.r = 0.6f;
	endColor.g = 0.1f;
	endColor.b = 0.1f;
	endColor.a = 0.0f;
	endColorVar.r = 0.0f;
	endColorVar.g = 0.0f;
	endColorVar.b = 0.0f;
	endColorVar.a = 0.0f;
    
	startSize = 12;
	startSizeVar = 1;
	endSize = 4;
	endSizeVar = 2;

	startSwirl=0;
	startSwirlVar=0;
	endSwirl=0;
	endSwirlVar=0;

	force.x = 0.000f;
	force.y = -0.0f;
	force.z = -0.38f;
	*/

	yaw = 0;//DEGTORAD(0.0f);
	yawVar = (float)(PI*2);//DEGTORAD(360.0f);
	pitch = 0;//DEGTORAD(90.0f);
	pitchVar = (float)(PI*2);//DEGTORAD(40.0f);
	speed = 5;
	speedVar = 1;

	totalParticles	= 200;
	particleCount	= 0;
	emitsPerFrame	= 200;
	emitVar	= 0;
	life = 60;
	lifeVar = 0;
    Selected=false;
    
	startColor.r = 0.5f;
	startColor.g = 0.0f;
	startColor.b = 0.5f;
	startColor.a = 0.9f;
	startColorVar.r = 0.5f;
	startColorVar.g = 0.0f;
	startColorVar.b = 0.5f;
	startColorVar.a = 0.0f;
	endColor.r = 0.2f;
	endColor.g = 0.1f;
	endColor.b = 0.2f;
	endColor.a = 0.0f;
	endColorVar.r = 0.2f;
	endColorVar.g = 0.0f;
	endColorVar.b = 0.2f;
	endColorVar.a = 0.0f;
    
	startSize = 10;
	startSizeVar = 0;
	endSize = 0;
	endSizeVar = 0;

	startSwirl=0;
	startSwirlVar=0;
	endSwirl=0;
	endSwirlVar=0;

	force.x = 0.000f;
	force.y = -0.0f;
	force.z = -0.38f;
    particle	= NULL;

    m_ParticlePool = (Particle *)malloc(4000 * sizeof(Particle));
	// THIS IS A LINKED LIST OF PARTICLES, SO I NEED TO ESTABLISH LINKS
	for (loop = 0; loop < 3999; loop++)
	{
		m_ParticlePool[loop].next = &m_ParticlePool[loop + 1];
	}
	// SET THE LAST PARTICLE TO POINT TO NULL
	m_ParticlePool[3999].next = NULL;
                   /*
    for (loop = 0; loop < 2000; loop++)
        addParticle();
                     */
    //particle=new (Particle);

}

Emitter::~Emitter()
{
}

bool Emitter::updateParticle(Particle *mparticle) //,Emitter *emitter)
{
	// IF THIS IS AN VALID PARTICLE
	if (mparticle != NULL)
	{
		if ( mparticle->life > 0)
		{
			// SAVE ITS OLD POS FOR ANTI ALIASING
			mparticle->prevPos.x = mparticle->pos.x;
			mparticle->prevPos.y = mparticle->pos.y;
			mparticle->prevPos.z = mparticle->pos.z;

			// CALCULATE THE NEW
			mparticle->pos.x += mparticle->dir.x;
			mparticle->pos.y += mparticle->dir.y;
			mparticle->pos.z += mparticle->dir.z;

			// APPLY GLOBAL FORCE TO DIRECTION
			mparticle->dir.x += force.x;
			mparticle->dir.y += force.y;
			mparticle->dir.z += force.z;
	/*
			// SAVE THE OLD COLOR
			particle->prevColor.r = particle->color.r;
			particle->prevColor.g = particle->color.g;
			particle->prevColor.b = particle->color.b;
	*/
			// GET THE NEW COLOR
			mparticle->color.r += mparticle->deltaColor.r;
			mparticle->color.g += mparticle->deltaColor.g;
			mparticle->color.b += mparticle->deltaColor.b;
			mparticle->color.a += mparticle->deltaColor.a;

			mparticle->Size += mparticle->deltaSize;

			mparticle->Swirl += mparticle->deltaSwirl;

			mparticle->life--;	// IT IS A CYCLE OLDER
			return TRUE;
		}
		else 
		{
			// FREE THIS SUCKER UP BACK TO THE MAIN POOL
			if (mparticle->prev != NULL)
				mparticle->prev->next = mparticle->next;
			else
				particle = mparticle->next;
			// FIX UP THE NEXT'S PREV POINTER IF THERE IS A NEXT
			if (mparticle->next != NULL)
				mparticle->next->prev = mparticle->prev;

			mparticle->next = m_ParticlePool;
			m_ParticlePool = mparticle;	// NEW POOL POINTER
			particleCount--;	// ADD ONE TO POOL
			OutputDebugString("DEL\n");
		}
	}
	return FALSE;
}

bool Emitter::addParticle(void)
{
/// Local Variables ///////////////////////////////////////////////////////////
	Particle *mparticle;
	tColor	start,end;
	float mstartSize,mendSize;
	float mstartSwirl,mendSwirl;
	float myaw,mpitch,mspeed;
///////////////////////////////////////////////////////////////////////////////
	// IF THERE IS AN EMITTER AND A PARTICLE IN THE POOL
	// AND I HAVEN'T EMITTED MY MAX
	if (m_ParticlePool != NULL &&
		particleCount < totalParticles)
	{
		OutputDebugString("Add\n");
		mparticle = m_ParticlePool;		// THE CURRENT PARTICLE
		m_ParticlePool = m_ParticlePool->next;	// FIX THE POOL POINTERS

		if (particle != NULL)
			particle->prev = mparticle; // SET BACK LINK
		mparticle->next = particle;	// SET ITS NEXT POINTER
		mparticle->prev = NULL;				// IT HAS NO BACK POINTER
		particle = mparticle;		// SET IT IN THE EMITTER

		mparticle->pos.x = pos.x;	// RELATIVE TO EMITTER BASE
		mparticle->pos.y = pos.y;
		mparticle->pos.z = pos.z;

		mparticle->prevPos.x = pos.x;	// USED FOR ANTI ALIAS
		mparticle->prevPos.y = pos.y;
		mparticle->prevPos.z = pos.z;

		// CALCULATE THE STARTING DIRECTION VECTOR
		myaw = yaw + (yawVar * RandomNum());
		mpitch = pitch + (pitchVar * RandomNum());

		// CONVERT THE ROTATIONS TO A VECTOR
		RotationToDirection(mpitch,myaw,&mparticle->dir);

		// MULTIPLY IN THE SPEED FACTOR
		mspeed = speed + (speedVar * RandomNum());
		mparticle->dir.x *= mspeed;
		mparticle->dir.y *= mspeed;
		mparticle->dir.z *= mspeed;
        
		// CALCULATE THE COLORS
		start.r = startColor.r + (startColorVar.r * RandomNum());
		start.g = startColor.g + (startColorVar.g * RandomNum());
		start.b = startColor.b + (startColorVar.b * RandomNum());
		start.a = startColor.a + (startColorVar.a * RandomNum());

		end.r = endColor.r + (endColorVar.r * RandomNum());
		end.g = endColor.g + (endColorVar.g * RandomNum());
		end.b = endColor.b + (endColorVar.b * RandomNum());
		end.a = endColor.a + (endColorVar.a * RandomNum());
        
        mstartSize=startSize+(startSizeVar * RandomNum());
		mendSize=endSize+(endSizeVar * RandomNum());

        mstartSwirl=startSwirl+(startSwirlVar * RandomNum());
		mendSwirl=endSwirl+(endSwirlVar * RandomNum());

		mparticle->color.r = start.r;
		mparticle->color.g = start.g;
		mparticle->color.b = start.b;
		mparticle->color.a = start.a;
        
		// CALCULATE THE LIFE SPAN
		mparticle->life = life + (int)((float)lifeVar * RandomNum());
        
		// CREATE THE COLOR DELTA
		mparticle->deltaColor.r = (end.r - start.r) / mparticle->life;
		mparticle->deltaColor.g = (end.g - start.g) / mparticle->life;
		mparticle->deltaColor.b = (end.b - start.b) / mparticle->life;
		mparticle->deltaColor.a = (end.a - start.a) / mparticle->life;

		mparticle->Size=mstartSize;
		mparticle->deltaSize = (mendSize - mstartSize) / mparticle->life;

		mparticle->Swirl=mstartSwirl;
		mparticle->deltaSwirl = (mendSwirl - mstartSwirl) / mparticle->life;
        
		particleCount++;	// A NEW PARTICLE IS BORN
		return TRUE;
	}

	return FALSE;
}
bool Emitter::UpdateEmitter(void)
{
/// Local Variables ///////////////////////////////////////////////////////////
	int loop,emits;
	Particle *mparticle, *next;
///////////////////////////////////////////////////////////////////////////////
	// IF THERE IS AN EMITTER
    if (particle != NULL)
    {
        // GO THROUGH THE PARTICLES AND UPDATE THEM
        mparticle = particle;
        while (mparticle)
        {
            next = mparticle->next;	// SAVE THIS BECAUSE IT MAY CHANGE UNDER ME
            updateParticle(mparticle);
            mparticle = next;
        }
    }

    // EMIT PARTICLES FOR THIS FRAME
    emits = emitsPerFrame + (int)((float)emitVar * RandomNum());
//    for (loop = 0; loop < emits; loop++)

    for (loop = 0; loop < emits; loop++)
        addParticle();

    return TRUE;
}

CKTexture *datex=NULL;

void Emitter::Draw(CKRenderer *pRender,int daState,int WichOne)
{
	/* Ho
	if (datex==NULL)
	{
		datex=new CKTexture(NULL,NULL);
		datex->FileName=GetFullPath("particle2.bmp");
		datex->Type=TEXTURE_FILE;
		datex->Load();
	}

	
*/	
    Particle *tparticle;

	Vertex pt[6];

	pt[0]=Vertex(pos.x,pos.y,pos.z+speed*10);

	pt[1]=Vertex(pos.x+speed*5,pos.y+speed*5,pos.z);
	pt[2]=Vertex(pos.x-speed*5,pos.y+speed*5,pos.z);
	pt[3]=Vertex(pos.x-speed*5,pos.y-speed*5,pos.z);
	pt[4]=Vertex(pos.x+speed*5,pos.y-speed*5,pos.z);

	pt[5]=Vertex(pos.x,pos.y,pos.z-speed*10);

	static int Inds[16]={0,1,0,2,0,3,0,4,5,1,5,2,5,3,5,4};
	static int Inds2[16]={1,2,3,4};

    if (Selected)
	{
        pRender->DirectRender(pt,NULL,Inds,KLINES,16,1,0,0,1);
		pRender->DirectRender(pt,NULL,Inds2,KLINE_LOOP,4,1,0,0,1);
	}
    else
	{
		pRender->DirectRender(pt,NULL,Inds,KLINES,16,1,1,1,1);
		pRender->DirectRender(pt,NULL,Inds2,KLINE_LOOP,4,1,1,1,1);
	}


	float modelview[16];
	int i,j;
/*
	glEnable(GL_TEXTURE_2D);
	datex->Bind();
	// save the current modelview matrix
	glPushMatrix();

	// bill board for camera/perspective




	glDisable(GL_DEPTH_TEST);

	glBlendFunc(GL_SRC_ALPHA,GL_ONE);		
	glEnable(GL_BLEND);
	
    

	


    if (particle != NULL)
    {
        tparticle = particle;
        // DON'T ANTIALIAS FIRST FRAME
        while (tparticle!=NULL && tparticle->life > 0)
        {
			//glColor3fv((const float*)&tparticle->color);
			glColor4f(tparticle->color.r,tparticle->color.g,tparticle->color.b,tparticle->color.a);


			//glRotatef(tparticle->Swirl,0,0,1);

			glPushMatrix();
			glTranslatef(tparticle->pos.x,tparticle->pos.y,tparticle->pos.z);
			//glRotatef(tparticle->Swirl,0,1,0);
			
			 Ho2
	if (CurEntity->m_Scene->ViewType[WichOne]!=0)
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

			glRotatef(tparticle->Swirl,0,0,1);
			glTranslatef(-tparticle->Size/2,-tparticle->Size/2,0);

			glBegin(GL_QUADS);
			  glTexCoord2f(0.0f, 0.0f); 
			  glVertex3f(0,0,0);
				glTexCoord2f(0.0f, 1.0f); 
				glVertex3f(0,tparticle->Size,0);
				glTexCoord2f(1.0f, 1.0f); 
				glVertex3f(tparticle->Size,tparticle->Size,0);

				glTexCoord2f(1.0f, 0.0f); 
				glVertex3f(tparticle->Size,0,0);
				glEnd();
				
			glPopMatrix();
            
			
            tparticle = tparticle->next;
        }
    }
    
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
    
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	*/
}