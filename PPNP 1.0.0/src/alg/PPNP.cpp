#include "alg/PPNP.h"
#include "alg/Dijkstra.h"
#include <ngl/ShaderLib.h>

ppnp::PPNP::PPNP(const LatticeOptions &_lattice, const WeightOptions &_weight, std::vector<std::string> _largs, std::vector<std::string> _wargs)
{
  ppnp::Lattice::Type ltype = convert(_lattice);
  WeightFunction::Type wtype = convert(_weight);
  m_lattice = Lattice::factory(ltype, _largs);
  m_lattice->setWeightFunction(wtype, _wargs);
  m_drawLattice = true;
  m_drawDendrite = true;
  m_drawBoundingBox = false;
  m_boundingBox = new BoundingBox(ngl::Vec3(-1, -1, -1), ngl::Vec3(1, 1, 1));
}

ppnp::PPNP::~PPNP()
{
  if(m_lattice != nullptr)
  {
    delete m_lattice;
  }

  if(m_dendrite != nullptr)
  {
    delete m_dendrite;
  }

  if(m_boundingBox != nullptr)
  {
    delete m_boundingBox;
  }
}

void ppnp::PPNP::createLattice()
{
  if(m_lattice != nullptr)
  {
    m_lattice->construct();
    m_dendrite = new ppnp::Dendrite(m_lattice);
  }
  else
  {
    std::cerr <<"No lattice was created - abort operation." << std::endl;
    return;
  }
}

void ppnp::PPNP::createBoundingBox(const ngl::Vec3 &_min, const ngl::Vec3 &_max)
{
  if(m_boundingBox != nullptr)
  {
    delete m_boundingBox;
    m_boundingBox = nullptr;
  }

  m_boundingBox = new BoundingBox(_min, _max);
}

void ppnp::PPNP::setRootByIndex(const int &_rootIndex)
{
  m_dendrite->setRootByIndex(_rootIndex);
}

void ppnp::PPNP::calculateDistances()
{
  Dijkstra::algorithm(m_dendrite);
}

void ppnp::PPNP::addEndPointByIndex(const int &_endpointIndex)
{
  m_dendrite->addEndPointByIndex(_endpointIndex);
}

void ppnp::PPNP::removeEndPointByIndex(const int &_endpointIndex)
{
  m_dendrite->removeEndPointByIndex(_endpointIndex);
}

void ppnp::PPNP::findPaths()
{
  m_dendrite->backtrack();
}

std::vector<int> ppnp::PPNP::setRandomEndPoints()
{
  return m_dendrite->setRandomEndPoints();
}

std::vector<int> ppnp::PPNP::setRandomEndPoints(const int &_num, const ngl::Vec3 &_minBounds, const ngl::Vec3 &_maxBounds)
{
  return m_dendrite->setRandomEndPoints(_num, _minBounds, _maxBounds);
}

void ppnp::PPNP::exportPaths()
{
  m_dendrite->save();
}

ppnp::Lattice::Type ppnp::PPNP::convert(LatticeOptions _lattice)
{
  switch(_lattice)
  {
    case LatticeOptions::Hexagon: return ppnp::Lattice::Hexagon;
    case LatticeOptions::Square: return ppnp::Lattice::Square;
    default : return ppnp::Lattice::Square;
  }
}

WeightFunction::Type ppnp::PPNP::convert(PPNP::WeightOptions _weightfunc)
{
  switch(_weightfunc)
  {
    case WeightOptions::Default: return WeightFunction::Type::Default;
    case WeightOptions::Image: return WeightFunction::Type::Image;
    default: return WeightFunction::Type::Default;
  }
}

void ppnp::PPNP::draw(ngl::Mat4 &_mouseGlobalTX, ngl::Camera &_cam)
{
  if (m_drawDendrite && m_dendrite->hasPaths())
  {
    m_dendrite->draw(_mouseGlobalTX, _cam);
  }

  if(m_drawLattice)
  {
    m_lattice->draw(_mouseGlobalTX, _cam);
  }

  if(m_boundingBox != nullptr && m_drawBoundingBox)
  {
    m_boundingBox->draw(_mouseGlobalTX, _cam);
  }
}

void ppnp::PPNP::setWeightFunctionDisplay(const bool _display)
{
  m_lattice->setWeightFunctionDisplay(_display);
}

void ppnp::PPNP::refinePaths()
{
  m_dendrite->refinePaths();
}

void ppnp::PPNP::setPathSelected(const int _endpointIndex, const bool _selected)
{
  if(m_dendrite->hasPaths())
  {
    Node * endpoint = m_lattice->findByIndex(_endpointIndex);

    if(endpoint != nullptr)
    {
      for(int i = 0; i < m_dendrite->m_paths.size(); ++i)
      {
        Path * p = m_dendrite->m_paths[i];

        if(p->m_points[0] == endpoint->m_pos)
        {
          p->setSelected(_selected);
        }
      }
    }
  }
}


