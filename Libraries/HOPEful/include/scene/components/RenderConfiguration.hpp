#ifndef __HOPE__RENDER_CONFIGURATION__
#define __HOPE__RENDER_CONFIGURATION__

#include <utils/Platform.hpp>

#include <scene/components/Component.hpp>
#include <scene/FrameGraphNode.hpp>

namespace Hope {
    class ISceneGraphVisitor ;

    /**
     * Component that must be installed in the root entity of the scene graph.
     * It is used to manage how are rendered entities, shaders and other render
     * related stuff.
     */
    class RenderConfiguration final : public Component {
        public:
            /**
             * Component class type.
             */
            static const ComponentType ClassType = RenderConfigurationType ;

        private:
            /**
             * Root node of the frame graph.
             */
            FrameGraphNode* m_frameGraphRoot = nullptr ;

        public:
            /**
             * Create a new RenderConfiguration.
             */
            exported RenderConfiguration() ;

            /**
             * To know if the component can be shared by several entities.
             * @return  false, the RenderConfiguration cannot be shared.
             */
            exported bool isShareable() const override {
                return false ;
            }

            /**
             * To know if the component can be removed from its entity(-ies).
             * @return  false, the component cannot be removed.
             */
            exported bool isRemovable() const override {
                return false ;
            }

            /**
             * To know if several components of the current type can be beared
             * by a single entity.
             * @return  false, an entity can only bear one RenderConfiguration.
             */
            exported bool isStackable() const override {
                return false ;
            }

            /**
             * Set the root node of the frame graph.
             */
            exported void setFrameGraphRoot(FrameGraphNode* root) {
                m_frameGraphRoot = root ;
            }

            /**
             * Get the frame graph root node.
             */
            exported FrameGraphNode* root() const {
                return m_frameGraphRoot ;
            }
    } ;
}

#endif
