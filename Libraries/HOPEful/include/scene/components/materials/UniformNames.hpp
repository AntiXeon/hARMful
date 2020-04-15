#ifndef __HOPE__UNIFORM_NAMES__
#define __HOPE__UNIFORM_NAMES__

#include <utils/Platform.hpp>

#include <string>
#include <vector>

namespace Hope {
    /**
     * List all the uniform names available in a shader program.
     */
    struct UniformNames {
        const int AmbientLocation = 0 ;
        const int DiffuseLocation = 1 ;
        const int SpecularLocation = 2 ;
        const int ShininessLocation = 3 ;

        // Materials uniforms names.
        exported static std::string MaterialCubemapUniformName() { return "cubemap" ; }

        exported static std::string MaterialUseShadowUniformName() { return "useShadow" ; }
        exported static std::string MaterialAmountCascadesUniformName() { return "amountCascades" ; }
        exported static std::string MaterialCascadedSplitsUniformName() { return "cascadedSplits" ; }
        exported static std::string MaterialLightViewProjectionMatricesUniformName() { return "lightViewProjectionMatrices" ; }

        exported static std::string MaterialUseAOUniformName() { return "useSSAO" ; }
        exported static std::string MaterialAONoiseUniformName() { return "noise" ; }
        exported static std::string MaterialAOKernelUniformName() { return "kernel" ; }

		// PBR shading.
		exported static std::string PBRShadingAmbientLightColorUniformName() { return "ambientLightColor" ; }

		// PBR material uniforms names.
		exported static std::string PBRMaterialAlbedoUseTextureUniformName() { return "albedoUseTexture" ; }
		exported static std::string PBRMaterialAlbedoVertexUniformName() { return "albedoVertex" ; }
		exported static std::string PBRMaterialAlbedoTextureUniformName() { return "albedoTexture" ; }

		exported static std::string PBRMaterialMetalnessUseTextureUniformName() { return "metalnessUseTexture" ; }
		exported static std::string PBRMaterialMetalnessVertexUniformName() { return "metalnessVertex" ; }
		exported static std::string PBRMaterialMetalnessTextureUniformName() { return "metalnessTexture" ; }

		exported static std::string PBRMaterialEmissiveUseTextureUniformName() { return "emissiveUseTexture" ; }
		exported static std::string PBRMaterialEmissiveVertexUniformName() { return "emissiveVertex" ; }
		exported static std::string PBRMaterialEmissiveTextureUniformName() { return "emissiveTexture" ; }

		exported static std::string PBRMaterialRoughnessUseTextureUniformName() { return "roughnessUseTexture" ; }
		exported static std::string PBRMaterialRoughnessVertexUniformName() { return "roughnessVertex" ; }
		exported static std::string PBRMaterialRoughnessTextureUniformName() { return "roughnessTexture" ; }

		exported static std::string PBRMaterialAOUseTextureUniformName() { return "aoUseTexture" ; }
		exported static std::string PBRMaterialAOVertexUniformName() { return "aoVertex" ; }
		exported static std::string PBRMaterialAOTextureUniformName() { return "aoTexture" ; }

		exported static std::string PBRMaterialNormalUseTextureUniformName() { return "normalUseTexture" ; }
		exported static std::string PBRMaterialNormalTextureUniformName() { return "normalTexture" ; }

        // Other uniforms.
        exported static std::string MSAAQualityUniformName() { return "msaaQuality" ; }
    } ;
}

#endif
