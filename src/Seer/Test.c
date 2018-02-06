/************************************************************************
       -= SEER - C-Scripting engine v 0.92a =-
State      : under implementation
Author     : Przemyslaw Podsiadly
             email: ppodsiad@elka.pw.edu.pl
             WWW:   http://home.elka.pw.edu.pl/~ppodsiad
File:test.c
Desc:testing program
************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "seer.h"
#include <math.h>
#include <time.h>

//#define PROFILE_SEER
scInstance *otherScript=NULL;

typedef int fixed;

//script imports these:
char varchar=12;
int varint=13;
float varfloat=(float)14.2;
double vardouble=15.5;
char chartable[10]="Karol";
char *charptr="Ludwik";
int table[10]={1,2,3,4,5,6,7,8,9,10};
int *tableptr=table;
struct {
       int a;
       float b;
       double c;
       char d1 ,d2;
       struct {int x,y;} inside;
       char name[10];
       } structure
       =
       {1,2.0,3.0,64,65,{1,2},"Jan"};

struct Class{
       int m;
       int a;
};

struct Struct1b{char a;
};

struct Struct2b{short a;
};

struct Struct4b{int a;
};

struct Struct8b{int a,b;
};

struct Struct1b retStruct1b(int a)
{struct Struct1b b;b.a=a;return b;}

struct Struct2b retStruct2b(int a)
{struct Struct2b b;b.a=a;return b;}

struct Struct4b retStruct4b(int a)
{struct Struct4b b;b.a=a;return b;}

struct Struct8b retStruct8b(int a,int a2)
{struct Struct8b b;b.a=a;b.b=a2;return b;}

int Class_Imp(struct Class *_this,int z)
{return _this->m+z;
}


double doublefunc(int a,double b,float c,fixed d)
{
 return 1.0*a+b+c+d/65536.0;
}

void MyDispatcher
(int *result,void *function,int *params,int paramcount,unsigned int options)
{
  if (options&scDispatch_Member)
  {//C++ call - convert to typical C call, so 'this' is the first param.
        options^=scDispatch_Member;
  }
  scStandardDispatcher(result,function,params,paramcount,options);
}

bool getScript(scScriptTypeHeader *script,char *typeinfo)
{
 return scAssignInstance(script,otherScript,typeinfo);
}

void Init()
{
//************************ Special *************************
 scAddExtSym(table);
 scAddExtSym(tableptr);
 scAddExtSym(chartable);
 scAddExtSym(charptr);
 scAddExtSym(doublefunc);
 scAddExtSym(structure);
 scAddExtSym(varchar);
 scAddExtSym(varint);
 scAddExtSym(vardouble);
 scAddExtSym(varfloat);
 scAddExtSym(retStruct1b);
 scAddExtSym(retStruct2b);
 scAddExtSym(retStruct4b);
 scAddExtSym(retStruct8b);
 scAdd_External_Symbol("Class.Imp",Class_Imp);

 scAddExtSym(getScript);
//************************ STDIO ***************************
 scAdd_Internal_Header("stdio",
 "import int printf(char *,...);\n"
 "import int sprintf(char*,char *,...);\n"
 "import int scanf(char *,...);\n"
 "import int getchar();\n"
 "import int rand();\n"
 "import int srand(int seed);\n"
 "import int strcpy(char *,char *);\n"
 "import int strcmp(char *,char *);\n"
 "import int strtol(char *,char **,int);\n"
 "import int atoi(char *);\n"
 "import double atof(char *);\n"
 "import unsigned int strtoul(char *,char **,int);\n"
 "import double strtod(char *,char **);\n"
 "import char *strdup(char *);\n"
 "import double sqrt(double);\n"
 "import double sin(double);\n"
 "import double cos(double);\n"
 "import void* malloc(int);\n"
 "import void free(void *);\n"
 );
 scAddExtSym(printf);
 scAddExtSym(sprintf);
 scAddExtSym(rand);
 scAddExtSym(srand);
 scAddExtSym(scanf);
 scAddExtSym(getchar);
 scAddExtSym(strcpy);
 scAddExtSym(strcmp);
 scAddExtSym(strdup);
 scAddExtSym(strtoul);
 scAddExtSym(strtol);
 scAddExtSym(strtod);
 scAddExtSym(atoi);
 scAddExtSym(atof);
 scAddExtSym(sqrt);
 scAddExtSym(sin);
 scAddExtSym(cos);
 scAddExtSym(malloc);
 scAddExtSym(free);

 scSeeR_Set(scSeeR_Dispatcher,1,MyDispatcher);
}

int benchmark(scInstance *in)
{int i;
 int f;
 for(i=0;i<6000000;++i)
  {f=10*--i%13;++i;f>>=2;}
 return i;
}

int SeeRBenchmark(scInstance *in)
{
 return scCall_Instance(in,scGet_Symbol(in,"benchmark"),1);
}

int CompileBenchmark(void *none)
{scScript sc;
 scProgressCallback=NULL;
 sc=scCompile_File("test.sc");
 if (!sc) return -1;
 free(sc);
 return scSeeR_Get(scSeeR_LinesCompiled);
}

int bench(void *in,int (*f)(),char *s,char *unit)
{
#ifdef PROFILE_SEER
     uclock_t t1,t2;
     int i,j;
     printf("Benchmarking `%s' ...",s);fflush(stdout);
     t1=uclock();
     i=(*f)(in);
     t2=uclock();
     if (i<0) {printf("\rError occurred while benchmarking!\n");return -1;}
     if (!scErrorNo)
     {
      if (t2<t1) printf("\rClock overflow?    \n");
      t2-=t1;
      j=(int)((uclock_t)(UCLOCKS_PER_SEC)*i/t2);
      printf("\r%s benchmark(%d/%.2fs)\t: %8d %s/s\n",
         s,i,t2*1.0/UCLOCKS_PER_SEC,j,unit);
      return j;
     }
     return -1;
#else
         printf("Benchmarking not enabled.\n");fflush(stdout);
         return 1;
#endif
}

void test(scScript sc)
{scInstance *in;
 in=scCreate_Instance(sc,"");
 if (in)
 {int i;
  otherScript=scCreate_Instance(sc,"");
  if (!otherScript)
    printf("Unable to create the second instance!\nThe script calls in script may not work!\n");
  //here I assume otherscript is OK

//  printf(" member '%s' at %d\n","ex_inc",scGet_Symbol(in,"ex_inc"));

  i=scCall_Instance(in,scGet_Symbol(in,"main"));

  if (i)
    {
     printf("\n%d error%s encountered!\n",i,(i>1)?"s":"");
    }
    else
    {
     if (!scErrorNo) printf("\nAll seems OK!\n");
    }
 }

 if (!scErrorNo)
    {
#ifdef PROFILE_SEER
     int i1,i2;
     if (scSeeR_Get(scSeeR_Build)==scSeeR_Build_Debug)
     {
      printf("SeeR Debug build detected. Closing debug file for benchmarking. \n"
             "WARNING: Debug-SeeR works slower then release (result will be inaccurate).\n\n");
      scClose_Debug();
     }
     i1=bench(in,&benchmark,"CPU","loops");
     i2=bench(in,&SeeRBenchmark,"SeeR","loops");
     printf(" (so SeeR is %.1f times slower :-( )\n",i1*1.0/i2);
     bench(NULL,&CompileBenchmark,"Compiler","lines");
#endif
    }
 if (scErrorNo)
    printf("Runtime error :\n%s\n",scErrorMsg);
 scFree_Instance(in);
 if (otherScript) scFree_Instance(otherScript);
}

/* function to be called during compilation to display progress bar */
int progresscallback(int percent)
{int i;
 static int per=-1;
 percent/=5;
 if (per==percent) return 1;//don't repeat yourself
 per=percent;
 printf("\r|");
 for (i=0;i<percent;i++) printf("*");
 for (;i<100/5;i++) printf(".");
 printf("|");fflush(stdout);
 return 1;
}

/******************************************************************/
int main()
{FILE *file;
 scScript scrpt;
 scOpen_Debug("a.out");

// scSeeR_Set(scSeeR_ExprOpcode,0);//that's default

 printf("**********SeeR v.%s****(%s)**********************\n",SeeR_VERSION_STR,SeeR_DATE_STR);
 printf("Compiling...");fflush(stdout);

 Init();

 scProgressCallback=progresscallback;
 scrpt=scCompile_File("test.sc");
 if (!scrpt)
  {printf("Error during compilation:\n%s\nIn line:%s\n",scErrorMsg,scErrorLine);
   exit(scErrorNo);
  }

 printf("\rCompiled successfully.\n");

 file=fopen("test.cs","wb");
 fwrite(scrpt,scGet_Script_Size(scrpt),1,file);
 fclose(file);
 printf("Written as test.cs\n\n");

 test(scrpt);
 printf("End of %s (press enter).\n",scGet_Title(scrpt));
 free(scrpt);
 getchar();
 return 0;
}

