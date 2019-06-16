#ifndef __HOPE__LAYER_OFFSCREEN_RENDER__
#define __HOPE__LAYER_OFFSCREEN_RENDER__

#include <HopeAPI.hpp>

#ifdef OGL
    #include <scene/ogl/rendering/framebuffers/Framebuffer2DStack.hpp>
    namespace API = Hope::GL ;
#endif

#include <scene/FrameGraphNode.hpp>
#include <scene/SceneTypes.hpp>

namespace Hope {
    /**
     * Perform an off-screen render pass using a framebuffer with layered
     * textures.
     */
    class LayerOffScreenRenderNode : public FrameGraphNode {
        friend class FrameGraphBranchState ;

        private:
            /**
             * The underlying framebuffer to perform off-screen rendering.
             */
            API::Framebuffer2DStack* m_framebuffer = nullptr ;

            /**
             * If true, the size of the framebuffer follows the size of the
             * window. If false, the size of the framebuffer is fixed.
             */
            bool m_windowSize = true ;

            /**
             * Layer of the framebuffer to use.
             */
            int m_layer = -1 ;

        public:
            /**
             * Create a new LayerOffScreenRenderNode instance.
             * @param   framebuffer Framebuffer to use.
             * @param   layer       Layer of the framebuffer to use.
             * @param   windowSize  If true, the size of the framebuffer follows
             *                      the size of the window. If false, the size
             *                      of the framebuffer is fixed.
             */
            LayerOffScreenRenderNode(
                API::Framebuffer2DStack* framebuffer,
                int layer,
                const bool windowSize,
                FrameGraphNode* parent = nullptr
            ) ;

            /**
             * Get the framebuffer.
             */
            API::Framebuffer2DStack* framebuffer() {
                return m_framebuffer ;
            }

            /**
             * Get the framebuffer.
             */
            const API::Framebuffer2DStack* framebuffer() const {
                return m_framebuffer ;
            }

            /**
             * Layer of the framegraph to use.
             */
            int layer() const {
                return m_layer ;
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
             * Accept the visitor.
             */
            void specificAccept(IFrameGraphVisitor* visitor) override ;
    } ;
}

#endif
