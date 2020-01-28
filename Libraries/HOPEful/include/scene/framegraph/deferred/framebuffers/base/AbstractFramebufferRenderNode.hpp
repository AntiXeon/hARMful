#ifndef __HOPE__ABSTRACT_FRAMEBUFFER_RENDER__
#define __HOPE__ABSTRACT_FRAMEBUFFER_RENDER__

#include <HopeAPI.hpp>

#ifdef OGL
    #include <scene/ogl/rendering/framebuffers/Framebuffer.hpp>
    namespace API = Hope::GL ;
#endif

#include <scene/FrameGraphNode.hpp>
#include <scene/SceneTypes.hpp>

namespace Hope {
    /**
     * Node to use a framebuffer.
     */
    class AbstractFramebufferRenderNode : public FrameGraphNode {
        friend class FrameGraphBranchState ;

        private:
            /**
             * To know if the framebuffer has been created internally or if it
             * is taken from another node.
             */
            bool m_internalFramebuffer = false ;

            /**
             * If true, the size of the framebuffer follows the size of the
             * window. If false, the size of the framebuffer is fixed.
             */
            bool m_windowSize = true ;

        public:
            /**
             * Create a new AbstractFramebufferRenderNode instance.
             * @param   windowSize  If true, the size of the framebuffer follows
             *                      the size of the window. If false, the size
             *                      of the framebuffer is fixed.
             */
            AbstractFramebufferRenderNode(
                const bool windowSize,
                FrameGraphNode* parent = nullptr
            ) ;

            /**
             * Create a new AbstractFramebufferRenderNode instance to edit the
             * content of an existing framebuffer.
             * @param   other   Other AbstractFramebufferRenderNode to edit
             *                  framebuffer.
             */
            AbstractFramebufferRenderNode(
                AbstractFramebufferRenderNode* other,
                FrameGraphNode* parent
            ) ;

            /**
             * Get the framebuffer.
             */
            virtual API::Framebuffer* framebuffer() = 0 ;

            /**
             * Get the framebuffer.
             */
            virtual const API::Framebuffer* framebuffer() const = 0 ;

            /**
             * If true, the size of the framebuffer follows the size of the
             * window. If false, the size of the framebuffer is fixed.
             */
            bool windowSize() const {
                return m_windowSize ;
            }

            // Avoid copy/move operations.
            AbstractFramebufferRenderNode(const AbstractFramebufferRenderNode& copied) = delete ;
            AbstractFramebufferRenderNode(AbstractFramebufferRenderNode&& moved) = delete ;
            AbstractFramebufferRenderNode& operator=(const AbstractFramebufferRenderNode& copied) = delete ;
            AbstractFramebufferRenderNode& operator=(AbstractFramebufferRenderNode&& moved) = delete ;

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
