#include <scene/ogl/rendering/glsl/ShaderParameterApplicator.hpp>

using namespace Hope ;
using namespace Hope::GL ;

void ShaderParameterApplicator::ApplyParameter(
    const GLuint programID,
    const std::shared_ptr<ShaderParameter>& param
) {
    ShaderParameter::ValueType type = param -> type() ;

    switch(type) {
        case ShaderParameter::Boolean:
        case ShaderParameter::Integer:
            Integer(programID, param) ;
            return ;
        case ShaderParameter::UInteger:
            UnsignedInteger(programID, param) ;
            return ;
        case ShaderParameter::Floating:
            Floating(programID, param) ;
            return ;

        case ShaderParameter::BVec2:
        case ShaderParameter::IVec2:
            IVec2(programID, param) ;
            return ;
        case ShaderParameter::BVec3:
        case ShaderParameter::IVec3:
            IVec3(programID, param) ;
            return ;
        case ShaderParameter::BVec4:
        case ShaderParameter::IVec4:
            IVec4(programID, param) ;
            return ;

        case ShaderParameter::UIVec2:
            UnsignedIVec2(programID, param) ;
            return ;
        case ShaderParameter::UIVec3:
            UnsignedIVec3(programID, param) ;
            return ;
        case ShaderParameter::UIVec4:
            UnsignedIVec4(programID, param) ;
            return ;

        case ShaderParameter::Vec2:
            Vec2(programID, param) ;
            return ;
        case ShaderParameter::Vec3:
            Vec3(programID, param) ;
            return ;
        case ShaderParameter::Vec4:
            Vec4(programID, param) ;
            return ;

        case ShaderParameter::Mat2:
            Mat2(programID, param) ;
            return ;
        case ShaderParameter::Mat3:
            Mat3(programID, param) ;
            return ;
        case ShaderParameter::Mat4:
            Mat4(programID, param) ;
            return ;

        case ShaderParameter::Mat2x3:
            Mat2x3(programID, param) ;
            return ;
        case ShaderParameter::Mat3x2:
            Mat3x2(programID, param) ;
            return ;
        case ShaderParameter::Mat2x4:
            Mat2x4(programID, param) ;
            return ;
        case ShaderParameter::Mat4x2:
            Mat4x2(programID, param) ;
            return ;
        case ShaderParameter::Mat3x4:
            Mat3x4(programID, param) ;
            return ;
        case ShaderParameter::Mat4x3:
            Mat4x3(programID, param) ;
            return ;

        case ShaderParameter::Sampler2D:
            Sampler2D(programID, param) ;
            return ;
        case ShaderParameter::SamplerCube:
            SamplerCube(programID, param) ;
            return ;

        default:
            return ;
    }
}

bool ShaderParameterApplicator::LocateUniform(
    GLuint programID,
    const std::string& name,
    int& location
) {
    location = glGetUniformLocation(programID, name.c_str()) ;

    GLenum error = glGetError() ;
    return error != GL_NO_ERROR ;
}

void ShaderParameterApplicator::Integer(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderParameter>& param
) {
    int uniformLocation = -1 ;
    bool success = LocateUniform(programID, param -> name(), uniformLocation) ;

    if (success) {
        glUniform1i(uniformLocation, param -> integer()) ;
    }
}

void ShaderParameterApplicator::IVec2(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderParameter>& param
) {
    int uniformLocation = -1 ;
    bool success = LocateUniform(programID, param -> name(), uniformLocation) ;

    if (success) {
        const int* values = param -> ivec2() ;
        glUniform2i(uniformLocation, values[0], values[1]) ;
    }
}

void ShaderParameterApplicator::IVec3(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderParameter>& param
) {
    int uniformLocation = -1 ;
    bool success = LocateUniform(programID, param -> name(), uniformLocation) ;

    if (success) {
        const int* values = param -> ivec3() ;
        glUniform3i(uniformLocation, values[0], values[1], values[2]) ;
    }
}

void ShaderParameterApplicator::IVec4(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderParameter>& param
) {
    int uniformLocation = -1 ;
    bool success = LocateUniform(programID, param -> name(), uniformLocation) ;

    if (success) {
        const int* values = param -> ivec4() ;
        glUniform4i(uniformLocation, values[0], values[1], values[2], values[3]) ;
    }
}

void ShaderParameterApplicator::UnsignedInteger(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderParameter>& param
) {
    int uniformLocation = -1 ;
    bool success = LocateUniform(programID, param -> name(), uniformLocation) ;

    if (success) {
        glUniform1ui(uniformLocation, param -> uinteger()) ;
    }
}

void ShaderParameterApplicator::UnsignedIVec2(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderParameter>& param
) {
    int uniformLocation = -1 ;
    bool success = LocateUniform(programID, param -> name(), uniformLocation) ;

    if (success) {
        const unsigned int* values = param -> uivec2() ;
        glUniform2ui(uniformLocation, values[0], values[1]) ;
    }
}

void ShaderParameterApplicator::UnsignedIVec3(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderParameter>& param
) {
    int uniformLocation = -1 ;
    bool success = LocateUniform(programID, param -> name(), uniformLocation) ;

    if (success) {
        const unsigned int* values = param -> uivec3() ;
        glUniform3ui(uniformLocation, values[0], values[1], values[2]) ;
    }
}

void ShaderParameterApplicator::UnsignedIVec4(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderParameter>& param
) {
    int uniformLocation = -1 ;
    bool success = LocateUniform(programID, param -> name(), uniformLocation) ;

    if (success) {
        const unsigned int* values = param -> uivec4() ;
        glUniform4ui(uniformLocation, values[0], values[1], values[2], values[3]) ;
    }
}

void ShaderParameterApplicator::Floating(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderParameter>& param
) {
    int uniformLocation = -1 ;
    bool success = LocateUniform(programID, param -> name(), uniformLocation) ;

    if (success) {
        glUniform1f(uniformLocation, param -> floating()) ;
    }
}

void ShaderParameterApplicator::Vec2(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderParameter>& param
) {
    int uniformLocation = -1 ;
    bool success = LocateUniform(programID, param -> name(), uniformLocation) ;

    if (success) {
        const float* values = param -> vec2() ;
        glUniform2f(uniformLocation, values[0], values[1]) ;
    }
}

void ShaderParameterApplicator::Vec3(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderParameter>& param
) {
    int uniformLocation = -1 ;
    bool success = LocateUniform(programID, param -> name(), uniformLocation) ;

    if (success) {
        const float* values = param -> vec3() ;
        glUniform3f(uniformLocation, values[0], values[1], values[2]) ;
    }
}

void ShaderParameterApplicator::Vec4(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderParameter>& param
) {
    int uniformLocation = -1 ;
    bool success = LocateUniform(programID, param -> name(), uniformLocation) ;

    if (success) {
        const float* values = param -> vec4() ;
        glUniform4f(uniformLocation, values[0], values[1], values[2], values[3]) ;
    }
}

void ShaderParameterApplicator::Mat2(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderParameter>& param
) {
    int uniformLocation = -1 ;
    bool success = LocateUniform(programID, param -> name(), uniformLocation) ;

    if (success) {
        static const GLsizei AmountUpdatedMatrices = 1 ;
        static const GLboolean Transpose = false ;
        const float* values = param -> mat2() ;
        glUniformMatrix2fv(uniformLocation, AmountUpdatedMatrices, Transpose, values) ;
    }
}

void ShaderParameterApplicator::Mat3(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderParameter>& param
) {
    int uniformLocation = -1 ;
    bool success = LocateUniform(programID, param -> name(), uniformLocation) ;

    if (success) {
        static const GLsizei AmountUpdatedMatrices = 1 ;
        static const GLboolean Transpose = false ;
        const float* values = param -> mat3() ;
        glUniformMatrix3fv(uniformLocation, AmountUpdatedMatrices, Transpose, values) ;
    }
}

void ShaderParameterApplicator::Mat4(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderParameter>& param
) {
    int uniformLocation = -1 ;
    bool success = LocateUniform(programID, param -> name(), uniformLocation) ;

    if (success) {
        static const GLsizei AmountUpdatedMatrices = 1 ;
        static const GLboolean Transpose = false ;
        const float* values = param -> mat4() ;
        glUniformMatrix4fv(uniformLocation, AmountUpdatedMatrices, Transpose, values) ;
    }
}

void ShaderParameterApplicator::Mat2x3(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderParameter>& param
) {
    int uniformLocation = -1 ;
    bool success = LocateUniform(programID, param -> name(), uniformLocation) ;

    if (success) {
        static const GLsizei AmountUpdatedMatrices = 1 ;
        static const GLboolean Transpose = false ;
        const float* values = param -> mat2x3() ;
        glUniformMatrix2x3fv(uniformLocation, AmountUpdatedMatrices, Transpose, values) ;
    }
}

void ShaderParameterApplicator::Mat3x2(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderParameter>& param
) {
    int uniformLocation = -1 ;
    bool success = LocateUniform(programID, param -> name(), uniformLocation) ;

    if (success) {
        static const GLsizei AmountUpdatedMatrices = 1 ;
        static const GLboolean Transpose = false ;
        const float* values = param -> mat3x2() ;
        glUniformMatrix3x2fv(uniformLocation, AmountUpdatedMatrices, Transpose, values) ;
    }
}

void ShaderParameterApplicator::Mat2x4(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderParameter>& param
) {
    int uniformLocation = -1 ;
    bool success = LocateUniform(programID, param -> name(), uniformLocation) ;

    if (success) {
        static const GLsizei AmountUpdatedMatrices = 1 ;
        static const GLboolean Transpose = false ;
        const float* values = param -> mat2x4() ;
        glUniformMatrix2x4fv(uniformLocation, AmountUpdatedMatrices, Transpose, values) ;
    }
}

void ShaderParameterApplicator::Mat4x2(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderParameter>& param
) {
    int uniformLocation = -1 ;
    bool success = LocateUniform(programID, param -> name(), uniformLocation) ;

    if (success) {
        static const GLsizei AmountUpdatedMatrices = 1 ;
        static const GLboolean Transpose = false ;
        const float* values = param -> mat4x2() ;
        glUniformMatrix4x2fv(uniformLocation, AmountUpdatedMatrices, Transpose, values) ;
    }
}

void ShaderParameterApplicator::Mat3x4(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderParameter>& param
) {
    int uniformLocation = -1 ;
    bool success = LocateUniform(programID, param -> name(), uniformLocation) ;

    if (success) {
        static const GLsizei AmountUpdatedMatrices = 1 ;
        static const GLboolean Transpose = false ;
        const float* values = param -> mat3x4() ;
        glUniformMatrix3x4fv(uniformLocation, AmountUpdatedMatrices, Transpose, values) ;
    }
}

void ShaderParameterApplicator::Mat4x3(
    GLuint programID,
    const std::shared_ptr<Hope::ShaderParameter>& param
) {
    int uniformLocation = -1 ;
    bool success = LocateUniform(programID, param -> name(), uniformLocation) ;

    if (success) {
        static const GLsizei AmountUpdatedMatrices = 1 ;
        static const GLboolean Transpose = false ;
        const float* values = param -> mat4x3() ;
        glUniformMatrix4x3fv(uniformLocation, AmountUpdatedMatrices, Transpose, values) ;
    }
}

void ShaderParameterApplicator::Sampler2D(
    GLuint /*programID*/,
    const std::shared_ptr<Hope::ShaderParameter>& /*param*/
) {
}

void ShaderParameterApplicator::SamplerCube(
    GLuint /*programID*/,
    const std::shared_ptr<Hope::ShaderParameter>& /*param*/
) {
}
