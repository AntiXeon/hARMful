#include <scene/ogl/visitors/OpenGLRenderVisitor.hpp>
#include <scene/components/CameraComponent.hpp>
#include <scene/components/MeshComponent.hpp>
#include <scene/components/RenderConfiguration.hpp>

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
