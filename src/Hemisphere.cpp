#include "Hemisphere.h"
#include <iostream>
#include <math.h>

namespace pwl
{

  const float PI = 3.141592653589793238462643383279502884197;

  //constructor
  Hemisphere::Hemisphere()
  {
    std::cout<<"Hemisphere successfully constructed\n";
  }

  //this code has been derived from http://www.cplusplus.com/forum/general/65476/
  //and been modified to work in this system.
  void Hemisphere::create(ngl::BBox _bbox, int _numGtons)
  {

    m_radius = _bbox.depth()*2;

    ngl::Vec3 centre = _bbox.center();

    for(float phi = 0.0; phi < (float)_numGtons/(float)100; phi += PI/10.0)
    {
      for(float theta = 0.0; theta < PI; theta += PI/10.0)
      {
        ngl::Vec3 position;
        position[0] = m_radius * cos(phi) * sin(theta) + centre[0];
        position[1] = m_radius * sin(phi) * sin(theta) + centre[1];
        position[2] = m_radius * cos(theta) + centre[0];
        m_hemisphere.push_back(position);
      }
    }

    int count = 0;
    unsigned int index = 0;
    //add gammatons to the vertices of the hemisphere
    while(count != _numGtons)
    {
      //if we have hit the end of the hemisphere loop back around
      if(index == m_hemisphere.size())
      {
        index = 0;
      }
      //create gammaton set position and add to vector
      else
      {
        pwl::GTon gt;
        ngl::Vec3 position;
        position[0] = m_hemisphere[index][0];
        position[1] = m_hemisphere[index][1];
        position[2] = m_hemisphere[index][2];
        gt.setup(position);
        m_gammatons.push_back(gt);
        //increase count and index for next gammaton.
        ++count;
        ++index;
      }
    }
  }

  void Hemisphere::propagate(std::vector <Triangle> _triInfo)
  {
    //go through each gammaton
    for(unsigned int i = 0; i < m_gammatons.size(); ++i)
    {
      //create the ray end.
      ngl::Vec3 rayEnd = m_gammatons[i].getPos();
      m_gammatons[i].propagate(rayEnd, _triInfo);
    }
  }

  void Hemisphere::transfer(std::vector <Surfel> _surf)
  {

  }

  void Hemisphere::repeatProp(std::vector <Triangle> _triInfo)
  {

  }

  //destructor
  Hemisphere::~Hemisphere()
  {
    std::cout<<"Hemisphere destructed\n";
  }
}
