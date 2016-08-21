#ifndef DENDRITE_H
#define DENDRITE_H

#include "graph/Lattice.h"
#include "abstract/Portable.h"
#include "Path.h"

#include <QtCore/QString>
#include <QtCore/QFile>
#include <QtCore/QTextStream>

#include <map>

namespace ppnp
{

//----------------------------------------------------------------------------------------------------------------------
/// @class Dendrite
/// @brief Class for the sub graph tha represents the structure, can be exported and imported to/from XML
/// @author Erika Camilleri
/// @version 1.0
/// @date 06/16/16
//----------------------------------------------------------------------------------------------------------------------

class Dendrite : public Portable
{
  friend class Dijkstra;    // since classes are closely related Dijkstra is given practical access to members and functions of this class
  public:
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief default constructor
    /// @param[in] _lattice     the reference to the parent lattice structure
    //----------------------------------------------------------------------------------------------------------------------
    Dendrite(Lattice* _lattice);

    ~Dendrite();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief implementation of the export to XML inherited from Portable
    //----------------------------------------------------------------------------------------------------------------------
    virtual void save();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief implementation of the import from XML inherited from Portable
    //----------------------------------------------------------------------------------------------------------------------
    virtual void load();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief set root from reference
    /// @param[in] _root     pointer to the node that is going to be the root
    //----------------------------------------------------------------------------------------------------------------------
    void setRoot(Node * _root);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief set root from index
    /// @param[in] _root     the index of the node that is going to be the root
    //----------------------------------------------------------------------------------------------------------------------
    void setRootByIndex(const int &_rootIndex);


    void setRootAtPosition(const ngl::Vec3 &_pos);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief add an endpoint by passing in a reference
    /// @param[in] _root     pointer of the node you would like to set as an endpoint
    //----------------------------------------------------------------------------------------------------------------------
    void addEndPoint(Node * _endpoint);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief set endpoint by passing its node index
    /// @param[in] _root     the index of the node that is going to be an endpoint
    //----------------------------------------------------------------------------------------------------------------------
    void addEndPointByIndex(const int &_endpointIndex);

    void addEndPointAt(const ngl::Vec3 &_pos);


    std::vector<int> setRandomEndPoints();
    std::vector<int> setRandomEndPoints(const int &_num, const ngl::Vec3 &_minBounds, const ngl::Vec3 &_maxBounds);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief set endpoint by passing its node index
    /// @param[in] _root     the index of the node that is going to be an endpoint
    //----------------------------------------------------------------------------------------------------------------------
    void removeEndPointByIndex(const int &_endpointIndex);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief greedy algorithm that traces the paths from end points to the root
    //----------------------------------------------------------------------------------------------------------------------
    void backtrack();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief return the distance from the root of the node specified by the index
    //----------------------------------------------------------------------------------------------------------------------
    ngl::Real getDistanceFromRoot(const int &_nodeIndex);

    void draw(ngl::Mat4 &_mouseGlobalTX, ngl::Camera &_cam);

    bool hasPaths();

    void refinePaths();

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the list of paths that make up the entire structure
    //----------------------------------------------------------------------------------------------------------------------
    std::vector<Path*> m_paths;
  protected:

  private:
    ppnp::Path* backtrack(ppnp::Node* _endpoint);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief pointer to the lattice we need to go through
    //----------------------------------------------------------------------------------------------------------------------
    Lattice * m_lattice;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the list of pointers of the end points
    //----------------------------------------------------------------------------------------------------------------------
    std::vector<Node *> m_endpoints;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief store pointer to the root node
    //----------------------------------------------------------------------------------------------------------------------
    Node * m_root;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief maps node index to its distance to the specified root filled in by costing algorithm
    //----------------------------------------------------------------------------------------------------------------------
    std::map<int, ngl::Real> m_rootNodeDist;

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief maximum distance from node to root - used for init
    //----------------------------------------------------------------------------------------------------------------------
    const int MAX_DIST = 99999;
};

} // end namespace ppnp

#endif // end DENDRITE_H
