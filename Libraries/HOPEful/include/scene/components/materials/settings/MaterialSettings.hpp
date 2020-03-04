#ifndef __HOPE__MATERIAL_SETTINGS__
#define __HOPE__MATERIAL_SETTINGS__

#include <utils/Platform.hpp>

#include <scene/framegraph/shading/RenderEffect.hpp>
#include <scene/framegraph/shading/ShaderValue.hpp>
#include <scene/components/materials/settings/AlphaBlendingModes.hpp>
#include <scene/components/materials/settings/ShadowModes.hpp>
#include <map>
#include <string>

#include <HopeAPI.hpp>

#ifdef OGL
    namespace API = Hope::GL ;

    #include <scene/ogl/rendering/capabilities/CapabilityTypes.hpp>
#endif

namespace Hope {
    /**
     * Settings for materials.
     */
    class MaterialSettings final {
        friend class MaterialComponent ;

        private:
            /**
             * Mode for alpha blending.
             */
            AlphaBlendingMode m_alphaBlend = AlphaBlendingMode::Opaque ;

            /**
             * Mode for rendering shadows.
             */
            ShadowMode m_shadowMode = ShadowMode::Opaque ;

            /**
             * Render effect on which settings are applied.
             */
            RenderEffect* m_effect = nullptr ;

        public:
            /**
             * Set the alpha blending mode applied on this material.
             * @param   pass    ID of the render pass to update.
             * @warning This is a helper method to avoid tricky stuff on render
             *          pass capabilities. No need to add blending mode
             *          capability on default render passes or whatever.
             */
            exported void setAlphaBlendingMode(
                const RenderPassID pass,
                const AlphaBlendingMode mode
            ) ;

            /**
             * Get the alpha blending mode applied on this material.
             */
            exported AlphaBlendingMode alphaBlendingMode() const { return m_alphaBlend ; }

            /**
             * Set the shadow mode applied on this material.
             * @warning This is a helper method to avoid tricky stuff on render
             *          pass capabilities. No need to add blending mode
             *          capability on shadow render passes or whatever.
             */
            exported void setShadowMode(const ShadowMode mode) ;

            /**
             * Get the shadow mode applied on this material.
             */
            exported ShadowMode shadowMode() const { return m_shadowMode ; }

        private:
            /**
             * Set the material render effect. Settings are applied on it.
             */
            void setRenderEffect(RenderEffect* effect) { m_effect = effect ; }

            /**
             * Get the capability for alpha channel management from the blending
             * mode.
             */
            API::CapabilityType findAlphaCapabilityType(const AlphaBlendingMode mode) ;
    } ;
}

#endif
