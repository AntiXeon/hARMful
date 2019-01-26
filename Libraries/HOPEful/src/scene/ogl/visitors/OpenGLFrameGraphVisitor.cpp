#include <scene/ogl/visitors/OpenGLFrameGraphVisitor.hpp>
#include <scene/framegraph/ActiveCamera.hpp>
#include <scene/framegraph/FrustumCulling.hpp>
#include <scene/framegraph/Viewport.hpp>

using namespace Hope ;
using namespace Hope::GL ;

void OpenGLFrameGraphVisitor::visit(ActiveCamera* /*node*/) {
    // TODO
}

void OpenGLFrameGraphVisitor::visit(FrustumCulling* /*node*/) {
    // TODO
}

void OpenGLFrameGraphVisitor::visit(Viewport* /*node*/) {
    // TODO
}
