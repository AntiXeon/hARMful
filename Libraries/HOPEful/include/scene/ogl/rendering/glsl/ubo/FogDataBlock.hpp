#ifndef __HOPE__GL_FOG_DATA_UNIFORM_BUFFER_OBJECT__
#define __HOPE__GL_FOG_DATA_UNIFORM_BUFFER_OBJECT__

#include <utils/Platform.hpp>

#include <scene/common/Color.hpp>
#include <scene/ogl/rendering/glsl/ubo/UniformBufferObject.hpp>
#include <geometry/points/Point4Df.hpp>
#include <algorithm>

namespace Hope::GL {
    /**
     * UBO containing all the fog data that are sent to every shader.
     */
    class FogDataBlock final : public UniformBufferObject {
        private:
            /**
             * The structure of the data that are set in the UBO.
             */
            struct ShaderData {
                std::array<float, Mind::Vector4f::AmountCoords> color ;
                std::array<float, Mind::Vector2f::AmountCoords> min_max ;
            } m_data ;

        public:
            /**
             * Create a new FogDataBlock instance.
             */
            exported FogDataBlock() ;

            /**
             * Set the color value.
             */
            exported void setColor(const Color& color) {
                m_data.color = color.toRGBA() ;
                askForAnUpdate() ;
            }

            /**
             * Set the minimal distance value.
             */
            exported void setMinimalDistance(const float min) {
                m_data.min_max[0] = min ;
                askForAnUpdate() ;
            }

            /**
             * Set the maximal distance value.
             */
            exported void setMaximalDistance(const float max) {
                m_data.min_max[1] = max ;
                askForAnUpdate() ;
            }

        protected:
            /**
             * Get the data of the UBO.
             */
            exported const void* data() const override {
                return static_cast<const void*>(&m_data) ;
            }

            /**
             * Size of the data.
             */
            exported size_t size() const override {
                return sizeof(m_data) ;
            }
    } ;
}

#endif
