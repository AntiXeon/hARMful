#ifndef __SIN_SDL2_ENTITY_INSTANCE_FACTORY__
#define __SIN_SDL2_ENTITY_INSTANCE_FACTORY__


#include <scene_objects/entities/instances/ImageEntityInstance.h>
#include <scene_objects/entities/instances/SoundEntityInstance.h>
#include <scene_objects/entities/instances/MusicEntityInstance.h>
#include <scene_objects/AbstractEntityInstanceFactory.h>
#include <SDL2/SDL.h>


namespace Sin {

    /**
     * @brief   The EntityInstanceFactory is the class to have a factory of
     *          entity instances in the application.
     * @author  CB (c) 2016
     * @version 0.1     2016/03/02
     */
    class EntityInstanceFactory : public AbstractEntityInstanceFactory {
        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Create a new EntityInstanceFactory.
             * @param   allEntities List of the loaded entities in the
             *                      application. This is used to create new
             *                      instances of such entities.
             */
            EntityInstanceFactory(AllEntities* allEntities) ;

            /**
             * @brief   Destruction of the EntityInstanceFactory.
             */
            virtual ~EntityInstanceFactory() ;


                                                             /*** UTILITIES ***/
            /**
             * @brief   Create a new instance of the wanted image entity.
             * @param   entityID    ID of the image entity to copy into the
             *                      scene.
             * @param   position    Position of the instance on creation.
             * @return  The newly created instance of the image entity.
             */
            ImageEntityInstance* createImageInstance(
                                                     const unsigned int& entityID,
                                                     const Mind::Point2Df& position = Mind::Point2Df(0,0)
                                                    ) ;

            /**
             * @brief   Create a new instance of the wanted sound entity.
             * @param   entityID    ID of the image entity to copy into the
             *                      scene.
             * @param   position    Position of the instance on creation.
             * @return  The newly created instance of the sound entity.
             */
            SoundEntityInstance* createSoundInstance(
                                                     const unsigned int& entityID,
                                                     const Mind::Point2Df& position = Mind::Point2Df(0,0)
                                                    ) ;

            /**
             * @brief   Create a new instance of the wanted music entity.
             * @param   entityID    ID of the image entity to copy into the
             *                      scene.
             * @param   position    Position of the instance on creation.
             * @return  The newly created instance of the music entity.
             */
            MusicEntityInstance* createMusicInstance(
                                                     const unsigned int& entityID,
                                                     const Mind::Point2Df& position = Mind::Point2Df(0,0)
                                                    ) ;


        private:
            /**
             * @brief   Get the IEntity having the given ID.
             * @param   category    Category of the entity to get.
             * @param   entityID    ID of the wanted IEntity.
             * @return  The corresponding IEntity.
             */
            IEntity* getEntity(
                               const AllEntities::EntityCategory& category,
                               const unsigned int& entityID
                              ) ;
    } ;

} ;

#endif
