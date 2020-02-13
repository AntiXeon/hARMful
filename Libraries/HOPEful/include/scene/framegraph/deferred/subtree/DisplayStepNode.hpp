#ifndef __HOPE__DISPLAY_STEP_NODE__
#define __HOPE__DISPLAY_STEP_NODE__

#include <HopeAPI.hpp>

#ifdef OGL
    #include <scene/ogl/rendering/framebuffers/Framebuffer.hpp>
    namespace API = Hope::GL ;
#endif

#include <scene/FrameGraphNode.hpp>

namespace Hope {
    /**
     * Framegraph node to display on screen the result of deferred rendering.
     */
    class DisplayStepNode final : public FrameGraphNode {
        private:
            /**
             * Framebuffer containing the final render to be displayed.
             */
            API::Framebuffer* m_framebuffer = nullptr ;

        public:
            /**
            * Create a new PostProdStepNode instance.
            * @param   outputFBO    Framebuffer containing the final render to
            *                       be displayed.
            */
            DisplayStepNode(
                API::Framebuffer* framebuffer,
                FrameGraphNode* parent = nullptr
            ) ;

        protected:
            /**
             * Accept the visitor.
             */
            void specificAccept(IFrameGraphVisitor* visitor) ;
    } ;
}

#endif
