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
      (10/28/00)
         - fixed region bug
      (10/19/00)
         - started re-working old font code
   TODO  
      - add ability to change gradient or shadow color mid string?
      ? will it still compile on linux?

   DOCUMENTATION
      - for documentation on this class go here
        http://nate.scuzzy.net/common/font.html
      - for information about where this code came from go here
        http://nate.scuzzy.net/gltexfont/
*/
#ifndef __FONTH__
#define __FONTH__

#include <stdio.h>
#include <stdarg.h>

#include <GL/gl.h>

struct font_t
{
   font_t();
   virtual ~font_t() {Release();}

   GLboolean GetManualModes(void)        {return modeMan;}
   void SetManualModes(GLboolean m)      {modeMan = m;}
   void SetupFontModes(void)             {glState.GetStates();}
   void UndoFontModes(void)              {glState.SetStates();}
   GLboolean GetManualProjection(void)   {return projMan;}
   void SetManualProjection(GLboolean m) {projMan = m;}

   GLboolean GetCoordCustom(void)        {return coordCustom;}
   void SetCoordCustom(GLboolean s)      {coordCustom = s;}
   void SetupCoords(GLint l, GLint r, GLint b, GLint t)
                                         {coord.Setup(l, r, b, t);}

   GLboolean GetBold(void)               {return bold;}
   void SetBold(GLboolean b)             {bold = b;}
   GLboolean GetItalic(void)             {return italic;}
   void SetItalic(GLboolean i)           {italic = i;}
   GLboolean GetGradient(void)           {return gradient;}
   void SetGradient(GLboolean g)         {gradient = g;}
   GLboolean GetShadow(void)             {return shadow;}
   void SetShadow(GLboolean s)           {shadow = s;}
   
   void SetRegion(GLint x, GLint y, GLint w, GLint h)
    {region = 1; regionDims[0] = x; regionDims[1] = y;
     regionDims[2] = w; regionDims[3] = h;}

   // normal color
   void Color3f(GLfloat r, GLfloat g, GLfloat b)
    {ColorSet(colorForGrnd, r, g, b, 1);}
   void Color3ub(GLubyte r, GLubyte g, GLubyte b)
    {ColorSet(colorForGrnd, r, g, b, 255);}
   void Color3fv(GLfloat *clr)
    {ColorSet(colorForGrnd, clr, 3);}
   void Color3ubv(GLubyte *clr)
    {ColorCopy(colorForGrnd, clr, 3);}
   void Color4f(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
    {ColorSet(colorForGrnd, r, g, b, a);}
   void Color4ub(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
    {ColorSet(colorForGrnd, r, g, b, a);}
   void Color4fv(GLfloat *clr)
    {ColorSet(colorForGrnd, clr, 4);}
   void Color4ubv(GLubyte *clr)
    {ColorCopy(colorForGrnd, clr, 4);}
   // gradient color
   void GradientColor3f(GLfloat r, GLfloat g, GLfloat b)
    {ColorSet(colorGrad, r, g, b, 1);}
   void GradientColor3ub(GLubyte r, GLubyte g, GLubyte b)
    {ColorSet(colorGrad, r, g, b, 255);}
   void GradientColor3fv(GLfloat *clr)
    {ColorSet(colorGrad, clr, 3);}
   void GradientColor3ubv(GLubyte *clr)
    {ColorCopy(colorGrad, clr, 3);}
   void GradientColor4f(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
    {ColorSet(colorGrad, r, g, b, a);}
   void GradientColor4ub(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
    {ColorSet(colorGrad, r, g, b, a);}
   void GradientColor4fv(GLfloat *clr)
    {ColorSet(colorGrad, clr, 4);}
   void GradientColor4ubv(GLubyte *clr)
    {ColorCopy(colorGrad, clr, 4);}
   // shadow color
   void ShadowColor3f(GLfloat r, GLfloat g, GLfloat b)
    {ColorSet(colorShadow, r, g, b, 1);}
   void ShadowColor3ub(GLubyte r, GLubyte g, GLubyte b)
    {ColorSet(colorShadow, r, g, b, 255);}
   void ShadowColor3fv(GLfloat *clr)
    {ColorSet(colorShadow, clr, 3);}
   void ShadowColor3ubv(GLubyte *clr)
    {ColorCopy(colorShadow, clr, 3);}
   void ShadowColor4f(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
    {ColorSet(colorShadow, r, g, b, a);}
   void ShadowColor4ub(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
    {ColorSet(colorShadow, r, g, b, a);}
   void  ShadowColor4fv(GLfloat *clr)
    {ColorSet(colorShadow, clr, 4);}
   void ShadowColor4ubv(GLubyte *clr)
    {ColorCopy(colorShadow, clr, 4);}

   void Release(void) {if (texId) glDeleteTextures(1, &texId); texId = 0;}
   void Reset(void);
   bool Load(char *name, GLint row = 0, GLint col = 0);
   void Draw(GLint xpos, GLint ypos, char *format, ...);
   
public:
	CKOption *m_Option;
   enum
   {
      maxLen = 1024 * 4,   // max length of a string we can draw
      formatBoldOn = 1,    // \b+ was scanned
      formatBoldOff,       // \b- was scanned
      formatItalicOn,      // \i+ was scanned
      formatItalicOff,     // \i- was scanned
      formatColor,         // \c(int int int) was scanned
      formatColorA,        // \a(int int int int) was scanned
      toggleOn = 1,        // + was scanned
      toggleOff = 2,       // - was scanned
      fontBlockCol = 16,   // number of characters per column
      fontBlockRow = 16,   // number of characters per row
      fontTabSize = 4,     // how much to move for a \t
      fontItalicShift = 8, // how much to move for italics
      fontBoldShift = 2,   // how much to move for bold
      fontShadowShift = 2, // how much to move for shadow
   };

   struct fontGLRenderState_t
   {  
      void SetStates(void);
      void GetStates(void);
   protected:
      GLint matrixMode;
      GLint lightingOn;
      GLint blendOn;
      GLint depthOn;
      GLint textureOn;
      GLint scissorOn;
      GLint blendSrc;
      GLint blendDst;
   };

   struct fontCoord_t
   {
      fontCoord_t() {up = 1; right = 1; dim[0] = dim[1] = dim[2] = dim[3] = 0;}
      
      void Setup(GLint l, GLint r, GLint b, GLint t);

      GLint up;   
      GLint right;
      GLint dim[4];
   };

   void WalkString(GLint xpos, GLint ypos, char *string);
   void ProcessChar(GLint x, GLint y, char c);
   void DrawChar(GLint x, GLint y, char c);

   // utility type calls
   void ColorCopy(GLubyte *dest, const GLubyte *src, int n)
    {for (GLint i = 0; i < n; i++) dest[i] = src[i];}
   void ColorSet(GLubyte *dest, GLfloat r, GLfloat g, GLfloat b, GLfloat a)
    {dest[0] = (GLubyte) (255.0f * r); dest[1] = (GLubyte) (255.0f * g);
     dest[2] = (GLubyte) (255.0f * b); dest[3] = (GLubyte) (255.0f * a);}
   void ColorSet(GLubyte *dest, GLubyte r, GLubyte g, GLubyte b, GLubyte a)   
    {dest[0] = r; dest[1] = g; dest[2] = b; dest[3] = a;}
   void ColorSet(GLubyte *dest, const GLfloat *src, int n)
    {for (GLint i = 0; i < n; i++) dest[i] = (GLubyte) (255 * src[i]);}

   GLint FormatCheck(char **where, GLubyte *clr);
   GLint IsToggle(char **where);
   GLboolean ParseColor(GLubyte *clr, char **where, GLint num);
   void MakeFontMap(GLint row, GLint col);

   // rendering options
   GLuint texId;            // font texture id, held
   //GLint size;              // font size, default 12, held
   GLboolean bold;          // bold, default 0
   GLboolean italic;        // italic, default 0
   GLboolean gradient;      // gradient, default 0
   GLboolean shadow;        // shadow, default 0
   GLboolean region;        // font region, default 0
   GLubyte colorForGrnd[4]; // font color, default white
   GLubyte colorGrad[4];    // gradient color, default gray
   GLubyte colorShadow[4];  // shadow color, default gray 

   // system
   GLint regionDims[4];     // dimensions of the region (x, y, w, h)
   GLdouble tIncX;           // used for texture coords, x axis amount to move
   GLdouble tIncY;           // used for texture coords, y axis amount to move
   GLdouble tPoints[257][2]; // font map
   GLboolean modeMan;       // set modes manually, held
   GLboolean projMan;       // set projection manually, held
   GLboolean coordCustom;   // use a special coordinate system
   fontCoord_t coord;       // coordinate system, held
   fontGLRenderState_t glState; // stores GL modes
   static char buffer[maxLen + 1];  // one buffer for all font objects
   unsigned int texid;
};

#endif