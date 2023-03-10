/**
 *  @file   PandoraSDK/include/Managers/TrackManager.h
 * 
 *  @brief  Header file for the track manager class.
 * 
 *  $Log: $
 */
#ifndef PANDORA_TRACK_MANAGER_H
#define PANDORA_TRACK_MANAGER_H 1

#include "Managers/InputObjectManager.h"

#include "Pandora/ObjectCreation.h"
#include "Pandora/PandoraInternal.h"

namespace pandora
{

/**
 *    @brief TrackManager class
 */
class TrackManager : public InputObjectManager<Track>
{
public:
    /**
     *  @brief  Constructor
     * 
     *  @param  pPandora address of the associated pandora object
     */
    TrackManager(const Pandora *const pPandora);

    /**
     *  @brief  Destructor
     */
    ~TrackManager();

private:
    /**
     *  @brief  Create track
     * 
     *  @param  parameters the track parameters
     *  @param  pTrack to receive the address of the track
     *  @param  factory the factory that performs the object allocation
     */
    StatusCode Create(const object_creation::Track::Parameters &parameters, const Track *&pTrack,
        const ObjectFactory<object_creation::Track::Parameters, object_creation::Track::Object> &factory);

    /**
     *  @brief  Is a track, or a list of tracks, available to add to a particle flow object
     * 
     *  @param  pT address of the object or object list
     * 
     *  @return boolean
     */
    template <typename T>
    bool IsAvailable(const T *const pT) const;

    /**
     *  @brief  Set availability of a track, or a list of tracks, to be added to a particle flow object
     * 
     *  @param  pT the address of the object or object list
     *  @param  isAvailable the availability
     */
    template <typename T>
    void SetAvailability(const T *const pT, bool isAvailable) const;

    /**
     *  @brief  Erase all track manager content
     */
    StatusCode EraseAllContent();

    /**
     *  @brief  Match tracks to their correct mc particles for particle flow
     *
     *  @param  trackToPfoTargetsMap the track uid to mc pfo target map
     */
    StatusCode MatchTracksToMCPfoTargets(const UidToMCParticleWeightMap &trackToPfoTargetsMap);

    /**
     *  @brief  Remove all mc particle associations that have been registered with tracks
     */
    StatusCode RemoveAllMCParticleRelationships();

    /**
     *  @brief  Set a track parent-daughter relationship
     * 
     *  @param  parentUid the parent track unique identifier
     *  @param  daughterUid the daughter track unique identifier
     */
    StatusCode SetTrackParentDaughterRelationship(const Uid parentUid, const Uid daughterUid);

    /**
     *  @brief  Set a track sibling relationship
     * 
     *  @param  firstSiblingUid the first sibling track unique identifier
     *  @param  secondSiblingUid the second sibling track unique identifier
     */
    StatusCode SetTrackSiblingRelationship(const Uid firstSiblingUid, const Uid secondSiblingUid);

    /**
     *  @brief  Apply track associations (parent-daughter and sibling) that have been registered with the track manager
     */
    StatusCode AssociateTracks() const;

    /**
     *  @brief  Add parent-daughter associations to tracks
     */
    StatusCode AddParentDaughterAssociations() const;

    /**
     *  @brief  Add sibling associations to tracks
     */
    StatusCode AddSiblingAssociations() const;

    /**
     *  @brief  Set the cluster associated with a track
     * 
     *  @param  pTrack the address of the relevant track
     *  @param  pCluster the address of the associated cluster
     */
    StatusCode SetAssociatedCluster(const Track *const pTrack, const Cluster *const pCluster) const;

    /**
     *  @brief  Remove the association of a track with a cluster
     *
     *  @param  pTrack the address of the relevant track
     *  @param  pCluster the address of the cluster with which the track is no longer associated
     */
    StatusCode RemoveAssociatedCluster(const Track *const pTrack, const Cluster *const pCluster) const;

    /**
     *  @brief  Remove all track to cluster associations
     */
    StatusCode RemoveAllClusterAssociations() const;

    /**
     *  @brief  Remove track to cluster associations from all tracks in the current list
     * 
     *  @param  danglingClusters to receive the list of "dangling" associations
     */
    StatusCode RemoveCurrentClusterAssociations(TrackToClusterMap &danglingClusters) const;

    /**
     *  @brief  Remove track to cluster associations from a specified list of tracks
     * 
     *  @param  trackList the specified track list
     */
    StatusCode RemoveClusterAssociations(const TrackList &trackList) const;

    /**
     *  @brief  Initialize reclustering operations, preparing lists and metadata accordingly
     * 
     *  @param  pAlgorithm address of the algorithm controlling reclustering
     *  @param  clusterList the input cluster list
     *  @param  originalReclusterListName the list name/key for the original recluster candidates
     */
    StatusCode InitializeReclustering(const Algorithm *const pAlgorithm, const TrackList &trackList,
        const std::string &originalReclusterListName);

    typedef std::unordered_map<Uid, const Track *> UidToTrackMap;
    typedef std::unordered_multimap<Uid, Uid> TrackRelationMap;

    UidToTrackMap                   m_uidToTrackMap;                    ///< The uid to track map
    TrackRelationMap                m_parentDaughterRelationMap;        ///< The track parent-daughter relation map
    TrackRelationMap                m_siblingRelationMap;               ///< The track sibling relation map

    friend class PandoraApiImpl;
    friend class PandoraContentApiImpl;
    friend class PandoraImpl;
};

} // namespace pandora

#endif // #ifndef PANDORA_TRACK_MANAGER_H
