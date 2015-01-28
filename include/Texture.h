#ifndef TEXTURE_H
#define TEXTURE_H

#include <vector>
#include <ngl/Vec3.h>

namespace pwl
{
  class Texture
  {
    public:
      //constructor
      Texture();
      //destructor
      ~Texture();

      void generateTexture(std::vector <ngl::Vec3> _pos);

    private:
  };
}
#endif // TEXTURE_H
