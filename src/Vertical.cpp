#include "Vertical.h"
#include "Halton.h"
#include <iostream>
#include <ngl/Random.h>

namespace pwl
{
  Vertical::Vertical()
  {
    //std::cout<<"Vertical successfully constructed\n";
  }

  void Vertical::create(ngl::BBox _bbox, int _numGtons)
  {

      ngl::Random *rand=ngl::Random::instance();

      float height = _bbox.height() + 3;
      float width = _bbox.width();
      float length = _bbox.depth();

      //create Halton Sequence
      //Halton h;
      //h.doSequence(_xRadius, _zRadius, _numGtons, 2, 3);

      for(int i = 0; i < _numGtons; ++i)
      {
        pwl::GTon gt;
        //get position from halton sequence
        //ngl::Vec3 position = h.getHSeq(i);
        //edit height value to fit with emitter
        ngl::Vec3 position;
        position[0] = rand->randomNumber(width);
        position[1] = height;
        position[2] = rand->randomNumber(length);
        //setup gammatons
        gt.setup(position);
        //add to vector
        m_gammatons.push_back(gt);
      }

      std::cout<<"gamma ton vector created\n";
      std::cout<<"gamma ton vector size : "<<m_gammatons.size()<<"\n";
  }

 void Vertical::propagate(std::vector <Triangle> _triInfo)
  {
    for(unsigned int i = 0; i < m_gammatons.size(); ++i)
    {
      //get gammaton position
      ngl::Vec3 rayEnd = m_gammatons[i].getPos();
      //we want to travel downwards, set rayEnd for y = 0
      rayEnd[1] = 0;
      m_gammatons[i].propagate(rayEnd, _triInfo);
    }
  }

 void Vertical::transfer(std::vector<Surfel *> _surf)
 {
   //In this version no ray tracing is used except the initial GTon and Surfel placement ray cast
   //Here we assume which surfels are affected by the gammaton tracing.

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

  Vertical::~Vertical()
  {
    //std::cout<<"Vertical destructed\n";
  }
}
