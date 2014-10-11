//
// Class for loading images form files.
//
#ifndef CABRIO_IMAGE_HPP_
#define CABRIO_IMAGE_HPP_

#include <string>
#include "SDL.h"
#include "SDL_image.h"

class Image {
  public:
    Image();
    ~Image();
    Image(std::string path);

  private:
    SDL_Surface *image_data;
};

#endif
