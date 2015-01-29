#include "BBox.h"
#include "Halton.h"
#include <ngl/Random.h>
#include <algorithm>
#include <iostream>

namespace pwl
{
  BBox::BBox()
  {
    //std::cout<<"BBox successfully constructed\n";
  }

  void BBox::create(ngl::BBox _bbox, int _numSurfels, ngl::Vec3 _rayStart)
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
      //get position from halton sequence
      ngl::Vec3 position; //= top.getHSeq(i);
      //edit height so it is above object
      position[0] = rand->randomNumber(length);
      position[1] = height;
      position[2] = rand->randomNumber(width);
      //setup surfel
      pwl::Surfel *surf = new pwl::Surfel;
      surf->setup(position, _rayStart);
      //add to vector
      m_surfels.push_back(surf);
    }

    //bottom
    //Halton bottom;
    //bottom.doSequenceBB(_xRadius, _zRadius, _numSurfels, 2, 3, 1);
    //create surfels for bottom face
    for(int i = 0; i < _numSurfels; ++i)
    {
      //get position from halton sequence
      ngl::Vec3 position; //= bottom.getHSeq(i);
      //edit so it is below object
      position[0] = rand->randomNumber(length);
      position[1] = -height;
      position[2] = rand->randomNumber(width);
      //setup surfel
      pwl::Surfel *surf = new pwl::Surfel;
      surf->setup(position, _rayStart);
      //add to vector
      m_surfels.push_back(surf);
    }

    //front
    //Halton front;
    //front.doSequenceBB(_xRadius, _yRadius, _numSurfels, 2, 3, 2);
    //create surfels for front face
    for(int i = 0; i < _numSurfels; ++i)
    {
      //get position from halton sequence
      ngl::Vec3 position; //= front.getHSeq(i);
      //edit so it is in front of object
      position[0] = rand->randomNumber(length);
      position[1] = rand->randomNumber(height);
      position[2] = length;
      //setup surfel
      pwl::Surfel *surf = new pwl::Surfel;
      surf->setup(position,_rayStart);
      //add to vector
      m_surfels.push_back(surf);
    }

    //back
    //Halton back;
    //back.doSequenceBB(_xRadius, _yRadius, _numSurfels, 2, 3, 2);
    //create surfels for back face
    for(int i = 0; i < _numSurfels; ++i)
    {
      //get position from halton sequence
      ngl::Vec3 position; //= back.getHSeq(i);
      //edit so it is behind object
      position[0] = rand->randomNumber(length);
      position[1] = rand->randomNumber(height);
      position[2] = -length;
      //setup surfel
      pwl::Surfel *surf = new pwl::Surfel;
      surf->setup(position, _rayStart);
      //add to vector
      m_surfels.push_back(surf);
    }

    //left
    //Halton left;
    //left.doSequenceBB(_yRadius, _zRadius, _numSurfels, 2, 3, 3);
    //create surfels for left face
    for(int i = 0; i < _numSurfels; ++i)
    {
      //get position from halton sequence
      ngl::Vec3 position; // = left.getHSeq(i);
      //edit so it is left of object
      position[0] = -width;
      position[1] = rand->randomNumber(height);
      position[2] = rand->randomNumber(width);
      //setup surfel
      pwl::Surfel *surf = new pwl::Surfel;
      surf->setup(position, _rayStart);
      //add to vector
      m_surfels.push_back(surf);
    }

    //right
    //Halton right;
    //right.doSequenceBB(_yRadius, _zRadius, _numSurfels, 2, 3, 3);
    //create surfels for right face
    for(int i = 0; i < _numSurfels; ++i)
    {
      //get position from halton sequence
      ngl::Vec3 position; //= right.getHSeq(i);
      //edit so it is right of object
      position[0] = width;
      position[1] = rand->randomNumber(height);
      position[2] = rand->randomNumber(width);
      //setup surfel
      pwl::Surfel *surf = new pwl::Surfel;
      surf->setup(position, _rayStart);
      //add to vector
      m_surfels.push_back(surf);
    }
  }

  void BBox::goToSurface(std::vector <Triangle> _triInfo)
  {
    //loop through all surfels
    for(unsigned int i = 0; i < m_surfels.size(); ++i)
    {
      //for each surfel check all triangles
      for(unsigned int j= 0; j < _triInfo.size(); ++j)
      {
        //if the surfel has not intersected with anything check next tri
        if(m_surfels[i]->getIntersect() == false)
        {
          _triInfo[j].rayTriangleIntersect(m_surfels[i]->getRayStart(), m_surfels[i]->getPos());
          bool hit = _triInfo[j].getIntersectBool();
          //if the surfel has hit this time update position and break
          if(hit)
          {
            m_surfels[i]->updateInt(true);
            m_surfels[i]->updatePos(_triInfo[j].getHitPoint());
          }
          //if we have reached the end of the tri vector and we still haven't hit then we don't hit
          else if (i == _triInfo.size()-1 && !hit)
          {
            //default position
            m_surfels[i]->updatePos(ngl::Vec3(1,1,1));
          }
        }
      }

      //reset the triangle. Vital...do not delete. I learnt the hard way!
      for(unsigned int k = 0; k < _triInfo.size(); ++k)
      {
        _triInfo[k].reset();
      }
    }
  }

  bool sortFunc(pwl::Surfel *i, pwl::Surfel *j)
  {
    ngl::Vec3 tempi = i->getPos();
    ngl::Vec3 tempj = j->getPos();

    return (tempi[0]>tempj[0]);
  }

  //derived from pseudocode on wikipedia
  void BBox::setKdTree(int _depth)
  {
    /**
      int k = 3; //using Vec3 therefore will always be 3 dimensional
      int axis = _depth % k;

      for(unsigned int i = 0; i < m_surfels.size(); ++i)
      {
        ngl::Vec3 t = m_surfels[i].getPos();
        std::cout<<"["<<t[0]<<", "<<t[1]<<", "<<t[2]<<"]\n";
      }

      std::cout<<"sorting by x pos...\n";
      std::sort(m_surfels.begin(), m_surfels.end(), sortFunc);
      std::cout<<"sorted!\n";

      //choose median
      unsigned int median = m_surfels.size() / 2;

      for(unsigned int i = 0; i < m_surfels.size(); ++i)
      {
        ngl::Vec3 t = m_surfels[i].getPos();
        std::cout<<"["<<t[0]<<", "<<t[1]<<", "<<t[2]<<"]\n";
      }

      //print function
      std::cout<<"surfel postion : ["<<pos[0]<<", "<<pos[1]<<", "<<pos[2]<<"]\n";
      **/
  }

  BBox::~BBox()
  {
    //std::cout<<"BBox destructed\n";
  }
}
