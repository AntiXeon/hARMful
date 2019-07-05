#ifndef __HOPE__GL_MATERIAL_LOADER__
#define __HOPE__GL_MATERIAL_LOADER__

#include <assimp/scene.h>
#include <filesystem>

namespace fs = std::filesystem ;

namespace Hope {
    class MaterialComponent ;
}

namespace Hope::GL {
    class TextureImage2D ;

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
            static MaterialComponent* ConvertMaterial(
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
            static MaterialComponent* BlinnPhongMaterial(const aiMaterial* material) ;

            /**
             * Create a Blinn-Phong material with a diffuse texture.
             * @param   meshPath    Path of the mesh that is currently loaded.
             *                      It is useful to retreive the absolute path
             *                      to the textures in case it is relative to
             *                      the file.
             * @param   material    Material to convert as a component.
             */
            static MaterialComponent* DiffuseMaterial(
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
            static MaterialComponent* DiffuseNormalMaterial(
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
            static MaterialComponent* DiffuseNormalSpecularMaterial(
                const fs::path& meshPath,
                const aiMaterial* material
            ) ;


            /**
             * Get the texture from an Assimp material.
             */
            static TextureImage2D* GetTexture(
                const aiTextureType type,
                const fs::path& meshPath,
                const aiMaterial* material
            ) ;

            /**
             * Get the full path to a texture file.
             */
            static std::string GetFullTexturePath(
                const fs::path& meshPath,
                const aiString& assimpPath
            ) ;
    } ;
} ;

#endif
