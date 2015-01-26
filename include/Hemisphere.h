#ifndef HEMISPHERE_H
#define HEMISPHERE_H

#include <ngl/Vec3.h>
#include <ngl/BBox.h>
#include "GTon.h"

namespace pwl
{
  class Hemisphere
  {
    public:
      //constructor
      Hemisphere();
      //destructor
      ~Hemisphere();

      //place gammatons into a hemisphere
      void create(ngl::BBox _bbox, int _numGtons);

      void propagate(ngl::BBox _bbox);

      std::vector <GTon> getHem() { return m_gammatons; }

    private:

      //radius for the hemisphere
      float m_radius;

      //vector to hold gammatons
      std::vector <GTon> m_gammatons;

      //vector for hemisphere structure
      std::vector <ngl::Vec3> m_hemisphere;
  };
}
#endif // HEMISPHERE_H
