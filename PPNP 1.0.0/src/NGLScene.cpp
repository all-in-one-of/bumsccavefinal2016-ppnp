#include <QMouseEvent>
#include <QGuiApplication>

#include <ngl/Camera.h>
#include <ngl/Light.h>
#include <ngl/Material.h>
#include <ngl/NGLInit.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>

#include "NGLScene.h"
#include "graph/Hexagon.h"
#include "graph/Square.h"
#include "alg/Dijkstra.h"
#include "functions/ImageWeightFunction.h"
#include "utils/glu.h"

#include <boost/lexical_cast.hpp>

//----------------------------------------------------------------------------------------------------------------------
/// @brief the increment for x/y translation with mouse movement
//----------------------------------------------------------------------------------------------------------------------
const static float INCREMENT=0.01f;
//----------------------------------------------------------------------------------------------------------------------
/// @brief the increment for the wheel zoom
//----------------------------------------------------------------------------------------------------------------------
const static float ZOOM=0.1f;

NGLScene::NGLScene(QWidget *_parent)
{
  // set this widget to have the initial keyboard focus
  setFocus();
  // re-size the widget to that of the parent (in this case the GLFrame passed in on construction)
  this->resize(_parent->size());
  // re-size the widget to that of the parent (in that case the GLFrame passed in on construction)
  m_rotate=false;
  // mouse rotation values set to 0
  m_spinXFace=0.0f;
  m_spinYFace=0.0f;
  // turn off all switches
  m_weightsDisplay = false;
  m_costingsDisplay = false;
  // except the node indices - display by default
  m_indicesDisplay = true;

  m_dendritetDisplay = false;
}

NGLScene::~NGLScene()
{
  std::cout<<"Shutting down NGL, removing VAO's and Shaders\n";
}

void NGLScene::resizeGL(QResizeEvent *_event)
{
  m_width=_event->size().width()*devicePixelRatio();
  m_height=_event->size().height()*devicePixelRatio();
  // now set the camera size values as the screen size has changed
  m_cam.setShape(45.0f,(float)width()/height(),0.05f,350.0f);
}

void NGLScene::resizeGL(int _w , int _h)
{
  m_cam.setShape(45.0f,(float)_w/_h,0.05f,350.0f);
  m_width=_w*devicePixelRatio();
  m_height=_h*devicePixelRatio();
}

void NGLScene::initializeGL()
{
  // we must call that first before any other GL commands to load and link the
  // gl commands from the lib, if that is not done program will crash
  ngl::NGLInit::instance();
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);			   // Grey Background
  // enable depth testing for drawing
   glEnable(GL_DEPTH_TEST);
  // enable multisampling for smoother drawing
  glEnable(GL_MULTISAMPLE);

  //enable blending to be able to use alpha
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Now we will create a basic Camera from the graphics library
  // This is a static camera so it only needs to be set once
  // First create Values for the camera position
  ngl::Vec3 from(0,0,-15);
  ngl::Vec3 to(0,0,0);
  ngl::Vec3 up(0,1,0);
  // now load to our new camera
  m_cam.set(from,to,up);
  // set the shape using FOV 45 Aspect Ratio based on Width and Height
  // The final two are near and far clipping planes of 0.5 and 10
  m_cam.setShape(45.0f,(float)720.0/576.0f,0.05f,350.0f);

  // now create our light that is done after the camera so we can pass the
  // transpose of the projection matrix to the light to do correct eye space
  // transformations
  ngl::Mat4 iv=m_cam.getViewMatrix();
  iv.transpose();
  ngl::Light light(ngl::Vec3(-2,5,2),ngl::Colour(1,1,1,1),ngl::Colour(1,1,1,1),ngl::LightModes::POINTLIGHT );
  light.setTransform(iv);
  // load these values to the shader as well
  light.loadToShader("light");
  // as re-size is not explicitly called we need to do that.
  // set the viewport for openGL we need to take into account retina display

  m_text.reset( new ngl::Text(QFont("Arial",7)));
  m_text->setScreenSize(width(),height());
  // as re-size is not explicitly called we need to do this.
  glViewport(0,0,width(),height());

//  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
//  // load a frag and vert shaders

//  shader->createShaderProgram("TextureShader");

//  shader->attachShader("SimpleVertex",ngl::ShaderType::VERTEX);
//  shader->attachShader("SimpleFragment",ngl::ShaderType::FRAGMENT);
//  shader->loadShaderSource("SimpleVertex","shaders/TextureVert.glsl");
//  shader->loadShaderSource("SimpleFragment","shaders/TextureFrag.glsl");

//  shader->compileShader("SimpleVertex");
//  shader->compileShader("SimpleFragment");
//  shader->attachShaderToProgram("TextureShader","SimpleVertex");
//  shader->attachShaderToProgram("TextureShader","SimpleFragment");


//  shader->linkProgramObject("TextureShader");
//  shader->use("TextureShader");

//  createCube(0.2);
//  loadTexture();

  //ngl::Vec3 normal = ngl::Vec3(1, 0, 0);
  //m_prim = ngl::VAOPrimitives::instance();
  //m_prim->createTrianglePlane("plane", 10, 10, 10, 10, normal);

  ngl::Vec3 normal = ngl::Vec3(1, 0, 0);
  ngl::VAOPrimitives* prim  = ngl::VAOPrimitives::instance();
  prim->createTrianglePlane("plane", 10, 10, 10, 10, normal);



 // createBoundingBox(ngl::Vec3(-1, -1, -1), ngl::Vec3(1, 1, 1));
  //m_boundingBoxDisplay = true;


}

void NGLScene::constructLattice(int _latticeOptionIndex, int _weightOptionIndex, std::vector<std::string> _largs, std::vector<std::string> _wargs)
{
  ppnp::PPNP::LatticeOptions latticeType = static_cast<ppnp::PPNP::LatticeOptions>(_latticeOptionIndex);
  ppnp::PPNP::WeightOptions weightFunctionType = static_cast<ppnp::PPNP::WeightOptions>(_weightOptionIndex);
  m_ppnp.reset(new ppnp::PPNP(latticeType, weightFunctionType, _largs, _wargs));
  m_ppnp->createLattice();

  // update the screen
  update();
}

void NGLScene::setRootByIndex(int _index)
{
  m_ppnp->setRootByIndex(_index);
}

void NGLScene::calculateDistancesFromRoot()
{
  m_ppnp->calculateDistances();
}

void NGLScene::generatePaths(std::vector<int> _endpointIndices)
{
  for (int i = 0; i < _endpointIndices.size(); ++i)
  {
    m_ppnp->addEndPointByIndex(_endpointIndices[i]);
  }

  m_ppnp->findPaths();

  m_dendritetDisplay = true;

  update();
}

void NGLScene::removeEndPointByIndex(const int &_endpointIndex)
{
  m_ppnp->removeEndPointByIndex(_endpointIndex);

  update();
}

void NGLScene::exportPaths()
{
  m_ppnp->exportPaths();
}

void NGLScene::paintGL()
{
  glViewport(0,0,m_width,m_height);
  // clear the screen and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_BLEND);

  // Rotation based on the mouse position for our global transform
  ngl::Mat4 rotX;
  ngl::Mat4 rotY;
  // create the rotation matrices
  rotX.rotateX(m_spinXFace);
  rotY.rotateY(m_spinYFace);
  // multiply the rotations
  m_mouseGlobalTX=rotY*rotX;
  // add the translations
  m_mouseGlobalTX.m_m[3][0] = m_modelPos.m_x;
  m_mouseGlobalTX.m_m[3][1] = m_modelPos.m_y;
  m_mouseGlobalTX.m_m[3][2] = m_modelPos.m_z;

  if(m_ppnp != nullptr)
  {
    glLineWidth(1);
    m_ppnp->draw(m_mouseGlobalTX, m_cam);

    // display text info
    m_text.reset(new ngl::Text(QFont("Courier New", 9)));
    if(m_weightsDisplay)
    {
      m_text->setColour(ngl::Colour(0, 0, 0)); // black
      displayLatticeWeights();
    }

    if (m_indicesDisplay)
    {
      m_text->setColour(ngl::Colour(153, 0, 153)); // purple
      displayNodeIndices();
    }

    if (m_costingsDisplay)
    {
      m_text->setColour(ngl::Colour(0, 0, 0)); // green
      displayDistancesFromRoot();
    }

    if (m_dendritetDisplay)
    {
      glLineWidth(5);
      m_ppnp->m_dendrite->draw(m_mouseGlobalTX, m_cam);
    }
  }
}

void NGLScene::createBoundingBox(const ngl::Vec3 &_min, const ngl::Vec3 &_max)
{
  m_ppnp->createBoundingBox(_min, _max);
  update();
}

void NGLScene::displayLatticeWeights()
{
  std::map<std::string, ngl::Real> weightmap = m_ppnp->getEdgeWeights();

  for(auto &ent : weightmap)
  {
    std::string delimited_pos = ent.first;
    std::string delimiter = ",";
    std::size_t pos = 0;
    std::vector<std::string> tokens;

    while ((pos = delimited_pos.find(delimiter)) != std::string::npos)
    {
      std::string token = delimited_pos.substr(0, pos);
      tokens.push_back(token);
      delimited_pos.erase(0, pos + delimiter.length());
    }

    ngl::Vec3 weight_pos;
    try
    {
      weight_pos.m_x = boost::lexical_cast<double>(tokens[0]);
      weight_pos.m_y = boost::lexical_cast<double>(tokens[1]);
      weight_pos.m_z = boost::lexical_cast<double>(tokens[2]);
    }
    catch ( boost::bad_lexical_cast const& )
    {
      std::cerr << "Trying to parse weght position but cannot." << std::endl;
    }

    std::string weight_str = std::to_string(ent.second);
    weight_str.resize(4);
    QString text = QString::fromStdString(weight_str);

    textProject(text, weight_pos);
  }
}

void NGLScene::displayNodeIndices()
{
  for(auto &ent : m_ppnp->m_lattice->m_nodes)
  {
    ppnp::Node * node = ent.second;
    std::string index_str = std::to_string(node->m_index);
    QString text = QString::fromStdString(index_str);
    textProject(text, node->m_pos);
  }
}

void NGLScene::displayDistancesFromRoot()
{
  for(auto &ent : m_ppnp->m_lattice->m_nodes)
  {
    ppnp::Node * node = ent.second;
    ngl::Real distance = m_ppnp->m_dendrite->getDistanceFromRoot(node->m_index);
    std::string distance_str = std::to_string(distance);
    distance_str.resize(4);
    QString text = QString::fromStdString(distance_str);
    textProject(text, node->m_pos);
  }
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::mouseMoveEvent (QMouseEvent * _event)
{
  // note the method buttons() is the button state when event was called
  // that is different from button() which is used to check which button was
  // pressed when the mousePress/Release event is generated
  if(m_rotate && _event->buttons() == Qt::LeftButton)
  {
    int diffx=_event->x()-m_origX;
    int diffy=_event->y()-m_origY;
    m_spinXFace += (float) 0.5f * diffy;
    m_spinYFace += (float) 0.5f * diffx;
    m_origX = _event->x();
    m_origY = _event->y();
    update();

  } // right mouse translate code
  else if(m_translate && _event->buttons() == Qt::RightButton)
  {
    int diffX = (int)(_event->x() - m_origXPos);
    int diffY = (int)(_event->y() - m_origYPos);
    m_origXPos=_event->x();
    m_origYPos=_event->y();
    m_modelPos.m_x += INCREMENT * diffX;
    m_modelPos.m_y -= INCREMENT * diffY;
    update();
   }
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::mousePressEvent ( QMouseEvent * _event)
{
  // that method is called when the mouse button is pressed in this case we
  // store the value where the maouse was clicked (x,y) and set the Rotate flag to true
  if(_event->button() == Qt::LeftButton)
  {
    m_origX = _event->x();
    m_origY = _event->y();
    m_rotate =true;
  }
  // right mouse translate mode
  else if(_event->button() == Qt::RightButton)
  {
    m_origXPos = _event->x();
    m_origYPos = _event->y();
    m_translate=true;
  }
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::mouseReleaseEvent ( QMouseEvent * _event )
{
  // that event is called when the mouse button is released
  // we then set Rotate to false
  if (_event->button() == Qt::LeftButton)
  {
    m_rotate=false;
  }
        // right mouse translate mode
  if (_event->button() == Qt::RightButton)
  {
    m_translate=false;
  }
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::wheelEvent(QWheelEvent *_event)
{

	// check the diff of the wheel position (0 means no change)
	if(_event->delta() > 0)
	{
		m_modelPos.m_z+=ZOOM;
	}
	else if(_event->delta() <0 )
	{
		m_modelPos.m_z-=ZOOM;
	}
	update();
}

void NGLScene::textProject(QString &_text, ngl::Vec3 &_pos)
{
  ngl::Mat4 MV = m_mouseGlobalTX * m_cam.getViewMatrix();
  float modelview[16] = { MV.m_00, MV.m_01, MV.m_02, MV.m_03,
                          MV.m_10, MV.m_11, MV.m_12, MV.m_13,
                          MV.m_20, MV.m_21, MV.m_22, MV.m_23,
                          MV.m_30, MV.m_31, MV.m_32, MV.m_33 };

  ngl::Mat4 P = m_mouseGlobalTX * m_cam.getProjectionMatrix();
  float projection[16] = { P.m_00, P.m_01, P.m_02, P.m_03,
                           P.m_10, P.m_11, P.m_12, P.m_13,
                           P.m_20, P.m_21, P.m_22, P.m_23,
                           P.m_30, P.m_31, P.m_32, P.m_33 };

  int viewport[4] = { 0,0,m_width,m_height};

  float windowcoord[3];

  int success = glu::GLU::glhProjectf(_pos.m_x, _pos.m_y, _pos.m_z, &modelview[0], &projection[0], &viewport[0], &windowcoord[0]);

  if(success == 1)
  {
    // fix y
    ngl::Real y;
    ngl::Real x;

    x = windowcoord[0];
    y = windowcoord[1];


    if (windowcoord[1] < m_height/2)
    {
       float diff = (m_height/2) - windowcoord[1];
       y = m_height/2 + diff;
    }
    else
    {
      float diff = windowcoord[1] - (m_height/2);
      y = m_height/2 - diff;

    }

//    if (windowcoord[0] < m_width/2)
//    {
//       float diff2 = (m_width/2) - windowcoord[0];
//       x = m_width/2 + diff2;
//    }
//    else
//    {

//      float diff2 = windowcoord[0] - (m_width/2);
//      x = m_width/2 - diff2;
//    }

    //m_text->renderText(windowcoord[0],y,_text);
    m_text->renderText(x,y,_text);
  }
}

void NGLScene::setIndicesDisplay(const bool _display)
{
  m_indicesDisplay = _display;
  update();
}

void NGLScene::setWeightsDisplay(const bool _display)
{
  m_weightsDisplay = _display;
  update();
}

void NGLScene::setDistancesDisplay(const bool _display)
{
  m_costingsDisplay = _display;
  update();
}

void NGLScene::setLatticeDisplay(const bool _display)
{
  m_ppnp->setDrawLattice(_display);
  update();
}

void NGLScene::setImageDisplay(const bool _display)
{
  m_ppnp->setWeightFunctionDisplay(_display);
  update();
}

void NGLScene::setBoundingBoxDisplay(const bool _display)
{
  m_ppnp->setDrawBoundingBox(_display);
  update();
}


void NGLScene::setPathSelected(const int _endpointIndex, const bool _selected)
{
  m_ppnp->setPathSelected(_endpointIndex, _selected);
}


void NGLScene::setDisplayAll(const bool _display)
{
  m_indicesDisplay = _display;
  m_weightsDisplay = _display;
  m_costingsDisplay = _display;
  m_ppnp->setDrawLattice(_display);
  update();
}

void NGLScene::refinePaths()
{
  m_ppnp->refinePaths();
  update();
}

std::vector<int> NGLScene::setRandomEndPoints()
{
  return m_ppnp->setRandomEndPoints();
}

std::vector<int> NGLScene::setRandomEndPoints(const int &_num, const ngl::Vec3 &_minBounds, const ngl::Vec3 &_maxBounds)
{
  return m_ppnp->setRandomEndPoints(_num, _minBounds, _maxBounds);
}


