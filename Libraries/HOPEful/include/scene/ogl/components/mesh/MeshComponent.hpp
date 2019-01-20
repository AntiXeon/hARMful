#ifndef __HOPE__GL_MESH_COMPONENT__
#define __HOPE__GL_MESH_COMPONENT__

#include <memory>
#include <string>
#include <scene/Component.hpp>

namespace Hope { namespace GL {

    class Mesh ;

    /**
     * Component to link a 3D mesh to an entity.
     */
    class MeshComponent final : public Hope::Component {
        private:
            /**
             * Mesh that is beared by the component.
             */
            std::shared_ptr<Mesh> m_mesh = nullptr ;

        public:
            /**
             * Create a new MeshComponent.
             * @param   meshFile    File path of the mesh to use in this
             *                      component.
             */
            MeshComponent(const std::string& meshFile) ;

            /**
             * To know if the component can be shared by several entities.
             * @return  true, the MeshComponent can be shared.
             */
            bool isShareable() const override ;
    } ;
}}

#endif
