#ifndef ARGLIST_H
#define ARGLIST_H

#include "stl.h"

//############################################################################
//##                                                                        ##
//##  ARGLIST.H                                                             ##
//##                                                                        ##
//##  Parses a string into a series of arguments.                           ##
//##                                                                        ##
//##  OpenSourced 12/5/2000 by John W. Ratcliff                             ##
//##                                                                        ##
//##  No warranty expressed or implied.                                     ##
//##                                                                        ##
//##  Part of the Q3BSP project, which converts a Quake 3 BSP file into a   ##
//##  polygon mesh.                                                         ##
//############################################################################
//##                                                                        ##
//##  Contact John W. Ratcliff at jratcliff@verant.com                      ##
//############################################################################

class ArgList
{
public:
  ArgList( void );
  ArgList( const String& line );
  ~ArgList( void );
  ArgList( const ArgList& copy );
  ArgList& operator= ( const ArgList& copy );
  ArgList& operator= ( const String& line );

  void Set( const String& line );

  const String& operator[]( int argc ) const;
  String& operator[]( int argc );

  operator String (void) const;

  // lower case to emulate an STL container
  bool empty( void ) const;
  int size( void ) const;
  void clear( void );

  void Push( const String& arg );

  const StringVector & Get(void) const { return mArgs; }
protected:
  void Copy( const ArgList& copy );
  StringVector mArgs;
};

#endif // ARGLIST_H
