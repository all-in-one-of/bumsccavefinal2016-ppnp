#ifndef PATH_H
#define PATH_H

#include "ngl/Vec3.h"
#include "ngl/Mat4.h"
#include "ngl/Camera.h"
#include "ngl/VAOPrimitives.h"

#include <memory>

#include <vector>
namespace ppnp
{

class Path
{
  public:
    Path()
    {
      m_vaoReady = false;
      m_isSelected = false;
    }

    Path(const Path &_copy)
    {
      m_vaoReady = false;
      m_isSelected = _copy.m_isSelected;
      for(ngl::Vec3 p : _copy.m_points)
      {
        m_points.push_back(p);
      }
    }

    ~Path() {
      if (m_vao != nullptr)
      {
        m_vao->removeVOA();}
      }
    inline void addPoint(const ngl::Vec3 &_point) { m_points.push_back(_point); }
    std::vector<ngl::Vec3> m_points;
    void draw(ngl::Mat4 &_mouseGlobalTX, ngl::Camera &_cam);
    void setSelected(const bool _selected) { m_isSelected = _selected; }
  private:
    void setupVAO();
    bool m_vaoReady;
    bool m_isSelected;
    std::unique_ptr<ngl::VertexArrayObject> m_vao;
};

} // end namespace ppnp

#endif
