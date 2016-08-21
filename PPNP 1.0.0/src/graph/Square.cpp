#include "graph/Square.h"
#include "graph/Node.h"
#include "utils/Logger.h"
#include "ngl/Random.h"

ppnp::Square::Square(const int &_n, const ngl::Real &_distance, const ngl::Vec3 &_centre, bool _3D, bool _irregular)
{
//  m_n = _n;
//  m_distance = _distance;
//  m_edgeLength = _distance;
//  m_height = _n * _distance;
//  m_width = _n * _distance;
//  m_3D = _3D;
//  m_irregular = _irregular;
//  m_centre = _centre;

//  m_type = ppnp::Lattice::Square;
}

ngl::Vec2 ppnp::Square::fuv(const ngl::Vec3 &_vertex)
{
  ngl::Real max_value = m_n *  m_distance;
  ngl::Real num_steps = m_width/m_distance;
  ngl::Real uv_step = 1/num_steps;

  ngl::Real x_step = (max_value - _vertex.m_x)/m_distance;
  ngl::Real y_step = (max_value - _vertex.m_y)/m_distance;

  ngl::Real u = 1 - (x_step * uv_step);
  ngl::Real v = 1 - (y_step * uv_step);

  return ngl::Vec2(u, v);
}

void ppnp::Square::construct()
{
  // some good default values
  int n = 1;
  ngl::Real distance = 1.0;

  // try put user input in
  if (m_distance > 0)
  {
    distance = m_distance;
  }

  if(m_n > 1)
  {
    n = m_n;
  }

  ngl::Vec3 node_pos = ngl::Vec3(0, 0, 0);
  int node_index = 0;
  int repeat_z = 0;

  if(m_3D)
  {
    repeat_z = 2*n;
  }

  for(int k = 0; k <= repeat_z; ++k)
  {
    // calc z
    if(k != 0 && k%2 == 0)
    {
      node_pos.m_z = m_centre.m_z + ((k/2)*distance*-1);
    }
    else if (k != 0 && k%2 != 0)
    {
      node_pos.m_z = m_centre.m_z + (((k+1)/2)*distance);
    }
    else
    {
      node_pos.m_z = m_centre.m_z + 0;
    }

    for (int i = 0; i <= 2*n; ++i)   // columns
    {
      // calc x
      // if i not zero, and is even
      if(i != 0 && i%2 == 0)
      {
        node_pos.m_x = m_centre.m_x + ((i/2)*distance*-1);

      }
      // if i is not zero annd not even
      else if (i != 0 && i%2 != 0)
      {
        node_pos.m_x = m_centre.m_x + (((i+1)/2)*distance);
      }
      else
      {
        node_pos.m_x = m_centre.m_x + 0;
      }

      for (int j = 0; j <= 2*n; ++j)   // columns
      {
        // calc y
        // if i not zero, and is even
        if(j != 0 && j%2 == 0)
        {
          node_pos.m_y = m_centre.m_y + ((j/2)*distance*-1);

        }
        // if i is not zero annd not even
        else if (j != 0 && j%2 != 0)
        {
          node_pos.m_y = m_centre.m_y + (((j+1)/2)*distance);
        }
        else
        {
          node_pos.m_y = m_centre.m_y + 0;
        }

        Node* node = new Node(node_index++, node_pos);
        addNode(node);

      }

//      for(int j = 0; j <= n; ++j)   // rows
//      {



//        node_pos.m_y = m_centre.m_y + (j*distance);
//        Node* node = new Node(node_index++, node_pos);
//        addNode(node);

//        if(node_pos.m_y != 0 && node_pos.m_y != m_centre.m_y)
//        {
//          node_pos.m_y = m_centre.m_y + (node_pos.m_y * -1);
//          Node* node = new Node(node_index++, node_pos);
//          addNode(node);
//        }
//      }
    }
  }

  // now we have to process all the nodes and form all the possible edges between the nodes
  for (int i = 0; i < m_nodes.size(); ++i)
  {
    for(int j = 0; j < m_nodes.size(); ++j)
    {
      ngl::Vec3 difference = m_nodes[i]->m_pos - m_nodes[j]->m_pos;
      ngl::Real d = std::sqrt(std::pow(difference.m_x, 2) + std::pow(difference.m_y, 2) + std::pow(difference.m_z, 2));
      // sometimes the distance is extremely close to value - no roudning up is happening here, so we have to make sure
      // that we do not get affected by really small error
      ngl::Real error = std::abs(distance - d);

      if(error <= 0.001)
      {
        ngl::Real edge_len = difference.length();

        if(m_isWeighted)
        {
          m_rand = ngl::Random::instance();
          m_rand->setSeed(i + j);

          // see if the edge already exsists so that
          // if it does then we can reuse the weight
          ngl::Real exist_weight = findEdgeWeight(m_nodes[i], m_nodes[j]);

          // we have found a weight so let us use the same one
          if(exist_weight != -1)
          {
            m_nodes[i]->addEdge(m_nodes[j], exist_weight, edge_len);
          }
          else
          {
            // let us add the edge... and then assign the weight later...
            m_nodes[i]->addEdge(m_nodes[j], 1, edge_len);

            // check if a function is chosen...
            if(m_weightFunction != nullptr)
            {
              m_weightFunction->function(m_nodes[i], &(m_nodes[i]->m_edges.back()));
            }
          }
        }
        else
        {
          m_nodes[i]->addEdge(m_nodes[j], 1, edge_len);
        }
      }
    }
  }

  if(m_irregular)
  {
    for(auto &ent : m_nodes)
    {
      Node* node = ent.second;
      ngl::Random* rand = ngl::Random::instance();
      ngl::Real rand_x = rand->randomPositiveNumber(m_distance/2) - (m_distance/2);
      node->m_pos.m_x += rand_x;
      ngl::Real rand_y = rand->randomPositiveNumber(m_distance/2) - (m_distance/2);
      node->m_pos.m_y += rand_y;

      if(m_3D)
      {
        ngl::Real rand_z = rand->randomPositiveNumber(m_distance/2) - (m_distance/2);
        node->m_pos.m_z += rand_z;
      }
    }
  }

  // lets log the info
  Logger* logger = Logger::instance();

  for(auto &ent : m_nodes)
  {
    Node * node = ent.second;

    std::string log = "";

    log = "Node " + std::to_string(node->m_index) + " : " +  std::to_string(node->m_pos.m_x) + ", " + std::to_string(node->m_pos.m_y) + ", " + std::to_string(node->m_pos.m_z) + " uv: " + std::to_string(node->m_uv.m_x) + ", " + std::to_string(node->m_uv.m_y) + "\n\n";
    //logger->log(log);

    int hasBadEdge = false;
    for(Node::Edge &e : node->m_edges)
    {
       log = log + "Edge " + std::to_string(e.adjacent->m_index) + " : " +  std::to_string(e.adjacent->m_pos.m_x) + ", " + std::to_string(e.adjacent->m_pos.m_y) + ", " + std::to_string(e.adjacent->m_pos.m_z) + " weight: " + std::to_string(e.weight) + "\n";

       if(e.weight >= m_maxWeightValue &&   m_weightFunction->m_type == WeightFunction::Image)
       {
         hasBadEdge = true;

       }
    }

    if (!hasBadEdge)
    {
      logger->log(log + "\n");
      node->m_isEligableEndPoint = true;
    }
    else
    {
      node->m_isEligableEndPoint = false;
    }
  }
}

void ppnp::Square::load()
{

}

void ppnp::Square::save()
{

}
