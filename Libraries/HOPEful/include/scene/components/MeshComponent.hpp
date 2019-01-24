#ifndef __HOPE__MESH_COMPONENT__
#define __HOPE__MESH_COMPONENT__

#include <memory>
#include <string>
#include <scene/components/Component.hpp>
#include <HopeAPI.hpp>

#ifdef OGL
    #include <scene/ogl/mesh/loader/MeshLoader.hpp>
    #include <scene/ogl/mesh/Mesh.hpp>
    namespace API = Hope::GL ;
#endif

namespace Hope {
    class IVisitor ;

    /**
     * Component to link a 3D mesh to an entity.
     */
    class MeshComponent final : public Component {
        private:
            /**
             * Mesh that is beared by the component.
             */
            std::shared_ptr<API::Mesh> m_mesh = nullptr ;

        public:
            /**
             * Create a new MeshComponent.
             * @param   meshFile    File path of the mesh to use in this
             *                      component.
             */
            MeshComponent(const std::string& meshFile) ;

            /**
             * Accept the visitor.
             */
            void accept(IVisitor* visitor) override ;

            /**
             * To know if the component can be shared by several entities.
             * @return  true, the MeshComponent can be shared.
             */
            bool isShareable() const override ;
    } ;
}

#endif
