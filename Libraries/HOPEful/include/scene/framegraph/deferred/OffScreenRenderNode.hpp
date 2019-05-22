#ifndef __HOPE__OFFSCREEN_RENDER__
#define __HOPE__OFFSCREEN_RENDER__

#include <HopeAPI.hpp>

#ifdef OGL
    #include <scene/ogl/rendering/Framebuffer.hpp>
    namespace API = Hope::GL ;
#endif

#include <scene/FrameGraphNode.hpp>
#include <scene/SceneTypes.hpp>

namespace Hope {
    /**
     * Perform an off-screen render pass using a framebuffer.
     */
    class OffScreenRenderNode : public FrameGraphNode {
        friend class FrameGraphBranchState ;

        private:
            /**
             * The underlying framebuffer to perform off-screen rendering.
             */
            API::Framebuffer m_framebuffer ;

            /**
             * If true, the size of the framebuffer follows the size of the
             * window. If false, the size of the framebuffer is fixed.
             */
            bool m_windowSize = true ;

        public:
            /**
             * Create a new OffScreenRenderNode instance.
             * @param   size        Size of the framebuffer.
             * @param   windowSize  If true, the size of the framebuffer follows
             *                      the size of the window. If false, the size
             *                      of the framebuffer is fixed.
             */
            OffScreenRenderNode(
                const Mind::Dimension2Di& size,
                const bool windowSize,
                FrameGraphNode* parent = nullptr
            ) ;

            /**
             * Get the framebuffer.
             */
            API::Framebuffer& framebuffer() {
                return m_framebuffer ;
            }

            /**
             * Get the framebuffer.
             */
            const API::Framebuffer& framebuffer() const {
                return m_framebuffer ;
            }

            /**
             * If true, the size of the framebuffer follows the size of the
             * window. If false, the size of the framebuffer is fixed.
             */
            bool windowSize() const {
                return m_windowSize ;
            }

        protected:
            /**
             * Set up the attachments to the framebuffer.
             */
            virtual void setup() {}

            /**
             * Accept the visitor.
             */
            void specificAccept(IFrameGraphVisitor* visitor) override ;
    } ;
}

#endif
