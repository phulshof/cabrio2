//
// A quad (4-sided polygon) to display on screen.
//
#ifndef CABRIO_QUAD_HPP_
#define CABRIO_QUAD_HPP_

#include <string>

#include "Image.hpp"

class Quad {
  public:
    Quad();
    Quad(std::string path);
    ~Quad();


    float x;
    float y;
    float z;
    float size_x;
    float size_y;
    float rotation_x;
    float rotation_y;
    float rotation_z;
    float alpha;

    Image *texture();
    void texture(Image *i);
    void texture(std::string path);

  private:
    Image *image;
};

#endif
