#ifndef __HOPE__PROCESSED_SCENE_NODE__
#define __HOPE__PROCESSED_SCENE_NODE__

#include <matrices/Matrix4x4f.hpp>

namespace Hope {
    class Entity ;

    /**
     * A structure to aggregate all the required data to render a scene
     * graph with some optimizations, and without having recursion that
     * could lead to a crash if the scene graph is too deep.
     */
    struct ProcessedSceneNode final {
        /**
         * The node itself.
         */
        Hope::Entity* node = nullptr ;

        /**
         * The world matrix of the node. Requires its parents matrices.
         * Cache the world matrix as it is a complicated computation.
         */
        Mind::Matrix4x4f worldMatrix ;
    } ;
}

#endif
