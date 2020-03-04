#ifndef __HOPE__QUAD_GEOMETRY_COMPONENT__
#define __HOPE__QUAD_GEOMETRY_COMPONENT__

#include <utils/Platform.hpp>

#include <scene/components/mesh/GeometryComponent.hpp>
#include <HopeAPI.hpp>

#ifdef OGL
    #include <scene/ogl/mesh/builtin/QuadGeometry.hpp>
    namespace API = Hope::GL ;
#endif

namespace Hope {
    class ISceneGraphVisitor ;

    /**
     * Component to render a quad.
     */
    class QuadGeometryComponent final : public GeometryComponent {
        public:
            /**
             * Component class type.
             */
            static const ComponentType ClassType = GeometryComponentType ;

        private:
            /**
             * Geometry of the 3D cube.
             */
            API::QuadGeometry m_geometry ;

        public:
            /**
             * Creation of a CubeGeometryComponent.
             */
            exported QuadGeometryComponent() : GeometryComponent() {}

            /**
             * Get the geometry.
             */
            exported const API::QuadGeometry* geometry() const override {
                return &m_geometry ;
            }
    } ;
}

#endif
