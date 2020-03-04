#ifndef __HOPE__GL_CAPABILITY_ALPHA_TEST__
#define __HOPE__GL_CAPABILITY_ALPHA_TEST__

#include <utils/Platform.hpp>

#include <scene/ogl/rendering/capabilities/Capability.hpp>

namespace Hope::GL {
    /**
     * Encapsulate the alpha test GL capability.
     */
    class AlphaTest final : public Capability {
        public:
            /**
             * Possible alpha test function to apply.
             */
            enum AlphaFunction : GLenum {
                Never = GL_NEVER,
                Less = GL_LESS,
                Equal = GL_EQUAL,
                LessOrEqual = GL_LEQUAL,
                Greater = GL_GREATER,
                GreaterOrEqual = GL_GEQUAL,
                NotEqual = GL_NOTEQUAL,
                Always = GL_ALWAYS
            } ;

            /**
             * Create a new AlphaTest instance.
             */
            exported AlphaTest() : Capability(CapabilityType::AlphaTest) {}

        private:
            struct Parameters {
                /**
                 * Alpha test function to apply.
                 */
                AlphaFunction function ;

                /**
                 * Reference value for the alpha test function.
                 */
                GLclampf reference ;

                bool operator==(const Parameters& other) {
                   return (function == other.function) &&
                           (reference == other.reference) ;
               }

               bool operator!=(const Parameters& other) {
                   return !(*this == other) ;
               }
            } ;

            /**
             * Alpha test function to apply.
             */
            Parameters m_current = { AlphaFunction::Always, 0.f } ;

            /**
             * Store old parameters for restore.
             */
            Parameters m_old ;

        public:
            /**
             * Set the applied alpha test function.
             */
            exported void setFunction(const AlphaFunction func) {
                m_current.function = func ;
            }

            /**
             * Set the reference value for the alpha test function.
             */
            exported void setReference(const GLclampf ref) {
                m_current.reference = ref ;
            }

        protected:
            /**
             * Apply the capability.
             */
            void apply() override ;

            /**
             * Remove the capability.
             */
            void remove() override ;
    } ;
}

#endif
