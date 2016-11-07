#ifndef __SIN_INTERFACE_IMAGE_ENTITY__
#define __SIN_INTERFACE_IMAGE_ENTITY__


#include <scene_objects/ObjectRotation2D.h>
#include <scene_objects/entities/IEntity.h>


namespace Sin {

    /**
     * @brief   An IEntity contains heavy data to be rendered on screen,
     *          as picture and/or sound for example.
     * @author  CB (c) 2016
     * @version 0.1     2016/02/12
     */
    class IImageEntity : public IEntity {
        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Destruction of the IImageEntity.
             */
            virtual ~IImageEntity() ;

                                                             /*** UTILITIES ***/
            /**
             * @brief   Render the ImageEntity at the given position.
             * @param   x           Position on X axis of the rendered entity.
             * @param   y           Position on Y axis of the rendered entity.
             * @param   rotation    Rotation of the rendered entity.
             * @param   scale       Scale of the rendered entity.
             */
            virtual void renderAt(
                                  const Mind::Scalar& x,
                                  const Mind::Scalar& y,
                                  const ObjectRotation2D& rotation,
                                  const Mind::Scalar& scale
                                 ) = 0 ;
    } ;

} ;


#endif
