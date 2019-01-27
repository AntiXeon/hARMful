#ifndef __HOPE__GL_FRUSTUM_CULLING__
#define __HOPE__GL_FRUSTUM_CULLING__

#include <scene/FrameGraphNode.hpp>

namespace Hope {
    /**
     * If inserted in a frame graph, this node can enable viewing frustum
     * culling. This means that all the objects that are not inside the active
     * camera viewing cone are not drawn at all.
     * This is very useful to save GPU time on rendering computations, improving
     * overall performances.
     *
     * @warning An ActiveCamera node must be inserted in the same frame graph
     *          than the current FrustumCulling node to work properly.
     */
    class FrustumCulling final : public FrameGraphNode {
        public:
            /**
             * Create a new FrustumCulling node.
             */
            FrustumCulling(Hope::FrameGraphNode* parent = nullptr)
                : Hope::FrameGraphNode(parent) {}

        protected:
            /**
             * Accept the visitor.
             */
            void specificAccept(IFrameGraphVisitor* visitor) override ;
    } ;
}

#endif
