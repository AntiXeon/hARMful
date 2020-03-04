#ifndef __HOPE__GL_SHADER_ATTRIBUTE_APPLICATOR__
#define __HOPE__GL_SHADER_ATTRIBUTE_APPLICATOR__

#include <utils/Platform.hpp>

#include <scene/framegraph/shading/ShaderValue.hpp>
#include <GL/glew.h>

namespace Hope::GL {
    /**
     * Apply shader attribute values to the bound shader program.
     */
    class ShaderAttributeApplicator final {
        public :
            /**
             * Apply the shader attribute.
             */
            exported static void ApplyAttribute(
                const GLuint programID,
                const std::shared_ptr<Hope::ShaderAttribute>& attrib
            ) ;

        private:
            /**
             * Get the location of an attribute value in the shader program.
             * @return  false if no error occurred; true otherwise.
             */
            exported static bool LocateAttribute(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderAttribute>& attrib
            ) ;

            /**
             * Apply single Integer value.
             */
            exported static void Integer(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderAttribute>& attrib
            ) ;

            /**
             * Apply IVec2 value.
             */
            exported static void IVec2(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderAttribute>& attrib
            ) ;

            /**
             * Apply IVec3 value.
             */
            exported static void IVec3(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderAttribute>& attrib
            ) ;

            /**
             * Apply IVec4 value.
             */
            exported static void IVec4(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderAttribute>& attrib
            ) ;

            /**
             * Apply single unsigned Integer value.
             */
            exported static void UnsignedInteger(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderAttribute>& attrib
            ) ;

            /**
             * Apply UnsignedIVec2 value.
             */
            exported static void UnsignedIVec2(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderAttribute>& attrib
            ) ;

            /**
             * Apply UnsignedIVec3 value.
             */
            exported static void UnsignedIVec3(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderAttribute>& attrib
            ) ;

            /**
             * Apply UnsignedIVec4 value.
             */
            exported static void UnsignedIVec4(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderAttribute>& attrib
            ) ;

            /**
             * Apply single Floating-point value.
             */
            exported static void Floating(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderAttribute>& attrib
            ) ;

            /**
             * Apply Vec2 value.
             */
            exported static void Vec2(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderAttribute>& attrib
            ) ;

            /**
             * Apply Vec3 value.
             */
            exported static void Vec3(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderAttribute>& attrib
            ) ;

            /**
             * Apply Vec4 value.
             */
            static void Vec4(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderAttribute>& attrib
            ) ;

            /**
             * Apply Mat2 value.
             */
            exported static void Mat2(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderAttribute>& attrib
            ) ;

            /**
             * Apply Mat3 value.
             */
            exported static void Mat3(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderAttribute>& attrib
            ) ;

            /**
             * Apply Vec4 value.
             */
            exported static void Mat4(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderAttribute>& attrib
            ) ;

            /**
             * Apply Sampler2D value.
             */
            exported static void Sampler2D(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderAttribute>& attrib
            ) ;

            /**
             * Apply SamplerCube value.
             */
            exported static void SamplerCube(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderAttribute>& attrib
            ) ;
    } ;
}

#endif
