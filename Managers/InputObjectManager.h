/**
 *  @file   PandoraSDK/include/Managers/InputObjectManager.h
 * 
 *  @brief  Header file for the input object manager class.
 * 
 *  $Log: $
 */
#ifndef PANDORA_INPUT_OBJECT_MANAGER
#define PANDORA_INPUT_OBJECT_MANAGER 1

#include "Managers/Manager.h"

namespace pandora
{

/**
 *  @brief  InputObjectManager class
 */
template<typename T>
class InputObjectManager : public Manager<T>
{
public:
    /**
     *  @brief  Constructor
     * 
     *  @param  pPandora address of the associated pandora object
     */
    InputObjectManager(const Pandora *const pPandora);

    /**
     *  @brief  Destructor
     */
    virtual ~InputObjectManager();

protected:
    typedef typename Manager<T>::ObjectList ObjectList;

    /**
     *  @brief  Create the input list (accessible to algorithms), using objects created by client application
     */
    virtual StatusCode CreateInputList();

    using Manager<T>::CreateTemporaryListAndSetCurrent;

    /**
     *  @brief  Change the current list to a specified temporary list
     *
     *  @param  pAlgorithm address of the algorithm changing the current list
     *  @param  objectList the specified temporary list
     *  @param  temporaryListName to receive the name of the temporary list
     */
    virtual StatusCode CreateTemporaryListAndSetCurrent(const Algorithm *const pAlgorithm, const ObjectList &objectList,
        std::string &temporaryListName);

    /**
     *  @brief  Save a list of objects in a list with a specified name; create new list if required
     * 
     *  @param  listName the list name
     *  @param  objectList the object list
     */
    virtual StatusCode SaveList(const std::string &listName, const ObjectList &objectList);

    /**
     *  @brief  Add objects to a saved list with a specified name
     *
     *  @param  listName the list to add the objects to
     *  @param  objectList the list of objects to be added
     */
    virtual StatusCode AddObjectsToList(const std::string &listName, const ObjectList &objectList);

    /**
     * @brief Remove objects from a saved list
     *
     * @param listName the list to remove the objects from
     * @param objectList the list of objects to be removed
     */
    virtual StatusCode RemoveObjectsFromList(const std::string &listName, const ObjectList &objectList);

    /**
     *  @brief  Rename a saved list, altering its saved name from a specified old list name to a specified new list name
     * 
     *  @param  oldListName the old list name
     *  @param  newListName the new list name
     */
    virtual StatusCode RenameList(const std::string &oldListName, const std::string &newListName);

    /**
     *  @brief  Erase all manager content
     */
    virtual StatusCode EraseAllContent();

    /**
     *  @brief  Create initial lists
     */
    virtual StatusCode CreateInitialLists();

    const std::string               m_inputListName;                    ///< The name of the input list
};

} // namespace pandora

#endif // #ifndef PANDORA_INPUT_OBJECT_MANAGER
