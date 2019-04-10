#ifndef __HOPE__SCENE_RENDER_DATA__
#define __HOPE__SCENE_RENDER_DATA__

#include <set>

namespace Hope {
    class LightComponent ;
    class DirectionalLightComponent ;

    /**
     * Shared data between scene and the scene graph.
     */
    class SceneRenderData final {
        friend class Scene ;
        friend class LightComponent ;

        private:
            /**
             * List of the directional lights in the scene.
             */
            std::set<DirectionalLightComponent*> m_directionalLights ;

            /**
             * Register a light.
             */
            void registerLight(LightComponent* light) ;

            /**
             * Deregister a light.
             */
            void deregisterLight(LightComponent* light) ;

        public:
            /**
             * Get the list of lights.
             */
            std::set<DirectionalLightComponent*> directionalLights() const ;
    } ;
}

#endif
