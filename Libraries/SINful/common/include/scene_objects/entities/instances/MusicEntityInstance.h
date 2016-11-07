#ifndef __SIN_MUSIC_ENTITY_INSTANCE__
#define __SIN_MUSIC_ENTITY_INSTANCE__


#include <scene_objects/entities/ISoundEntity.h>
#include <scene_objects/entities/instances/AbstractEntityInstance.h>


namespace Sin {

    /**
     * @brief   An MusicEntityInstance is a light copy of an ISoundEntity.
     *          It only contains data that may differ from other
     *          SoundEntityInstance (volume, channels, ...). Yet, heavy
     *          data as picture are not duplicated.
     *          Musics are played as loop.
     * @author  CB (c) 2016
     * @version 0.1     2016/02/12
     */
    class MusicEntityInstance : public AbstractEntityInstance {
        private:
            /**
             * @brief   Entity the instance is a light copy of.
             */
            ISoundEntity* m_entity ;


        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Create an MusicEntityInstance at position (0,0).
             * @param   entity  Entity the instance is a light copy of.
             */
            MusicEntityInstance(ISoundEntity* entity) ;

            /**
             * @brief   Create an MusicEntityInstance at the given position.
             * @param   position    Position of the MusicEntityInstance when
             *                      created.
             * @param   entity      Entity the instance is a light copy of.
             */
            MusicEntityInstance(
                                ISoundEntity* entity,
                                const Mind::Point2Df& position
                               ) ;

            /**
             * @brief   Destruction of the MusicEntityInstance.
             */
            virtual ~MusicEntityInstance() ;


                                                             /*** UTILITIES ***/
            /**
             * @brief   Set the volume of the SoundEntityInstance.
             * @param   volume  Volume of the associated sound or music.
             */
            void setVolume(const int& volume) ;


        protected:
            /**
             * @brief   Get the ISoundEntity of the instance.
             * @return  The ISoundEntity of the SoundEntityInstance.
             */
            ISoundEntity* getEntity() const ;

    } ;

} ;


#endif
