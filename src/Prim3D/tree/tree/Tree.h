#ifndef Tree_INCLUDED
#define Tree_INCLUDED

#pragma warning( disable : 4244 )
#pragma warning( disable : 4305 )

#include "Branch.h"

#include "Leaves.h"
#include "Branches.h"


struct __declspec( dllexport ) Tree {

  Tree();
  ~Tree();

  void draw( bool wireframe = false);
  void build(CKMesh *daTronc,CKMesh *daLeaf,Vertex *Center);

  void newCharacter();

  void setWire(bool);

  void setLeafSize(const double&);
  void setBranchSize(const double&);
  void setBranchNoise(const double&);
  void setThreshhold(const double&);
  void setBranchBias(const double&);
  void setBranch(const double&); 
  void setTwist(const double&);

  int depth;
  int branch_facets;
  double branch_radius;

  double leaf_size;
  double branch_size;
  double branch_noise;      // between 0 and 1
  double branch_angle_bias; // between 0 and 1
  double branch_angle; // between 0 and 1
  double branch_twist; // between 0 and 180
  double leaf_threshhold;
    vector<Face> MeshFaces;
  bool wireframe_flag;

  bool geometry_dirty;

  Leaves* leaves;
  Branches* branches;
  BranchNoise* bn; // per branch data structure
};


#endif