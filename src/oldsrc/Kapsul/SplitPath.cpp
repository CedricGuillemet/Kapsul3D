
// Simple C++ _splitpath wrapper
                 
#include "stdafx.h"                  
#include <io.h>

//#include "memmgr/mmgr.h"

#include "splitpath.h"


CSplitPath::CSplitPath (const char *path)
{
  _splitpath( path, drive, dir, fname, ext );

}

CSplitPath::~CSplitPath ()
{

}

const char *CSplitPath::getdrive()
{
  return drive ;
}


const char *CSplitPath::getname()
{
  return fname ;
}


const char *CSplitPath::getdir()
{
  return dir ;
}

const char *CSplitPath::getextension()
{
  return ext ;
}
