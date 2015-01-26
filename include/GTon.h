#ifndef GTON_H
#define GTON_H

#include <ngl/Vec3.h>

namespace pwl
{
  class GTon
  {
    public:
      //constructor
      GTon();
      //destructor
      ~GTon();

      //sets all initial data for gamma ton
      void setup(ngl::Vec3 _position);

      //returns surfel position
      ngl::Vec3 getPos() { return m_pos; }
      //update surfel position
      void updatePos(ngl::Vec3 _newPos) { m_pos = _newPos; }

      //returns whether we have intersected or not
      bool getIntersect() { return m_intersect; }
      //update intersect bool
      void updateInt(bool _newBool) { m_intersect = _newBool; }

      //initial propagate for vertical
      void propagateVert();

      //initial propagate for Hemisphere
      void propagateHem(ngl::Vec3 _bboxCentre);

     private:

        //motion probabilities
        float m_ks; //probability of propagating along a straight line
        float m_kp; //probability of propagating along a parabolic curve
        float m_kf; //probability of flowing

        //carrier attributes
        float m_sh; //humidity
        float m_sd; //dirt
        float m_sf; //fungus

        //other
        ngl::Vec3 m_pos; //position
        float m_setProb; //probability of settling
        bool m_intersect; //indicator of intersection
  };

}
#endif // GTON_H
