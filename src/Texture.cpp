#include "Texture.h"
#include <iostream>
#include "lodepng/include/lodepng.h"
#include <ngl/Random.h>
#include <math.h>

namespace pwl
{
  Texture::Texture(int _width, int _height, std::string _name)
  {
    //set image size
    m_width = _width;
    m_height = _height;

    //set colours for dirt/rust
    m_lightRust = ngl::Vec4(247,68,24,255);
    m_darkRust = ngl::Vec4(165,93,53,255);
    m_dirt = ngl::Vec4(131,101,57,255);

    m_pngName = _name;
  }

  bool sortFunc(ngl::Vec2 i, ngl::Vec2 j)
  {
    return i[0] < j[0];
  }

  void Texture::generateTexture(std::vector <Surfel *> _data, std::vector<ngl::Vec2> _uv)
  {
    std::cout<<"Generating Texture\n";

    //work out surfel colour
    std::vector <ngl::Vec4> colour;
    std::vector <ngl::Vec2> position;

    //work out surfel
    for(unsigned int i = 0; i < _data.size(); ++i)
    {
      ngl::Vec2 mp = _data[i]->getMP();
      //decide whether we rust or make this section dirty
      //we have dirt
      ngl::Random *rand = ngl::Random::instance();
      int ran = rand->randomPositiveNumber(2);
      //dirt
      if(ran == 0)
      {
        colour.push_back(m_dirt);
      }
      //rust
      else if(ran == 1)
      {
        //decide whether dark or light
        if(mp[0] > 0.16)
        {
          colour.push_back(m_darkRust);
        }
        else
        {
          colour.push_back(m_lightRust);
        }
      }

      //normalise the data
      ngl::Vec3 tempPos = _data[i]->getPos();
      ngl::Vec2 temp2D = ngl::Vec2(tempPos[0],tempPos[1]);
      temp2D.normalize();
      //get normalised 2D coords
      temp2D = get2DNormCoords(temp2D);

      if(temp2D[0] == m_width+1 && temp2D[1] == m_height+1)
      {
        //do nothing
      }
      else
      {
        //add position
        position.push_back(temp2D);
      }
    }

    //sort position by x
    //std::sort(position.begin(), position.end(), sortFunc);

    std::cout<<"colours size : "<<colour.size()<<"\n";
    std::cout<<"position size : "<<position.size()<<"\n";

    float highV = 0;
    float lowV = 0;
    float highU = 0;
    float lowU = 0;

    ngl::Vec2 v1;
    ngl::Vec2 v2;
    ngl::Vec2 v3;
    ngl::Vec2 v4;

    for(unsigned int i = 0; i < _uv.size(); ++i)
    {
       //get bounding quad for unwrap
       if(_uv[i][0] >= highU) { highU = _uv[i][0]; }
       if(_uv[i][0] <= lowU) { lowU = _uv[i][0]; }
       if(_uv[i][1] >= highV) { highV = _uv[i][1]; }
       if(_uv[i][1] <= lowV) { lowV = _uv[i][1]; }

       //check large u
       if(highU == lowU) { highU = highV; }
    }

    //make vertics
    v1 = ngl::Vec2(highV,lowU);
    v2 = ngl::Vec2(lowV,lowU);
    v3 = ngl::Vec2(highV,highU);
    v4 = ngl::Vec2(lowV,highU);

    //work out bquad len and width
    //v3 & v1
    float length = sqrt( pow(v3[0] - v1[0],2) + pow(v3[1] - v1[1],2));
    //v1 & v2
    float width = sqrt( pow(v1[0] - v2[0],2) + pow(v1[1] - v2[1],2));

    //set position
    ngl::Random *rand = ngl::Random::instance();

    for(unsigned int i = 0; i < position.size(); ++i)
    {
      position[i][0] = (float)rand->randomPositiveNumber(length);
      position[i][1] = (float)rand->randomPositiveNumber(width);
      //reverse normalisation
      position[i][0] = int(position[i][0] * m_width);
      position[i][1] = int(position[i][1] * m_height);
    }

    for(unsigned int i = 0; i < position.size(); ++i)
    {
      std::cout<<"position : ["<<position[i][0]<<", "<<position[i][1]<<"] | i : "<<i<<"\n";
    }

    //Following derived from lodepng examples
    //https://raw.githubusercontent.com/lvandeve/lodepng/master/example_encode.cpp
    //Josh Bainbridge helped me understand this library.

    std::vector <unsigned char> image(m_width * m_height * 4);
    //loop through image and set colour
    //loop through each pixel in all columns
    for(unsigned int i= 0; i < m_height; ++i)
    {
      //for the next pixel in that row
      for(unsigned int j = 0; j < m_width; ++j)
      {
        //search for a surfel with that position
        for(unsigned int k = 0; k < position.size(); ++k)
        {
          ngl::Vec2 pos = position[k];
          if(pos[0] == j && pos[1] == i)
          {
            //get colour data
            ngl::Vec4 c = colour[k];
            //set colour
            image[4 * m_width * i + 4 * j + 0] = (unsigned char)c[0];
            image[4 * m_width * i + 4 * j + 1] = (unsigned char)c[1];
            image[4 * m_width * i + 4 * j + 2] = (unsigned char)c[2];
            image[4 * m_width * i + 4 * j + 3] = (unsigned char)c[3];
          }
        }
          /**
          else if (position[k][0] != i && position[k][1] != j)
          {
            //we have no colour here so set to transparent
            image[4 * m_width * i + 4 * j + 0] = (unsigned char)255;
            image[4 * m_width * i + 4 * j + 1] = (unsigned char)255;
            image[4 * m_width * i + 4 * j + 2] = (unsigned char)255;
            image[4 * m_width * i + 4 * j + 3] = (unsigned char)255;
          }**/


      }
    }

    //generate png using lodepng
    unsigned error = lodepng::encode(m_pngName, image, m_width, m_height);
    //catch any errors
    if(error) std::cout<< "image encoder error "<<error<<" : "<<lodepng_error_text(error)<<std::endl;

    std::cout<<"Texture Generation complete\n";
  }

  ngl::Vec2 Texture::get2DNormCoords(ngl::Vec2 _coords)
  {
    //make norm vector fit in 2D. Accuracy doesn't matter as we are not physically accurate.
    if(_coords[0] <= -1 || _coords[0] >= 1 || _coords[1] <= -1 || _coords[1] >= 1)
    {
      return ngl::Vec2(m_width+1,m_height+1);
    }

    //find the 2D position
    int x = int(((_coords[0] + 1) * 0.5) * (m_width-1));
    int y = int(((_coords[1] + 1) * 0.5) * (m_height-1));

    return ngl::Vec2(x,y);
  }

  Texture::~Texture()
  {

  }
}
