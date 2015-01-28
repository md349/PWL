#ifndef BBOX_H
#define BBOX_H
#include "Surfel.h"
#include "Triangle.h"
#include <ngl/Vec3.h>
#include <ngl/BBox.h>

namespace pwl
{
  class BBox
  {
    public:
      //constructor
      BBox();
      //destructor
      ~BBox();

      //create area for emitter
      void create(ngl::BBox _bbox, int _numSurfels, ngl::Vec3 _rayEnd);

      //propagate surfels to object surface.
      void goToSurface(std::vector <Triangle> _triInfo);

      //set surfel vector to a Kd Tree
      void setKdTree(int _depth);

      std::vector <Surfel *> getBBox() { return m_surfels; }

    private:

      //vector for surfels - convert to kdtree later
      std::vector <pwl::Surfel *> m_surfels;

      //kdtree container
      std::map <int, pwl::Surfel> m_surfKDT;
  };
}
#endif // BBOX_Hs
