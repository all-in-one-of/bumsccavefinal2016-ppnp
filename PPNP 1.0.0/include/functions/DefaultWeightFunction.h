#ifndef DEFAULTWEIGHTFUNCTION_H
#define DEFAULTWEIGHTFUNCTION_H

#include <cmath>

#include <ngl/Util.h>

#include "abstract/WeightFunction.h"

//----------------------------------------------------------------------------------------------------------------------
/// @file DefaultWeightFunction.h
/// @brief Default weight function definition
/// @author Erika Camilleri
/// @version 1.0
/// ----------------------------------------------------------------------------------------------------------------------
class DefaultWeightFunction : public WeightFunction
{
  public:
    DefaultWeightFunction(const ngl::Real &_alpha, const ngl::Real &_randMax);
    void function(ppnp::Node* _node, ppnp::Node::Edge* _edge);
  private:
    ngl::Real m_alpha;
    ngl::Real m_randMax;
};

#endif
