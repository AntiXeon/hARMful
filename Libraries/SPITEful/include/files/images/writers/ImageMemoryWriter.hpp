#ifndef __SPITE__IMAGE_MEMORY_WRITER__
#define __SPITE__IMAGE_MEMORY_WRITER__

#include <utils/Platform.hpp>
#include <files/images/writers/ImageWriter.hpp>
#include <functional>
#include <vector>
#include <map>

namespace Spite {
    /**
     * Dedicated class to store compressed images in memory.
     */
    class ImageMemoryWriter final : public ImageWriter {
        private:
            using Functor = std::function<bool(RawImage&, std::vector<unsigned char>&)> ;

            /**
             * Bind extensions to their functor to store compressed image in
             * memory.
             */
            static const std::map<std::string, Functor> ExtensionMemorySave ;

            /**
             * Memory buffer where the data are saved.
             */
            std::vector<unsigned char> m_buffer ;

        public:
            /**
             * Create a new ImageFileWriter to write compressed data in a file.
             * @param   data         Binary data containing raw picture data.
             * @param   verticalFlip true to flip vertically; false otherwise.
             */
            exported ImageMemoryWriter(
                RawImage& data,
                const bool verticalFlip = false
            ) ;

            /**
             * Get the memory buffer containing the data.
             */
            std::vector<unsigned char>& buffer() ;

        private:
            /**
             * Perform save.
             */
            exported bool processSpecific() override ;

            /**
             * Callback to write bytes in memory buffer.
             * Called several times until the file is totally written.
             * @param   context     Pointer to the memory buffer.
             * @param   data        Bytes of data that have been processed and
             *                      to put into the buffer.
             * @param   size        Size of data.
             */
            exported static void WriteBytesFunc(
                void* context,
                void* data,
                int size
            ) ;

            /**
             * Save PNG file.
             * @return  true on success; false otherwise.
             */
            exported static bool SavePNG(
                RawImage& image,
                std::vector<unsigned char>& buffer
            ) ;

            /**
             * Save JPEG file.
             * @return  true on success; false otherwise.
             */
            exported static bool SaveJPEG(
                RawImage& image,
                std::vector<unsigned char>& buffer
            ) ;

            /**
             * Save TGA file.
             * @return  true on success; false otherwise.
             */
            exported static bool SaveTGA(
                RawImage& image,
                std::vector<unsigned char>& buffer
            ) ;

            /**
             * Save BMP file.
             * @return  true on success; false otherwise.
             */
            exported static bool SaveBMP(
                RawImage& image,
                std::vector<unsigned char>& buffer
            ) ;

            /**
             * Save HDR file.
             * @return  true on success; false otherwise.
             */
            exported static bool SaveHDR(
                RawImage& image,
                std::vector<unsigned char>& buffer
            ) ;
    } ;
}

#endif
