#include <scene/ogl/visitors/OpenGLFrameGraphVisitor.hpp>
#include <scene/framegraph/ActiveCamera.hpp>
#include <scene/framegraph/FrustumCulling.hpp>
#include <scene/framegraph/Viewport.hpp>
#include <scene/ogl/Utils.hpp>
#include <scene/Entity.hpp>
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

    // Update the projection matrix if needed.
    if (m_hasWindowChanged) {
        // Set up the projection matrix.
        const float CameraFOV = 45.f ;
        const float NearPlaneDistance = 1.f ;
        const float FarPlaneDistance = 1000.f ;
        float aspectRatio = m_windowSize.width() / m_windowSize.height() ;

        glMatrixMode(GL_PROJECTION) ;
        glLoadIdentity() ;
        GLPerspective(CameraFOV, aspectRatio, NearPlaneDistance, FarPlaneDistance) ;
    }

    // Update the model view matrix.
    glMatrixMode(GL_MODELVIEW) ;
    Mind::Matrix4x4f projectionMatrix = camera -> projectionMatrix() ;
    float projectionMatrixData[Mind::Matrix4x4f::MatrixSize] ;
    projectionMatrix.data(projectionMatrixData) ;
    glMultMatrixf(projectionMatrixData) ;

    Hope::Entity* cameraEntity = camera -> firstEntity() ;
    Hope::Transform& cameraTransform = cameraEntity -> transform() ;
    // Inverse as the world moves instead of the camera!
    Mind::Vector3f eyeView = -cameraTransform.translation() ;
    glTranslated(
        eyeView.get(Mind::Vector3f::X),
        eyeView.get(Mind::Vector3f::Y),
        eyeView.get(Mind::Vector3f::Z)
    ) ;
}

void OpenGLFrameGraphVisitor::visit(FrustumCulling* /*node*/) {
    // TODO
}

void OpenGLFrameGraphVisitor::visit(Viewport* node) {
    if (!m_hasWindowChanged) {
        return ;
    }

    // Update the projection matrix.
    glMatrixMode(GL_PROJECTION) ;

    Mind::Point2Df relativePosition = node -> position() ;
    Mind::Dimension2Df relativeDimension = node -> dimension() ;

    Mind::Point2Df absolutePosition(
        relativePosition.get(Mind::Point2Df::X) * m_windowSize.width(),
        relativePosition.get(Mind::Point2Df::Y) * m_windowSize.height()
    ) ;

    Mind::Dimension2Df absoluteDimension(
        relativeDimension.width() * m_windowSize.width(),
        relativeDimension.height() * m_windowSize.height()
    ) ;

    // Apply the viewport parameters.
    glViewport(
        absolutePosition.get(Mind::Point2Df::X),
        absolutePosition.get(Mind::Point2Df::Y),
        absoluteDimension.width(),
        absoluteDimension.height()
    ) ;

    // Switch back to the modelview matrix.
    glMatrixMode(GL_MODELVIEW) ;
}
