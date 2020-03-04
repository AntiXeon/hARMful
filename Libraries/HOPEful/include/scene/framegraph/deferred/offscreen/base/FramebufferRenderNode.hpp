#ifndef __HOPE__FRAMEBUFFER_RENDER__
#define __HOPE__FRAMEBUFFER_RENDER__

#include <utils/Platform.hpp>

#include <scene/framegraph/deferred/offscreen/base/AbstractFramebufferRenderNode.hpp>
#include <scene/SceneTypes.hpp>
#include <memory>

#ifdef OGL
    #include <scene/ogl/rendering/framebuffers/Framebuffer2D.hpp>
#endif

namespace Hope {
    /**
     * Node to use a framebuffer.
     */
    class FramebufferRenderNode : public AbstractFramebufferRenderNode {
        private:
            /**
             * The underlying framebuffer to perform off-screen rendering.
             */
            std::shared_ptr<API::Framebuffer2D> m_framebuffer = nullptr ;

        public:
            /**
             * Create a new FramebufferRenderNode instance.
             * @param   size        Size of the framebuffer.
             * @param   windowSize  If true, the size of the framebuffer follows
             *                      the size of the window. If false, the size
             *                      of the framebuffer is fixed.
             */
            exported FramebufferRenderNode(
                const Mind::Dimension2Di& size,
                const bool windowSize,
                FrameGraphNode* parent = nullptr
            ) ;

            /**
             * Create a new FramebufferRenderNode instance to edit the content of
             * an existing framebuffer.
             * @param   other   Other OffScreenRenderNode to edit framebuffer.
             */
            exported FramebufferRenderNode(
                FramebufferRenderNode* other,
                FrameGraphNode* parent
            ) ;

            /**
             * Get the framebuffer.
             */
            exported API::Framebuffer* framebuffer() override {
                return m_framebuffer.get() ;
            }

            /**
             * Get the framebuffer.
             */
            exported const API::Framebuffer* framebuffer() const override {
                return m_framebuffer.get() ;
            }
    } ;
}

#endif
