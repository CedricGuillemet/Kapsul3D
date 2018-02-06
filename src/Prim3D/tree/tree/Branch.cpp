#include "stdafx.h"

#include "Branch.h"

//#include <thigs/util.h>

#include "Tree.h"
#include "Branches.h"
#include "Leaves.h"



Branch::Branch(const Tree& tree, 
               Branches& branches,
               Leaves& leaves,
               BranchNoise* bn) : lower(0), upper(0), left(0), right(0) 
{
    
    build(tree, branches, leaves, bn, ident_matrix_f, 0.0f, 0.0f, 0.9f, 0,0);
    
    // build stump
    
    int facets = branches.facets;
    double radius = tree.branch_radius;
    
    for (int i=0; i<(facets+1); ++i) 
    {
        
        double t = 1.0/facets*i;
        Vertex g(branches.geom[i]);
        
        Vertex n(g.x, g.y, 0.5f);
        Vertex v(g.x*radius*1.5, g.y*radius*1.5, -0.5);
        Vertex tc(t, -radius-0.5,0);
        
        branches.addIndex(lower[i]);
        branches.addIndex(branches.add(n,tc,v));
    }
    
}



Branch::Branch(const Tree& tree,
               Branches& branches,
               Leaves& leaves,
               BranchNoise* bn,
               const CKMatrix& mat,
               double texcoord_y,
               double twist,
               double decay,
               int level,
               int StartInd) 
               : lower(0), upper(0), left(0), right(0) 
{
    
    build(tree, branches, leaves, bn, mat, texcoord_y, twist, decay, level,StartInd);
}


void Branch::build(const Tree& tree,
                   Branches& branches,
                   Leaves& leaves,
                   BranchNoise* bn,
                   const CKMatrix& mat,
                   double texcoord_y,
                   double twist,
                   double decay,
                   int level,
                   int StartInd) 
{
    
    int facets = branches.facets;
    double radius = tree.branch_radius;
    
    lower = new int[facets+1];
    upper = new int[facets+1];
    
    
    double branch_angle = tree.branch_angle;
    double branch_angle_bias = tree.branch_angle_bias;
    double branch_twist = twist + tree.branch_twist;
    
    BranchNoise* left_bn = bn->getLeft();
    BranchNoise* right_bn = bn->getRight();
    
    double left_branch_noise = ((left_bn->branch_noise * 0.3) - 0.1)*tree.branch_noise;
    double right_branch_noise = ((right_bn->branch_noise * 0.3) - 0.1)*tree.branch_noise;
    
    double left_radius = sqrtf(1.0 - branch_angle)+left_branch_noise;
    left_radius = clamp(left_radius, 0.0f, 1.0f);
    double left_angle = branch_angle * 90.0 * branch_angle_bias;
    
    double right_radius = sqrtf(branch_angle)+right_branch_noise;
    right_radius = clamp(right_radius, 0.0f, 1.0f);
    double right_angle = (1.0 - branch_angle) * -90.0 * branch_angle_bias;
    
    double taper = max(left_radius, right_radius);
    
    
    int ind,ind2;
    
    ind2=branches.vertices.size();
    
    for (int i=0; i<(facets+1); i++) 
    {
        
        double t = 1.0/facets*i;
        Vertex g(branches.geom[i]);
        
        Vertex n(transformNormal(Vertex(g.x, g.y, 0.0f), mat));
        Vertex v(transformPoint(Vertex(g.x*radius, g.y*radius, radius), mat));
        Vertex tc(t, texcoord_y,0);
        
        lower[i] = branches.add(n,tc,v);
    }
    
    texcoord_y += 1.0-2*radius;
    
    /* build cylinder upper */
    
    if ((StartInd>0)&&(ind2!=StartInd))
    {
        for (int i=0; i<=(facets-1); i++) 
        {
            
            branches.myfaces.push_back(Face(StartInd+i,StartInd+1+i,ind2+i));
            
            branches.myfaces.push_back(Face(ind2+i+1,ind2+i,StartInd+i+1));
            
        }
    }
    
    ind=branches.vertices.size();
    
    for (i=0; i<(facets+1); i++) 
    {
        
        double t = 1.0/facets*i;
        Vertex g(branches.geom[i]);
        
        Vertex n(transformNormal(Vertex(g.x, g.y, 0.0f), mat));
        Vertex v(transformPoint(Vertex(g.x*radius*taper, g.y*radius*taper, 1.0-radius), mat));
        Vertex tc(t, texcoord_y,0);
        
        upper[i] = branches.add(n,tc,v);
    }
    
    
    texcoord_y += 2*radius;
    
    if (ind2!=ind)
    for (i=0; i<=(facets); i++) 
    {
        
        branches.myfaces.push_back(Face(ind2+i,ind2+1+i,ind+i));
        
        branches.myfaces.push_back(Face(ind+i+1,ind+i,ind2+i+1));
        
    }
    
    
    /* build matricies */
    
    CKMatrix translate_mat = translate(0.0f, 0.0f, 1.0f) * mat;
    
    double s = sin(degToRad(branch_twist));
    double c = cos(degToRad(branch_twist));
    
    CKMatrix left_mat = 
        scale(left_radius, left_radius, left_radius) *
        rotate(Vertex(s, c, 0.0f), degToRad(left_angle)) *
        translate_mat;
    
    double left_decay = left_radius*decay;
    
    if (((level+1)>=tree.depth) || (left_decay<tree.leaf_threshhold)) 
    {
        
        leaves.addLeaf(left_mat);
        
    } 
    else 
    {
        
        left = new Branch(tree, branches, 
            leaves, 
            left_bn, 
            left_mat, 
            texcoord_y,
            branch_twist,
            left_decay,
            level+1,ind);
    }
    
    
    CKMatrix right_mat = 
        scale(right_radius, right_radius, right_radius) *
        rotate(Vertex(s, c, 0.0f), degToRad(right_angle)) *
        translate_mat;
    
    double right_decay = right_radius*decay;
    
    if (((level+1)>=tree.depth) || (right_decay<tree.leaf_threshhold)) 
    {
        
        leaves.addLeaf(right_mat);
        
    } 
    else 
    {
        
        right = new Branch(tree,
            branches,
            leaves,
            right_bn,
            right_mat,
            texcoord_y,
            branch_twist,
            right_decay,
            level+1,ind);
    }
    
    for (i=0; i<facets+1; ++i) 
    {
        
        branches.addIndex(upper[i]);
        branches.addIndex(lower[i]);
    }
    
    if (right) 
    {
        
        for (i=0; i<facets+1; ++i) 
        {
            
            branches.addIndex(right->lower[i]);
            branches.addIndex(upper[i]);
        }
    }
    
    if (left) 
    {
        
        for (i=0; i<facets+1; ++i) 
        {
            
            branches.addIndex(left->lower[i]);
            branches.addIndex(upper[i]);
        }
    }
    
}  

Branch::~Branch()
{
    
    delete left;
    delete right;
    
    delete [] lower;
    delete [] upper;
}
