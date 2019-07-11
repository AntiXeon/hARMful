#ifndef __HOPE__FRAMEBUFFER_RENDER__
#define __HOPE__FRAMEBUFFER_RENDER__

#include <HopeAPI.hpp>

#ifdef OGL
    #include <scene/ogl/rendering/framebuffers/Framebuffer2D.hpp>
    namespace API = Hope::GL ;
#endif

#include <scene/FrameGraphNode.hpp>
#include <scene/SceneTypes.hpp>

namespace Hope {
    /**
     * Perform an off-screen render pass using a framebuffer.
     */
    class FramebufferRenderNode : public FrameGraphNode {
        friend class FrameGraphBranchState ;

        private:
            /**
             * To know if the framebuffer has been created internally or if it
             * is taken from another node.
             */
            bool m_internalFramebuffer = false ;

            /**
             * The underlying framebuffer to perform off-screen rendering.
             */
            API::Framebuffer2D* m_framebuffer = nullptr ;

            /**
             * If true, the size of the framebuffer follows the size of the
             * window. If false, the size of the framebuffer is fixed.
             */
            bool m_windowSize = true ;

        public:
            /**
             * Create a new FramebufferRenderNode instance.
             * @param   size        Size of the framebuffer.
             * @param   windowSize  If true, the size of the framebuffer follows
             *                      the size of the window. If false, the size
             *                      of the framebuffer is fixed.
             */
            FramebufferRenderNode(
                const Mind::Dimension2Di& size,
                const bool windowSize,
                FrameGraphNode* parent = nullptr
            ) ;

            /**
             * Create a new OffScreenRenderNode instance to edit the content of
             * an existing framebuffer.
             * @param   other   Other OffScreenRenderNode to edit framebuffer.
             */
            FramebufferRenderNode(
                FramebufferRenderNode* other,
                FrameGraphNode* parent
            ) ;

            /**
             * Destruction of the FramebufferRenderNode.
             */
            virtual ~FramebufferRenderNode() ;

            /**
             * Get the framebuffer.
             */
            API::Framebuffer2D* framebuffer() {
                return m_framebuffer ;
            }

            /**
             * Get the framebuffer.
             */
            const API::Framebuffer2D* framebuffer() const {
                return m_framebuffer ;
            }

            /**
             * If true, the size of the framebuffer follows the size of the
             * window. If false, the size of the framebuffer is fixed.
             */
            bool windowSize() const {
                return m_windowSize ;
            }

            // Avoid copy/move operations.
            FramebufferRenderNode(const FramebufferRenderNode& copied) = delete ;
            FramebufferRenderNode(FramebufferRenderNode&& moved) = delete ;
            FramebufferRenderNode& operator=(const FramebufferRenderNode& copied) = delete ;
            FramebufferRenderNode& operator=(FramebufferRenderNode&& moved) = delete ;

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
