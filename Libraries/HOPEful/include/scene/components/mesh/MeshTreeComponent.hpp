#ifndef __HOPE__MESH_TREE_COMPONENT__
#define __HOPE__MESH_TREE_COMPONENT__

#include <utils/Platform.hpp>

#include <string>
#include <scene/components/Component.hpp>
#include <HopeAPI.hpp>

#ifdef OGL
    #include <scene/ogl/mesh/loader/MeshTreeLoader.hpp>
    namespace API = Hope::GL ;
#endif

namespace Hope {
    class ISceneGraphVisitor ;

    /**
     * Component to load a hierarchy composing a complex 3D object.
     */
    class MeshTreeComponent final : public Component {
        public:
            /**
             * Component class type.
             */
            static const ComponentType ClassType = MeshTreeComponentType ;

        private:
            /**
             * Source file.
             */
            std::string m_source ;

            /**
             * Loader of the mesh tree
             */
            API::MeshTreeLoader m_loader ;

        public:
            /**
             * Create a new MeshTreeComponent.
             * @param   meshFile    File path of the mesh to use in this
             *                      component.
             */
            exported MeshTreeComponent(const std::string& meshFile) ;

            /**
             * Get an entity generated on loading by its name.
             * If the name is not found, nullptr is returned.
             */
            exported Entity* entity(const std::string& name) {
                return m_loader.entity(name) ;
            }

            /**
             * To know if the component can be shared by several entities.
             * @return  false, the MeshTreeComponent cannot be shared.
             */
            exported bool isShareable() const override {
                return false ;
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
             * @return  false, an entity cannot bear several MeshTreeComponent.
             */
            exported bool isStackable() const override {
                return false ;
            }

        protected:
            /**
             * Action to performed when the component is attached to an
             * entity.
             * @param   entity  Entity to attach the component to.
             */
            exported void onAttach(Entity* entity) override ;

            /**
             * Action to perform when the component is detached from its entity.
             * @param   entity  Entity to detach the component from.
             */
            exported void onDetach(Entity* entity) override ;
    } ;
}

#endif
