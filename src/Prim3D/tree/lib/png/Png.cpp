
#include <png/Png.h>

#include <xutility>
using std::pair;

#include <util/util.h>


Png::PngMap* Png::png_map = 0;
int Png::Init::count = 0;

Png::Png(const char* file_name) 
  : data(0), png_ptr(NULL), info_ptr(NULL), end_info(NULL) {

  pair<PngMap::iterator, bool> success = 
    png_map->insert(PngMap::value_type(png_ptr, this));
  assert(success.second);

  fp = fopen(file_name, "rb");
  if (!fp) {
    string message(file_name);
    message.append(": ");
    message.append(strerror(errno));
    showWarning(message.c_str());
    return;
  }

  const int num = 8;
  unsigned char header[num];
  int bytes_read = fread(header, sizeof(char), num, fp);
  if (bytes_read != num) {
    fclose(fp);
    fp = 0;
    string message(file_name);
    message.append(": not a PNG image");
    showWarning(message.c_str());
    return;
  }

  bool is_png = png_check_sig(header, num);
  if (!is_png) {
    fclose(fp);
    fp = 0;
    string message(file_name);
    message.append(": not a PNG image");
    showWarning(message.c_str());
    return;
  }

  png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
				   NULL,
				   &Png::error_callback,
				   &Png::warning_callback);
  if (!png_ptr) {
    showWarning("png_create_read_struct: ");
    return;
  }

  info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr) {
    showWarning("png_create_info_struct: ");
    return;
  }

  end_info = png_create_info_struct(png_ptr);
  if (!end_info) {
    showWarning("png_create_info_struct: ");
    return;
  }

  png_init_io(png_ptr, fp);

  png_set_sig_bytes(png_ptr, 8);

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

  rows = new unsigned long*[height];
  data = new unsigned long[height*width];

  unsigned long* ptr = data;
  for (int row = 0; row<height; ++row) {

    rows[row] = ptr;
    ptr+=width;
  }

  png_read_image(png_ptr, reinterpret_cast<unsigned char**>(rows));

  png_read_end(png_ptr, info_ptr);

  fclose(fp);
}


Png::~Png() {

  delete rows;
  delete data;

  if (png_ptr) {
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    png_ptr = 0;
  }

  PngMap::iterator i = png_map->find(png_ptr);
  assert(i!=png_map->end());
  png_map->erase(i);

}

void Png::error_callback(png_structp png_ptr, png_const_charp message) {

  PngMap::iterator i = png_map->find(png_ptr);
  assert(i!=png_map->end());
  (*i).second->error(message);
}


void Png::error(const char* m) {

  string message(file_name);
  message.append(": ");
  message.append(m);
  showError(message.c_str());
}


void Png::warning_callback(png_structp png_ptr, png_const_charp message) {

  PngMap::iterator i = png_map->find(png_ptr);
  assert(i!=png_map->end());
  (*i).second->warning(message);
}


void Png::warning(png_const_charp m) {

  string message(file_name);
  message.append(": ");
  message.append(m);
  showWarning(message.c_str());
}


Png::operator bool() {

  return png_ptr && info_ptr && end_info;
}
