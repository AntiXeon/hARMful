#ifndef __HOPE__GL_ENVIRONMENTMAP__
#define __HOPE__GL_ENVIRONMENTMAP__

#include <utils/Platform.hpp>
#include <scene/ogl/textures/environment/EnvironmentMapTexture.hpp>
#include <memory>
#include <string>

namespace Hope::GL {
    /**
     * An environment map contains all the required data for performing image
     * based lighting: environment map itself (cubemap to be displayed as sky
     * for example), its specular maps (for different roughness degrees in
     * physics-based shading pipeline) and irradiance map (for ambient lighting
     * based on the environment map).
     */
    class EnvironmentMap final {
        private:
            /**
             * Environment map itself (sky, etc).
             */
            std::unique_ptr<EnvironmentMapTexture> m_envMap = nullptr ;

            /**
             * Specular map (with roughness levels as mipmap) to display
             * precomputed specular on objects.
             */
            std::unique_ptr<EnvironmentMapTexture> m_specularMap = nullptr ;

            /**
             * Irradiance map for ambient lighting.
             */
            std::unique_ptr<EnvironmentMapTexture> m_irradianceMap = nullptr ;

        public:
            /**
             * Create a new EnvironmentMap instance.
             * @param   hemFilepath Path to the HEM archive containing all
             *                      the image files.
             */
            exported EnvironmentMap(const std::string& hemFilepath) ;

            /**
             * Get the environment map texture.
             */
            exported EnvironmentMapTexture* envMap() const {
                return m_envMap.get() ;
            }

            /**
             * Get the specular map texture.
             */
            exported EnvironmentMapTexture* specularMap() const {
                return m_specularMap.get() ;
            }

            /**
             * Get the irradiance map texture.
             */
            exported EnvironmentMapTexture* irradianceMap() const {
                return m_irradianceMap.get() ;
            }
    } ;
}

#endif
