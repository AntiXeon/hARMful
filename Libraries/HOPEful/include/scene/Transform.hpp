#ifndef __HOPE__TRANSFORM__
#define __HOPE__TRANSFORM__

#include <utils/Platform.hpp>

#include <scene/Node.hpp>
#include <geometry/quaternions/Quaternion.hpp>
#include <geometry/points/Point3Df.hpp>
#include <matrices/Matrix4x4f.hpp>

#include <memory>

namespace Hope {
	class Entity ;

    /**
     * Transform of an object to describe its position, rotation and scale in a
     * 3D space. It is also a handy way to manipulate such 3D objects in their
     * environment.
     * Operations on transform are applied in the following order:
     * scale, rotation, translation.
     */
    class Transform final : public Node {
        private:
			/**
			 * Entity associated to the current transform.
			 */
			std::unique_ptr<Entity> m_entity ;

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
             * Local transformation matrix containing all the operations in a
			 * single place: scale, rotation and translation.
             */
            Mind::Matrix4x4f m_localMatrix ;

			/**
             * true if the local matrix is not up to date with the independent
             * transformation values (m_rotation, m_translation and m_scale).
             * false if the matrix corresponds to these values.
             */
            bool m_outdatedLocal = true ;

			/**
			 * World transformation matrix containing all the operations in a
			 * single place: scale, rotation and translation.
			 */
			Mind::Matrix4x4f m_worldMatrix ;

			/**
			 * true if the world matrix is not up to date. false otherwise.
			 */
			bool m_outdatedWorld = true ;

        public:
            /**
             * Create a new Transform.
             */
            exported Transform(Transform* parent = nullptr) ;

			/**
			 * Get the entity associated to the current transform.
			 */
			exported Entity* entity() const {
				return m_entity.get() ;
			}

            /**
             * Set the local rotation of the object.
             * @param  rotation    Rotation to apply.
             */
            exported void setRotation(const Mind::Quaternion& rotation) ;

            /**
             * Set the local rotation of the object on X axis.
             * @param  rotation    Rotation to apply.
             */
            exported void setRotationOnX(const float rotation) ;

            /**
             * Set the local rotation of the object on Y axis.
             * @param  rotation    Rotation to apply.
             */
            exported void setRotationOnY(const float rotation) ;

            /**
             * Set the local rotation of the object on Z axis.
             * @param  rotation    Rotation to apply.
             */
            exported void setRotationOnZ(const float rotation) ;

            /**
             * Set the local translation of the object.
             * @param  translation  Translation to apply.
             */
            exported void setTranslation(const Mind::Vector3f& translation) ;

            /**
             * Set the local scale of the object.
             * @param  scale    Scale to apply.
             */
            exported void setScale(const float scale) ;

            /**
             * Set the local scale of the object.
             * @param  scale    Scale to apply.
             */
            exported void setScale3D(const Mind::Vector3f& scale) ;

            /**
             * Set the local transformation matrix of the object.
             */
            exported void setLocal(const Mind::Matrix4x4f& matrix) ;


            /**
             * Get the local rotation of the object.
             * @return  Rotation of the object.
             */
            exported Mind::Quaternion rotation() const ;

            /**
             * Get the local rotation of the object on X axis.
             * @return  Rotation of the object.
             */
            exported float rotationOnX() const ;

            /**
             * Get the local rotation of the object on Y axis.
             * @return  Rotation of the object.
             */
            exported float rotationOnY() const ;

            /**
             * Get the local rotation of the object on Z axis.
             * @return  Rotation of the object.
             */
            exported float rotationOnZ() const ;

            /**
             * Get the local translation of the object.
             * @return  Translation of the object.
             */
            exported Mind::Vector3f translation() const ;

            /**
             * Get the local scale of the object.
             * @return  Scale of the object.
             */
            exported float scale() const ;

            /**
             * Get the local scale of the object for each axis.
             * @return  Scale of the object.
             */
            exported Mind::Vector3f scale3D() const ;

            /**
             * Get the local transformation matrix of the object.
             * @return  Local transformation matrix of the object.
             */
            exported const Mind::Matrix4x4f& local() ;

			/**
			 * Get the world transformation matrix of the object.
			 * @return  World transformation matrix of the object.
			 */
			exported const Mind::Matrix4x4f& world() ;

		private:
			/**
			 * Notify the children transform that the current transform has
			 * changed.
			 */
			exported void notifyWorldChangeToChildren() ;
    } ;
}

#endif
