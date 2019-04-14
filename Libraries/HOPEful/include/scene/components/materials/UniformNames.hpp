#ifndef __HOPE__UNIFORM_NAMES__
#define __HOPE__UNIFORM_NAMES__

#include <string>
#include <vector>

namespace Hope {
    /**
     * List all the uniform names available in a shader program.
     */
    class UniformNames {
        private:
            /**
             * List of the uniform names.
             */
            std::vector<std::string> m_names ;

        public:
            /**
             * Initialize uniform names.
             */
            UniformNames() ;

            /**
             * Get the names of the uniform variables.
             */
            const std::vector<std::string>& names() const {
                return m_names ;
            }


            // Generic uniforms names.
            static std::string ModelMatrixParamName() { return "modelMatrix" ; }
            static std::string ViewMatrixParamName() { return "viewMatrix" ; }
            static std::string ProjectionMatrixParamName() { return "projectionMatrix" ; }
            static std::string ModelViewMatrixParamName() { return "modelViewMatrix" ; }
            static std::string ViewProjectionMatrixParamName() { return "viewProjectionMatrix" ; }
            static std::string MVPMatrixParamName() { return "mvpMatrix" ; }
            static std::string InverseModelMatrixParamName() { return "inverseModelMatrix" ; }
            static std::string InverseViewMatrixParamName() { return "inverseViewMatrix" ; }
            static std::string InverseProjectionMatrixParamName() { return "inverseProjectionMatrix" ; }
            static std::string InverseModelViewMatrixParamName() { return "inverseModelViewMatrix" ; }
            static std::string InverseViewProjectionMatrixParamName() { return "inverseViewProjectionMatrix" ; }
            static std::string InverseMVPMatrixParamName() { return "inverseMVPMatrix" ; }
            static std::string NormalMatrixParamName() { return "normalMatrix" ; }
            static std::string ModelNormalMatrixParamName() { return "modelNormalMatrix" ; }
            static std::string ModelViewNormalMatrixParamName() { return "modelViewNormalMatrix" ; }
            static std::string ViewportMatrixParamName() { return "viewportMatrix" ; }
            static std::string InverseViewportMatrixParamName() { return "inverseViewportMatrix" ; }
            static std::string AspectRatioParamName() { return "aspectRatio" ; }
            static std::string TimeParamName() { return "time" ; }
            static std::string EyePositionParamName() { return "eyePosition" ; }

            // Lighting uniforms names.
            static std::string AmountDirectionalLightsParamName() { return "amountDirectionalLights" ; }

            static std::string DirectionalLightParamName() { return "dirLights" ; }
            static std::string PointLightParamName() { return "pointLights" ; }
            static std::string SpotLightParamName() { return "spotLights" ; }
            static std::string HemisphereLightParamName() { return "hemiLights" ; }
            static std::string LightColorParamName() { return "color" ; }
            static std::string LightPowerParamName() { return "power" ; }
            static std::string LightGenerateSpecularParamName() { return "generateSpecular" ; }
            static std::string LightDirectionParamName() { return "direction" ; }
    } ;
}

#endif
