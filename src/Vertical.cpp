#include "Vertical.h"
#include "Halton.h"
#include <iostream>
#include <ngl/Random.h>

namespace pwl
{
  Vertical::Vertical()
  {
    std::cout<<"Vertical successfully constructed\n";
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

  void Vertical::propagate()
  {
    for(unsigned int i = 0; i < m_gammatons.size(); ++i)
    {
      m_gammatons[i].propagateVert();
    }
  }

  Vertical::~Vertical()
  {
    std::cout<<"Vertical destructed\n";
  }
}
