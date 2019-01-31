#include <scene/ogl/rendering/capabilities/SeamlessCubemap.hpp>

using namespace Hope::GL ;

void SeamlessCubemap::apply() {
    enable(GL_TEXTURE_CUBE_MAP_SEAMLESS) ;
}

void SeamlessCubemap::remove() {
    disable(GL_TEXTURE_CUBE_MAP_SEAMLESS) ;
}
