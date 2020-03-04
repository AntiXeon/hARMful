#ifndef __HOPE__GL_GEOMETRY__
#define __HOPE__GL_GEOMETRY__

#include <utils/Platform.hpp>

#include <scene/ogl/mesh/GeometryPart.hpp>

namespace Hope::GL {
    /**
     * Base class for 3D geometries.
     */
    class Geometry {
        public:
            /**
             * Bind the geometry for data management, rendering, etc.
             */
            exported virtual void bind() const = 0 ;

            /**
             * Unbind the geometry after data management, rendering, etc.
             */
            exported virtual void unbind() const = 0 ;

            /**
             * Get a part.
             */
            exported virtual const GeometryPart& part(const uint32_t index) const = 0 ;

            /**
             * Amount of parts in the geometry.
             */
            exported virtual size_t amountParts() const = 0 ;

            /**
             * Amount of indices in the geometry.
             */
            exported virtual size_t amountIndices() const = 0 ;

            /**
             * Type of the indice values.
             * Must be one of GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, or
             * GL_UNSIGNED_INT.
             */
            exported virtual GLenum indiceType() const = 0 ;
    } ;
}

#endif
