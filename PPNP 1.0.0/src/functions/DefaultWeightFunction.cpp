#include "functions/DefaultWeightFunction.h"

#include <ngl/Random.h>

DefaultWeightFunction::DefaultWeightFunction(const ngl::Real &_alpha, const ngl::Real &_randMax)
{
  m_alpha = _alpha;
  m_randMax = _randMax;
  m_type = WeightFunction::Default;
}

void DefaultWeightFunction::function(ppnp::Node *_node, ppnp::Node::Edge *_edge)
{
  ngl::Random* rand = ngl::Random::instance();
  ngl::Real weight = rand->randomPositiveNumber(m_randMax);
  _edge->weight = std::pow(weight, m_alpha);
}
