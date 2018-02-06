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
#include "stdafx.h"
#include "utility.h"

long FileGetSize(FILE *stream)
{
   long curpos, length;
   curpos = ftell(stream);
   fseek(stream, 0L, SEEK_END);
   length = ftell(stream);
   fseek(stream, curpos, SEEK_SET);
   return length;
}

long FileNameGetSize(char *name)
{
   FILE *f = fopen(name, "r");
   long size = FileGetSize(f);
   fclose(f);
   return size;
}

byte *FileReadAll(FILE *in, long *dsize)
{
   byte *b = 0;
   long size = 0;
   
   size = FileGetSize(in);   

   if (!size)
      return 0;
   
   b = new byte[size + 1];
   memset(b, '\0', size + 1);

   if (!b)
      return 0;
   
   fread(b, 1, size, in); // check return with size?

   if (dsize)
      *dsize = size;

   return b;
}

byte *FileReadAll(char *name, long *dsize)
{
   FILE *in = fopen(name, "r");
   
   if (!in)
      return 0;

   byte *b = FileReadAll(in, dsize);
   
   fclose(in);
   
   return b;
}

void LineRead(char **pos, char *dest)
{
   char *start = *pos;

   while (**pos && **pos != '\n' && **pos != '\r')
      dest[*pos - start] = *(*pos)++;
   dest[*pos - start] = '\0';
}

char *LineRead(char **pos)
{
   char *start = *pos;
   char *buffer = 0;
   
   while (**pos && **pos != '\n' && **pos != '\r')
      (*pos)++;

   buffer = new char[(*pos - start) + 1];
   strncpy(buffer, start, *pos - start);
   buffer[*pos - start] = '\0';

   return buffer;
}

void LineEat(char **pos)
{
   while(**pos && **pos != '\n' && **pos != '\r')
      (*pos)++;
   if (**pos)
      (*pos)++;
}

void LineEatWhite(char **pos)
{
   while (**pos &&
    (**pos == ' ' || **pos == '\t' || **pos == '\r' || **pos == '\n'))
      (*pos)++;
}

char *LineReadUntil(char **pos, char end)
{
   char *start = *pos;
   char *buffer = 0;

   while (**pos && **pos != end)
      (*pos)++;   

   buffer = new char[(*pos - start) + 1];   
   strncpy(buffer, start, *pos - start);
   buffer[*pos - start] = '\0';

   if (**pos && **pos == end)
      return buffer;
   delete [] buffer;
   return 0;   
}

void LineReadChars(char **pos, char *dest)
{
   char *start = *pos;
   while (**pos && uIsAlpha(**pos))
      dest[*pos - start] = *(*pos)++;
   dest[*pos - start] = '\0';
}

int LineReadInt(char **pos)
{
   int val = 0;
   while (**pos && (**pos >= '0' && **pos <= '9'))
      val = (val * 10) + (*(*pos)++ - '0');
   return val;
}

