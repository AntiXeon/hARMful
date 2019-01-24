#ifndef __HOPE_SCENE__
#define __HOPE_SCENE__

#include <scene/Entity.hpp>

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

        public:
            /**
             * Get the root entity of the scene.
             */
            Entity& root() ;
    } ;
}

#endif
