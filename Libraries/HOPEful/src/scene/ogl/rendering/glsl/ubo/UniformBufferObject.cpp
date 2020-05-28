#include <scene/ogl/rendering/glsl/ubo/UniformBufferObject.hpp>
#include <utils/LogSystem.hpp>
#include <HOPEStrings.hpp>
#include <cstring>

using namespace Hope::GL ;

UniformBufferObject::UniformBufferObject(const GLuint bindingPointIndex) {
    const GLuint MaxBindingIndexCount = static_cast<GLuint>(MaxUniformBufferBindings()) ;
    if (bindingPointIndex < MaxBindingIndexCount) {
        m_bindingPointIndex = bindingPointIndex ;
        glGenBuffers(1, &m_uniformBuffer) ;
    }
    else {
        Doom::LogSystem::Gravity level = Doom::LogSystem::Gravity::Critical ;
        Doom::LogSystem::WriteLine(level, Hope::Texts::UBO_BadBindingIndex) ;
    }
}

UniformBufferObject::~UniformBufferObject() {
    if (glIsBuffer(m_uniformBuffer)) {
        glDeleteBuffers(1, &m_uniformBuffer) ;
    }
}

void UniformBufferObject::update() {
    if (needUpdate()) {
        glBindBuffer(GL_UNIFORM_BUFFER, m_uniformBuffer) ;
        GLvoid* pointer = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY) ;
        memcpy(pointer, data(), size()) ;
        glUnmapBuffer(GL_UNIFORM_BUFFER) ;
        updated() ;
    }
}
