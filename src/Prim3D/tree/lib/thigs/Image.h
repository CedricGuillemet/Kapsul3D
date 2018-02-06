#ifndef Image_INCLUDED
#define Image_INCLUDED

#pragma warning( disable : 4800 ) 
#pragma warning( disable : 4786 )

#include <string>
using std::string;

#include <math.h>
#include <windows.h>
#include <ptr/Ptr.h>

#include <thigs/Color.h>

struct Image {

  Image();
  Image(int height, int width);
  ~Image();

  void setSize(int height, int width);
  inline int width() const {return the_width;}
  inline int height() const {return the_height;}

  // fast and unsafe
  inline unsigned long& index(int y, int x) {return data[x + the_width*y];}
  inline unsigned long index(int y, int x) const {return data[x + the_width*y];}

  inline PackedRGBA indexByInt(int y, int x) const {
    if (x<0 || x>=the_width || y<0 || y>=the_height) {
      return 0x00000000;
    } else {
      return data[x + the_width*y];
    }
  }

  inline PackedRGBA indexByNormal(double y, double x) {
    double i = (x + 1.0) * (the_width-1.0) / 2.0;
    double j = (y + 1.0) * (the_height-1.0) / 2.0;
    return indexByDouble(j,i);
  }

  inline PackedRGBA indexByDouble(double y, double x) const {

    int left = floor(x);
    int right = left+1;
    int bottom = floor(y);
    int top = bottom+1;

    double vf = top - y;   // vertical factor
    double hf = right - x;  // horizontal factor

    PackedRGBA bl(indexByInt(bottom, left));
    PackedRGBA tl(indexByInt(top, left));
    PackedRGBA br(indexByInt(bottom, right));
    PackedRGBA tr(indexByInt(top, right));

    double blf = vf*hf;
    double tlf = (1.0-vf)*hf;
    double brf = vf*(1.0-hf);
    double trf = (1.0-vf)*(1.0-hf);

    return bl*blf + br*brf + tl*tlf + tr*trf;
  }

  inline unsigned long* operator[](int i) {
    assert(i>=0 && i<the_height);
    return data + the_width*i;
  }

  Ptr<Image> stretch(int height, int width) const;
  Ptr<Image> contract(int height, int width) const;
  Ptr<Image> resize(int height, int width) const;

  Ptr<Image> powerOfTwo() const;
  Ptr<Image> mip() const;

 private:

  void clear();
  
  int the_width;
  int the_height;
  unsigned long* data;

  // only PNG supported so far
  friend Ptr<Image> readPNGFile(const char*);
  friend Ptr<Image> readPNGResource(const char*);
  friend Ptr<Image> checker(int height, int width, int sy, int sx);

};

struct PNG_Error {

  PNG_Error(const char* m) : message(m) {};

  string message;
};


#endif



