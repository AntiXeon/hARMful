#include <scene/ogl/rendering/capabilities/Dithering.hpp>

using namespace Hope::GL ;

void Dithering::apply() {
    enable(GL_DITHER) ;
}

void Dithering::remove() {
    disable(GL_DITHER) ;
}
