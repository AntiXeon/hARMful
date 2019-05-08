#ifndef __HOPE__CUBE_GEOMETRY_COMPONENT__
#define __HOPE__CUBE_GEOMETRY_COMPONENT__

#include <scene/components/mesh/GeometryComponent.hpp>
#include <HopeAPI.hpp>

#ifdef OGL
    #include <scene/ogl/mesh/builtin/CubeGeometry.hpp>
    namespace API = Hope::GL ;
#endif

namespace Hope {
    class ISceneGraphVisitor ;

    /**
     * Component to render a cube.
     */
    class CubeGeometryComponent final : public GeometryComponent {
        public:
            /**
             * Component class type.
             */
            static const ComponentType ClassType = GeometryComponentType ;

        private:
            /**
             * Geometry of the 3D cube.
             */
            API::CubeGeometry m_geometry ;

        public:
            /**
             * Creation of a CubeGeometryComponent.
             */
            CubeGeometryComponent() : GeometryComponent() {}

            /**
             * Get the geometry.
             */
            const API::CubeGeometry* geometry() const override {
                return &m_geometry ;
            }
    } ;
}

#endif
