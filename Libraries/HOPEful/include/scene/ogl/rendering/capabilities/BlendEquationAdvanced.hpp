#ifndef __HOPE__GL_CAPABILITY_BLEND_EQUATION_ADVANCED__
#define __HOPE__GL_CAPABILITY_BLEND_EQUATION_ADVANCED__

#include <utils/Platform.hpp>

#include <scene/ogl/rendering/capabilities/Capability.hpp>
#include <scene/common/Color.hpp>
#include <array>

namespace Hope::GL {
    /**
     * Encapsulate the blend equation GL capability.
     */
    class BlendEquationAdvanced final : public Capability {
        public:
            /**
             * Possible blend parameters.
             */
            enum BlendParameter : GLenum {
                Zero =  GL_ZERO,
                One = GL_ONE,
                SourceColor = GL_SRC_COLOR,
                OneMinusSourceColor =  GL_ONE_MINUS_SRC_COLOR,
                DestinationColor = GL_DST_COLOR,
                OneMinusDestinationColor =  GL_ONE_MINUS_DST_COLOR,
                SourceAlpha = GL_SRC_ALPHA,
                OneMinusSourceAlpha = GL_ONE_MINUS_SRC_ALPHA,
                DestinationAlpha = GL_DST_ALPHA,
                OneMineDestinationAlpha = GL_ONE_MINUS_DST_ALPHA,
                ConstantColor = GL_CONSTANT_COLOR,
                OneMinusConstantColor = GL_ONE_MINUS_CONSTANT_COLOR,
                ConstantAlpha = GL_CONSTANT_ALPHA,
                OneMinusConstantAlpha = GL_ONE_MINUS_CONSTANT_ALPHA,
                SourceSaturateAlpha = GL_SRC_ALPHA_SATURATE,
                Source1Color = GL_SRC1_COLOR,
                OneMinusSource1Color = GL_ONE_MINUS_SRC1_COLOR,
                Source1Alpha = GL_SRC1_ALPHA,
                OneMinusSource1Alpha = GL_ONE_MINUS_SRC1_ALPHA
            } ;

            /**
             * Create a new BlendEquationAdvanced instance.
             */
            exported BlendEquationAdvanced() : Capability(CapabilityType::BlendEquationAdvanced) {}

        private:
            static const char RGBIndex = 0 ;
            static const char AlphaIndex = 0 ;
            static const char AmountColorIndices = 2 ;


            struct Parameters {
                /**
                 * To know how the red, green, blue, and alpha source blending
                 * factors are computed.
                 */
                std::array<BlendParameter, AmountColorIndices> source ;

                /**
                 * To know how the red, green, blue, and alpha destination
                 * blending factors are computed.
                 */
                std::array<BlendParameter, AmountColorIndices> destination ;

                bool operator==(const Parameters& other) {
                    return (source == other.source) &&
                            (destination == other.destination) ;
                }

                bool operator!=(const Parameters& other) {
                    return !(*this == other) ;
                }
            } ;


            /**
             * Index of the draw buffer for which to set the blend function.
             */
            GLuint m_bufferIndex ;

            /**
             * Current parameters.
             */
            Parameters m_current = { { One, One }, { Zero, Zero }  } ;

            /**
             * Store old parameters for restore.
             */
            Parameters m_old ;

        public:
            /**
             * Set the buffer index.
             */
            exported void setBufferIndex(const GLuint index) {
                m_bufferIndex = index ;
            }

            /**
             * Set the blend parameter for the RGB channels of the source.
             */
            exported void setSourceRGBParameter(const BlendParameter param) {
                m_current.source[RGBIndex] = param ;
            }

            /**
             * Set the blend parameter for the alpha channel of the source.
             */
            exported void setSourceAlphaParameter(const BlendParameter param) {
                m_current.source[AlphaIndex] = param ;
            }

            /**
             * Set the blend parameter for the RGBA channels of the source.
             */
            exported void setSourceRGBAParameter(const BlendParameter param) {
                setSourceRGBParameter(param) ;
                setSourceAlphaParameter(param) ;
            }

            /**
             * Set the blend parameter for the RGB channels of the destination.
             */
            exported void setDestinationRGBParameter(const BlendParameter param) {
                m_current.destination[RGBIndex] = param ;
            }

            /**
             * Set the blend parameter for the alpha channel of the destination.
             */
            exported void setDestinationAlphaParameter(const BlendParameter param) {
                m_current.destination[AlphaIndex] = param ;
            }

            /**
             * Set the blend parameter for the RGBA channels of the destination.
             */
            exported void setDestinationRGBAParameter(const BlendParameter param) {
                setDestinationRGBParameter(param) ;
                setDestinationAlphaParameter(param) ;
            }

        protected:
            /**
             * Apply the capability.
             */
            void apply() override ;

            /**
             * Remove the capability.
             */
            void remove() override ;

        private:
            /**
             * Store the old source parameters.
             */
            void storeOldSourceParameters() ;

            /**
             * Store the old source parameters.
             */
            void storeOldDestinationParameters() ;
    } ;
}

#endif
