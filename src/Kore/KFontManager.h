/* 
  FontManager.h: interface for the CKFontManager class.
  Description  : well, works in this simple way. Depending on
				 which OS you are using. you have define WIN32
				 or LINUX as follows.

					On Win32 Platforms:
						#define WIN32 
					On Linux Platforms:
						#define LINUX
*/
#if !defined(AFX_FONTMANAGER_H__155535F9_05AE_40A5_B65B_08A31E4A6B2D__INCLUDED_)
#define AFX_FONTMANAGER_H__155535F9_05AE_40A5_B65B_08A31E4A6B2D__INCLUDED_

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

// -> In the line that follow you have to define the OS.
#ifndef WIN32
#define WIN32
#endif
// -> End OS definition.

typedef enum 
{
 MODE_256_256 = 0,
 MODE_512_512,
 MODE_1024_1024
}Enum_FontMode;

class KAPSUL_DESC CKFontManager  
{
public:
	CKFontManager();
	~CKFontManager();

	// Init/Cleanup
	bool Initialize();					//Called on initialization
	void CleanUp();						//Kills mem
	void Clear();						//NULL vars

	// Font managing
	int  AddFont(const char *szFontFile);							//Loads a font in memory
	void RemoveFont(const int iIndex);								//Removes a font from memory
	void SetFontSize(const int iIndex,Enum_FontMode iMode);			//Sets font size
	void *Render(const int iIndex,Enum_FontMode iMode,void *pData); //Renders font to a bitmap
	bool RenderChar(const int iIndex,char c,Enum_FontMode iMode,BYTE *dest,UINT Delta);
	bool Render(const int iIndex,Enum_FontMode iMode,BYTE *dest);

	// Errors 
	void GetLastError(char *Buffer);	//Gets latest's error message string 

private:
	FT_Error	 m_fntError;			//Keeps track of errors 
	unsigned int m_iNumFonts;			//Loaded fonts count
	FT_Library	 m_fntLibrary;			//Our library
	FT_Face 	 *m_FaceArray;			//Font indexed array

#if defined(WIN32) 
	void *Win32_RenderFunc(HWND hWnd,const int iIndex,Enum_FontMode iMode);
#endif

#if defined(LINUX)
	void *Linux_RenderFunc();
#endif
};

#endif // !defined(AFX_FONTMANAGER_H__155535F9_05AE_40A5_B65B_08A31E4A6B2D__INCLUDED_)
