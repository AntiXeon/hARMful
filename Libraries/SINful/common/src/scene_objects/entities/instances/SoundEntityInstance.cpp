#include <scene_objects/entities/instances/SoundEntityInstance.h>


namespace Sin {

                                              /** CONSTRUCTION / DESTRUCTION **/
    SoundEntityInstance::SoundEntityInstance(
                                             ISoundEntity* entity,
                                             const int& playDelay
                                            )
        : AbstractEntityInstance(),
          m_entity(entity),
          m_soundState(SoundEntityInstance::StoppedSound),
          m_playDelay(playDelay) {}

    SoundEntityInstance::SoundEntityInstance(
                                             ISoundEntity* entity,
                                             const int& playDelay,
                                             const Mind::Point2Df& position
                                            ) : AbstractEntityInstance(position),
                                                m_entity(entity),
                                                m_soundState(SoundEntityInstance::StoppedSound),
                                                m_playDelay(playDelay) {}

    SoundEntityInstance::~SoundEntityInstance() {}


                                                             /*** UTILITIES ***/
    void SoundEntityInstance::setVolume(const int&) {
        // @TODO!
    }

    ISoundEntity* SoundEntityInstance::getEntity() const {
        return m_entity ;
    }

} ;
