#include "Obj.h"
#include <iostream>

namespace pwl
{
  Obj::Obj()
  {
    std::cout<<"Obj Constructed\n";
  }

  void Obj::loadObj(std::string _model)
  {
    std::cout<<"loading model\n";

    //load obj
    ngl::Obj mesh(_model);

    std::cout<<"checking triangular...\n";
    //ngl only works with tri meshes
    if( ! mesh.isTriangular() )
    {
      std::cout<<"only works for tri meshes\n";
      exit(EXIT_FAILURE);
    }

    //get mesh data
    std::cout<<"getting mesh data\n";
    m_verts = mesh.getVertexList();
    m_faces = mesh.getFaceList();
    m_texs = mesh.getTextureCordList();
    m_normals = mesh.getNormalList();
    std::cout<<"mesh data collected\n";

    mesh.calcDimensions();
    m_bbox = mesh.getBBox(); //returns ngl::BBox
  }

  void Obj::createVAO()
  {
    vertData d;
    unsigned int nFaces = m_faces.size();
    unsigned int nNorm = m_normals.size();
    unsigned int nTex = m_texs.size();

    //loop for each face
    for(unsigned int i = 0; i < nFaces; ++i)
    {
      //for each tri
      for(int j = 0; j < 3; ++j)
      {
        //pack in vertex data first
        d.x = m_verts[m_faces[i].m_vert[j]].m_x;
        d.y = m_verts[m_faces[i].m_vert[j]].m_y;
        d.z = m_verts[m_faces[i].m_vert[j]].m_z;

        //if we have norms or tex pack them as well
        if(nNorm > 0 && nTex > 0)
        {
          //normals
          d.nx = m_normals[m_faces[i].m_norm[j]].m_x;
          d.ny = m_normals[m_faces[i].m_norm[j]].m_y;
          d.nz = m_normals[m_faces[i].m_norm[j]].m_z;

          //tex
          d.u = m_texs[m_faces[i].m_tex[j]].m_x;
          d.v = m_texs[m_faces[i].m_tex[j]].m_y;
        }
        //if neither are present
        else if(nNorm == 0 && nTex == 0)
        {
          d.nx = 0;
          d.ny = 0;
          d.nz = 0;
          d.u = 0;
          d.v = 0;
        }
        //if we have norm but no tex
        else if(nNorm > 0 && nTex == 0)
        {
          d.nx = m_normals[m_faces[i].m_norm[j]].m_x;
          d.ny = m_normals[m_faces[i].m_norm[j]].m_y;
          d.nz = m_normals[m_faces[i].m_norm[j]].m_z;
          d.u = 0;
          d.v = 0;
        }

      vboMesh.push_back(d);
      }
    }
    //grab instance of VAO class. As Tri Strip
    m_vaoMesh = ngl::VertexArrayObject::createVOA(GL_TRIANGLES);
    //bind to set data
    m_vaoMesh->bind();
    unsigned int meshSize = vboMesh.size();

    //tell the VAO how much data we are copying (in bytes)
    m_vaoMesh->setData(meshSize*sizeof(vertData),vboMesh[0].u);

    //set vertexAttributePointer to the right size and type
    m_vaoMesh->setVertexAttributePointer(0,3,GL_FLOAT,sizeof(vertData),5); //position
    m_vaoMesh->setVertexAttributePointer(1,2,GL_FLOAT,sizeof(vertData),0); //uv
    m_vaoMesh->setVertexAttributePointer(2,3,GL_FLOAT,sizeof(vertData),2); //normals

    //tell vao how many indices to draw
    m_vaoMesh->setNumIndices(meshSize);
    //unbind now we have finished
    m_vaoMesh->unbind();

    std::cout<<"VAO HAS BEEN CREATED\n";

  }

  Obj::~Obj()
  {
    std::cout<<"Obj destructed\n";
  }
}
