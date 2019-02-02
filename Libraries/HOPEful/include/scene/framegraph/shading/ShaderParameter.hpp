#ifndef __HOPE__SHADER_PARAMETER__
#define __HOPE__SHADER_PARAMETER__

#include <array>
#include <string>
#include <cstdlib>
#include <set>
#include <memory>

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
                UInteger,
                Floating,

                BVec2,
                BVec3,
                BVec4,

                IVec2,
                IVec3,
                IVec4,

                UIVec2,
                UIVec3,
                UIVec4,

                Vec2,
                Vec3,
                Vec4,

                Mat2,
                Mat3,
                Mat4,

                Mat2x3,
                Mat3x2,
                Mat2x4,
                Mat4x2,
                Mat3x4,
                Mat4x3,

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
                unsigned int uinteger ;
                float floating ;

                // Vectors
                bool bvec2[2] ;
                bool bvec3[3] ;
                bool bvec4[4] ;

                int ivec2[2] ;
                int ivec3[3] ;
                int ivec4[4] ;

                unsigned int uivec2[2] ;
                unsigned int uivec3[3] ;
                unsigned int uivec4[4] ;

                float vec2[2] ;
                float vec3[3] ;
                float vec4[4] ;

                // Matrices
                float mat2[4] ;  // 2x2
                float mat3[9] ;  // 3x3
                float mat4[16] ; // 4x4
                float mat2x3[6] ;
                float mat3x2[6] ;
                float mat2x4[8] ;
                float mat4x2[8] ;
                float mat3x4[12] ;
                float mat4x3[12] ;

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
             * Merge two sets.
             * Values from the first set are replaced by the ones in the second
             * set.
             */
            static void merge(
                std::set<std::shared_ptr<Hope::ShaderParameter>>& first,
                const std::set<std::shared_ptr<Hope::ShaderParameter>>& second
            ) ;

            /**
             * Check if two parameters describe the same value.
             * Only compares name and type, the value is not evaluated here.
             */
            bool identical(const std::shared_ptr<Hope::ShaderParameter>& other) ;

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
            void setUInteger(const unsigned int uinteger) {
                m_type = UInteger ;
                m_value.uinteger = uinteger ;
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
            void setUIVec2(const std::array<unsigned int, 2>& uivec2) {
                m_type = UIVec2 ;
                std::copy(
                    std::begin(uivec2),
                    std::end(uivec2),
                    std::begin(m_value.uivec2)
                ) ;
            }

            /**
             * Set the parameter value.
             */
            void setUIVec3(const std::array<unsigned int, 3>& uivec3) {
                m_type = UIVec3 ;
                std::copy(
                    std::begin(uivec3),
                    std::end(uivec3),
                    std::begin(m_value.uivec3)
                ) ;
            }

            /**
             * Set the parameter value.
             */
            void setUIVec4(const std::array<unsigned int, 4>& uivec4) {
                m_type = UIVec4 ;
                std::copy(
                    std::begin(uivec4),
                    std::end(uivec4),
                    std::begin(m_value.uivec4)
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
            void setMat2x3(const std::array<float, 6>& mat) {
                m_type = Mat2x3 ;
                std::copy(
                    std::begin(mat),
                    std::end(mat),
                    std::begin(m_value.mat2x3)
                ) ;
            }

            /**
             * Set the parameter value.
             */
            void setMat3x2(const std::array<float, 6>& mat) {
                m_type = Mat3x2 ;
                std::copy(
                    std::begin(mat),
                    std::end(mat),
                    std::begin(m_value.mat3x2)
                ) ;
            }

            /**
             * Set the parameter value.
             */
            void setMat2x4(const std::array<float, 8>& mat) {
                m_type = Mat2x4 ;
                std::copy(
                    std::begin(mat),
                    std::end(mat),
                    std::begin(m_value.mat2x4)
                ) ;
            }

            /**
             * Set the parameter value.
             */
            void setMat4x2(const std::array<float, 8>& mat) {
                m_type = Mat4x2 ;
                std::copy(
                    std::begin(mat),
                    std::end(mat),
                    std::begin(m_value.mat4x2)
                ) ;
            }

            /**
             * Set the parameter value.
             */
            void setMat3x4(const std::array<float, 12>& mat) {
                m_type = Mat3x4 ;
                std::copy(
                    std::begin(mat),
                    std::end(mat),
                    std::begin(m_value.mat3x4)
                ) ;
            }

            /**
             * Set the parameter value.
             */
            void setMat4x3(const std::array<float, 12>& mat) {
                m_type = Mat4x3 ;
                std::copy(
                    std::begin(mat),
                    std::end(mat),
                    std::begin(m_value.mat4x3)
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
            const std::string& name() const {
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
            unsigned int uinteger() const {
                return m_value.uinteger ;
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
            const unsigned int* uivec2() const {
                return m_value.uivec2 ;
            }

            /**
             * Get the value.
             */
            const unsigned int* uivec3() const {
                return m_value.uivec3 ;
            }

            /**
             * Get the value.
             */
            const unsigned int* uivec4() const {
                return m_value.uivec4 ;
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
            const float* mat2x3() const {
                return m_value.mat2x3 ;
            }

            /**
             * Get the value.
             */
            const float* mat3x2() const {
                return m_value.mat3x2 ;
            }

            /**
             * Get the value.
             */
            const float* mat2x4() const {
                return m_value.mat2x4 ;
            }

            /**
             * Get the value.
             */
            const float* mat4x2() const {
                return m_value.mat4x2 ;
            }

            /**
             * Get the value.
             */
            const float* mat3x4() const {
                return m_value.mat3x4 ;
            }

            /**
             * Get the value.
             */
            const float* mat4x3() const {
                return m_value.mat4x3 ;
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
