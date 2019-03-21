#ifndef __HOPE__GL_SHADER_ATTRIBUTE_APPLICATOR__
#define __HOPE__GL_SHADER_ATTRIBUTE_APPLICATOR__

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
            static void ApplyAttribute(
                const GLuint programID,
                const std::shared_ptr<Hope::ShaderAttribute>& attrib
            ) ;

        private:
            /**
             * Get the location of an attribute value in the shader program.
             * @return  false if no error occurred; true otherwise.
             */
            static bool LocateAttribute(
                GLuint programID,
                const std::string& name,
                int& location
            ) ;

            /**
             * Apply single Integer value.
             */
            static void Integer(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderAttribute>& attrib
            ) ;

            /**
             * Apply IVec2 value.
             */
            static void IVec2(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderAttribute>& attrib
            ) ;

            /**
             * Apply IVec3 value.
             */
            static void IVec3(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderAttribute>& attrib
            ) ;

            /**
             * Apply IVec4 value.
             */
            static void IVec4(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderAttribute>& attrib
            ) ;

            /**
             * Apply single unsigned Integer value.
             */
            static void UnsignedInteger(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderAttribute>& attrib
            ) ;

            /**
             * Apply UnsignedIVec2 value.
             */
            static void UnsignedIVec2(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderAttribute>& attrib
            ) ;

            /**
             * Apply UnsignedIVec3 value.
             */
            static void UnsignedIVec3(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderAttribute>& attrib
            ) ;

            /**
             * Apply UnsignedIVec4 value.
             */
            static void UnsignedIVec4(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderAttribute>& attrib
            ) ;

            /**
             * Apply single Floating-point value.
             */
            static void Floating(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderAttribute>& attrib
            ) ;

            /**
             * Apply Vec2 value.
             */
            static void Vec2(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderAttribute>& attrib
            ) ;

            /**
             * Apply Vec3 value.
             */
            static void Vec3(
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
            static void Mat2(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderAttribute>& attrib
            ) ;

            /**
             * Apply Mat3 value.
             */
            static void Mat3(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderAttribute>& attrib
            ) ;

            /**
             * Apply Vec4 value.
             */
            static void Mat4(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderAttribute>& attrib
            ) ;

            /**
             * Apply Sampler2D value.
             */
            static void Sampler2D(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderAttribute>& attrib
            ) ;

            /**
             * Apply SamplerCube value.
             */
            static void SamplerCube(
                GLuint programID,
                const std::shared_ptr<Hope::ShaderAttribute>& attrib
            ) ;
    } ;
}

#endif
