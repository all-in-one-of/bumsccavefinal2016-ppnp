#ifndef WEIGHTFUNCTION_H
#define WEIGHTFUNCTION_H

#include <vector>
#include <string>

#include <ngl/Util.h>

#include "graph/Node.h"

//----------------------------------------------------------------------------------------------------------------------
/// @file WeightFunction.h
/// @brief Base Class that defines any weight function
/// @author Erika Camilleri
/// @version 1.0
/// ----------------------------------------------------------------------------------------------------------------------
class WeightFunction
{
  public:
    enum Type { None = 0, Default = 1, Image = 2 };
    virtual void function(ppnp::Node* _node, ppnp::Node::Edge* _edge) = 0;
    static WeightFunction * factory(const WeightFunction::Type &_type, std::vector<std::string> _args);
    WeightFunction::Type m_type;
  protected:
    WeightFunction() {}
};

#endif
