#include "Surfel.h"
#include <ngl/Random.h>
#include <iostream>

namespace pwl
{
  Surfel::Surfel()
  {
    //std::cout<<"Surfel successfully constructed\n";
  }

  void Surfel::setup(ngl::Vec3 _position)
  {
    //FOR NOW deterioration rates are random
    //deterioration rates should conform with material
    ngl::Random *rand=ngl::Random::instance();
    m_deltaS = rand->randomPositiveNumber(1);
    m_deltaP = rand->randomPositiveNumber(1);
    m_deltaF = rand->randomPositiveNumber(1);

    //we assume the model is pristine
    m_sh = 0;
    m_sd = 0;
    m_sf = 0;

    //set surfel position based on halton sequence
    m_pos = _position;

    //boolean whether we have intersected with the object or not
    m_intersect = false;

    //set node info
    m_right = -1;
    m_left = -1;
  }

  void Surfel::propagate(ngl::Vec3 _bboxCentre, std::vector <Triangle> _triInfo)
  {
    //centre is an ngl::Vec3 fot the centre of BBox
    ngl::Vec3 rayEnd = _bboxCentre;

    //loop through triangles and see if we hit anything
    for(unsigned int i = 0; i < _triInfo.size(); ++i)
    {
      _triInfo[i].rayTriangleIntersect(m_pos,rayEnd);
      bool intersect = _triInfo[i].getIntersectBool();
      if(intersect == true)
      {
        m_intersect = true;
        m_pos = _triInfo[i].getHitPoint();
      }
    }

  }

  Surfel::~Surfel()
  {
    //std::cout<<"Surfel destructed\n";
  }

}
