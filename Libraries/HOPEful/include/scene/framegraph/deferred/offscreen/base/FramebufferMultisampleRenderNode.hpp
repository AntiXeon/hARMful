#ifndef __HOPE__FRAMEBUFFER_MULTISAMPLE_RENDER__
#define __HOPE__FRAMEBUFFER_MULTISAMPLE_RENDER__

#include <scene/framegraph/deferred/offscreen/base/AbstractFramebufferRenderNode.hpp>
#include <scene/SceneTypes.hpp>
#include <memory>

#ifdef OGL
    #include <scene/ogl/rendering/framebuffers/Framebuffer2DMultisample.hpp>
#endif

namespace Hope {
    /**
     * Node to use a framebuffer supporting multisampling (antialiasing).
     */
    class FramebufferMultisampleRenderNode : public AbstractFramebufferRenderNode {
        private:
            /**
             * The underlying framebuffer to perform off-screen rendering.
             */
            std::shared_ptr<API::Framebuffer2DMultisample> m_framebuffer = nullptr ;

        public:
            /**
             * Create a new FramebufferRenderNode instance.
             * @param   size        Size of the framebuffer.
             * @param   windowSize  If true, the size of the framebuffer follows
             *                      the size of the window. If false, the size
             *                      of the framebuffer is fixed.
             */
            FramebufferMultisampleRenderNode(
                const Mind::Dimension2Di& size,
                const bool windowSize,
                FrameGraphNode* parent = nullptr
            ) ;

            /**
             * Create a new FramebufferMultisampleRenderNode instance to edit
             * the content of an existing framebuffer.
             * @param   other   Other FramebufferMultisampleRenderNode to edit
             *                  framebuffer.
             */
            FramebufferMultisampleRenderNode(
                FramebufferMultisampleRenderNode* other,
                FrameGraphNode* parent
            ) ;

            /**
             * Get the framebuffer.
             */
            API::Framebuffer* framebuffer() override {
                return m_framebuffer.get() ;
            }

            /**
             * Get the framebuffer.
             */
            const API::Framebuffer* framebuffer() const override {
                return m_framebuffer.get() ;
            }

        protected:
            /**
             * Get the framebuffer.
             */
            API::Framebuffer2DMultisample* framebufferMultisample() const {
                return m_framebuffer.get() ;
            }
    } ;
}

#endif
