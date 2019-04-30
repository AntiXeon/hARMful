#ifndef __HOPE__GL_RENDERER__
#define __HOPE__GL_RENDERER__

#include <scene/ogl/visitors/cache/MeshData.hpp>

namespace Hope::GL {
    /**
     * Render the scene.
     */
    class OpenGLRenderer final {
        public:
            /**
             * Render the scene.
             */
            void render(std::vector<MeshData>& dataList) ;

        private:
            /**
             * Use a material component.
             */
            void useMaterial(const Hope::MaterialComponent* component) ;
    } ;
}

#endif
