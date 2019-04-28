#ifndef __HOPE__MESH_TREE_COMPONENT__
#define __HOPE__MESH_TREE_COMPONENT__

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
            MeshTreeComponent(const std::string& meshFile) ;

            /**
             * To know if the component can be shared by several entities.
             * @return  false, the MeshTreeComponent cannot be shared.
             */
            bool isShareable() const override {
                return false ;
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
             * @return  false, an entity cannot bear several MeshTreeComponent.
             */
            bool isStackable() const override {
                return false ;
            }

        protected:
            /**
             * Action to performed when the component is attached to an
             * entity.
             * @param   entity  Entity to attach the component to.
             */
            void onAttach(Entity* entity) override ;

            /**
             * Action to perform when the component is detached from its entity.
             * @param   entity  Entity to detach the component from.
             */
            void onDetach(Entity* entity) override ;
    } ;
}

#endif
