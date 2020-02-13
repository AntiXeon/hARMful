#ifndef __HOPE_SCENE__
#define __HOPE_SCENE__

#include <scene/Entity.hpp>
#include <scene/components/RenderConfiguration.hpp>

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
            Entity* m_root = nullptr ;

            /**
             * Enable the configuration of the rendering through frame graph
             * nodes.
             */
            RenderConfiguration* m_renderConfig = nullptr ;

            /**
             * Frame graph visitor for rendering the scene.
             */
            std::shared_ptr<IFrameGraphVisitor> m_frameGraphVisitor = nullptr ;

        public:
            /**
             * Create a new Scene instance.
             */
            Scene(std::shared_ptr<IFrameGraphVisitor> visitor) ;

            /**
             * Destroy the Scene instance.
             */
            virtual ~Scene() ;

            /**
             * Render the scene.
             */
            void render() ;

            /**
             * Loop over Entity objects to lock the ones that have the lock
             * flag.
             * @param   state   Lock state for available entities.
             */
            void lockEntities(const bool state) ;

            /**
             * Get the root entity of the scene.
             */
            Entity* root() const {
                return m_root ;
            }

            /**
             * Set the root of the framegraph.
             */
            void setFrameGraphRoot(FrameGraphNode* root) ;

            // Remove copy/move operations.
            Scene(const Scene& copied) = delete;
            Scene(Scene&& moved) = delete;
            Scene& operator=(const Scene& copied) = delete;
            Scene& operator=(Scene&& moved) = delete;

        private:
            /**
             * Lock an Entity.
             * @param   entity  The Entity to lock if available.
             * @param   state   Lock state.
             */
            void lockEntity(Entity* entity, const bool state) ;
    } ;
}

#endif
