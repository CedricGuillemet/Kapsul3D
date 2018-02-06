#ifndef Png_INCLUDED
#define Png_INCLUDED

#pragma warning( disable : 4786 ) 
#pragma warning( disable : 4800 ) 

#include <assert.h>

#include <map>
#include <string>

using std::map;
using std::string;

#include <lpng/png.h>

struct Png {

  Png(const char* file_name);
  ~Png();

  operator bool();  // valid image

  void warning(const char*);
  void error(const char*);

private:

  static void error_callback(png_structp, png_const_charp);
  static void warning_callback(png_structp, png_const_charp);

  png_structp png_ptr;
  png_infop info_ptr;
  png_infop end_info;

  FILE* fp;
  unsigned long* data;
  unsigned long** rows;

  string file_name;

  typedef map<png_structp, Png*> PngMap;
  static PngMap* png_map;

public:

  struct Init {
    Init() {
      if (count++==0) {
	Png::png_map = new PngMap();
      }
    }
    ~Init() {
      if (--count==0) {
	assert(png_map->size()==0);
	delete Png::png_map;
      }
    }
    static int count;
  };

  friend struct Init;
};

static Png::Init png_init;

#endif
