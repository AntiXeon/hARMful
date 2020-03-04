#ifndef __HOPE__GL_CAPABILITY_TYPES__
#define __HOPE__GL_CAPABILITY_TYPES__

#include <cstdint>

namespace Hope::GL {
    /**
     * Capability types.
     */
    enum class CapabilityType : uint8_t {
        Undefined,
        AlphaCoverage,
        AlphaTest,
        AntiAliasing,
        BlendEquation,
        BlendEquationAdvanced,
        ClipPlane,
        ColorMask,
        DepthMask,
        DepthTest,
        Dithering,
        FaceCulling,
        FrontFace,
        LineWidth,
        PointSize,
        PolygonOffset,
        ScissorTest,
        SeamlessCubemap,
        StencilMask,
        StencilOperation,
        StencilTest
    } ;
}

#endif
