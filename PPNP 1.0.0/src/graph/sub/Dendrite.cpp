#include "graph/sub/Dendrite.h"
#include "alg/Dijkstra.h"

#include <ctime>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <algorithm>

ppnp::Dendrite::Dendrite(Lattice *_lattice)
{
  m_lattice = _lattice;
  m_dirpath = "../xml/";
  std::time_t result = std::time(nullptr);
  std::string timestamp = std::asctime(std::localtime(&result));
  boost::algorithm::trim(timestamp);
  m_filename = m_dirpath + "sample_" + timestamp + ".xml";

  // init distances to "infinity"
  for (auto &ent : m_lattice->m_nodes)
  {
    m_rootNodeDist.insert(std::pair<int, ngl::Real>(ent.first, MAX_DIST));
  }
}

ppnp::Dendrite::~Dendrite()
{
  if(m_paths.size() > 0)
  {
    for(Path* p : m_paths)
    {
      delete p;
    }
  }
}

void ppnp::Dendrite::setRoot(Node *_root)
{
  m_root = _root;
}

void ppnp::Dendrite::setRootByIndex(const int &_rootIndex)
{
  Node * root = m_lattice->findByIndex(_rootIndex);

  if(root != nullptr)
  {
    m_root = root;
  }
}

void ppnp::Dendrite::setRootAtPosition(const ngl::Vec3 &_pos)
{
  Node * root = m_lattice->findNodeAt(_pos);

  if(root != nullptr)
  {
    m_root = root;
  }
}

void ppnp::Dendrite::addEndPoint(Node *_endpoint)
{
  m_endpoints.push_back(_endpoint);
}

void ppnp::Dendrite::addEndPointAt(const ngl::Vec3 &_pos)
{
  Node * endpoint = m_lattice->findNodeAt(_pos);

  if(endpoint != nullptr)
  {
    m_endpoints.push_back(endpoint);
  }
}

std::vector<int> ppnp::Dendrite::setRandomEndPoints()
{
  int count = 25;
  std::vector<int> eligableNodeIndices;
  std::vector<int> randomEndPoints;

  for(auto &ent : m_lattice->m_nodes)
  {
    Node * node = ent.second;
    if(node->m_isEligableEndPoint)
    {
      eligableNodeIndices.push_back(node->m_index);
    }
  }

  std::random_shuffle(eligableNodeIndices.begin(), eligableNodeIndices.end());

  for(int i = 0; i < count; ++i)
  {
    addEndPointByIndex(eligableNodeIndices[i]);
    randomEndPoints.push_back(eligableNodeIndices[i]);
  }

  return randomEndPoints;
}

std::vector<int> ppnp::Dendrite::setRandomEndPoints(const int &_num, const ngl::Vec3 &_minBounds, const ngl::Vec3 &_maxBounds)
{
  std::vector<int> eligableNodeIndices;
  std::vector<int> randomEndPoints;

  for(auto &ent : m_lattice->m_nodes)
  {
    Node * node = ent.second;

    if(node->m_isEligableEndPoint &&
       node->m_pos.m_x >= _minBounds.m_x && node->m_pos.m_x <= _maxBounds.m_x &&
       node->m_pos.m_y >= _minBounds.m_y && node->m_pos.m_y <= _maxBounds.m_y &&
       node->m_pos.m_z >= _minBounds.m_z && node->m_pos.m_z <= _maxBounds.m_z)
    {
      eligableNodeIndices.push_back(node->m_index);
    }
  }

  std::random_shuffle(eligableNodeIndices.begin(), eligableNodeIndices.end());

  for(int i = 0; i < _num; ++i)
  {
    addEndPointByIndex(eligableNodeIndices[i]);
    randomEndPoints.push_back(eligableNodeIndices[i]);
  }

  return randomEndPoints;
}

void ppnp::Dendrite::removeEndPointByIndex(const int &_endpointIndex)
{
  Node * endpoint = m_lattice->findByIndex(_endpointIndex);

  if(endpoint != nullptr)
  {
    m_endpoints.erase(std::remove(m_endpoints.begin(), m_endpoints.end(), endpoint), m_endpoints.end());

    if(!m_paths.empty())
    {
      for(Path* p : m_paths)
      {
        if(p->m_points[0] == endpoint->m_pos)
        {
          m_paths.erase(std::remove(m_paths.begin(), m_paths.end(), p), m_paths.end());
        }
      }
    }
  }
}

void ppnp::Dendrite::addEndPointByIndex(const int &_endpointIndex)
{
  Node * endpoint = m_lattice->findByIndex(_endpointIndex);
  std::vector<Node*>::iterator it;
  it = std::find(m_endpoints.begin(), m_endpoints.end(), endpoint);

  if(it == m_endpoints.end() && endpoint != nullptr)
  {
    m_endpoints.push_back(endpoint);
  }
}

ngl::Real ppnp::Dendrite::getDistanceFromRoot(const int &_nodeIndex)
{
  ngl::Real distance = -1;
  std::map<int, ngl::Real>::iterator it;

  it = m_rootNodeDist.find(_nodeIndex);

  if(it != m_rootNodeDist.end())
  {
    distance = m_rootNodeDist.find(_nodeIndex)->second;
  }

  return distance;
}

bool ppnp::Dendrite::hasPaths()
{
  return (m_paths.size() > 0);
}

void ppnp::Dendrite::backtrack()
{
  for (int i = 0; i < m_endpoints.size(); ++i)
  {
    bool path_exists = false;

    // check if path already has been generated
    if(!m_paths.empty())
    {
      ngl::Vec3 endpoint_pos = m_endpoints[i]->m_pos;

      for(Path* p : m_paths)
      {
        if(p->m_points[0] == endpoint_pos)
        {
          path_exists = true;
        }
      }
    }

    if(!path_exists)
    {
      Path* p = backtrack(m_endpoints[i]);

      // finally add the path
      if(p != nullptr)
      {
         m_paths.push_back(p);
      }
    }
  }
}

ppnp::Path* ppnp::Dendrite::backtrack(ppnp::Node * _endpoint)
{
  // initialize stuff for greedy
  Path* p = new Path();                                            // init a path
  std::vector<int> node_indices_in_path;                           // keep track of the nodes already in path
  std::vector<int> bad_node_indices;                               // keep track of the nodes that are causing problems
  p->addPoint(_endpoint->m_pos);                                   // add the end point as part of the path
  Node* current = _endpoint;                                       // set current to the end point (starting point)
  node_indices_in_path.push_back(_endpoint->m_index);              // add endpoint index to the path

  // do not stop until current is root
  while(current->m_index != m_root->m_index && p != nullptr)
  {
    // get all the adjacent nodes from the end point
    // using the rootNodeDist map, select the adjacent node
    // that has the least cost or select the root if an option
    Node * step = nullptr;
    ngl::Real step_distance = this->MAX_DIST;

    for (Node::Edge e : current->m_edges)
    {
      // check if adjacent node is already in the path
      std::vector<int>::iterator it_inpath = std::find(node_indices_in_path.begin(), node_indices_in_path.end(), e.adjacent->m_index);
      // or is a bad node
      std::vector<int>::iterator it_badnode = std::find(bad_node_indices.begin(), bad_node_indices.end(), e.adjacent->m_index);

      if(it_inpath == node_indices_in_path.end() && it_badnode == bad_node_indices.end())
      {
        // let us find the distance
        ngl::Real distance = m_rootNodeDist.find(e.adjacent->m_index)->second;
        if(distance < step_distance)
        {
          step_distance = distance;
          step = e.adjacent;
        }
      }
    }

    if(step != nullptr)
    {
      // add the position to the path
      p->addPoint(step->m_pos);
      // add index
      node_indices_in_path.push_back(step->m_index);
      // set the current to the next node
      current = step;
    }
    else
    {
      if(!node_indices_in_path.empty())
      {
        // we should perhaps go back a step and choose a different route
        int bad_node = node_indices_in_path.back();
        // put it in the bad nodes
        bad_node_indices.push_back(bad_node);
        // remove from the path
        node_indices_in_path.pop_back();
        // remove from the path
        p->m_points.pop_back();
        // get the last good node
        int step_back = node_indices_in_path.back();
        // set it as the current
        current = m_lattice->m_nodes.find(step_back)->second;
      }
      else
      {
        // no path found!
        p = nullptr;
      }
    }
  }

  return p;
}

void ppnp::Dendrite::save()
{
  std::time_t result = std::time(nullptr);
  std::string timestamp = std::asctime(std::localtime(&result));
  boost::algorithm::trim(timestamp);
  m_filename = m_dirpath + "sample_" + timestamp + ".xml";

  QString outputFilename = QString::fromUtf8(m_filename.c_str());
  QFile outputFile(outputFilename);
  outputFile.open(QIODevice::Append);
  if(outputFile.isOpen())
  {
    QTextStream outStream(&outputFile);
    outStream << "<skeleton name='simple_example'>\n";
    for(int i = 0; i < m_paths.size(); ++i)
    {
      std::string pathname = "path_" + std::to_string(i);
      outStream << "<path name='" << QString::fromStdString(pathname) << "'>\n";
      for(ngl::Vec3 v : m_paths[i]->m_points)
      {
        outStream << "<vertex>\n";
        outStream << "<x>" << v.m_x << "</x>\n";
        outStream << "<y>" << v.m_y << "</y>\n";
        outStream << "<z>" << v.m_z << "</z>\n";
        outStream << "</vertex>\n";
      }
      outStream << "</path>";
    }
    outStream << "</skeleton>\n";
  }
  outputFile.close();
}

void ppnp::Dendrite::load()
{
  // cannot be implemented exception
}

void ppnp::Dendrite::draw(ngl::Mat4 &_mouseGlobalTX, ngl::Camera &_cam)
{
  for(Path *p : m_paths)
  {
    p->draw(_mouseGlobalTX, _cam);
  }
}

void ppnp::Dendrite::refinePaths()
{
  std::vector<Path*> temp_paths;

  if(!m_paths.empty())
  {
    // go through each path
    for(int j = 0; j < m_paths.size(); ++j)
    {
      Path* p = m_paths[j];

      // for each alternate vertex build a lattice around it
      for(int i = 0; i < p->m_points.size(); i=i+2)
      {
        // if there is an endpoint to get to
        if((i+2) < p->m_points.size())
        {
          // set up a temporary sub dendrites
          // new lattice parameters
          int n = 10;
         // ngl::Real distance = (m_lattice->getEdgeLength()*2)/n;
          ngl::Real distance = 0.2;
          ngl::Vec3 centre = p->m_points[i];
          std::vector<std::string> largs;
          largs.push_back(std::to_string(n));
          largs.push_back(std::to_string(distance));
          largs.push_back(std::to_string(centre.m_x));
          largs.push_back(std::to_string(centre.m_y));
          largs.push_back(std::to_string(centre.m_z));
          largs.push_back("1");
          largs.push_back("0");
          largs.push_back("0");

          // construct a temporary lattice
          ppnp::Lattice::Type ltype = m_lattice->getType();
          Lattice * temp_lattice = Lattice::factory(ltype, largs);

          std::vector<std::string> wargs;
          wargs.push_back("1"); // alpha
          wargs.push_back("4"); // random max value

          // set weight function to default
          temp_lattice->setWeightFunction(WeightFunction::Default ,wargs);
          temp_lattice->construct();

          Dendrite* temp_dendrite = new  Dendrite(temp_lattice);

          // set this position as the root
          temp_dendrite->setRootAtPosition(centre);

          Dijkstra::algorithm(temp_dendrite);

          // find next endpoint in lattice and set it as the endpoint
          temp_dendrite->addEndPointAt(p->m_points[i+2]);

          // generate new path
          temp_dendrite->backtrack();

          // and add to temp paths
          Path* temp_path = new Path();
          temp_path->m_points = temp_dendrite->m_paths[0]->m_points;
          temp_paths.push_back(temp_path);

          delete temp_dendrite;
        }
      }
    }

    m_paths = temp_paths;
  }
}




