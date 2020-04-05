#include <scene/ogl/rendering/capabilities/DepthClamping.hpp>

using namespace Hope::GL ;

void DepthClamping::apply() {
    enable(GL_DEPTH_CLAMP) ;
}

void DepthClamping::remove() {
    disable(GL_DEPTH_CLAMP) ;
}
