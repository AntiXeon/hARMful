#ifndef __SIN_SOUND_ENTITY_INSTANCE__
#define __SIN_SOUND_ENTITY_INSTANCE__


#include <scene_objects/entities/ISoundEntity.h>
#include <scene_objects/entities/instances/AbstractEntityInstance.h>


namespace Sin {

    /**
     * @brief   An SoundEntityInstance is a light copy of an ISoundEntity.
     *          It only contains data that may differ from other
     *          SoundEntityInstance (volume, channels, ...). Yet, heavy
     *          data as picture are not duplicated.
     * @author  CB (c) 2016
     * @version 0.1     2016/02/12
     */
    class SoundEntityInstance : public AbstractEntityInstance {
        public:
            /**
             * @brief   State of the sound.
             */
            enum State {
                        StoppedSound,
                        PlayingSound,
                        PausedSound
                       } ;


        private:
            /**
             * @brief   Entity the instance is a light copy of.
             */
            ISoundEntity* m_entity ;

            /**
             * @brief   State of the sound.
             */
            State m_soundState ;

            /**
             * @brief   Delay to wait before sound is played again from the
             *          current instance.
             */
            int m_playDelay ;

            /**
             * @brief   Delay since the last time the sound has been played.
             */
            int m_playDelaySinceLastTime ;


        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Create an SoundEntityInstance at position (0,0).
             * @param   entity      Entity the instance is a light copy of.
             * @param   playDelay   Delay to wait before sound is played again
             *                      from the current instance. Delay is
             *                      expressed in frame, just after the end of
             *                      the previous play session.
             *                      A value of -1 indicates the sound is played
             *                      once only.
             */
            SoundEntityInstance(
                                ISoundEntity* entity,
                                const int& playDelay
                               ) ;

            /**
             * @brief   Create an SoundEntityInstance at the given position.
             * @param   position    Position of the SoundEntityInstance when
             *                      created.
             * @param   playDelay   Delay to wait before sound is played again
             *                      from the current instance. Delay is
             *                      expressed in frame, just after the end of
             *                      the previous play session.
             *                      A value of -1 indicates the sound is played
             *                      once only.
             * @param   entity      Entity the instance is a light copy of.
             */
            SoundEntityInstance(
                                ISoundEntity* entity,
                                const int& playDelay,
                                const Mind::Point2Df& position
                               ) ;

            /**
             * @brief   Destruction of the SoundEntityInstance.
             */
            virtual ~SoundEntityInstance() ;


                                                             /*** UTILITIES ***/
            /**
             * @brief   Update the SoundEntityInstance.
             */
            virtual void update() ;

            /**
             * @brief   Play the SoundEntityInstance at its position,
             *          relatively to the given position.
             * @param   relativeX   Relative position on X from which the
             *                      rendering must be done.
             * @param   relativeY   Relative position on Y from which the
             *                      rendering must be done.
             */
            void render(const Mind::Point2Df& relative) ;


        protected:
            /**
             * @brief   Get the delay in frames before the sound is played again
             *          by the current instance.
             * @return  Delay to wait before sound is played again from the
             *          current instance.
             *          A value of -1 indicates the sound is played once only.
             */
            int getPlayDelay() const ;


            /**
             * @brief   Get the delay in frames since the last time it has been
             *          played (from the end of the playing session).
             * @return  Delay since the last time the sound has been played.
             */
            int getPlayDelaySinceLastTime() const ;

            /**
             * @brief   Get the ISoundEntity of the instance.
             * @return  The ISoundEntity of the SoundEntityInstance.
             */
            ISoundEntity* getEntity() const ;

    } ;

} ;


#endif
