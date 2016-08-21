#include "alg/Dijkstra.h"
#include "utils/Logger.h"

#include <vector>
#include <algorithm>

void ppnp::Dijkstra::algorithm(Dendrite* _graph)
{
  std::vector<int> unvisited_indices;     // list of the indices of the unfinished nodes

  /* All distances are init to infinity */
  for(auto &ent : _graph->m_rootNodeDist)
  {
    ent.second = _graph->MAX_DIST;
  }

  /* The distance from the root to itself is zero */
  std::map<int, ngl::Real>::iterator it;
  it = _graph->m_rootNodeDist.find(_graph->m_root->m_index);

  if(it != _graph->m_rootNodeDist.end())
  {
    _graph->m_rootNodeDist.find(_graph->m_root->m_index)->second = 0;
  }

  /* Add all vertices to queue */
  for(auto &ent : _graph->m_lattice->m_nodes)
  {
    unvisited_indices.push_back(ent.first);
  }

  // while we have missing visited nodes
  while(!unvisited_indices.empty())
  {
    // pick the node which is closest to the root node
    ngl::Real shortest_distance = _graph->MAX_DIST;
    int closest_node_index = -1;
    for(int i = 0; i < unvisited_indices.size(); ++i)
    {
      int index = unvisited_indices[i];
      ngl::Real current_distance = _graph->m_rootNodeDist.find(index)->second;
      if(current_distance < shortest_distance)
      {
          shortest_distance = current_distance;
          closest_node_index = index;
      }
    }

    // mark the node as visited
    if(closest_node_index != -1)
    {
      std::vector<int>::iterator it = std::find(unvisited_indices.begin(), unvisited_indices.end(), closest_node_index);
      // remove from queue
      unvisited_indices.erase(it);
    }

    if(closest_node_index == 5)
    {
      int temp = 0;
    }

    Node* closest_node = _graph->m_lattice->findByIndex(closest_node_index);

    for (Node::Edge e : closest_node->m_edges)
    {
      // if the distance of the current node and the weighted length of the adjacent edge, is less then,
      // the distance of the edge from root

      // distance between B from Root via A = Distance of A  + (Length of B * Weight of B)
      // ngl::Real distance_from_child_via_parent = (shortest_distance + e.length) * e.weight;
      ngl::Real distance_from_child_via_parent = shortest_distance + (e.length * e.weight);

      ngl::Real recorded_child_distance = _graph->m_rootNodeDist.find(e.adjacent->m_index)->second;

      // if what we calculated is less than the recorded distance then update...
      if((distance_from_child_via_parent < recorded_child_distance))
      {
        _graph->m_rootNodeDist.find(e.adjacent->m_index)->second = distance_from_child_via_parent;
        e.adjacent->m_previous = closest_node;
      }

      // never let distance be "infinity"
      // so clamp it to a lesser value
      if(_graph->m_rootNodeDist.find(e.adjacent->m_index)->second == _graph->MAX_DIST)
      {
        _graph->m_rootNodeDist.find(e.adjacent->m_index)->second = _graph->MAX_DIST - 1;
      }
    }
  }

  // once all this is ready we should have costs from root
//  Logger * logger = Logger::instance();
//  std::string msg = "Root Node: " + std::to_string(_graph->m_root->m_index) + " " + std::to_string(_graph->m_root->m_pos.m_x) + ", " + std::to_string(_graph->m_root->m_pos.m_y) + ", " + std::to_string(_graph->m_root->m_pos.m_z) + "\n";
//  logger->log(msg);
//  logger->log("------------------------------------------------------------------------------------------------");
//  for(auto &ent : _graph->m_rootNodeDist)
//  {
//    msg = "Distance from node: " + std::to_string(ent.first) + ": " + std::to_string(ent.second) + "\n";
//    logger->log(msg);
//  }
}
