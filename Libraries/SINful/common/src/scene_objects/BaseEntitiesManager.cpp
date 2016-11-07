#include <scene_objects/BaseEntitiesManager.h>


namespace Sin {
                                              /** CONSTRUCTION / DESTRUCTION **/
    BaseEntitiesManager::BaseEntitiesManager(AllEntities* allEntities)
        : m_allEntities(allEntities) {}

    BaseEntitiesManager::~BaseEntitiesManager() {}


    bool BaseEntitiesManager::loadEntity(
                                         const AllEntities::EntityCategory& category,
                                         const unsigned int& entityID,
                                         const std::string& path
                                        ) {
        Spite::Path filepath(path) ;
        IEntity* entity ;

        // Create the entity from the corresponding factory.
        switch(category) {
            case AllEntities::ImageEntity:
                entity = m_imageEntityFactory.createEntityFromPath(filepath) ;
                break ;

            case AllEntities::SoundEntity:
            case AllEntities::MusicEntity:
                entity = m_soundEntityFactory.createEntityFromPath(filepath) ;
                break ;

            default:
                break;
        }

        if (entity != NULL) {
            m_allEntities -> addEntity(category, entityID, entity) ;
            return true ;
        }

        return false ;
    }

    bool BaseEntitiesManager::unloadEntity(
                                           const AllEntities::EntityCategory& category,
                                           const unsigned int& entityID
                                          ) {
        IEntity* entity = NULL ;
        m_allEntities -> getEntity(category, entityID, entity) ;
        return (entity -> unload()) ;
    }


                                                     /*** SETTERS / GETTERS ***/
    AllEntities* BaseEntitiesManager::getAllEntities() const {
        return m_allEntities ;
    }


    const ImageEntityFactory& BaseEntitiesManager::getImageEntityFactory() const {
        return m_imageEntityFactory ;
    }

    const SoundEntityFactory& BaseEntitiesManager::getSoundEntityFactory() const {
        return m_soundEntityFactory ;
    }

} ;
