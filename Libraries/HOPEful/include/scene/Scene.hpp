#ifndef __HOPE_SCENE__
#define __HOPE_SCENE__

#include <scene/Entity.hpp>
#include <scene/components/RenderConfiguration.hpp>

namespace Hope {
    /**
     * Scene that embeds the scene graph.
     */
    class Scene {
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

        public:
            /**
             * Create a new Scene instance.
             */
            Scene() ;


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
