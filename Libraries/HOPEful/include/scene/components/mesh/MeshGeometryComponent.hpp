#ifndef __HOPE__MESH_GEOMETRY_COMPONENT__
#define __HOPE__MESH_GEOMETRY_COMPONENT__

#include <scene/components/mesh/GeometryComponent.hpp>
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
    class MeshGeometryComponent final : public GeometryComponent {
        public:
            /**
             * Component class type.
             */
            static const ComponentType ClassType = GeometryComponentType ;

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
            const API::Geometry* geometry() const override {
                return m_geometry ;
            }

            // Copy/move operations.
            MeshGeometryComponent(const MeshGeometryComponent& copied) = default ;
            MeshGeometryComponent(MeshGeometryComponent&& moved) = default ;
            MeshGeometryComponent& operator=(const MeshGeometryComponent& copied) = default ;
            MeshGeometryComponent& operator=(MeshGeometryComponent&& moved) = default ;
    } ;
}

#endif
