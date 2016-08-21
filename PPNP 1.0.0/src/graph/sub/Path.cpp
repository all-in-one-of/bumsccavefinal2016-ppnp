#include "graph/sub/Path.h"

#include <ngl/ShaderLib.h>

void ppnp::Path::setupVAO()
{
  std::vector<ngl::Vec3> data;

  for(int i = 0; i < m_points.size() - 1; ++i)
  {
    data.push_back(m_points[i]);
    data.push_back(m_points[i + 1]);
  }

  m_vao.reset(ngl::VertexArrayObject::createVOA(GL_LINES));
  m_vao->bind();
  m_vao->setData(data.size()*sizeof(ngl::Vec3), data[0].m_x);
  m_vao->setVertexAttributePointer(0,3,GL_FLOAT,0,0);
  m_vao->setNumIndices(data.size());
  m_vao->unbind();
  m_vaoReady = true;
}

void ppnp::Path::draw(ngl::Mat4 &_mouseGlobalTX, ngl::Camera &_cam)
{
  if (!m_vaoReady)
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

  if(m_isSelected)
  {


    shader->setShaderParam4f("Colour",1.0f, 0.0f,0.0f,1.0f); //purple
  }
  else
  {
    shader->setShaderParam4f("Colour",0.0f, 0.0f,0.0f,1.0f); //black
  }

  shader->setShaderParamFromMat4("MV",MV);
  shader->setShaderParamFromMat4("MVP",MVP);
  shader->setShaderParamFromMat3("normalMatrix",normalMatrix);
  shader->setShaderParamFromMat4("M",M);

  m_vao->bind();
  m_vao->draw();
  m_vao->unbind();
}
