#ifndef __HOPE__RENDER_CONFIGURATION__
#define __HOPE__RENDER_CONFIGURATION__

#include <scene/components/Component.hpp>
#include <scene/FrameGraphNode.hpp>

namespace Hope {
    class IVisitor ;

    /**
     * Component that must be installed in the root entity of the scene graph.
     * It is used to manage how are rendered entities, shaders and other render
     * related stuff.
     */
    class RenderConfiguration final : public Component {
        private:
            /**
             * Root node of the frame graph.
             */
            FrameGraphNode* m_frameGraphRoot = nullptr ;

        public:
            /**
             * Create a new RenderConfiguration.
             */
            RenderConfiguration() ;

            /**
             * Accept the visitor.
             */
            void accept(IVisitor* visitor) override ;

            /**
             * To know if the component can be shared by several entities.
             * @return  false, the RenderConfiguration cannot be shared.
             */
            bool isShareable() const override ;

            /**
             * Set the root node of the frame graph.
             */
            void setFrameGraphRoot(FrameGraphNode* root) {
                m_frameGraphRoot = root ;
            }
    } ;
}

#endif
