#include <ogl/mesh/Mesh.hpp>

using namespace Hope::GL ;

Mesh::Mesh(const std::vector<MeshPart>& parts)
{
    m_parts = parts ;
}

Mesh::~Mesh() {
    // Clear texture data.
}

void Mesh::render() {
    // To be done...
}
