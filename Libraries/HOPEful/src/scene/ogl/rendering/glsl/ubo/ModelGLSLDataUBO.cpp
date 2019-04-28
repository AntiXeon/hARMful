#include <scene/ogl/rendering/glsl/ubo/ModelGLSLDataUBO.hpp>
#include <scene/components/materials/BlockBindings.hpp>

using namespace Hope::GL ;

ModelGLSLDataUBO::ModelGLSLDataUBO()
    : UniformBufferObject(MODEL_DATA_UBO_BINDING_INDEX) {
    glBindBuffer(GL_UNIFORM_BUFFER, bufferID()) ;
    glBufferData(GL_UNIFORM_BUFFER, size(), data(), GL_DYNAMIC_DRAW) ;
    glBindBufferBase(GL_UNIFORM_BUFFER, MODEL_DATA_UBO_BINDING_INDEX, bufferID()) ;
    glBindBuffer(GL_UNIFORM_BUFFER, 0) ;
}

void ModelGLSLDataUBO::setMatrices(
    const Mind::Matrix4x4f& modelMatrix,
    const Mind::Matrix4x4f& viewMatrix,
    const Mind::Matrix4x4f& projectionMatrix
) {
    // Update the UBO matrices.
    m_data.modelMatrix = modelMatrix.toArray() ;

    Mind::Matrix4x4f modelViewMatrix = viewMatrix * modelMatrix ;
    m_data.modelViewMatrix = modelViewMatrix.toArray() ;

    Mind::Matrix4x4f mvpMatrix = projectionMatrix * modelViewMatrix ;
    m_data.mvpMatrix = mvpMatrix.toArray() ;

    Mind::Matrix4x4f resultMatrix ;
    modelMatrix.inverse(resultMatrix) ;
    m_data.inverseModelMatrix = resultMatrix.toArray() ;

    modelViewMatrix.inverse(resultMatrix) ;
    m_data.inverseModelViewMatrix = resultMatrix.toArray() ;

    Mind::Matrix4x4f normalMatrix ;
    resultMatrix.transposed(normalMatrix) ; // Normal matrix = transposed of the inverse model view matrix.
    m_data.normalMatrix = normalMatrix.toArray() ;

    mvpMatrix.inverse(resultMatrix) ;
    m_data.inverseMVPMatrix = resultMatrix.toArray() ;

    m_data.modelNormalMatrix = (normalMatrix * modelMatrix).toArray() ;
    m_data.modelViewNormalMatrix = (normalMatrix * modelViewMatrix).toArray() ;
}
