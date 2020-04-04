#ifndef __HOPE__DIRECTIONAL_LIGHT_SHADOW_CASCADE__
#define __HOPE__DIRECTIONAL_LIGHT_SHADOW_CASCADE__

#include <utils/Platform.hpp>

#include <HopeAPI.hpp>

#ifdef OGL
    #include <scene/ogl/rendering/framebuffers/Framebuffer2DStack.hpp>
    #include <scene/components/materials/shaders/GLSL/includes/TextureUnits.hpp>
    namespace API = Hope::GL ;
#endif

#include <scene/Entity.hpp>
#include <scene/components/cameras/OrthographicCameraComponent.hpp>
#include <scene/components/lights/DirectionalLightComponent.hpp>
#include <scene/FrameGraphNode.hpp>
#include <scene/components/cameras/light/DirectionalLightCameraComponent.hpp>
#include <scene/framegraph/deferred/effects/shadows/cascade/CSMFramegraphSubtree.hpp>
#include <matrices/Matrix4x4f.hpp>
#include <memory>

namespace Hope {
    /**
     * Store the data for a division of the render camera frustum in which
     * shadows are computed (cascade shadow mapping for directional lights).
     */
    class ShadowCascade final {
        private:
            /**
             * Index of the cascade.
             */
            int8_t m_cascadeIndex = 0 ;

            /**
             * Entity bearing the DirectionalLightCameraComponent.
             */
            std::unique_ptr<Entity> m_lightCamEntity = nullptr ;

            /**
             * Camera component that is used to render the cascade shadow map.
             */
            std::unique_ptr<DirectionalLightCameraComponent> m_lightCamera = nullptr ;

            /**
             * An orthographic camera used to compute the matrices to apply.
             */
            OrthographicCameraComponent* m_computeCameraComponent = nullptr ;

            /**
             * Near plane of the frustum division.
             */
            float m_cascadeNearPlane ;

            /**
             * Far plane of the frustum division.
             */
            float m_cascadeFarPlane ;

            /**
             * Near plane of the frustum division, relatively to the far plane
             * distance of the rendering camera.
             */
            float m_relativeCascadeNearPlane ;

            /**
             * Far plane of the frustum division, relatively to the far plane
             * distance of the rendering camera.
             */
            float m_relativeCascadeFarPlane ;

            /**
             * The subtree is as follows:
             * - ActiveCameraNode for the orthographic camera that renders the
             *   depth map.
             * - RenderPassSelectorNode to only draw the depth map from the
             *   light point-of-view with the previous orthographic camera.
             * - ClearBuffersNode to clear the depth map in between two frame
             *   renders.
             * - LayerFramebufferRenderNode to render the depth map in a dedicated
             *   framebuffer.
             */
            CSMFramegraphSubtree m_fgSubtree ;

            /**
             * Center of the frustum division.
             */
            Mind::Vector3f m_center ;

            /**
             * Light view matrix.
             */
            Mind::Matrix4x4f m_lightViewMatrix ;

            /**
             * Light projection matrix.
             */
            Mind::Matrix4x4f m_lightProjectionMatrix ;

        public:
            /**
             * Create a new ShadowCascade instance.
             */
            exported ShadowCascade(
                int8_t cascadeIndex = -1,
                Entity* cascadeRoot = nullptr,
                OrthographicCameraComponent* computeCameraComponent = nullptr
            ) ;

            /**
             * Update the cascade data.
             */
            exported void update(
                CameraComponent* renderCam,
                const DirectionalLightComponent* light,
                std::array<Mind::Vector3f, CameraComponent::AmountFrustumCorners / 2>& frustumCornersWorld
            ) ;

            /**
             * Set the near plane for the current division.
             */
            exported void setNearPlane(const float nearPlane) {
                m_cascadeNearPlane = nearPlane ;
            }

            /**
             * Set the far plane for the current division.
             */
            exported void setFarPlane(const float farPlane) {
                m_cascadeFarPlane = farPlane ;
            }

            /**
             * Set up the framegraph subtree.
             */
            exported void setupFramegraph(
                FrameGraphNode* owner,
                ActiveCameraNode* renderingCamera,
                API::Framebuffer2DStack* framebuffer
            ) ;

            /**
             * Near plane of the current shadow cascade.
             */
            exported float nearPlane() const {
                return m_cascadeNearPlane ;
            }

            /**
             * Far plane of the current shadow cascade.
             */
            exported float farPlane() const {
                return m_cascadeFarPlane ;
            }

            /**
             * Near plane of the current shadow cascade.
             */
            exported float relativeNearPlane() const {
                return m_relativeCascadeNearPlane ;
            }

            /**
             * Far plane of the current shadow cascade.
             */
            exported float relativeFarPlane() const {
                return m_relativeCascadeFarPlane ;
            }

            /**
             * Get the view matrix of the current shadow cascade.
             */
            exported const Mind::Matrix4x4f& viewMatrix() const {
                return m_lightViewMatrix ;
            }

            /**
             * Get the projection matrix of the current shadow cascade.
             */
            exported const Mind::Matrix4x4f& projectionMatrix() const {
                return m_lightProjectionMatrix ;
            }

        private:
            /**
             * Update the view matrix of the cascade.
             */
            exported void updateLightViewMatrix(
                const Mind::Vector3f& lightPosition,
                const Mind::Vector3f& lightDirection
            ) ;

            /**
             * Update the projection matrix of the cascade.
             */
            exported void updateLightProjectionMatrix(
                const std::array<Mind::Vector3f, CameraComponent::AmountFrustumCorners>& frustumCornersWorld
            ) ;
    } ;
}

#endif
