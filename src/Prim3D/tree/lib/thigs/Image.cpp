#include "Image.h"


#include <GL/gl.h>
#include <lpng/png.h>
#include <util/util.h>

Image::Image() : data(0), the_width(0), the_height(0) {}

Image::Image(int h, int w) : data(0) {

  setSize(h, w);

}

Image::~Image() {

  delete data;
}

void Image::setSize(int h, int w) {

  delete data;
  the_width = w;
  the_height = h;
  data = new unsigned long[the_width*the_height];
}


void Image::clear() {

  int data_size = the_height*the_width;
  for (int i = 0; i<data_size; ++i) data[i] = 0;
}


bool isPowerOfTwo(unsigned long num) {

  int s = 0;
  for (int i = 0; i<32; ++i) {
    s += (0x00000001 & num);
    if (s>1) return false;
    num = num >> 1;
  }
  return true;
}


Ptr<Image> Image::mip() const {

  if (!isPowerOfTwo(the_width) || !isPowerOfTwo(the_height)) return 0;

  int new_width = the_width/2;
  int new_height = the_height/2;

  if (new_width==0 && new_height>0) new_width = 1;
  if (new_height==0 && new_width>0) new_height = 1;

  if (new_width==0 && new_height==0) return 0;


  Ptr<Image> new_image = new Image(new_height, new_width);

  // there's probably an easier way to do this

  for (int y = 0; y<new_height; ++y) {
    for (int x = 0; x<new_width; ++x) {

      PackedRGBA colors[4];
      colors[0] = index(y*2,   x*2);
      colors[1] = index(y*2+1, x*2);
      colors[2] = index(y*2,   x*2+1);
      colors[3] = index(y*2+1, x*2+1);

      unsigned long component[4];
      for (int i=0; i<4; ++i) component[i] = 0x00000000;

      for (int j=0; j<4; ++j) {
	for (int i=0; i<4; ++i) {
	  component[j] += colors[i][j];
	}
      }

      for (i=0; i<4; ++i) component[i] = component[i] >> 2;

      new_image->index(y,x) = PackedRGBA(component[0],
					 component[1],
					 component[2],
					 component[3]);
    }
  }

  return new_image;
}


Ptr<Image> Image::powerOfTwo() const {

  // for now stretches instead of shrinks

  unsigned long old_width = the_width;
  unsigned long old_height = the_height;
  
  unsigned long new_width = 0x80000000; // no image is this big
  unsigned long new_height = 0x80000000; // no image is this big

  if (isPowerOfTwo(old_width)) {
    new_width = old_width;
  } else {
    while (!(old_width & new_width)) new_width = new_width >> 1;
    new_width = new_width << 1; // power of two bigger, not smaller
  }

  if (isPowerOfTwo(old_height)) {
    new_height = old_height;
  } else {
    while (!(old_height & new_height)) new_height = new_height >> 1;
    new_height = new_height << 1; // power of two bigger, not smaller
  }

  if ((old_height == new_height) && (old_width == new_width)) {
    return Ptr<Image>(const_cast<Image*>(this));
  }

  return stretch(new_height, new_width);
}


Ptr<Image> Image::stretch(int new_height, int new_width) const {

  assert(new_width>=the_width && new_height>=the_height);

  Ptr<Image> new_image = new Image(new_height, new_width);

  double dx = double(the_width - 1) / double(new_width - 1);
  double dy = double(the_height - 1) / double(new_height - 1);

  for (int y = 0; y<new_height; ++y) {
    for (int x = 0; x<new_width; ++x) {
      (*new_image)[y][x] = indexByDouble(dy*y, dx*x);
    }
  }

  return new_image;
}


static void png_error_callback(png_structp, png_const_charp message) {

  PNG_Error error(message);
  throw (error);

  //  throw(PNG_Error(message));
}

static void png_warning_callback(png_structp, png_const_charp message) {

  showWarning(message);
}


Ptr<Image> readPNGFile(const char* file_name) {

  // fuck Microsoft

  if (!file_name || !file_name[0]) {
    showWarning("openImageFile: null file name");
    return 0;
  }

  FILE* fp = fopen(file_name, "rb");

  if (!fp) {
    string message(file_name);
    message.append(": ");
    message.append(strerror(errno));
    showWarning(message.c_str());
    return 0;
  }

  const int advance = 8;
  unsigned char header[advance];
  int bytes_read = fread(header, sizeof(char), advance, fp);
  if (bytes_read != advance) {
    fclose(fp);
    string message(file_name);
    message.append(": not an image file");
    showWarning(message.c_str());
    return 0;
  }

  bool is_png = png_check_sig(header, advance);
  if (!is_png) {
    fclose(fp);
    string message(file_name);
    message.append(": not a PNG image");
    showWarning(message.c_str());
    return 0;
  }

  png_structp png_ptr;
  png_infop info_ptr;
  png_infop end_info;

  unsigned long** rows;
  Ptr<Image> image;

  try {

    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
				     NULL,
				     png_error_callback,
				     png_warning_callback);

    if (!png_ptr) {
      string message(file_name);
      message.append(": png_create_read_struct failed to return valid png_ptr");
      showWarning(message.c_str());
      return 0;
    }

    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
      string message(file_name);
      message.append(": png_create_read_struct failed to return valid info_ptr");
      showWarning(message.c_str());
      return 0;
    }

    end_info = png_create_info_struct(png_ptr);
    if (!end_info) {
      string message(file_name);
      message.append(": png_create_read_struct failed to return valid end_info");
      showWarning(message.c_str());
      return 0;
    }

    png_init_io(png_ptr, fp);

    png_set_sig_bytes(png_ptr, advance);

    png_read_info(png_ptr, info_ptr);

    png_uint_32 width, height;
    int bit_depth, color_type, interlace_type;
  
    png_get_IHDR(png_ptr, info_ptr, 
		 &width, 
		 &height, 
		 &bit_depth, 
		 &color_type,
		 &interlace_type, NULL, NULL);


    png_set_strip_16(png_ptr);
    png_set_packing(png_ptr);

    if (color_type == PNG_COLOR_TYPE_PALETTE)
      png_set_expand(png_ptr);

    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
      png_set_expand(png_ptr);

    if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
      png_set_expand(png_ptr);

    if (bit_depth == 16)
      png_set_strip_16(png_ptr);

    // in theory this has no effect if the image contains an alpha channel
    if (bit_depth == 8 && color_type == PNG_COLOR_TYPE_RGB)
      png_set_filler(png_ptr, 0xff, PNG_FILLER_AFTER);

    rows = new unsigned long*[height];
    image = Ptr<Image>(new Image(height, width));

    unsigned long* ptr = image->data;
    for (int row = 0; row<height; ++row) {

      rows[height-row-1] = ptr;
      ptr+=width;
    }

    png_read_image(png_ptr, reinterpret_cast<unsigned char**>(rows));

    png_read_end(png_ptr, info_ptr);

  }

  catch (const PNG_Error& error) {

    string message(file_name);
    message.append(": ");
    message.append(error.message);
    showWarning(message.c_str());

    png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) NULL);
    delete rows;
    fclose(fp);
    return 0;
  }

  delete rows;

  fclose(fp);

  return image;
}


static map<png_structp, png_bytep> src_ptrs;

static void scan_png(png_structp png_ptr,
		     png_bytep data, unsigned int length) {

  png_bytep src = src_ptrs[png_ptr];
  memcpy(data, src, length);
  src_ptrs[png_ptr] = src + length;
}


Ptr<Image> readPNGResource(const char* resource_name) {

  HRSRC hrsrc = FindResource(0, resource_name, "PNG");
  if (hrsrc==0) {
    showLastError(resource_name);
    return 0;
  }

  HGLOBAL resource = LoadResource(0, hrsrc);
  if (resource==0) {
    showLastError(resource_name);
    return 0;
  }

  png_bytep data = reinterpret_cast<png_bytep>(LockResource(resource));
  assert(data);

  const int advance = 8;
  bool is_png = png_check_sig(data, advance);

  if (!is_png) {
    FreeResource(resource);
    string message(resource_name);
    message.append(": not a PNG image");
    showWarning(message.c_str());
    return 0;
  }

  png_structp png_ptr;
  png_infop info_ptr;
  png_infop end_info;

  unsigned long** rows;
  Ptr<Image> image;

  try {

    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
				     NULL,
				     png_error_callback,
				     png_warning_callback);

    if (!png_ptr) {
      string message(resource_name);
      message.append(": png_create_read_struct failed to return valid png_ptr");
      showWarning(message.c_str());
      return 0;
    }

    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
      string message(resource_name);
      message.append(": png_create_read_struct failed to return valid info_ptr");
      showWarning(message.c_str());
      return 0;
    }

    end_info = png_create_info_struct(png_ptr);
    if (!end_info) {
      string message(resource_name);
      message.append(": png_create_read_struct failed to return valid end_info");
      showWarning(message.c_str());
      return 0;
    }

    src_ptrs[png_ptr] = data+advance;
    png_set_read_fn(png_ptr, 0, &scan_png);

    png_set_sig_bytes(png_ptr, advance);

    png_read_info(png_ptr, info_ptr);

    png_uint_32 width, height;
    int bit_depth, color_type, interlace_type;
  
    png_get_IHDR(png_ptr, info_ptr, 
		 &width, 
		 &height, 
		 &bit_depth, 
		 &color_type,
		 &interlace_type, NULL, NULL);


    png_set_strip_16(png_ptr);
    png_set_packing(png_ptr);

    if (color_type == PNG_COLOR_TYPE_PALETTE)
      png_set_expand(png_ptr);

    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
      png_set_expand(png_ptr);

    if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
      png_set_expand(png_ptr);

    if (bit_depth == 16)
      png_set_strip_16(png_ptr);

    // in theory this has no effect if the image contains an alpha channel
    if (bit_depth == 8 && color_type == PNG_COLOR_TYPE_RGB)
      png_set_filler(png_ptr, 0xff, PNG_FILLER_AFTER);

    rows = new unsigned long*[height];
    image = Ptr<Image>(new Image(height, width));

    unsigned long* ptr = image->data;
    for (int row = 0; row<height; ++row) {

      rows[height-row-1] = ptr;
      ptr+=width;
    }

    png_read_image(png_ptr, reinterpret_cast<unsigned char**>(rows));

    png_read_end(png_ptr, info_ptr);

  }

  catch (const PNG_Error& error) {

    string message(resource_name);
    message.append(": ");
    message.append(error.message);
    showWarning(message.c_str());

    png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) NULL);
    delete rows;
    FreeResource(resource);
    return 0;
  }

  delete rows;

  FreeResource(resource);

  return image;
}




  
Ptr<Image> checker(int h, int w, int sy, int sx) {

  Ptr<Image> image = new Image(w, h);

  for (int i=0; i<image->height(); ++i) {

    for (int j=0; j<image->width(); ++j) {

      (*image)[i][j] = ((i/sy + j/sx)%2)?0xffffff:0xff000000;
    }
  }

  return image;
}
