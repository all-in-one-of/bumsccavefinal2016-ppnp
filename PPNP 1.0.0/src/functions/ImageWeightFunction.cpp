#include "functions/ImageWeightFunction.h"

#include <ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>

#include <QColor>
#include <utils/Logger.h>

ImageWeightFunction::ImageWeightFunction(const std::string &_filename, ngl::Real _width, ngl::Real _height)
{
  std::string dir = "../img/";
  std::string filename = dir + _filename;
  m_texture.reset(new ngl::Texture(filename));
  m_image = QImage(filename.c_str());


  int texture_width = m_texture->getWidth();
  int texture_height = m_texture->getHeight();

  m_image = m_image.scaled(1000, 1000, Qt::IgnoreAspectRatio);

//  Logger* log = Logger::instance();

//  for (int i=0; i<m_image.width(); ++i)
//  {
//    log->log("\n");

//      for (int j=0; j<m_image.height(); ++j)
//      {
//        QColor col = QColor(m_image.pixel(i, j));


//        ngl::Real col_weight = (0.21 * col.red()) + (0.72 * col.green()) + (0.07 * col.blue());

//        log->log(std::to_string(col_weight) + "\n");
//      }
//  }


  m_textureID = m_texture->setTextureGL();
  m_width = _width;
  m_height = _height;
  m_type = WeightFunction::Image;
}

void ImageWeightFunction::function(ppnp::Node *_node, ppnp::Node::Edge *_edge)
{

  Logger* log = Logger::instance();

  // we are taking the midpoint of the edge
  ngl::Vec3 midpoint = _node->m_pos + (_edge->adjacent->m_pos - _node->m_pos)/2;


  //log->log("Nodes: " + std::to_string(_node->m_pos.m_x) + ", " + std::to_string(_node->m_pos.m_y) + ", " + std::to_string(_node->m_pos.m_z) + "    " + std::to_string(_edge->adjacent->m_pos.m_x) + ", " + std::to_string(_edge->adjacent->m_pos.m_y) + ", " + std::to_string(_edge->adjacent->m_pos.m_z) + "\n");

  //ngl:Real x = _node->m_pos.m_x


  ngl::Real x = midpoint.m_x;
  ngl::Real y = midpoint.m_y;

  //http://www.scratchapixel.com/lessons/3d-basic-rendering/computing-pixel-coordinates-of-3d-point/mathematics-computing-2d-coordinates-of-3d-points
  // normalize
  x = (x + (m_width)/2)/m_width;
  y = ((y + (m_height)/2)/m_height);

  // convert
  ngl::Real x_raster = std::floor(x * (m_image.width()-1));
  ngl::Real y_raster = std::floor((1 - y) * (m_image.height()-1));


  // end cite

  ngl::Real w = m_image.width();
  ngl::Real h = m_image.height();


  ngl::Real col_weight = 255;



  QColor col = QColor(m_image.pixel(x_raster, y_raster));

  int r = col.red();
  int g = col.green();
  int b = col.blue();



  col_weight = (0.21 * col.red()) + (0.72 * col.green()) + (0.07 * col.blue());

  col_weight = col_weight/255; // between 0 and 1

  //Logger* log = Logger::instance();
  //log->log("Midpoint:" + std::to_string(midpoint.m_x) + "," + std::to_string(midpoint.m_y) + ". Raster: " + std::to_string(x_raster) + ", " + std::to_string(y_raster) + " .Col:" + std::to_string(col_weight) +"\n");

  // ngl::Colour col = m_map->getColour(u_coord, v_coord);

  // convert the colour to a grayscale value and set it as a weight
  // http://www.johndcook.com/blog/2009/08/24/algorithms-convert-color-grayscale/
  // ngl::Real col_weight = (0.21 * col.m_r) + (0.72 * col.m_g) + (0.07 * col.m_b);
  // end cite

  _edge->weight = col_weight;
}

void ImageWeightFunction::display(const ngl::Mat4 &_mouseGlobalTX, const ngl::Camera &_cam)
{
  ngl::ShaderLib *shader = ngl::ShaderLib::instance();
  shader->createShaderProgram("TextureShader");
  shader->attachShader("SimpleVertex",ngl::ShaderType::VERTEX);
  shader->attachShader("SimpleFragment",ngl::ShaderType::FRAGMENT);
  shader->loadShaderSource("SimpleVertex","shaders/TextureVert.glsl");
  shader->loadShaderSource("SimpleFragment","shaders/TextureFrag.glsl");
  shader->compileShader("SimpleVertex");
  shader->compileShader("SimpleFragment");
  shader->attachShaderToProgram("TextureShader","SimpleVertex");
  shader->attachShaderToProgram("TextureShader","SimpleFragment");
  shader->linkProgramObject("TextureShader");

  (*shader)["TextureShader"]->use();
  glBindTexture(GL_TEXTURE_2D, m_textureID);
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  m_transform.reset();
  //m_transform.setRotation(270, 180, 0);
  m_transform.setRotation(-90, 0, 0);
  m_transform.setScale(0.1, 1, 0.1);
  m_transform.setScale(m_width*0.1, 1, m_height*0.1);

  // load matrices to shader
  ngl::Mat4 MVP = m_transform.getMatrix()*_mouseGlobalTX*_cam.getVPMatrix();
  shader->setRegisteredUniform("MVP",MVP);

  //m_vao->bind();
  //m_vao->draw();
  //m_vao->unbind();

  ngl::VAOPrimitives::instance()->draw("plane");
}
