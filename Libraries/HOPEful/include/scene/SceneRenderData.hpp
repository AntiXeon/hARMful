#ifndef __HOPE_SCENE_RENDER_DATA__
#define __HOPE_SCENE_RENDER_DATA__

#include <vector>

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
            std::vector<DirectionalLightComponent*> m_directionalLights ;

            /**
             * Add a light.
             */
            void addLight(LightComponent* light) ;

            /**
             * Remove a light.
             */
            void removeLight(LightComponent* light) ;

        public:
            /**
             * Get the list of lights.
             */
            std::vector<DirectionalLightComponent*> directionalLights() const ;
    } ;
}

#endif
