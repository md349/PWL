#include "Surfel.h"
#include <ngl/Random.h>
#include <iostream>

namespace pwl
{
  Surfel::Surfel()
  {
    //std::cout<<"Surfel successfully constructed\n";
  }

  void Surfel::setup(ngl::Vec3 _position, ngl::Vec3 _rayStart)
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

    //set ray end point
    m_rayStart = _rayStart;

    //set node info
    m_right = -1;
    m_left = -1;
  }

  Surfel::~Surfel()
  {
    //std::cout<<"Surfel destructed\n";
  }

}
