#ifndef Branches_INCLUDED
#define Branches_INCLUDED

#pragma warning( disable : 4786)
#pragma warning( disable : 4305)

#include <vector>
using std::vector;
/*
#include <thigs/Vec3.h>
#include <thigs/Texture.h>
#include <thigs/Material.h>
#include <thigs/thigs.h>
*/
class Branches 
{
public:
  Branches( int facets);
  ~Branches();

  int add(const Vertex& n, const Vertex& tc, const Vertex& v);
  void addIndex(int);

  int getPolygonCount() const;
  int getBranchCount() const;

  void draw(CKMesh *daTronc,Vertex *Center);

  vector<Vertex> vertices;
  vector<Vertex> normals;
  vector<Vertex> texcoords;
  vector<Face> myfaces;

  vector<int> indecies;
  int facets;
  Vertex* geom;
};

#endif



