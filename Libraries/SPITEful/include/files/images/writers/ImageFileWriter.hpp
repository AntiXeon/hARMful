#ifndef __SPITE__IMAGE_FILE_WRITER__
#define __SPITE__IMAGE_FILE_WRITER__

#include <utils/Platform.hpp>
#include <files/images/writers/ImageWriter.hpp>
#include <filesystem>
#include <functional>
#include <vector>
#include <map>

namespace fs = std::filesystem ;

namespace Spite {
    /**
     * Dedicated class to store compressed images in files.
     */
    class ImageFileWriter final : public ImageWriter {
        private:
            using Functor = std::function<bool(RawImage&, const std::string&)> ;

            /**
             * Bind extensions to their functor to save file on disk.
             */
            static const std::map<std::string, Functor> ExtensionFileSave ;

            /**
             * Path to the file to save.
             */
            fs::path m_path ;

        public:
            /**
             * Create a new ImageFileWriter to write compressed data in a file.
             * @param   data         Binary data containing raw picture data.
             * @param   path         Path of the file to save to.
             * @param   verticalFlip true to flip vertically; false otherwise.
             */
            exported ImageFileWriter(
                RawImage& data,
                const fs::path& path,
                const bool verticalFlip = false
            ) ;

        private:
            /**
             * Perform save.
             */
            exported bool processSpecific() override ;

            /**
             * Save PNG file.
             * @return  true on success; false otherwise.
             */
            exported static bool SavePNG(
                RawImage& image,
                const std::string& path
            ) ;

            /**
             * Save JPEG file.
             * @return  true on success; false otherwise.
             */
            exported static bool SaveJPEG(
                RawImage& image,
                const std::string& path
            ) ;

            /**
             * Save TGA file.
             * @return  true on success; false otherwise.
             */
            exported static bool SaveTGA(
                RawImage& image,
                const std::string& path
            ) ;

            /**
             * Save BMP file.
             * @return  true on success; false otherwise.
             */
            exported static bool SaveBMP(
                RawImage& image,
                const std::string& path
            ) ;

            /**
             * Save HDR file.
             * @return  true on success; false otherwise.
             */
            exported static bool SaveHDR(
                RawImage& image,
                const std::string& path
            ) ;
    } ;
}

#endif
