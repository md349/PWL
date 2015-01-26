#ifndef HALTON_H
#define HALTON_H

#include <ngl/Vec3.h>

namespace pwl
{
  class Halton
  {
    public:
      //constructor
      Halton();
      //destructor
      ~Halton();

      //perform sequence and store results for vertical emitter
      void doSequence(float _xRadius, float _zRadius, int _index, int _base1, int _base2);

      //perform sequence and store results for BBox emitter
      void doSequenceBB(float _radius1, float _radius2, int _index, int _base1, int _base2, const int _id);

      //returns halton seuqence result for particular GTon/Surfel.
      ngl::Vec3 getHSeq(int _id) { return m_finalSequence[_id]; }

    private:
      //vector holds halton sequence
      std::vector <ngl::Vec3> m_finalSequence;
  };
}

#endif // HALTON_H
