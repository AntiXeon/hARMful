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

        public:
            /**
             * Create a new environment map.
             */
            EnvironmentMap(const std::string& path) ;

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
    } ;
}

#endif
