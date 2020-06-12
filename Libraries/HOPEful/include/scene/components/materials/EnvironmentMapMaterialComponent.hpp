#ifndef __HOPE__CUBEMAP_MATERIAL_COMPONENT__
#define __HOPE__CUBEMAP_MATERIAL_COMPONENT__

#include <utils/Platform.hpp>

#include <scene/components/materials/MaterialComponent.hpp>
#include <scene/common/Color.hpp>
#include <algorithm>
#include <memory>
#include <string>

#include <HopeAPI.hpp>

#ifdef OGL
    #include <scene/ogl/rendering/capabilities/DepthTest.hpp>
    #include <scene/ogl/textures/environment/EnvironmentMap.hpp>
    namespace API = Hope::GL ;
#endif

namespace Hope {
    /**
     * A material that is used to show a cubemap.
     */
    class EnvironmentMapMaterialComponent : public MaterialComponent {
        public:
            /**
             * Component class type.
             */
            static const ComponentType ClassType = MaterialComponentType ;

        private:
            /**
             * Binding of the cubemap.
             */
            static const unsigned short CubemapBinding = 0 ;

            /**
             * Cubemap texture.
             */
            std::shared_ptr<API::EnvironmentMapTexture> m_map = nullptr ;

        public:
            /**
             * Create a EnvironmentMapMaterialComponent.
             */
            exported EnvironmentMapMaterialComponent(API::EnvironmentMap* map) ;

            /**
             * Update the uniform values before the processing of the material
             * component.
             */
            exported void updateUniformValues() override ;

        protected:
            /**
             * Setup the shader for the forward rendering pass.
             */
            exported void setupForwardShader() override ;

            /**
             * Setup the shader for the deferred rendering pass.
             */
            exported void setupDeferredShader() override ;

        private:
            /**
             * Set up the Uniforms of the current material.
             */
            exported void setupUniforms() ;
    } ;
}

#endif
