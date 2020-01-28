#ifndef __HOPE__SSAO_RENDER_NODE__
#define __HOPE__SSAO_RENDER_NODE__

#include <HopeAPI.hpp>

#ifdef OGL
    #include <scene/ogl/textures/TextureImage2D.hpp>
    #include <scene/components/materials/shaders/GLSL/includes/Ao.hpp>
    namespace API = Hope::GL ;
#endif

#include <scene/framegraph/deferred/effects/ao/SSAOApplyData.hpp>
#include <scene/framegraph/deferred/effects/EffectFramegraphNode.hpp>
#include <scene/framegraph/deferred/effects/ao/AOFramegraphSubtree.hpp>
#include <scene/framegraph/deferred/offscreen/GBufferRenderNode.hpp>
#include <scene/SceneTypes.hpp>
#include <geometry/points/Point4Df.hpp>

namespace Hope {
    class SSAOMaterialComponent ;
    class SSAOBlurMaterialComponent ;

    /**
     * Node to compute screen-space ambient occlusion.
     */
    class SSAORenderNode final : public EffectFrameGraphNode {
        public:
            static const unsigned char AORenderTarget = 0 ;
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
            SSAOApplyData m_effectApplyData ;

            /**
             * Random texture that is used to sample ambient occlusion all over
             * the screen. The texture is wrapped with a repeat mode so that it
             * can be applied to every fragment of the render with a minimal
             * memory cost.
             */
            std::shared_ptr<API::TextureImage2D> m_noiseTexture = nullptr ;

            /**
             * G-Buffer containing the normal and depth buffers, required to
             * compute ambient occlusion.
             */
            GBufferRenderNode* m_gBuffer = nullptr ;

            /**
             * Material used to render the ambient occlusion.
             */
            SSAOMaterialComponent* m_ssaoMaterial = nullptr ;

            /**
             * Material used to blur (and copy) the ambient occlusion.
             */
            SSAOBlurMaterialComponent* m_ssaoBlurMaterial = nullptr ;

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
             */
            SSAORenderNode(
                GBufferRenderNode* gBuffer,
                FrameGraphNode* parent = nullptr
            ) ;

            /**
             * Destruction of the SSAORenderNode.
             */
            virtual ~SSAORenderNode() ;

            /**
             * Get the random texture that is used to sample ambient occlusion
             * all over the screen.
             */
            const std::shared_ptr<API::TextureImage2D> noiseTexture() const {
                return m_noiseTexture ;
            }

            /**
             * Get the normal-oriented hemisphere kernel.
             */
            const std::array<Mind::Vector3f, AO_KERNEL_SIZE>& kernel() const {
                return m_kernel ;
            }

            /**
             * Get the buffer containing the resulting ambient occlusion.
             */
            AbstractFramebufferRenderNode* gBuffer() {
                return m_gBuffer ;
            }

            /**
             * Get the buffer containing the resulting ambient occlusion.
             */
            AbstractFramebufferRenderNode* aoBuffer() {
                return m_subtree.aoRendering.offscreen ;
            }

            /**
             * Get the type of the effect.
             */
            EffectNodeType effectType() const override {
                return AmbientOcclusionEffectType ;
            }

            /**
             * Get the effect data of the node.
             */
            EffectData* data() override {
                return &m_effectApplyData ;
            }

            // Avoid copy/move operations.
            SSAORenderNode(const SSAORenderNode& copied) = delete ;
            SSAORenderNode(SSAORenderNode&& moved) = delete ;
            SSAORenderNode& operator=(const SSAORenderNode& copied) = delete ;
            SSAORenderNode& operator=(SSAORenderNode&& moved) = delete ;

        private:
            /**
             * Generate the noise texture.
             */
            void generateNoiseTexture() ;

            /**
             * Generate the AO kernel.
             */
            void generateKernel() ;

            /**
             * Generate the subtree of the framegraph.
             */
            void generateFramegraphSubtree() ;
    } ;
}

#endif
