#ifndef LATTICE_H
#define LATTICE_H

#include <memory>
#include <map>

#include <ngl/VertexArrayObject.h>
#include <ngl/Random.h>
#include <ngl/Camera.h>

#include "Node.h"
#include "abstract/WeightFunction.h"
#include "abstract/Portable.h"

namespace ppnp
{

//----------------------------------------------------------------------------------------------------------------------
/// @class Lattice
/// @brief Base lattice class representing graph structure
/// @author Erika Camilleri
/// @version 1.0
/// @date 06/16/16
//----------------------------------------------------------------------------------------------------------------------
class Lattice : public Portable
{
  public:
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief lattice types
    //----------------------------------------------------------------------------------------------------------------------
    enum Type{Square = 0, Hexagon = 1};
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief factory method to generate some form of lattice
    //----------------------------------------------------------------------------------------------------------------------
    static Lattice * factory(const Type &_type, std::vector<std::string> args);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the constructor that should be used to instance a lattice
    /// @param[in] _isWeighted    a flag to determine whether the edges should be weighted - this will effect distance/cost
    //----------------------------------------------------------------------------------------------------------------------
    Lattice(const bool &_isWeighted){ m_isWeighted = _isWeighted; }
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief standard destructor
    //----------------------------------------------------------------------------------------------------------------------
    ~Lattice();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief virtual method that is implemented by sub classes that algorithmically build a lattice
    //----------------------------------------------------------------------------------------------------------------------
    virtual void construct() = 0; 
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief add a node to the lattice
    //----------------------------------------------------------------------------------------------------------------------
    void addNode(Node * _node);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief draw the lattice
    //----------------------------------------------------------------------------------------------------------------------
    void draw(ngl::Mat4 &_mouseGlobalTX, ngl::Camera &_cam);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief get the node that has some index - efficient because of map structure
    /// @param[in] _index    index of the node you want
    //----------------------------------------------------------------------------------------------------------------------
    Node * findByIndex(const int &_index);


    Node * findNodeAt(const ngl::Vec3 &_pos);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief set up weight function
    //----------------------------------------------------------------------------------------------------------------------
    void setWeightFunction(const WeightFunction::Type &_type, std::vector<std::string> _args);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief get all the weights edges keyed by weight position so that all entries are unique
    /// had to put positions as a string
    //----------------------------------------------------------------------------------------------------------------------
    std::map<std::string, ngl::Real> getEdgeWeights();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief storing the node pointers into a map for efficient searching
    //----------------------------------------------------------------------------------------------------------------------
    std::map<int, Node*> m_nodes;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief save weight configuration
    //----------------------------------------------------------------------------------------------------------------------
    virtual void save();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief load weight from configuration
    //----------------------------------------------------------------------------------------------------------------------
    virtual void load();

    ngl::Real getEdgeLength();

    Lattice::Type getType( ) { return m_type; }


    void setWeightFunctionDisplay(const bool _display) { m_weightFunctionDisplay = _display; }
  protected:
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief default empty constructor
    //----------------------------------------------------------------------------------------------------------------------
    Lattice(){}
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief method that finds the weight of an edge between two nodes if already exsists
    //----------------------------------------------------------------------------------------------------------------------
    ngl::Real findEdgeWeight(Node* _node1, Node* _node2);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief flag to set if it is weighted or not
    //----------------------------------------------------------------------------------------------------------------------
    bool m_isWeighted;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief instance of rand
    //----------------------------------------------------------------------------------------------------------------------
    ngl::Random * m_rand;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief pointer to weight function
    //----------------------------------------------------------------------------------------------------------------------
    WeightFunction * m_weightFunction;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief lattice height
    //----------------------------------------------------------------------------------------------------------------------
    ngl::Real m_height;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief lattice width
    //----------------------------------------------------------------------------------------------------------------------
    ngl::Real m_width;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief file name with lattice configuration
    //----------------------------------------------------------------------------------------------------------------------
    std::string m_filename;


    Type m_type;

    ngl::Real m_edgeLength;

    ngl::Real m_maxWeightValue;

    bool m_weightFunctionDisplay;
};

} // end namespace ppnp

#endif // end LATTICE_H
