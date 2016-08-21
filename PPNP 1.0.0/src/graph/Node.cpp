#include "graph/Node.h"

#include <ngl/ShaderLib.h>

ppnp::Node::Node(const int &_index, const ngl::Vec3 &_pos)
{
  m_pos = _pos;
  m_index = _index;
  m_vaosReady = false;
  m_isEligableEndPoint = true;
}

ppnp::Node::~Node()
{
  m_vaoNode->removeVOA();
  m_vaoEdges->removeVOA();
}

void ppnp::Node::addEdge(Node *_next, ngl::Real _weight, ngl::Real _length)
{
  Node::Edge e = {_next, _weight, _length};
  m_edges.push_back(e);
}

void ppnp::Node::setupVAOs()
{
  // set up the vao to draw the node (which is a point)
  glPointSize(5);
  m_vaoNode.reset(ngl::VertexArrayObject::createVOA(GL_POINTS));
  m_vaoNode->bind();
  m_vaoNode->setData(sizeof(ngl::Vec3), m_pos.m_x);
  m_vaoNode->setVertexAttributePointer(0,3,GL_FLOAT,0,0);
  m_vaoNode->setNumIndices(1);
  m_vaoNode->unbind();

  // set up the vao to draw the edges (which are lines)
  std::vector<ngl::Vec3> data;
  for(ppnp::Node::Edge e : m_edges)
  {
    data.push_back(m_pos);
    data.push_back(e.adjacent->m_pos);
  }

  m_vaoEdges.reset(ngl::VertexArrayObject::createVOA(GL_LINES));
  m_vaoEdges->bind();
  m_vaoEdges->setData(data.size()*sizeof(ngl::Vec3), data[0].m_x);
  m_vaoEdges->setVertexAttributePointer(0,3,GL_FLOAT,0,0);
  m_vaoEdges->setNumIndices(data.size());
  m_vaoEdges->unbind();

  m_vaosReady = true;
}

void ppnp::Node::draw(ngl::Mat4 _mouseGlobalTX, ngl::Camera _cam)
{
  if(!m_vaosReady)
  {
    setupVAOs();
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

  m_vaoNode->bind();
  m_vaoNode->draw();
  m_vaoNode->unbind();

  shader->use("nglColourShader");
  shader->setShaderParam4f("Colour",0.0f,0.0f,1.0f,0.2f); //blue
  shader->setShaderParamFromMat4("MV",MV);
  shader->setShaderParamFromMat4("MVP",MVP);
  shader->setShaderParamFromMat3("normalMatrix",normalMatrix);
  shader->setShaderParamFromMat4("M",M);

  m_vaoEdges->bind();
  m_vaoEdges->draw();
  m_vaoEdges->unbind();
}
