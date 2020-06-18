#ifndef __HOPE__GL_ENVIRONMENTMAP__
#define __HOPE__GL_ENVIRONMENTMAP__

#include <utils/Platform.hpp>
#include <scene/ogl/textures/environment/EnvironmentMapTexture.hpp>
#include <files/archives/TARData.hpp>
#include <memory>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

namespace Hope {
    class EnvironmentMapMaterialComponent ;
    class ShadingDeferredRenderMaterialComponent ;
}

namespace Hope::GL {
    /**
     * An environment map contains all the required data for performing image
     * based lighting: environment map itself (cubemap to be displayed as sky
     * for example), its specular maps (for different roughness degrees in
     * physics-based shading pipeline) and irradiance map (for ambient lighting
     * based on the environment map).
     */
    class EnvironmentMap final {
        friend class Hope::EnvironmentMapMaterialComponent ;
        friend class Hope::ShadingDeferredRenderMaterialComponent ;

        public:
            static const std::string EnvironmentMapName ;
            static const std::string IrradianceMapName ;
            static const std::string SpecularMapName ;

        private:
            /**
             * Environment map itself (sky, etc).
             */
            std::shared_ptr<EnvironmentMapTexture> m_envMap = nullptr ;

            /**
             * Specular map (with roughness levels as mipmap) to display
             * precomputed specular on objects.
             */
            std::shared_ptr<EnvironmentMapTexture> m_specularMap = nullptr ;

            /**
             * Irradiance map for ambient lighting.
             */
            std::shared_ptr<EnvironmentMapTexture> m_irradianceMap = nullptr ;

        public:
            /**
             * Create a new EnvironmentMap instance.
             * @param   hemFilepath Path to the HEM archive containing all
             *                      the image files.
             */
            exported EnvironmentMap(const std::string& hemFilepath) ;

        private:
            /**
             * Get the environment map texture.
             */
            exported std::shared_ptr<EnvironmentMapTexture> envMap() const {
                return m_envMap ;
            }

            /**
             * Get the specular map texture.
             */
            exported std::shared_ptr<EnvironmentMapTexture> specularMap() const {
                return m_specularMap ;
            }

            /**
             * Get the irradiance map texture.
             */
            exported std::shared_ptr<EnvironmentMapTexture> irradianceMap() const {
                return m_irradianceMap ;
            }

            /**
             * Get the specular levels in order from bigger size to smaller one.
             * @param hemContent    TAR archive that contains the environment map
             *                      cube face textures.
             * @return  Ordered list of specular map sizes.
             */
             exported bool orderedSpecularLevels(
                 const Spite::TARData& hemContent,
                 std::vector<unsigned int>& levels
             ) ;

            /**
             * Check the specular levels have the expected values.
             */
            exported bool checkSpecularLevels(const std::vector<unsigned int>& levels) ;
    } ;
}

#endif
