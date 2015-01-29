#include "Hemisphere.h"
#include <iostream>
#include <math.h>

#include <ngl/Random.h>

namespace pwl
{

  const float PI = 3.141592653589793238462643383279502884197;

  //constructor
  Hemisphere::Hemisphere()
  {
    //std::cout<<"Hemisphere successfully constructed\n";
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

  void Hemisphere::propagate(std::vector <Triangle> _triInfo, ngl::Vec3 _rayStart)
  {
    //go through each gammaton
    for(unsigned int i = 0; i < m_gammatons.size(); ++i)
    {
      //send to check to each tri
      m_gammatons[i].propagate(_rayStart, _triInfo);
    }
  }

  void Hemisphere::transfer(std::vector <Surfel *> _surf)
  {
    //for each gammaton we have see if we should react with surfels
    for(unsigned int j = 0; j < m_gammatons.size(); ++j)
    {
      //decide how many surfels we react with
      ngl::Random *rand = ngl::Random::instance();
      //change the number divised by to alter severity of weathering
      int toReact = rand->randomPositiveNumber(_surf.size()/rand->randomPositiveNumber(150));

      //if the GTon hit we react if not move on
      if(m_gammatons[j].getIntersect())
      {
        //for the amount we decide to affect select random surfels in the surfel vector
        for(int i = 0; i < toReact; ++i)
        {
           //get the current Surfel we want to interact with
           float currentSurfel = rand->randomPositiveNumber(_surf.size());

           //get gammaton carrier attributes
           ngl::Vec2 ca = m_gammatons[j].getCA();
           //get surfel material properties
           ngl::Vec2 mp = _surf[currentSurfel]->getMP();

           //do interaction
           //alter surfel
           //we should never get over 1.
           if(mp[0] > 1)
           {
             mp[0] = 1;
           }
           else
           {
            mp[0] = mp[0] + 0.4 * ca[0];
           }
           if(mp[1] > 1)
           {
             mp[1] = 1;
           }
           else
           {
             mp[1] = mp[1] + 0.5 * ca[1];
           }

           //update surfel
           _surf[currentSurfel]->updateMP(mp);

           //alter GTon
           //randomly select whether gammaton loses or gains.
           int gainLose = rand->randomPositiveNumber(2);
           //lose
           if (gainLose == 0)
           {
             //check for less than 0
             if(ca[0] - mp[0] < 0)
             {
               ca[0] = 0;
             }
             else
             {
               ca[0] = ca[0] - mp[0];
             }
             if(ca[1] - mp[0] < 0)
             {
               ca[1] = 0;
             }
             else
             {
               ca[1] = ca[1] -  mp[1];
             }
             //update GTon
             m_gammatons[j].updateCA(ca);
           }
           //gain
           else if (gainLose == 1)
           {
             //check for over 1
             if(ca[0] + mp[0] > 1)
             {
               ca[0] = 1;
             }
             else
             {
               ca[0] = ca[0] + mp[0];
             }
             if(ca[1] + mp[1] > 1)
             {
               ca[1] = 1;
             }
             else
             {
               ca[1] = ca[1] + mp[0];
             }
             //update GTon
             m_gammatons[j].updateCA(ca);
           }
        }
      }
    }
  }


  //destructor
  Hemisphere::~Hemisphere()
  {
   //std::cout<<"Hemisphere destructed\n";
  }
}
