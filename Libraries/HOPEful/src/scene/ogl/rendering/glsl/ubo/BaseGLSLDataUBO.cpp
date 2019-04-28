#include <scene/ogl/rendering/glsl/ubo/BaseGLSLDataUBO.hpp>
#include <scene/components/materials/BlockBindings.hpp>

using namespace Hope::GL ;

BaseGLSLDataUBO::BaseGLSLDataUBO()
    : UniformBufferObject(BASE_DATA_UBO_BINDING_INDEX) {
    glBindBuffer(GL_UNIFORM_BUFFER, bufferID()) ;
    glBufferData(GL_UNIFORM_BUFFER, size(), data(), GL_DYNAMIC_DRAW) ;
    glBindBufferBase(GL_UNIFORM_BUFFER, BASE_DATA_UBO_BINDING_INDEX, bufferID()) ;
    glBindBuffer(GL_UNIFORM_BUFFER, 0) ;
}
