#include <scene/ogl/components/mesh/Vertex.hpp>

using namespace Hope::GL ;

Vertex::Vertex(
    const Mind::Vector3f& pos,
    const Mind::Vector2f& tex,
    const Mind::Vector3f& normal
) {
    m_pos = pos ;
    m_tex = tex ;
    m_normal = normal ;
}
