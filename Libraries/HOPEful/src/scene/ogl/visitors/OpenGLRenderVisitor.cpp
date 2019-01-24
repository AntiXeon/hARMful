#include <scene/ogl/visitors/OpenGLRenderVisitor.hpp>

using namespace Hope ;
using namespace Hope::GL ;

void OpenGLRenderVisitor::startNewFrame() {
    m_currentFrameID++ ;
}

FrameID OpenGLRenderVisitor::currentFrameID() const {
    return m_currentFrameID ;
}

void OpenGLRenderVisitor::visit(CameraComponent* /*component*/) {
    // TODO
}

void OpenGLRenderVisitor::visit(MeshComponent* /*component*/) {
    // TODO
}

void OpenGLRenderVisitor::visit(Hope::RenderConfiguration* /*component*/) {

}
