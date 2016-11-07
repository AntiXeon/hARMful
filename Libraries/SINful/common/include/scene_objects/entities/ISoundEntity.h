#ifndef __SIN_INTERFACE_SOUND_ENTITY__
#define __SIN_INTERFACE_SOUND_ENTITY__


#include <scene_objects/entities/IEntity.h>


namespace Sin {

    class ISoundEntity : public IEntity {
        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Destruction of the ISoundEntity.
             */
            virtual ~ISoundEntity() ;


                                                             /*** UTILITIES ***/
            /**
             * @brief   Play the sound or music without any spatial effect.
             * @param   times   Amount of loops to repeat sound.
             */
            virtual void play(const int times) = 0 ;

            /**
             * @brief   Play the sound or music as if it is coming from the
             *          given position.
             * @param   times   Amount of loops to repeat sound.
             * @param   x       Relative position of the incoming sound on X
             *                  axis.
             * @param   y       Relative position of the incoming sound on Y
             *                  axis.
             */
            virtual void play(
                              const int times,
                              const Mind::Scalar& x,
                              const Mind::Scalar& y
                             ) = 0 ;

            /**
             * @brief   Pause the sound or music.
             */
            virtual void pause() = 0 ;

            /**
             * @brief   Stop the sound or music.
             */
            virtual void stop() = 0 ;



            /**
             * @brief   Check if the sound is currently playing.
             * @return  TRUE if the sound is playing, FALSE otherwise.
             */
            virtual bool isPlaying() = 0 ;

            /**
             * @brief   Check if the sound is currently paused.
             * @return  TRUE if the sound is paused, FALSE otherwise.
             */
            virtual bool isPaused() = 0 ;

            /**
             * @brief   Check if the sound is currently stopped.
             * @return  TRUE if the sound is stopped, FALSE otherwise.
             */
            virtual bool isStopped() = 0 ;
    } ;

} ;


#endif
