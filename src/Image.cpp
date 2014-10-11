//
// Class for loading images form files.
//
#include "Image.hpp"
#include "Logger.hpp"

Logger& logger = Logger::get_instance();

Image::Image() {
  logger.log(LOG_DEBUG, "New Image()");
  image_data = NULL;
}

Image::Image(std::string path) {
  logger.log(LOG_DEBUG, "New Image(" + path + ")");
  image_data = NULL;

  logger.log(LOG_DEBUG, "Loading image from " + path);
  image_data = IMG_Load(path.c_str());
}

Image::~Image() {
  SDL_FreeSurface(image_data);
  image_data = NULL;
}
