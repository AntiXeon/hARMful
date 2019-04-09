#ifndef __HOPE_SCENE_RENDER_DATA__
#define __HOPE_SCENE_RENDER_DATA__

#include <set>

namespace Hope {
    class LightComponent ;

    /**
     * Shared data between scene and the scene graph.
     */
    class SceneRenderData final {
        friend class Scene ;
        friend class LightComponent ;

        private:
            /**
             * List of the lights in the scene.
             */
            std::set<LightComponent*> m_lights ;

            /**
             * Add a light.
             */
            void addLight(LightComponent* light) ;

            /**
             * Remove a light.
             */
            void removeLight(LightComponent* light) ;

            /**
             * Get the list of lights.
             */
            std::set<LightComponent*> lights() const ;
    } ;
}

#endif
