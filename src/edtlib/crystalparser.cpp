////////////////////////////////////////////////////////////////////////////
//	File:		CrystalParser.cpp
//
//	Author:		Sven Wiegand
//	E-mail:		sven.wiegand@gmx.de
//
//	Implementation of the CCrystalParser class, a part of Crystal Edit -
//	syntax coloring text editor.
//
//	You are free to use or modify this code to the following restrictions:
//	- Acknowledge me somewhere in your about box, simple "Parts of code by.."
//	will be enough. If you can't (or don't want to), contact me personally.
//	- LEAVE THIS HEADER INTACT
////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CrystalParser.h"
#include "ccrystaltextview.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC( CCrystalParser, CObject )

CCrystalParser::CCrystalParser()
{
	m_pTextView = NULL;
}


CCrystalParser::~CCrystalParser()
{
}


DWORD CCrystalParser::ParseLine(
											DWORD dwCookie, int nLineIndex, CCrystalTextBlock *pBlock )
{
	return 0;
}


void CCrystalParser::WrapLine( int nLineIndex, int nMaxLineWidth, int *anBreaks, int &nBreaks )
{
	// The parser must be attached to a view!
	ASSERT( m_pTextView );

	int			nLineLength = m_pTextView->GetLineLength( nLineIndex );
	int			nTabWidth = m_pTextView->GetTabSize();
	int			nLineCharCount = 0;
	int			nCharCount = 0;
	LPCTSTR	szLine = m_pTextView->GetLineChars( nLineIndex );
	int			nLastBreakPos = 0;
	int			nLastCharBreakPos = 0;
	BOOL		bWhitespace = FALSE;

	for( int i = 0; i < nLineLength; i++ )
	{
		// remember position of whitespace for wrap
		if( bWhitespace )
		{
			nLastBreakPos = i;
			nLastCharBreakPos = nCharCount;
			bWhitespace = FALSE;
		}

		// increment char counter (evtl. expand tab)
		if( szLine[i] == _T('\t') )
		{
			nLineCharCount+= (nTabWidth - nCharCount % nTabWidth);
			nCharCount+= (nTabWidth - nCharCount % nTabWidth);
		}
		else
		{
			nLineCharCount++;
			nCharCount++;
		}

		// remember whitespace
		if( szLine[i] == _T('\t') || szLine[i] == _T(' ') )
			bWhitespace = TRUE;

		// wrap line
		if( nLineCharCount >= nMaxLineWidth )
		{
			if( anBreaks )
			{
				// if no wrap position found, but line is to wide, 
				// wrap at current position
				if( (nBreaks && nLastBreakPos == anBreaks[nBreaks - 1]) || (!nBreaks && !nLastBreakPos) )
				{
					nLastBreakPos = i;
					nLastCharBreakPos = nCharCount;
				}

				anBreaks[nBreaks++] = nLastBreakPos;
			}
			else
				nBreaks++;

			nLineCharCount = nCharCount - nLastCharBreakPos;
		}
	}
}
