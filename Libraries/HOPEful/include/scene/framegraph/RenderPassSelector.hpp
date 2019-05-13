#ifndef __HOPE__RENDER_PASS_SELECTOR__
#define __HOPE__RENDER_PASS_SELECTOR__

#include <scene/FrameGraphNode.hpp>
#include <scene/SceneTypes.hpp>

namespace Hope {
    /**
     * Define which render pass to use to render the objects.
     * Any object that does not bear the RenderPass is not rendered.
     */
    class RenderPassSelector final : public FrameGraphNode {
        private:
            /**
             * ID of the render pass to use for rendering the framegraph branch
             * in which the node is.
             */
            RenderPassID m_passID ;

        public:
            /**
             * Create a new RenderPassSelector node.
             */
            RenderPassSelector(
                const RenderPassID passID,
                Hope::FrameGraphNode* parent = nullptr
            ) : Hope::FrameGraphNode(parent),
                m_passID(passID) {}

            /**
             * Get the ID of the render pass to use for rendering the framegraph
             * branch in which the node is.
             */
            RenderPassID passID() const {
                return m_passID ;
            }

        protected:
            /**
             * Accept the visitor.
             */
            void specificAccept(IFrameGraphVisitor* visitor) override {
                visitor -> visit(this) ;
            }
    } ;
}

#endif
