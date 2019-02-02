#ifndef __HOPE__GL_SHADER_PARAMETER_APPLICATOR__
#define __HOPE__GL_SHADER_PARAMETER_APPLICATOR__

#include <scene/framegraph/shading/ShaderParameter.hpp>
#include <GL/glew.h>

namespace Hope::GL {
    /**
     * Apply shader parameter values to the bound shader program.
     */
    class ShaderParameterApplicator final {
        public :
            /**
             * Apply the shader parameter.
             */
            static void ApplyParameter(
                const GLuint programID,
                const std::shared_ptr<Hope::ShaderParameter>& param
            ) ;

        private:
            /**
             * Apply single Integer value.
             */
            static void Integer(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderParameter>& param
            ) ;

            /**
             * Apply IVec2 value.
             */
            static void IVec2(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderParameter>& param
            ) ;

            /**
             * Apply IVec3 value.
             */
            static void IVec3(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderParameter>& param
            ) ;

            /**
             * Apply IVec4 value.
             */
            static void IVec4(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderParameter>& param
            ) ;

            /**
             * Apply single unsigned Integer value.
             */
            static void UnsignedInteger(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderParameter>& param
            ) ;

            /**
             * Apply UnsignedIVec2 value.
             */
            static void UnsignedIVec2(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderParameter>& param
            ) ;

            /**
             * Apply UnsignedIVec3 value.
             */
            static void UnsignedIVec3(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderParameter>& param
            ) ;

            /**
             * Apply UnsignedIVec4 value.
             */
            static void UnsignedIVec4(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderParameter>& param
            ) ;

            /**
             * Apply single Floating-point value.
             */
            static void Floating(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderParameter>& param
            ) ;

            /**
             * Apply Vec2 value.
             */
            static void Vec2(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderParameter>& param
            ) ;

            /**
             * Apply Vec3 value.
             */
            static void Vec3(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderParameter>& param
            ) ;

            /**
             * Apply Vec4 value.
             */
            static void Vec4(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderParameter>& param
            ) ;

            /**
             * Apply Mat2 value.
             */
            static void Mat2(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderParameter>& param
            ) ;

            /**
             * Apply Mat3 value.
             */
            static void Mat3(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderParameter>& param
            ) ;

            /**
             * Apply Vec4 value.
             */
            static void Mat4(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderParameter>& param
            ) ;

            /**
             * Apply Mat2x3 value.
             */
            static void Mat2x3(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderParameter>& param
            ) ;

            /**
             * Apply Mat3x2 value.
             */
            static void Mat3x2(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderParameter>& param
            ) ;

            /**
             * Apply Vec2x4 value.
             */
            static void Mat2x4(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderParameter>& param
            ) ;

            /**
             * Apply Vec4x2 value.
             */
            static void Mat4x2(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderParameter>& param
            ) ;

            /**
             * Apply Vec3x4 value.
             */
            static void Mat3x4(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderParameter>& param
            ) ;

            /**
             * Apply Vec4x3 value.
             */
            static void Mat4x3(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderParameter>& param
            ) ;

            /**
             * Apply Sampler2D value.
             */
            static void Sampler2D(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderParameter>& param
            ) ;

            /**
             * Apply SamplerCube value.
             */
            static void SamplerCube(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderParameter>& param
            ) ;
    } ;
}

#endif
