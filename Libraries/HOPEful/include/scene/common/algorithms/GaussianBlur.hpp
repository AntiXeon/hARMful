#ifndef __HOPE__GAUSSIAN_BLUR__
#define __HOPE__GAUSSIAN_BLUR__

#include <utils/Platform.hpp>
#include <scene/common/RGB.hpp>
#include <files/images/data/RawImage.hpp>
#include <functional>
#include <vector>

namespace Hope {
    /**
     * Blur an image applying a fast Gaussian blur.
     * Full explanations: http://blog.ivank.net/fastest-gaussian-blur.html
     */
    class GaussianBlur final {
        private:
            /**
             * Original image data.
             */
            std::reference_wrapper<Spite::RawImage> m_original ;

        public:
            /**
             * Create a new GaussianBlur.
             * @param   original    Original image data.
             */
            exported GaussianBlur(Spite::RawImage& original) ;

            /**
             * Process blurring the original image.
             * @return  Blurred image.
             */
            exported Spite::RawImage process(const float radius) ;

        private:
            /**
             * Process blurring the original image.
             */
            exported void processFloat(
                std::vector<unsigned char>& sourceBytes,
                std::vector<unsigned char>& destinationBytes,
                const float radius
            ) ;

            /**
             * Convolution.
             * @param amountBoxes   Amount of boxes for blurring.
             * @return The size of Gauss boxes.
             */
            exported std::vector<float> boxesForGauss(
                const float sigma,
                const int amountBoxes
            ) ;

            /**
             * Box blur.
             * @warning PixelType is found from the original picture format.
             */
            template<typename PixelType>
            exported void boxBlur(
                PixelType* sourceChannels,
                PixelType* destinationChannels,
                const unsigned int channel,
                const float radius
            ) ;

            /**
             * Apply blur in horizontal orientation.
             */
            template<typename PixelType>
            exported void boxBlurHorizontal(
                PixelType* originalChannels,
                PixelType* blurredChannels,
                const unsigned int imageWidth,
                const unsigned int imageHeight,
                const unsigned int channel,
                const float radius
            ) ;

            /**
             * Apply blur in vertical orientation.
             */
            template<typename PixelType>
            exported void boxBlurVertical(
                PixelType* originalChannels,
                PixelType* blurredChannels,
                const unsigned int imageWidth,
                const unsigned int imageHeight,
                const unsigned int channel,
                const float radius
            ) ;
    } ;
}

#endif
