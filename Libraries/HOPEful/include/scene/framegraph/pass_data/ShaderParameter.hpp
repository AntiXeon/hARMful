#ifndef __HOPE__SCENE_PARAMETER__
#define __HOPE__SCENE_PARAMETER__

#include <array>
#include <string>
#include <cstdlib>

namespace Hope {
    /**
     * A class for parameters sended to shaders.
     */
    class ShaderParameter final {
        public:
            /**
             * Type of the parameter value.
             */
            enum ValueType : char {
                None,

                Boolean,
                Integer,
                Floating,

                BVec2,
                BVec3,
                BVec4,

                IVec2,
                IVec3,
                IVec4,

                Vec2,
                Vec3,
                Vec4,

                Mat2,
                Mat3,
                Mat4,

                Sampler2D,
                SamplerCube
            } ;

        private:
            /**
             * Union representing all the types of data the parameter can embed.
             */
            union ValueUnion {
                // Base types
                bool boolean ;
                int integer ;
                float floating ;

                // Vectors
                bool bvec2[2] ;
                bool bvec3[3] ;
                bool bvec4[4] ;

                int ivec2[2] ;
                int ivec3[3] ;
                int ivec4[4] ;

                float vec2[2] ;
                float vec3[3] ;
                float vec4[4] ;

                // Matrices
                float mat2[4] ;  // 2x2
                float mat3[9] ;  // 3x3
                float mat4[16] ; // 4x4

                // Textures
                int sampler2D ;  // 2D texture
                int samplerCube ;// 3D texture
            } ;

            /**
             * Name of the parameter.
             */
            std::string m_name ;

            /**
             * Type of the parameter value.
             */
            ValueType m_type = None ;

            /**
             * Value of the parameter.
             */
            ValueUnion m_value ;

        public:
            /**
             * Set the parameter name.
             */
            void setName(const std::string& name) {
                m_name = name ;
            }

            /**
             * Set the parameter value.
             */
            void setBoolean(const bool boolean) {
                m_type = Boolean ;
                m_value.boolean = boolean ;
            }

            /**
             * Set the parameter value.
             */
            void setInteger(const int integer) {
                m_type = Integer ;
                m_value.integer = integer ;
            }

            /**
             * Set the parameter value.
             */
            void setFloating(const float floating) {
                m_type = Floating ;
                m_value.floating = floating ;
            }

            /**
             * Set the parameter value.
             */
            void setBVec2(const std::array<bool, 2>& bvec2) {
                m_type = BVec2 ;
                std::copy(
                    std::begin(bvec2),
                    std::end(bvec2),
                    std::begin(m_value.bvec2)
                ) ;
            }

            /**
             * Set the parameter value.
             */
            void setBVec3(const std::array<bool, 3>& bvec3) {
                m_type = BVec3 ;
                std::copy(
                    std::begin(bvec3),
                    std::end(bvec3),
                    std::begin(m_value.bvec3)
                ) ;
            }

            /**
             * Set the parameter value.
             */
            void setBVec4(const std::array<bool, 4>& bvec4) {
                m_type = BVec4 ;
                std::copy(
                    std::begin(bvec4),
                    std::end(bvec4),
                    std::begin(m_value.bvec4)
                ) ;
            }

            /**
             * Set the parameter value.
             */
            void setIVec2(const std::array<int, 2>& ivec2) {
                m_type = IVec2 ;
                std::copy(
                    std::begin(ivec2),
                    std::end(ivec2),
                    std::begin(m_value.ivec2)
                ) ;
            }

            /**
             * Set the parameter value.
             */
            void setIVec3(const std::array<int, 3>& ivec3) {
                m_type = IVec3 ;
                std::copy(
                    std::begin(ivec3),
                    std::end(ivec3),
                    std::begin(m_value.ivec3)
                ) ;
            }

            /**
             * Set the parameter value.
             */
            void setIVec4(const std::array<int, 4>& ivec4) {
                m_type = IVec4 ;
                std::copy(
                    std::begin(ivec4),
                    std::end(ivec4),
                    std::begin(m_value.ivec4)
                ) ;
            }

            /**
             * Set the parameter value.
             */
            void setVec2(const std::array<float, 2>& vec2) {
                m_type = Vec2 ;
                std::copy(
                    std::begin(vec2),
                    std::end(vec2),
                    std::begin(m_value.vec2)
                ) ;
            }

            /**
             * Set the parameter value.
             */
            void setVec3(const std::array<float, 3>& vec3) {
                m_type = Vec3 ;
                std::copy(
                    std::begin(vec3),
                    std::end(vec3),
                    std::begin(m_value.vec3)
                ) ;
            }

            /**
             * Set the parameter value.
             */
            void setVec4(const std::array<float, 4>& vec4) {
                m_type = Vec4 ;
                std::copy(
                    std::begin(vec4),
                    std::end(vec4),
                    std::begin(m_value.vec4)
                ) ;
            }

            /**
             * Set the parameter value.
             */
            void setMat2(const std::array<float, 4>& mat2) {
                m_type = Mat2 ;
                std::copy(
                    std::begin(mat2),
                    std::end(mat2),
                    std::begin(m_value.mat2)
                ) ;
            }

            /**
             * Set the parameter value.
             */
            void setMat3(const std::array<float, 9>& mat3) {
                m_type = Mat3 ;
                std::copy(
                    std::begin(mat3),
                    std::end(mat3),
                    std::begin(m_value.mat3)
                ) ;
            }

            /**
             * Set the parameter value.
             */
            void setMat4(const std::array<float, 16>& mat4) {
                m_type = Mat4 ;
                std::copy(
                    std::begin(mat4),
                    std::end(mat4),
                    std::begin(m_value.mat4)
                ) ;
            }

            /**
             * Set the parameter value.
             */
            void setSampler2D(const int sampler2D) {
                m_type = Sampler2D ;
                m_value.sampler2D = sampler2D ;
            }

            /**
             * Set the parameter value.
             */
            void setSamplerCube(const int samplerCube) {
                m_type = SamplerCube ;
                m_value.samplerCube = samplerCube ;
            }

            /**
             * Get the name of the parameter.
             */
            std::string name() const {
                return m_name ;
            }

            /**
             * Type of the parameter.
             */
            ValueType type() const {
                return m_type ;
            }

            /**
             * Get the value.
             */
            bool boolean() const {
                return m_value.boolean ;
            }

            /**
             * Get the value.
             */
            int integer() const {
                return m_value.integer ;
            }

            /**
             * Get the value.
             */
            float floating() const {
                return m_value.floating ;
            }

            /**
             * Get the value.
             */
            const bool* bvec2() const {
                return m_value.bvec2 ;
            }

            /**
             * Get the value.
             */
            const bool* bvec3() const {
                return m_value.bvec3 ;
            }

            /**
             * Get the value.
             */
            const bool* bvec4() const {
                return m_value.bvec4 ;
            }

            /**
             * Get the value.
             */
            const int* ivec2() const {
                return m_value.ivec2 ;
            }

            /**
             * Get the value.
             */
            const int* ivec3() const {
                return m_value.ivec3 ;
            }

            /**
             * Get the value.
             */
            const int* ivec4() const {
                return m_value.ivec4 ;
            }

            /**
             * Get the value.
             */
            const float* vec2() const {
                return m_value.vec2 ;
            }

            /**
             * Get the value.
             */
            const float* vec3() const {
                return m_value.vec3 ;
            }

            /**
             * Get the value.
             */
            const float* vec4() const {
                return m_value.vec4 ;
            }

            /**
             * Get the value.
             */
            const float* mat2() const {
                return m_value.mat2 ;
            }

            /**
             * Get the value.
             */
            const float* mat3() const {
                return m_value.mat3 ;
            }

            /**
             * Get the value.
             */
            const float* mat4() const {
                return m_value.mat4 ;
            }

            /**
             * Get the value.
             */
            int sampler2D() const {
                return m_value.sampler2D ;
            }

            /**
             * Get the value.
             */
            int samplerCube() const {
                return m_value.samplerCube ;
            }
    } ;
}

#endif
