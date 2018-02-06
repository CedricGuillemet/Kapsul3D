#include "stdafx.h"

#include "Leaves.h"

extern "C" 
{
    extern CKTexture *FeuilTex;
}

Leaves::Leaves(int f, double r)
: count(0),

facets(f),
radius(r) 
{
    
}



void Leaves::addLeaf(const CKMatrix& mat) 
{
    
    ++count;
    
    Vertex n(1.0f, 0.0f, 0.0f);
    
    Vertex t0(1.0, 0.0,0);
    Vertex t1(0.0, 0.0,0);
    Vertex t2(0.0, 1.0,0);
    Vertex t3(1.0, 1.0,0);
    
    Vertex v0(0.0, -1.0*radius, 0.0);
    Vertex v1(0.0, 1.0*radius, 0.0);
    Vertex v2(0.0, 1.0*radius, 2.0*radius);
    Vertex v3(0.0, -1.0*radius, 2.0*radius);
    
    
    
    normals.push_back(transformNormal(n, mat));
    
    texcoords.push_back(t0);
    colors.push_back(Vertex(rand(), rand(), rand()));
    vertices.push_back(transformPoint(v0, mat));
    
    texcoords.push_back(t1);
    colors.push_back(Vertex(rand(), rand(), rand()));
    vertices.push_back(transformPoint(v1, mat));
    
    texcoords.push_back(t2);
    colors.push_back(Vertex(rand(), rand(), rand()));
    vertices.push_back(transformPoint(v2, mat));
    
    texcoords.push_back(t3);
    colors.push_back(Vertex(rand(), rand(), rand()));
    vertices.push_back(transformPoint(v3, mat));
    
}


void Leaves::draw(CKMesh *daLeaf,Vertex *Center) 
{
/*
glPushMatrix();

  glScalef(100,100,100);
  
    
      
        glEnable(GL_TEXTURE_2D);
        
          FeuilTex->Bind();
          
            glAlphaFunc(GL_GREATER, 0.5);
            glEnable(GL_ALPHA_TEST);
            glEnable(GL_COLOR_MATERIAL);
            
              
                glBegin(GL_QUADS);
    */

    daLeaf->AllocatePoly(count*2,count*4);
	daLeaf->AllocateUV(0,count*4);

    //Face **ptrf;
    Vertex *ptrv;
	CKPolygon *ptrp;

    ptrv=daLeaf->pv;
    //ptrf=daLeaf->pf;
	ptrp=daLeaf->pl;

    for (int i=0, j=0; i<count; ++i) 
    {
		ptrp[j].Allocate(daLeaf,1,4);
		ptrp[j+1].Allocate(daLeaf,1,4);

      
        for (int k=0; k<4; ++k) 
        {
            /*
            glTexCoord2f(texcoords[j+k].x,texcoords[j+k].y);
            glVertex3f(vertices[j+k].x,vertices[j+k].y,vertices[j+k].z);
            */

            ptrv[(j*2)+k]=((vertices[(j*2)+k]*100.0f)+(*Center));
			
            daLeaf->puv[0][(j*2)+k].u=texcoords[(j*2)+k].x;
            daLeaf->puv[0][(j*2)+k].v=texcoords[(j*2)+k].y;
			
        }

        ptrp[j].nbvert[0]=(j*2);
        ptrp[j].nbvert[1]=(j*2)+1;
        ptrp[j].nbvert[2]=(j*2)+2;
        ptrp[j].nbvert[3]=(j*2)+3;

        ptrp[j].Tex[0][0]=(j*2);
        ptrp[j].Tex[0][1]=(j*2)+1;
        ptrp[j].Tex[0][2]=(j*2)+2;
        ptrp[j].Tex[0][3]=(j*2)+3;

        ptrp[j+1].nbvert[3]=(j*2);
        ptrp[j+1].nbvert[2]=(j*2)+1;
        ptrp[j+1].nbvert[1]=(j*2)+2;
        ptrp[j+1].nbvert[0]=(j*2)+3;

        ptrp[j+1].Tex[0][3]=(j*2);
        ptrp[j+1].Tex[0][2]=(j*2)+1;
        ptrp[j+1].Tex[0][1]=(j*2)+2;
        ptrp[j+1].Tex[0][0]=(j*2)+3;



        j += 2;
    }
    
    /*
    glEnd();
    glBegin(GL_QUADS);
    */
    /*
    for (i=0, j=0; i<count; ++i) 
    {
        
        for (int k=0; k<4; ++k) {
            
            glTexCoord2f(texcoords[j+k].x,texcoords[j+k].y);
            glVertex3f(vertices[j+k].x,vertices[j+k].y,vertices[j+k].z);
        }
        j += 4;
    }
    */
    /*
    glEnd();
    
      
        glDisable(GL_TEXTURE_2D);
        
          glDisable(GL_ALPHA_TEST);
          glPopMatrix();
          
    */  
}



int Leaves::getPolygonCount() const 
{
    return count * 2 * 2;
}

int Leaves::getLeafCount() const 
{
    return count;
}
