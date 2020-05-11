#ifndef __HOPE__GL_ENVIRONMENTMAP__
#define __HOPE__GL_ENVIRONMENTMAP__

#include <HopeAPI.hpp>
#include <scene/ogl/textures/environment/EnvironmentMapTexture.hpp>
#include <scene/ogl/textures/environment/EnvironmentMapProcessing.hpp>
#include <array>
#include <memory>

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
             * Loads the different map components (environment, irradiance and
             * radiance) from a directory.
             * @param   directory   Directory to search for the maps.
             * @param   name        Name of the environment map (used in
             *                      filenames).
             */
            EnvironmentMap(
                const std::string& directory,
                const std::string& name
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
