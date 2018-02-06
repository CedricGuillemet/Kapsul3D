// KIrc.cpp: implementation of the CKIrc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ircUBImport.h"
#include "Entity.h"
#include "KIrc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
// ScreenChars[IRC_SCREEN_Y][IRC_SCREEN_X]


void CKIrcClient::Print (ubChar *cFunction, ubChar *cText, ...)
{
	ubChar cBuffer  [CUB_IRC_MAX_BUFFER];
	
	// Pure virtual function, override this!

	// Combine the args with the string
	va_list args;
	va_start (args, cText);
	vsprintf (cBuffer, cText, args);
	va_end   (args);
	((CKIrc*)Parent)->Print (cBuffer);
}

CKIrc::CKIrc()
{
	
	font=new font_t;
	memset(ScreenChars,0,IRC_SCREEN_Y*IRC_SCREEN_X);
	CursorX=0;
	CursorY=IRC_SCREEN_Y-1;
	int i,j;

	for (i=0;i<IRC_SCREEN_Y;i++)
	{
		for (j=0;j<IRC_SCREEN_X;j++)
		{
			ScreenChars[i][j]=0;//'a'+(rand()&15);
		}
	}
	Connected=false;
	Client.Parent=this;
}

CKIrc::~CKIrc()
{

}
void CKIrc::Scroll(int nbLines)
{
	/*
	char *Start=&ScreenChars[nbLines][0];
	int ToTrans=(IRC_SCREEN_Y-nbLines)*IRC_SCREEN_X;
	memcpy(ScreenChars,Start,ToTrans);
	Start=&ScreenChars[IRC_SCREEN_Y-nbLines][0];
	memset(Start,0,nbLines*IRC_SCREEN_X);
	*/

	//char *Start=&ScreenChars[1][0];
	//int ToTrans=(IRC_SCREEN_Y-nbLines)*IRC_SCREEN_X;
	memcpy(&ScreenChars[0][0],&ScreenChars[1][0],(IRC_SCREEN_Y-1)*IRC_SCREEN_X);
	//Start=&ScreenChars[IRC_SCREEN_Y-nbLines][0];
	memset(&ScreenChars[(IRC_SCREEN_Y-1)][0],0,IRC_SCREEN_X);

}

void CKIrc::Print(char *format, ...)
{
	char buffer[1024];
	CString temp;

	va_list	msg;

	va_start(msg, format);
	vsprintf((char*)buffer, format, msg);

	//CursorX=0;
	for (int i=0;i<strlen(buffer);i++)
	{
		if (buffer[i]=='\n')
		{
			Scroll(1);
			CursorX=0;
		}
		else
		{
			ScreenChars[IRC_SCREEN_Y-1][CursorX]=buffer[i];
			CursorX++;
			if (CursorX==IRC_SCREEN_X)
			{	
				Scroll(1);
				CursorX=0;

			}
		}
	}
}

void CKIrc::Init(void)
{
	if (Connected) return;//Close();

	sprintf (clientInfo.m_cNickName,    "lacraple");
	sprintf (clientInfo.m_cAltNameName, "lacrapleX");
	sprintf (clientInfo.m_cPassword,    "");
	sprintf (clientInfo.m_cRealName,    "Ircub - United Bytes");

	// NEW: Ident server information
	sprintf (clientInfo.m_cIdentName,   "IrcubTest");
	clientInfo.m_bUseIdentServer = ubFalse;
	clientInfo.m_iIdentServerPort = 113;

	// NEW: Channel for chatting
	sprintf (cChannel, "#kapsul");

	// Set the logfile
	LogFile.CreateLogFile ("ConsoleTestLog.txt");
	LogFile.SetLogging (ubFalse);
	
	// Add log file to client
	Client.SetLogFile (&LogFile);

	// Initialize socket system (this is needed on several platform, .e.g. Windows)
	Client.InitSocketSystem ();

	printf ("Connecting to IRC...");

	// Connect to irc.quakenet.eu.org (62.79.27.110, port 6667)
	if (!Client.ConnectToIRC ("irc.voila.fr", 6667, &clientInfo))
	{
		// Something went wrong :(
		Print ("ERROR: Something went wrong!\n");
		Connected=false;
	}
	else 
	{
		Print ("DONE.\n");
		Connected=true;
	}
}

void CKIrc::Close(void)
{
	// Close Ircub
	Client.Shutdown ();

	// Shutdown socket system
	Client.ShutdownSocketSystem ();
	
	Connected=false;
}

void CKIrc::UpdateIRC()
{
}
int Test=0,Test2=0;

void CKIrc::Draw(int daState,int WichOne)
{
	int i,j;
	int SizeChar=4;
/*
	if (Test==100)
	{
		Print("Cedric -> %d ",Test2);
		Print(" Now feedback\n");
		Test=0;
		Test2++;
	}
	*/
	Init();

	Client.MessageManager ();

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, font->texid);

		for (i=0;i<IRC_SCREEN_Y;i++)
		{
			for (j=0;j<IRC_SCREEN_X;j++)
			{
				BYTE ci=ScreenChars[i][j];
				float x=j*SizeChar;
				float y=(IRC_SCREEN_Y-1-i)*SizeChar;

				glColor4f(1,1,1,1);
				glBegin (GL_TRIANGLE_FAN);
				glTexCoord2f(font->tPoints[ci][0], font->tPoints[ci][1]+ font->tIncY+0.01f);
				glVertex3f(x,0, y);
			
				glTexCoord2f(font->tPoints[ci][0] + font->tIncX, font->tPoints[ci][1]+ font->tIncY+0.01f);
				glVertex3f(x + SizeChar,0, y);
				

				glTexCoord2f(font->tPoints[ci][0] + font->tIncX, font->tPoints[ci][1]+0.01f );
				glVertex3f(x + SizeChar,0, y + SizeChar);
				
				glTexCoord2f(font->tPoints[ci][0], font->tPoints[ci][1]+0.01f );
				glVertex3f(x ,0,y + SizeChar);
				glEnd ();
			}
		}
		glDisable(GL_TEXTURE_2D);

	
	Test++;
	
}
