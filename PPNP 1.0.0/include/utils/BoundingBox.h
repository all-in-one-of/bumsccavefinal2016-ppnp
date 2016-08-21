#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <ngl/VertexArrayObject.h>
#include <ngl/Camera.h>

#include <memory>

class BoundingBox
{
  public:
    BoundingBox(const ngl::Vec3 &_minBounds, const ngl::Vec3 &_maxBounds);
    ~BoundingBox();
    void draw(ngl::Mat4 _mouseGlobalTX, ngl::Camera _cam);
  private:
    std::unique_ptr<ngl::VertexArrayObject> m_vao;
    void setupVAO();
    ngl::Vec3 m_min;
    ngl::Vec3 m_max;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief put drawable data in the appropriate buffers
    //----------------------------------------------------------------------------------------------------------------------
    bool m_vaoReady;
};

#endif
