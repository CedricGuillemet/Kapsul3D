//
//
//	HillTerrain.h
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


class HillTerrain
{
	public:
		HillTerrain(	unsigned short	uSize			= 512,
						float			fHillMin		= 10.0,
						float			fHillMax		= 60.0,
						unsigned short	uNumHills		= 4000,
						unsigned short	uFlattening		= 1,
						bool			bIsland			= true,
						unsigned int	uSeed			= 12345 );
		//	constructs a blank terrain. note that every cell in the heightmap is
		//	a float (usually 4 bytes) and there are
		//	iHeightmapSize * iHeightmapSize cells in the heightmap, so a terrain
		//	can eat a lot of memory quickly.
		//
		//	arguments:
		//		uSize: width and height of the heightmap. only square heightmaps
		//			are supported in this implemented, but that could be easily
		//			changed.
		//
		//		fHillMin: smallest possible radius for a hill.
		//			range: 0.0 to fHillMax
		//
		//		fHillMax: largest possible radius for a hill.
		//			range: fHillMax or greater
		//
		//		uNumHills: number of hills to add to the terrain when generated.
		//			range: any
		//
		//		uFlattening: power to raise heightmap values to to flatten. 1 is
		//			no flattening. increasing this number very dramatically
		//			distorts the map.
		//			range: 1 or greater
		//
		//		bIsland: true if hills should be positioned to create an island.
		//			if so, the edge of the heightmap will always reach 0.0,
		//			otherwise, hills will be placed randomly distributed across
		//			the heightmap.
		//
		//		uSeed: the value to seed the random number generator with before
		//			generating. change this to create different terrains. store
		//			it to be able to recreate a terrain.
		//
		//	throws:
		//		ErrorOutOfMemory
		//			if it could not allocate the heightmap.		
		
		~HillTerrain();
		//	deallocates the heightmap and destructs the terrain.
		
		void	Generate( void );
		//	clears, regenerates, normalizes, and flattens the terrain using the
		//	current parameters. unless the seed is changed, this will generate
		//	the same terrain every time. call this after setting the parameters
		//	to create a terrain.

		unsigned int GetSize( void );
		//	returns:
		//		the size of the heightmap in either direction.
		
		float	GetHillMin( void );
		//	returns:
		//		the minimum possible hill radius.
		
		void	SetHillMin( float fHillMin );
		//	sets the minimum possible radius for a hill. must be regenerated to
		//	have any visible effect.
		//
		//	arguments:
		//		fHillMin: the minimum hill radius.
		//		range: 0.0 to m_fHillMax
		
		float	GetHillMax( void );
		//	returns:
		//		the maximum possible hill radius.
		
		void	SetHillMax( float fHillMax );
		//	sets the maximum possible radius for a hill. must be regenerated to
		//	have any visible effect.
		//
		//	arguments:
		//		fHillMax: the maximum hill radius.
		//			range: m_fHillMin or greater
		
		void	SetHillSize( float fHillMin, float fHillMax );
		//	sets the range of possible hill radii. must be regenerated to have
		//	any visible effect.
		//
		//	arguments:
		//		fHillMin: the minimum hill radius.
		//			range: 0.0 to fHillMax
		//
		//		fHillMax: the maximum hill radius.
		//			range: fHillMin or greater
		
		unsigned int GetNumHills( void );
		//	returns:
		//		the number of hills to add when generating.
		
		void	SetNumHills( unsigned int uNumHills );
		//	sets the hills added when the terrain is generated. must be
		//	regenerated to have any visible effect.
		//
		//	arguments:
		//		uNumHills: the number of hills.
		//			range: any
		
		unsigned int GetFlattening( void );
		//	returns:
		//		the amount of flattening to apply to the terrain.
		
		void	SetFlattening( unsigned int uFlattening );
		//	sets the amount of flattening to apply to the terrain when
		//	generated. must be regenerated to have any visible effect.
		//
		//	arguments:
		//		uFlattening: the amount of flattening.
		//			range: 1 or greater
		
		bool	IsIsland( void );
		//	returns:
		//		true if this terrain is an island.
		
		void	SetIsland( bool bIsland );
		//	sets whether or not this terrain is an island. must be regenerated
		//	to have any visible effect.
		//
		//	arguments:
		//		bIsland: true if this terrain will be an island
		
		unsigned int GetSeed( void );
		//	returns:
		//		the random seed used to generate the terrain.
		
		void	SetSeed( unsigned int uSeed );
		//	sets the random seed used to generate the terrain. must be
		//	regenerated to have any visible effect.
		//
		//	arguments:
		//		uSeed: the random seed to use.
		//			range: any
		
		float	GetCell( int x, int y );
		//	determines the height of the map at the given cell.
		//
		//	arguments:
		//		x, y: the position of the cell.
		//			range: 0 to heightmap size - 1
		//
		//	returns:
		//		the value of the heightmap at that cell.
		
		void	SetCell( int x, int y, float value );
		//	sets the height of the map at the given cell.
		//
		//	arguments:
		//		x, y: the position of the cell.
		//			range: 0 to heightmap size - 1
		//
		//		value: the height to assign to that cell.
		
		void	OffsetCell( int x, int y, float value );
		//	modifies the height of the map at the given cell.
		//
		//	arguments:
		//		x, y: the position of the cell.
		//			range: 0 to heightmap size - 1
		//
		//		value: the height to add to that cell.
		
		// exception classes
		class	ErrorOutOfMemory {};

	private:
		unsigned short	m_uSize;
		float			m_fHillMin;
		float			m_fHillMax;
		unsigned short	m_uNumHills;
		unsigned short	m_uFlattening;
		bool			m_bIsland;
		unsigned int	m_uSeed;
		
		float	*m_pMap;	// buffer of cells
		
		void	Clear( void );
		void	AddHill( void );
		void	Normalize( void );
		void	Flatten( void );
		
		float	RandomRange( float min, float max );

		// intentionally unimplemented copy constructor and assigment operator.
		// implement these to be able to copy terrains.
		HillTerrain( const HillTerrain & );
		HillTerrain& operator=( const HillTerrain & );
		
}; // class HillTerrain


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
/*
    // check the parameters
	//assert( fHillMin >= 0.0 );
	//assert( fHillMin < m_fHillMax );
*/	
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
	//assert( m_fHillMin < fHillMax );
	//assert( fHillMax >= 0.0 );
	
	m_fHillMax = fHillMax;
}


//	SetHillSize
//	----------------------------------------------------------------------------
inline void
HillTerrain::SetHillSize( float fHillMin, float fHillMax )
{
	// check the parameters
	//assert( fHillMin >= 0.0 );
	//assert( fHillMin < fHillMax );
	//assert( fHillMax >= 0.0 );
	
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
	//assert( uFlattening > 0 );
	
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
	//assert( m_pMap != NULL );
	
	// check the parameters
	//assert( ( x >= 0 ) && ( x < m_uSize ) );
	//assert( ( y >= 0 ) && ( y < m_uSize ) );
		
	return( m_pMap[ x + ( y * m_uSize ) ] );
}


//	SetCell
//	----------------------------------------------------------------------------
inline void
HillTerrain::SetCell( int x, int y, float value )
{
	// make sure we have a terrain
	//assert( m_pMap != NULL );
	
	// check the parameters
	//assert( ( x >= 0 ) && ( x < m_uSize ) );
	//assert( ( y >= 0 ) && ( y < m_uSize ) );
	
	// set the cell
	m_pMap[ x + ( y * m_uSize ) ] = value;
}


//	OffsetCell
//	----------------------------------------------------------------------------
inline void
HillTerrain::OffsetCell( int x, int y, float value )
{
	// make sure we have a terrain
	//assert( m_pMap != NULL );
	
	// check the parameters
	//assert( ( x >= 0 ) && ( x < m_uSize ) );
	//assert( ( y >= 0 ) && ( y < m_uSize ) );

	// offset the cell
	m_pMap[ x + ( y * m_uSize ) ] += value;
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