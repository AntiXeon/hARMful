#ifndef __HOPE_SCENE__
#define __HOPE_SCENE__

#include <scene/Entity.hpp>
#include <scene/components/RenderConfiguration.hpp>
#include <scene/ogl/visitors/OpenGLFrameGraphVisitor.hpp>
#include <interfaces/IRenderable.hpp>

namespace Hope {
    /**
     * Scene that embeds the scene graph.
     */
    class Scene : public IRenderable {
        private:
            /**
             * Root entity of the scene.
             */
            Entity m_root ;

            /**
             * Enable the configuration of the rendering through frame graph
             * nodes.
             */
            RenderConfiguration m_renderConfig ;

            /**
             * Frame graph visitor for rendering the scene.
             */
            Hope::GL::OpenGLFrameGraphVisitor m_frameGraphVisitor ;

        public:
            /**
             * Create a new Scene instance.
             */
            Scene() ;

            /**
             * Render the scene.
             */
            void render() override ;

            /**
             * Get the root entity of the scene.
             */
            Entity& root() ;

            /**
             * Set the root of the framegraph.
             */
            void setFrameGraphRoot(FrameGraphNode* root) ;
    } ;
}

#endif
