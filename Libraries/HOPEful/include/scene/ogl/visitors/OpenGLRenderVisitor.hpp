#ifndef __HOPE__OPENGL_RENDER_VISITOR__
#define __HOPE__OPENGL_RENDER_VISITOR__

#include <interfaces/visitors/scenegraph/ISceneGraphVisitor.hpp>

namespace Hope::GL {
    /**
     * Visitor for rendering objects using the OpenGL API.
     */
    class OpenGLRenderVisitor final : public ISceneGraphVisitor {
        private:
            /**
             * The ID of the current frame being rendered.
             */
            FrameID m_currentFrameID = 0 ;

        public:
            /**
             * A new frame starts to be rendered.
             */
            void startNewFrame() ;

            /**
             * Get the current frame ID while visiting.
             */
            FrameID currentFrameID() const override ;

            /**
             * Visit a camera component.
             */
            void visit(CameraComponent* component) override ;

            /**
             * Visit a mesh component.
             */
            void visit(MeshComponent* component) override ;

            /**
             * Visit a render configuration component.
             */
            void visit(Hope::RenderConfiguration* component) override ;
    } ;
}

#endif
