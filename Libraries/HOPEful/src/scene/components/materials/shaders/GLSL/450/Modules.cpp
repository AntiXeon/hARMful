// WARNING: This file is automatically generated. Any manual modification will be removed.
#include <scene/components/materials/shaders/GLSL/450/Modules.hpp>

std::string ModulesModelDataBlockModuleCode =
"\
layout (std140, binding = MODEL_DATA_UBO_BINDING_INDEX) uniform ModelData\n\
{\n\
    mat4 modelMatrix ;\n\
    mat4 modelViewMatrix ;\n\
    mat4 mvpMatrix ;\n\
    mat4 inverseModelMatrix ;\n\
    mat4 inverseModelViewMatrix ;\n\
    mat4 inverseMVPMatrix ;\n\
    mat4 normalMatrix ;\n\
    mat4 modelNormalMatrix ;\n\
    mat4 modelViewNormalMatrix ;\n\
} ;\n\
" ;

std::string ModulesBaseDataBlockModuleCode =
"\
layout (std140, binding = BASE_DATA_UBO_BINDING_INDEX) uniform BaseData\n\
{\n\
    mat4 viewMatrix ;\n\
    mat4 projectionMatrix ;\n\
    mat4 viewProjectionMatrix ;\n\
    mat4 inverseViewMatrix ;\n\
    mat4 inverseProjectionMatrix ;\n\
    mat4 inverseViewProjectionMatrix ;\n\
    mat3 viewportMatrix ;\n\
    mat3 inverseViewportMatrix ;\n\
    vec3 eyePosition ;\n\
    float farPlaneDistance ;\n\
    float aspectRatio ;\n\
    float time ;\n\
} ;\n\
" ;

std::string ModulesDirectiveModuleCode =
"\
#version 450 core    // OpenGL 4.5\n\
 layout(row_major) uniform ;\n\
" ;

