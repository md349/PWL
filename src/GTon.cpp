#include "GTon.h"
#include <ngl/Random.h>
#include <iostream>

namespace pwl
{
  GTon::GTon()
  {
    //std::cout<<"GTon successfully constructed\n";
  }

  void GTon::setup(ngl::Vec3 _position)
  {
    //work out a random value for each motion probabilities
    //ks+kp+kf <= 1
    ngl::Random *rand=ngl::Random::instance();
    m_ks = rand->randomPositiveNumber(1);
    m_kp = rand->randomPositiveNumber(1-m_ks);
    m_kf = rand->randomPositiveNumber(1-(m_ks+m_kp));

    //assign values for carrier attributes
    m_sh = rand->randomPositiveNumber(10); //change input to alter weathering effect
    m_sd = rand->randomPositiveNumber(10);
    m_sf = 0; //fungus not implemented right now.

    //set other attributes
    m_pos = _position; //position
    m_setProb = 1-m_ks-m_kp-m_kf; //probability of settling is 1-ks-kp-kf
    m_intersect = false; //initially we have not intersected with anything
  }

  void GTon::propagate(ngl::Vec3 _rayEnd, std::vector <Triangle> _triInfo)
  {
    for(unsigned int i = 0; i < _triInfo.size(); ++i)
    {
      if(!m_intersect)
      {
        _triInfo[i].rayTriangleIntersect(m_pos, _rayEnd);
        bool check = _triInfo[i].getIntersectBool();
        //std::cout<<"check : "<<check<<" loop num : "<<i<<"\n";
        if(check)
        {
          m_pos = _triInfo[i].getHitPoint();
          m_intersect = true;
          break;
        }
      }
    }
    if(!m_intersect)
    {
      //m_pos = _rayEnd;
    }
  }

  GTon::~GTon()
  {
    //std::cout<<"GTon destructed\n";
  }
}
