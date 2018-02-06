
// classe permettant de splitter un nom de fichier
// en composants (semblable à _splitpath)


class CSplitPath
{
  char drive[_MAX_DRIVE];
  char dir[_MAX_DIR];
  char fname[_MAX_FNAME];
  char ext[_MAX_EXT];

public:
  CSplitPath (const char *path) ;
  CSplitPath () ;
  ~CSplitPath () ;
  
  const char *getdrive () ;
  const char *getdir () ;
  const char *getname () ;  
  const char *getextension () ;
  
  const char *getpath () ;
} ;

