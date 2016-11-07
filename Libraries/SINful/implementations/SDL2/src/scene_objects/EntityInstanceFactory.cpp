#include <scene_objects/EntityInstanceFactory.h>


namespace Sin {

                                              /** CONSTRUCTION / DESTRUCTION **/
    EntityInstanceFactory::EntityInstanceFactory(AllEntities* allEntities)
        : AbstractEntityInstanceFactory(allEntities) {}

    EntityInstanceFactory::~EntityInstanceFactory() {}


                                                             /*** UTILITIES ***/
    ImageEntityInstance* EntityInstanceFactory::createImageInstance(
                                                                    const unsigned int& entityID,
                                                                    const Mind::Point2Df& position
                                                                   ) {
        IImageEntity* entity = (IImageEntity*) getEntity(AllEntities::ImageEntity, entityID) ;
        return new ImageEntityInstance(entity, position) ;
    }

    SoundEntityInstance* EntityInstanceFactory::createSoundInstance(
                                                                    const unsigned int& entityID,
                                                                    const Mind::Point2Df& position
                                                                   ) {
        ISoundEntity* entity = (ISoundEntity*) getEntity(AllEntities::SoundEntity, entityID) ;
        return new SoundEntityInstance(entity, position) ;
    }

    MusicEntityInstance* EntityInstanceFactory::createMusicInstance(
                                                                    const unsigned int& entityID,
                                                                    const Mind::Point2Df& position
                                                                   ) {
        ISoundEntity* entity = (ISoundEntity*) getEntity(AllEntities::MusicEntity, entityID) ;
        return new MusicEntityInstance(entity, position) ;
    }




    AbstractEntityInstance* EntityInstanceFactory::createInstance(const unsigned int& entityID) {
        IEntity* entity = getEntity(entityID) ;
        return new EntityInstance(entity) ;
    }

    AbstractEntityInstance* EntityInstanceFactory::createInstance(
                                                                  const unsigned int& entityID,
                                                                  const Mind::Point2Df& position
                                                                 ) {
        IEntity* entity = getEntity(entityID) ;
        return new EntityInstance(entity, position) ;
    }


    IEntity* EntityInstanceFactory::getEntity(
                                              const AllEntities::EntityCategory& category,
                                              const unsigned int& entityID
                                             ) {
        AllEntities* allEntities = getAllEntities() ;
        return allEntities -> getEntity(category, entityID) ;
    }

} ;
