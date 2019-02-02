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

void ShaderParameterApplicator::Integer(
    GLuint /*programID*/,
    const std::shared_ptr<Hope::ShaderParameter>& /*param*/
) {
}

void ShaderParameterApplicator::IVec2(
    GLuint /*programID*/,
    const std::shared_ptr<Hope::ShaderParameter>& /*param*/
) {
}

void ShaderParameterApplicator::IVec3(
    GLuint /*programID*/,
    const std::shared_ptr<Hope::ShaderParameter>& /*param*/
) {
}

void ShaderParameterApplicator::IVec4(
    GLuint /*programID*/,
    const std::shared_ptr<Hope::ShaderParameter>& /*param*/
) {
}

void ShaderParameterApplicator::UnsignedInteger(
    GLuint /*programID*/,
    const std::shared_ptr<Hope::ShaderParameter>& /*param*/
) {
}

void ShaderParameterApplicator::UnsignedIVec2(
    GLuint /*programID*/,
    const std::shared_ptr<Hope::ShaderParameter>& /*param*/
) {
}

void ShaderParameterApplicator::UnsignedIVec3(
    GLuint /*programID*/,
    const std::shared_ptr<Hope::ShaderParameter>& /*param*/
) {
}

void ShaderParameterApplicator::UnsignedIVec4(
    GLuint /*programID*/,
    const std::shared_ptr<Hope::ShaderParameter>& /*param*/
) {
}

void ShaderParameterApplicator::Floating(
    GLuint /*programID*/,
    const std::shared_ptr<Hope::ShaderParameter>& /*param*/
) {
}

void ShaderParameterApplicator::Vec2(
    GLuint /*programID*/,
    const std::shared_ptr<Hope::ShaderParameter>& /*param*/
) {
}

void ShaderParameterApplicator::Vec3(
    GLuint /*programID*/,
    const std::shared_ptr<Hope::ShaderParameter>& /*param*/
) {
}

void ShaderParameterApplicator::Vec4(
    GLuint /*programID*/,
    const std::shared_ptr<Hope::ShaderParameter>& /*param*/
) {
}

void ShaderParameterApplicator::Mat2(
    GLuint /*programID*/,
    const std::shared_ptr<Hope::ShaderParameter>& /*param*/
) {
}

void ShaderParameterApplicator::Mat3(
    GLuint /*programID*/,
    const std::shared_ptr<Hope::ShaderParameter>& /*param*/
) {
}

void ShaderParameterApplicator::Mat4(
    GLuint /*programID*/,
    const std::shared_ptr<Hope::ShaderParameter>& /*param*/
) {
}

void ShaderParameterApplicator::Mat2x3(
    GLuint /*programID*/,
    const std::shared_ptr<Hope::ShaderParameter>& /*param*/
) {
}

void ShaderParameterApplicator::Mat3x2(
    GLuint /*programID*/,
    const std::shared_ptr<Hope::ShaderParameter>& /*param*/
) {
}

void ShaderParameterApplicator::Mat2x4(
    GLuint /*programID*/,
    const std::shared_ptr<Hope::ShaderParameter>& /*param*/
) {
}

void ShaderParameterApplicator::Mat4x2(
    GLuint /*programID*/,
    const std::shared_ptr<Hope::ShaderParameter>& /*param*/
) {
}

void ShaderParameterApplicator::Mat3x4(
    GLuint /*programID*/,
    const std::shared_ptr<Hope::ShaderParameter>& /*param*/
) {
}

void ShaderParameterApplicator::Mat4x3(
    GLuint /*programID*/,
    const std::shared_ptr<Hope::ShaderParameter>& /*param*/
) {
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
