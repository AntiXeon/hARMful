#include <scene/ogl/rendering/glsl/ShaderAttributeApplicator.hpp>

using namespace Hope ;
using namespace Hope::GL ;

void ShaderAttributeApplicator::ApplyAttribute(
    const GLuint programID,
    const std::shared_ptr<ShaderAttribute>& attrib
) {
    ShaderUniform::ValueType type = attrib -> type() ;

    switch(type) {
        case ShaderUniform::Boolean:
        case ShaderUniform::Integer:
            Integer(programID, attrib) ;
            return ;
        case ShaderUniform::UInteger:
            UnsignedInteger(programID, attrib) ;
            return ;
        case ShaderUniform::Floating:
            Floating(programID, attrib) ;
            return ;

        case ShaderUniform::BVec2:
        case ShaderUniform::IVec2:
            IVec2(programID, attrib) ;
            return ;
        case ShaderUniform::BVec3:
        case ShaderUniform::IVec3:
            IVec3(programID, attrib) ;
            return ;
        case ShaderUniform::BVec4:
        case ShaderUniform::IVec4:
            IVec4(programID, attrib) ;
            return ;

        case ShaderUniform::UIVec2:
            UnsignedIVec2(programID, attrib) ;
            return ;
        case ShaderUniform::UIVec3:
            UnsignedIVec3(programID, attrib) ;
            return ;
        case ShaderUniform::UIVec4:
            UnsignedIVec4(programID, attrib) ;
            return ;

        case ShaderUniform::Vec2:
            Vec2(programID, attrib) ;
            return ;
        case ShaderUniform::Vec3:
            Vec3(programID, attrib) ;
            return ;
        case ShaderUniform::Vec4:
            Vec4(programID, attrib) ;
            return ;

        case ShaderUniform::Mat2:
            Mat2(programID, attrib) ;
            return ;
        case ShaderUniform::Mat3:
            Mat3(programID, attrib) ;
            return ;
        case ShaderUniform::Mat4:
            Mat4(programID, attrib) ;
            return ;

        case ShaderUniform::Sampler2D:
            Sampler2D(programID, attrib) ;
            return ;
        case ShaderUniform::SamplerCube:
            SamplerCube(programID, attrib) ;
            return ;

        default:
            return ;
    }
}

bool ShaderAttributeApplicator::LocateAttribute(
    GLuint programID,
    const std::string& name,
    int& location
) {
    location = glGetAttribLocation(programID, name.c_str()) ;

    GLenum error = glGetError() ;
    return error == GL_NO_ERROR ;
}

void ShaderAttributeApplicator::Integer(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderAttribute>& attrib
) {
    int attribLocation = -1 ;
    bool success = LocateAttribute(programID, attrib -> name(), attribLocation) ;

    if (success) {
        glVertexAttribI1i(attribLocation, attrib -> integer()) ;
    }
}

void ShaderAttributeApplicator::IVec2(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderAttribute>& attrib
) {
    int attribLocation = -1 ;
    bool success = LocateAttribute(programID, attrib -> name(), attribLocation) ;

    if (success) {
        const int* values = attrib -> ivec2() ;
        glVertexAttribI2i(attribLocation, values[0], values[1]) ;
    }
}

void ShaderAttributeApplicator::IVec3(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderAttribute>& attrib
) {
    int attribLocation = -1 ;
    bool success = LocateAttribute(programID, attrib -> name(), attribLocation) ;

    if (success) {
        const int* values = attrib -> ivec3() ;
        glVertexAttribI3i(attribLocation, values[0], values[1], values[2]) ;
    }
}

void ShaderAttributeApplicator::IVec4(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderAttribute>& attrib
) {
    int attribLocation = -1 ;
    bool success = LocateAttribute(programID, attrib -> name(), attribLocation) ;

    if (success) {
        const int* values = attrib -> ivec4() ;
        glVertexAttribI4i(attribLocation, values[0], values[1], values[2], values[3]) ;
    }
}

void ShaderAttributeApplicator::UnsignedInteger(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderAttribute>& attrib
) {
    int attribLocation = -1 ;
    bool success = LocateAttribute(programID, attrib -> name(), attribLocation) ;

    if (success) {
        glVertexAttribI1ui(attribLocation, attrib -> uinteger()) ;
    }
}

void ShaderAttributeApplicator::UnsignedIVec2(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderAttribute>& attrib
) {
    int attribLocation = -1 ;
    bool success = LocateAttribute(programID, attrib -> name(), attribLocation) ;

    if (success) {
        const unsigned int* values = attrib -> uivec2() ;
        glVertexAttribI2ui(attribLocation, values[0], values[1]) ;
    }
}

void ShaderAttributeApplicator::UnsignedIVec3(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderAttribute>& attrib
) {
    int attribLocation = -1 ;
    bool success = LocateAttribute(programID, attrib -> name(), attribLocation) ;

    if (success) {
        const unsigned int* values = attrib -> uivec3() ;
        glVertexAttribI3ui(attribLocation, values[0], values[1], values[2]) ;
    }
}

void ShaderAttributeApplicator::UnsignedIVec4(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderAttribute>& attrib
) {
    int attribLocation = -1 ;
    bool success = LocateAttribute(programID, attrib -> name(), attribLocation) ;

    if (success) {
        const unsigned int* values = attrib -> uivec4() ;
        glVertexAttribI4ui(attribLocation, values[0], values[1], values[2], values[3]) ;
    }
}

void ShaderAttributeApplicator::Floating(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderAttribute>& attrib
) {
    int attribLocation = -1 ;
    bool success = LocateAttribute(programID, attrib -> name(), attribLocation) ;

    if (success) {
        glVertexAttrib1f(attribLocation, attrib -> floating()) ;
    }
}

void ShaderAttributeApplicator::Vec2(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderAttribute>& attrib
) {
    int attribLocation = -1 ;
    bool success = LocateAttribute(programID, attrib -> name(), attribLocation) ;

    if (success) {
        const float* values = attrib -> vec2() ;
        glVertexAttrib2f(attribLocation, values[0], values[1]) ;
    }
}

void ShaderAttributeApplicator::Vec3(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderAttribute>& attrib
) {
    int attribLocation = -1 ;
    bool success = LocateAttribute(programID, attrib -> name(), attribLocation) ;

    if (success) {
        const float* values = attrib -> vec3() ;
        glVertexAttrib3f(attribLocation, values[0], values[1], values[2]) ;
    }
}

void ShaderAttributeApplicator::Vec4(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderAttribute>& attrib
) {
    int attribLocation = -1 ;
    bool success = LocateAttribute(programID, attrib -> name(), attribLocation) ;

    if (success) {
        const float* values = attrib -> vec4() ;
        glVertexAttrib4f(attribLocation, values[0], values[1], values[2], values[3]) ;
    }
}

void ShaderAttributeApplicator::Mat2(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderAttribute>& attrib
) {
    int attribLocation = -1 ;
    bool success = LocateAttribute(programID, attrib -> name(), attribLocation) ;

    if (success) {
        const float* values = attrib -> mat2() ;
        glVertexAttrib2fv(attribLocation, values) ;
    }
}

void ShaderAttributeApplicator::Mat3(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderAttribute>& attrib
) {
    int attribLocation = -1 ;
    bool success = LocateAttribute(programID, attrib -> name(), attribLocation) ;

    if (success) {
        const float* values = attrib -> mat3() ;
        glVertexAttrib3fv(attribLocation, values) ;
    }
}

void ShaderAttributeApplicator::Mat4(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderAttribute>& attrib
) {
    int attribLocation = -1 ;
    bool success = LocateAttribute(programID, attrib -> name(), attribLocation) ;

    if (success) {
        const float* values = attrib -> mat4() ;
        glVertexAttrib4fv(attribLocation, values) ;
    }
}

void ShaderAttributeApplicator::Sampler2D(
    GLuint /*programID*/,
    const std::shared_ptr<Hope::ShaderAttribute>& /*attrib*/
) {
}

void ShaderAttributeApplicator::SamplerCube(
    GLuint /*programID*/,
    const std::shared_ptr<Hope::ShaderAttribute>& /*attrib*/
) {
}
