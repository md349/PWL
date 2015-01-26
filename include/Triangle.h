#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <ngl/Vec3.h>

//From Jon Macey's Ray-Triangle Collision Demo.
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

      //method to check for ray-triangle intersection
      void rayTriangleIntersect(ngl::Vec3 _rayStart, ngl::Vec3 _rayEnd);

      //returns true or false if the ray has intersected a triangle
      bool getIntersectBool();

      //returns hitpoint so position can be updated
      ngl::Vec3 getHitPoint();

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
  };
}
#endif // TRIANGLE_H
