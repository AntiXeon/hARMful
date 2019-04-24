#ifndef __HOPE__HL_MESH_GEOMETRY_COMPONENT__
#define __HOPE__HL_MESH_GEOMETRY_COMPONENT__

#include <scene/components/Component.hpp>
#include <HopeAPI.hpp>

#ifdef OGL
    #include <scene/ogl/mesh/MeshGeometry.hpp>
    namespace API = Hope::GL ;
#endif

namespace Hope {
    class ISceneGraphVisitor ;

    /**
     * Component to render a 3D object.
     */
    class MeshGeometryComponent final : public Component {
        private:
            /**
             * Geometry of the 3D object.
             */
            API::MeshGeometry* m_geometry ;

        public:
            /**
             * Creation of a MeshGeometryComponent.
             */
            MeshGeometryComponent(API::MeshGeometry* geometry) ;

            /**
             * Destruction of the MeshGeometryComponent.
             */
            virtual ~MeshGeometryComponent() ;

            /**
             * Get the geometry.
             */
            const API::MeshGeometry* geometry() const {
                return m_geometry ;
            }

            /**
             * Accept the visitor.
             */
            void accept(ISceneGraphVisitor* visitor) override ;

            /**
             * To know if the component can be shared by several entities.
             * @return  true, the MeshGeometryComponent can be shared.
             */
            bool isShareable() const override {
                return true ;
            }

            /**
             * To know if the component can be removed from its entity(-ies).
             * @return  true, the component can be removed.
             */
            bool isRemovable() const override {
                return false ;
            }

            /**
             * To know if several components of the current type can be beared
             * by a single entity.
             * @return  false, an entity cannot bear several
             *          MeshGeometryComponent.
             */
            bool isStackable() const override {
                return false ;
            }
    } ;
}

#endif
