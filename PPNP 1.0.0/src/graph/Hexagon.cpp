#include "graph/Hexagon.h"
#include "graph/Node.h"
#include "utils/Logger.h"

ppnp::Hexagon::Hexagon(const int &_n, const ngl::Real &_distance)
{
  m_n = _n;
  m_distance = _distance;
  m_edgeLength = _distance;
  m_height = ( (_n * 2 ) - 2) * _distance;
  m_width = ( (_n * 2 ) - 2) * _distance;
}

void ppnp::Hexagon::construct()
{
  /// The following section is adapted from :-
  /// Mohamed (2013). Algorithm to generate 2D magic hexagon lattice [online]. [Accessed 6 Jun 2016].
  /// Available from: <http://stackoverflow.com/questions/14280831/algorithm-to-generate-2d-magic-hexagon-lattice>.

  // some good default values
  int n = 2;
  ngl::Real distance = 1.0;

  // try put user input in
  if (m_distance > 0)
  {
    distance = m_distance;
  }

  if(m_n > 2)
  {
    n = m_n;
  }

  ngl::Vec3 node_pos = ngl::Vec3();
  int node_index = 0;
  for (int i = 0; i < n; ++i)
  {
    // calc y
    node_pos.m_y = (std::sqrt(3)*i*distance)/2.0;

    for(int j = 0; j <= (2*(n-1) - i); ++j)
    {
      // calc x
      ngl::Real temp = (-((2*n)-i-2)*distance)/2.0;
      node_pos.m_x = temp + (j*distance);

      Node* node = new Node(node_index++, node_pos);
      addNode(node);

      if(node_pos.m_y != 0)
      {
        node_pos.m_y = node_pos.m_y * -1;

        Node* node = new Node(node_index++, node_pos);
        addNode(node);
      }
    }
  }

  /// end of Citation

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
}

void ppnp::Hexagon::load()
{

}

void ppnp::Hexagon::save()
{

}

