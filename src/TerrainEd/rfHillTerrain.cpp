//
//
//	HillTerrain.cpp
//
//
//	a class for a heightmap-based terrain generated using the hill algorithm.
//
//	change log:
//	--------
//	10/10/01	bob	first completion
//
//	----------------------------------------------------------------------------
//	copyright (c) 2001 bob nystrom                  [see license at end of file]

#include "stdafx.h"
#include "rfHillTerrain.h"

#include <math.h>
#include <assert.h>
#include <new.h>


//	HillTerrain
//	----------------------------------------------------------------------------
HillTerrain::HillTerrain(	unsigned short	uSize,
							float			fHillMin,
							float			fHillMax,
							unsigned short	uNumHills,
							unsigned short	uFlattening,
							bool			bIsland,
							unsigned int	uSeed )
:	m_uSize( uSize ),
	m_fHillMin( fHillMin ),
	m_fHillMax( fHillMax ),
	m_uNumHills( uNumHills ),
	m_uFlattening( uFlattening ),
	m_bIsland( bIsland ),
	m_uSeed( uSeed )
{
	// check the parameters
	assert( uSize > 0 );
	assert( fHillMin >= 0.0 );
	assert( fHillMin < fHillMax );
	assert( fHillMax >= 0.0 );
	assert( uFlattening > 0 );
	
	#ifdef _WIN32
		// hack since windows fails to throw bad_alloc on a failed new like
		// it should.
		
		// allocate the map
		m_pMap = new float[ m_uSize * m_uSize ];
		
		if( m_pMap == NULL )
		{
			throw( ErrorOutOfMemory() );
		}
		
	#else
		// this is the c++ standard way of behaving
		try
		{
			// allocate the map
			m_pMap = new float[ m_uSize * m_uSize ];
		}
		catch( std::bad_alloc )
		{
			throw( ErrorOutOfMemory() );
		}
	#endif
}


//	~HillTerrain
//	----------------------------------------------------------------------------
HillTerrain::~HillTerrain()
{
	// free up the cell buffer.
	delete [] m_pMap;
}


//	Generate
//	----------------------------------------------------------------------------
void
HillTerrain::Generate( void )
{
	// make sure there is a terrain
	assert( m_pMap != NULL );

	Clear();
	
	// set the seed
	srand( m_uSeed );
	
	// add as many hills as needed
	for( int i = 0; i < m_uNumHills; ++i )
	{
		AddHill();
	}
	
	// now clean it up
	Normalize();
	Flatten();
}


//	Clear
//	----------------------------------------------------------------------------
void
HillTerrain::Clear( void )
{
	// make sure there is a terrain
	assert( m_pMap != NULL );

	for( int x = 0; x < m_uSize; ++x )
	{
		for( int y = 0; y < m_uSize; ++y )
		{
			SetCell( x, y, 0 );
		}
	}
}


//	AddHill
//	----------------------------------------------------------------------------
void
HillTerrain::AddHill( void )
{
	// make sure there is a terrain
	assert( m_pMap != NULL );

	// pick a size for the hill
	float fRadius = RandomRange( m_fHillMin, m_fHillMax );
	
	// pick a centerpoint for the hill
	float x, y;
	if( m_bIsland )
	{
		// island code:
		
		float fTheta = RandomRange( 0, 6.28 );
		// this determines in which direction from the center of the map the
		// hill will be placed.
		
		float fDistance = RandomRange( fRadius/2, m_uSize/2 - fRadius );
		// this is how far from the center of the map the hill be placed. note
		// that the radius of the hill is subtracted from the range to prevent
		// any part of a hill from reaching the very edge of the map.
		
		x = m_uSize/2.0 + cos( fTheta ) * fDistance;
		y = m_uSize/2.0 + sin( fTheta ) * fDistance;
		// converts theta and a distance into x and y coordinates.
	}
	else
	{
		// non-island code:
		
		x = RandomRange( -fRadius, m_uSize + fRadius );
		y = RandomRange( -fRadius, m_uSize + fRadius );
		// note that the range of the hill is used to determine the
		// centerpoint. this allows hills to have their centerpoint off the
		// edge of the terrain as long as part of the hill is in bounds. this
		// makes the terrains appear continuous all the way to the edge of the
		// map.
	}

	// square the hill radius so we don't have to square root the distance 
	float fRadiusSq = fRadius * fRadius;
	float fDistSq;
	float fHeight;
	
	// find the range of cells affected by this hill
	int xMin = x - fRadius - 1;
	int xMax = x + fRadius + 1;
	// don't affect cell outside of bounds
	if( xMin < 0 ) xMin = 0;
	if( xMax >= m_uSize ) xMax = m_uSize - 1;
	
	int yMin = y - fRadius - 1;
	int yMax = y + fRadius + 1;
	// don't affect cell outside of bounds
	if( yMin < 0 ) yMin = 0;
	if( yMax >= m_uSize ) yMax = m_uSize - 1;
	
	// for each affected cell, determine the height of the hill at that point
	// and add it to that cell
	for( int h = xMin; h <= xMax; ++h )
	{
		for( int v = yMin; v <= yMax; ++v )
		{
			// determine how far from the center of the hill this point is
			fDistSq = ( x - h ) * ( x - h ) + ( y - v ) * ( y - v );
			// determine the height of the hill at this point
			fHeight = fRadiusSq - fDistSq;
			
			// don't add negative hill values (i.e. outside the hill's radius)
			if( fHeight > 0 )
			{
				// add the height of this hill to the cell
				OffsetCell( h, v, fHeight );
			}	
		}
	}
}


//	Normalize
//	----------------------------------------------------------------------------
void
HillTerrain::Normalize( void )
{
	// make sure there is a terrain
	assert( m_pMap != NULL );
	
	float fMin = GetCell( 0, 0 );
	float fMax = GetCell( 0, 0 );
	
	// find the min and max
	for( int x = 0; x < m_uSize; ++x )
	{
		for( int y = 0; y < m_uSize; ++y )
		{
			float z = GetCell( x, y );
			if( z < fMin ) fMin = z;
			if( z > fMax ) fMax = z;
		}
	}

	// avoiding divide by zero (unlikely with floats, but just in case)
	if( fMax != fMin )
	{
		// divide every height by the maximum to normalize to ( 0.0, 1.0 )
		for( int x = 0; x < m_uSize; ++x )
		{
			for( int y = 0; y < m_uSize; ++y )
			{
				SetCell( x, y, ( GetCell( x, y ) - fMin ) / ( fMax - fMin ) );
			}
		}
	}
	else
	{
		// if the min and max are the same, then the terrain has no height, so just clear it
		// to 0.0.
		Clear();
	}
}	


//	Flatten
//	----------------------------------------------------------------------------
void
HillTerrain::Flatten( void )
{
	// make sure there is a terrain
	assert( m_pMap != NULL );

	// if flattening is one, then nothing would be changed, so just skip the
	// process altogether.
	if( m_uFlattening > 1 )
	{
		for( int x = 0; x < m_uSize; ++x )
		{
			for( int y = 0; y < m_uSize; ++y )
			{
				float fFlat 	= 1.0;
				float fOriginal	= GetCell( x, y );
				
				// flatten as many times as desired
				for( int i = 0; i < m_uFlattening; ++i )
				{
					fFlat *= fOriginal;
				}
				
				// put it back into the cell
				SetCell( x, y, fFlat );
			}
		}
	}
}


//	RandomRange
//	----------------------------------------------------------------------------
float
HillTerrain::RandomRange( float min, float max )
{
	return( ( rand() * ( max - min ) / RAND_MAX ) + min );
}


//	license agreement:
//
//	----------------------------------------------------------------------------
//	copyright (c) 2001 bob nystrom
//
//	permission is hereby granted, free of charge, to any person obtaining a copy
//	of this software and associated documentation files (the "software"), to
//	deal in the software without restriction, including without limitation the
//	rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
//	sell copies of the software, and to permit persons to whom the software is
//	furnished to do so, subject to the following conditions:
//
//	The above copyright notice and this permission notice shall be included in
//	all copies or substantial portions of the Software.
//
//	the software is provided "as is", without warranty of any kind, express or
//	implied, including but not limited to the warranties of merchantability,
//	fitness for a particular purpose and noninfringement. in no event shall the
//	authors or copyright holders be liable for any claim, damages or other
//	liability, whether in an action of contract, tort or otherwise, arising
//	from, out of or in connection with the software or the use or other dealings
//	in the software.
//	----------------------------------------------------------------------------
//	see www.opensource.org for more info.