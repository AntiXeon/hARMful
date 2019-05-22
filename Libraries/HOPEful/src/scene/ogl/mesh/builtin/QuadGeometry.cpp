#include <scene/ogl/mesh/builtin/QuadGeometry.hpp>
#include <scene/ogl/mesh/Vertex.hpp>

using namespace Hope::GL ;

QuadGeometry::QuadGeometry()
    : Geometry() {
    glGenVertexArrays(1, &m_vertexArray) ;
    glGenBuffers(1, &m_vertexBuffer) ;
    glGenBuffers(1, &m_indexBuffer) ;
    fillBuffers() ;

    const int MaterialID = 0 ;
    const int Offset = 0 ;
    m_parts[0] = GeometryPart(
        MaterialID,
        Offset,
        AmountIndices
    ) ;
}

QuadGeometry::~QuadGeometry() {
    glDeleteBuffers(1, &m_indexBuffer) ;
    glDeleteBuffers(1, &m_vertexBuffer) ;
    glDeleteVertexArrays(1, &m_vertexArray) ;
}

void QuadGeometry::fillBuffers() {
    static const float Vertices[AmountVertexData] = {
        // Position,        TexCoords
        -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
         1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
         1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    } ;

    static const uint8_t IndiceArray[AmountIndices] = { 0, 1, 2, 2, 1, 3 } ;

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer) ;
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW) ;

    glBindVertexArray(m_vertexArray) ;

    static const size_t VertexByteSize = VertexDataSize * sizeof(float) ;
    unsigned char offset = 0 ;
    // Position attribute.
    glEnableVertexAttribArray(0) ;
    glVertexAttribPointer(0, Vertex::PositionLength, GL_FLOAT, GL_FALSE, VertexByteSize, reinterpret_cast<void*>(offset)) ;
    offset += (Vertex::PositionLength * sizeof(float)) ;

    // Texture coordinates attribute.
    glEnableVertexAttribArray(1) ;
    glVertexAttribPointer(1, Vertex::TexCoordLength, GL_FLOAT, GL_FALSE, VertexByteSize, reinterpret_cast<void*>(offset)) ;
    offset += (Vertex::TexCoordLength * sizeof(float)) ;

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer) ;
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndiceArray), IndiceArray, GL_STATIC_DRAW) ;

    glBindVertexArray(0) ;
    glBindBuffer(GL_ARRAY_BUFFER, 0) ;
}
