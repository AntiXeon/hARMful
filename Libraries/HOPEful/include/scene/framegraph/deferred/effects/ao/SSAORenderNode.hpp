#ifndef __HOPE__SSAO_RENDER_NODE__
#define __HOPE__SSAO_RENDER_NODE__

#include <utils/Platform.hpp>

#include <HopeAPI.hpp>

#ifdef OGL
    #include <scene/ogl/textures/TextureImage2D.hpp>
    #include <scene/components/materials/shaders/GLSL/includes/Ao.hpp>
    namespace API = Hope::GL ;
#endif

#include <scene/framegraph/deferred/effects/ao/SSAOData.hpp>
#include <scene/framegraph/deferred/effects/EffectFramegraphNode.hpp>
#include <scene/framegraph/deferred/effects/ao/AOFramegraphSubtree.hpp>
#include <scene/framegraph/deferred/offscreen/GBufferRenderNode.hpp>
#include <scene/SceneTypes.hpp>
#include <geometry/points/Point4Df.hpp>

namespace Hope {
    /**
     * Node to compute screen-space ambient occlusion.
     */
    class SSAORenderNode final : public EffectFrameGraphNode {
        public:
            static const unsigned char AORenderTarget = 1 ;
            static const unsigned char NoiseRenderTarget = 1 ;

        private:
            /**
             * Amount of pixels on a side of the square noise texture that is
             * generated.
             */
            const static int NoiseTextureSideSize = AO_NOISE_TEXTURE_SIZE ;

            /**
             * Total amount of pixels in the noise texture.
             */
            const static int NoiseTexturePixelAmount = NoiseTextureSideSize * NoiseTextureSideSize ;

            /**
             * Amount of data in the RGB noise texture.
             */
            const static int NoiseTextureDataSize = NoiseTexturePixelAmount * Mind::Vector4f::AmountCoords ;

            /**
             * The effect data that are applied on final rendering stage.
             */
            SSAOData m_effectApplyData ;

            /**
             * Random texture that is used to sample ambient occlusion all over
             * the screen. The texture is wrapped with a repeat mode so that it
             * can be applied to every fragment of the render with a minimal
             * memory cost.
             */
            std::unique_ptr<API::TextureImage2D> m_noiseTexture = nullptr ;

            /**
             * G-Buffer containing the normal and depth buffers, required to
             * compute ambient occlusion.
             */
            GBufferRenderNode* m_gBuffer = nullptr ;

            /**
             * Framebuffer node to which SSAO will be finally rendered to (in a
             * specific render target).
             */
            FramebufferRenderNode* m_output = nullptr ;

            /**
             * Normal-oriented hemisphere kernel.
             */
            std::array<Mind::Vector3f, AO_KERNEL_SIZE> m_kernel ;

            /**
             * Subtree in framegraph to render ambient occlusion.
             */
            AOFramegraphSubtree m_subtree ;

        public:
            /**
             * Create a new SSAORenderNode instance.
             * @param   gBuffer G-Buffer containing required data for SSAO
             *                  computing.
             * @param   output  Framebuffer node to which SSAO will be finally
             *                  rendered to (in a specific render target).
             */
            exported SSAORenderNode(
                GBufferRenderNode* gBuffer,
                FramebufferRenderNode* output,
                FrameGraphNode* parent = nullptr
            ) ;

            /**
             * Get the random texture that is used to sample ambient occlusion
             * all over the screen.
             */
            exported const API::TextureImage2D* noiseTexture() const {
                return m_noiseTexture.get() ;
            }

            /**
             * Get the normal-oriented hemisphere kernel.
             */
            exported const std::array<Mind::Vector3f, AO_KERNEL_SIZE>& kernel() const {
                return m_kernel ;
            }

            /**
             * Get the buffer containing the resulting ambient occlusion.
             */
            exported AbstractFramebufferRenderNode* gBuffer() {
                return m_gBuffer ;
            }

            /**
             * Get the buffer containing the resulting ambient occlusion.
             */
            exported AbstractFramebufferRenderNode* aoBuffer() {
                return m_subtree.aoRendering.offscreen.get() ;
            }

            /**
             * Get the type of the effect.
             */
            exported EffectNodeType effectType() const override {
                return AmbientOcclusionEffectType ;
            }

            /**
             * Get the effect data of the node.
             */
            exported EffectData* data() override {
                return &m_effectApplyData ;
            }

        private:
            /**
             * Generate the noise texture.
             */
            exported void generateNoiseTexture() ;

            /**
             * Generate the AO kernel.
             */
            exported void generateKernel() ;

            /**
             * Generate the subtree of the framegraph.
             */
            exported void generateFramegraphSubtree() ;
    } ;
}

#endif
