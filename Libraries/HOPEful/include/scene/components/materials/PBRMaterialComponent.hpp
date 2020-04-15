#ifndef __HOPE__PBR_MATERIAL_COMPONENT__
#define __HOPE__PBR_MATERIAL_COMPONENT__

#include <utils/Platform.hpp>

#include <scene/components/materials/MaterialComponent.hpp>
#include <scene/components/materials/ColorTexture.hpp>
#include <scene/components/materials/ValueTexture.hpp>
#include <algorithm>
#include <memory>
#include <string>

namespace Hope {
    /**
     * Physics-based rendering material with several data to compute shaders.
	 * Both textures and colors/values can be mixed for each element of the
	 * material. The material embeds values for albedo, metalness, roughness,
	 * light emission, normal map, etc.
     */
    class PBRMaterialComponent final : public MaterialComponent {
		public:
			/**
			 * Component class type.
			 */
			static const ComponentType ClassType = MaterialComponentType ;

		private:
			/**
			 * Aggregate name and location of uniform.
			 */
			struct UniformNameLocation {
				std::string name ;
				unsigned short location ;
			} ;

			/**
			 * Bindings of the albedo.
			 */
			static const unsigned short AlbedoUseTextureBinding = 0 ;
			static const unsigned short AlbedoVertexValueBinding = 1 ;
			static const unsigned short AlbedoTextureValueBinding = 2 ;

			/**
			 * Bindings of the metalness.
			 */
			static const unsigned short MetalnessUseTextureBinding = 3 ;
			static const unsigned short MetalnessVertexValueBinding = 4 ;
			static const unsigned short MetalnessTextureValueBinding = 5 ;

			/**
			 * Bindings of the emissive.
			 */
			static const unsigned short EmissiveUseTextureBinding = 6 ;
			static const unsigned short EmissiveVertexValueBinding = 7 ;
			static const unsigned short EmissiveTextureValueBinding = 8 ;

			/**
			 * Bindings of the roughness.
			 */
			static const unsigned short RoughnessUseTextureBinding = 9 ;
			static const unsigned short RoughnessVertexValueBinding = 10 ;
			static const unsigned short RoughnessTextureValueBinding = 11 ;

			/**
			 * Bindings of the AO.
			 */
			static const unsigned short AOUseTextureBinding = 12 ;
			static const unsigned short AOVertexValueBinding = 13 ;
			static const unsigned short AOTextureValueBinding = 14 ;

			/**
			 * Bindings of the normal.
			 */
			static const unsigned short NormalUseTextureBinding = 15 ;
			static const unsigned short NormalTextureValueBinding = 16 ;


			/**
			 * Albedo of the material.
			 */
			ColorTexture m_albedo ;

			/**
			 * Metalness of the material.
			 */
			ValueTexture m_metalness ;

			/**
			 * Light emission of the material.
			 */
			ColorTexture m_emissive ;

			/**
			 * Roughness of the material.
			 */
			ValueTexture m_roughness ;

			/**
			 * Ambient occlusion of the material.
			 */
			ValueTexture m_ao ;

			/**
			 * Normal map.
			 */
			std::unique_ptr<API::TextureImage2D> m_normal = nullptr ;

		public:
			/**
			 * Create a PBRMaterialComponent.
			 */
			exported PBRMaterialComponent() ;

			/**
			 * Set the albedo value.
			 */
			exported void setAlbedo(
				const Color& color,
				std::unique_ptr<API::TextureImage2D> texture,
				const float texturePercentage
			) {
				m_albedo.setColor(color) ;
				m_albedo.setTexture(std::move(texture)) ;
				m_albedo.setTexturePercentage(texturePercentage) ;
			}

			/**
			 * Set the metalness value.
			 */
			exported void setMetalness(
				const float value,
				std::unique_ptr<API::TextureImage2D> texture,
				const float texturePercentage
			) {
				m_metalness.setValue(value) ;
				m_metalness.setTexture(std::move(texture)) ;
				m_metalness.setTexturePercentage(texturePercentage) ;
			}

			/**
			 * Set the emissive value.
			 */
			exported void setEmissive(
				const Color& color,
				std::unique_ptr<API::TextureImage2D> texture,
				const float texturePercentage
			) {
				m_emissive.setColor(color) ;
				m_emissive.setTexture(std::move(texture)) ;
				m_emissive.setTexturePercentage(texturePercentage) ;
			}

			/**
			 * Set the roughness value.
			 */
			exported void setRoughness(
				const float value,
				std::unique_ptr<API::TextureImage2D> texture,
				const float texturePercentage
			) {
				m_roughness.setValue(value) ;
				m_roughness.setTexture(std::move(texture)) ;
				m_roughness.setTexturePercentage(texturePercentage) ;
			}

			/**
			 * Set the ambient occlusion value.
			 */
			exported void setAmbientOcclusion(
				const float value,
				std::unique_ptr<API::TextureImage2D> texture,
				const float texturePercentage
			) {
				m_ao.setValue(value) ;
				m_ao.setTexture(std::move(texture)) ;
				m_ao.setTexturePercentage(texturePercentage) ;
			}

			/**
			 * Set the normal map.
			 */
			exported void setNormalMap(std::unique_ptr<API::TextureImage2D> normal) {
				m_normal = std::move(normal) ;
			}

			/**
			 * Update the uniform values before the processing of the material
			 * component.
			 */
			exported void updateUniformValues() override ;

		protected:
			/**
			 * Setup the shader for the forward rendering pass.
			 * Here: does nothing, no forwared rendering supported.
			 */
			exported void setupForwardShader() override {}

			/**
			 * Setup the shader for the deferred rendering pass.
			 */
			exported void setupDeferredShader() override ;

		private:
			/**
			 * Generate the uniforms for one of the values of the material.
			 */
			exported void generateValueUniforms(
				RenderPassID passID,
				const std::array<UniformNameLocation, 3>& namesAndLocations
			) ;

			/**
			 * Set up the uniforms of the current material.
			 */
			exported void setupUniforms() ;

			/**
			 * Bind a value and texture (if any) to the shader of the material.
			 */
			exported void bind(
				const ValueTexture& valueTexture,
				Hope::ShaderUniform* valueUniform,
				const unsigned short textureUnit,
				Hope::ShaderUniform* percentageUniform
			) ;

			/**
			 * Bind a color and texture (if any) to the shader of the material.
			 */
			exported void bind(
				const ColorTexture& valueTexture,
				Hope::ShaderUniform* colorUniform,
				const unsigned short textureUnit,
				Hope::ShaderUniform* percentageUniform
			) ;

			/**
			 * Bind a value to the shader of the material.
			 */
			exported void bind(
				const unsigned short bindingUnit,
				const API::TextureImage2D* texture,
				Hope::ShaderUniform* percentageUniform,
				const float percentage
			) ;
	} ;
}

#endif
