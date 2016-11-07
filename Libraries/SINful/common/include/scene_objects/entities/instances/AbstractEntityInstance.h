#ifndef __SIN_ABSTRACT_ENTITY_INSTANCE__
#define __SIN_ABSTRACT_ENTITY_INSTANCE__


#include <geometry/dimensions/Dimension2Df.h>
#include <scene_objects/AbstractSceneObject.h>
#include <scene_objects/ObjectRotation2D.h>


namespace Sin {

    /**
     * @brief   AbstractEntityInstance is the base class for entity instances.
     * @author  CB (c) 2016
     * @version 0.1     2016/02/12
     */
    class AbstractEntityInstance : public AbstractSceneObject {
        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Create an AbstractEntityInstance at position (0,0).
             */
            AbstractEntityInstance() ;

            /**
             * @brief   Create an AbstractEntityInstance at the given position.
             * @param   position    Position of the AbstractEntityInstance when
             *                      created.
             */
            AbstractEntityInstance(const Mind::Point2Df& position) ;

            /**
             * @brief   Destruction of the AbstractEntityInstance.
             */
            virtual ~AbstractEntityInstance() ;
    } ;

} ;


#endif
