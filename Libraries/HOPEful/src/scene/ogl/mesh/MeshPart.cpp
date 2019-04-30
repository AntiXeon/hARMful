#include <scene/ogl/mesh/MeshPart.hpp>
#include <scene/ogl/mesh/Vertex.hpp>

using namespace Hope::GL ;

MeshPart::MeshPart(
    uint32_t materialID,
    uint32_t offset,
    uint32_t amountIndices
) : m_materialID(materialID),
    m_offset(offset),
    m_amountIndices(amountIndices) {}
