// FontManager.cpp: implementation of the CKFontManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
/*
#include "FontManager.h"
#include <//assert.h>
*/
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*#define charArraySize 3

static char charArray[] =
{
 'a','b','c'
};*/

CKFontManager::CKFontManager()
{

}

CKFontManager::~CKFontManager()
{

}

/* Func Name:	Initialize()
   Return Val.: TRUE/FALSE
   Argumets:	NONE
   Description:	Loads the library, initialzes it & clear vars.
*/
bool CKFontManager::Initialize()
{
 Clear();

 m_fntError = FT_Init_FreeType(&m_fntLibrary);
 if(m_fntError)
 {
  return false;
 }

 return true;	
}

/* Func Name:	CleanUp()
   Return Val.: NONE
   Argumets:	NONE
   Description: Frees memory
*/		
void CKFontManager::CleanUp()
{
 unsigned int j = m_iNumFonts;

 for(unsigned int k = 0; k < j; k++)
	RemoveFont(k);

 if(m_fntLibrary)
	m_fntError = FT_Done_FreeType(m_fntLibrary);

 Clear();
}


/* Func Name:	Clear()
   Return Value:NONE
   Argumets:	NONE
   Description: Set every var to NULL
*/
void CKFontManager::Clear()
{
 m_fntError   = NULL;	
 m_iNumFonts  = 0;
 m_fntLibrary = NULL;
 m_FaceArray  = NULL;
}

/* Func Name:   AddFont(const char *szFontFile)
   Return Value:an integer depending on error
   Argumets:    font string
   Description: Appends the created font instance to the internal array
*/
int CKFontManager::AddFont(const char *szFontFile)
{
 //assert(szFontFile);

 // Allocate memory for the new element
 if(m_iNumFonts == 0)
 {
  m_FaceArray = new FT_Face;
 }

 if(!m_FaceArray[m_iNumFonts])
	 return FT_Err_Out_Of_Memory;

 m_fntError = FT_New_Face(m_fntLibrary,szFontFile,0,&m_FaceArray[m_iNumFonts]);
 if(m_fntError != 0)
 {
	 free(m_FaceArray[m_iNumFonts]);
	 return m_fntError;
 }

 // Increase font count
 m_iNumFonts++;
 
 return 0;
}

/* Func Name:   RemoveFont(const int iIndex)
   Return Value:NONE
   Argumets:    const int (index of the font to remove)
   Description: releases the memory allocated for the font at the 
				iIndex position of the array
*/
void CKFontManager::RemoveFont(const int iIndex)
{
 if(!m_FaceArray[iIndex])
	 return;

 m_fntError = FT_Done_Face(m_FaceArray[iIndex]);	
 if(m_fntError == 0)
	 m_iNumFonts--;

 m_FaceArray[iIndex] = NULL;
}

void CKFontManager::SetFontSize(const int iIndex,Enum_FontMode iMode)
{
 if(!m_FaceArray[iIndex])
	 return;

 switch(iMode)
 {
 case MODE_256_256:
	 m_fntError = FT_Set_Pixel_Sizes(m_FaceArray[iIndex], 0 ,16); 
	 break;
 case MODE_512_512:
	 m_fntError = FT_Set_Pixel_Sizes(m_FaceArray[iIndex], 0 ,32); //FIXME?
	 break;
 case MODE_1024_1024:
	 m_fntError = FT_Set_Pixel_Sizes(m_FaceArray[iIndex], 0 ,64); 
	 break;
 }
}

/* Func Name:   Render(
   Return Value:NONE
   Argumets:	
   Description: Renders the charArray to a bitmap and 
*/
void *CKFontManager::Render(const int iIndex,Enum_FontMode iMode,void *pData)
{

#if defined(WIN32)
 return Win32_RenderFunc((HWND)&pData,iIndex,iMode);
#elif defined(LINUX)
 return Linux_RenderFunc();
#endif

 /* Should never reach this point */
 return NULL;
}

/* Func Name:   GetLastError(char *Buffer)
   Return Value:NONE
   Argumets:	char * (a buffer to hold error message string)
   Description: fills buffer with the latest error message string
*/
void CKFontManager::GetLastError(char *Buffer)
{
 //assert(Buffer);

 switch(m_fntError)
 {
 /*Freetype error codes*/
 case FT_Err_Ok: strcpy(Buffer,"No errors"); break;
 case FT_Err_Unknown_File_Format: strcpy(Buffer,"Unknown font file format"); break;

 /*Class custom errors*/ 
 case (FT_Err_Missing_Bbx_Field + 1): strcpy(Buffer,"Unable to create a generic bitmap"); break;

 default: strcpy(Buffer,"Unknown error code"); break;
 }
}

#if defined(WIN32)
void *CKFontManager::Win32_RenderFunc(HWND hWnd,const int iIndex,Enum_FontMode iMode)
{
 FT_Glyph			glyph;
 FT_Bitmap			*bitmap;
 BITMAPINFO			i;
 HBITMAP			hbmp;
 HDC				dc;
 int				pen_x = 0,pen_y = 0,spacer = 0;
 

 // -> We now initialize our bitmap
 ZeroMemory( &i.bmiHeader, sizeof(BITMAPINFOHEADER) );

 switch(iMode)
 {
 case MODE_256_256:
	  i.bmiHeader.biWidth = i.bmiHeader.biHeight = 256;
	  spacer = 16;
	  break;
 case MODE_512_512:
	  i.bmiHeader.biWidth = i.bmiHeader.biHeight = 512;
	  spacer = 32;
	  break;
 case MODE_1024_1024:
	  i.bmiHeader.biWidth = i.bmiHeader.biHeight = 1024;
	  spacer = 64;
	  break;
 }
 
 dc = CreateCompatibleDC(NULL);

 i.bmiHeader.biPlanes	= 1;
 i.bmiHeader.biBitCount = 16; 
 i.bmiHeader.biSize		= sizeof(BITMAPINFOHEADER);

 VOID *pvBits;
 hbmp = CreateDIBSection(dc,&i,DIB_RGB_COLORS,&pvBits,NULL,0);

 HBITMAP oldBmp = (HBITMAP)SelectObject(dc,hbmp);


 // -> We draw the charmap to the bitmap
 m_fntError = FT_Select_Charmap(m_FaceArray[iIndex],ft_encoding_unicode);

 int index = 0;
 for(int iChar = 0;iChar < 256;iChar++,index++)
 {
  m_fntError = FT_Load_Char(m_FaceArray[iIndex],iChar,FT_LOAD_DEFAULT);
  if(m_fntError != 0)
	continue;

  m_fntError = FT_Get_Glyph(m_FaceArray[iIndex]->glyph, &glyph);
  if(m_fntError != 0)
	continue;

  bitmap = NULL;
  if(glyph->format != ft_glyph_format_bitmap)
  {
   if(FT_Glyph_To_Bitmap(&glyph,ft_render_mode_normal,NULL,1)==0)
 	bitmap = &((FT_BitmapGlyph)glyph)->bitmap;

  }else
   bitmap = &((FT_BitmapGlyph)glyph)->bitmap;

  for(int j = 0;j < bitmap->rows;j++)
  {
	for(int k = 0; k < bitmap->width;k++)
	{
	 FT_BitmapGlyph pBmp = (FT_BitmapGlyph)glyph;
	 int iDrawX = pen_x + k + pBmp->left;
	 int iDrawY = pen_y + j - pBmp->top;

	 RECT rect = {iDrawX,iDrawY,iDrawX+1,iDrawY+1};

     if(bitmap->buffer[j*bitmap->width + k] != 0)
	  FillRect(dc, &rect, (HBRUSH) (WHITE_BRUSH));
	 /*else
	  FillRect(dc, &rect, (HBRUSH) (GRAY_BRUSH));*/

	}
  }
  
  FT_Done_Glyph(glyph); 

  pen_x += spacer;
  if(index == 16)
  {
   pen_y += spacer;
   pen_x = 0;
   index = 0;
  }
 }

 SelectObject(dc,oldBmp);
 //DeleteObject(hbmp);
 DeleteDC(dc);

 return hbmp;

 /*FT_Glyph	    glyph;
 FT_UInt		glyph_index;
 FT_Bitmap      *bitmap;
 
 FILE *p = fopen("c:\\test.txt","wt+");
 if(!p)
	 return NULL;

 fprintf(p,"Avaiable character maps:\n");

 for(int i = 0;i < m_FaceArray[iIndex]->num_charmaps;i++)
 {
      switch(m_FaceArray[iIndex]->charmaps[i]->encoding)
      {
        case ft_encoding_none:
          fprintf(p,"  ft_encoding_none\n");
          break;
        case ft_encoding_unicode:
          fprintf(p,"  ft_encoding_unicode\n");
          break;
        case ft_encoding_latin_1:
          fprintf(p,"  ft_encoding_latin_1\n");
          break;
        case ft_encoding_latin_2:
          fprintf(p,"  ft_encoding_latin_2\n");
          break;
        case ft_encoding_sjis:
          fprintf(p,"  ft_encoding_sjis\n");
          break;
        case ft_encoding_gb2312:
          fprintf(p,"  ft_encoding_gb2312\n");
          break;
        case ft_encoding_big5:
          fprintf(p,"  ft_encoding_big5\n");
          break;
        case ft_encoding_wansung:
          fprintf(p,"  ft_encoding_wansung\n");
          break;
        case ft_encoding_johab:
          fprintf(p,"  ft_encoding_johab\n");
          break;
        case ft_encoding_adobe_standard:
          fprintf(p,"  ft_encoding_adobe_standard\n");
          break;
        case ft_encoding_adobe_expert:
          fprintf(p,"  ft_encoding_adobe_expert\n");
          break;
        case ft_encoding_adobe_custom:
          fprintf(p,"  ft_encoding_adobe_custom\n");
          break;
        case ft_encoding_apple_roman:
          fprintf(p,"  ft_encoding_apple_roman\n");
          break;
      }
 }

 m_fntError = FT_Select_Charmap(m_FaceArray[iIndex],ft_encoding_unicode);
 if(m_fntError == 0)
	 fprintf(p,"\nUNICODE Char Map Selected");
 else
	 fprintf(p,"\nUnable to set unicode char map");

 for(int iChar = 0;iChar < 256;iChar++)
 {
  m_fntError = FT_Load_Char(m_FaceArray[iIndex],iChar,FT_LOAD_DEFAULT);
  if(m_fntError == 0)
	 fprintf(p,"\n%c Char Loaded",iChar);
  else
	 fprintf(p,"\nUnable to load character");

  m_fntError = FT_Get_Glyph(m_FaceArray[iIndex]->glyph, &glyph);
  if(m_fntError == 0)
	 fprintf(p,"\nGlyph loaded");
  else
	 fprintf(p,"\nUnable to load glyph");

  bitmap=NULL;
  if(glyph->format != ft_glyph_format_bitmap)
  {
   //convert to bitmap and destroy old bitmap
   if(FT_Glyph_To_Bitmap(&glyph,ft_render_mode_normal,NULL,1)==0)
 	bitmap = &((FT_BitmapGlyph)glyph)->bitmap;
   else
    fprintf(p,"cannot convert glyph %u in resource nb %d to bitmap\n",(unsigned char)'A',glyph_index);
  }else
   bitmap = &((FT_BitmapGlyph)glyph)->bitmap;

  fprintf(p,"\n");

  for(int j = 0;j < bitmap->rows;j++)
  {
	fprintf(p,"\n");
	for(int k = 0; k < bitmap->width;k++)
	{
     if(bitmap->buffer[j*bitmap->width + k] != 0)
		fprintf(p,"A");
	 else
		fprintf(p,"B");
	}
  }
  fprintf(p,"\n");
 }

 fclose(p);

 return NULL;*/
}
#endif

#if defined(LINUX) 
void *CKFontManager::Linux_RenderFunc()
{
 return NULL;
}

#endif

bool CKFontManager::Render(const int iIndex,Enum_FontMode iMode,BYTE *dest)
{
	int				pen_x = 0,pen_y = 0,spacer = 0,delta=0;

	
	switch(iMode)
	{
	case MODE_256_256:
		delta = 256*3;
		spacer = 16;
		break;
	case MODE_512_512:
		delta = 512*3;
		spacer = 32;
		break;
	case MODE_1024_1024:
		delta = 1024*3;
		spacer = 64;
		break;
	}
	
	int index = 0;
	

	for(int iChar = 0;iChar < 256;iChar++,index++)
	{
		BYTE *dst2=dest;
		dst2+=((iChar%16)*spacer*3);
		dst2+=((iChar>>4)*delta*spacer);

		RenderChar(iIndex,iChar,iMode,dst2,delta);
	}
	
	return true;
}

bool CKFontManager::RenderChar(const int iIndex,char c,Enum_FontMode iMode,BYTE *dest,UINT Delta)
{
	FT_Glyph			glyph;
	FT_Bitmap			*bitmap;
	int				pen_x = 0,pen_y = 0,spacer = 0;
	
	if (c<33) return true;

	// -> We draw the charmap to the bitmap
	m_fntError = FT_Select_Charmap(m_FaceArray[iIndex],ft_encoding_unicode);
	
	m_fntError = FT_Load_Char(m_FaceArray[iIndex],c,FT_LOAD_DEFAULT);
	/*
	if(m_fntError != 0)
		continue;
	*/
	m_fntError = FT_Get_Glyph(m_FaceArray[iIndex]->glyph, &glyph);
	/*
	if(m_fntError != 0)
		continue;
	*/	
	bitmap = NULL;
	if(glyph->format != ft_glyph_format_bitmap)
	{
		if(FT_Glyph_To_Bitmap(&glyph,ft_render_mode_normal,NULL,1)==0)
			bitmap = &((FT_BitmapGlyph)glyph)->bitmap;
		
	}
	else
		bitmap = &((FT_BitmapGlyph)glyph)->bitmap;
		

FT_BitmapGlyph pBmp = (FT_BitmapGlyph)glyph;
/*
			int iDrawX = k + pBmp->left;
			int iDrawY = j - pBmp->top;
*/

//FT_BitmapGlyph pBmp = (FT_BitmapGlyph)glyph;

	for(int j = 0;j < bitmap->rows;j++)
	{
		BYTE *dst2=dest;
		dst2+=((j)*3*512);
		//dst2+=pBmp->left*3;
		//if ((j-pBmp->top)>=0)
		for(int k = 0; k < bitmap->width;k++)
		{
			
			
			//RECT rect = {iDrawX,iDrawY,iDrawX+1,iDrawY+1};
			
			//if ((iDrawX>=0)&&(iDrawY>=0))
			//if ((iDrawX>=0)&&(iDrawY>=0))
			{
				//dst2+=((iDrawY*Delta)+(iDrawX*3));
				BYTE *dst3;
				dst3=dst2+(( 32-pBmp->top)*3*512);
/*
				int iDrawX = pen_x + k + pBmp->left;
				int iDrawY = pen_y + j - pBmp->top;
*/
				if(bitmap->buffer[j*bitmap->width + k] != 0)
				{
					*dst3++=0xff;
					*dst3++=0xff;
					*dst3++=0xff;
					
					//FillRect(dc, &rect, (HBRUSH) (WHITE_BRUSH));
				}
				/*
				else
				{
					*dst3++=0x0;
					*dst3++=0x0;
					*dst3++=0x0;
				}
				*/
				dst2+=3;
			}
			//dst2+=3;
		}
	}
	
	FT_Done_Glyph(glyph); 
		
	return true;
}

