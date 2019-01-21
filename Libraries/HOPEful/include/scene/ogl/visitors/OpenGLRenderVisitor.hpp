#ifndef __HOPE__OPENGL_RENDER_VISITOR__
#define __HOPE__OPENGL_RENDER_VISITOR__

#include <interfaces/visitor/IVisitor.hpp>

namespace Hope::GL {
    /**
     * Visitor for rendering objects using the OpenGL API.
     */
    class OpenGLRenderVisitor final : public IVisitor {
        public:
            /**
             * Visit a camera component.
             */
            void visit(CameraComponent* component) override ;

            /**
             * Visit a mesh component.
             */
            void visit(MeshComponent* component) override ;
    } ;
}

#endif
