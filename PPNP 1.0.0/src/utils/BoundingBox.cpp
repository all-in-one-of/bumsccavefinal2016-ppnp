#include "utils/BoundingBox.h"
#include <ngl/ShaderLib.h>

BoundingBox::BoundingBox(const ngl::Vec3 &_minBounds, const ngl::Vec3 &_maxBounds)
{
  m_min = _minBounds;
  m_max = _maxBounds;
//  m_min = ngl::Vec3(-1, -1, -1);
//  m_min = ngl::Vec3(1, 1, 1);
  m_vaoReady = false;
  //setupVAO();
}

BoundingBox::~BoundingBox()
{
  if (m_vao != nullptr)
  {
    m_vao->removeVOA();
  }
  //m_vao->removeVOA();
}

void BoundingBox::setupVAO()
{
  std::vector<ngl::Vec3> data;

  ngl::Vec3 point1 = ngl::Vec3(m_min.m_x, m_max.m_y, m_min.m_z);
  ngl::Vec3 point2 = ngl::Vec3(m_min.m_x, m_max.m_y, m_max.m_z);
  ngl::Vec3 point3 = ngl::Vec3(m_max.m_x, m_max.m_y, m_min.m_z);
  ngl::Vec3 point4 = ngl::Vec3(m_min.m_x, m_min.m_y, m_max.m_z);
  ngl::Vec3 point5 = ngl::Vec3(m_max.m_x, m_min.m_y, m_min.m_z);
  ngl::Vec3 point6 = ngl::Vec3(m_max.m_x, m_min.m_y, m_max.m_z);

  data.push_back(point1);
  data.push_back(point2);
  data.push_back(point2);
  data.push_back(m_max);
  data.push_back(m_max);
  data.push_back(point3);
  data.push_back(point3);
  data.push_back(point1);

  data.push_back(point1);
  data.push_back(m_min);
  data.push_back(point2);
  data.push_back(point4);
  data.push_back(m_max);
  data.push_back(point6);
  data.push_back(point3);
  data.push_back(point5);

  data.push_back(m_min);
  data.push_back(point4);
  data.push_back(point4);
  data.push_back(point6);
  data.push_back(point6);
  data.push_back(point5);
  data.push_back(point5);
  data.push_back(m_min);

  m_vao.reset(ngl::VertexArrayObject::createVOA(GL_LINES));
  m_vao->bind();
  m_vao->setData(data.size()*sizeof(ngl::Vec3), data[0].m_x);
  m_vao->setVertexAttributePointer(0,3,GL_FLOAT,0,0);
  m_vao->setNumIndices(data.size());
  m_vao->unbind();

  m_vaoReady = true;
}

void BoundingBox::draw(ngl::Mat4 _mouseGlobalTX, ngl::Camera _cam)
{
  if(!m_vaoReady)
  {
    setupVAO();
  }

  // get shader instance
  ngl::ShaderLib *shader = ngl::ShaderLib::instance();
  // load matrices to shader
  ngl::Mat4 MV;
  ngl::Mat4 MVP;
  ngl::Mat3 normalMatrix;
  ngl::Mat4 M;
  M=_mouseGlobalTX;
  MV=  M*_cam.getViewMatrix();
  MVP= M*_cam.getVPMatrix();
  normalMatrix=MV;
  normalMatrix.inverse();

  shader->use("nglColourShader");
  shader->setShaderParam4f("Colour",1.0f,0.0f,0.0f,1.0f);
  shader->setShaderParamFromMat4("MV",MV);
  shader->setShaderParamFromMat4("MVP",MVP);
  shader->setShaderParamFromMat3("normalMatrix",normalMatrix);
  shader->setShaderParamFromMat4("M",M);

  m_vao->bind();
  m_vao->draw();
  m_vao->unbind();
}
