#ifndef __HOPE__GEOMETRY_COMPONENT__
#define __HOPE__GEOMETRY_COMPONENT__

#include <utils/Platform.hpp>

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
    class GeometryComponent : public Component {
        public:
            /**
             * Component class type.
             */
            static const ComponentType ClassType = GeometryComponentType ;

        public:
            /**
             * Creation of a GeometryComponent.
             */
            exported GeometryComponent() : Component(ClassType) {}

            /**
             * Get the geometry.
             */
            exported virtual const API::Geometry* geometry() const = 0 ;

            /**
             * To know if the component can be shared by several entities.
             * @return  true, the MeshGeometryComponent can be shared.
             */
            exported bool isShareable() const override {
                return true ;
            }

            /**
             * To know if the component can be removed from its entity(-ies).
             * @return  true, the component can be removed.
             */
            exported bool isRemovable() const override {
                return false ;
            }

            /**
             * To know if several components of the current type can be beared
             * by a single entity.
             * @return  false, an entity cannot bear several
             *          MeshGeometryComponent.
             */
            exported bool isStackable() const override {
                return false ;
            }
    } ;
}

#endif
