// KIrc.h: interface for the CKIrc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KIRC_H__B2E67F74_3591_47DA_B7B7_0E21597AFC2F__INCLUDED_)
#define AFX_KIRC_H__B2E67F74_3591_47DA_B7B7_0E21597AFC2F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define IRC_SCREEN_X 60
#define IRC_SCREEN_Y 45
#include "ircUBImport.h"

class CKIrcClient : public CUB_ircClient
{
public:
	void *Parent;
	void Print (ubChar *cFunction, ubChar *cText, ...);

};

class CKIrc  
{
public:
	CKIrc();
	virtual ~CKIrc();



	// IRC

	CUB_LogFile			 LogFile;
	CKIrcClient 		 Client;
	CUB_ircClientInfo	 clientInfo;
	CUB_ircClientMessage clientMessage;
	ubChar				cChannel        [CUB_IRC_MAX_CHANNEL];

	// properties
	CString	m_cNickName;
	CString	m_cAltNameName;
	CString	m_cPassword;
	CString	m_cRealName;
	CString	m_cCurrentChannel;
	CString  m_cIdentName;
	int	m_iIdentServerPort;
	bool	m_bUseIdentServer;

	CString m_Name;
	Vertex Pos;

	font_t *font;
	int CursorX,CursorY;
	bool Connected;

	// methods
	void Init(void);
	void Close(void);
	void UpdateIRC();
	void Draw(int daState,int WichOne);
	
	char ScreenChars[IRC_SCREEN_Y][IRC_SCREEN_X];
	void Print(char *format, ...);
	void Scroll(int nbLines);



};

#endif // !defined(AFX_KIRC_H__B2E67F74_3591_47DA_B7B7_0E21597AFC2F__INCLUDED_)
