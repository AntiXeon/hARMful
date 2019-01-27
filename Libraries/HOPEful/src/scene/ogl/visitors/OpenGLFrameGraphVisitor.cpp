#include <scene/ogl/visitors/OpenGLFrameGraphVisitor.hpp>
#include <scene/framegraph/ActiveCamera.hpp>
#include <scene/framegraph/FrustumCulling.hpp>
#include <scene/framegraph/Viewport.hpp>
#include <scene/ogl/Utils.hpp>
#include <GL/glew.h>

using namespace Hope ;
using namespace Hope::GL ;

void OpenGLFrameGraphVisitor::visit(ActiveCamera* node) {
    Hope::CameraComponent* camera = node -> camera() ;

    // Set up the clear color.
    Color clearColor = camera -> clearColor() ;
    glClearColor(
        clearColor.red(),
        clearColor.green(),
        clearColor.blue(),
        clearColor.alpha()
    ) ;

    // Set up the projection matrix.
    const float CameraFOV = 45.f ;
    const float NearPlaneDistance = 1.f ;
    const float FarPlaneDistance = 1000.f ;
    float aspectRatio = m_windowSize.width() / m_windowSize.height() ;

    glMatrixMode(GL_PROJECTION) ;
    glLoadIdentity() ;
    GLPerspective(CameraFOV, aspectRatio, NearPlaneDistance, FarPlaneDistance) ;
}

void OpenGLFrameGraphVisitor::visit(FrustumCulling* /*node*/) {
    // TODO
}

void OpenGLFrameGraphVisitor::visit(Viewport* /*node*/) {
    // TODO
}
