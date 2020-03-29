#ifndef __HOPE__ABSTRACT_MATERIAL__
#define __HOPE__ABSTRACT_MATERIAL__

#include <utils/Platform.hpp>

#include <scene/components/Component.hpp>
#include <scene/framegraph/shading/RenderEffect.hpp>
#include <scene/components/materials/settings/MaterialSettings.hpp>

#include <HopeAPI.hpp>

#ifdef OGL
    namespace API = Hope::GL ;
#endif

namespace Hope {
    /**
     * A material is applied to a 3D object to define how it is rendered.
     */
    class MaterialComponent : public Component {
        public:
            /**
             * Component class type.
             */
            static const ComponentType ClassType = MaterialComponentType ;

        private:
            /**
             * Names of the uniform variables.
             */
            static const UniformNames Uniforms ;

            /**
             * Settings of the material.
             */
            MaterialSettings m_settings ;

            /**
             * Effect of the material.
             */
            RenderEffect m_effect ;

        public:
            /**
             * Create a MaterialComponent.
             * @param   drawShadow  true to draw a shadow; false otherwise.
             */
            exported MaterialComponent(const bool drawShadow = true) ;

            /**
             * Update the uniform values before the processing of the material
             * component.
             */
            exported virtual void updateUniformValues(const Hope::RenderPassID pass) = 0 ;

            /**
             * To know if the component can be shared by several entities.
             * @return  true as it can be shared among several objects that are
             *          rendered the same way.
             */
            exported bool isShareable() const override {
                return true ;
            }

            /**
             * To know if the component can be removed from its entity(-ies).
             * @return  false, the component cannot be removed.
             */
            exported bool isRemovable() const override {
                return false ;
            }

            /**
             * To know if several components of the current type can be beared
             * by a single entity.
             * @return  true, an entity can bear several MaterialComponent.
             */
            exported bool isStackable() const override {
                return true ;
            }

            /**
             * Check if the material has a render pass corresponding the
             * provided ID.
             */
            exported bool hasRenderPass(const RenderPassID passID) const {
                return m_effect.hasRenderPass(passID) ;
            }

            /**
             * Get a render pass.
             * @return  The render pass having the provided ID if available;
             *          nullptr otherwise.
             */
            exported API::RenderPass* renderPass(const RenderPassID passID) const {
                return m_effect.renderPass(passID) ;
            }

            /**
             * Get the settings of the material.
             */
            exported MaterialSettings& settings() {
                 return m_settings ;
             }

        protected:
            /**
             * Get the effect of the material.
             */
            exported RenderEffect& effect() {
                return m_effect ;
            }

            /**
             * Get the unoforms of the material.
             */
            exported UniformCache& uniforms(const RenderPassID passID) {
                return (m_effect.renderPass(passID)) -> uniformCache() ;
            }

            /**
             * Setup the render passes of the material.
             */
            exported void setupRendering() ;

            /**
             * Setup the shader for the forward rendering pass.
             */
            exported virtual void setupForwardShader() = 0 ;

            /**
             * Setup the shader for the deferred rendering pass.
             */
            exported virtual void setupDeferredShader() = 0 ;

        private:
            /**
             * Set up the shader for the depth map used to generate the shadow
             * map of a directional light.
             */
            exported void setupDirectionalLightDepthMapShader() ;
    } ;
}

#endif
