#ifndef __HOPE__GL_MATERIAL_LOADER__
#define __HOPE__GL_MATERIAL_LOADER__

#include <utils/Platform.hpp>

#include <scene/components/materials/MaterialComponent.hpp>
#include <scene/components/materials/PBRMaterialComponent.hpp>
#include <scene/ogl/textures/TextureImage2D.hpp>
#include <assimp/scene.h>
#include <filesystem>
#include <list>
#include <memory>

namespace fs = std::filesystem ;

namespace Hope::GL {
    /**
     * Load the right material from the Assimp data.
     */
    class MaterialLoader final {
		private:
			static const std::string TextureFolderName ;
			static const std::list<std::string> TextureExtensions ;

			static const std::string AlbedoFilename ;
			static const std::string AmbientOcclusionFilename ;
			static const std::string EmissiveFilename ;
			static const std::string HeightFilename ;
			static const std::string MetalnessFilename ;
			static const std::string NormalFilename ;
			static const std::string RoughnessFilename ;

        public:
            /**
             * Convert the Assimp material structure to a material component
             * that can be attached to an entity.
             * @param   meshPath    Path of the mesh that is currently loaded.
             *                      It is useful to retreive the absolute path
             *                      to the textures in case it is relative to
             *                      the file.
             * @param   material    Material to convert as a component.
             */
            static std::unique_ptr<MaterialComponent> ConvertMaterial(
                const fs::path& meshPath,
                const aiMaterial* material
            ) ;

            // Copy/move operations.
            MaterialLoader() = delete ;
            MaterialLoader(const MaterialLoader& copied) = delete ;
            MaterialLoader(MaterialLoader&& moved) = delete ;
            MaterialLoader& operator=(const MaterialLoader& copied) = delete ;
            MaterialLoader& operator=(MaterialLoader&& moved) = delete ;

        private:
            /**
             * Load a single value property of the material.
			 * @param 	meshPath			Path to the mesh.
			 * @param 	material			Material structure from Assimp.
			 * @param 	propertyKeyValue	Key value of the property.
			 * @param 	propertyTextureType	Texture type of the property.
             */
            exported static Hope::ValueTexture PropertyValue(
				const fs::path& meshPath,
				const aiMaterial* material,
				const char* pKey,
				const unsigned int type,
				const unsigned int idx,
				const std::string& textureName
			) ;

			/**
             * Load a color value property of the material.
			 * @param 	meshPath			Path to the mesh.
			 * @param 	material			Material structure from Assimp.
			 * @param 	propertyKeyValue	Key value of the property.
			 * @param 	propertyTextureType	Texture type of the property.
             */
			exported static Hope::ColorTexture PropertyColor(
				const fs::path& meshPath,
				const aiMaterial* material,
				const char* pKey,
				const unsigned int type,
				const unsigned int idx,
				const std::string& textureName
			) ;

			/**
			 * A very basic texture loader for PBR materials, as Assimp only
			 * refers to Phong material related textures.
			 * The textures are search into the folder called
			 * "$TextureFolderName" at the same level as the loaded mesh file.
			 * The textures are put into a subfolder sharing the same name as
			 * the loaded mesh file.
			 * Texture files must have the names among the "$xxxFilename" static
			 * properties of the MaterialLoader.
			 * Texture files must have the "$TextureExtensions" extensions.
			 *
			 * For example:
			 * + LoadedMesh.obj
			 * + textures/LoadedMesh/alebdo.jpg
			 * + textures/LoadedMesh/metalness.jpg
			 * + textures/LoadedMesh/roughness.jpg
			 * etc.
			 */
			exported static std::unique_ptr<TextureImage2D> GetTexture(
				const fs::path& meshPath,
				const std::string& textureName
			) ;

            /**
             * Set alpha blending mode on the provided material component.
             */
            exported static void SetAlphaBlendingMaterial(MaterialComponent* material) ;
    } ;
} ;

#endif
