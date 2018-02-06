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

glTga_t::glTga_t()
{
   minFilter = magFilter = GL_LINEAR;
   wrapS = wrapT = GL_REPEAT;
   texEnv = GL_MODULATE;
   texid = format = internal = 0;
   mipmap = 0;
   lastError = 0;
}

glTga_t::glTga_t(char *name)
{
   minFilter = magFilter = GL_LINEAR;
   wrapS = wrapT = GL_REPEAT;
   texEnv = GL_MODULATE;
   texid = format = internal = 0;
   lastError = 0;
   mipmap = 0;
   Load(name);
}

glTga_t::glTga_t(char *name, GLuint texId, GLenum nf)
{
   minFilter = magFilter = GL_LINEAR;
   wrapS = wrapT = GL_REPEAT;
   texEnv = GL_MODULATE;
   texid = format = internal = 0;
   lastError = 0;
   mipmap = 0;
   Load(name, texId, nf);
}

int glTga_t::Load(char *name)
{
   int ret = tga_t::Load(name);

   if (ret == 1)
      SetupFormat();
   return ret;
}

int glTga_t::Load(char *name, GLuint texId, GLenum nf)
{
   int err;

   if ((err = Load(name)) == 1)
   {
      SetId(texId);      

      if (nf)
         format = nf;
   }

   return err;
}

int glTga_t::LoadBuffer(byte *buff)
{
   int ret = tga_t::LoadBuffer(buff);

   if (ret)
      SetupFormat();
   return ret;
}

int glTga_t::LoadBuffer(byte *buff, GLuint texId, GLenum nf)
{
   int err;

   if ((err = LoadBuffer(buff)) == 1)
   {
      SetId(texId);      

      if (nf)
         format = nf;
   }

   return err;
}

int glTga_t::Upload(bool n)
{
   if (!data)
      return badUpload;

   if (!CheckSize (width) || !CheckSize (height))
      return badDimension;

   glBindTexture(GL_TEXTURE_2D, texid);
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, texEnv);

   if (mipmap)
      gluBuild2DMipmaps(GL_TEXTURE_2D, internal, width, height, format,
       GL_UNSIGNED_BYTE, data);
   else
      glTexImage2D(GL_TEXTURE_2D, 0, internal, width, height, 0, format,
       GL_UNSIGNED_BYTE, data);
   
   if (n)
      Release();
   
   return 1;
}

int glTga_t::CheckSize(int x)
{
   uint i = 0;

   for ( ; pow(2, i) <= maxTexSize; i++)
      if (x == pow(2, i))
         return 1;
   return 0;
}

void glTga_t::Reset(void)
{
   minFilter = magFilter = GL_LINEAR;
   wrapS = wrapT = GL_REPEAT;
   texEnv = GL_MODULATE;
   texid = format = internal = 0;
   tga_t::Reset();
}

void glTga_t::SetupFormat(void)
{
   switch (bits)
   {
      case 8:
         format = internal = GL_ALPHA;
      break;
      case 24:
         format = internal = GL_RGB;
      break;
      case 32:
         format = internal = GL_RGBA;
      break;
   }
}