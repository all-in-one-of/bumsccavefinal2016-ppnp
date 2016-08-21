#ifndef SQUARE_H
#define SQUARE_H

#include "graph/Lattice.h"

#include <memory>

#include <ngl/VertexArrayObject.h>
namespace ppnp
{

//----------------------------------------------------------------------------------------------------------------------
/// @class Hexagon
/// @brief Construct square plane
/// @author Erika Camilleri
/// @version 1.0
/// @date 06/16/16
//----------------------------------------------------------------------------------------------------------------------
class Square : public Lattice
{
  public:
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief constructor to build *regular* hexagonal 2D lattice
    /// @param[in] _n         steps for rows/cols
    /// @param[in] _distance  distance between 2 points
    //----------------------------------------------------------------------------------------------------------------------
    Square(const int &_n, const ngl::Real &_distance, const ngl::Vec3 &_centre, bool _3D = false, bool _irregular = false);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief constructor with inheritence to build *regular* hexagonal 2D lattice
    /// @param[in] _n         centered hexagonal number
    /// @param[in] _distance  distance between 2 points
    /// @param[in] _isWeighted  whether or not the lattice edges have weights (inherited param)
    //----------------------------------------------------------------------------------------------------------------------
    Square(const int &_n, const ngl::Real &_distance, const ngl::Vec3 &_centre, const ngl::Real &_isWeighted, bool _3D = false, bool _irregular = false) : Lattice(_isWeighted)
    {
      // if the user input is not good
      // then put in good default values
      m_n = _n;
      m_distance = _distance;
      m_edgeLength = _distance;

      if(_n < 1)
      {
        m_n = 1;
      }

      if(_distance < 0)
      {
        m_distance = 1;
      }

      m_height = 2 * (m_n * m_distance);
      m_width = 2 * (m_n * m_distance);

      m_3D = _3D;
      m_irregular = _irregular;
      m_centre = _centre;

      m_type = ppnp::Lattice::Square;
    }
    virtual void construct();
    virtual void save();
    virtual void load();

    ngl::Vec2 fuv(const ngl::Vec3 &_vertex);
  protected:
  private:
    ngl::Vec3 m_centre;
    int m_n;
    ngl::Real m_distance;
    bool m_3D;
    bool m_irregular;
};

} //end namespace ppnp

#endif // end SQUARE_H
