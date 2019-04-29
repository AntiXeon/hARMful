#ifndef __HOPE__GL_RENDERER__
#define __HOPE__GL_RENDERER__

#include <scene/ogl/visitors/cache/MeshData.hpp>
#include <scene/ogl/visitors/cache/FrameRenderCache.hpp>
#include <scene/ogl/rendering/glsl/ubo/ModelGLSLDataUBO.hpp>

namespace Hope::GL {
    /**
     * Render the scene.
     */
    class OpenGLRenderer final {
        private:
            /**
             * Model UBO.
             */
            ModelGLSLDataUBO m_ubo ;

            /**
             * Cache for rendering the current frame.
             */
            FrameRenderCache m_renderCache ;

        public:
            /**
             * Render the scene.
             */
            void render() ;

            /**
             * Get the cache for rendering the current frame.
             */
            const FrameRenderCache& cache() const {
                return m_renderCache ;
            }

            FrameRenderCache& cache() {
                return m_renderCache ;
            }

        private:
            /**
             * Use a material component.
             */
            void useMaterial(const Hope::MaterialComponent* component) ;
    } ;
}

#endif
