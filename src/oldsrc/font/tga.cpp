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

typedef struct
{
   byte numIden;
   byte colorMapType;
   byte imageType;
   byte colorMapSpec[5]; // not used, just here to take up space
   byte origX[2];
   byte origY[2];
   byte width[2];
   byte height[2];
   byte bpp;
   byte imageDes; // don't use, space eater
} tgaHeader_t;

tga_t::tga_t()
{
   lastError = 0;
   bits = width = height = size = 0; 
   data = 0;
}

tga_t::tga_t(char *name)
{
   lastError = 0;
   bits = width = height = size = 0; 
   data = 0;

   Load(name);
}
// not tested, probably broken so use at your own risk
void tga_t::Write(char *dest, byte *buff, int w, int h, int pbits)
{
   byte *tempBuff = 0;
   tgaHeader_t header;
   int bit = 0;
   int type = 0;
   byte temp;

   switch (pbits)
   {
      case bitsRGB:
         tempBuff = new byte[w * h * (bit = 3)];
         type = 2;
      break;
      case bitsRGBA:
         tempBuff = new byte[w * h * (bit = 4)];   
         type = 2;
      break;
      case bitsGray:
         tempBuff = new byte[w * h * (bit = 1)];
         type = 3;
      break;
   }

   if (!buff)
      return;

	FILE *out = fopen(dest, "wb");
    
   memset(&header, 0, sizeof(tgaHeader_t));
   header.imageType = type;
   header.width[0] = w % 256;
   header.width[1] = w / 256;
   header.height[0] = h % 256;
   header.height[1] = h / 256;
   header.bpp = pbits;
   
   fwrite(&header, 1, sizeof(tgaHeader_t), out);

   memcpy(tempBuff, buff, w * h * bit);
	
   if (bit != 1)     
   {
	   for (int i = 0; i < (w * h * bit); i += bit)
	   {
   		temp = buff[i];
		   tempBuff[i] = buff[i + 2];
		   tempBuff[i + 2] = temp;
	   }
   }

   fwrite(tempBuff, 1, w * h * bit, out);
   fclose(out);
   delete [] tempBuff;
}

int tga_t::ParseBuffer(byte *buffer)
{
   if (!buffer)
      return badData;

   byte *where = buffer;
   tgaHeader_t *header = (tgaHeader_t *) where;
   
   where += (sizeof(tgaHeader_t) + header->numIden);

   if (header->colorMapType != 0)
      return badType;

   if (header->imageType != 2 && header->imageType != 3)
      return badType;

   width = header->width[0] + header->width[1] * 256; 
   height = header->height[0] + header->height[1] * 256; 
   bits = header->bpp; 
   size = width * height; 

   // make sure we are loading a supported type 
   if (bits != 32 && bits != 24 && bits != 8)
      return badBits; 

   data = GrabData(where, size);

   // no image data 
   if (data == 0)
      return badData;

   return 1;
}

int tga_t::Load(char *name)
{
   FILE *iFile = 0;
   byte *buffer = 0;
   uint fSize;

   if (!name)
      return notFound;

   if (!(iFile = fopen(name, "rb")))
      return notFound;

   fSize = FileGetSize(iFile);

   if (!(buffer = new byte[fSize + 1]))
   {
      fclose(iFile);
      return badData;
   }
   
   fread(buffer, 1, fSize, iFile);
   fclose(iFile);

   int ret = ParseBuffer(buffer);
   delete [] buffer;

   return ret;
}

void tga_t::Reset(void)
{
   delete [] data;
   lastError = 0;
   bits = width = height = size = 0; 
   data = 0;
}

byte *tga_t::GetRGBA(byte *buff, int size)
{
   byte *rgba = new byte[size * 4];
   byte temp;
   int i;

   if (rgba == 0)
      return 0;

   if (!memcpy(rgba, buff, size * 4))
   {
      delete [] rgba;
      return 0;
   }

   for (i = 0; i < size * 4; i += 4)
   {
      temp = rgba[i];
      rgba[i] = rgba[i + 2];
      rgba[i + 2] = temp;
   }

   return rgba;
}

byte *tga_t::GetRGB(byte *buff, int size)
{
   byte *rgb = new byte[size * 3];
   byte temp;
   int i;

   if (rgb == 0)
      return 0;

   if (!memcpy(rgb, buff, size * 3))
   {
      delete [] rgb;
      return 0;
   }

   for (i = 0; i < size * 3; i += 3)
   {
      temp = rgb[i];
      rgb[i] = rgb[i + 2];
      rgb[i + 2] = temp;
   }

   return rgb;
}

byte *tga_t::GetGray(byte *buff, int size)
{
   byte *grayData = new byte[size];

   if (grayData == 0)
      return 0;

   
   if (!memcpy(grayData, buff, size))
   {
      delete [] grayData;
      return 0;
   }

   return grayData;
}

byte *tga_t::GrabData(byte *buff, int size)
{
   if (bits == 32)
      return GetRGBA (buff, size);
   else if (bits == 24)
      return GetRGB (buff, size);	
   else if (bits == 8)
      return GetGray (buff, size);
   
   return 0;
}

