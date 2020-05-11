#ifndef __HOPE__GL_SHADER_UNIFORM_APPLICATOR__
#define __HOPE__GL_SHADER_UNIFORM_APPLICATOR__

#include <HopeAPI.hpp>
#include <utils/Platform.hpp>

#include <scene/framegraph/shading/ShaderValue.hpp>

namespace Hope::GL {
    /**
     * Apply shader uniform values to the bound shader program.
     */
    class ShaderUniformApplicator final {
        public :
            /**
             * Apply the shader parameter.
             */
            exported static void ApplyUniform(
                const GLuint programID,
                Hope::ShaderUniform* uniform
            ) ;

        private:
            /**
             * Get the location of a uniform value in the shader program.
             * @return  false if no error occurred; true otherwise.
             */
            exported static bool LocateUniform(
                GLuint programID,
                Hope::ShaderUniform* uniform
            ) ;

            /**
             * Apply single Integer value.
             */
            exported static void Integer(
                GLuint programID,
                Hope::ShaderUniform* uniform
            ) ;

            /**
             * Apply IVec2 value.
             */
            exported static void IVec2(
                GLuint programID,
                Hope::ShaderUniform* uniform
            ) ;

            /**
             * Apply IVec3 value.
             */
            exported static void IVec3(
                GLuint programID,
                Hope::ShaderUniform* uniform
            ) ;

            /**
             * Apply IVec4 value.
             */
            exported static void IVec4(
                GLuint programID,
                Hope::ShaderUniform* uniform
            ) ;

            /**
             * Apply single unsigned Integer value.
             */
            exported static void UnsignedInteger(
                GLuint programID,
                Hope::ShaderUniform* uniform
            ) ;

            /**
             * Apply UnsignedIVec2 value.
             */
            exported static void UnsignedIVec2(
                GLuint programID,
                Hope::ShaderUniform* uniform
            ) ;

            /**
             * Apply UnsignedIVec3 value.
             */
            exported static void UnsignedIVec3(
                GLuint programID,
                Hope::ShaderUniform* uniform
            ) ;

            /**
             * Apply UnsignedIVec4 value.
             */
            exported static void UnsignedIVec4(
                GLuint programID,
                Hope::ShaderUniform* uniform
            ) ;

            /**
             * Apply single Floating-point value.
             */
            exported static void Floating(
                GLuint programID,
                Hope::ShaderUniform* uniform
            ) ;

            /**
             * Apply Vec2 value.
             */
            exported static void Vec2(
                GLuint programID,
                Hope::ShaderUniform* uniform
            ) ;

            /**
             * Apply Vec3 value.
             */
            exported static void Vec3(
                GLuint programID,
                Hope::ShaderUniform* uniform
            ) ;

            /**
             * Apply Vec4 value.
             */
            exported static void Vec4(
                GLuint programID,
                Hope::ShaderUniform* uniform
            ) ;

            /**
             * Apply Mat2 value.
             */
            exported static void Mat2(
                GLuint programID,
                Hope::ShaderUniform* uniform
            ) ;

            /**
             * Apply Mat3 value.
             */
            exported static void Mat3(
                GLuint programID,
                Hope::ShaderUniform* uniform
            ) ;

            /**
             * Apply Vec4 value.
             */
            exported static void Mat4(
                GLuint programID,
                Hope::ShaderUniform* uniform
            ) ;

            /**
             * Apply Mat2x3 value.
             */
            exported static void Mat2x3(
                GLuint programID,
                Hope::ShaderUniform* uniform
            ) ;

            /**
             * Apply Mat3x2 value.
             */
            exported static void Mat3x2(
                GLuint programID,
                Hope::ShaderUniform* uniform
            ) ;

            /**
             * Apply Vec2x4 value.
             */
            exported static void Mat2x4(
                GLuint programID,
                Hope::ShaderUniform* uniform
            ) ;

            /**
             * Apply Vec4x2 value.
             */
            exported static void Mat4x2(
                GLuint programID,
                Hope::ShaderUniform* uniform
            ) ;

            /**
             * Apply Vec3x4 value.
             */
            exported static void Mat3x4(
                GLuint programID,
                Hope::ShaderUniform* uniform
            ) ;

            /**
             * Apply Vec4x3 value.
             */
            exported static void Mat4x3(
                GLuint programID,
                Hope::ShaderUniform* uniform
            ) ;

            /**
             * Apply Sampler2D value.
             */
            exported static void Sampler2D(
                GLuint programID,
                Hope::ShaderUniform* uniform
            ) ;

            /**
             * Apply SamplerCube value.
             */
            exported static void SamplerCube(
                GLuint programID,
                Hope::ShaderUniform* uniform
            ) ;
    } ;
}

#endif
