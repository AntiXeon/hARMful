#ifndef __HOPE_SCENE__
#define __HOPE_SCENE__

#include <utils/Platform.hpp>

#include <scene/Transform.hpp>
#include <scene/components/RenderConfiguration.hpp>
#include <memory>

namespace Hope {
    class IFrameGraphVisitor ;

    /**
     * Scene that embeds the scene graph.
     */
    class Scene {
        private:
            /**
             * true if the Scene is prepared for rendering.
             */
            bool m_isPrepared = false ;

            /**
             * Root entity of the scene.
             */
            std::unique_ptr<Transform> m_root = nullptr ;

            /**
             * Enable the configuration of the rendering through frame graph
             * nodes.
             */
            std::shared_ptr<RenderConfiguration> m_renderConfig = nullptr ;

            /**
             * Frame graph visitor for rendering the scene.
             */
            std::shared_ptr<IFrameGraphVisitor> m_frameGraphVisitor = nullptr ;

        public:
            /**
             * Create a new Scene instance.
             */
            exported Scene(std::shared_ptr<IFrameGraphVisitor> visitor) ;

            /**
             * Render the scene.
             */
            exported void render() ;

            /**
             * Loop over Entity objects to lock the ones that have the lock
             * flag.
             * @param   state   Lock state for available entities.
             */
            exported void lockEntities(const bool state) ;

            /**
             * Get the root entity of the scene.
             */
            exported Transform* root() const {
                return m_root.get() ;
            }

            /**
             * Set the root of the framegraph.
             */
            exported void setFrameGraphRoot(FrameGraphNode* root) ;

        private:
            /**
             * Lock the Entity of a Transform.
             * @param   transform  	The Transform to get the Entity to lock if
			 *						available.
             * @param   state   	Lock state.
             */
            exported void lockEntity(Transform* transform, const bool state) ;
    } ;
}

#endif
