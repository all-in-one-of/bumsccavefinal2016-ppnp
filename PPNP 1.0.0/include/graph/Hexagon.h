#ifndef HEXAGON_H
#define HEXAGON_H

#include "graph/Lattice.h"

#include <memory>

#include <ngl/VertexArrayObject.h>
namespace ppnp
{

//----------------------------------------------------------------------------------------------------------------------
/// @class Hexagon
/// @brief Construct triangulated hexagon plane
/// @author Erika Camilleri
/// @version 1.0
/// @date 06/16/16
//----------------------------------------------------------------------------------------------------------------------
class Hexagon : public Lattice
{
  public:
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief constructor to build *regular* hexagonal 2D lattice
    /// @param[in] _n         centered hexagonal number
    /// @param[in] _distance  distance between 2 points
    //----------------------------------------------------------------------------------------------------------------------
    Hexagon(const int &_n, const ngl::Real &_distance);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief constructor with inheritence to build *regular* hexagonal 2D lattice
    /// @param[in] _n         centered hexagonal number
    /// @param[in] _distance  distance between 2 points
    /// @param[in] _isWeighted  whether or not the lattice edges have weights (inherited param)
    //----------------------------------------------------------------------------------------------------------------------
    Hexagon(const int &_n, const ngl::Real &_distance, const ngl::Real &_isWeighted) : Lattice(_isWeighted)
    {
      m_n = _n;
      m_distance = _distance;
      m_height = ( (_n * 2 ) - 2) * _distance;
      m_width = ( (_n * 2 ) - 2) * _distance;
    }
    virtual void construct();
    virtual void save();
    virtual void load();
  protected:
  private:
    int m_n;
    ngl::Real m_distance;
};

} //end namespace ppnp

#endif // end HEXAGON_H
