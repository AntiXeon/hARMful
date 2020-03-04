#ifndef __HOPE__UNIFORM_NAMES__
#define __HOPE__UNIFORM_NAMES__

#include <utils/Platform.hpp>

#include <string>
#include <vector>

namespace Hope {
    /**
     * List all the uniform names available in a shader program.
     */
    class UniformNames {
        public:
            static const int AmbientLocation = 0 ;
            static const int DiffuseLocation = 1 ;
            static const int SpecularLocation = 2 ;
            static const int ShininessLocation = 3 ;

        private:
            /**
             * List of the uniform names.
             */
            std::vector<std::string> m_names ;

        public:
            /**
             * Initialize uniform names.
             */
            exported UniformNames() ;

            /**
             * Get the names of the uniform variables.
             */
            exported const std::vector<std::string>& names() const {
                return m_names ;
            }


            // Generic uniforms names.
            exported static std::string ModelMatrixParamName() { return "modelMatrix" ; }
            exported static std::string ViewMatrixParamName() { return "viewMatrix" ; }
            exported static std::string ProjectionMatrixParamName() { return "projectionMatrix" ; }
            exported static std::string ModelViewMatrixParamName() { return "modelViewMatrix" ; }
            exported static std::string ViewProjectionMatrixParamName() { return "viewProjectionMatrix" ; }
            exported static std::string MVPMatrixParamName() { return "mvpMatrix" ; }
            exported static std::string InverseModelMatrixParamName() { return "inverseModelMatrix" ; }
            exported static std::string InverseViewMatrixParamName() { return "inverseViewMatrix" ; }
            exported static std::string InverseProjectionMatrixParamName() { return "inverseProjectionMatrix" ; }
            exported static std::string InverseModelViewMatrixParamName() { return "inverseModelViewMatrix" ; }
            exported static std::string InverseViewProjectionMatrixParamName() { return "inverseViewProjectionMatrix" ; }
            exported static std::string InverseMVPMatrixParamName() { return "inverseMVPMatrix" ; }
            exported static std::string NormalMatrixParamName() { return "normalMatrix" ; }
            exported static std::string ModelNormalMatrixParamName() { return "modelNormalMatrix" ; }
            exported static std::string ModelViewNormalMatrixParamName() { return "modelViewNormalMatrix" ; }
            exported static std::string ViewportMatrixParamName() { return "viewportMatrix" ; }
            exported static std::string InverseViewportMatrixParamName() { return "inverseViewportMatrix" ; }
            exported static std::string AspectRatioParamName() { return "aspectRatio" ; }
            exported static std::string TimeParamName() { return "time" ; }
            exported static std::string EyePositionParamName() { return "eyePosition" ; }

            // Lighting uniforms names.
            exported static std::string AmountDirectionalLightsParamName() { return "amountDirectionalLights" ; }
            exported static std::string AmountPointLightsParamName() { return "amountPointLights" ; }

            exported static std::string DirectionalLightParamName() { return "dirLights" ; }
            exported static std::string PointLightParamName() { return "pointLights" ; }
            exported static std::string SpotLightParamName() { return "spotLights" ; }
            exported static std::string HemisphereLightParamName() { return "hemiLights" ; }
            exported static std::string LightColorParamName() { return "color" ; }
            exported static std::string LightPowerParamName() { return "power" ; }
            exported static std::string LightGenerateSpecularParamName() { return "generateSpecular" ; }
            exported static std::string LightFalloffDistanceParamName() { return "falloffDistance" ; }
            exported static std::string LightDirectionParamName() { return "direction" ; }
            exported static std::string LightPositionParamName() { return "position" ; }
            exported static std::string LightLinearAttenuationParamName() { return "linearAttenuation" ; }
            exported static std::string LightQuadraticAttenuationParamName() { return "quadraticAttenuation" ; }

            // Fog uniforms names.
            exported static std::string FogMinimalDistanceParamName() { return "minDistance" ; }
            exported static std::string FogMaximalDistanceParamName() { return "maxDistance" ; }
            exported static std::string FogColorParamName() { return "color" ; }

            // Materials uniforms names.
            exported static std::string MaterialNormalUniformName() { return "normal" ; }
            exported static std::string MaterialAmbientUniformName() { return "ambient" ; }
            exported static std::string MaterialDiffuseUniformName() { return "diffuse" ; }
            exported static std::string MaterialSpecularUniformName() { return "specular" ; }
            exported static std::string MaterialShininessUniformName() { return "shininess" ; }
            exported static std::string MaterialCubemapUniformName() { return "cubemap" ; }

            exported static std::string MaterialUseShadowUniformName() { return "useShadow" ; }
            exported static std::string MaterialAmountCascadesUniformName() { return "amountCascades" ; }
            exported static std::string MaterialCascadedSplitsUniformName() { return "cascadedSplits" ; }
            exported static std::string MaterialLightViewProjectionMatricesUniformName() { return "lightViewProjectionMatrices" ; }

            exported static std::string MaterialUseAOUniformName() { return "useSSAO" ; }
            exported static std::string MaterialAONoiseUniformName() { return "noise" ; }
            exported static std::string MaterialAOKernelUniformName() { return "kernel" ; }

            exported static std::string MaterialGBufferAlbedoUniformName() { return "albedo" ; }
            exported static std::string MaterialGBufferSpecularUniformName() { return "specular" ; }
            exported static std::string MaterialGBufferNormalUniformName() { return "normal" ; }
            exported static std::string MaterialGBufferDepthUniformName() { return "depth" ; }

            // Other uniforms.
            exported static std::string MSAAQualityUniformName() { return "msaaQuality" ; }
    } ;
}

#endif
