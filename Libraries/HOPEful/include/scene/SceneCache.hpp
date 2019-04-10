#ifndef __HOPE__SCENE_CACHE__
#define __HOPE__SCENE_CACHE__

#include <set>

namespace Hope {
    class LightComponent ;
    class DirectionalLightComponent ;

    /**
     * Cache some elements of the scene to access them faster while rendering.
     */
    class SceneCache final {
        friend class Scene ;
        friend class LightComponent ;

        private:
            /**
             * List of the directional lights in the scene.
             */
            std::set<DirectionalLightComponent*> m_directionalLights ;

        public:
            /**
             * Register a light.
             */
            void registerLight(LightComponent* light) ;

            /**
             * Deregister a light.
             */
            void deregisterLight(LightComponent* light) ;

            /**
             * Get the list of lights.
             */
            std::set<DirectionalLightComponent*> directionalLights() const ;
    } ;
}

#endif
