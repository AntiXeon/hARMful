#ifndef __HOPE__TRANSFORM__
#define __HOPE__TRANSFORM__

#include <geometry/quaternions/Quaternion.hpp>
#include <geometry/points/Point3Df.hpp>
#include <matrices/Matrix4x4f.hpp>

namespace Hope {
    /**
     * Transform of an object to describe its position, rotation and scale in a
     * 3D space. It is also a handy way to manipulate such 3D objects in their
     * environment.
     * Operations on transform are applied in the following order:
     * scale, rotation, translation.
     */
    class Transform final {
        private:
            /**
             * Rotation of the object.
             */
            Mind::Quaternion m_rotation = Mind::Quaternion(0.f, 0.f, 0.f, 1.f) ;

            /**
             * Translation of the object.
             */
            Mind::Vector3f m_translation = Mind::Vector3f(0.f, 0.f, 0.f) ;

            /**
             * Scale of the object.
             */
            Mind::Vector3f m_scale = Mind::Vector3f(1.f, 1.f, 1.f) ;

            /**
             * Store Euler angles as a cache.
             */
            Mind::Vector3f m_eulerAngles ;

            /**
             * Transformation matrix containing all the operations in a single
             * place: scale, rotation and translation.
             */
            Mind::Matrix4x4f m_matrix ;

            /**
             * true if the matrix is not up to date with the independent
             * transformation values (m_rotation, m_translation and m_scale).
             * false if the matrix corresponds to these values.
             */
            bool m_outdatedMatrix = true ;

        public:
            /**
             * Create a new Transform.
             */
            Transform() ;

            /**
             * Set the rotation of the object.
             * @param  rotation    Rotation to apply.
             */
            void setRotation(const Mind::Quaternion& rotation) ;

            /**
             * Set the rotation of the object on X axis.
             * @param  rotation    Rotation to apply.
             */
            void setRotationOnX(const float rotation) ;

            /**
             * Set the rotation of the object on Y axis.
             * @param  rotation    Rotation to apply.
             */
            void setRotationOnY(const float rotation) ;

            /**
             * Set the rotation of the object on Z axis.
             * @param  rotation    Rotation to apply.
             */
            void setRotationOnZ(const float rotation) ;

            /**
             * Set the translation of the object.
             * @param  translation  Translation to apply.
             */
            void setTranslation(const Mind::Vector3f& translation) ;

            /**
             * Set the scale of the object.
             * @param  scale    Scale to apply.
             */
            void setScale(const float scale) ;

            /**
             * Set the scale of the object.
             * @param  scale    Scale to apply.
             */
            void setScale3D(const Mind::Vector3f& scale) ;

            /**
             * Set the transformation matrix of the object.
             */
            void setMatrix(const Mind::Matrix4x4f& matrix) ;


            /**
             * Get the rotation of the object.
             * @return  Rotation of the object.
             */
            Mind::Quaternion rotation() const ;

            /**
             * Get the rotation of the object on X axis.
             * @return  Rotation of the object.
             */
            float rotationOnX() const ;

            /**
             * Get the rotation of the object on Y axis.
             * @return  Rotation of the object.
             */
            float rotationOnY() const ;

            /**
             * Get the rotation of the object on Z axis.
             * @return  Rotation of the object.
             */
            float rotationOnZ() const ;

            /**
             * Get the translation of the object.
             * @return  Translation of the object.
             */
            Mind::Vector3f translation() const ;

            /**
             * Get the scale of the object.
             * @return  Scale of the object.
             */
            float scale() const ;

            /**
             * Get the scale of the object for each axis.
             * @return  Scale of the object.
             */
            Mind::Vector3f scale3D() const ;

            /**
             * Get the transformation matrix of the object.
             * @return  Transformation matrix of the object.
             */
            const Mind::Matrix4x4f& matrix() ;
    } ;
}

#endif
