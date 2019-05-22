#ifndef __HOPE__CUBEMAP_MATERIAL_COMPONENT__
#define __HOPE__CUBEMAP_MATERIAL_COMPONENT__

#include <scene/components/materials/MaterialComponent.hpp>
#include <scene/common/Color.hpp>
#include <algorithm>
#include <string>
#include <HopeAPI.hpp>

#ifdef OGL
    #include <scene/ogl/rendering/capabilities/DepthTest.hpp>
    #include <scene/ogl/textures/CubemapTexture.hpp>
    namespace API = Hope::GL ;
#endif

namespace Hope {
    /**
     * A material that is used to show a cubemap.
     */
    class CubemapMaterialComponent : public MaterialComponent {
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
            const API::CubemapTexture* m_map = nullptr ;

        public:
            /**
             * Create a CubemapMaterialComponent.
             */
            CubemapMaterialComponent() ;

            /**
             * Destruction of the CubemapMaterialComponent.
             */
            virtual ~CubemapMaterialComponent() ;

            /**
             * Update the uniform values before the processing of the material
             * component.
             */
            void updateUniformValues() override ;

            /**
             * Set the cubemap texture.
             */
            void setCubemap(const API::CubemapTexture* map) {
                m_map = map ;
            }

            /**
             * Get the cubemap texture.
             */
            const API::CubemapTexture* cubemap() const {
                return m_map ;
            }

        protected:
            /**
             * Setup the shader for the forward rendering pass.
             */
            void setupForwardShader() override ;

            /**
             * Setup the shader for the deferred rendering pass.
             */
            void setupDeferredShader() override ;

        private:
            /**
             * Set up the Uniforms of the current material.
             */
            void setupUniforms() ;
    } ;
}

#endif
