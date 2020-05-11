#ifndef __HOPE__GL_TEXTURE_PIXEL_FORMATS__
#define __HOPE__GL_TEXTURE_PIXEL_FORMATS__

#include <HopeAPI.hpp>

namespace Hope::GL {
    /**
     * Pixel format of the texture.
     */
    enum class PixelFormat {
        Red = GL_RED,
        RedGreen = GL_RG,
        RedGreenBlue = GL_RGB,
        BlueGreenRed = GL_BGR,
        RedGreenBlueAlpha = GL_RGBA,
        BlueGreenRedAlpha = GL_BGRA,
        RedInteger = GL_RED_INTEGER,
        RedGreenInteger = GL_RG_INTEGER,
        RedGreenBlueInteger = GL_RGB_INTEGER,
        BlueGreenRedInteger = GL_BGR_INTEGER,
        RedGreenBlueAlphaInteger = GL_RGBA_INTEGER,
        BlueGreenRedAlphaInteger = GL_BGRA_INTEGER,
        StencilIndex = GL_STENCIL_INDEX,
        DepthComponent = GL_DEPTH_COMPONENT,
        DepthStencil = GL_DEPTH_STENCIL,
        Depth24Stencil8 = GL_DEPTH24_STENCIL8
    } ;
}

#endif
