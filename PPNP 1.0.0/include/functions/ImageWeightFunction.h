#ifndef IMAGEWEIGHTFUNCTION_H
#define IMAGEWEIGHTFUNCTION_H

#include <memory>

#include <QImage>

#include <ngl/Util.h>
#include <ngl/Image.h>
#include <ngl/Texture.h>
#include <ngl/VertexArrayObject.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/Camera.h>
#include <ngl/Transformation.h>

#include "abstract/WeightFunction.h"

//----------------------------------------------------------------------------------------------------------------------
/// @file ImageWeightFunction.h
/// @brief Image weight function definition
/// @author Erika Camilleri
/// @version 1.0
/// ----------------------------------------------------------------------------------------------------------------------
class ImageWeightFunction : public WeightFunction
{
  public:
    ImageWeightFunction(const std::string &_filename, ngl::Real _width = 10, ngl::Real _height = 10);
    void function(ppnp::Node* _node, ppnp::Node::Edge* _edge);
    void display(const ngl::Mat4 &_mouseGlobalTX, const ngl::Camera &_cam);
  private:
    ngl::Transformation m_transform;
    ngl::Vec2 findClosestUV(const ngl::Vec3 _point);
    std::unique_ptr<ngl::VertexArrayObject> m_vao;
    std::unique_ptr<ngl::Image> m_map;
    QImage m_image;
    std::unique_ptr<ngl::Texture> m_texture;
    GLuint m_textureID;
    std::vector<ngl::vertData> m_data;
    ngl::Real m_width;
    ngl::Real m_height;
};

#endif
