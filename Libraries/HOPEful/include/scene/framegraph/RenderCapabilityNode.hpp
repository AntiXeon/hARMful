#ifndef __HOPE__RENDER_CAPABILITY__
#define __HOPE__RENDER_CAPABILITY__

#include <utils/Platform.hpp>

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
            exported RenderCapabilityNode(FrameGraphNode* parent = nullptr)
                : FrameGraphNode(parent) {}

            /**
             * Add a new capability.
             */
            exported void addCapability(API::Capability* capability) ;

        protected:
            /**
             * Accept the visitor.
             */
            exported void specificAccept(IFrameGraphVisitor* visitor) override ;

        private:
            /**
             * Get the list of capabilities.
             */
            exported const std::vector<API::Capability*>& capabilities() const {
                return m_capabilities ;
            }
    } ;
}

#endif
