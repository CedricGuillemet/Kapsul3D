// stdafx.cpp : source file that includes just the standard includes
//	Sample.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"


int
xisspecial (int c)
{
  return (unsigned) c > (unsigned) _T ('\x7f') || c == _T ('_');
//  return _tcschr (_T ("ØçŸı§ì ¡‚¢£…Ôœå–ê’˜„‰”·æ¬ü¦íµÖïOéŞÒ›Õ•è‘—Ó™šõ"), c) != NULL;
}

int
xisalpha (int c)
{
  return _istalpha (c) || xisspecial (c);
}

int
xisalnum (int c)
{
  return _istalnum (c) || xisspecial (c);
}
