#ifndef BranchNoise_INCLUDED
#define BranchNoise_INCLUDED

//#include <windows.h>

//#include <thigs/Random.h>
struct Random {

  explicit Random(double s = 1.0) : seed(s) {}

  operator double();

 private:

  double seed;

  static const double a;
  static const double m;
};

inline Vertex transformPoint(const Vertex& v, const CKMatrix m) {

  return Vertex(v.x*m.mat[0] + v.y*m.mat[4] + v.z*m.mat[8] + m.mat[12],
		 v.x*m.mat[1] + v.y*m.mat[5] + v.z*m.mat[9] + m.mat[13],
		 v.x*m.mat[2] + v.y*m.mat[6] + v.z*m.mat[10] + m.mat[14]);
}

inline Vertex transformNormal(const Vertex& v, const CKMatrix m) {

  return Vertex(v.x*m.mat[0] + v.y*m.mat[4] + v.z*m.mat[8],
		 v.x*m.mat[1] + v.y*m.mat[5] + v.z*m.mat[9],
		 v.x*m.mat[2] + v.y*m.mat[6] + v.z*m.mat[10]);
}


inline CKMatrix translate(const Vertex& vec) {

  return CKMatrix (1.0, 0.0, 0.0, 0.0,
                0.0, 1.0, 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                vec.x, vec.y, vec.z, 1.0);
}

inline CKMatrix translate(double x,double y,double z) {

  return CKMatrix (1.0, 0.0, 0.0, 0.0,
                0.0, 1.0, 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                x, y, z, 1.0);
}


inline CKMatrix scale(double x, double y,double z) {

  return CKMatrix (     x,    0.0,    0.0, 0.0,
                0.0,      y,    0.0, 0.0,
                0.0,    0.0,      z, 0.0,
                0.0,    0.0,    0.0, 1.0);
}

inline CKMatrix scale(const Vertex& vec) {

  return CKMatrix
    (vec.x,    0.0,    0.0, 0.0,
        0.0, vec.y,    0.0, 0.0,
        0.0,    0.0, vec.z, 0.0,
        0.0,    0.0,    0.0, 1.0);
}

/*
inline Matrix scale(double s) {

  return Matrix(     s,    0.0,    0.0, 0.0,
                 0.0,      s,    0.0, 0.0,
                 0.0,    0.0,      s, 0.0,
                 0.0,    0.0,    0.0, 1.0);
}
*/
inline CKMatrix scale(double s) {

  return CKMatrix
    (     s,    0.0,    0.0, 0.0,
        0.0,      s,    0.0, 0.0,
        0.0,    0.0,      s, 0.0,
        0.0,    0.0,    0.0, 1.0);
}


static const CKMatrix ident_matrix_f =
CKMatrix( 1.0f, 0.0f, 0.0f, 0.0f,
		      0.0f, 1.0f, 0.0f, 0.0f,
		      0.0f, 0.0f, 1.0f, 0.0f,
		      0.0f, 0.0f, 0.0f, 1.0f );


inline CKMatrix operator*(const CKMatrix& a, 
				 const CKMatrix& b) {

  CKMatrix result;
  
  for (int i=0; i<4; ++i) {

    for (int j=0; j<4; ++j) {

      double s = 0;
      for (int k=0; k<4; ++k) {

	    s += a.mat[i*4+k] * b.mat[k*4+j];
      }
      result.mat[i*4+j] = s;
    }
  }
  return result;
}

inline void quat(const Vertex& axis, double angle,double *q) {

  //Vec4<double> q;

  double length = sin(angle/2.0);

  double r =
    axis.x*axis.x+
    axis.y*axis.y+
    axis.z*axis.z;

  if (r==0.0) {
    //q = Vec4<double>(0.0,0.0,0.0,1.0);
      q[0]=0;
      q[1]=0;
      q[2]=0;
      q[3]=1;
  } else {
/*
    q = Vec4<double>(axis[0]*length, 
		     axis[1]*length,
		     axis[2]*length, 
		     cos(angle/2.0));
             */
      q[0]=axis.x*length;
      q[1]=axis.y*length;
      q[2]=axis.z*length;
      q[3]=cos(angle/2.0);
  }

  //return q;
}

/*
template <class T>
inline T clamp(T a, T min, T max) {

  if (a<min) return min;
  if (a>max) return max;
  return a;
}
*/
inline double clamp(double a,double min,double max)
{
  if (a<min) return min;
  if (a>max) return max;
  return a;

}
static const double pi = 3.14159265358979323846;
inline double degToRad(double d) {return d * pi / 180.0;}
//inline double degToRad(double d) {return d * double(pi) / 180.0f;}

inline CKMatrix rotate(const Vertex& axis, double angle) {

  double q[4];
  quat(axis, angle,q);
    double x=q[0];
    double y=q[1];
    double z=q[2];
    double w=q[3];

  return CKMatrix
    (1.0 + 2.0 * (-y*y - z*z),
	     2.0 * ( x*y + w*z),
	     2.0 * ( x*z - w*y),
	     0.0,
     2.0 * ( x*y - w*z),
	     1.0 + 2.0 * (-x*x - z*z),
	     2.0 * ( y*z + w*x),
	     0.0,
     2.0 * ( x*z + w*y),
	     2.0 * ( y*z - w*x),
	     1.0 + 2.0 * (-x*x - y*y),
	     0.0,
     0.0, 0.0, 0.0, 1.0);
}


inline Random::operator double() {
const double a = 16807.0;
const double m = 2147483647.0;

    double t = a * seed;
    seed = t - m * floor(t/m);

    return seed/m;
}

struct BranchNoise {

  BranchNoise();
  ~BranchNoise();

  double branch_noise;

  BranchNoise* getLeft();  // deleted when parent is deleted
  BranchNoise* getRight();

 private:

  BranchNoise* left;
  BranchNoise* right;

  static Random random;

};
  

#endif
