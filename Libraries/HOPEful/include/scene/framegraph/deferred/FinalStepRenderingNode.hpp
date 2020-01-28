#ifndef __HOPE__FINAL_STEP_RENDERING__
#define __HOPE__FINAL_STEP_RENDERING__

#include <scene/FrameGraphNode.hpp>
#include <scene/framegraph/deferred/offscreen/base/FramebufferRenderNode.hpp>
#include <scene/components/materials/deferred/GBufferQuadMaterialComponent.hpp>

namespace Hope {
    /**
     * Framegraph node that ends the deferred rendering process and produces the
     * final picture that is shown on screen. It applies different rendering
     * effects as wanted in its configuration (depth of field, bloom,
     * motion blur, ...).
     * One can use a simple OffscreenRenderingNode if no effect is wanted (nor
     * shadows and ambient occlusion though) but is not as obvious as this one
     * when reading the code.
     *
     * @warning A GBuffer must have been created and rendered into before
     *          putting this node in the framegraph!
     */
    class FinalStepRenderingNode final : public FrameGraphNode {
        private:
            /**
             * Material bearing the shader program to use for performing the
             * deferred shading.
             */
            GBufferQuadMaterialComponent* m_material = nullptr ;

        public:
            /**
             * Create a new FinalStepRenderingNode instance.
             * @param   material    Material bearing the shader program to use
             *                      for performing the deferred shading.
             */
            FinalStepRenderingNode(
                GBufferQuadMaterialComponent* material,
                FrameGraphNode* parent = nullptr
            ) ;

            /**
             * Material bearing the shader program to use for performing the
             * deferred shading.
             */
            GBufferQuadMaterialComponent* material() const {
                return m_material ;
            }

        protected:
            /**
             * Accept the visitor.
             */
            void specificAccept(IFrameGraphVisitor* visitor) ;
    } ;
}

#endif
