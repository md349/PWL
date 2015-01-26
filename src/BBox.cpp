#include "BBox.h"
#include "Halton.h"
#include <ngl/Random.h>
#include <algorithm>
#include <iostream>

namespace pwl
{
  BBox::BBox()
  {
    std::cout<<"BBox successfully constructed\n";
  }

  void BBox::create(ngl::BBox _bbox, int _numSurfels)
  {
    //we have six faces here so we need six halton sequences
    ngl::Random *rand=ngl::Random::instance();

    float width = _bbox.width();
    float length = _bbox.depth();
    float height = _bbox.height();

    //top
    //Halton top;
    //top.doSequenceBB(_xRadius, _zRadius, _numSurfels, 2, 3, 1);
    //create surfels for top face
    for(int i = 0; i < _numSurfels; ++i)
    {
      pwl::Surfel surf;
      //get position from halton sequence
      ngl::Vec3 position; //= top.getHSeq(i);
      //edit height so it is above object
      position[0] = rand->randomNumber(width);
      position[1] = height;
      position[2] = rand->randomNumber(length);
      //setup surfel
      surf.setup(position);
      //add to vector
      m_surfels.push_back(surf);
    }

    //bottom
    //Halton bottom;
    //bottom.doSequenceBB(_xRadius, _zRadius, _numSurfels, 2, 3, 1);
    //create surfels for bottom face
    for(int i = 0; i < _numSurfels; ++i)
    {
      pwl::Surfel surf;
      //get position from halton sequence
      ngl::Vec3 position; //= bottom.getHSeq(i);
      //edit height so it is above object
      position[0] = rand->randomNumber(width);
      position[1] = -height;
      position[2] = rand->randomNumber(length);
      //setup surfel
      surf.setup(position);
      //add to vector
      m_surfels.push_back(surf);
    }

    //front
    //Halton front;
    //front.doSequenceBB(_xRadius, _yRadius, _numSurfels, 2, 3, 2);
    //create surfels for front face
    for(int i = 0; i < _numSurfels; ++i)
    {
      pwl::Surfel surf;
      //get position from halton sequence
      ngl::Vec3 position; //= front.getHSeq(i);
      //edit height so it is above object
      position[0] = rand->randomNumber(width);
      position[1] = rand->randomNumber(height);
      position[2] = length;
      //setup surfel
      surf.setup(position);
      //add to vector
      m_surfels.push_back(surf);
    }

    //back
    //Halton back;
    //back.doSequenceBB(_xRadius, _yRadius, _numSurfels, 2, 3, 2);
    //create surfels for back face
    for(int i = 0; i < _numSurfels; ++i)
    {
      pwl::Surfel surf;
      //get position from halton sequence
      ngl::Vec3 position; //= back.getHSeq(i);
      //edit height so it is above object
      position[0] = rand->randomNumber(width);
      position[1] = rand->randomNumber(height);
      position[2] = -length;
      //setup surfel
      surf.setup(position);
      //add to vector
      m_surfels.push_back(surf);
    }

    //left
    //Halton left;
    //left.doSequenceBB(_yRadius, _zRadius, _numSurfels, 2, 3, 3);
    //create surfels for left face
    for(int i = 0; i < _numSurfels; ++i)
    {
      pwl::Surfel surf;
      //get position from halton sequence
      ngl::Vec3 position; // = left.getHSeq(i);
      //edit height so it is above object
      position[0] = -width;
      position[1] = rand->randomNumber(height);
      position[2] = rand->randomNumber(length);
      //setup surfel
      surf.setup(position);
      //add to vector
      m_surfels.push_back(surf);
    }

    //right
    //Halton right;
    //right.doSequenceBB(_yRadius, _zRadius, _numSurfels, 2, 3, 3);
    //create surfels for right face
    for(int i = 0; i < _numSurfels; ++i)
    {
      pwl::Surfel surf;
      //get position from halton sequence
      ngl::Vec3 position; //= right.getHSeq(i);
      //edit height so it is above object
      position[0] = width;
      position[1] = rand->randomNumber(height);
      position[2] = rand->randomNumber(length);
      //setup surfel
      surf.setup(position);
      //add to vector
      m_surfels.push_back(surf);
    }
  }

  bool sortFunc(pwl::Surfel i, pwl::Surfel j)
  {
    ngl::Vec3 tempi = i.getPos();
    ngl::Vec3 tempj = j.getPos();

    return (tempi[0]>tempj[0]);
  }

  void BBox::goToSurface(ngl::BBox _bbox, std::vector <Triangle> _triInfo)
  {
    for(unsigned int i = 0; i < m_surfels.size(); ++i)
    {
      m_surfels[i].propagate(_bbox.center(), _triInfo);
    }
  }

  //derived from pseudocode on wikipedia
  void BBox::setKdTree(int _depth)
  {
      int k = 3; //using Vec3 therefore will always be 3 dimensional
      int axis = _depth % k;

      /**
      for(unsigned int i = 0; i < m_surfels.size(); ++i)
      {
        ngl::Vec3 t = m_surfels[i].getPos();
        std::cout<<"["<<t[0]<<", "<<t[1]<<", "<<t[2]<<"]\n";
      }
      **/
      std::cout<<"sorting by x pos...\n";
      std::sort(m_surfels.begin(), m_surfels.end(), sortFunc);
      std::cout<<"sorted!\n";

      //choose median
      unsigned int median = m_surfels.size() / 2;

      /**
      for(unsigned int i = 0; i < m_surfels.size(); ++i)
      {
        ngl::Vec3 t = m_surfels[i].getPos();
        std::cout<<"["<<t[0]<<", "<<t[1]<<", "<<t[2]<<"]\n";
      }**/

      //print function
      //std::cout<<"surfel postion : ["<<pos[0]<<", "<<pos[1]<<", "<<pos[2]<<"]\n";
  }

  BBox::~BBox()
  {
    std::cout<<"BBox destructed\n";
  }
}
