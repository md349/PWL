#ifndef OBJ_H
#define OBJ_H

#include <ngl/Obj.h>
#include <ngl/VAOPrimitives.h>

namespace pwl
{
  class Obj
  {
    public:
      //constructor
      Obj();
      //destructor
      ~Obj();

      //load obj file
      void loadObj(std::string _model);

      //create VAO for obj.
      void createVAO();

      //return face vector THESE ARE COPIES. WORK OUT WAY AROUND
      std::vector <ngl::Vec3> getObjVertexVec() { return m_verts; }
      std::vector <ngl::Face> getObjFace() { return m_faces; }
      std::vector <ngl::Vec3> getObjTexVec() { return m_texs; }
      std::vector <ngl::Vec3> getObjNormVec() { return m_normals; }

      ngl::BBox getBBox() { return m_bbox; }

    private:
      //vector for vertex information.
      std::vector <ngl::Vec3> m_verts;

      //vector for face information.
      std::vector <ngl::Face> m_faces;

      //vector for texture coordinates.
      std::vector <ngl::Vec3> m_texs;

      //vector for normals.
      std::vector <ngl::Vec3> m_normals;

      struct vertData
      {
        GLfloat u;  //tex coord
        GLfloat v;  //tex coord
        GLfloat nx; //normal
        GLfloat ny;
        GLfloat nz;
        GLfloat x;  //position
        GLfloat y;
        GLfloat z;
      };

      //vector of data for our mesh
      std::vector <vertData> vboMesh;

      //vertex array object
      ngl::VertexArrayObject *m_vaoMesh;

      //bounding box to work out emitter sizes.
      ngl::BBox m_bbox;
  };

}

#endif // OBJ_H
