// WARNING: This file is automatically generated. Any manual modification will be removed.
#include <scene/components/materials/shaders/GL/4.5/modules/Lights.hpp>

std::string LightsFragmentCode =
"\
struct DirectionalLight {\n\
    // Direction of the light.\n\
    vec3 direction ;\n\
\n\
    // Color of the light.\n\
    vec3 color ;\n\
\n\
    // Power of the light.\n\
    float power ;\n\
\n\
    // Does the light produce a specular?\n\
    bool generateSpecular ;\n\
} ;\n\
\n\
uniform DirectionalLight dirLights[MAX_DIRECTIONAL_LIGHTS] ;\n\
" ;

