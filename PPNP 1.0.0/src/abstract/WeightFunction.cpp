#include "abstract/WeightFunction.h"
#include "functions/DefaultWeightFunction.h"
#include "functions/ImageWeightFunction.h"

#include <boost/lexical_cast.hpp>

WeightFunction * WeightFunction::factory(const WeightFunction::Type &_type, std::vector<std::string> _args)
{
  switch(_type)
  {
    case WeightFunction::Type::Default:
    {
      if(_args.size() >= 2)
      {
        try
        {
          ngl::Real alpha = boost::lexical_cast<float>(_args[0]);
          ngl::Real randmax =  boost::lexical_cast<float>(_args[1]);
          return new DefaultWeightFunction(alpha, randmax);
        }
        catch( boost::bad_lexical_cast const& )
        {
          std::cerr << "Cannot create Weight Function because of bad arguments arguments." << std::endl;
          return nullptr;
        }
      }
      else
      {
        std::cerr << "Cannot create Weight Function because of too many/few arguments." << std::endl;
        return nullptr;
      }
    }
    case WeightFunction::Type::Image:
    {
      if(_args.size() == 1)
      {
        std::string filename = _args[0];
        return new ImageWeightFunction(filename);
      }
      else if (_args.size() == 3)
      {
        std::string filename = _args[0];

        try
        {
          ngl::Real width = boost::lexical_cast<float>(_args[1]);
          ngl::Real height = boost::lexical_cast<float>(_args[2]);
          return new ImageWeightFunction(filename, width, height);
        }
        catch( boost::bad_lexical_cast const& )
        {
          std::cerr << "Cannot create Weight Function because of bad arguments arguments." << std::endl;
          return nullptr;
        }
      }
      else
      {
        std::cerr << "Cannot create Weight Function because of too many/few arguments." << std::endl;
        return nullptr;
      }
    }
    default: return nullptr;
  }
}
