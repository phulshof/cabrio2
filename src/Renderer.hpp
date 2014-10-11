//
// Abstract class for all renderers.
//
#ifndef CABRIO_RENDERER_HPP_
#define CABRIO_RENDERER_HPP_

#include <vector>

#include "Quad.hpp"

class Renderer {
  public:
    Renderer();
    ~Renderer();

    void add_quad(Quad& q);

    virtual void init() = 0;
  private:
};

#endif
