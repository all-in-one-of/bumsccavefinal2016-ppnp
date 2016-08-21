#include "graph/Lattice.h"
#include "graph/Hexagon.h"
#include "graph/Square.h"
#include "functions/ImageWeightFunction.h"

#include <ngl/Util.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>
#include <ngl/Camera.h>

#include <cmath>
#include <stdlib.h>
#include <algorithm>
#include <typeinfo>

#include <boost/lexical_cast.hpp>

ppnp::Lattice * ppnp::Lattice::factory(const Type &_type, std::vector<std::string> _args)
{
  int size = _args.size();
  switch(_type)
  {
    case Type::Hexagon:
    {
      int n = 2;
      ngl::Real distance = 1.0;

      if(_args.size() == 2)
      {
        try
        {
            n = boost::lexical_cast<int>(_args[0]);
            distance = boost::lexical_cast<float>(_args[1]);
            return new ppnp::Hexagon(n, distance);
        }
        catch( boost::bad_lexical_cast const& )
        {
            std::cerr << "Cannot create Hexagon Lattice because of bad arguments." << std::endl;
            return nullptr;
        }
      }
      else if (_args.size() == 3)
      {
        try
        {
          n = boost::lexical_cast<int>(_args[0]);
          distance = boost::lexical_cast<float>(_args[1]);
          bool isWeighted = boost::lexical_cast<bool>(_args[2]);
          return new ppnp::Hexagon(n, distance, isWeighted);
        }
        catch ( boost::bad_lexical_cast const& )
        {
          std::cerr << "Cannot create Hexagon Lattice because of bad arguments." << std::endl;
          return nullptr;
        }
      }
      else
      {
        std::cerr << "Cannot create Hexagon Lattice because too few or many arguments" << std::endl;
        return nullptr;
      }
    }
    case Type::Square:
    {
      int n = 2;
      ngl::Real distance = 1.0;

      if(_args.size() == 2)
      {
        try
        {
            n = boost::lexical_cast<int>(_args[0]);
            distance = boost::lexical_cast<float>(_args[1]);
            return new ppnp::Square(n, distance, ngl::Vec3(0, 0, 0), false, false);
        }
        catch( boost::bad_lexical_cast const& )
        {
            std::cerr << "Cannot create Square Lattice because of bad arguments." << std::endl;
            return nullptr;
        }
      }
      else if (_args.size() == 3)
      {
        try
        {
          n = boost::lexical_cast<int>(_args[0]);
          distance = boost::lexical_cast<float>(_args[1]);
          bool isWeighted = boost::lexical_cast<bool>(_args[2]);
          return new ppnp::Square(n, distance, ngl::Vec3(0, 0, 0), isWeighted, false, false);
        }
        catch ( boost::bad_lexical_cast const& )
        {
          std::cerr << "Cannot create Square Lattice because of bad arguments." << std::endl;
          return nullptr;
        }
      }
      else if (_args.size() == 8)
      {
        n = boost::lexical_cast<int>(_args[0]);
        distance = boost::lexical_cast<float>(_args[1]);
        ngl::Vec3 centre;
        centre.m_x = boost::lexical_cast<float>(_args[2]);
        centre.m_y = boost::lexical_cast<float>(_args[3]);
        centre.m_z = boost::lexical_cast<float>(_args[4]);
        bool isWeighted = boost::lexical_cast<bool>(_args[5]);
        bool is3D = boost::lexical_cast<bool>(_args[6]);
        bool isIrregular = boost::lexical_cast<bool>(_args[7]);
        return new ppnp::Square(n, distance, centre, isWeighted, is3D, isIrregular);
      }
      else
      {
        std::cerr << "Cannot create Square Lattice because too few or many arguments" << std::endl;
        return nullptr;
      }
    }
    default:
    {
      return nullptr;
    }
  }
}

ppnp::Lattice::~Lattice()
{
  // loop through entries in m_nodes map
  for(auto &ent : m_nodes)
  {
    delete ent.second;
  }

  // delete weight
  if(m_isWeighted && m_weightFunction != nullptr)
  {
    delete m_weightFunction;
  }
}

void ppnp::Lattice::draw(ngl::Mat4 &_mouseGlobalTX, ngl::Camera &_cam)
{
  for(int i = 0; i < m_nodes.size(); ++i)
  {
    m_nodes[i]->draw(_mouseGlobalTX, _cam);
  }

  if(m_weightFunctionDisplay && m_isWeighted && m_weightFunction != nullptr && typeid(*m_weightFunction).hash_code() == typeid(ImageWeightFunction).hash_code())
  {
    ((ImageWeightFunction*)m_weightFunction)->display(_mouseGlobalTX, _cam);
  }
}

void ppnp::Lattice::addNode(Node *_node)
{
  m_nodes.insert(std::pair<int, Node*>(_node->m_index, _node));
}

ppnp::Node * ppnp::Lattice::findByIndex(const int &_index)
{
  Node * found = nullptr;
  std::map<int,Node*>::iterator it;

  it = m_nodes.find(_index);

  if(it !=  m_nodes.end())
  {
    found = m_nodes.find(_index)->second;
  }

  return found;
}

ppnp::Node* ppnp::Lattice::findNodeAt(const ngl::Vec3 &_pos)
{
  Node * found = nullptr;

  for(auto &ent : m_nodes)
  {
    Node * current = ent.second;
    if(current->m_pos == _pos)
    {
      found = current;
    }
  }

  return found;
}

ngl::Real ppnp::Lattice::findEdgeWeight(Node* _node1, Node* _node2)
{
  ngl::Real weight = -1;

  for(auto &ent : m_nodes)
  {
    Node* n = ent.second;

    if((n->m_index == _node1->m_index || n->m_index == _node2->m_index) && n->m_edges.size() > 0)
    {
      for(Node::Edge e : n->m_edges)
      {
        if((n->m_index == _node1->m_index && e.adjacent->m_index == _node2->m_index) ||
           (n->m_index == _node2->m_index && e.adjacent->m_index == _node1->m_index))
        {
          weight = e.weight;
        }
      }
    }
  }

  return weight;
}

void ppnp::Lattice::setWeightFunction(const WeightFunction::Type &_type, std::vector<std::string> _args)
{
  if(_type == WeightFunction::Type::Image)
  {
    m_maxWeightValue = 1;
  }
  else
  {
    m_maxWeightValue = 999;
  }

  _args.push_back(std::to_string(m_width));
  _args.push_back(std::to_string(m_height));
  m_weightFunction = WeightFunction::factory(_type, _args);
}

std::map<std::string, ngl::Real> ppnp::Lattice::getEdgeWeights()
{
  std::map<std::string, ngl::Real> weight_map;

  std::map<std::string, ngl::Real>::iterator it;

  // traverse each node
  for(auto &n : m_nodes)
  {
    Node* current = n.second;

    // traverse each edge
    for (Node::Edge e: current->m_edges)
    {
      ngl::Vec3 offset;
      ngl::Vec3 midpoint;
      if(e.adjacent->m_pos.m_x > current->m_pos.m_x || e.adjacent->m_pos.m_y > current->m_pos.m_y || e.adjacent->m_pos.m_z > current->m_pos.m_z)
      {
        offset = (e.adjacent->m_pos - current->m_pos)/2.0;
        midpoint = current->m_pos + offset;
      }
      else
      {
        offset = (current->m_pos - e.adjacent->m_pos)/2.0;
        midpoint = e.adjacent->m_pos + offset;
      }

      std::string midpoint_str = std::to_string(midpoint.m_x) + "," + std::to_string(midpoint.m_y) + "," + std::to_string(midpoint.m_z) + ",";

      it = weight_map.find(midpoint_str);
      if(it ==  weight_map.end())
      {
        weight_map.insert(std::pair<std::string, ngl::Real>(midpoint_str, e.weight));
      }
    }
  }

  return weight_map;
}

void ppnp::Lattice::save()
{

}

void ppnp::Lattice::load()
{

}

ngl::Real ppnp::Lattice::getEdgeLength()
{
  return m_edgeLength;
}
