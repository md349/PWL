#ifndef VERTICAL_H
#define VERTICAL_H

#include "GTon.h"
#include <ngl/Vec3.h>
#include <ngl/BBox.h>

namespace pwl
{
  class Vertical
  {
    public:
      //constructor
      Vertical();
      //destructor
      ~Vertical();

      //create vertical emitter
      void create(ngl::BBox _bbox, int _numGtons);

      //propagate the GTons in space.
      void propagate();

      std::vector <GTon> getVertical() { return m_gammatons; }

    private:
      //vector of Gamma Tons
      std::vector <GTon> m_gammatons;
  };
}
#endif // VERTICAL_H
