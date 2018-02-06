
//---------------------------------------------------------------------------
#ifndef EmitterH
#define EmitterH

#include "Kapsul3D.h"

typedef struct
{
	float r,g,b,a;
} tColor;

class __declspec( dllexport ) Particle
{
    public:

	Particle *prev,*next;				// LINK
	Vertex	pos;						// CURRENT POSITION
	Vertex	prevPos;					// PREVIOUS POSITION
	Vertex	dir;						// CURRENT DIRECTION WITH SPEED
	int		life;						// HOW LONG IT WILL LAST
	
	tColor	color;						// CURRENT COLOR OF PARTICLE
	tColor  deltaColor;

	float	Size;
	float  deltaSize;

	float Swirl;
	float deltaSwirl;
    
    inline Particle(void) {};
	inline ~Particle(void) {};

};

class __declspec( dllexport ) Emitter
{
    public:

	long		id;							// EMITTER ID
	CString Name;					// EMITTER NAME
	long		flags;						// EMITTER FLAGS
	// TRANSFORMATION INFO
	Vertex		pos;						// XYZ POSITION
	float		yaw, yawVar;				// YAW AND VARIATION
	float		pitch, pitchVar;			// PITCH AND VARIATION
	float		speed,speedVar;

	float		startSize,startSizeVar;
	float		endSize,endSizeVar;

	float		startSwirl,startSwirlVar;
	float		endSwirl,endSwirlVar;


	// Particle
	Particle	*particle;					// NULL TERMINATED LINKED LIST
	int			totalParticles;				// TOTAL EMITTED AT ANY TIME
	int			particleCount;				// TOTAL EMITTED RIGHT NOW
	int			emitsPerFrame, emitVar;		// EMITS PER FRAME AND VARIATION
	int			life, lifeVar;				// LIFE COUNT AND VARIATION
    
	tColor		startColor, startColorVar;	// CURRENT COLOR OF PARTICLE
	tColor		endColor, endColorVar;		// CURRENT COLOR OF PARTICLE
    
	// Physics
	Vertex		force;

    Particle *m_ParticlePool;		// POOL TO PULL PARTICLES FROM

    Emitter();
    ~Emitter();

    bool UpdateEmitter(void);
    bool addParticle(void);
    bool updateParticle(Particle *particle); //,Emitter *emitter)

    Emitter *Next,*Prev;

    bool Selected;
	void Draw(CKRenderer *pRender,int daState,int WichOne);
};

//---------------------------------------------------------------------------
#endif
