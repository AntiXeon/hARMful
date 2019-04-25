#include <scene/ogl/rendering/glsl/ubo/BaseGLSLDataUBO.hpp>

using namespace Hope::GL ;

BaseGLSLDataUBO::BaseGLSLDataUBO(const GLuint bindingPointIndex)
    : UniformBufferObject(bindingPointIndex) {
    glBindBuffer(GL_UNIFORM_BUFFER, bufferID()) ;
    glBufferData(GL_UNIFORM_BUFFER, size(), data(), GL_DYNAMIC_DRAW) ;
    glBindBufferBase(GL_UNIFORM_BUFFER, bindingPointIndex, bufferID()) ;
    glBindBuffer(GL_UNIFORM_BUFFER, 0) ;
}
