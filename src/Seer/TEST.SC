#!bin/seer -r
/************************************************************************
       -= SEER - C-Scripting engine v 0.92a =-
State      : under implementation
Author     : Przemyslaw Podsiadly
             email: ppodsiad@elka.pw.edu.pl
             WWW:   http://home.elka.pw.edu.pl/~ppodsiad
File:test.sc
Desc:testing script
Here are many SeeR features you shouldn't use (like explicitly call
a constructor or operator). They are only to _test_ something, no
other purpose.
************************************************************************/
#ifdef SeeR
#title "Testing SeeR"
#author "Przemyslaw Podsiadly"

int first_variable;//to get DS, that points to this var.

#include stdio
#include stdlib

#define TEST_SCRIPTS

#else

/*
Can compile this file under another compiler (for result comparison)
Note: Should be compiled as C++ because of structs, member functions,
and struct-variable declaration...
*/

#include <stdio.h>
#define import
typedef int fixed;

#endif

/* CHECK PREPROCESSOR */
#define macro(x) be##x##d
int macro(love);        //should give 'beloved'

/* EXPORT */
#ifdef SeeR
export main;
export benchmark;
#endif

/* IMPORT */
import char varchar;
import int varint;
import char chartable[10];
import char *charptr;
import double vardouble;
import int table[10];
import int *tableptr;

struct insidetype{int x,y;};
struct structuretype{
       int a;
       float b;
       double c;
       char d1,d2;
       insidetype inside;
       char name[10];
       };
import structuretype structure;

#ifdef SeeR
import double doublefunc(int a,double b,float c,fixed d);
#else
double doublefunc(int a,double b,float c,fixed d)
{ return 1.0*a+b+c+d/65536.0;
}
#endif

/* SCRIPT itself */
int errornum=0,act_errornum=0;
void Error(int i,char *s="None")
{
 ++errornum;++act_errornum;
 printf(":%d<%s> ",i,s);
}

void start(char *s)
{printf("---%s---\n\t",s);
 act_errornum=0;
}

void subtest(char *s)
{printf("\r\t%s:\t",s);
 act_errornum=0;
}

#define TEST(i,v) if (!(v)) Error(i,#v);
void Sumarize()
{static int labi=0;
 static string Jaba="Sumarize :";
 labi++;
 Jaba+=labi;
 TEST(-1,labi!=8||Jaba=="Sumarize :12345678");//test of static vars
 if (act_errornum)
                   printf("\n(%2d)FAILED!\n",labi);
                   else
                   printf("\r(%2d)  +\n",labi);
}

void Test_Operators();
void Test_Initialization();
void Test_Importing();
void Test_Types();
void Test_Classes();

//idea:maybe also benchmark with double and float operations for comparison
int benchmark()
{int i;
 int f;
 for(i=0;i<100000;++i)
  {f=10*--i%13;++i;f>>=2;}
 return i;
}

/* THE MAIN */

int main()
{
#ifdef SeeR
 printf("Testing some features of SeeR v.%4.2f ...\n\n",SeeR/100.0);
#else
 printf("Testing for comparison with SeeR\n\n");
#endif
 Test_Types();
 Test_Operators();
 Test_Initialization();
#ifdef SeeR
//Won't ever work outside SeeR, though it'll compile
 Test_Importing();
#endif
 Test_Classes();
 return errornum;
}

/**********************************************************************/
struct struct1{
       int b;
       structuretype *s1;
       int a;
};
//     struct module{
//       int a,b,c,d;
//     };

typedef int module[4];

struct WINDOW {
        module *owner;
        int ordinal;
        int type;
        int flags;
        char *caption;
        int x;
        int y;
        int w;
        int h;
};

int ref_func1(int& x)
{ x+=1;
  return x;
}

int& ref_func2(int& x)
{ x+=2;
  return x;
}

struct retStruct1{short x,y;};
retStruct1 structFunc1(int a,int b)
{retStruct1 i;//={a,b};//causes an error-bug!
 i.x=a;i.y=b;
 return i;
}

struct retStruct2{int x,y;};
#ifdef SeeR
export structFunc2;
#endif
retStruct2 structFunc2(int a,int b)
{retStruct2 i;
 i.x=a;i.y=b;
 return i;
}

struct Struct1b{char a;};

struct Struct2b{short a;};

struct Struct4b{int a;};

struct Struct8b{int a,b;};

import Struct1b retStruct1b(int a);
import Struct2b retStruct2b(int a);
import Struct4b retStruct4b(int a);
import Struct8b retStruct8b(int a,int b);

void Test_Types()
{start("Type handling");
//STANDARD
 printf("standard");
 TEST(1,sizeof(char)==1);
 TEST(2,sizeof(short)==2);
 TEST(3,sizeof(int)==4);
 TEST(4,sizeof(float)==4);
 TEST(5,sizeof(double)==8);
//POINTER
 printf(",pointer");
 TEST(1,sizeof(int*)==4);
 TEST(2,sizeof(double*)==4);
 TEST(3,sizeof(int[10])==40);
 TEST(4,sizeof(short[5])==10);
 TEST(5,sizeof(double[2])==16);
 TEST(6,sizeof(WINDOW*)==4);
//STRUCT
 printf(",struct");
 TEST(1,sizeof(struct1)==12);
 TEST(2,sizeof(WINDOW)==9*4);
 TEST(3,sizeof(structure)==40);

 retStruct1 reS1;
 reS1.y=2;reS1.x=1;
 TEST(4,reS1.x==1);
 TEST(5,reS1.y==2);
 reS1=structFunc1(10,20);
 TEST(6,reS1.x==10);
 TEST(7,reS1.y==20);
 retStruct2 reS2;
 reS2.y=2;reS2.x=1;
 reS2=structFunc2(10,20);
// printf("<%d>\n",structFunc2(10,20).x);
 TEST(8,reS2.x==10);
 TEST(9,reS2.y==20);
 structuretype *ptrstr=&structure;
 structure.b=10.1;
 TEST(10,structure.b==(float)10.1);
 TEST(11,ptrstr->b==(float)10.1);
 ptrstr->b++; ptrstr->b+=1;
 TEST(11,ptrstr->b==(float)12.1);
 structure.b=2;//set previous value

 TEST(12,sizeof(Struct1b)==1);
 TEST(13,sizeof(Struct2b)==2);
 TEST(14,sizeof(Struct4b)==4);
 TEST(15,sizeof(Struct8b)==8);
 TEST(16,retStruct1b(2).a==2);
 TEST(17,retStruct2b(2).a==2);
 TEST(18,retStruct4b(2).a==2);
 TEST(19,retStruct8b(2,3).b==3);
//CASTING:
 printf(",casting");
 int i;
 structuretype *sptr;sptr=&structure;
 fixed y;
 y=(fixed)i;
 y=(fixed)structure.a;
// y=(fixed)(&structure)->a;
 y=(fixed)320;//sptr->a;
 y=((fixed)320-(fixed)sptr->a)/5;
//REFERENCE:
 printf(",reference");
 int &x=i;
 i=5;
 x=1;
 TEST(1,sizeof(WINDOW&)==sizeof(WINDOW));
 TEST(2,i==1);
 TEST(3,x==1);
 i=3;
 TEST(4,x==3);
 WINDOW win,&rwin=win;
 win.type=1;
 TEST(5,rwin.type==1);
 rwin.type=10;
 TEST(6,win.type==10);
 i=5;
 TEST(7,ref_func1(i)==6);
 TEST(8,ref_func1(i)==7);
 TEST(9,ref_func2(i)==9);
 TEST(10,i==9);
// TEST(11,ref_func1(structure.a)==2);
// structure.a=1;
 Sumarize();
}
/**********************************************************************/

void Test_Operators()
{start("Operators");
 subtest("arythmetic");
//INT:
 printf("int");
 int i1=4,i2=2,i3=10;
 i3=i1*i2+(++i3)+(i3++)+i3;
 TEST(1,i3==42);
 TEST(2,i3%10==2);
 TEST(3,~-1==0);
 TEST(4,~i3==-43);
//CHAR:
 printf(",char");
 char c1=4,c2=2,c3=10;
 c3=c1*c2+(++c3)+(c3++)+c3;
 TEST(1,c3==42);
 TEST(2,c3%10==2);
//SHORT:
 printf(",short");
 short s1=4,s2=2,s3=10;
 s3=s1*s2+(++s3)+(s3++)+s3;
 TEST(1,s3==42);
 TEST(2,s3%10==2);
//FIXED:
 printf(",fixed");
 fixed x1=4.0,x2=2.0,x3=10.0;
 x3=x1*x2+x3/x1-x3;
 TEST(1,x3==0.5);
//FLOAT:
 printf(",float");
 float f1=4.0,f2=2.0,f3=10.0;
 f3=f1*f2+f3/f1-f3;
 TEST(1,f3==0.5);
//DOUBLE
 printf(",double");
 double d1=4.0,d2=2.0,d3=10.0;
 d3=d1*d2+d3/d1-d3;
 TEST(1,d3==0.5);
//UNSIGNED - signed and unsigned differences check
 printf(",unsigned");

#define SIGNED(val,vl2,mark)   ((unsigned int)((int)val mark (int)vl2))
#define UNSIGNED(val,vl2,mark) ((unsigned int)((unsigned int)val mark (unsigned int)vl2))

 TEST(1,SIGNED(-1,2,<));
 TEST(2,!UNSIGNED(-1,2,<));
 TEST(3,!SIGNED(-1,2,>));
 TEST(4,UNSIGNED(-1,2,>));
 TEST(5,SIGNED(-1,2,%)==-1);
 TEST(6,UNSIGNED(-1,2,%)==1);
 TEST(7,SIGNED(-1,2,/)==0);
 TEST(8,UNSIGNED(-1,2,/)==0x7fffffff);
 TEST(9,(int)SIGNED(-16,2,>>)==-4);
 TEST(10,UNSIGNED(-16,2,>>)==0x3ffffffc);
 unsigned int u1=-1,u2=2;
 TEST(11,SIGNED(u1,u2,<));
 TEST(12,!UNSIGNED(u1,u2,<));
 TEST(13,!SIGNED(u1,u2,>));
 TEST(14,UNSIGNED(u1,u2,>));
 TEST(15,SIGNED(u1,u2,%)==-1);
 TEST(16,UNSIGNED(u1,u2,%)==1);
 TEST(17,SIGNED(u1,u2,/)==0);
 TEST(18,UNSIGNED(u1,u2,/)==0x7fffffff);
 u1=-16;u2=2;
 TEST(19,(int)SIGNED(u1,u2,>>)==-4);
 TEST(20,UNSIGNED(u1,u2,>>)==0x3ffffffc);
 TEST(21,0xffffffff==-1);
 Sumarize();

 subtest("other  ");
 int i,j;
 i=1,j=2;
//COMMA
 printf("comma");
 TEST(1,i==1);
 TEST(2,j==2);
//SWITCH
 printf(",switch");
 switch(i)
 {case 1:j=4;break;
#define FORSWITCH 2 //check if comment in macro does f**ks things up
  case FORSWITCH:j=3;break;
#undef FORSWITCH
  default:j=1;break;
 }
 TEST(1,j==4);
//TYPEOF
#ifdef SeeR
 printf(",typeof");
 TEST(1,strcmp(typeof(int),"int")==0);
 TEST(2,strcmp(typeof(1),"int")==0);
 TEST(3,strcmp(typeof(x1),"fixed")==0);
#endif
 Sumarize();
}
/**********************************************************************/

struct initCHARPtr{
       char *n1,*n2,*n3;
};
struct initCHARTab{
       char n1[50],n2[50],n3[50];
};

/* test of two dimensional matrix initialization */
#define P_OFFX 320
#define P_OFFY 32
int Array2D[4][2] =
   {
     {P_OFFX+1,P_OFFY+1},
     {P_OFFX+2,P_OFFY+2},
     {P_OFFX+3,P_OFFY+3},
     {P_OFFX+4,P_OFFX+4},
   };

initCHARPtr initPCHAR={"Jan","Skrzetuski",NULL};
initCHARTab initTCHAR={"Jan","Skrzetuski","Bohun"};
int initINTPtr[3]={1,2,3};
initCHARPtr initGCHAR={initPCHAR.n1,initPCHAR.n2,initPCHAR.n3};
initCHARPtr initGCHAR2=initPCHAR;
char GinitCHARArray[5*2]="Zosia";
const int GinitINT1=13;
int GinitINT2=GinitINT1;

void Test_Initialization()
{start("Initialization");

 subtest("heap");
//VAR:
 printf("via var");
 TEST(1,strcmp(initGCHAR.n1,"Jan")==0);
 TEST(2,strcmp(initGCHAR.n2,"Skrzetuski")==0);
 TEST(3,!initGCHAR.n3);
 TEST(4,strcmp(initGCHAR2.n1,"Jan")==0);
 TEST(5,strcmp(initGCHAR2.n2,"Skrzetuski")==0);
 TEST(6,!initGCHAR2.n3);
//CHAR/:
 printf(",char*");
 TEST(1,strcmp(initPCHAR.n1,"Jan")==0);
 TEST(2,strcmp(initPCHAR.n2,"Skrzetuski")==0);
 TEST(3,!initPCHAR.n3);
//INT:
 printf(",int");
 TEST(1,GinitINT1==13);
 TEST(2,GinitINT2==13);
//CHAR[]:
 printf(",char[]");
 TEST(1,strcmp(initTCHAR.n1,"Jan")==0);
 TEST(2,strcmp(initTCHAR.n2,"Skrzetuski")==0);
 TEST(3,strcmp(GinitCHARArray,"Zosia")==0);

//INT[][]
 printf(",int[][]");
 TEST(1,Array2D[0][0]==P_OFFX+1);
 TEST(2,Array2D[0][1]==P_OFFY+1);
 TEST(3,Array2D[1][0]==P_OFFX+2);
 TEST(4,Array2D[2][1]==P_OFFY+3);
//INT*
 printf(",int*");
 TEST(1,initINTPtr[0]==1);
 TEST(2,initINTPtr[1]==2);
 TEST(3,initINTPtr[2]==3);

 Sumarize();

 subtest("stack");
 initCHARPtr initPCHAR2={"Jan","Skrzetuski",NULL};
// initCHARPtr initLCHAR2=initPCHAR2;
 initCHARPtr initLCHAR1={initPCHAR2.n1,initPCHAR2.n2,initPCHAR2.n3};
 initCHARPtr initLCHAR2={initPCHAR.n1,initPCHAR.n2,initPCHAR.n3};
 initCHARPtr initLCHAR3={structure.name/*initPCHAR2.n1*/,initPCHAR2.n2,initPCHAR2.n3};
 initCHARPtr initLCHAR4=initPCHAR2;
 initCHARPtr initLCHAR5=initPCHAR;
//VAR
 printf("via var");
 TEST(1,strcmp(initLCHAR1.n1,"Jan")==0);
 TEST(2,strcmp(initLCHAR1.n2,"Skrzetuski")==0);
 TEST(3,!initLCHAR1.n3);
 TEST(4,strcmp(initLCHAR2.n1,"Jan")==0);
 TEST(5,strcmp(initLCHAR2.n2,"Skrzetuski")==0);
 TEST(6,!initLCHAR2.n3);
 TEST(7,strcmp(initLCHAR3.n1,"Jan")==0);
 TEST(8,strcmp(initLCHAR3.n2,"Skrzetuski")==0);
 TEST(9,!initLCHAR3.n3);
 TEST(10,strcmp(initLCHAR4.n1,"Jan")==0);
 TEST(11,strcmp(initLCHAR4.n2,"Skrzetuski")==0);
 TEST(12,!initLCHAR4.n3);
 TEST(13,strcmp(initLCHAR5.n1,"Jan")==0);
 TEST(14,strcmp(initLCHAR5.n2,"Skrzetuski")==0);
 TEST(15,!initLCHAR5.n3);
//INT
 printf(",int");
 int LinitINT1=13;
 int LinitINT2=LinitINT1;
 TEST(1,LinitINT1==13);
 TEST(2,LinitINT2==13);
 int LinitINT3=LinitINT1||LinitINT2;
 TEST(3,LinitINT3);

//CHAR*
 char *LinitCHARPtr="Kamil";
 printf(",char*");
 TEST(1,strcmp(initPCHAR2.n1,"Jan")==0);
 TEST(2,strcmp(initPCHAR2.n2,"Skrzetuski")==0);
 TEST(3,!initPCHAR2.n3);
 TEST(4,strcmp(LinitCHARPtr,"Kamil")==0);

//CHAR[]:
 char LinitCHARArray[10]="Joasia";
 printf(",char[]");
 initCHARTab initTCHAR2={"Jan","Skrzetuski","Bohun"};
 TEST(1,strcmp(initTCHAR2.n1,"Jan")==0);
 TEST(2,strcmp(initTCHAR2.n2,"Skrzetuski")==0);
 TEST(3,strcmp(LinitCHARArray,"Joasia")==0);
//INT[][]
 printf(",int[][]");
 int Array2D2[4][2] =
   {
     {P_OFFX+1,P_OFFY+1},
     {P_OFFX+2,P_OFFY+2},
     {P_OFFX+3,P_OFFY+3},
     {P_OFFX+4,P_OFFX+4},
   };
 TEST(5,Array2D2[0][0]==P_OFFX+1);
 TEST(6,Array2D2[0][1]==P_OFFY+1);
 TEST(7,Array2D2[1][0]==P_OFFX+2);
 TEST(8,Array2D2[2][1]==P_OFFY+3);
//INT*

/*
 printf(",int*");
 int *initINTPtr2={1,2,3};
 TEST(1,initINTPtr2[0]==1);
 TEST(2,initINTPtr2[1]==2);
 TEST(3,initINTPtr2[2]==3);
*/

 Sumarize();
}

/**********************************************************************/
void Test_Importing()
{start("Importing");
//CHAR:
 printf("char");
 TEST(1,varchar==12);
 varchar=13;
 TEST(2,varchar==13);
//INT:
 printf(",int");
 TEST(1,varint==13);
 varint=14;
 TEST(2,varint==14);
//STRUCT:
 printf(",struct");
 TEST(1,structure.a==1);
 TEST(2,structure.b==2.0);
 TEST(3,structure.c==3.0);
 TEST(4,structure.d1==64);
 TEST(5,structure.d2==65);
 TEST(6,structure.inside.x==1);
 TEST(7,structure.inside.y==2);
 TEST(8,strcmp(structure.name,"Jan")==0);
//TABLE:
 printf(",table");
 TEST(1,table[0]==1);
 TEST(2,table[1]==2);
 TEST(3,table[2]==3);
 TEST(4,strcmp(chartable,"Karol")==0);
//POINTER:
 printf(",pointer");
 TEST(1,tableptr[0]==1);
 TEST(2,tableptr[1]==2);
 TEST(3,tableptr[2]==3);
 TEST(4,strcmp(charptr,"Ludwik")==0);
 strcpy(chartable,charptr);
 TEST(5,strcmp(chartable,"Ludwik")==0);
// strcpy(charptr,"Jan");
// TEST(6,strcmp(charptr,"Jan")==0);
 printf(",functions");
 TEST(1,doublefunc(1,2.0,3.0,4.0)==10.0);

 Sumarize();
}

/**********************************************************************/
#ifdef SeeR
export Class.farther;
#endif
struct Class{
       class InClass{
       public:
       int a,b;
       int set(int A,int B) {a=A;b=B;}
       };
       int m;
       int f(int i) {return i+m;}
       int farther(int _m=1);
       int a;
       InClass inclass;
#ifdef SeeR
       import(1) int Imp(int z);//does the same as f
#else
       int Imp(int z) {return f(z);}
#endif
};

struct Fighter{
 class Weapon{
 public:
  int inflict,deflect;
  void init(int i,int d);
  int go() {return inflict-deflect;}
 };
 char *name;
 Weapon left,right;
 Class x;
 Fighter *against;
 int a()
 {Weapon *i=&left;
  i->init(5,2);
  TEST(6,i->go()==left.go());
  TEST(7,i->go()==3);
  x.m=1;
  TEST(8,x.f(1)==2);
  return left.go()+right.go();
 }
};

void Fighter::Weapon::init(int i,int d)
{inflict=i,deflect=d;}

#ifdef SeeR
#ifdef TEST_SCRIPTS

script ThisScript{
 struct Class{
        class InClass{
        int a,b;
        };
        int m;
        int f(int i);
        int farther(int _m=1);
        int a;
        InClass inclass;
 };
 int ex_int;
 int ex_inc(int i);
 retStruct2 structFunc2(int a,int b);
};

export ex_int;
export ex_inc;
int ex_int=103;
int ex_inc(int i)
{return ex_int+=i;
}

import bool getScript(ThisScript &s,char *scriptType);
bool isScript(ThisScript &s)
{return (*((int*)&s))?true:false;
}

#endif
#endif



class complex
{
public:
 double r,i;
public:
 complex();// {r=i=0;}
 complex(double _r,double _i)
  {
   r=_r;
   i=_i;
  }
 ~complex();// {r=i=0;}
// complex operator+(complex& x);
 complex operator+(complex& x)
  {complex re;
   re.r=r+x.r;re.i=i+x.i;
   return re;
  }
 double real(complex& a)
 {return r;
 }
};
complex::complex()
{r=i=-1;
// printf("complex()\n");
}
complex::~complex()
{r=i=0;
// printf("~complex()\n");
}
/*complex complex::operator+(complex& x)
{complex re;
 re.r=r+x.r;re.i=i+x.i;
 return re;
}
*/

void testComplex()
{complex a,b,c;
 a.complex();
 a=b+c;
}

//Test global constructors
string globalString1("global");
string globalString=globalString1;

void alterString(string& x)
{x+=" altered";
}
void noAlterString(string x)
{x+=" altered";
}

void Test_Classes()
{start("Classes");
 Class f;
 Class::InClass fi;
 subtest("standard");

 printf("basics");
 TEST(1,(int)&f.m==(int)&f);
 TEST(2,4+(int)&f==(int)&f.a);
 TEST(3,sizeof(Class)==16);
 TEST(4,sizeof(Class::InClass)==8);
 TEST(5,sizeof(Fighter)==24+sizeof(Class));
 TEST(6,sizeof(Fighter::Weapon)==8);
 TEST(7,sizeof(fi)==8);
 Fighter Avatar;
 Avatar.a();
 printf(",calling");
 f.m=2;
 TEST(1,f.f(1)==3);
 TEST(2,f.farther(2)==2);
 TEST(3,f.farther()==1);//should default to farther(1)...
 int a=(int)&f.a;
 TEST(4,a-((int)(&f))==4);
 f.inclass.set(1,2);
 TEST(5,f.inclass.a==1&&f.inclass.b==2);
 printf(",imported");
 f.m=2;
 TEST(1,f.Imp(1)==3);
 printf(",constructors");
 {
 complex cpxA,cpxB(1,2);
 TEST(1,cpxA.r==-1&&cpxA.i==-1);
 }

#ifdef SeeR
#ifdef TEST_SCRIPTS
 printf(",scripts");
 TEST(1,sizeof(ThisScript::Class)==sizeof(Class));
 TEST(2,sizeof(ThisScript)==5*4+12);
 ThisScript responder;
 TEST(3,strcmp(typeof(responder),typeof(ThisScript))==0);

 //now a trick - set DS reg of a script
 *((int*)&responder)=(int*)(&first_variable) + (-1);

 ex_int=100;

 if (getScript(responder,typeof(responder)))
 {
  TEST(4,responder.ex_int==103);
  TEST(5,isScript(responder)&&(responder.ex_int=3));
  TEST(6,responder.ex_int==3);
  TEST(7,responder.ex_inc(2)==5);
  TEST(8,responder.ex_int==5);
  TEST(9,ex_int==100);
  ThisScript::Class ic;
  ic.m=2;
  retStruct2 reS2;
  reS2.y=2;reS2.x=1;
  reS2=responder.structFunc2(10,20);
// printf("<%d>\n",structFunc2(10,20).x);
  TEST(10,reS2.x==10);
  TEST(11,reS2.y==20);

  //here is a problem! it should be rejected!
  //TEST(1,ic.f(1)==3);
  //TEST(2,ic.farther(2)==2);
 }
#endif

 Sumarize();

 subtest("stdlib  ");

//STRING
 string x("Jasio"),y,z="sio";
 y.string("string");//although y.string() should have been called before...
 printf("%s",y);//instead of printf("string");
 y="Ja";
 string w(x);
 TEST(1,x.operator==(w));
 w.operator=(y.operator+(z));//w=y+z;
 TEST(2,w==x);
 w=y+z+" i Malgosia";
 w+="!!";
 TEST(3,w==x+" i Malgosia!!");
 w=x(1,2);//substring starting from 1 and of length 2
 TEST(4,w=="as");
 string v=1;
 w=2;
 TEST(5,v=="1");
 TEST(6,w.toInt()==2);
 w="Ja i Baba Jaga";
 w.insert(2,z);
 //w.insert(2,"sio");//won't work
 TEST(7,w=="Jasio i Baba Jaga");
 TEST(8,w.find(z)==2);
 TEST(9,w.find(x)==0);
 TEST(10,x.find(w)==-1);
 w.del(2,3);
 TEST(11,w=="Ja i Baba Jaga");
 TEST(12,w.replace(y,v)==1);
 TEST(13,w=="1 i Baba Jaga");
 string v1="a";
// TEST(14,w.replace(v1,v,1)==4);
 ex_inc(ex_inc(ex_inc(ex_inc(ex_inc(ex_inc(ex_inc(ex_inc(ex_inc(1)))))))));
// TEST(14,w.replace(string("a"),v,1)==4);
 TEST(14,w.replace("a",v,1)==4);
 TEST(15,w=="1 i B1b1 J1g1");
// printf("%s\n",typeof(string("Joe ")+"Jack "));
 TEST(16,string("Joe ")+"Jack "+x=="Joe Jack Jasio");
// printf("%s\n",w);
 TEST(17,string("Ty")+"!\n"=="Ty!\n");
 TEST(18,string(v1=="a"?"yes":"no")=="yes");

 char *c1="lala",*c2="lala";//this checks if "lala" is not repeated in
 TEST(19,c1==c2);//memory
 TEST(20,globalString=="global");

 noAlterString(globalString);
 TEST(21,globalString=="global");
 alterString(globalString);
 TEST(22,globalString=="global altered");

 printf(",vector");
 vector vec1(1,0,0);
 vector vec2(10,11,12);
 TEST(1,vec1!=vec2);
 TEST(2,vec1+vec2==vector(11,11,12));
 TEST(3,vec1<vec2);
 TEST(4,vec2>vec1);
 TEST(5,vector(4,3,3)-vec1+vec2==vector(13,14,15));
 TEST(6,vec1.length()==1);
 vec1=vector(2,0,0);
 TEST(7,vec1.length()==2);
 vec1.normalize();
 TEST(8,vec1==vector(1,0,0));
#endif
 Sumarize();
}

//In SeeR you could also write '.' instead of '::'
//int Class.farther(int _m)
int Class::farther(int _m=1)
{
        this->m=_m;
        m=_m;
        m+=f(0);
        string o="JAVA";//this checks if memory allocated by o is freed
        return m/2;
}

//This one tests if SeeR wants unused functions to be exported in main
//program. It shouldn't! Unused imported functions are ignored by SeeR.
//(thew, it took a long work to achive this...)
import int Foo_NOT_USED();

struct structA;
struct structB{
  structA *prev,*next;
};
struct structA{
  structB *prev;
};
