//
// A quad (4-sided polygon) to display on screen.
//
#include "Quad.hpp"

Quad::Quad() {
  image = NULL;
}

Quad::~Quad() {
  if ( image ) {
    delete image;
  }
}

Image *Quad::texture() {
  return image;
}

void Quad::texture(Image *i) {
  image = i;
}

void Quad::texture(std::string path) {
  Image *i = new Image(path);
  image = i;
}
