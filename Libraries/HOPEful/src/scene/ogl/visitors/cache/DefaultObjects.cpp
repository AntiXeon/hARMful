#include <scene/ogl/visitors/cache/DefaultObjects.hpp>

using namespace Hope::GL ;

DefaultObjects::DefaultObjects() {
    m_defaultMaterial = new PhongMaterialComponent() ;
}

DefaultObjects::~DefaultObjects() {
    delete m_defaultMaterial ;
}
