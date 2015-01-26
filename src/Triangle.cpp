#include "Triangle.h"
#include <ngl/Util.h>


//From Jon Macey's Ray-Triangle Collision Demo.
//Modified for this project.
//This is a Moller-Trumbore method
namespace pwl
{
  Triangle::Triangle()
  {

  }

  Triangle::Triangle(ngl::Vec3 _p0, ngl::Vec3 _p1, ngl::Vec3 _p2)
  {
    //set default values
    m_u = 0;
    m_v = 0;
    m_w = 0;
    m_v0 = _p0;
    m_v1 = _p1;
    m_v2 = _p2;
    //calc edges
    m_edge1 = m_v1 - m_v0;
    m_edge2 = m_v2 - m_v0;
    //centre of tri is 3 verts averaged
    m_centre = (m_v0 + m_v1 + m_v2)/3.0;
    m_hit = false;
  }

  void Triangle::rayTriangleIntersect(ngl::Vec3 _rayStart, ngl::Vec3 _rayEnd)
  {
    m_hit = false;
    //calc ray direction
    ngl::Vec3 dir = _rayEnd - _rayStart;

    ngl::Vec3 tvec, pvec, qvec;
    float det, inv_det;

    //get vector of edge1
    pvec = dir.cross(m_edge2);
    //calculate the determinant
    det = m_edge1.dot(pvec);
    //if 0 we have no hit
    if(det > - 0.00001f && det < 0.00001)
    {
      return;
    }

    //get inverse determinant
    inv_det = 1.0f / det;
    //calc second vector
    tvec = _rayStart - m_v0;
    //get dot product of this and invesere determinant
    m_u = tvec.dot(pvec) * inv_det;
    //if out of range 0-1 no hit
    if(m_u < -0.001f || m_u > 1.001f)
    {
      return;
    }

    //check second vector edge
    qvec = tvec.cross(m_edge1);
    //get dot product
    m_v = dir.dot(qvec) * inv_det;
    //if out of range 0-1 no hit
    if(m_v < -0.001f || m_u + m_v > 1.001f)
    {
      return;
    }

    //check final value
    m_w = m_edge2.dot(qvec) * inv_det;
    //if less than 0 no hit
    if(m_w <= 0)
    {
      return;
    }

    //otherwise we are inside the triangle
    //we can get the hit point.

    //calculate the normal
    ngl::Vec3 norm = ngl::calcNormal(m_v0, m_v1, m_v2);
    float a = -norm.dot(tvec);
    float b = norm.dot(dir);
    float r = a/b;
    //work out the intersection point of ray and change the hit bool
    m_hitPoint = _rayStart + r * dir;
    m_hit = true;
  }

  ngl::Vec3 Triangle::getHitPoint()
  {
    return m_hitPoint;
  }

  bool Triangle::getIntersectBool()
  {
    return m_hit;
  }

  Triangle::~Triangle()
  {

  }
}















