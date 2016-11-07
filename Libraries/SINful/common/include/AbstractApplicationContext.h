#ifndef __SIN_ABSTRACT_APPLICATION_CONTEXT__
#define __SIN_ABSTRACT_APPLICATION_CONTEXT__


#include <scene_objects/BaseEntitiesManager.h>
#include <scene_objects/AbstractEntityInstanceFactory.h>
#include <transitions/interpolations/AllInterpolations.h>


namespace Sin {

    /**
     * @brief   Context to share data between different layers of the
     *          2D engine API.
     * @author  CB (c) 2016
     * @version 0.1     2016/02/07
     */
    class AbstractApplicationContext {
        private:
            /**
             * @brief   Manager of the different entities that are loaded in the
             *          application.
             */
            BaseEntitiesManager* m_BaseEntitiesManager ;

            /**
             * @brief   Factory to generate instances of entities.
             */
            AbstractEntityInstanceFactory* m_instanceFactory ;

            /**
             * @brief   Interpolations of transitions.
             */
            AllInterpolations m_interpolations ;


        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Create a new AbstractAllBaseEntitiesManager.
             * @param   BaseEntitiesManager Manager of the resources for the
             *                          entities of the application.
             * @param   factory         Factory to generate instances of
             *                          entities.
             */
            AbstractApplicationContext(
                                       BaseEntitiesManager* BaseEntitiesManager,
                                       AbstractEntityInstanceFactory* factory
                                      ) ;

            /**
             * @brief   Destruction of the AbstractAllBaseEntitiesManager.
             */
            virtual ~AbstractApplicationContext() ;


                                                     /*** SETTERS / GETTERS ***/
            /**
             * @brief   Get the entities manager.
             * @return  The AbstractAllBaseEntitiesManager of the application.
             */
            BaseEntitiesManager* getBaseEntitiesManager() const ;

            /**
             * @brief   Get the factory to generate instances of entities.
             * @return  The instances factory.
             */
            AbstractEntityInstanceFactory* getInstanceFactory() const ;

            /**
             * @brief   Get the available interpolations to create nice
             *          transitions.
             * @return  Aggregation of all available interpolations for
             *          transitions.
             */
            const AllInterpolations& getInterpolations() const ;
    } ;

} ;


#endif
