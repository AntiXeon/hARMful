#include <scene/ogl/textures/TextureStorage2D.hpp>

using namespace Hope::GL ;

TextureStorage2D::TextureStorage2D(
    const Mind::Dimension2Di& size,
    const InternalFormat internalFormat
) : Texture(
        GL_TEXTURE_2D,
        internalFormat
    ),
    m_size(size) {
    resize(size) ;
}

void TextureStorage2D::resize(const Mind::Dimension2Di& size) {
    static const GLsizei Level = 1 ;
    glBindTexture(GL_TEXTURE_2D, id()) ;
    glTexStorage2D(
        GL_TEXTURE_2D,
        Level,
        GL_RGBA8UI,
        size.width(),
        size.height()
    ) ;
    glBindTexture(GL_TEXTURE_2D, 0) ;
}

void TextureStorage2D::setWrapModes(std::array<WrapMode, AmountCoordinates> modes) {
    glTexParameteri(target(), GL_TEXTURE_WRAP_S, modes[0]) ;
    glTexParameteri(target(), GL_TEXTURE_WRAP_T, modes[1]) ;
}
