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
#include "font.h"
#include "utility.h"

//extern CKOption *m_Option;
//extern HINSTANCE ghInstDLL;

char font_t::buffer[maxLen + 1] = {'\0'};
static const GLubyte white[4] =   {255, 255, 255, 255};
static const GLubyte gray[4]  =   {128, 128, 128, 255};

/*
=============
Setup
=============
Sets up the coordinate system that will be used when drawing the characters.
*/
void font_t::fontCoord_t::Setup(GLint l, GLint r, GLint b, GLint t)
{
	right = l < r ? 1 : -1;
	up    = b < t ? 1 : -1;
	
	dim[0] = l;
	dim[1] = r;
	dim[2] = b;
	dim[3] = t;
}

/*
=============
font_t
=============
The amazing font_t constructor.
*/
font_t::font_t()
{
	m_Option= (CKOption*)GetGOption();

	texId = 0;
	tIncX = tIncY = 0.0f;
	modeMan = projMan = coordCustom = 0;
	Reset();
	
	
	CKFontManager fntmng;

	if(!fntmng.Initialize())
	{
		//fntmng.GetLastError(Msg);
		//MessageBox(hWnd,Msg,"Error",MB_OK);
	}

	if(fntmng.AddFont(m_Option->GetFont()))
	{
		fntmng.AddFont("por2.TTF");
	}

	fntmng.SetFontSize(0,MODE_512_512);
	BYTE dest[512*512*3];
	memset(dest,0,512*512*3);

	fntmng.Render(0,MODE_512_512,dest);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texid);
    glBindTexture(GL_TEXTURE_2D, texid);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    int err=gluBuild2DMipmaps(GL_TEXTURE_2D, 3, 512,512, GL_RGB, GL_UNSIGNED_BYTE, dest);

	MakeFontMap(16, 16);
}

/*
=============
Reset
=============
All variables that are not held over a font_t::Draw() call are reset here.  
*/
void font_t::Reset(void)
{
	bold = 0;      
	italic = 0;
	gradient = 0;
	shadow = 0;
	region = 0;
	regionDims[0] = regionDims[1] = regionDims[2] = regionDims[3] = 0;
	ColorCopy(colorForGrnd, white, 4);
	ColorCopy(colorGrad, gray, 4);
	ColorCopy(colorShadow, gray, 4);
}

/*
=============
Load
=============
Try and load the font image and then build the font map.  Returns 0 if it
fails.  'row' and 'col' are optional variables.  
*/
bool font_t::Load(char *name, GLint row, GLint col)
{
	/*
	if (!name || row < 0 || col < 0)
		return 0;
	
	glTga_t img;
	
	img.GenId(1, &texId);
	
	if (img.Load(name, texId) != 1)
		return 0;
	
	img.Upload(1);
	
	if ((row && col) && (row * col) == 256)
		MakeFontMap(row, col);
	else
		MakeFontMap(fontBlockRow, fontBlockCol);
		*/
	return 1;
	
}

/*
=============
Draw
=============
Draws a string.  We setup the GL states and projection if needed and then 
render the string.  After the string has been drawn we undo all of the state
and projection changes if needed.  If letting the font code handle the
projection (0, 0) will be the lower left hand corner of the window and (w, h)
will be the upper right hand corner of the window.  
*/
void font_t::Draw(GLint xpos, GLint ypos, char *format, ...)
{
	va_list	msg;
	
	va_start(msg, format);
#ifdef _WIN32
	//_vsntprintf(buffer, maxLen, format, msg);	
	vsprintf(buffer, format, msg); // not safe
#else
	// linux
	vsnprintf(buffer, maxLen, format, msg);	
#endif
	va_end (msg);
	
	if (!modeMan)
		glState.GetStates();
	
	if (!projMan)
	{
		
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		
		if (!coordCustom)
		{
			GLint vPort[4];
			glGetIntegerv(GL_VIEWPORT, vPort);
			glOrtho(0, vPort[2], 0, vPort[3], -1, 1);
		}
		else
			glOrtho(coord.dim[0], coord.dim[1], coord.dim[2], coord.dim[3],
			-1, 1);
		
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
	}
	
	glBindTexture(GL_TEXTURE_2D, texid);
	WalkString(xpos, ypos, buffer);
	
	if (!projMan)
	{
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();   
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	}
	
	if (!modeMan)
		glState.SetStates();
	Reset();
}

/*
=============
WalkString
=============
Walks the passed string and either renders or changes some font state based
on what it encounters.  Makes sure that failed formatters don't break anything.
*/
void font_t::WalkString(GLint xpos, GLint ypos, char *string)
{
	GLint px = region ? regionDims[0] : xpos;
	GLint py = region ? regionDims[1] - (coord.up * m_Option->GetFontSize()) : ypos;
	
	for (char *where = string; *where; where++)
	{
		if (region)
		{
			// ugly mess
			if ((coord.right > 0 && (px + m_Option->GetFontSize()) > (regionDims[0] + regionDims[2]))
				|| (coord.right < 0 && (px - m_Option->GetFontSize()) < (regionDims[0] - regionDims[2])))
			{
				py -= (m_Option->GetFontSize() * coord.up);
				px = regionDims[0];
			}
			
			if (coord.up < 0 && py > (regionDims[1] + regionDims[3]) || 
				coord.up > 0 && py < (regionDims[1] - regionDims[3]))
				break;
		}
		
		if (*where == '\t')
			px += (m_Option->GetFontSize() * fontTabSize);
		else if (*where == '\n')
		{
			py -= (coord.up * m_Option->GetFontSize());
			px = region ? regionDims[0] : xpos;
		}
		else if (*where == '\\')
		{
			GLubyte clr[4];
			GLint format = FormatCheck(&where, clr);
			
			if (!format)
			{
				ProcessChar(px, py, *where);
				px += (coord.right * m_Option->GetFontSize());
			}
			else if (format == formatBoldOn)
				bold = 1;
			else if (format == formatBoldOff)
				bold = 0;
			else if (format == formatItalicOn)
				italic = 1;
			else if (format == formatItalicOff)
				italic = 0;
			else if (format == formatColor || format == formatColorA)
				ColorCopy(colorForGrnd, clr, 4);
		}
		else
		{
			ProcessChar(px, py, *where);
			px += (coord.right * m_Option->GetFontSize());
		}
	}
}

/*
=============
ProcessChar
=============
This function decides how many times a given character needs to be rendered.
If there is no shadow or bold the character is only rendered once.  
*/
void font_t::ProcessChar(GLint x, GLint y, char c)
{
	if (shadow)
	{
		if (!bold)
			DrawChar(x + (fontShadowShift * coord.right),
			y + (fontShadowShift * coord.up), c);
		else
			DrawChar(x + ((fontShadowShift + fontBoldShift) * coord.right),
			y + (fontShadowShift * coord.up), c);
	}
	
	GLboolean s = shadow;
	
	shadow = 0;
	
	DrawChar(x, y, c);
	
	if (bold)
		DrawChar(x + (fontBoldShift * coord.right), y, c);
	
	shadow = s ? 1 : 0;
}

/*
=============
DrawChar
=============
Draws a character.  Uses the integer value of the character to index in to
the font map.  Italic drawing is handled here as well, italic just offsets the 
top of the font character.  
*/
void font_t::DrawChar(GLint x, GLint y, char c)
{
	GLint ci = c;
	GLint ital = italic ? fontItalicShift : 0;
	
	glDisable(GL_DEPTH_TEST);
	if (m_Option->DrawFontBack())
	{
		glDisable(GL_BLEND);
		glColor3ub(m_Option->FontBackColor()->bBlue,m_Option->FontBackColor()->bGreen,m_Option->FontBackColor()->bRed);
		
		glBegin (GL_TRIANGLE_FAN);
		glVertex2i(x, y);
		
		glVertex2i(x + (m_Option->GetFontSize() * coord.right), y);
		
		glVertex2i(x + ((m_Option->GetFontSize() + ital) * coord.right), y + (m_Option->GetFontSize() * coord.up));
		
		glVertex2i(x + (ital * coord.right), y + (m_Option->GetFontSize() * coord.up));
		glEnd ();
		
		glEnable(GL_BLEND);
	}
	
	if (!gradient && !shadow)
		glColor4ubv(colorForGrnd);
	else if (!gradient && shadow)
		glColor4ubv(colorShadow);
	else if (gradient && !shadow)
		glColor4ubv(colorGrad);
	
	glBegin (GL_TRIANGLE_FAN);
	glTexCoord2f(tPoints[ci][0], tPoints[ci][1]+ tIncY);
	glVertex2i(x, y);
	
	glTexCoord2f(tPoints[ci][0] + tIncX, tPoints[ci][1]+ tIncY);
	glVertex2i(x + (m_Option->GetFontSize() * coord.right), y);
	
	if (!shadow)
		glColor4ubv(colorForGrnd);
	else 
		glColor4ubv(colorShadow);
	
	glTexCoord2f(tPoints[ci][0] + tIncX, tPoints[ci][1] );
	glVertex2i(x + ((m_Option->GetFontSize() + ital) * coord.right), y + (m_Option->GetFontSize() * coord.up));
	
	glTexCoord2f(tPoints[ci][0], tPoints[ci][1] );
	glVertex2i(x + (ital * coord.right), y + (m_Option->GetFontSize() * coord.up));
	glEnd ();
	
	
}

/*
=============
FormatCheck
=============
This is called when we hit a \ in the string.  It checks for \b+, \b-, \i+, 
\i-, \c(int int int) and \a(int int int int).  It is very picky about things so
if there is anything wrong with the passed string it will return 0, an error.  
If everything is parsed without problem it will return an enum from font.h that
represents what was just read in.  
*/
GLint font_t::FormatCheck(char **where, GLubyte *clr)
{
	if (**where != '\\')
		return 0;
	
	GLint res = 0;
	char *start = *where;
	char curr;
	
	if (!*++(*where))
	{
		*where = start;
		return 0;
	}
	
	curr = **where;
	
	if (curr == 'b' || curr == 'i')
	{
		GLboolean b = curr == 'b';
		res = IsToggle(where);
		
		if (res == toggleOn)
			return b ? formatBoldOn : formatItalicOn;
		else if (res == toggleOff)
			return b ? formatBoldOff : formatItalicOff;
	}
	else if ((curr == 'c' || curr == 'a') &&
		ParseColor(clr, where, curr == 'c' ? 3 : 4))
		return curr == 'c' ? formatColor : formatColorA;
	
	*where = start;
	
	return 0;
}

/*
=============
IsToggle
=============
Determins if we have a toggle character, + or -.  Returns an enum from
font.h if all is well and 0 otherwise.
*/
GLint font_t::IsToggle(char **where)
{  
	if (!*++(*where))
		return 0;
	if (**where == '+')
		return toggleOn;
	else if (**where == '-')
		return toggleOff;
	return 0;
}

/*
=============
ParseColor
=============
Parses a color out of the string.  It is very picky, one problem and
everything is considered wrong.  Scans (int int int) and (int int int int).
*/
GLboolean font_t::ParseColor(GLubyte *clr, char **where, GLint num)
{
	GLubyte temp[4] = {0, 0, 0, 255};
	
	if (!*++(*where) || *(*where)++ != '(')
		return 0;
	
	if (!**where)
		return 0;
	
	for (int i = 0; i < num - 1; i++)
	{   
		temp[i] = uClamp(LineReadInt(where), 0, 255);
		
		if (!**where || *(*where)++ != ' ')
			return 0;
	}
	
	temp[num - 1] = uClamp(LineReadInt(where), 0, 255);
	
	if (**where && **where == ')')
	{
		ColorCopy(clr, temp, 4);
		return 1;
	}
	
	return 0;
}

/*
=============
MakeFontMap
=============
Makes the font map that is used when rendering characters.
*/
void font_t::MakeFontMap(GLint row, GLint col)
{
	// assume 16x16
	double ax=0,ay=0.01f;
	int av=0;

	for (int i=0;i<16;i++)
	{
		for (int j=0;j<16;j++)
		{

			tPoints[av][0] = ax;
			tPoints[av][1] = ay;

			ax+=0.0625f;
			av++;
		}
		ax=0;
		ay+=0.0625f;
		

	}
	tIncX=0.0625f;
	tIncY=0.0625f;
	/*
	GLint i = 0;
	GLfloat x, y;
	
	tIncX = (GLfloat)pow(col, -1);
	tIncY = (GLfloat)pow(row, -1);
	
	for (y = 1 - tIncY; y >= 0; y -= tIncY)
	{
		for (x = 0; x <= 1 - tIncX; x += tIncX, i++)
		{
			
		}
	}
	*/
}

/*
=============
GetStates
=============
Gets the states we change from OpenGL so we can restore them.
*/
void font_t::fontGLRenderState_t::GetStates(void)
{
	textureOn = glIsEnabled(GL_TEXTURE_2D);
	
	if (!textureOn)
		glEnable(GL_TEXTURE_2D);
	
	depthOn = glIsEnabled(GL_DEPTH_TEST);
	/*
	if (depthOn)
	glDisable(GL_DEPTH_TEST);
	*/
	lightingOn = glIsEnabled(GL_LIGHTING);
	
	if (lightingOn) 
		glDisable(GL_LIGHTING);
	
	scissorOn= glIsEnabled(GL_SCISSOR_TEST);        
	
	if (!scissorOn) 
		glEnable(GL_SCISSOR_TEST);
	
	glGetIntegerv(GL_MATRIX_MODE, &matrixMode); 
	
	blendOn= glIsEnabled(GL_BLEND);        
	glGetIntegerv(GL_BLEND_SRC, &blendSrc);
	glGetIntegerv(GL_BLEND_DST, &blendDst);
	
	if (!blendOn)
		glEnable(GL_BLEND);
	
	glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
}

/*
=============
SetStates
=============
Restores the states we changed.
*/
void font_t::fontGLRenderState_t::SetStates(void)
{
	if (lightingOn)
		glEnable(GL_LIGHTING);
	
	if (!blendOn)
	{
		glDisable(GL_BLEND);
		glBlendFunc(blendSrc, blendDst);
	}
	else
		glBlendFunc(blendSrc, blendDst);
		/*
		if (depthOn);
		glEnable(GL_DEPTH_TEST);
	*/
	if (!textureOn)
		glDisable(GL_TEXTURE_2D);
	
	if (!scissorOn) 
		glDisable(GL_SCISSOR_TEST);
	
	glMatrixMode(matrixMode);
}