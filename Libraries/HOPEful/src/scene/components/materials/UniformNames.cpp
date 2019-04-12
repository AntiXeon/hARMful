#include <scene/components/materials/UniformNames.hpp>
#include <scene/components/materials/AmountLights.hpp>
#include <utils/StringExt.hpp>

#include <iostream>

using namespace Hope ;

UniformNames::UniformNames() {
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
    m_names.push_back(ModelNormalMatrixParamName()) ;
    m_names.push_back(ModelViewNormalMatrixParamName()) ;
    m_names.push_back(ViewportMatrixParamName()) ;
    m_names.push_back(InverseViewportMatrixParamName()) ;
    m_names.push_back(AspectRatioParamName()) ;
    m_names.push_back(TimeParamName()) ;
    m_names.push_back(EyePositionParamName()) ;

    for (int dirLampIndex = 0 ; dirLampIndex < MAX_DIRECTIONAL_LIGHTS ; ++dirLampIndex) {
        std::string indexString = "[" + Doom::StringExt::ToStringi(dirLampIndex) + "]." ;
        m_names.push_back(DirectionalLightParamName() + indexString + LightAmbientParamName()) ;
        m_names.push_back(DirectionalLightParamName() + indexString + LightDiffuseParamName()) ;
        m_names.push_back(DirectionalLightParamName() + indexString + LightSpecularParamName()) ;
        m_names.push_back(DirectionalLightParamName() + indexString + LightDirectionParamName()) ;
    }
}
