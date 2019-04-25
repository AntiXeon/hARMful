#ifndef __HOPE__GL_UNIFORM_BUFFER_OBJECT__
#define __HOPE__GL_UNIFORM_BUFFER_OBJECT__

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

        public:
            /**
             * Create a UniformBufferObject instance.
             */
            UniformBufferObject(const GLuint bindingPointIndex) ;

            /**
             * Destruction of the UniformBufferObject.
             */
            ~UniformBufferObject() ;

            /**
             * Update the UBO on the GPU side.
             */
            void update() ;

        protected:
            /**
             * Get the ID of the UBO.
             */
            GLuint bufferID() const {
                return m_uniformBuffer ;
            }

            /**
             * Get the data of the UBO.
             */
            virtual void* data() const = 0 ;

            /**
             * Size of the data.
             */
            virtual size_t size() const = 0 ;

        public:
            /**
             * Get the maximal amount of UBO that can be stored on the GPU.
             */
            static GLint MaxUniformBufferBindings() {
                GLint value ;
                glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS, &value) ;
                return value ;
            }

            /**
             * Get the maximal size of UBO that can be stored on the GPU.
             */
            static GLint MaxUniformBufferSize() {
                GLint value ;
                glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &value) ;
                return value ;
            }

            /**
             * Get the maximal amount of UBO that can be stored on the GPU for a
             * vertex shader.
             */
            static GLint MaxVertexUniformBlocks() {
                GLint value ;
                glGetIntegerv(GL_MAX_VERTEX_UNIFORM_BLOCKS, &value) ;
                return value ;
            }

            /**
             * Get the maximal amount of UBO that can be stored on the GPU for a
             * fragment shader.
             */
            static GLint MaxFragmentUniformBlocks() {
                GLint value ;
                glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_BLOCKS, &value) ;
                return value ;
            }

            /**
             * Get the maximal amount of UBO that can be stored on the GPU for a
             * geometry shader.
             */
            static GLint MaxGeometryUniformBlocks() {
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
