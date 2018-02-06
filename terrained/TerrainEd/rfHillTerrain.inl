//
//
//	HillTerrain.inl
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

#include <assert.h>
#include <stdlib.h>	// for NULL

namespace RobotFrog
{

//	GetSize
//	----------------------------------------------------------------------------
inline unsigned int HillTerrain::GetSize( void )
{
	return( m_uSize );
}


//	GetHillMin
//	----------------------------------------------------------------------------
inline float
HillTerrain::GetHillMin( void )
{
	return( m_fHillMin );
}


//	SetHillMin
//	----------------------------------------------------------------------------
inline void
HillTerrain::SetHillMin( float fHillMin )
{
	// check the parameters
	assert( fHillMin >= 0.0 );
	assert( fHillMin < m_fHillMax );
	
	m_fHillMin = fHillMin;
}


//	GetHillMax
//	----------------------------------------------------------------------------
inline float
HillTerrain::GetHillMax( void )
{
	return( m_fHillMax );
}


//	SetHillMax
//	----------------------------------------------------------------------------
inline void
HillTerrain::SetHillMax( float fHillMax )
{
	// check the parameters
	assert( m_fHillMin < fHillMax );
	assert( fHillMax >= 0.0 );
	
	m_fHillMax = fHillMax;
}


//	SetHillSize
//	----------------------------------------------------------------------------
inline void
HillTerrain::SetHillSize( float fHillMin, float fHillMax )
{
	// check the parameters
	assert( fHillMin >= 0.0 );
	assert( fHillMin < fHillMax );
	assert( fHillMax >= 0.0 );
	
	m_fHillMin = fHillMin;
	m_fHillMax = fHillMax;
}


//	GetNumHills
//	----------------------------------------------------------------------------
inline unsigned int
HillTerrain::GetNumHills( void )
{
	return( m_uNumHills );
}


//	SetNumHills
//	----------------------------------------------------------------------------
inline void
HillTerrain::SetNumHills( unsigned int uNumHills )
{
	m_uNumHills = uNumHills;
}


//	GetFlattening
//	----------------------------------------------------------------------------
inline unsigned int
HillTerrain::GetFlattening( void )
{
	return( m_uFlattening );
}


//	SetFlattening
//	----------------------------------------------------------------------------
inline void
HillTerrain::SetFlattening( unsigned int uFlattening )
{
	// check the parameters
	assert( uFlattening > 0 );
	
	m_uFlattening = uFlattening;
}


//	IsIsland
//	----------------------------------------------------------------------------
inline bool
HillTerrain::IsIsland( void )
{
	return( m_bIsland );
}


//	SetIsland
//	----------------------------------------------------------------------------
inline void
HillTerrain::SetIsland( bool bIsland )
{
	m_bIsland = bIsland;
}


//	GetSeed
//	----------------------------------------------------------------------------
inline unsigned int
HillTerrain::GetSeed( void )
{
	return( m_uSeed );
}


//	SetSeed
//	----------------------------------------------------------------------------
inline void
HillTerrain::SetSeed( unsigned int uSeed )
{
	m_uSeed = uSeed;
}


//	GetCell
//	----------------------------------------------------------------------------
inline float
HillTerrain::GetCell( int x, int y )
{
	// make sure we have a terrain
	assert( m_pMap != NULL );
	
	// check the parameters
	assert( ( x >= 0 ) && ( x < m_uSize ) );
	assert( ( y >= 0 ) && ( y < m_uSize ) );
		
	return( m_pMap[ x + ( y * m_uSize ) ] );
}


//	SetCell
//	----------------------------------------------------------------------------
inline void
HillTerrain::SetCell( int x, int y, float value )
{
	// make sure we have a terrain
	assert( m_pMap != NULL );
	
	// check the parameters
	assert( ( x >= 0 ) && ( x < m_uSize ) );
	assert( ( y >= 0 ) && ( y < m_uSize ) );
	
	// set the cell
	m_pMap[ x + ( y * m_uSize ) ] = value;
}


//	OffsetCell
//	----------------------------------------------------------------------------
inline void
HillTerrain::OffsetCell( int x, int y, float value )
{
	// make sure we have a terrain
	assert( m_pMap != NULL );
	
	// check the parameters
	assert( ( x >= 0 ) && ( x < m_uSize ) );
	assert( ( y >= 0 ) && ( y < m_uSize ) );

	// offset the cell
	m_pMap[ x + ( y * m_uSize ) ] += value;
}

} // namespace RobotFrog


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