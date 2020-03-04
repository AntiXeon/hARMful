#ifndef __HOPE__GL_MATERIAL_LOADER__
#define __HOPE__GL_MATERIAL_LOADER__

#include <utils/Platform.hpp>

#include <scene/components/materials/MaterialComponent.hpp>
#include <scene/ogl/textures/TextureImage2D.hpp>
#include <assimp/scene.h>
#include <filesystem>
#include <memory>

namespace fs = std::filesystem ;

namespace Hope::GL {
    /**
     * Load the right material from the Assimp data.
     */
    class MaterialLoader final {
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
             * Create a Blinn-Phong material.
             * @param   material    Material to convert as a component.
             */
            exported static std::unique_ptr<MaterialComponent> BlinnPhongMaterial(const aiMaterial* material) ;

            /**
             * Create a Blinn-Phong material with a diffuse texture.
             * @param   meshPath    Path of the mesh that is currently loaded.
             *                      It is useful to retreive the absolute path
             *                      to the textures in case it is relative to
             *                      the file.
             * @param   material    Material to convert as a component.
             */
            exported static std::unique_ptr<MaterialComponent> DiffuseMaterial(
                const fs::path& meshPath,
                const aiMaterial* material
            ) ;

            /**
             * Create a Blinn-Phong material with a diffuse texture and a normal
             * map.
             * @param   meshPath    Path of the mesh that is currently loaded.
             *                      It is useful to retreive the absolute path
             *                      to the textures in case it is relative to
             *                      the file.
             * @param   material    Material to convert as a component.
             */
            exported static std::unique_ptr<MaterialComponent> DiffuseNormalMaterial(
                const fs::path& meshPath,
                const aiMaterial* material
            ) ;

            /**
             * Create a Blinn-Phong material with a diffuse texture, a normal
             * and a specular maps.
             * @param   meshPath    Path of the mesh that is currently loaded.
             *                      It is useful to retreive the absolute path
             *                      to the textures in case it is relative to
             *                      the file.
             * @param   material    Material to convert as a component.
             */
            exported static std::unique_ptr<MaterialComponent> DiffuseNormalSpecularMaterial(
                const fs::path& meshPath,
                const aiMaterial* material
            ) ;


            /**
             * Get the texture from an Assimp material.
             */
            exported static std::unique_ptr<TextureImage2D> GetTexture(
                const aiTextureType type,
                const fs::path& meshPath,
                const aiMaterial* material
            ) ;

            /**
             * Get the full path to a texture file.
             */
            exported static std::string GetFullTexturePath(
                const fs::path& meshPath,
                const aiString& assimpPath
            ) ;

            /**
             * Set alpha blending mode on the provided material component.
             */
            exported static void SetAlphaBlendingMaterial(MaterialComponent* material) ;
    } ;
} ;

#endif
