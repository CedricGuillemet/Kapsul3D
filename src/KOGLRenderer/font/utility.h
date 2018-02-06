/*
   Copyright (C) 2000 Nate Miller nkmiller@calpoly.edu

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

   See gpl.txt for more information regarding the GNU General Public License.
*/
/*
   WORKLOG
      (10/31/00)
         - removed duplicate code
      (10/23/00)
         - added clamp, min and max.  they assume the object has the proper 
           operators avaliable
      (10/17/00)
         - LineReadUntil() now returns 0 if it doesn't hit the 'end' char
      (10/13/00) 
         - added another version of LineReadUntil()
      (10/07/00)
         - added IsAlpha() and IsComment()
         - added LineReadChars(), only reads characters
   TODO  

*/
#ifndef __UTILH__
#define __UTILH__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "mmgr.h" 

typedef unsigned char byte;
typedef unsigned int  uint;

// assmues objects have proper operators
template <class Type>
inline Type uClamp(Type a, Type min, Type max)
 {return a < min ? min : a > max ? max : a;}
template <class Type>
inline Type uMax(Type a, Type b)   {return a > b ? a : b;}
template <class Type>
inline Type uMin(Type a, Type b)   {return a < b ? a : b;}

inline bool uIsAlpha(char c)
 {return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));}
inline bool uIsComment(char *line) {return (line[0] == '/' && line[1] == '/');}
inline bool uIsWhite(char c)
 {return (c == ' ' || c == '\t' || c == '\r' || c == '\n');}

// returns the file size
long FileGetSize(FILE *stream);
long FileNameGetSize(char *name);

// returns the contents of a file
byte *FileReadAll(FILE *in, long *size = 0);
byte *FileReadAll(char *name, long *size = 0);

// reads a line
void LineRead(char **pos, char *dest);
char *LineRead(char **pos);

// eats a line or white space
void LineEat(char **pos);
void LineEatWhite(char **pos);

// read a line until a char
char *LineReadUntil(char **pos, char end);
inline char *LineReadUntil(char *pos, char end)
 {return LineReadUntil(&pos, end);}
inline void LineReadUntil(char *pos, char end, char *dest)
 {dest = LineReadUntil(&pos, end);}

// read all characters in a line
void LineReadChars(char **pos, char *dest);
inline void LineReadChars(char *pos, char *dest)
 {LineReadChars(&pos, dest);}

// read an int from a string
int LineReadInt(char **pos);
inline int LineReadInt(char *pos)
 {return LineReadInt(&pos);}

#endif