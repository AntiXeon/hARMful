#ifndef __HOPE_SCENE_RENDER_DATA__
#define __HOPE_SCENE_RENDER_DATA__

#include <set>

namespace Hope {
    class Light ;

    /**
     * Shared data between scene and the scene graph.
     */
    class SceneRenderData final {
        friend class Scene ;
        friend class Light ;

        private:
            /**
             * List of the lights in the scene.
             */
            std::set<Light*> m_lights ;

            /**
             * Add a light.
             */
            void addLight(Light* light) ;

            /**
             * Remove a light.
             */
            void removeLight(Light* light) ;

            /**
             * Get the list of lights.
             */
            std::set<Light*> lights() const ;
    }
}

#endif
