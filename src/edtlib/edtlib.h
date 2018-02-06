#ifndef __EDTLIB_H
#define __EDTLIB_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifdef _AFXDLL
	#ifdef _DEBUG
		#ifdef _UNICODE
			#pragma comment(lib,"edtlibud.lib") 
			#pragma message("Automatically linking with edtlibud.dll")
		#else
			#pragma comment(lib,"edtlibd.lib") 
			#pragma message("Automatically linking with edtlibd.dll")
		#endif
	#else
		#ifdef _UNICODE
			#pragma comment(lib,"edtlibu.lib") 
			#pragma message("Automatically linking with edtlibu.dll") 
		#else
			#pragma comment(lib,"edtlib.lib") 
			#pragma message("Automatically linking with edtlib.dll") 
		#endif
	#endif
#else
	#ifdef _DEBUG
		#ifdef _UNICODE
			#pragma comment(lib,"edtlibsud.lib") 
			#pragma message("Automatically linking with edtlibsud.lib") 
		#else
			#pragma comment(lib,"edtlibsd.lib") 
			#pragma message("Automatically linking with edtlibsd.lib") 
		#endif
	#else
		#ifdef _UNICODE
			#pragma comment(lib,"edtlibsu.lib") 
			#pragma message("Automatically linking with edtlibsu.lib") 
		#else
			#pragma comment(lib,"edtlibs.lib") 
			#pragma message("Automatically linking with edtlibs.lib") 
		#endif
	#endif
#endif

#endif // __EDTLIB_H
