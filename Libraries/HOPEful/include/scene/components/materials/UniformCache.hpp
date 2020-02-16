#ifndef __HOPE__MATERIAL_UNIFORM_CACHE__
#define __HOPE__MATERIAL_UNIFORM_CACHE__

#include <scene/framegraph/shading/ShaderValue.hpp>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace Hope {
    /**
     * Cache for uniforms of materials.
     */
    class UniformCache final {
        private:
            /**
             * List of shader uniforms.
             */
            std::map<std::string, std::unique_ptr<Hope::ShaderUniform>> m_named ;

            /**
             * Cache of uniform pointers for sharing without ownership.
             */
            std::vector<Hope::ShaderUniform*> m_pointers ;

        public:
            /**
             * Add a shader uniform value.
             * It is sent to the shader as a uniform value.
             * Some usual values are already sent to the shaders.
             */
            void add(std::unique_ptr<Hope::ShaderUniform> uniform) {
                m_pointers.push_back(uniform.get()) ;
                m_named.insert(std::make_pair(uniform -> name(), std::move(uniform))) ;
            }

            /**
             * Get the uniform pointers for sharing without ownership.
             */
            const std::vector<Hope::ShaderUniform*>& pointers() const {
                return m_pointers ;
            }

            /**
             * Get a uniform from its name.
             */
            Hope::ShaderUniform* at(const std::string& name) {
                if (m_named.count(name) == 1) {
                    return m_named[name].get() ;
                }

                return nullptr ;
            }
    } ;
}

#endif
