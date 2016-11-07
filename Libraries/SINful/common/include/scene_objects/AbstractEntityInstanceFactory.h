#ifndef __SIN_ABSTRACT_ENTITY_INSTANCE_FACTORY__
#define __SIN_ABSTRACT_ENTITY_INSTANCE_FACTORY__


#include <scene_objects/AllEntities.h>
#include <scene_objects/entities/instances/AbstractEntityInstance.h>


namespace Sin {

    /**
     * @brief   The AbstractEntityInstanceFactory is the base class to have a
     *          factory of entity instances in the application.
     * @author  CB (c) 2016
     * @version 0.1     2016/02/18
     */
    class AbstractEntityInstanceFactory {

        private:
            /**
             * @brief   List of the loaded entities in the application.
             */
            AllEntities* m_allEntities ;


        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Create a new AbstractEntityInstanceFactory.
             * @param   allEntities List of the loaded entities in the
             *                      application. This is used to create new
             *                      instances of such entities.
             */
            AbstractEntityInstanceFactory(AllEntities* allEntities) ;

            /**
             * @brief   Destruction of the AbstractEntityInstanceFactory.
             */
            virtual ~AbstractEntityInstanceFactory() ;


                                                             /*** UTILITIES ***/
            /**
             * @brief   Create a new instance of the wanted entity.
             * @param   entityID    ID of the entity to copy into the scene.
             * @return  The newly created instance of the entity.
             */
            virtual AbstractEntityInstance* createInstance(const unsigned int& entityID) = 0 ;

            /**
             * @brief   Create a new instance of the wanted entity.
             * @param   entityID    ID of the entity to copy into the scene.
             * @param   position    Position of the AbstractEntityInstance when
             *                      created.
             * @return  The newly created instance of the entity.
             */
            virtual AbstractEntityInstance* createInstance(
                                                           const unsigned int& entityID,
                                                           const Mind::Point2Df& position
                                                          ) = 0 ;


        protected:
                                                     /*** SETTERS / GETTERS ***/
            /**
             * @brief   Get all the entities available in the application.
             * @return  All the entities list as an object.
             */
            AllEntities* getAllEntities() const ;

    } ;

} ;


#endif
