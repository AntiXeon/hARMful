#ifndef __SIN_BASE_ENTITIES_MANAGER__
#define __SIN_BASE_ENTITIES_MANAGER__


#include <string>
#include <vector>
#include <Path.h>
#include <scene_objects/AllEntities.h>
#include <scene_objects/entities/instances/AbstractEntityInstance.h>
#include <scene_objects/factories/ImageEntityFactory.h>
#include <scene_objects/factories/SoundEntityFactory.h>


namespace Sin {

    /**
     * @brief   A BaseEntitiesManager contains all resources to generate new
     *          instances of IEntity.
     * @author  CB (c) 2016
     * @version 0.1     2016/02/12
     */
    class BaseEntitiesManager {
        private:
            /**
             * @brief   List of loaded entities.
             */
            AllEntities* m_allEntities ;

            /**
             * @brief   Factory to create image entities.
             */
            ImageEntityFactory m_imageEntityFactory ;

            /**
             * @brief   Factory to create sound entities.
             */
            SoundEntityFactory m_soundEntityFactory ;


        protected:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Create an BaseEntitiesManager.
             * @param   allEntities List of the loaded entities in the
             *                      application. This is used to store and clear
             *                      memory used by entities.
             */
            BaseEntitiesManager(AllEntities* allEntities) ;

            /**
             * @brief   Destruction of the BaseEntitiesManager.
             */
            virtual ~BaseEntitiesManager() ;


        public:
                                                             /*** UTILITIES ***/
            /**
             * @brief   Load an entity.
             * @param   category    Category of the entity to load.
             * @param   entityID    The ID of the entity.
             * @param   path        Path of the entity to load.
             * @return  TRUE on success, FALSE on fail.
             */
            bool loadEntity(
                            const AllEntities::EntityCategory& category,
                            const unsigned int& entityID,
                            const std::string& path
                           ) ;

            /**
             * @brief   Unload an entity.
             * @param   category    Category of the entity to unload.
             * @param   entityID    ID of the entity to unload.
             * @return  TRUE on success, FALSE on fail.
             */
            bool unloadEntity(
                              const AllEntities::EntityCategory& category,
                              const unsigned int& entityID
                             ) ;


                                                     /*** SETTERS / GETTERS ***/
            /**
             * @brief   Get all the entities available in the application.
             * @return  All the entities list as an object.
             */
            AllEntities* getAllEntities() const ;


        protected:
            /**
             * @brief   Get the factory to create new IImageEntity objects.
             * @return  The factory of IImageEntity objects.
             */
            const ImageEntityFactory& getImageEntityFactory() const ;

            /**
             * @brief   Get the factory to create new ISoundEntity objects.
             * @return  The factory of ISoundEntity objects.
             */
            const SoundEntityFactory& getSoundEntityFactory() const ;
    } ;

} ;


 #endif
