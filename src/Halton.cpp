#include "Halton.h"
#include <math.h>
#include <iostream>

namespace pwl
{
  Halton::Halton()
  {
    std::cout<<"Halton successfully constructed\n";
  }

  //derived from pseudocode on wikipedia
  void Halton::doSequence(float _xRadius, float _zRadius, int _index, int _base1, int _base2)
  {
      //convert the radius to diameter
      _xRadius = _xRadius * 2;
      _zRadius = _zRadius * 2;
      //do halton sequence and store in a vector
      float hal = (float)1/(float)_base1;
      float hal2 = (float)1/(float)_base2;
      for(int i = 0; i < _index; ++i)
      {
        ngl::Vec3 element (hal,0,hal2);
        hal = (float)hal/(float)_base1;
        hal2 = (float)hal2/(float)_base2;
        m_finalSequence.push_back(element);
      }

      /** Print out halton sequence
      for(unsigned int i = 0; i < m_finalSequence.size(); ++i)
      {
        std::cout<<"["<<m_finalSequence[i][0]<<", "<<m_finalSequence[i][1]<<", "<<m_finalSequence[i][2]<<"]\n";
      }
      **/
  }

  void Halton::doSequenceBB(float _radius1, float _radius2, int _index, int _base1, int _base2, const int _id)
  {
    //convert radius to diameter
    _radius1 = _radius1 * 2;
    _radius2 = _radius2 * 2;
    //do halton sequence and store in a vector
    float hal = (float)_radius1/(float)_base1;
    float hal2 = (float)_radius2/(float)_base2;
    for(int i = 0; i < _index; ++i)
    {
      switch(_id)
      {
        //top or bottom
        case 1 :
        {
          ngl::Vec3 tbElement (hal,0,hal2);
          hal = (float)hal/(float)_base1;
          hal2 = (float)hal2/(float)_base2;
          m_finalSequence.push_back(tbElement);
          break;
        }
        //front or back
        case 2 :
        {
          ngl::Vec3 fbElement (hal,hal2,0);
          hal = (float)hal/(float)_base1;
          hal2 = (float)hal2/(float)_base2;
          m_finalSequence.push_back(fbElement);
          break;
        }
        //left or right
        case 3 :
        {
          ngl::Vec3 lrElement (0,hal,hal2);
          hal = (float)hal/(float)_base1;
          hal2 = (float)hal2/(float)_base2;
          m_finalSequence.push_back(lrElement);
          break;
        }
      }
    }

    /** Print function for halton sequences
    for(unsigned int i = 0; i < m_finalSequence.size(); ++i)
    {
      std::cout<<"["<<m_finalSequence[i][0]<<", "<<m_finalSequence[i][1]<<", "<<m_finalSequence[i][2]<<"]\n";
    }
    std::cout<<"\n";
    **/

  }

  Halton::~Halton()
  {

  }
}



