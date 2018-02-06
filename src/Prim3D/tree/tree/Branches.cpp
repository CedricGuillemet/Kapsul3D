#include "stdafx.h"
#include "Branches.h"

//static const double PI = 3.141592653589;

extern "C"
{
    extern CKTexture *treeTex;
}

Branches::Branches( int f) :  facets(f) 
{
    geom = new Vertex[facets+1];
    
    for (int i=0; i<facets+1; ++i) {
        
        double u = 1.0/facets*i;
        
        double s = sinf(PI*2.0*u);
        double c = cosf(PI*2.0*u);
        
        geom[i] = Vertex(c, s,0);
    }
}


Branches::~Branches() 
{
    //delete [] geom;
}


int Branches::add(const Vertex& n, const Vertex& tc, const Vertex& v) 
{
    int index = vertices.size();
    //  assert((normals.size()==index)&&(texcoords.size()==index));
    
    vertices.push_back(v);
    normals.push_back(n);
    texcoords.push_back(tc);
    
    return index;
}

void Branches::addIndex(int i) 
{
    indecies.push_back(i);
}

void Branches::draw(CKMesh *daTronc,Vertex *Center)
{
    int size = indecies.size();
    int stride = (facets+1)*2;
/*    
    glColor4f(1,1,1,0);
    glEnable(GL_DEPTH_TEST);
    
    glPushMatrix();
    
    glScalef(100,100,100);
    
    glEnable(GL_TEXTURE_2D);
    
    treeTex->Bind();

    glBegin(GL_TRIANGLES);
*/    
    
    daTronc->AllocatePoly(((myfaces.size()-2)/2),vertices.size());
	daTronc->AllocateUV(0,vertices.size());
    Vertex *ptrv;
    CKPolygon *ptrp;
    ptrp=daTronc->pl;
    ptrv=daTronc->pv;
    
/*
    for (int i=0;i<myfaces.size();i+=2)
    {
        
        int i1,i2,i3;
        
        i1=myfaces[i].nbvert[0];
        i2=myfaces[i].nbvert[1];
        i3=myfaces[i].nbvert[2];
        
        glTexCoord2f(texcoords[i1].x,texcoords[i1].y);
        glVertex3f(vertices[i1].x,vertices[i1].y,vertices[i1].z);
        
        glTexCoord2f(texcoords[i2].x,texcoords[i2].y);
        glVertex3f(vertices[i2].x,vertices[i2].y,vertices[i2].z);
        
        glTexCoord2f(texcoords[i3].x,texcoords[i3].y);
        glVertex3f(vertices[i3].x,vertices[i3].y,vertices[i3].z);
        
    }
    */

    for (int i=0;i<(myfaces.size()-2)/2;i++)
    {
		ptrp[i].Allocate(daTronc,1,4);
        ptrp[i].nbvert[0]=myfaces[(i*2)].nbvert[0];
		ptrp[i].nbvert[1]=myfaces[(i*2)].nbvert[1];
		ptrp[i].nbvert[3]=myfaces[(i*2)].nbvert[2];
		ptrp[i].nbvert[2]=myfaces[(i*2)+1].nbvert[0];

        ptrp[i].Tex[0][0]=ptrp[i].nbvert[0];
		ptrp[i].Tex[0][1]=ptrp[i].nbvert[1];
		ptrp[i].Tex[0][2]=ptrp[i].nbvert[2];
		ptrp[i].Tex[0][3]=ptrp[i].nbvert[3];

    }


    for (i=0;i<vertices.size();i++)
    {
        ptrv[i]=((vertices[i]*100.0f)+(*Center));
        daTronc->puv[0][i].u=texcoords[i].x;
        daTronc->puv[0][i].v=texcoords[i].y;
    }

    /*
    glEnd();
    
    glPopMatrix();
    
    glDisable(GL_TEXTURE_2D);
    */
}


int Branches::getPolygonCount() const {
    
    int stride = (facets+1)*2;
    int cyl_count = indecies.size()/stride;
    return cyl_count * facets * 2;
}


int Branches::getBranchCount() const {
    
    int stride = (facets+1)*2;
    int cyl_count = indecies.size()/stride;
    return (cyl_count+1) / 2;
}

