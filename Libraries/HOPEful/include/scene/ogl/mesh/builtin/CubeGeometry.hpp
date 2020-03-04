#ifndef __HOPE__GL_CUBE_GEOMETRY__
#define __HOPE__GL_CUBE_GEOMETRY__

#include <utils/Platform.hpp>

#include <array>
#include <scene/ogl/mesh/Geometry.hpp>
#include <scene/ogl/mesh/GeometryPart.hpp>
#include <scene/ogl/GLDefines.hpp>
#include <GL/glew.h>

namespace Hope::GL {
    /**
     * A CubeGeometry is dedicated to draw a simple cube.
     */
    class CubeGeometry final : public Geometry {
        private:
            static const size_t AmountParts = 1 ;
            static const size_t AmountVertexCoords = 8 * 3 ;
            static const size_t AmountIndices = 3 * 2 * 6 ;

            /**
             * ID of the VAO.
             */
            GLuint m_vertexArray = INVALID_VALUE ;

            /**
             * ID of the vertex buffer of this part.
             */
            GLuint m_vertexBuffer = INVALID_VALUE ;

            /**
             * ID of the index buffer of this part.
             */
            GLuint m_indexBuffer = INVALID_VALUE ;

            /**
             * Mesh parts composing the whole mesh.
             */
            std::array<GeometryPart, AmountParts> m_parts ;

        public:
            /**
             * Create a new CubeGeometry.
             */
            exported CubeGeometry() ;

            /**
             * Destruction of the CubeGeometry.
             */
            exported ~CubeGeometry() ;

            /**
             * Bind the geometry for data management, rendering, etc.
             */
            void bind() const override {
                glBindVertexArray(m_vertexArray) ;
            }

            /**
             * Unbind the geometry after data management, rendering, etc.
             */
            void unbind() const override {
                glBindVertexArray(0) ;
            }

            /**
             * Get a part.
             */
            const GeometryPart& part(const uint32_t index) const override {
                return m_parts[index] ;
            }

            /**
             * Amount of parts in the geometry.
             */
            size_t amountParts() const override {
                return AmountParts ;
            }

            /**
             * Amount of indices in the geometry.
             */
            size_t amountIndices() const override {
                return AmountIndices ;
            }

            /**
             * Type of the indice values.
             */
            GLenum indiceType() const override {
                return GL_UNSIGNED_BYTE ;
            }

            // Copy/move operations.
            CubeGeometry(const CubeGeometry& copied) = default ;
            CubeGeometry(CubeGeometry&& moved) = default ;
            CubeGeometry& operator=(const CubeGeometry& copied) = default ;
            CubeGeometry& operator=(CubeGeometry&& moved) = default ;

        private:
            /**
             * Point of the cube.
             */
            void fillBuffers() ;
    } ;
}

#endif
