#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//############################################################################
//##                                                                        ##
//##  MAIN.CPP                                                              ##
//##                                                                        ##
//##  Console APP to load Q3BSP files, interpret them, organize them into   ##
//##  a triangle mesh, and save them out in various ASCII file formats.     ##
//##                                                                        ##
//##  OpenSourced 12/5/2000 by John W. Ratcliff                             ##
//##                                                                        ##
//##  No warranty expressed or implied.                                     ##
//##                                                                        ##
//##  Part of the Q3BSP project, which converts a Quake 3 BSP file into a   ##
//##  polygon mesh.                                                         ##
//############################################################################
//##                                                                        ##
//##  Contact John W. Ratcliff at jratcliff@verant.com                      ##
//############################################################################

#include "q3bsp.h"

void main(int argc,char **argv)
{

  // Usage: q3bsp <name>.BSP
  if ( argc != 2 )
  {
    printf("Usage: q3bsp <name>.BSP\n");
    printf("Where <name> is the name of a valid Quake3 BSP file.\n\n");
    printf("This utility will convert a Quake3 BSP into a valid\n");
    printf("polygon mesh and output the results into two seperate VRML 1.0\n");
    printf("files.  The first VRML file contains all the U/V mapping and\n");
    printf("texture mapping information for channel #1, and the second\n");
    printf("VRML file will contain all of the U/V mapping and texture names\n");
    printf("for the second U/V channel, which contains all lightmap\n");
    printf("information.  You can then directly import these files into any\n");
    printf("number of 3d editing tools, including 3d Studio Max\n");

    printf("This tool also extracts the lightmap data and saves it out as a\n");
    printf("series of .BMP files.\n\n");
    printf("OpenSourced by John W. Ratcliff on December 5, 2000\n");
    printf("Merry Christmas!\n\n");
    printf("Contact Id Software about using Quake 3 data files in and\n");
    printf("Quake 3 editing tools for commercial software development\n");
    printf("projects.\n");
    exit(1);
  }

  Quake3BSP q( SGET(argv[1]), SGET("a") );

  VertexMesh *mesh = q.GetVertexMesh();
  if ( mesh )
  {
    // save VRML file using channel #1
    // save VRML file using channel #2
    String str = argv[1];
    String name1 = str + "1";
    String name2 = str + "2";
    printf("Saving U/V channel #1 to file %s.WRL\n",name1.c_str());
    mesh->SaveVRML(name1,true);
    printf("Saving U/V channel #2 to file %s.WRL\n",name2.c_str());
    mesh->SaveVRML(name2,false);
  }
  else
  {
    printf("Failed to crunch %s\n", argv[1]);
  }


}
