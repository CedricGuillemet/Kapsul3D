#include "stdafx.h"
#include <math.h>

#include "Tree.h"



//#include <thigs/util.h>

//static const double PI = 3.141592653589;
/*
void Tree::setBarkTexture(const Ptr<Texture>& t) {
  bark_texture = t;
  bark_texture->repeatVertical(true);
  geometry_dirty = true;
}

void Tree::setLeafTexture(const Ptr<Texture>& t) {
  leaf_texture = t;
  geometry_dirty = true;
}

void Tree::setWire(bool w) {

  wireframe_flag = w;
}

void Tree::setLeafBackTexture(const Ptr<Texture>& t) {
  leaf_back_texture = t;
  geometry_dirty = true;
}

*/
/*
void Tree::newCharacter() {

  delete bn;
  bn = new BranchNoise();
  geometry_dirty = true;
}
*/

Tree::Tree()
{
    depth=31;
    bn=new BranchNoise();
    leaf_threshhold=0.5;
    branch_angle_bias=0.75;
    branch_angle=0.7;
    branch_twist=60.0;
    branch_noise=0.5;
    leaves=0;
    branches=0;
    leaf_size=0.5;
    branch_radius=0.5;

    wireframe_flag=true;
    geometry_dirty=true;

//    build();
}


void Tree::build(CKMesh *daTronc,CKMesh *daLeaf,Vertex *Center) 
{
    geometry_dirty = false;

    delete leaves;
    leaves = new Leaves( 7, leaf_size);
    delete branches;
    branches = new Branches( 6);

    Branch branch(*this, *branches, *leaves, bn);

    leaves->draw(daLeaf,Center);
    branches->draw(daTronc,Center);

}


Tree::~Tree() {

  delete leaves;
  delete branches;
  delete bn;
}



void Tree::draw( bool wireframe_flag) {

//  build();
  glEnable(GL_DEPTH_TEST);

}


void Tree::setLeafSize(const double& r) {

  leaf_size = r;
  geometry_dirty = true;
  return ;
}


void Tree::setBranchSize(const double& r) {

  branch_radius = r;
  geometry_dirty = true;
  return ;
}


void Tree::setThreshhold(const double& a) {

  leaf_threshhold = a;
  geometry_dirty = true;
  return ;
}

void Tree::setBranchNoise(const double& n) {

  branch_noise = n;
  geometry_dirty = true;
  return ;
}


void Tree::setBranchBias(const double& a) {

  branch_angle_bias = a;
  geometry_dirty = true;
  return ;
}


void Tree::setBranch(const double& a) {

  branch_angle = a;
  geometry_dirty = true;
  return ;
}


void Tree::setTwist(const double& a) {

  branch_twist = a;
  geometry_dirty = true;
  return ;
}


