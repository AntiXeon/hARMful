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

void OpenGLRenderVisitor::visit(MeshComponent* component) {
    std::shared_ptr<API::Mesh> mesh = component -> mesh() ;
    const std::vector<MeshPart>& meshParts = mesh -> parts() ;

    for (const MeshPart& part : meshParts) {
        glBindBuffer(GL_ARRAY_BUFFER, part.vertexBufferID()) ;
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, part.indexBufferID()) ;
        glDrawElements(GL_TRIANGLES, part.amountIndices(), GL_UNSIGNED_INT, 0) ;
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0) ;
    }
}

void OpenGLRenderVisitor::visit(Hope::RenderConfiguration* /*component*/) {
    // TODO
}
