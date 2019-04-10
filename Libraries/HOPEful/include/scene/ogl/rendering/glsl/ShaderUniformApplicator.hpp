#ifndef __HOPE__GL_SHADER_UNIFORM_APPLICATOR__
#define __HOPE__GL_SHADER_UNIFORM_APPLICATOR__

#include <scene/framegraph/shading/ShaderValue.hpp>
#include <GL/glew.h>

namespace Hope::GL {
    /**
     * Apply shader uniform values to the bound shader program.
     */
    class ShaderUniformApplicator final {
        public :
            /**
             * Apply the shader parameter.
             */
            static void ApplyUniform(
                const GLuint programID,
                const std::shared_ptr<Hope::ShaderUniform>& uniform
            ) ;

        private:
            /**
             * Get the location of a uniform value in the shader program.
             * @return  false if no error occurred; true otherwise.
             */
            static bool LocateUniform(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderUniform>& uniform
            ) ;

            /**
             * Apply single Integer value.
             */
            static void Integer(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderUniform>& uniform
            ) ;

            /**
             * Apply IVec2 value.
             */
            static void IVec2(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderUniform>& uniform
            ) ;

            /**
             * Apply IVec3 value.
             */
            static void IVec3(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderUniform>& uniform
            ) ;

            /**
             * Apply IVec4 value.
             */
            static void IVec4(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderUniform>& uniform
            ) ;

            /**
             * Apply single unsigned Integer value.
             */
            static void UnsignedInteger(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderUniform>& uniform
            ) ;

            /**
             * Apply UnsignedIVec2 value.
             */
            static void UnsignedIVec2(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderUniform>& uniform
            ) ;

            /**
             * Apply UnsignedIVec3 value.
             */
            static void UnsignedIVec3(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderUniform>& uniform
            ) ;

            /**
             * Apply UnsignedIVec4 value.
             */
            static void UnsignedIVec4(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderUniform>& uniform
            ) ;

            /**
             * Apply single Floating-point value.
             */
            static void Floating(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderUniform>& uniform
            ) ;

            /**
             * Apply Vec2 value.
             */
            static void Vec2(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderUniform>& uniform
            ) ;

            /**
             * Apply Vec3 value.
             */
            static void Vec3(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderUniform>& uniform
            ) ;

            /**
             * Apply Vec4 value.
             */
            static void Vec4(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderUniform>& uniform
            ) ;

            /**
             * Apply Mat2 value.
             */
            static void Mat2(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderUniform>& uniform
            ) ;

            /**
             * Apply Mat3 value.
             */
            static void Mat3(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderUniform>& uniform
            ) ;

            /**
             * Apply Vec4 value.
             */
            static void Mat4(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderUniform>& uniform
            ) ;

            /**
             * Apply Mat2x3 value.
             */
            static void Mat2x3(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderUniform>& uniform
            ) ;

            /**
             * Apply Mat3x2 value.
             */
            static void Mat3x2(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderUniform>& uniform
            ) ;

            /**
             * Apply Vec2x4 value.
             */
            static void Mat2x4(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderUniform>& uniform
            ) ;

            /**
             * Apply Vec4x2 value.
             */
            static void Mat4x2(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderUniform>& uniform
            ) ;

            /**
             * Apply Vec3x4 value.
             */
            static void Mat3x4(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderUniform>& uniform
            ) ;

            /**
             * Apply Vec4x3 value.
             */
            static void Mat4x3(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderUniform>& uniform
            ) ;

            /**
             * Apply Sampler2D value.
             */
            static void Sampler2D(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderUniform>& uniform
            ) ;

            /**
             * Apply SamplerCube value.
             */
            static void SamplerCube(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderUniform>& uniform
            ) ;
    } ;
}

#endif
