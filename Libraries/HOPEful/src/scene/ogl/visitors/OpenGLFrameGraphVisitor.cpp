#include <scene/ogl/visitors/OpenGLFrameGraphVisitor.hpp>
#include <scene/framegraph/ActiveCamera.hpp>
#include <scene/framegraph/FrustumCulling.hpp>
#include <scene/framegraph/Viewport.hpp>
#include <GL/glew.h>

using namespace Hope ;
using namespace Hope::GL ;

void OpenGLFrameGraphVisitor::visit(ActiveCamera* node) {
    Hope::CameraComponent* camera = node -> camera() ;
    Color clearColor = camera -> clearColor() ;

    glClearColor(
        clearColor.red(),
        clearColor.green(),
        clearColor.blue(),
        clearColor.alpha()
    ) ;
}

void OpenGLFrameGraphVisitor::visit(FrustumCulling* /*node*/) {
    // TODO
}

void OpenGLFrameGraphVisitor::visit(Viewport* /*node*/) {
    // TODO
}
