#include <scene/ogl/rendering/glsl/ubo/FogDataBlock.hpp>
#include <scene/components/materials/shaders/GLSL/includes/BlockBindings.hpp>

using namespace Hope::GL ;

FogDataBlock::FogDataBlock()
    : UniformBufferObject(FOG_DATA_UBO_BINDING_INDEX) {
    glBindBuffer(GL_UNIFORM_BUFFER, bufferID()) ;
    glBufferData(GL_UNIFORM_BUFFER, size(), data(), GL_DYNAMIC_DRAW) ;
    glBindBufferBase(GL_UNIFORM_BUFFER, FOG_DATA_UBO_BINDING_INDEX, bufferID()) ;
    glBindBuffer(GL_UNIFORM_BUFFER, 0) ;
}
