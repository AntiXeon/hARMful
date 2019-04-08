#include <HopeAPI.hpp>
#include <HOPEStrings.hpp>
#include <scene/components/test/TriangleTestComponent.hpp>
#include <scene/SceneTypes.hpp>
#include <interfaces/visitors/scenegraph/ISceneGraphVisitor.hpp>
#include <utils/LogSystem.hpp>
#include <cassert>

using namespace Hope ;

TriangleTestComponent::TriangleTestComponent()
    : Component(Hope::TriangleTestType) {
        static const GLfloat Vertices[] = {
             0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
        };

        glGenVertexArrays(1, &m_vertexArrayIndex) ;
        glBindVertexArray(m_vertexArrayIndex) ;

        GLuint vbo ;
        glGenBuffers(1, &vbo) ;
        glBindBuffer(GL_ARRAY_BUFFER, vbo) ;
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW) ;

        // Position attribute.
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr) ;
        glEnableVertexAttribArray(0) ;

        ushort indices[3] ;
        indices[0] = 0 ;
        indices[1] = 1 ;
        indices[2] = 2 ;

        glGenBuffers(1, &m_indexBuffer) ;
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer) ;
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW) ;

        glBindVertexArray(0) ;
}

void TriangleTestComponent::accept(ISceneGraphVisitor* visitor) {
    visitor -> visit(this) ;
}

void TriangleTestComponent::render() {
    glBindVertexArray(m_vertexArrayIndex) ;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer) ;
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, nullptr) ;
    glBindVertexArray(0) ;
}

bool TriangleTestComponent::isShareable() const {
    return true ;
}
