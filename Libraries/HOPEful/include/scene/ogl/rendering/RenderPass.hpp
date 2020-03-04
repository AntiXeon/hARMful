#ifndef __HOPE__GL_RENDER_PASS__
#define __HOPE__GL_RENDER_PASS__

#include <scene/SceneTypes.hpp>
#include <scene/framegraph/shading/FilterOption.hpp>
#include <scene/ogl/rendering/glsl/ShaderProgram.hpp>
#include <scene/ogl/rendering/capabilities/Capability.hpp>
#include <map>
#include <memory>
#include <set>
#include <vector>

namespace Hope::GL {
    /**
     * Represents a shader program execution as a single render pass.
     */
    class RenderPass final {
        private:
            /**
             * For direct access to capabilities pointers.
             */
            struct CapabilityIndex {
                unsigned int index ;
                std::unique_ptr<Capability> capability ;
            } ;

            /**
             * ID of the pass.
             */
            RenderPassID m_id = ForwardPassID ;

            /**
             * List of the options.
             */
            std::set<std::shared_ptr<Hope::FilterOption>> m_options ;

            /**
             * List of graphics API capabilities.
             */
            std::map<CapabilityType, CapabilityIndex> m_capabilities ;

            /**
             * Cache pointers on capabilities for easy sharing without
             * ownership.
             */
            std::vector<Capability*> m_capabilitiesPointers ;

            /**
             * The shader program that is executed in the current render pass.
             */
            std::unique_ptr<ShaderProgram> m_shaderProgram ;

        public:
            /**
             * Create a render pass.
             */
            RenderPass(const Hope::RenderPassID id = ForwardPassID) ;

            /**
             * Add a filter option.
             * If a FilterOption is set in the framegraph branch and that at
             * least one of them matches in the current render pass, the entity
             * may be rendered. If no option matches in the current render pass,
             * the entity cannot be rendered (neither its children).
             *
             * If there is a FilterOption in the framegraph but no one in the
             * current render pass, the entity is discarded from rendering (and
             * its children as well).
             */
            void addFilterOption(const std::shared_ptr<Hope::FilterOption> option) ;

            /**
             * Remove a filter option.
             */
            void removeFilterOption(const std::shared_ptr<Hope::FilterOption> option) ;

            /**
             * Get the filter options.
             */
            std::set<std::shared_ptr<Hope::FilterOption>> filterOptions() const {
                return m_options ;
            }

            /**
             * Add a graphics API capability.
             * @return  true if the Capability can be added; false if a
             *          Capability of same type is already in use.
             */
            bool addCapability(std::unique_ptr<Capability> capability) ;

            /**
             * Remove a graphics API capability.
             */
            void removeCapability(const CapabilityType type) ;

            /**
             * Get the capability of wanted type.
             */
            const Capability* capability(const CapabilityType type) const ;

            /**
             * Get the capabilities of the current render pass.
             */
            const std::vector<Capability*>& capabilities() const {
                return m_capabilitiesPointers ;
            }

            /**
             * Get the shader program.
             */
            ShaderProgram* shaderProgram() const {
                return m_shaderProgram.get() ;
            }

            /**
             * Get the render pass ID.
             */
            Hope::RenderPassID id() const {
                return m_id ;
            }
    } ;
}

#endif
