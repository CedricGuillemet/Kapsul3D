/*
 * 20010119
 *
 * txtcolor.c by Pierre Renaux (prenaux@alias25.com)
 *
 * TxtColor is a little program which syntax highlight a simple text file
 * (which can be a C, C++, or other language source code) and output the
 * result in a html file. Use the file extension to reconize the file type.
 */

#include <stdio.h>
#include <string.h>

/*===========================================================================
	GLOBAL VARS
===========================================================================*/
FILE *in, *out;

/*===========================================================================
	COLORS & MISC VARS
===========================================================================*/
int tab_size = 1;

// C++
char cpp_color_ctag[] = "#0000FF";		// C sepcific commands
char cpp_color_ptag[] = "#FF00FF";		// C++ preprocessor commands
char cpp_color_cpptag[] = "#FF0000";	// C++ specific commands
char cpp_color_string[] = "#999999";	// C++ Strings
char cpp_color_comment[] = "#007700";	// C++ Comment

/*===========================================================================
	MISC UTILS
===========================================================================*/
/*
	Echo a string in the out file.
*/
void echo(char *string)
{
	int i;
	int len = strlen(string);
	
	for(i = 0; i < len; i++)
	{
	 	fputc(string[i], out);
	}
}

/*
	echo a tabluation
*/
void echo_tab(void)
{
	int i;
	
	for(i = 0; i < tab_size; i++)
		fputc(' ', out);
}

/*
	echo a char
*/
void echo_char(int c)
{
	if(c == '\t')
	{
		echo_tab();
	}
	else if(c == '\\')
	{
		fputc('\\', out);
		fputc(fgetc(in), out);
	}
	else if(c == '<')
	{
		echo("&lt");
	}
	else if(c == '>')
	{
		echo("&gt");
	}
	else
		fputc(c, out);	
}

/*===========================================================================
	TXT
===========================================================================*/
/*
	Read a text file and output the result in the passe FILE
*/
void txt_read_and_output(void)
{
	unsigned char tmp;
	
	while(1)
	{
		tmp = fgetc(in);
		if(feof(in))
			break;
		fputc(tmp, out);
	}
}

/*===========================================================================
	C/C++
===========================================================================*/
// preprocesor
char *p_tags[] = {
	"#define","#error","#include","#elif","#if","#line",
	"#else","#ifdef","#pragma","#endif","#ifndef","#undef",
	NULL,
};

// C
char *c_tags[] = {
 	"auto", "break",
	"case","char","const","continue",
	"default","do","double",
	"else","enum","extern",
	"float","for", "goto",
	"if","int",	"long",
	"register","return", "short", "signed", "sizeof",
	"static","struct","switch", "typedef",
	"union","unsigned", "void","volatile",
	"while", "asm", "_asm", "__asm",
	"__fastcall","__self","__segment","__based","__segname","__fortran",
	"__cdecl","__huge","__far","__saveregs","__export","__pascal","__near",
	"__loadds","__interrupt","__inline",
 	"I8","I16","I32","I64", "U8","U16","U32","U64",
 	NULL
};

// C++
char *cpp_tags[] = {
	"class", "delete",
	"explicit", "friend",
	"inline", "new", "namespace",
	"operator", "private", "protected", "public",
	"this", "try", "virtual",
	"__multiple_inheritance",
	"__single_inheritance",
	"__virtual_inheritance",
	NULL
};

#define CPP_BUFF_SIZE		16384

// zero the buffer
#define CPP_ZERO_BUFFER()   memset(buffer, 0, CPP_BUFF_SIZE); bi = 0
// flush and zero the buffer
#define CPP_FLUSHZ_BUFFER()	if(buffer[0]) { echo(buffer); CPP_ZERO_BUFFER(); }

/*
	Check if the passed char is valid for the reader
*/
int cpp_is_valid_char(int c)
{
	if((c == '#') ||
	   (c >= 'a' && c <= 'z') ||
	   (c >= 'A' && c <= 'Z'))
		return 1;
	
	return 0;
}

/*
	Write the passed string with the right color.
*/
void cpp_echo_tag(char *str, int cpp)
{
 	int i = 0;
 
 	if(strlen(str) <= 1)
 	{
 		echo(str);
 		return;
 	}

 	if(str[0] == '#')
 	{

 		for(i = 0; p_tags[i]; i++)
 		{
 			if(strcmp(str, p_tags[i])==0)
 			{
 				fprintf(out, "<font color='%s'>", cpp_color_ptag);
 				echo(str);
 				echo("</font>");
 				return;
 			}
 		} 	
 	}
 	else
 	{ 
 		if(cpp)
 		{ 		 		
 			for(i = 0; cpp_tags[i]; i++)
 			{
 				if(strcmp(str, cpp_tags[i])==0)
 				{
 					fprintf(out, "<font color='%s'>", cpp_color_cpptag);
 					echo(str);
 					echo("</font>");
 					return;
 				}
 			}
 		}
 	 	
 		for(i = 0; c_tags[i]; i++)
 		{
 			if(strcmp(str, c_tags[i])==0)
 			{
 				fprintf(out, "<font color='%s'>", cpp_color_ctag);
 				echo(str);
 				echo("</font>");
 				return;
 			}
 		}
 	}
 
 	echo(str);
}

/*
	Read a C++ file and output it.
*/
void cpp_read_and_output(int cpp)
{
	int bi = 0;
	unsigned char c;
	unsigned char buffer[CPP_BUFF_SIZE];
	
	memset(buffer, 0, CPP_BUFF_SIZE);
	
 	while(!feof(in))
 	{
		c = fgetc(in);
		if(feof(in))
		{
			CPP_FLUSHZ_BUFFER();
			return;
		}
	
		// string
		if(c == '"' || c == '\'')
		{						
			unsigned char s = c;
			
			CPP_FLUSHZ_BUFFER();
			
			fprintf(out, "<font color=%s>", cpp_color_string);
			fputc(c, out);
			
			while(!feof(in))
			{
				c = fgetc(in);				
				
				if(c == s)
				{
					fputc(c, out);
					break;
				}
				else
				{
					echo_char(c);
				}
			}
			echo("</font>");
		}
		// comments
		else if(c == '/')
		{
			CPP_FLUSHZ_BUFFER();
			
			c = fgetc(in);
			if(c == '/')
			{
				char tc;

				fprintf(out, "<font color=%s>//", cpp_color_comment);				
				while(1)
				{
					tc = fgetc(in);
					if(feof(in))
					{
						return;
					}
				
					echo_char(tc);
					if(tc == '\n' || tc == '\r')
					{
						break;
					}										
				}
				echo("</font>");
			}
			else if(c == '*')
			{
				fprintf(out, "<font color=%s>/*", cpp_color_comment);
				while(!feof(in))
				{
					c = fgetc(in);
					if(feof(in))
					{
						return;
					}
				
					if(c == '*')
					{
						c = fgetc(in);
						if(c == '/')
						{
							echo("*/</font>");
							break;
						}
						else
						{
							fputc('*', out);
							echo_char(c);
						}
					}
					else
					{
						echo_char(c);
					}
					
				}
			}
			else
			{
				echo_char('/');
				echo_char(c);
			}
		}
		// valid char for keyword
		else if(cpp_is_valid_char(c))
		{
			buffer[bi++] = c;
		}
		// normal
		else
		{	
			if(buffer[0])
			{
				cpp_echo_tag(buffer, cpp);
				CPP_ZERO_BUFFER();
			}
			
			echo_char(c);
		}
		
	}
}

/*===========================================================================
	GLOBAL
===========================================================================*/
/*
	Return the file extension.
*/
char *get_extension(char *filename)
{
 int pos, c;

 pos = strlen(filename);

 while(pos > 0)
 {
  c = filename[pos-1];
  if((c == '.') || (c == '/') || (c == '\\'))
   break;
  pos--;
 }

 if((pos > 0) && (filename[pos-1] == '.'))
  return filename + pos;

 return filename + strlen(filename);
}

/*
	Show the help
*/
void show_help(void)
{
	printf( "\nsyntax:\n"
			"    txtcolor text_file_to_convert.ext text_file_out.html (tab_size)\n"
			"\nsupported file types:\n"
			"    note: The file type is detected with the filename extension\n\n"
			"    c, cxx, cc, cpp, h, hpp => C/C++ source files\n"
			"    other => simple text files\n\n"
			">>>>>>>>>>>>>>>>>>>> Web site: www.Alias25.com <<<<<<<<<<<<<<<<<<<<\n"
		  );
		
}

/*
	MAIN function
*/
int main(int argc, char **argv)
{
	char *ext;
	
	printf(">>> TxtColor v1.0 by Pierre Renaux (prenaux@alias25.com) <<<\n");
	
	if(argc <= 2)
	{
		show_help();
		return 1;
	}
	
	if(argc >= 4)
	{
		tab_size = atoi(argv[3]);
	}
	
	in = fopen(argv[1], "r");
	if(!in)
	{
		printf("Unable to open text file %s !\n", argv[1]);
		return 1;
	}

	out = fopen(argv[2], "w");
	if(!out)
	{
		printf("Unable to open output file %s !\n", argv[2]);
		return 1;
	}
	
	// write the html header
	echo("<pre>\n");
	
	// read the extension and output the file
	ext = get_extension(argv[1]);
	if(stricmp(ext, "c") == 0)
	{	// C
		cpp_read_and_output(0);
	}
	else if((stricmp(ext, "cpp") == 0) ||
	        (stricmp(ext, "cc") == 0) ||
	        (stricmp(ext, "cxx") == 0) ||
	        (stricmp(ext, "h") == 0) ||
	        (stricmp(ext, "hpp") == 0))
	{	// C++
		cpp_read_and_output(1);
	}
	else
	{	// simple text file
		txt_read_and_output();
	}
	
	// write the html bottom
	echo("</pre>\n");
	
	printf("[%s] file colored to [%s]\n", argv[1], argv[2]);
		
	fclose(out);
	fclose(in);
	return 0;
}
