#ifndef __HOPE__GL_QUAD_GEOMETRY__
#define __HOPE__GL_QUAD_GEOMETRY__

#include <HopeAPI.hpp>
#include <utils/Platform.hpp>

#include <array>
#include <scene/ogl/mesh/Geometry.hpp>
#include <scene/ogl/mesh/GeometryPart.hpp>
#include <scene/ogl/GLDefines.hpp>

namespace Hope::GL {
    /**
     * A QuadGeometry is dedicated to draw a simple quad.
     */
    class QuadGeometry final : public Geometry {
        public:
            static const size_t Amountvertices = 4 ;

        private:
            static const size_t AmountParts = 1 ;
            static const size_t VertexDataSize = 3 + 2 ;
            static const size_t AmountVertexData = Amountvertices * VertexDataSize ;
            static const size_t AmountIndices = 3 * 2 ;

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
             * Create a new QuadGeometry.
             */
            exported QuadGeometry() ;

            /**
             * Destruction of the QuadGeometry.
             */
            exported ~QuadGeometry() ;

            /**
             * Bind the geometry for data management, rendering, etc.
             */
            exported void bind() const override {
                glBindVertexArray(m_vertexArray) ;
            }

            /**
             * Unbind the geometry after data management, rendering, etc.
             */
            exported void unbind() const override {
                glBindVertexArray(0) ;
            }

            /**
             * Get a part.
             */
            exported const GeometryPart& part(const uint32_t index) const override {
                return m_parts[index] ;
            }

            /**
             * Amount of parts in the geometry.
             */
            exported size_t amountParts() const override {
                return AmountParts ;
            }

            /**
             * Amount of indices in the geometry.
             */
            exported size_t amountIndices() const override {
                return AmountIndices ;
            }

            /**
             * Type of the indice values.
             */
            exported GLenum indiceType() const override {
                return GL_UNSIGNED_BYTE ;
            }

            // Copy/move operations.
            QuadGeometry(const QuadGeometry& copied) = default ;
            QuadGeometry(QuadGeometry&& moved) = default ;
            QuadGeometry& operator=(const QuadGeometry& copied) = default ;
            QuadGeometry& operator=(QuadGeometry&& moved) = default ;

        private:
            /**
             * Point of the cube.
             */
            exported void fillBuffers() ;
    } ;
}

#endif
