#include <scene/ogl/mesh/builtin/CubeGeometry.hpp>

using namespace Hope::GL ;

CubeGeometry::CubeGeometry()
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

CubeGeometry::~CubeGeometry() {
    glDeleteBuffers(1, &m_indexBuffer) ;
    glDeleteBuffers(1, &m_vertexBuffer) ;
    glDeleteVertexArrays(1, &m_vertexArray) ;
}

void CubeGeometry::fillBuffers() {
    static const int VertexSize = 3 ;
    static const int VertexStride = sizeof(float) * 3 ;

    static const float Vertices[AmountVertices] = {
    	-1.f,  1.f, -1.f,
    	-1.f, -1.f, -1.f,
    	-1.f,  1.f,  1.f,
    	-1.f, -1.f,  1.f,
    	 1.f,  1.f,  1.f,
    	 1.f, -1.f,  1.f,
    	 1.f,  1.f, -1.f,
    	 1.f, -1.f, -1.f
    } ;

    static const uint8_t IndiceArray[AmountIndices] = {
        4, 5, 6, 6, 5, 7,
    	0, 1, 2, 2, 1, 3,

    	3, 1, 5, 5, 1, 7,
    	0, 2, 6, 6, 2, 4,
        
        2, 3, 4, 4, 3, 5,
        6, 7, 0, 0, 7, 1,
    } ;

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer) ;
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW) ;

    glBindVertexArray(m_vertexArray) ;
    // Position attribute.
    glEnableVertexAttribArray(0) ;
    glVertexAttribPointer(0, VertexSize, GL_FLOAT, GL_FALSE, VertexStride, nullptr) ;

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer) ;
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndiceArray), IndiceArray, GL_STATIC_DRAW) ;
}
