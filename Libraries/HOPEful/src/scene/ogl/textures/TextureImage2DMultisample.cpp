#include <scene/ogl/textures/TextureImage2DMultisample.hpp>
#include <scene/ogl/textures/TextureLoader.hpp>
#include <scene/ogl/textures/formats/FilterModes.hpp>
#include <HOPEStrings.hpp>

using namespace Hope ;
using namespace Hope::GL ;

TextureImage2DMultisample::TextureImage2DMultisample(
    const Mind::Dimension2Di& size,
    const InternalFormat internalFormat,
    const int samples,
    const bool fixedSampleLocation
) : Texture(
        GL_TEXTURE_2D_MULTISAMPLE,
        internalFormat
    ),
    m_size(size),
    m_samples(samples),
    m_fixedSampleLocation(fixedSampleLocation) {
    resize(size) ;
}

void TextureImage2DMultisample::resize(const Mind::Dimension2Di& size) {
    m_size = size ;

    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, id()) ;

    glTexImage2DMultisample(
        GL_TEXTURE_2D_MULTISAMPLE,
        m_samples,
        static_cast<GLint>(internalFormat()),
        m_size.width(),
        m_size.height(),
        m_fixedSampleLocation
    ) ;

    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0) ;
}

void TextureImage2DMultisample::setWrapModes(std::array<WrapMode, AmountCoordinates>) {}
