#ifndef Leaves_INCLUDED
#define Leaves_INCLUDED

#pragma warning( disable : 4786 )
#pragma warning( disable : 4305 )

#include <vector>
using std::vector;
#include "branchnoise.h"

struct Leaves {

  Leaves(int facets, double radius);

  void addLeaf(const CKMatrix&);

  void draw(CKMesh *daLeaf,Vertex *Center);

  int getPolygonCount() const;
  int getLeafCount() const;
  double center_height;
  double radius;
  int facets;
  int count;

  vector<Vertex> vertices;
  vector<Vertex> normals;
  vector<Vertex> colors;
  vector<Vertex> texcoords;

  Random random;
  inline double rand() {
    return random * 0.5 + 0.5;
  }
};

#endif
