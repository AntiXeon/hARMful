#include <scene/ogl/mesh/Vertex.hpp>

using namespace Hope::GL ;

Vertex::Vertex(
    const Mind::Vector3f& pos,
    const Mind::Vector2f& tex,
    const Mind::Vector3f& normal,
    const Mind::Vector3f& tangent
) {
    m_data.resize(TotalLength) ;

    m_data[0] = pos.get(Mind::Vector3f::X) ;
    m_data[1] = pos.get(Mind::Vector3f::Y) ;
    m_data[2] = pos.get(Mind::Vector3f::Z) ;

    m_data[3] = tex.get(Mind::Vector2f::X) ;
    m_data[4] = tex.get(Mind::Vector2f::Y) ;

    m_data[5] = normal.get(Mind::Vector3f::X) ;
    m_data[6] = normal.get(Mind::Vector3f::Y) ;
    m_data[7] = normal.get(Mind::Vector3f::Z) ;

    m_data[8] = tangent.get(Mind::Vector3f::X) ;
    m_data[9] = tangent.get(Mind::Vector3f::Y) ;
    m_data[10] = tangent.get(Mind::Vector3f::Z) ;
}
