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

  void GTon::propagateVert()
  {
    //counting variable
    float t = 0.0f;
    //we want to go down
    ngl::Vec3 destination;
    destination[0] = m_pos[0];
    destination[1] = 0;
    destination[2] = m_pos[2];

    //keep moving until we intersect
    while(!m_intersect)
    {
      //update position
      m_pos = (m_pos * (1 - t) + destination * t);
      if(m_pos[1] < 0 || m_pos[1] > 0)
      {
        t += 0.01f;
      }
      else
      {
        m_intersect = true;
      }
    }
  }

  void GTon::propagateHem(ngl::Vec3 _bboxCentre)
  {
    //increase t to interpolate
    float t = 0.0f;
    //centre is an ngl::Vec3 fot the centre of BBox
    ngl::Vec3 destination = _bboxCentre;

    /**
    while(!m_intersect)
    {
      //pwl::Intersect intr;
      m_pos = (m_pos * (1 - t) + destination * t);
      if()
      {
        m_intersect = true;
      }
      else
      {
        t += 0.01f;
      }
    }**/
  }

  GTon::~GTon()
  {
    //std::cout<<"GTon destructed\n";
  }
}
