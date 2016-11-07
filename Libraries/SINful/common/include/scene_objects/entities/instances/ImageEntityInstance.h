#ifndef __SIN_IMAGE_ENTITY_INSTANCE__
#define __SIN_IMAGE_ENTITY_INSTANCE__


#include <scene_objects/ObjectRotation2D.h>
#include <geometry/dimensions/Dimension2Df.h>
#include <scene_objects/entities/IImageEntity.h>
#include <scene_objects/entities/instances/AbstractEntityInstance.h>


namespace Sin {

    /**
     * @brief   An ImageEntityInstance is a light copy of an IImageEntity.
     *          It only contains data that may differ from other
     *          ImageEntityInstance (position, rotation, ...). Yet, heavy
     *          data as picture are not duplicated.
     * @author  CB (c) 2016
     * @version 0.1     2016/02/12
     */
    class ImageEntityInstance : public AbstractEntityInstance {
        private:
            /**
             * @brief   Entity the instance is a light copy of.
             */
            IImageEntity* m_entity ;

            /**
             * @brief   Dimension of the ImageEntityInstance.
             */
            Mind::Dimension2Df m_dimension ;

            /**
             * @brief   Rotation of the ImageEntityInstance.
             */
            ObjectRotation2D m_rotation ;


        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Create an ImageEntityInstance at position (0,0).
             * @param   entity  Entity the instance is a light copy of.
             */
            ImageEntityInstance(IImageEntity* entity) ;

            /**
             * @brief   Create an ImageEntityInstance at the given position.
             * @param   position    Position of the ImageEntityInstance when
             *                      created.
             * @param   entity      Entity the instance is a light copy of.
             */
            ImageEntityInstance(
                                IImageEntity* entity,
                                const Mind::Point2Df& position
                               ) ;

            /**
             * @brief   Destruction of the ImageEntityInstance.
             */
            virtual ~ImageEntityInstance() ;


                                                             /*** UTILITIES ***/
            /**
             * @brief   Update the AbstractSceneObject.
             */
            void update() ;

            /**
             * @brief   Render the AbstractSceneObject at its position,
             *          relatively to the given position.
             * @param   relativeX   Relative position on X from which the
             *                      rendering must be done.
             * @param   relativeY   Relative position on Y from which the
             *                      rendering must be done.
             */
            void render(const Mind::Point2Df& relative) ;


            /**
             * @brief   Rotate the instance of the given angle. It is relative
             *          to the current rotation.
             * @param   angle   Angle to increment rotation of the instance.
             */
            void rotate(const Mind::Scalar& angle) ;

            /**
             * @brief   Add the given width and height to the current ones.
             * @param   size    Size to add to the current one.
             */
            void resize(const Mind::Dimension2Df& size) ;


                                                     /*** SETTERS / GETTERS ***/
            /**
             * @brief   Get the dimension of the ImageEntityInstance.
             * @return  Dimensions (width and height) of the
             *          ImageEntityInstance.
             */
            const Mind::Dimension2Df& getDimension() const ;

            /**
             * @brief   Set the dimension of the ImageEntityInstance.
             * @param   dimension   Dimension of the entity.
             */
            void setDimension(const Mind::Dimension2Df& dimension) ;

            /**
             * @brief   Get the rotation data of the ImageEntityInstance.
             * @return  Rotation data (pivot and angle) of the current
             *          ImageEntityInstance.
             */
            const ObjectRotation2D& getRotation() const ;

            /**
             * @brief   Set both pivot and angle of the rotation for the
             *          ImageEntityInstance.
             * @param   rotation    Rotation of the instance.
             */
            void setRotation(const ObjectRotation2D& rotation) ;

            /**
             * @brief   Set pivot of rotation for the current
             *          ImageEntityInstance.
             * @param   pivot   Pivot of rotation for the instance.
             */
            void setPivot(const Mind::Point2Df& pivot) ;

            /**
             * @brief   Set the angle of rotation for the current
             *          ImageEntityInstance.
             * @param   angle   Angle of rotation for the instance.
             */
            void setRotationAngle(const Mind::Scalar& angle) ;


        protected:
            /**
             * @brief   Get the IImageEntity of the instance.
             * @return  The IImageEntity of the ImageEntityInstance.
             */
            IImageEntity* getEntity() const ;

    } ;

} ;


#endif
