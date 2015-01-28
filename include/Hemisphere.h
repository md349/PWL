#ifndef HEMISPHERE_H
#define HEMISPHERE_H

#include <ngl/Vec3.h>
#include <ngl/BBox.h>
#include "GTon.h"
#include "Surfel.h"
#include "Triangle.h"

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

      //ray trace hem gammatons
      void propagate(std::vector <Triangle> _triInfo);

      //repeat trace after initial impact
      void repeatProp(std::vector <Triangle> _triInfo);

      //transfer data between surfel and gammaton
      void transfer(std::vector <Surfel> _surf);

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
