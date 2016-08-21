#ifndef PPNP_H
#define PPNP_H

#include "graph/sub/Dendrite.h"
#include "abstract/WeightFunction.h"
#include <ngl/Text.h>
#include "ngl/Camera.h"
#include "utils/BoundingBox.h"

namespace ppnp
{
  class PPNP
  {
    public:
      enum LatticeOptions {Square = 0, Hexagon = 1};
      enum WeightOptions {None = 0, Default = 1, Image = 2};
      PPNP(const LatticeOptions &_lattice,
           const WeightOptions &_weight,
           std::vector<std::string> _largs,
           std::vector<std::string> _wargs);
      ~PPNP();
      void createLattice();
      void setRootByIndex(const int &_rootIndex);
      void calculateDistances();
      void addEndPointByIndex(const int &_endpointIndex);
      void removeEndPointByIndex(const int &_endpointIndex);
      void findPaths();
      void exportPaths();
      void draw(ngl::Mat4 &_mouseGlobalTX, ngl::Camera &_cam);
      void drawPaths(ngl::Mat4 &_mouseGlobalTX, ngl::Camera &_cam);
      std::map<std::string, ngl::Real> getEdgeWeights() { return m_lattice->getEdgeWeights(); }
      void setDrawLattice(const bool _flag) { m_drawLattice = _flag; }
      void setDrawDendrite(const bool _flag) { m_drawDendrite = _flag; }
      void setDrawBoundingBox(const bool _flag) { m_drawBoundingBox = _flag; }
      Lattice::Type convert(PPNP::LatticeOptions _lattice);
      WeightFunction::Type convert(PPNP::WeightOptions _weightfunc);
      Lattice * m_lattice;
      Dendrite * m_dendrite;
      BoundingBox * m_boundingBox;
      void refinePaths();
      std::vector<int> setRandomEndPoints();
      std::vector<int> setRandomEndPoints(const int &_num, const ngl::Vec3 &_minBounds, const ngl::Vec3 &_maxBounds);
      void setWeightFunctionDisplay(const bool _display);
      void setPathSelected(const int _endpointIndex, const bool _selected);
      void createBoundingBox(const ngl::Vec3 &_min, const ngl::Vec3 &_max);
    private:
      bool m_drawLattice;
      bool m_drawDendrite;
      bool m_drawBoundingBox;
  };

} // end namespace ppnp

#endif
