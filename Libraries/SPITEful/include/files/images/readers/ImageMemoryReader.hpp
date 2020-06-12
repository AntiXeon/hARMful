#ifndef __SPITE__IMAGE_MEMORY_READER__
#define __SPITE__IMAGE_MEMORY_READER__

#include <utils/Platform.hpp>
#include <files/images/readers/ImageReader.hpp>
#include <string>
#include <vector>

namespace Spite {
    /**
     * Dedicated class to red compressed images from memory.
     */
    class ImageMemoryReader final : public ImageReader {
        private:
            /**
             * Buffer containing the bytes to read from.
             */
            const std::vector<unsigned char>* m_buffer = nullptr ;

        public:
            /**
             * Create a new ImageReader to write compressed data in a file.
             * @param   path         Path of the file to read.
             * @param   verticalFlip true to flip vertically; false otherwise.
             */
            exported ImageMemoryReader(
                const std::vector<unsigned char>& buffer,
                const bool verticalFlip = false
            ) ;

            /**
             * Perform read of the file.
             */
            exported RawImage process() ;

            /**
             * Shortcut in a single static method
             */
            exported static RawImage Read(
                const std::vector<unsigned char>& buffer,
                const bool verticalFlip = false
            ) {
                ImageMemoryReader reader(buffer, verticalFlip) ;
                return reader.process() ;
            }

        private:
            /**
             * Buffer raw bytes.
             */
            exported const unsigned char* bufferData() const {
                return (*m_buffer).data() ;
            }

            exported size_t bufferSize() const {
                return (*m_buffer).size() ;
            }

            /**
             * Read images.
             * @return  true on success; false otherwise.
             */
            exported RawImage readImage() ;

            /**
             * Read images with 8-bits per channel.
             * @return  true on success; false otherwise.
             */
            exported RawImage read8BitsChannel() ;

            /**
             * Read images with 16-bits per channel.
             * @return  true on success; false otherwise.
             */
            exported RawImage read16BitsChannel() ;

            /**
             * Read HDR file.
             * @return  true on success; false otherwise.
             */
            exported RawImage readHDR() ;
    } ;
}

#endif
