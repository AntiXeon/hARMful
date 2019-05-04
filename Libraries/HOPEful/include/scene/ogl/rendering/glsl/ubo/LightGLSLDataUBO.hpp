#ifndef __HOPE__GL_LIGHT_DATA_UNIFORM_BUFFER_OBJECT__
#define __HOPE__GL_LIGHT_DATA_UNIFORM_BUFFER_OBJECT__

#include <scene/components/materials/AmountLights.hpp>
#include <scene/components/materials/BlockBindings.hpp>
#include <scene/ogl/rendering/glsl/ubo/UniformBufferObject.hpp>
#include <geometry/points/Point4Df.hpp>
#include <array>

namespace Hope {
    class DirectionalLightComponent ;
    class PointLightComponent ;
}

namespace Hope::GL {
    /**
     * UBO containing all the base data that are sent to every shader (model,
     * view, projection matrices, etc).
     */
    class LightGLSLDataUBO final : public UniformBufferObject {
        private:
            /**
             * Data of a directional light.
             * It takes into account the packing of the GLSL structures.
             */
            struct DirectionalLightData {
                std::array<float, Mind::Vector4f::AmountCoords> direction ;
                std::array<float, Mind::Vector4f::AmountCoords> color_power ;
                std::array<float, Mind::Vector4f::AmountCoords> specular ;
            } ;

            /**
             * Data of a point light.
             * It takes into account the packing of the GLSL structures.
             */
            struct PointLightData {
                std::array<float, Mind::Vector4f::AmountCoords> position ;
                std::array<float, Mind::Vector4f::AmountCoords> color_distance ;
                std::array<float, Mind::Vector4f::AmountCoords> linAtt_quadAtt_power_specular ;
            } ;

            /**
             * The structure of the data that are set in the UBO.
             * It takes into account the packing of the GLSL structures.
             */
            struct ShaderData {
                std::array<DirectionalLightData, MAX_DIRECTIONAL_LIGHTS> dirLights ;
                std::array<PointLightData, MAX_POINT_LIGHTS> pointLights ;
                std::array<int, Mind::Vector4f::AmountCoords> amount_dir_point ;
            } m_data ;

        public:
            /**
             * Create a new BaseGLSLDataUBO instance.
             */
            LightGLSLDataUBO() ;

            /**
             * Set the amount of directional lights.
             */
            void setAmountDirectionalLights(const int count) {
                if (m_data.amount_dir_point[0] != count) {
                    m_data.amount_dir_point[0] = count ;
                    askForAnUpdate() ;
                }
            }

            /**
             * Set the amount of point lights.
             */
            void setAmountPointLights(const int count) {
                if (m_data.amount_dir_point[1] != count) {
                    m_data.amount_dir_point[1] = count ;
                    askForAnUpdate() ;
                }
            }

            /**
             * Set the data for a directional light.
             */
            void setDirectionalLight(
                const uint16_t index,
                DirectionalLightComponent* light
            ) ;

            /**
             * Set the data for a point light.
             */
            void setPointLight(
                const uint16_t index,
                PointLightComponent* light,
                const Mind::Vector4f& worldPosition,
                const Mind::Matrix4x4f& viewMatrix
            ) ;

        protected:
            /**
             * Get the data of the UBO.
             */
            const void* data() const override {
                return static_cast<const void*>(&m_data) ;
            }

            /**
             * Size of the data.
             */
            size_t size() const override {
                return sizeof(m_data) ;
            }
    } ;
}

#endif
