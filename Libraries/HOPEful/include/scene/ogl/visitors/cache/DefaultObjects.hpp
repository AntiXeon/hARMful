#ifndef __HOPE__GL_DEFAULT_OBJECTS__
#define __HOPE__GL_DEFAULT_OBJECTS__

#include <scene/components/materials/PhongMaterialComponent.hpp>

namespace Hope::GL {
    /**
     * Default objects in the scene.
     */
    class DefaultObjects final {
        private:
            /**
             * Default material when trying to render a mesh without material.
             */
            PhongMaterialComponent* m_defaultMaterial ;

        public:
            /**
             * Create an instance of DefaultObjects.
             */
            DefaultObjects() ;

            /**
             * Destruction of the DefaultObjects.
             */
            ~DefaultObjects() ;

            /**
             * Get the default material.
             */
            PhongMaterialComponent* material() const {
                return m_defaultMaterial ;
            }
    } ;
}

#endif
