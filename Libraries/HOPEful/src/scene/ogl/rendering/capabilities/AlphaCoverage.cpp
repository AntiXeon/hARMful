#include <scene/ogl/rendering/capabilities/AlphaCoverage.hpp>

using namespace Hope::GL ;

void AlphaCoverage::apply() {
    enable(GL_SAMPLE_ALPHA_TO_COVERAGE) ;
}

void AlphaCoverage::remove() {
    disable(GL_SAMPLE_ALPHA_TO_COVERAGE) ;
}
