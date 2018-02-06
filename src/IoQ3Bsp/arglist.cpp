#include <ctype.h>
#include <assert.h>

#include "arglist.h"

//############################################################################
//##                                                                        ##
//##  ARGLIST.CPP                                                             ##
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

int TranslateEscapedChar( int ch )
{
  switch( ch )
  {
  case 't':
    ch = '\t';
    break;
  case 'n':
    ch = '\n';
    break;
  case 'f':
    ch = '\f';
    break;
  }
  return ch;
}


ArgList::ArgList( void )
{
}


ArgList::ArgList( const String& line )
{
  Set( line );
}


ArgList::~ArgList( void )
{
}


ArgList::ArgList( const ArgList& copy )
{
  Copy( copy );
}


ArgList& ArgList::operator= ( const ArgList& copy )
{
  Copy( copy );
  return *this;
}


ArgList& ArgList::operator= ( const String& line )
{
  Set( line );
  return *this;
}


void ArgList::Copy( const ArgList& copy )
{
  mArgs = copy.mArgs;
}

void ArgList::Set( const String& line )
{
  enum State
  {
    LINE_START,
    LINE_SPACE,
    LINE_ARG,
    LINE_ESCAPED,
    LINE_QUOTED,
    LINE_QUOTEDESCAPED
  };
  State state;
  CharVector curArg;

  state = LINE_START;
  curArg.clear();
  mArgs.clear();

  for(unsigned int index = 0; index < line.size(); ++index )
  {
    int ch = line[index];

    if( ch == '\n' )
    {
      break;
    }

    switch( state )
    {
ProcessCharNormally:  // I know, a goto.  But it was convenient. ;)
    case LINE_ARG:
      if( ch == '"' )
      {
        state = LINE_QUOTED;
      }
      else if( ch == '\\' )
      {
        state = LINE_ESCAPED;
      }
      else if( isspace( ch ) )
      {
        String foo( &curArg[0], curArg.size() );
        mArgs.push_back( foo );
        curArg.clear();
        state = LINE_SPACE;
      }
      else
      {
        curArg.push_back( ch );
      }
      break;
      
    case LINE_START:
      if( !isspace( ch ) )
      {
        state = LINE_ARG;
        goto ProcessCharNormally;
      }
      break;
      
    case LINE_SPACE:
      if( !isspace( ch ) )
      {
        state = LINE_ARG;
        goto ProcessCharNormally;
      }
      break;
      
    case LINE_QUOTED:
      if( ch == '"' )
      {
        state = LINE_ARG;
      }
// Don't process escape characters inside quoted strings!!!
//      else if( ch == '\\' )
//      {
//        state = LINE_QUOTEDESCAPED;
//      }
      else
      {
        curArg.push_back( ch );
      }
      break;
      
    case LINE_ESCAPED:
      ch = TranslateEscapedChar( ch );
      state = LINE_ARG;
      curArg.push_back( ch );
      break;
      
    case LINE_QUOTEDESCAPED:
      ch = TranslateEscapedChar( ch );
      state = LINE_QUOTED;
      curArg.push_back( ch );
      break;
    }
  }

  switch( state )
  {
  case LINE_ARG:
  case LINE_QUOTED:
  case LINE_ESCAPED:
  case LINE_QUOTEDESCAPED:
    {
    String foo( &curArg[0], curArg.size() );
    mArgs.push_back( foo );
    }
    break;
    
  case LINE_START:
  case LINE_SPACE:
    break;
  }
}


int ArgList::size( void ) const
{
  return mArgs.size();
}


bool ArgList::empty( void ) const
{
  return mArgs.empty();
}


const String& ArgList::operator[]( int argc ) const
{
  return mArgs[argc];
}


String& ArgList::operator[]( int argc )
{
  return mArgs[argc];
}


ArgList::operator String ( void ) const
{
  CharVector result;

  result.clear();
  for(unsigned int argc = 0; argc < mArgs.size(); ++argc )
  {
    if( argc != 0 )
    {
      result.push_back( ' ' );
    }

    if( mArgs[argc].size() != 0 )
    {
      for(unsigned int index = 0; index < mArgs[argc].size(); ++index )
      {
        const String &foo = mArgs[argc];
        int ch = foo[index];

        assert( ch != '\0' );
        if( isspace( ch ) || ch == '"' || ch == '\\' )
        {
          result.push_back( '\\' );
        }
        result.push_back( ch );
      }
    }
    else
    {
      result.push_back( '"' );
      result.push_back( '"' );
    }
  }
  return String( &result[0], result.size() );
}


void ArgList::clear( void )
{
  mArgs.clear();
}


void ArgList::Push( const String& arg )
{
  mArgs.push_back( arg );
}

