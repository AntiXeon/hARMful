#include <scene/ogl/rendering/capabilities/AntiAliasing.hpp>

using namespace Hope::GL ;

void AntiAliasing::apply() {
    enable(GL_MULTISAMPLE) ;
}

void AntiAliasing::remove() {
    disable(GL_MULTISAMPLE) ;
}
