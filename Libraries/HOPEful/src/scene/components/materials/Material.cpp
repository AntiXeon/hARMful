#include <scene/components/materials/Material.hpp>

using namespace Hope ;

void Material::addShaderParameter(const std::shared_ptr<Hope::ShaderParameter> param) {
    m_shaderParams.insert(param) ;
}

void Material::removeShaderParameter(const std::shared_ptr<Hope::ShaderParameter> param) {
    m_shaderParams.erase(param) ;
}
