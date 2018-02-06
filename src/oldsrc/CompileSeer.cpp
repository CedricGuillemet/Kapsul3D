#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <seer.h>
//#include <headers.h>
char *header=
//This is the internal header.
//Something like 'stdio' internal header in seerc, but smaller
"#ifndef HEADER_INCLUDED                                                \n"
"#include stdlib							\n"
"import int printf(char *,...);                                         \n"
"import int scanf(char *,...);                                          \n"
"import void MessageBox(char *);                                          \n"

// Now some more things : the NPC class
// Hey, but we're in C and have no NPC class, only a struct.
//But we create below our custom dispatcher, which will convert
//script's calls to members to standard C functions with 'this'
//as first parameter. Quite a clean hack :-)
// Our dispatcher will have number 1, so 'import(1)' instead of 'import'
//is required.

//"#define c_import import(1)                                             \n"

"struct Vertex\n"
"{\n"
" double vx;\n"
" double vy;\n"
" double vz;\n"
" int Index;\n"
" int BoolStat;\n"
" bool Selected;\n"
"c_import double GetDistance ( Vertex pt );\n"
"c_import bool GetSelected ( );\n"
"c_import void SetSelected ( bool selected );\n"
"c_import bool operator== ( Vertex cmpt );\n"
"c_import bool operator!= ( Vertex cmpt );\n"
"c_import Vertex operator+ ( Vertex &cmpt );\n"
"c_import Vertex operator- ( Vertex cmpt );\n"
"c_import Vertex operator* ( int cmpt );\n"
"c_import void operator-= ( Vertex cmpt );\n"
"c_import void operator+= ( Vertex &cmpt );\n"
"c_import void operator*= ( Vertex cmpt );\n"
"c_import void operator/= ( int cmpt );\n"
"c_import Vertex operator/ ( double cmpt );\n"
"c_import void operator= ( Vertex cmpt );\n"
"c_import Vertex RotVect ( Vertex Vect , double ng );\n"
"c_import bool IsEquivalentTo ( Vertex cmpt );\n"
"c_import void Snap ( Vertex SnapVal );\n"
"c_import void GetMinOf ( Vertex vert );\n"
"c_import void GetMaxOf ( Vertex vert );\n"
"c_import double Normalize ( void );\n"
"c_import double Dot ( Vertex pVec );\n"
"c_import void Cross ( Vertex & p , Vertex & q );\n"

"};\n"
//let's force the script to export these,
//they should be implemented further in script:
"export Main;                                                        \n"
"void Main();                                               \n"

"#define HEADER_INCLUDED                                                \n"
"#endif                                                                 \n"
;

/*
This function tells SeeR addresses of functions and variables it can
use (import). If script imports symbol you don't tell the address SeeR
will complain : unresolved reference.Here we use only printf, but we
can add also scanf. In this way you also add variables.
We add also the header files and export class NPC.
*/
void MessageBox2(char *msg)
{
	MessageBox(NULL,msg,"Info",MB_OK);
}
void Init_Externals()
{
	scAdd_External_Symbol("printf",printf);
	scAdd_External_Symbol("scanf",scanf);
	scAdd_External_Symbol("MessageBox",MessageBox2);
	//let's export the class

	scAdd_Member_Symbol("Vertex.GetDistance",Vertex::GetDistance);
	scAdd_Member_Symbol("Vertex.GetSelected",Vertex::GetSelected);
	scAdd_Member_Symbol("Vertex.SetSelected",Vertex::SetSelected);
	scAdd_Member_Symbol("Vertex.operator==",Vertex::operator==);
	scAdd_Member_Symbol("Vertex.operator!=",Vertex::operator!=);
	scAdd_Member_Symbol("Vertex.operator+",Vertex::operator+);
	scAdd_Member_Symbol("Vertex.operator-",Vertex::operator-);
	//scAdd_Member_Symbol("Vertex.operator*",Vertex::operator *(double cmpt));
	scAdd_Member_Symbol("Vertex.operator-=",Vertex::operator-=);
	scAdd_Member_Symbol("Vertex.operator+=",Vertex::operator+=);
	scAdd_Member_Symbol("Vertex.operator*=",Vertex::operator*=);
	scAdd_Member_Symbol("Vertex.operator/=",Vertex::operator/=);
	scAdd_Member_Symbol("Vertex.operator/",Vertex::operator/);
	scAdd_Member_Symbol("Vertex.operator=",Vertex::operator=);
	scAdd_Member_Symbol("Vertex.RotVect",Vertex::RotVect);
	scAdd_Member_Symbol("Vertex.IsEquivalentTo",Vertex::IsEquivalentTo);
	scAdd_Member_Symbol("Vertex.Snap",Vertex::Snap);
	scAdd_Member_Symbol("Vertex.GetMinOf",Vertex::GetMinOf);
	scAdd_Member_Symbol("Vertex.GetMaxOf",Vertex::GetMaxOf);
	scAdd_Member_Symbol("Vertex.Normalize",Vertex::Normalize);
	scAdd_Member_Symbol("Vertex.Dot",Vertex::Dot);
	scAdd_Member_Symbol("Vertex.Cross",Vertex::Cross);
	//scAdd_Internal_Header("Vertex",Vertex);

	scAdd_Internal_Header("theHeader",header);
}

//It converts any C++ member call to C call.
//The dispatcher work like this:
// when you call any exported function, the required
// dispatcher is called.
// If this is a member function, the first parameter is
// 'this'.
// All parameters are stored in order one by one in params.
// The paramcount is size in bytes of them.
// The options tell us, if this function return double, or
// something 32bit long (int, pointer, char, float ...).
// It tells us also if the function is class-member or not.
// Here we only turn off the class-member flag. EASY :-)
//Now we can cooperate between objective script and
//non-objective C.
void MyDispatcher
(int *result,void *function,int *params,int paramcount,unsigned int options)
{
	if (options&scDispatch_Member)
	{//C++ call - convert to typical C call, so 'this' is the first param.
		//options^=scDispatch_Member;
	}
	scStandardDispatcher(result,function,params,paramcount,options);
}

/*** THE MAIN ***************************************/
int __declspec( dllexport ) CompileAndRun(char *ScriptSrc,char *DbgFile)
{
	char temp[512];
	//scrpt will contain the compiled script
	scScript scrpt;

	//and this is the instance of script, which we can call
	//it contains all the data from script.
	scInstance *prog;

	//let's give the script some functions of ours
	Init_Externals();

	//let's add the dispatcher as the 1st one (the default one is the 0);
	//all functions with "import(1)" will use this one.
	scSeeR_Set(scSeeR_Dispatcher,1,MyDispatcher);

	//when in SeeR in debug mode, here it will store all debugging data
	scOpen_Debug(DbgFile);//start debugging

	//compile example script : "excpp.sc", this won't need any changes!
	scrpt= scCompile_Text(ScriptSrc);

	//Error?
	if (scErrorNo)
	{
		sprintf(temp,"%s\n> %s\n",scErrorMsg,scErrorLine);
		MessageBox(NULL,temp,"Error",MB_OK);
		return 0;
	}

	//create instance of the script
	prog=scCreate_Instance(scrpt,"");

	//Error?
	if (!prog)
	{
		printf(temp,"Error creating instance!\n%s\n",scErrorMsg);
		MessageBox(NULL,temp,"Error",MB_OK);
		return 0;
	}

	//now, let's execute the function (here 'main' has no arguments)
	/*
	scCall_Instance(prog,scGet_Symbol(prog,"Init"),"Igor the Shopkeeper");
	//Error?
	if (scErrorNo)
	printf("%s\n",scErrorMsg);
	*/
	//NPCconstruct(&npc);//initialize object npc;we've got to do this manually in C

	//let's call the script... sorry - instance
	scCall_Instance(prog,scGet_Symbol(prog,"Main"));
	if (scErrorNo)
	{
		printf(temp,"%s\n",scErrorMsg);
		MessageBox(NULL,temp,"Error",MB_OK);
		return 0;
	}

	//let's delete instance and script
	scFree_Instance(prog);
	free(scrpt);

	//close debugging - close the debug file also
	scClose_Debug();

	return 0;
}

