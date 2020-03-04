#ifndef __HOPE__FOG_RENDER_NODE__
#define __HOPE__FOG_RENDER_NODE__

#include <utils/Platform.hpp>

#include <HopeAPI.hpp>

#ifdef OGL
    namespace API = Hope::GL ;
#endif

#include <scene/framegraph/deferred/effects/EffectFramegraphNode.hpp>
#include <scene/framegraph/deferred/effects/fog/FogData.hpp>
#include <scene/SceneTypes.hpp>

namespace Hope {
    /**
     * Render a fog in distance from camera.
     */
    class FogRenderNode final : public EffectFrameGraphNode {
        private:
            /**
             * The effect data that are applied on final rendering stage.
             */
            FogData m_effectData ;

        public:
            /**
             * Node to render fog on distance.
             * @param   color       Color of the fog.
             * @param   minDistance Minimal distance from the camera to start
             *                      displaying fog (low intensity).
             * @param   maxDistance Maximal distance from the camera to end
             *                      displaying fog (full intensity).
             */
            exported FogRenderNode(
                const Color& color,
                const float minDistance,
                const float maxDistance,
                FrameGraphNode* parent = nullptr
            ) ;

            /**
             * Set the color value.
             */
            exported void setColor(const Color& color) {
                m_effectData.setColor(color) ;
            }

            /**
             * Set the minimal distance value.
             */
            exported void setMinimalDistance(const float min) {
                m_effectData.setMinimalDistance(min) ;
            }

            /**
             * Set the maximal distance value.
             */
            exported void setMaximalDistance(const float max) {
                m_effectData.setMaximalDistance(max) ;
            }

            /**
             * Get the type of the effect.
             */
            exported EffectNodeType effectType() const override {
                return FogEffectType ;
            }

            /**
             * Get the effect data of the node.
             */
            exported EffectData* data() override {
                return &m_effectData ;
            }

            // Avoid copy/move operations.
            FogRenderNode(const FogRenderNode& copied) = delete ;
            FogRenderNode(FogRenderNode&& moved) = delete ;
            FogRenderNode& operator=(const FogRenderNode& copied) = delete ;
            FogRenderNode& operator=(FogRenderNode&& moved) = delete ;

        protected:
            /**
             * Accept the visitor.
             */
            exported void specificAccept(IFrameGraphVisitor* visitor) override ;
    } ;
}

#endif
