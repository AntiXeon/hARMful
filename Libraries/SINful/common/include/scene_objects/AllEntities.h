#ifndef __SIN_ALL_ENTITIES__
#define __SIN_ALL_ENTITIES__


#include <exceptions/UnexpectedValueException.h>
#include <scene_objects/entities/IEntity.h>
#include <vector>


namespace Sin {

    /**
     * @brief   An AllEntities object contains all the entities that are loaded
     *          in the application.
     * @author  CB (c) 2016
     * @version 0.1     2016/02/18
     */
    class AllEntities {
        public:
            /**
             * @brief Categories of entities that can be loaded.
             */
            enum EntityCategory {
                                 ImageEntity,
                                 SoundEntity,
                                 MusicEntity,
                                 AmountOfCategories
                                } ;


        private:
            /**
             * @brief   All loaded image entities.
             */
            std::vector<IEntity*> m_imageEntities ;

            /**
             * @brief   All loaded sound entities.
             */
            std::vector<IEntity*> m_soundEntities ;

            /**
             * @brief   All loaded music entities.
             */
            std::vector<IEntity*> m_musicEntities ;


        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Create an AllEntities object.
             * @param   amountImages    Expected amount of images.
             * @param   amountSounds    Expected amount of sounds.
             * @param   amountMusics    Expected amount of musics.
             * @warning For a convenient use, the given ID values should be
             *          stored as an enum and reused for any function to access
             *          entities.
             */
            AllEntities(
                        const unsigned int& amountImages,
                        const unsigned int& AmountSounds,
                        const unsigned int& AmountMusics
                       ) ;

            /**
             * @brief   Destruction of the AllEntities object.
             * @warning All IEntity pointers are deleted in this destructor.
             */
            virtual ~AllEntities() ;


                                                             /*** UTILITIES ***/
            /**
             * @brief   Add an IEntity.
             * @param   category    Category of the IEntity to add.
             * @param   entityID    ID of the IEntity to add.
             * @param   entity      The IEntity to add.
             */
            void addEntity(
                           const EntityCategory& category,
                           const unsigned int& entityID,
                           IEntity* entity
                          ) ;

            /**
             * @brief   Remove an IEntity from the application.
             * @param   category    Category of the IEntity to remove.
             * @param   entityID    ID of the IEntity to remove.
             * @warning This should not be used anymore by any instance.
             */
            void removeEntity(
                              const EntityCategory& category,
                              const unsigned int& entityID
                             ) ;


            /**
             * @brief   Clear all entities, freeing all the memory used by
             *          entities.
             */
            void clear() ;


        public:
                                                     /*** SETTERS / GETTERS ***/
            /**
             * @brief   Get the IEntity with the given ID.
             * @param   category    Category of the IEntity to get.
             * @param   entityID    ID of the IEntity to get.
             * @param   outEntity   The output IEntity at the given index.
             */
            void getEntity(
                           const EntityCategory& category,
                           const unsigned int& entityID,
                           IEntity* outEntity
                          ) const ;

        private:
            /** 
             * @brief   Select the right collection of entities from the
             *          provided category.
             * @param   category    Category for which select the collection.
             * @return  The collection of entities of the given @a category.
             */
            std::vector<IEntity*>& getCollection(const EntityCategory& category) throw(Doom::UnexpectedValueException) ;

            /** 
             * @brief   Select the right collection of entities from the
             *          provided category.
             * @param   category    Category for which select the collection.
             * @return  The collection of entities of the given @a category.
             */
            const std::vector<IEntity*>& getCollection(const EntityCategory& category) const throw(Doom::UnexpectedValueException) ;
    } ;

} ;


#endif
