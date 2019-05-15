#include <scene/components/materials/UniformNames.hpp>
#include <scene/components/materials/shaders/GLSL/includes/AmountLights.hpp>
#include <utils/StringExt.hpp>

using namespace Hope ;

UniformNames::UniformNames() {
    // Generic matrices and values.
    m_names.push_back(ModelMatrixParamName()) ;
    m_names.push_back(ViewMatrixParamName()) ;
    m_names.push_back(ProjectionMatrixParamName()) ;
    m_names.push_back(ModelViewMatrixParamName()) ;
    m_names.push_back(ViewProjectionMatrixParamName()) ;
    m_names.push_back(MVPMatrixParamName()) ;
    m_names.push_back(InverseModelMatrixParamName()) ;
    m_names.push_back(InverseViewMatrixParamName()) ;
    m_names.push_back(InverseProjectionMatrixParamName()) ;
    m_names.push_back(InverseModelViewMatrixParamName()) ;
    m_names.push_back(InverseViewProjectionMatrixParamName()) ;
    m_names.push_back(InverseMVPMatrixParamName()) ;
    m_names.push_back(NormalMatrixParamName()) ;
    m_names.push_back(ModelNormalMatrixParamName()) ;
    m_names.push_back(ModelViewNormalMatrixParamName()) ;
    m_names.push_back(ViewportMatrixParamName()) ;
    m_names.push_back(InverseViewportMatrixParamName()) ;
    m_names.push_back(AspectRatioParamName()) ;
    m_names.push_back(TimeParamName()) ;
    m_names.push_back(EyePositionParamName()) ;

    // Lights.
    m_names.push_back(AmountDirectionalLightsParamName()) ;

    for (int dirLampIndex = 0 ; dirLampIndex < MAX_DIRECTIONAL_LIGHTS ; ++dirLampIndex) {
        std::string indexString = "[" + Doom::StringExt::ToStringi(dirLampIndex) + "]." ;
        m_names.push_back(DirectionalLightParamName() + indexString + LightColorParamName()) ;
        m_names.push_back(DirectionalLightParamName() + indexString + LightPowerParamName()) ;
        m_names.push_back(DirectionalLightParamName() + indexString + LightGenerateSpecularParamName()) ;
        m_names.push_back(DirectionalLightParamName() + indexString + LightDirectionParamName()) ;
    }

    m_names.push_back(AmountPointLightsParamName()) ;

    for (int pointLampIndex = 0 ; pointLampIndex < MAX_POINT_LIGHTS ; ++pointLampIndex) {
        std::string indexString = "[" + Doom::StringExt::ToStringi(pointLampIndex) + "]." ;
        m_names.push_back(PointLightParamName() + indexString + LightColorParamName()) ;
        m_names.push_back(PointLightParamName() + indexString + LightPowerParamName()) ;
        m_names.push_back(PointLightParamName() + indexString + LightGenerateSpecularParamName()) ;
        m_names.push_back(PointLightParamName() + indexString + LightFalloffDistanceParamName()) ;
        m_names.push_back(PointLightParamName() + indexString + LightPositionParamName()) ;
        m_names.push_back(PointLightParamName() + indexString + LightLinearAttenuationParamName()) ;
        m_names.push_back(PointLightParamName() + indexString + LightQuadraticAttenuationParamName()) ;
    }

    m_names.push_back(MaterialNormalUniformName()) ;
    m_names.push_back(MaterialAmbientUniformName()) ;
    m_names.push_back(MaterialDiffuseUniformName()) ;
    m_names.push_back(MaterialSpecularUniformName()) ;
    m_names.push_back(MaterialShininessUniformName()) ;
    m_names.push_back(MaterialCubemapUniformName()) ;
}
