#include <util.h>
#include <fstream.h>
//#include <stdio.h>
//#include <conio.h>
//#include <process.h>

#include <GL/gl.h>

#include <string>

using std::string;


#include <windows.h>


void showError(const char* message) {

  MessageBox( NULL, message, "Error", MB_OK | MB_ICONEXCLAMATION );
}


void showWarning(const char* message) {

  MessageBox( NULL, message, "Warning", MB_OK | MB_ICONEXCLAMATION );
}

void showInfo(const char* message) {

  MessageBox( NULL, message, "Information", MB_OK | MB_ICONINFORMATION );
  
}

void writeInfo(const char* message) {
	ofstream ofile("results.txt");
    ofile.write(message, 200);
    ofile.close();
}


void showLastError(const char* m) {

	LPVOID lpMsgBuf;
	FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | 
				   FORMAT_MESSAGE_FROM_SYSTEM |
				   FORMAT_MESSAGE_IGNORE_INSERTS,
				   NULL,
				   GetLastError(),
				   MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
				   (LPTSTR) &lpMsgBuf,
				   0,
				   NULL );

	string message(m);
	message.append((LPCTSTR)lpMsgBuf);
	LocalFree( lpMsgBuf );
	showError(message.c_str());
}

void showLastWarning(const char* m) {

	LPVOID lpMsgBuf;
	FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | 
				   FORMAT_MESSAGE_FROM_SYSTEM |
				   FORMAT_MESSAGE_IGNORE_INSERTS,
				   NULL,
				   GetLastError(),
				   MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
				   (LPTSTR) &lpMsgBuf,
				   0,
				   NULL );

	string message(m);
	message.append((LPCTSTR)lpMsgBuf);
	LocalFree( lpMsgBuf );
	showLastWarning(message.c_str());
}


void checkGLError(const char* m) {

  string message(m);

  switch(glGetError()) {

  case GL_NO_ERROR:
    return;

  case GL_INVALID_ENUM:
    message.append(": invalid enum");
    showWarning(message.c_str());
    break;

  case GL_INVALID_VALUE:
    message.append(": invalid value");
    showWarning(message.c_str());
    break;

  case GL_INVALID_OPERATION:
    message.append(": invalid operation");
    showWarning(message.c_str());
    break;

  case GL_STACK_OVERFLOW:
    message.append(": stack overflow");
    showWarning(message.c_str());
    break;

  case GL_STACK_UNDERFLOW:
    message.append(": stack underflow");
    showWarning(message.c_str());
    break;

  case GL_OUT_OF_MEMORY:
    message.append(": out of memory");
    showWarning(message.c_str());
    break;
  }

}


