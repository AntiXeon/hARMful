#ifndef __HOPE__GL_UNIFORM_BUFFER_OBJECT__
#define __HOPE__GL_UNIFORM_BUFFER_OBJECT__

#include <utils/Platform.hpp>

#include <scene/ogl/GLDefines.hpp>
#include <GL/glew.h>

namespace Hope::GL {
    /**
     * A Uniform Buffer Object (UBO) is a GPU buffer in which uniform values are
     * stored. The UBO is shared between every shader program that is used
     * during the frame rendering.
     * All the shader programs have their uniform values updated at once by
     * sending the UBO update before rendering the frame.
     */
    class UniformBufferObject {
        private:
            /**
             * ID of the UBO.
             */
            GLuint m_uniformBuffer = INVALID_VALUE ;

            /**
             * Binding point index of the UBO.
             */
            GLuint m_bindingPointIndex = 0 ;

            /**
             * To know if an update is needed.
             */
            bool m_needUpdate = true ;

        public:
            /**
             * Create a UniformBufferObject instance.
             */
            exported UniformBufferObject(const GLuint bindingPointIndex) ;

            /**
             * Destruction of the UniformBufferObject.
             */
            exported ~UniformBufferObject() ;

            /**
             * Update the UBO on the GPU side.
             */
            exported void update() ;

            /**
             * To know if an update is required.
             */
            exported bool needUpdate() const {
                return m_needUpdate ;
            }

        protected:
            /**
             * The UBO ask for sending new values to the GPU memory.
             */
            exported void askForAnUpdate() {
                m_needUpdate = true ;
            }

            /**
             * The UBO has been updated.
             */
            exported void updated() {
                m_needUpdate = false ;
            }

            /**
             * Get the ID of the UBO.
             */
            exported GLuint bufferID() const {
                return m_uniformBuffer ;
            }

            /**
             * Get the data of the UBO.
             */
            exported virtual const void* data() const = 0 ;

            /**
             * Size of the data.
             */
            exported virtual size_t size() const = 0 ;

        public:
            /**
             * Get the maximal amount of UBO that can be stored on the GPU.
             */
            exported static GLint MaxUniformBufferBindings() {
                GLint value ;
                glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS, &value) ;
                return value ;
            }

            /**
             * Get the maximal size of UBO that can be stored on the GPU.
             */
            exported static GLint MaxUniformBufferSize() {
                GLint value ;
                glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &value) ;
                return value ;
            }

            /**
             * Get the maximal amount of UBO that can be stored on the GPU for a
             * vertex shader.
             */
            exported static GLint MaxVertexUniformBlocks() {
                GLint value ;
                glGetIntegerv(GL_MAX_VERTEX_UNIFORM_BLOCKS, &value) ;
                return value ;
            }

            /**
             * Get the maximal amount of UBO that can be stored on the GPU for a
             * fragment shader.
             */
            exported static GLint MaxFragmentUniformBlocks() {
                GLint value ;
                glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_BLOCKS, &value) ;
                return value ;
            }

            /**
             * Get the maximal amount of UBO that can be stored on the GPU for a
             * geometry shader.
             */
            exported static GLint MaxGeometryUniformBlocks() {
                GLint value ;
                glGetIntegerv(GL_MAX_GEOMETRY_UNIFORM_BLOCKS, &value) ;
                return value ;
            }

            // Copy/move operations.
            UniformBufferObject(const UniformBufferObject& copied) = default ;
            UniformBufferObject(UniformBufferObject&& moved) = default ;
            UniformBufferObject& operator=(const UniformBufferObject& copied) = default ;
            UniformBufferObject& operator=(UniformBufferObject&& moved) = default ;
    } ;
}

#endif
