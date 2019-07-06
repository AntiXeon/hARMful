#ifndef __HOPE__RENDER_CAPABILITY__
#define __HOPE__RENDER_CAPABILITY__

#include <vector>
#include <scene/FrameGraphNode.hpp>
#include <HopeAPI.hpp>

#ifdef OGL
    #include <scene/ogl/rendering/capabilities/Capability.hpp>
    namespace API = Hope::GL ;
#endif

namespace Hope {
    class IFrameGraphVisitor ;

    /**
     * Node used to activate one or several render capabilities before the
     * rendering step at the end of the framegraph branch. It is reverted to its
     * previous state when the rendering of the current framegraph branch is
     * ended.
     */
    class RenderCapabilityNode final : public FrameGraphNode {
        friend class FrameGraphBranchState ;

        private:
            /**
             * Capability to enaéble on rendering of the current framegraph
             * branch.
             */
            std::vector<API::Capability*> m_capabilities ;

        public:
            /**
             * Create a new RenderCapabilityNode.
             */
            RenderCapabilityNode(FrameGraphNode* parent = nullptr)
                : FrameGraphNode(parent) {}

            /**
             * Add a new capability.
             */
            void addCapability(API::Capability* capability) {
                if (capability) {
                    m_capabilities.push_back(capability) ;
                }
            }

        protected:
            /**
             * Accept the visitor.
             */
            void specificAccept(IFrameGraphVisitor* visitor) override {
                visitor -> visit(this) ;
            }

        private:
            /**
             * Get the list of capabilities.
             */
            const std::vector<API::Capability*>& capabilities() const {
                return m_capabilities ;
            }
    } ;
}

#endif
