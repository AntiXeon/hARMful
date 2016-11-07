#include <scene_objects/AllEntities.h>
#include <CommonSINStrings.h>
#include <debug/Test.h>
#include <debug/Log.h>
#include <stddef.h>


namespace Sin {
                                              /** CONSTRUCTION / DESTRUCTION **/
    AllEntities::AllEntities(
                             const unsigned int& amountImages,
                             const unsigned int& AmountSounds,
                             const unsigned int& AmountMusics
                            ) {
        m_imageEntities.resize(amountImages) ;
        m_soundEntities.resize(AmountSounds) ;
        m_musicEntities.resize(AmountMusics) ;
    }

    AllEntities::~AllEntities() {
        clear() ;
    }


                                                             /*** UTILITIES ***/
    void AllEntities::addEntity(
                                const AllEntities::EntityCategory& category,
                                const unsigned int& entityID,
                                IEntity* entity
                               ) {
        std::vector<IEntity*>& collection = getCollection(category) ;

        ABORT_CONDITION(
                        (entityID < collection.size()),
                        EntityMsg::Error::IndexOutOfBounds
                       ) ;
        collection[entityID] = entity ;
    }

    void AllEntities::removeEntity(
                                   const AllEntities::EntityCategory& category,
                                   const unsigned int& entityID
                                  ) {
        std::vector<IEntity*>& collection = getCollection(category) ;

        ABORT_CONDITION(
                        (entityID < collection.size()),
                        EntityMsg::Error::IndexOutOfBounds
                       ) ;

        if (collection[entityID] != NULL) {
            delete collection[entityID] ;
            collection[entityID] = NULL ;
        }
        else {
            Doom::Log::Write(
                             Doom::Log::LogWarning,
                             EntityMsg::Warning::AlreadyNULLPointer,
                             entityID
                            ) ;
        }
    }

    void AllEntities::clear() {
        // Clear all collections of entities.
        for (int intCategory = ImageEntity ; intCategory < AmountOfCategories ; ++intCategory) {
            EntityCategory category = (EntityCategory) intCategory ;
            std::vector<IEntity*>& collection = getCollection(category) ;
            
            // Clear the collection for the current category of entities.
            unsigned int totalAmount = collection.size() ;
            for (unsigned int index = 0 ; index < totalAmount ; ++index) {
                if (collection[index] != NULL) {
                    delete collection[index] ;
                }
            }

            collection.clear() ;
        }
    }


                                                     /*** SETTERS / GETTERS ***/
    void AllEntities::getEntity(
                                const AllEntities::EntityCategory& category,
                                const unsigned int& entityID,
                                IEntity* outEntity __attribute__ ((unused))
                               ) const {
        const std::vector<IEntity*>& collection = getCollection(category) ;

        ABORT_CONDITION(
                        (entityID < collection.size()),
                        EntityMsg::Error::IndexOutOfBounds
                       ) ;

        outEntity = collection[entityID] ;
    }


    std::vector<IEntity*>& AllEntities::getCollection(const AllEntities::EntityCategory& category) throw(Doom::UnexpectedValueException) {
        switch(category) {
            case AllEntities::ImageEntity:
                return m_imageEntities ;

            case AllEntities::SoundEntity:
                return m_soundEntities ;
                
            case AllEntities::MusicEntity:
                return m_musicEntities ;

            default:
                ThrowException(
                               Doom::UnexpectedValueException,
                               EntityMsg::Error::BadCategoryID
                              ) ;
        }
    }

    const std::vector<IEntity*>& AllEntities::getCollection(const AllEntities::EntityCategory& category) const throw(Doom::UnexpectedValueException) {
        switch(category) {
            case AllEntities::ImageEntity:
                return m_imageEntities ;

            case AllEntities::SoundEntity:
                return m_soundEntities ;
                
            case AllEntities::MusicEntity:
                return m_musicEntities ;

            default:
                ThrowException(
                               Doom::UnexpectedValueException,
                               EntityMsg::Error::BadCategoryID
                              ) ;
        }
    }

} ;
