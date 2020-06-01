#ifndef __HOPE__GL_ENVIRONMENTMAP_TEXTURE__
#define __HOPE__GL_ENVIRONMENTMAP_TEXTURE__

#include <HopeAPI.hpp>
#include <utils/Platform.hpp>
#include <files/archives/TARData.hpp>
#include <scene/ogl/textures/environment/CubeFaces.hpp>
#include <scene/common/Color.hpp>
#include <scene/ogl/GLDefines.hpp>
#include <files/images/data/RawImage.hpp>
#include <geometry/dimensions/Dimension2Di.hpp>
#include <array>
#include <filesystem>

namespace fs = std::filesystem;

namespace Hope::GL {
    /**
     * An environment map texture is generally used to display sky or a big
     * environment as a texture and illuminate the scene.
     */
    class EnvironmentMapTexture final {
        friend class EnvironmentMap ;

        public:
            /**
             * Extension file of the HDR images.
             */
            static const std::string HDRFileExtension ;

		private:
            /**
             * ID of the texture on GPU side.
             */
            GLuint m_textureID = INVALID_VALUE ;

            /**
             * Dimension of a single face texture.
             */
            Mind::Dimension2Di m_faceDimension ;

            /**
             * To know if mipmapping is enabled for this texture.
             */
            bool m_hasMipmap = false ;

        public:
            /**
             * Generate an empty EnvironmentMapTexture with predefined edge
             * length of cube faces.
             * @param cubeSize  Size of an edge of the cube maps.
             * @param mipmap    true to enable mipmapping; false otherwise.
             */
            exported EnvironmentMapTexture(
                const unsigned int cubeSize,
                const bool mipmap = false
            ) ;

            /**
             * Destruction of the EnvironmentMapTexture.
             */
            exported ~EnvironmentMapTexture() ;

            /**
             * Bind the cubemap texture.
             */
            exported void activate() const {
                glActiveTexture(GL_TEXTURE0) ;
            }

            /**
             * Bind the cubemap texture.
             */
            exported void bind() const {
                glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID) ;
            }

            /**
             * Unbind the cubemap texture.
             */
            exported void unbind() const {
                glBindTexture(GL_TEXTURE_CUBE_MAP, 0) ;
            }

            /**
             * Resize the texture (single face dimensions).
             * @param   size        The new size to apply on a square face.
             */
            exported void resize(const unsigned int size) ;

            /**
             * Get the texture ID.
             */
            exported GLuint id() const {
                return m_textureID ;
            }

            /**
             * Get the width of a single face.
             */
            exported unsigned int faceWidth() const {
                return m_faceDimension.width() ;
            }

            /**
             * Get the height of a single face.
             */
            exported unsigned int faceHeight() const {
                return m_faceDimension.height() ;
            }

            /**
             * Generate mipmap.
             */
            exported void generateMipmap() ;

        private:
            /**
             * Create a EnvironmentMapTexture from a HEM file content.
             * @param hemContent  Archive containing all the files to be
             *                    loaded.
             * @param dirPath     Directory containing all the images of the
             *                    faces.
             * @param autoMipmap  true to generate default mipmaps; false for
             *                    adding them manually.
             * @see EnvironmentMapTexture::addMipmap()
             */
            exported EnvironmentMapTexture(
                Spite::TARData& hemContent,
                const fs::path& path,
                const bool autoMipmap
            ) ;

            /**
             * Add manually a mipmap level to the texture.
             * @param hemContent  Archive containing all the files to be
             *                    loaded.
             * @param dirPath     Directory containing all the images of the
             *                    faces.
             * @param level       Mipmap level that is added.
             */
            exported void addMipmap(
                Spite::TARData& hemContent,
                const fs::path& path,
                const unsigned int level
            ) ;

            /**
             * Generate the texture ID on GPU.
             */
            exported void generateTextureID() ;

            /**
             * Set up the texture.
             */
            exported void setupTexture(const bool autoMipmap = true) ;

            // Remove copy/move operations.
            EnvironmentMapTexture(const EnvironmentMapTexture& copied) = delete ;
            EnvironmentMapTexture(EnvironmentMapTexture&& moved) = delete ;
            EnvironmentMapTexture& operator=(const EnvironmentMapTexture& copied) = delete ;
            EnvironmentMapTexture& operator=(EnvironmentMapTexture&& moved) = delete ;
    } ;
}

#endif
