/**
 *  @file   PandoraSDK/include/Managers/Manager.h
 * 
 *  @brief  Header file for the manager class.
 * 
 *  $Log: $
 */
#ifndef PANDORA_MANAGER_H
#define PANDORA_MANAGER_H 1

#include "Pandora/PandoraInternal.h"
#include "Pandora/StatusCodes.h"

namespace pandora
{

class Algorithm;
class Pandora;

//------------------------------------------------------------------------------------------------------------------------------------------

/**
 *  @brief  Manager class
 */
template<typename T>
class Manager
{
public:
    /**
     *  @brief  Constructor
     * 
     *  @param  pPandora address of the associated pandora object
     */
    Manager(const Pandora *const pPandora);

    /**
     *  @brief  Destructor
     */
    virtual ~Manager();

protected:
    typedef MANAGED_CONTAINER<const T *> ObjectList;

    /**
     *  @brief  Get a list
     * 
     *  @param  listName the name of the list
     *  @param  pObjectList to receive the list
     */
    virtual StatusCode GetList(const std::string &listName, const ObjectList *&pObjectList) const;

    /**
     *  @brief  Get the current list
     * 
     *  @param  pObjectList to receive the current list
     *  @param  listName to receive the name of the current list
     */
    virtual StatusCode GetCurrentList(const ObjectList *&pObjectList, std::string &listName) const;

    /**
     *  @brief  Get the current list name
     * 
     *  @param  listName to receive the current list name
     */
    virtual StatusCode GetCurrentListName(std::string &listName) const;

    /**
     *  @brief  Get the algorithm input list
     * 
     *  @param  pAlgorithm address of the algorithm
     *  @param  pObjectList to receive the algorithm input list
     *  @param  listName to receive the name of the algorithm input list
     */
    virtual StatusCode GetAlgorithmInputList(const Algorithm *const pAlgorithm, const ObjectList *&pObjectList, std::string &listName) const;

    /**
     *  @brief  Get the algorithm track list name
     * 
     *  @param  pAlgorithm address of the algorithm
     *  @param  listName to receive the algorithm input list name
     */
    virtual StatusCode GetAlgorithmInputListName(const Algorithm *const pAlgorithm, std::string &listName) const;

    /**
     *  @brief  Reset the current list to the algorithm input list
     *
     *  @param  pAlgorithm address of the algorithm changing the current track list
     */
    virtual StatusCode ResetCurrentListToAlgorithmInputList(const Algorithm *const pAlgorithm);

    /**
     *  @brief  Replace the current and algorithm input lists with a pre-existing list
     *
     *  @param  pAlgorithm address of the algorithm changing the current list
     *  @param  listName the name of the new current (and algorithm input) list
     */
    virtual StatusCode ReplaceCurrentAndAlgorithmInputLists(const Algorithm *const pAlgorithm, const std::string &listName);

    /**
     *  @brief  Drop the current list, returning the current list to its default empty/null state
     * 
     *  @param  pAlgorithm address of the algorithm altering the lists
     */
    virtual StatusCode DropCurrentList(const Algorithm *const pAlgorithm);

    /**
     *  @brief  Rename a saved list, altering its saved name from a specified old list name to a specified new list name
     * 
     *  @param  oldListName the old list name
     *  @param  newListName the new list name
     */
    virtual StatusCode RenameList(const std::string &oldListName, const std::string &newListName);

    /**
     *  @brief  Create a temporary list associated with a particular algorithm
     *
     *  @param  pAlgorithm address of the algorithm
     *  @param  temporaryListName to receive the name of the temporary list
     */
    virtual StatusCode CreateTemporaryListAndSetCurrent(const Algorithm *const pAlgorithm, std::string &temporaryListName);

    /**
     *  @brief  Register an algorithm with the manager
     * 
     *  @param  pAlgorithm address of the algorithm
     */
    virtual StatusCode RegisterAlgorithm(const Algorithm *const pAlgorithm);

    /**
     *  @brief  Remove temporary lists and reset the current list to that when algorithm was initialized
     * 
     *  @param  pAlgorithm address of the algorithm altering the lists
     *  @param  isAlgorithmFinished whether the algorithm has completely finished and the algorithm info should be entirely removed
     */
    virtual StatusCode ResetAlgorithmInfo(const Algorithm *const pAlgorithm, bool isAlgorithmFinished);

    /**
     *  @brief  Reset the manager
     */
    virtual StatusCode ResetForNextEvent();

    /**
     *  @brief  Erase all manager content
     */
    virtual StatusCode EraseAllContent();

    /**
     *  @brief  Create initial lists
     */
    virtual StatusCode CreateInitialLists();

    /**
     *  @brief  Access a modifiable object, when provided with address to const object
     * 
     *  @param  pT the address of the const object
     * 
     *  @return address of the modifiable object
     */
    virtual T *Modifiable(const T *const pT) const;

    /**
     *  @brief  AlgorithmInfo class
     */
    class AlgorithmInfo
    {
    public:
        std::string                 m_parentListName;                   ///< The current list when algorithm was initialized
        StringSet                   m_temporaryListNames;               ///< The temporary list names
        unsigned int                m_numberOfListsCreated;             ///< The number of lists created by the algorithm
    };

    const std::string               m_nullListName;                     ///< The name of the default empty (NULL) list
    const Pandora *const            m_pPandora;                         ///< The associated pandora object

    typedef std::map<std::string, ObjectList *> NameToListMap;
    typedef std::unordered_map<const Algorithm *, AlgorithmInfo> AlgorithmInfoMap;

    NameToListMap                   m_nameToListMap;                    ///< The name to list map
    AlgorithmInfoMap                m_algorithmInfoMap;                 ///< The algorithm info map

    std::string                     m_currentListName;                  ///< The name of the current list
    StringSet                       m_savedLists;                       ///< The set of saved lists
};

} // namespace pandora

#endif // #ifndef PANDORA_MANAGER_H
