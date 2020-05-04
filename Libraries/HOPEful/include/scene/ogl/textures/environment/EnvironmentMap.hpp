#ifndef __HOPE__GL_ENVIRONMENTMAP__
#define __HOPE__GL_ENVIRONMENTMAP__

#include <scene/ogl/textures/environment/EnvironmentMapTexture.hpp>
#include <scene/ogl/textures/environment/EnvironmentMapProcessing.hpp>
#include <array>
#include <memory>
#include <GL/glew.h>

namespace Hope::GL {
    /**
     * Aggregate an environment map and its related irradiance map.
     */
    class EnvironmentMap final {
        private:
            /**
             * The environment map as a cubemap.
             */
            std::unique_ptr<EnvironmentMapTexture> m_environmentMap = nullptr ;

            /**
             * The irradiance map as a cubemap.
             */
            std::unique_ptr<EnvironmentMapTexture> m_irradianceMap = nullptr ;

            /**
             * The radiance map as a cubemap.
             */
            std::unique_ptr<EnvironmentMapTexture> m_radianceMap = nullptr ;

        public:
            /**
             * Create a new environment map.
             * It builds the environment map and both its irradiance and
             * radiance maps. Notice that it can be a quite long process,
             * including if needed, the conversion from 2:1 equirectangular to
             * cubemap.
             */
            EnvironmentMap(const std::string& path) ;

            /**
             * Create a new environment map.
             * Directly load precomputed environment, irradiance and radiance
             * maps.
             */
            EnvironmentMap(
                const std::string& pathEnvironment,
                const std::string& pathIrradiance,
                const std::string& pathRadiance
            ) ;

            /**
             * Get the environment map.
             */
            std::unique_ptr<EnvironmentMapTexture> environment() {
                return std::move(m_environmentMap) ;
            }

            /**
             * Get the irradiance map.
             */
            std::unique_ptr<EnvironmentMapTexture> irradiance() {
                return std::move(m_irradianceMap) ;
            }

            /**
             * Get the radiance map.
             */
            std::unique_ptr<EnvironmentMapTexture> radiance() {
                return std::move(m_irradianceMap) ;
            }
    } ;
}

#endif
