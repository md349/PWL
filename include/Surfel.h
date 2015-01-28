#ifndef SURFEL_H
#define SURFEL_H

#include <ngl/Vec3.h>
#include "Triangle.h"

namespace pwl
{
  class Surfel
  {
    public:
      //constructor
      Surfel();
      //destructor
      ~Surfel();

      //setup initial surfel properties.
      void setup(ngl::Vec3 _position, ngl::Vec3 _rayEnd);

      //returns surfel position
      inline ngl::Vec3 getPos() { return m_pos; }
      //update surfel position
      inline void updatePos(ngl::Vec3 _newPos) { m_pos = _newPos; }

      //returns Ray start point
      inline ngl::Vec3 getRayStart() { return m_rayStart; }

      //returns whether we have intersected or not
      inline bool getIntersect() { return m_intersect; }
      //update intersect bool
      inline void updateInt(bool _newBool) { m_intersect = _newBool; }

      //returns surfels child nodes. returns -1 if it is a leaf node
      int getRightChildIndex() { return m_right; }
      int getLeftChildIndex() { return m_left; }

    private:
      //properties of a surfel
      //gamma reflectance
      //decide how incident gammatons react.
      float m_deltaS; //deterioration rate for Ks
      float m_deltaP; //deterioration rate for Kp
      float m_deltaF; //deterioration rate for Kf

      //material properties
      float m_sh; //humidity
      float m_sd; //dirt
      float m_sf; //fungus is not implemented yet

      ngl::Vec3 m_pos; //surfel position also ray start

      bool m_intersect; //intersected or not?

      //Rays start from the center of obj
      ngl::Vec3 m_rayStart;

      //index for nodes right and left of this surfel in kd-tree
      int m_right;
      int m_left;
  };
}
#endif // SURFEL_H
