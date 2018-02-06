// Generate.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char Text[512000];
int taille;
int ptr=0;
char Token[256];
int tcav;

/*
    #ifdef USE_SEER
    void ExportSeer(void);
    #endif
*/

char Gene[512000];
char Fns[512000];
char Operator[16];
char FnName[256];

void GetToken()
{
    tcav=0;
Start:
    while((Text[ptr]==' ')||(Text[ptr]=='\r')||(Text[ptr]=='\n')||(Text[ptr]=='\t')) ptr++;

    if ((Text[ptr]=='/')&&(Text[ptr+1]=='*'))
    {
        while(!((Text[ptr]=='*')&&(Text[ptr+1]=='/'))) ptr++;
        ptr+=2;
        goto Start;
    }

    if ((Text[ptr]=='/')&&(Text[ptr+1]=='/'))
    {
        while(Text[ptr]!='\n') ptr++;
        goto Start;
    }

    if ( ((Text[ptr]>='a')&&(Text[ptr]<='z'))||((Text[ptr]>='A')&&(Text[ptr]<='Z'))||(Text[ptr]=='_') )
    {
        while ( ((Text[ptr]>='a')&&(Text[ptr]<='z'))||((Text[ptr]>='A')&&(Text[ptr]<='Z'))||
            ((Text[ptr]>='0')&&(Text[ptr]<='9')) || (Text[ptr]=='_') )
        {

            Token[tcav++]=Text[ptr++];
            Token[tcav]=0;
        }
        return;
    }


    if ( ((Text[ptr]>='0')&&(Text[ptr]<='9')) )
    {
        while ( ((Text[ptr]>='0')&&(Text[ptr]<='9'))||(Text[ptr]=='.') )
        {

            Token[tcav++]=Text[ptr++];
            Token[tcav]=0;
        }
        return;


    }

    Token[0]=Text[ptr];
    Token[1]=0;
    ptr++;
}

bool IsCurrentFn(void)
{
    int svgptr=ptr;
    char tempToken[256];
    strcpy(tempToken,Token);
    
    GetToken();
    while(strcmp(Token,";")!=0)
    {
        if ( (strcmp(Token,"(")==0)||(strcmp(Token,")")==0))
        {
            ptr=svgptr;
            //GetToken();
            strcpy(Token,tempToken);
            return true;
        }
        GetToken();
    }

    ptr=svgptr;

    //GetToken();
    strcpy(Token,tempToken);
    return false;
}

void GetFnName(void)
{
    int svgptr=ptr;
    char tempToken[256];
    strcpy(tempToken,Token);
    
    
    strcpy(FnName,Token);
    GetToken();
    while(strcmp(Token,";")!=0)
    {
        if (strcmp(Token,"(")==0)
        {
            
            ptr=svgptr;
            strcpy(Token,tempToken);
            return ;
        }
        strcpy(FnName,Token);
        GetToken();
    }
    ptr=svgptr;
    strcpy(Token,tempToken);

}

void GetOperator(void)
{
    int svgptr=ptr;
    char tempToken[256];
    strcpy(tempToken,Token);
    int tcav=0;
    
    GetToken();
    while(strcmp(Token,";")!=0)
    {
        if ( (Text[ptr-1]=='+')||(Text[ptr-1]=='-')||(Text[ptr-1]=='*')||(Text[ptr-1]=='/')||(Text[ptr-1]=='!')||(Text[ptr-1]=='=') )
        {
            Operator[tcav]=Text[ptr-1];
            Operator[tcav+1]=0;
            tcav++;
        }
        GetToken();
    }
    ptr=svgptr;
    strcpy(Token,tempToken);

}

bool IsOperator(void)
{
    int svgptr=ptr;
    char tempToken[256];
    strcpy(tempToken,Token);
    
    //GetToken();
    while(strcmp(Token,";")!=0)
    {
        if (strcmp(Token,"operator")==0)
        {
            ptr=svgptr;

            strcpy(Token,tempToken);
            return true;
        }
        GetToken();
    }
    ptr=svgptr;

    strcpy(Token,tempToken);

    return false;
}

int Generate(char *Arg1,char *Arg2,char *Arg3)
{
    FILE *fp;
	/*
    if (argc!=4)
    {
        printf("Generate source.h Dest.inc Reg.cxx\n");
        return -1;
    }
	*/
    fp=fopen(Arg1,"rb");
    memset(Text,0,512000);
    memset(Gene,0,512000);
    memset(Fns,0,512000);
    if (fp!=NULL)
    {
        taille=fread(Text,511999,1,fp);
        fclose(fp);

    }
    char classname[256];
    char HeaderName[256];
    char HeaderName2[256]="char ";
    _splitpath(Arg1,NULL,NULL,HeaderName,NULL);
    strcat(HeaderName2,HeaderName);
    strcat(HeaderName2,"[]={\"");

    strcat(Gene,"//This is the to-be compiled text-based class for SeeR. DO NOT EDIT!!!\n\n");
    strcat(Gene,HeaderName2);

    taille=strlen(Text);
    ptr=0;

    //Header

    GetToken();
    while(strcmp(Token,"class")!=0)
    {
        GetToken();
    }
    strcat(Gene,"struct ");
    GetToken();
    if (strcmp(Token,"__declspec")==0)
        for (int i=0;i<4;i++) GetToken();

    strcpy(classname,Token);
    strcat(Gene,Token);

    GetToken(); // {
    strcat(Gene,"\\n\"\n\"{\\n\"\n");


    // loop members

    GetToken();
    do
    {
        
        if ((strcmp(Token,"private")==0)|| (strcmp(Token,"public")==0) || (strcmp(Token,"protected")==0) )
        {
            GetToken();
            while (strcmp(Token,":")!=0)
                GetToken();

            GetToken(); // :
        }
        else
        if (strcmp(Token,"inline")==0) // fonction
        {

            GetToken();
            if ( (strcmp(Token,"~")==0)|| (strcmp(Token,"virtual")==0) || (strcmp(Token,classname)==0 ) )
            {
                if (IsCurrentFn())
                {
                    GetFnName();
                    if (strcmp(FnName,classname)!=0)
                        goto goit2;
                }
                else
                    goto gotit;

                GetToken();
                if (strcmp(Token,"operator")==0) 
                {
goit2:
                    strcat(Gene,"\"");

                    if (IsCurrentFn())
                    {
                        strcat(Gene,"c_import");

                        //strcat(Gene,classname);
                        //strcat(Gene,"");

                        strcat(Fns,"    scAdd_Member_Symbol(\"");
                        strcat(Fns,classname);
                    
                        if (IsOperator())
                        {
                            strcat(Fns,".operator");
                        
                            GetOperator();
                            strcat(Fns,Operator);
                            strcat(Fns,"\",");
                            strcat(Fns,classname);
                            strcat(Fns,"::operator");
                            strcat(Fns,Operator);
                            strcat(Fns,");\n");


                        }
                        else
                        {
                            strcat(Fns,".");
                            GetFnName();
                            strcat(Fns,FnName);
                            strcat(Fns,"\",");
                            strcat(Fns,classname);
                            strcat(Fns,"::");
                            strcat(Fns,FnName);
                            strcat(Fns,");\n");                        
                        }


                    }
                    else
                        strcat(Gene,classname);
                    goto gotit;

                }

                while ((strcmp(Token,";")!=0)||(strcmp(Token,"{")==0))
                    GetToken();

                if (strcmp(Token,"{")==0)
                {
                    while (strcmp(Token,"}")!=0)
                        GetToken();

                    GetToken();
                }
                GetToken();
            }
            else
            {

                strcat(Gene,"\"");

                if (IsCurrentFn())
                {
                    strcat(Gene,"c_import");

                    strcat(Fns,"    scAdd_Member_Symbol(\"");
                    strcat(Fns,classname);
                    
                    if (IsOperator())
                    {
                        strcat(Fns,".operator");
                        
                        GetOperator();
                        strcat(Fns,Operator);
                        strcat(Fns,"\",");
                        strcat(Fns,classname);
                        strcat(Fns,"::operator");
                        strcat(Fns,Operator);
                        strcat(Fns,");\n");


                    }
                    else
                    {
                        strcat(Fns,".");
                        GetFnName();
                        strcat(Fns,FnName);
                        strcat(Fns,"\",");
                        strcat(Fns,classname);
                        strcat(Fns,"::");
                        strcat(Fns,FnName);
                        strcat(Fns,");\n");                        
                    }


                }
gotit:
                while ( (strcmp(Token,";")!=0)||(strcmp(Token,"{")==0))
                {
                    if ( (Text[ptr-1]=='+')||(Text[ptr-1]=='-')||(Text[ptr-1]=='*')||(Text[ptr-1]=='/')||(Text[ptr-1]=='!')||(Text[ptr-1]=='=') )
                        ;
                    else
                    strcat(Gene," ");                    
                    strcat(Gene,Token);
                    GetToken();
                }
                if (strcmp(Token,"{")==0)
                {
                    while (strcmp(Token,"}")!=0)
                        GetToken();

                    GetToken();
                }
                strcat(Gene,";\\n\"\n");
                GetToken();
            }
        }
        else

        if ( (strcmp(Token,"~")==0)|| (strcmp(Token,"virtual")==0) )
        {
            GetToken();
            while ((strcmp(Token,";")!=0)||(strcmp(Token,"{")==0))
                GetToken();

            if (strcmp(Token,"{")==0)
            {
                while (strcmp(Token,"}")!=0)
                    GetToken();

                GetToken();
            }
            GetToken();
        }
        else

        if (strcmp(Token,classname)==0)
        {
            if (IsCurrentFn())
            {
                GetFnName();
                if (strcmp(FnName,classname)!=0)
                    goto goit2;
            }
            else
            {
                strcat(Gene,"\"");
                goto gotit;
            }

            GetToken();
            while ((strcmp(Token,";")!=0)||(strcmp(Token,"{")==0))
                GetToken();

            if (strcmp(Token,"{")==0)
            {
                while (strcmp(Token,"}")!=0)
                    GetToken();

                GetToken();
            }
            GetToken();
        }
        else
        {
            strcat(Gene,"\"");

            if (IsCurrentFn())
            {
                strcat(Gene,"c_import");

                strcat(Fns,"    scAdd_Member_Symbol(\"");
                strcat(Fns,classname);
                
                if (IsOperator())
                {
                    strcat(Fns,".operator");
                    
                    GetOperator();
                    strcat(Fns,Operator);
                    strcat(Fns,"\",");
                    strcat(Fns,classname);
                    strcat(Fns,"::operator ");
                    strcat(Fns,Operator);
                    strcat(Fns,");\n");


                }
                else
                {
                    strcat(Fns,".");
                    GetFnName();
                    strcat(Fns,FnName);
                    strcat(Fns,"\",");
                    strcat(Fns,classname);
                    strcat(Fns,"::");
                    strcat(Fns,FnName);
                    strcat(Fns,");\n");                        
                }
            }


            while ((strcmp(Token,";")!=0)||(strcmp(Token,"{")==0))
            {


                if ( (Text[ptr-1]=='+')||(Text[ptr-1]=='-')||(Text[ptr-1]=='*')||(Text[ptr-1]=='/')||(Text[ptr-1]=='!')||(Text[ptr-1]=='=') )
                    ;
                else
                    strcat(Gene," ");

                strcat(Gene,Token);
                GetToken();
            }

            if (strcmp(Token,"{")==0)
            {
                while (strcmp(Token,"}")!=0)
                    GetToken();

                GetToken();
            }
            strcat(Gene,";\\n\"\n");
            GetToken();
        }

     //   strcat(Gene,"\\n\"\n");
    }
    while(strcmp(Token,"}")!=0);

    strcat(Gene,"\"};\\n\"};\n");

    // declaration vers seer
/*
    strcat(Fns,"\n\n//This Register the class to Seer\n\n");

    strcat(Gene,classname);
    strcat(Gene,"::ExportSeer(void)\n{\n");

    // declare le header
*/
    strcat(Fns,"    scAdd_Internal_Header(\"");
    strcat(Fns,HeaderName);
    strcat(Fns,"\",");
    strcat(Fns,HeaderName);
    strcat(Fns,");\n");

/*    
    scAdd_Member_Symbol("string.append",string::append);
    scAdd_Member_Symbol("string.operator[]",string_operatorINDEX);
    strcat(Gene,"}\n\n//End for this header");
*/
    // all to disk

    fp=fopen(Arg2,"wt");
    if (fp!=NULL) 
    {
        fwrite(Gene,strlen(Gene),1,fp);
        fclose(fp);
    }

    fp=fopen(Arg3,"wt");
    if (fp!=NULL) 
    {
        fwrite(Fns,strlen(Fns),1,fp);
        fclose(fp);
    }

	return 0;
}

int main(int argc, char* argv[])
{
	Generate("d:\\Kapsul3D\\Kore\\Vertex.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_Vertex.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_Vertex.cpp");
	Generate("d:\\Kapsul3D\\Kore\\UndoRedo.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_UndoRedo.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_UndoRedo.cpp");
	Generate("d:\\Kapsul3D\\Kore\\TextureSpacePacker.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_TextureSpacePacker.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_TextureSpacePacker.cpp");
	Generate("d:\\Kapsul3D\\Kore\\UndoRedoEntry.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_UndoRedoEntry.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_UndoRedoEntry.cpp");
	Generate("d:\\Kapsul3D\\Kore\\VertBuf.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_VertBuf.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_VertBuf.cpp");
	Generate("d:\\Kapsul3D\\Kore\\Bone.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_Bone.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_Bone.cpp");
	Generate("d:\\Kapsul3D\\Kore\\BSPTree.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_BSPTree.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_BSPTree.cpp");
	Generate("d:\\Kapsul3D\\Kore\\Camera.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_Camera.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_Camera.cpp");
	Generate("d:\\Kapsul3D\\Kore\\CSG.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_CSG.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_CSG.cpp");
	Generate("d:\\Kapsul3D\\Kore\\Desk.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_Desk.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_Desk.cpp");
	Generate("d:\\Kapsul3D\\Kore\\KBoundBox.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_KBoundBox.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_KBoundBox.cpp");
	Generate("d:\\Kapsul3D\\Kore\\KOctree.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_KOctree.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_KOctree.cpp");
	Generate("d:\\Kapsul3D\\Kore\\KOctreeNode.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_KOctreeNode.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_KOctreeNode.cpp");
	Generate("d:\\Kapsul3D\\Kore\\KOption.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_KOption.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_KOption.cpp");
	Generate("d:\\Kapsul3D\\Kore\\KPatch.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_KPatch.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_KPatch.cpp");
	Generate("d:\\Kapsul3D\\Kore\\KSegment.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_KSegment.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_KSegment.cpp");
	Generate("d:\\Kapsul3D\\Kore\\Light.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_Light.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_Light.cpp");
	Generate("d:\\Kapsul3D\\Kore\\Matrix.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_Matrix.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_Matrix.cpp");
	Generate("d:\\Kapsul3D\\Kore\\Object.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_Object.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_Object.cpp");
	Generate("d:\\Kapsul3D\\Kore\\OGLView.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_OGLView.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_OGLView.cpp");
	Generate("d:\\Kapsul3D\\Kore\\Plan.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_Plan.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_Plan.cpp");
	Generate("d:\\Kapsul3D\\Kore\\Polygon.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_Polygon.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_Polygon.cpp");
	Generate("d:\\Kapsul3D\\Kore\\PrivateData.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_PrivateData.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_PrivateData.cpp");
	Generate("d:\\Kapsul3D\\Kore\\Shape.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_Shape.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_Shape.cpp");
	Generate("d:\\Kapsul3D\\Kore\\Selection.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_Selection.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_Selection.cpp");
	Generate("d:\\Kapsul3D\\Kore\\skeletton.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_skeletton.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_skeletton.cpp");
	Generate("d:\\Kapsul3D\\Kore\\SkyBox.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_SkyBox.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_SkyBox.cpp");
	Generate("d:\\Kapsul3D\\Kore\\Texture.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_Texture.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_Texture.cpp");

	Generate("d:\\Kapsul3D\\Kore\\TextureSpace.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_TextureSpace.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_TextureSpace.cpp");
	Generate("d:\\Kapsul3D\\Kore\\EntityProp.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_EntityProp.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_EntityProp.cpp");
	Generate("d:\\Kapsul3D\\Kore\\EntityType.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_EntityType.h","d:\\Kapsul3D\\Kore\\SeerHeaders\\Seer_EntityType.cpp");
}