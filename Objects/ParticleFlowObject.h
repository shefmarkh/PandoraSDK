/**
 *  @file   PandoraSDK/include/Objects/ParticleFlowObject.h
 * 
 *  @brief  Header file for the particle flow object class.
 * 
 *  $Log: $
 */
#ifndef PANDORA_PARTICLE_FLOW_OBJECT_H
#define PANDORA_PARTICLE_FLOW_OBJECT_H 1

#include "Pandora/ObjectCreation.h"
#include "Pandora/StatusCodes.h"

namespace pandora
{

template<typename T> class AlgorithmObjectManager;
template<typename T, typename S> class PandoraObjectFactory;

//------------------------------------------------------------------------------------------------------------------------------------------

/**
 *  @brief  ParticleFlowObject class
 */
class ParticleFlowObject
{
public:
    /**
     *  @brief  Get the particle flow object id (PDG code)
     * 
     *  @return The particle flow object id
     */
    int GetParticleId() const;

    /**
     *  @brief  Get particle flow object charge
     * 
     *  @return The particle flow object charge
     */
    int GetCharge() const;

    /**
     *  @brief  Get particle flow object mass
     * 
     *  @return The particle flow object mass
     */
    float GetMass() const;

    /**
     *  @brief  Get the particle flow object energy
     * 
     *  @return The particle flow object energy
     */
    float GetEnergy() const;

    /**
     *  @brief  Get particle flow object momentum vector
     * 
     *  @return The particle flow object momentum vector
     */
    const CartesianVector &GetMomentum() const;

    /**
     *  @brief  Get the track list
     * 
     *  @return The track list
     */
    const TrackList &GetTrackList() const;

    /**
     *  @brief  Get the cluster list
     * 
     *  @return The cluster list
     */
    const ClusterList &GetClusterList() const;

    /**
     *  @brief  Get the vertex list
     * 
     *  @return The vertex list
     */
    const VertexList &GetVertexList() const;

    /**
     *  @brief  Get track address list
     * 
     *  @return The track address list
     */
    TrackAddressList GetTrackAddressList() const;

    /**
     *  @brief  Get the cluster address list
     * 
     *  @return The cluster address list
     */
    ClusterAddressList GetClusterAddressList() const;

    /**
     *  @brief  Get the number of tracks in the particle flow object
     * 
     *  @return The number of tracks in the particle flow object
     */
    unsigned int GetNTracks() const;

    /**
     *  @brief  Get the number of clusters in the particle flow object
     * 
     *  @return The number of clusters in the particle flow object
     */
    unsigned int GetNClusters() const;

    /**
     *  @brief  Get the parent pfo list
     * 
     *  @return The parent pfo list
     */
    const PfoList &GetParentPfoList() const;

    /**
     *  @brief  Get the daughter pfo list
     * 
     *  @return The daughter pfo list
     */
    const PfoList &GetDaughterPfoList() const;

    /**
     *  @brief  Get the number of parent pfos
     * 
     *  @return The number of parent pfos
     */
    unsigned int GetNParentPfos() const;

    /**
     *  @brief  Get the number of daughter pfos
     * 
     *  @return The number of daughter pfos
     */
    unsigned int GetNDaughterPfos() const;

    /**
     *  @brief  Get the map from registered property name to floating point property value
     * 
     *  @return The properties map
     */
    const PropertiesMap &GetPropertiesMap() const;

protected:
    /**
     *  @brief  Constructor
     * 
     *  @param  parameters the particle flow object parameters
     */
    ParticleFlowObject(const object_creation::ParticleFlowObject::Parameters &parameters);

    /**
     *  @brief  Destructor
     */
    virtual ~ParticleFlowObject();

    /**
     *  @brief  Alter particle flow object metadata parameters
     * 
     *  @param  metaData the new particle flow object metadata (all fields now optional)
     */
    StatusCode AlterMetadata(const object_creation::ParticleFlowObject::Metadata &metadata);

    /**
     *  @brief  Add an object to the particle flow object
     *
     *  @param  pT address of the object to add
     */
    template <typename T>
    StatusCode AddToPfo(const T *const pT);

    /**
     *  @brief  Remove an object from the particle flow object
     *
     *  @param  pT address of the object to remove
     */
    template <typename T>
    StatusCode RemoveFromPfo(const T *const pT);

    /**
     *  @brief  Add a parent pfo to the parent pfo list
     * 
     *  @param  pPfo the address of the parent pfo
     */
    StatusCode AddParent(const ParticleFlowObject *const pPfo);

    /**
     *  @brief  Add a daughter pfo to the daughter pfo list
     * 
     *  @param  pPfo the address of the daughter pfo
     */
    StatusCode AddDaughter(const ParticleFlowObject *const pPfo);

    /**
     *  @brief  Remove a parent pfo from the parent pfo list
     * 
     *  @param  pPfo the address of the parent pfo
     */
    StatusCode RemoveParent(const ParticleFlowObject *const pPfo);

    /**
     *  @brief  Remove a daughter pfo from the daughter pfo list
     * 
     *  @param  pPfo the address of the daughter pfo
     */
    StatusCode RemoveDaughter(const ParticleFlowObject *const pPfo);

    /**
     *  @brief  Update the properties map
     * 
     *  @param  metaData the new particle flow object metadata
     */
    StatusCode UpdatePropertiesMap(const object_creation::ParticleFlowObject::Metadata &metadata);

    int                     m_particleId;               ///< The particle flow object id (PDG code)
    int                     m_charge;                   ///< The particle flow object charge
    float                   m_mass;                     ///< The particle flow object mass
    float                   m_energy;                   ///< The particle flow object energy
    CartesianVector         m_momentum;                 ///< The particle flow object momentum
    TrackList               m_trackList;                ///< The track list
    ClusterList             m_clusterList;              ///< The cluster list
    VertexList              m_vertexList;               ///< The vertex list
    PfoList                 m_parentPfoList;            ///< The list of parent pfos
    PfoList                 m_daughterPfoList;          ///< The list of daughter pfos
    PropertiesMap           m_propertiesMap;            ///< The map from registered property name to floating point property value

    friend class ParticleFlowObjectManager;
    friend class AlgorithmObjectManager<ParticleFlowObject>;
    friend class PandoraObjectFactory<object_creation::ParticleFlowObject::Parameters, object_creation::ParticleFlowObject::Object>;
};

typedef ParticleFlowObject Pfo;                         ///< The ParticleFlowObject to Pfo typedef

//------------------------------------------------------------------------------------------------------------------------------------------

inline int ParticleFlowObject::GetParticleId() const
{
    return m_particleId;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline int ParticleFlowObject::GetCharge() const
{
    return m_charge;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline float ParticleFlowObject::GetMass() const
{
    return m_mass;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline float ParticleFlowObject::GetEnergy() const
{
    return m_energy;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline const CartesianVector &ParticleFlowObject::GetMomentum() const
{
    return m_momentum;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline const TrackList &ParticleFlowObject::GetTrackList() const
{
    return m_trackList;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline const ClusterList &ParticleFlowObject::GetClusterList() const
{
    return m_clusterList;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline const VertexList &ParticleFlowObject::GetVertexList() const
{
    return m_vertexList;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline unsigned int ParticleFlowObject::GetNTracks() const
{
    return m_trackList.size();
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline unsigned int ParticleFlowObject::GetNClusters() const
{
    return m_clusterList.size();
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline const PfoList &ParticleFlowObject::GetParentPfoList() const
{
    return m_parentPfoList;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline const PfoList &ParticleFlowObject::GetDaughterPfoList() const
{
    return m_daughterPfoList;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline unsigned int ParticleFlowObject::GetNParentPfos() const
{
    return m_parentPfoList.size();
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline unsigned int ParticleFlowObject::GetNDaughterPfos() const
{
    return m_daughterPfoList.size();
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline const PropertiesMap &ParticleFlowObject::GetPropertiesMap() const
{
    return m_propertiesMap;
}

} // namespace pandora

#endif // #ifndef PANDORA_PARTICLE_FLOW_OBJECT_H
