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
            Entity* m_root = nullptr ;

            /**
             * Enable the configuration of the rendering through frame graph
             * nodes.
             */
            RenderConfiguration* m_renderConfig = nullptr ;

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
             * Destroy the Scene instance.
             */
            virtual ~Scene() ;

            /**
             * Render the scene.
             */
            void render() override ;

            /**
             * Get the root entity of the scene.
             */
            Entity* root() ;

            /**
             * Set the root of the framegraph.
             */
            void setFrameGraphRoot(FrameGraphNode* root) ;


            // Remove copy/move operations.
            Scene(const Scene& copied) = delete;
            Scene(Scene&& moved) = delete;
            Scene& operator=(const Scene& copied) = delete;
            Scene& operator=(Scene&& moved) = delete;
    } ;
}

#endif
