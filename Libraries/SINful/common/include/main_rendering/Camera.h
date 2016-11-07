#ifndef __SIN_ABSTRACT_CAMERA_2D__
#define __SIN_ABSTRACT_CAMERA_2D__


#include <vector>
#include <geometry/dimensions/Dimension2Df.h>
#include <scene_objects/entities/instances/AbstractEntityInstance.h>


namespace Sin {

    /**
     * @brief   A Camera is used to render a part of the scene.
     * @author  CB (c) 2016
     * @version 0.1     2016/02/13
     */
    class Camera {
        private:
            /**
             * @brief   Area of the scene that is visible through the
             *          Camera.
             */
            Mind::Dimension2Df m_frustum ;

            /**
             * @brief   Instances of entities the camera is attached to.
             */
            std::vector<AbstractEntityInstance*> m_attachedTo ;
            typedef std::vector<AbstractEntityInstance*>::iterator AttachIterator ;


        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Creation of a Camera with default values.
             * @param   frustum     Area of the scene that is visible through
             *                      the Camera.
             */
            Camera(const Mind::Dimension2Df& frustum) ;

            /**
             * @brief   Destruction of the Camera.
             */
            virtual ~Camera() ;


                                                             /*** UTILITIES ***/
            /**
             * @brief   Attach the Camera to an AbstractEntityInstance.
             * @param   entity  The entity to attach the Camera to.
             */
            void attachTo(AbstractEntityInstance* entity) ;

            /**
             * @brief   Detach the Camera from the given
             *          AbstractEntityInstance. The Camera won't follow
             *          it anymore.
             * @param   entity  The entity to detach the Camera from.
             */
            void detachFrom(AbstractEntityInstance* entity) ;


        private:
            /**
             * @brief   Search for a specific AbstractEntityInstance.
             * @param   entity  The entity to search in the attached entities.
             * @return  Iterator pointing on the found entity, end if not found.
             */
            AttachIterator search(AbstractEntityInstance* entity) ;


                                                     /*** SETTERS / GETTERS ***/
            /**
             * @brief   Set the area of the scene that is visible through the
             *          Camera.
             * @param   frustum     Frustum of the Camera.
             */
            void setFrustum(const Mind::Dimension2Df& frustum) ;

            /**
             * @brief   Set the area of the scene that is visible through the
             *          Camera.
             * @param   width   Width of the frustum of the Camera.
             * @param   height  Height of the frustum of the Camera.
             */
            void setFrustum(
                            const Mind::Scalar& width,
                            const Mind::Scalar& height
                           ) ;
    } ;

} ;


#endif
