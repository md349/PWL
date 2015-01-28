#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <ngl/Vec3.h>

//From Jon Macey's Ray-Triangle Collision Demo and wikipedia
//Modified for this project.
//This is a Moller-Trumbore method
namespace pwl
{
  class Triangle
  {
    public:
      //constructor
      Triangle();
      Triangle(ngl::Vec3 _p0, ngl::Vec3 _p1, ngl::Vec3 _p2);
      //destructor
      ~Triangle();

      inline ngl::Vec3 getV0() { return m_v0; }
      inline ngl::Vec3 getV1() { return m_v1; }
      inline ngl::Vec3 getV2() { return m_v2; }

      //method to check for ray-triangle intersection
      void rayTriangleIntersect(ngl::Vec3 _rayStart, ngl::Vec3 _rayEnd);

      void reset();

      //returns true or false ifthe ray has intersected a triangle
      inline bool getIntersectBool() { return m_hit; }

      //returns hitpoint so position can be updated
      inline ngl::Vec3 getHitPoint() { return m_hitPoint; }

      inline float getDepth() { return m_rayDepth; }

    private:
      //triangle vertices
      ngl::Vec3 m_v0;
      ngl::Vec3 m_v1;
      ngl::Vec3 m_v2;

      //two edges for triangle/ray calc
      ngl::Vec3 m_edge1;
      ngl::Vec3 m_edge2;

      //centre of tri
      ngl::Vec3 m_centre;

      //intersection flag
      bool m_hit;
      //u,v,w values fpr the calc of hit point
      ngl::Real m_u;
      ngl::Real m_v;
      ngl::Real m_w;
      //actual hit point of ray on tri...needed for surfel position
      ngl::Vec3 m_hitPoint;

      //holds rayDepth
      float m_rayDepth;

  };
}
#endif // TRIANGLE_H
