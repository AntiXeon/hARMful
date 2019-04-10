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
    const std::shared_ptr<Hope::ShaderAttribute>& attrib
) {
    const char* attribName = (attrib -> name()).c_str() ;
    attrib -> setLocation(glGetAttribLocation(programID, attribName)) ;

    GLenum error = glGetError() ;
    return error == GL_NO_ERROR ;
}

void ShaderAttributeApplicator::Integer(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderAttribute>& attrib
) {
    bool success = true ;
    if (attrib -> location() == -2) {
        success = LocateAttribute(programID, attrib) ;
    }

    if (success) {
        glVertexAttribI1i(attrib -> location(), attrib -> integer()) ;
    }
}

void ShaderAttributeApplicator::IVec2(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderAttribute>& attrib
) {
    bool success = true ;
    if (attrib -> location() == -2) {
        success = LocateAttribute(programID, attrib) ;
    }

    if (success) {
        const int* values = attrib -> ivec2() ;
        glVertexAttribI2i(attrib -> location(), values[0], values[1]) ;
    }
}

void ShaderAttributeApplicator::IVec3(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderAttribute>& attrib
) {
    bool success = true ;
    if (attrib -> location() == -2) {
        success = LocateAttribute(programID, attrib) ;
    }

    if (success) {
        const int* values = attrib -> ivec3() ;
        glVertexAttribI3i(attrib -> location(), values[0], values[1], values[2]) ;
    }
}

void ShaderAttributeApplicator::IVec4(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderAttribute>& attrib
) {
    bool success = true ;
    if (attrib -> location() == -2) {
        success = LocateAttribute(programID, attrib) ;
    }

    if (success) {
        const int* values = attrib -> ivec4() ;
        glVertexAttribI4i(attrib -> location(), values[0], values[1], values[2], values[3]) ;
    }
}

void ShaderAttributeApplicator::UnsignedInteger(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderAttribute>& attrib
) {
    bool success = true ;
    if (attrib -> location() == -2) {
        success = LocateAttribute(programID, attrib) ;
    }

    if (success) {
        glVertexAttribI1ui(attrib -> location(), attrib -> uinteger()) ;
    }
}

void ShaderAttributeApplicator::UnsignedIVec2(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderAttribute>& attrib
) {
    bool success = true ;
    if (attrib -> location() == -2) {
        success = LocateAttribute(programID, attrib) ;
    }

    if (success) {
        const unsigned int* values = attrib -> uivec2() ;
        glVertexAttribI2ui(attrib -> location(), values[0], values[1]) ;
    }
}

void ShaderAttributeApplicator::UnsignedIVec3(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderAttribute>& attrib
) {
    bool success = true ;
    if (attrib -> location() == -2) {
        success = LocateAttribute(programID, attrib) ;
    }

    if (success) {
        const unsigned int* values = attrib -> uivec3() ;
        glVertexAttribI3ui(attrib -> location(), values[0], values[1], values[2]) ;
    }
}

void ShaderAttributeApplicator::UnsignedIVec4(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderAttribute>& attrib
) {
    bool success = true ;
    if (attrib -> location() == -2) {
        success = LocateAttribute(programID, attrib) ;
    }

    if (success) {
        const unsigned int* values = attrib -> uivec4() ;
        glVertexAttribI4ui(attrib -> location(), values[0], values[1], values[2], values[3]) ;
    }
}

void ShaderAttributeApplicator::Floating(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderAttribute>& attrib
) {
    bool success = true ;
    if (attrib -> location() == -2) {
        success = LocateAttribute(programID, attrib) ;
    }

    if (success) {
        glVertexAttrib1f(attrib -> location(), attrib -> floating()) ;
    }
}

void ShaderAttributeApplicator::Vec2(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderAttribute>& attrib
) {
    bool success = true ;
    if (attrib -> location() == -2) {
        success = LocateAttribute(programID, attrib) ;
    }

    if (success) {
        const float* values = attrib -> vec2() ;
        glVertexAttrib2f(attrib -> location(), values[0], values[1]) ;
    }
}

void ShaderAttributeApplicator::Vec3(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderAttribute>& attrib
) {
    bool success = true ;
    if (attrib -> location() == -2) {
        success = LocateAttribute(programID, attrib) ;
    }

    if (success) {
        const float* values = attrib -> vec3() ;
        glVertexAttrib3f(attrib -> location(), values[0], values[1], values[2]) ;
    }
}

void ShaderAttributeApplicator::Vec4(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderAttribute>& attrib
) {
    bool success = true ;
    if (attrib -> location() == -2) {
        success = LocateAttribute(programID, attrib) ;
    }

    if (success) {
        const float* values = attrib -> vec4() ;
        glVertexAttrib4f(attrib -> location(), values[0], values[1], values[2], values[3]) ;
    }
}

void ShaderAttributeApplicator::Mat2(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderAttribute>& attrib
) {
    bool success = true ;
    if (attrib -> location() == -2) {
        success = LocateAttribute(programID, attrib) ;
    }

    if (success) {
        const float* values = attrib -> mat2() ;
        glVertexAttrib2fv(attrib -> location(), values) ;
    }
}

void ShaderAttributeApplicator::Mat3(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderAttribute>& attrib
) {
    bool success = true ;
    if (attrib -> location() == -2) {
        success = LocateAttribute(programID, attrib) ;
    }

    if (success) {
        const float* values = attrib -> mat3() ;
        glVertexAttrib3fv(attrib -> location(), values) ;
    }
}

void ShaderAttributeApplicator::Mat4(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderAttribute>& attrib
) {
    bool success = true ;
    if (attrib -> location() == -2) {
        success = LocateAttribute(programID, attrib) ;
    }

    if (success) {
        const float* values = attrib -> mat4() ;
        glVertexAttrib4fv(attrib -> location(), values) ;
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
