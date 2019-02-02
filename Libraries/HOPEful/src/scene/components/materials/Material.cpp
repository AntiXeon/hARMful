#include <scene/components/materials/Material.hpp>
#include <interfaces/visitors/scenegraph/ISceneGraphVisitor.hpp>

using namespace Hope ;

Material::Material()
    : Component(Hope::MaterialComponentType) {}

void Material::accept(ISceneGraphVisitor* visitor) {
    visitor -> visit(this) ;
}

bool Material::isShareable() const {
    return true ;
}

const RenderEffect* Material::effect() const {
    return &m_effect ;
}

void Material::addShaderParameter(const std::shared_ptr<Hope::ShaderParameter> param) {
    m_shaderParams.insert(param) ;
}

void Material::removeShaderParameter(const std::shared_ptr<Hope::ShaderParameter> param) {
    m_shaderParams.erase(param) ;
}
