#ifndef TEXTURE_H
#define TEXTURE_H

#include <vector>
#include <ngl/Vec3.h>
#include <ngl/Vec4.h>
#include "Surfel.h"

namespace pwl
{
  class Texture
  {
    public:
      //constructor
      Texture(int _width, int _height, std::string _name);
      //destructor
      ~Texture();

      //generate texture
      void generateTexture(std::vector <Surfel *> _data, std::vector <ngl::Vec2> _uv);

    private:

      //work out 2D coords
      ngl::Vec2 get2DNormCoords(ngl::Vec2 _coords);

      //vector to hold colours
      ngl::Vec4 m_darkRust;
      ngl::Vec4 m_lightRust;
      ngl::Vec4 m_dirt;

      //width and height of the image
      unsigned int m_width;
      unsigned int m_height;

      //name of image file
      std::string m_pngName;
  };
}
#endif // TEXTURE_H
