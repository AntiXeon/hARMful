#ifndef __HOPE__GL_MESHPART__
#define __HOPE__GL_MESHPART__

#include <utils/Platform.hpp>

#include <scene/ogl/GLDefines.hpp>
#include <GL/glew.h>
#include <cstdint>

namespace Hope::GL {
    class MeshGeometry ;
    class Vertex ;

    /**
     * A GeometryPart is a subpart of a Mesh. A complex Mesh can have several parts.
     */
    class GeometryPart final {
        friend class MeshGeometry ;

        private:
            /**
             * ID of the material to draw this part.
             */
            uint32_t m_materialID = INVALID_MATERIAL ;

            /**
             * Offset at which data of the current part are stored in the GPU
             * buffer memory.
             */
            uint32_t m_offset = 0 ;

            /**
             * Amount of vertex indices.
             */
            uint32_t m_amountIndices = 0 ;

        public:
            /**
             * Create a new GeometryPart.
             * Values are not valid!
             */
            exported GeometryPart() = default ;

            /**
             * Create a new GeometryPart.
             */
             exported GeometryPart(
                uint32_t materialID,
                uint32_t offset,
                uint32_t amountIndices
            ) ;

            /**
             * ID of the material to draw this part.
             */
            exported uint32_t materialID() const {
                return m_materialID ;
            }

            /**
             * Offset at which data of the current part are stored in the GPU
             * buffer memory.
             */
            exported uint32_t offset() const {
                return m_offset ;
            }

            /**
             * Amount of indices of vertex in this part.
             */
            exported uint32_t amountIndices() const {
                return m_amountIndices ;
            }
    } ;
}

#endif
