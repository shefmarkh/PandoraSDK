/**
 *  @file   PandoraSDK/include/Objects/Track.h
 * 
 *  @brief  Header file for the track class.
 * 
 *  $Log: $
 */
#ifndef PANDORA_TRACK_H
#define PANDORA_TRACK_H 1

#include "Pandora/ObjectCreation.h"
#include "Pandora/StatusCodes.h"

namespace pandora
{

template<typename T> class InputObjectManager;
template<typename T, typename S> class PandoraObjectFactory;

//------------------------------------------------------------------------------------------------------------------------------------------

/**
 *  @brief  Track class
 */
class Track 
{
public:
    /**
     *  @brief  Get the 2D impact parameter wrt (0,0)
     * 
     *  @return the 2D impact parameter wrt (0,0)
     */
    float GetD0() const;

    /**
     *  @brief  Get the z coordinate at the 2D distance of closest approach
     * 
     *  @return the z coordinate at the 2D distance of closest approach
     */
    float GetZ0() const;

    /**
     *  @brief  Get the PDG code of the tracked particle
     *
     *  @return the PDG code of the tracked particle
     */
    int GetParticleId() const; 

    /**
     *  @brief  Get the charge of the tracked particle
     * 
     *  @return the charge of the tracked particle
     */
    int GetCharge() const;

    /**
     *  @brief  Get the mass of the tracked particle, units GeV
     * 
     *  @return the mass of the tracked particle
     */
    float GetMass() const;

    /**
     *  @brief  Get the track momentum at the 2D distance of closest approach
     * 
     *  @return the track momentum at the 2D distance of closest approach
     */
    const CartesianVector &GetMomentumAtDca() const;

    /**
     *  @brief  Get the track energy at the 2D distance of closest approach
     * 
     *  @return the track energy at the 2D distance of closest approach
     */
    float GetEnergyAtDca() const;

    /**
     *  @brief  Get the track state at the start of the track
     * 
     *  @return the track state at the start of the track
     */
    const TrackState &GetTrackStateAtStart() const;

    /**
     *  @brief  Get the track state at the end of the track
     * 
     *  @return the track state at the end of the track
     */
    const TrackState &GetTrackStateAtEnd() const;

    /**
     *  @brief  Get the (sometimes projected) track state at the calorimeter
     * 
     *  @return the track state at the calorimeter
     */
    const TrackState &GetTrackStateAtCalorimeter() const;

    /**
     *  @brief  Get the (sometimes projected) time at the calorimeter
     * 
     *  @return the time at the calorimeter
     */
    float GetTimeAtCalorimeter() const;

    /**
     *  @brief  Whether the track reaches the calorimeter
     * 
     *  @return boolean
     */
    bool ReachesCalorimeter() const;

    /**
     *  @brief  Whether the calorimeter projection is to an endcap
     * 
     *  @return boolean
     */
    bool IsProjectedToEndCap() const;

    /**
     *  @brief  Whether track should form a pfo, if it has an associated cluster
     * 
     *  @return boolean
     */
    bool CanFormPfo() const;

    /**
     *  @brief  Whether track should form a pfo, even if it has no associated cluster
     * 
     *  @return boolean
     */
    bool CanFormClusterlessPfo() const;

    /**
     *  @brief  Whether the track has an associated cluster
     * 
     *  @return boolean
     */
    bool HasAssociatedCluster() const;

    /**
     *  @brief  Get address of the cluster associated with the track
     * 
     *  @return the address of the cluster
     */
    const Cluster *GetAssociatedCluster() const;

    /**
     *  @brief  Get mc particle weight map for the track
     * 
     *  @return the mc particle weight map
     */
    const MCParticleWeightMap &GetMCParticleWeightMap() const;

    /**
     *  @brief  Get the address of the parent track in the user framework
     *
     *  @param  the address of the parent track in the user framework
     */
    const void *GetParentAddress() const;

    /**
     *  @brief  Get the parent track list
     * 
     *  @return the parent track list
     */
    const TrackList &GetParentList() const;

    /**
     *  @brief  Get the sibling track list
     * 
     *  @return the sibling track list
     */
    const TrackList &GetSiblingList() const;

    /**
     *  @brief  Get the daughter track list
     * 
     *  @return the daughter track list
     */
    const TrackList &GetDaughterList() const;

    /**
     *  @brief  Whether the track is available to be added to a particle flow object
     * 
     *  @return boolean
     */
    bool IsAvailable() const;

    /**
     *  @brief  operator< sorting by position at calorimeter, then energy at the 2D distance of closest approach
     * 
     *  @param  rhs the object for comparison
     * 
     *  @return boolean
     */
    bool operator< (const Track &rhs) const;

protected:
    /**
     *  @brief  Constructor
     * 
     *  @param  parameters the track parameters
     */
    Track(const object_creation::Track::Parameters &parameters);

    /**
     *  @brief  Destructor
     */
    virtual ~Track();

    /**
     *  @brief  Set the mc particles associated with the track
     * 
     *  @param  mcParticleWeightMap the mc particle weight map
     */
    void SetMCParticleWeightMap(const MCParticleWeightMap &mcParticleWeightMap);

    /**
     *  @brief  Remove the mc particles associated with the track
     */
    void RemoveMCParticles();

    /**
     *  @brief  Set the cluster associated with the track
     * 
     *  @param  pCluster the address of the associated cluster
     */
    StatusCode SetAssociatedCluster(const Cluster *const pCluster);

    /**
     *  @brief  Remove the association with a cluster
     *
     *  @param  pCluster the address of the cluster with which the track is no longer associated
     */
    StatusCode RemoveAssociatedCluster(const Cluster *const pCluster);

    /**
     *  @brief  Add a parent track to the parent track list
     * 
     *  @param  pTrack the address of the parent track
     */
    StatusCode AddParent(const Track *const pTrack);

    /**
     *  @brief  Add a daughter track to the daughter track list
     * 
     *  @param  pTrack the address of the daughter track
     */
    StatusCode AddDaughter(const Track *const pTrack);

    /**
     *  @brief  Add a sibling track to the sibling track list
     * 
     *  @param  pTrack the address of the sibling track
     */
    StatusCode AddSibling(const Track *const pTrack);

    /**
     *  @brief  Set availability of track to be added to a particle flow object
     * 
     *  @param  isAvailable the track availability
     */
    void SetAvailability(bool isAvailable);

    const float             m_d0;                       ///< The 2D impact parameter wrt (0,0), units mm
    const float             m_z0;                       ///< The z coordinate at the 2D distance of closest approach, units mm
    const int               m_particleId;               ///< The PDG code of the tracked particle
    const int               m_charge;                   ///< The charge of the tracked particle
    const float             m_mass;                     ///< The mass of the tracked particle, units GeV
    const CartesianVector   m_momentumAtDca;            ///< The momentum vector at the 2D distance of closest approach, units GeV
    const float             m_energyAtDca;              ///< The track energy at the 2D distance of closest approach, units GeV
    const TrackState        m_trackStateAtStart;        ///< The track state at the start of the track, units mm and GeV
    const TrackState        m_trackStateAtEnd;          ///< The track state at the end of the track, units mm and GeV
    const TrackState        m_trackStateAtCalorimeter;  ///< The (sometimes projected) track state at the calorimeter, units mm and GeV
    const float             m_timeAtCalorimeter;        ///< The (sometimes projected) time at the calorimeter, units ns
    const bool              m_reachesCalorimeter;       ///< Whether the track actually reaches the calorimeter
    const bool              m_isProjectedToEndCap;      ///< Whether the calorimeter projection is to an endcap
    const bool              m_canFormPfo;               ///< Whether track should form a pfo, if it has an associated cluster
    const bool              m_canFormClusterlessPfo;    ///< Whether track should form a pfo, even if it has no associated cluster
    const Cluster          *m_pAssociatedCluster;       ///< The address of an associated cluster
    MCParticleWeightMap     m_mcParticleWeightMap;      ///< The mc particle weight map
    const void             *m_pParentAddress;           ///< The address of the parent track in the user framework
    TrackList               m_parentTrackList;          ///< The list of parent track addresses
    TrackList               m_siblingTrackList;         ///< The list of sibling track addresses
    TrackList               m_daughterTrackList;        ///< The list of daughter track addresses
    bool                    m_isAvailable;              ///< Whether the track is available to be added to a particle flow object

    friend class TrackManager;
    friend class InputObjectManager<Track>;
    friend class PandoraObjectFactory<object_creation::Track::Parameters, object_creation::Track::Object>;
};

//------------------------------------------------------------------------------------------------------------------------------------------

inline float Track::GetD0() const
{
    return m_d0;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline float Track::GetZ0() const
{
    return m_z0;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline int Track::GetParticleId() const
{
    return m_particleId;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline int Track::GetCharge() const
{
    return m_charge;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline float Track::GetMass() const
{
    return m_mass;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline const CartesianVector &Track::GetMomentumAtDca() const
{
    return m_momentumAtDca;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline float Track::GetEnergyAtDca() const
{
    return m_energyAtDca;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline const TrackState &Track::GetTrackStateAtStart() const
{
    return m_trackStateAtStart;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline const TrackState &Track::GetTrackStateAtEnd() const
{
    return m_trackStateAtEnd;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline const TrackState &Track::GetTrackStateAtCalorimeter() const
{
    return m_trackStateAtCalorimeter;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline float Track::GetTimeAtCalorimeter() const
{
    return m_timeAtCalorimeter;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline bool Track::ReachesCalorimeter() const
{
    return m_reachesCalorimeter;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline bool Track::IsProjectedToEndCap() const
{
    return m_isProjectedToEndCap;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline bool Track::CanFormPfo() const
{
    return m_canFormPfo;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline bool Track::CanFormClusterlessPfo() const
{
    return m_canFormClusterlessPfo;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline bool Track::HasAssociatedCluster() const
{
    return (nullptr != m_pAssociatedCluster);
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline const MCParticleWeightMap &Track::GetMCParticleWeightMap() const
{
    return m_mcParticleWeightMap;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline const void *Track::GetParentAddress() const
{
    return m_pParentAddress;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline const TrackList &Track::GetParentList() const
{
    return m_parentTrackList;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline const TrackList &Track::GetSiblingList() const
{
    return m_siblingTrackList;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline const TrackList &Track::GetDaughterList() const
{
    return m_daughterTrackList;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline bool Track::IsAvailable() const
{
    return m_isAvailable;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline void Track::SetAvailability(bool isAvailable)
{
    m_isAvailable = isAvailable;
}

} // namespace pandora

#endif // #ifndef PANDORA_TRACK_H
