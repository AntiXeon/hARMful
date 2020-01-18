#ifndef __HOPE__ALPHA_BLENDING_MODES__
#define __HOPE__ALPHA_BLENDING_MODES__

namespace Hope {
    /**
     * Alpha blending modes:
     *  - Opaque to compute shadow as for opaque objects. Do not care about
     *    transparency;
     *  - AlphaBlend to compute blend alpha values;
     *  - AlphaClip to compute shadow taking full transparency into account. The
     *    non transparent parts draw shadows as for opaque objects.
     */
    enum class AlphaBlendingMode : uint8_t {
        Opaque,
        AlphaBlend,
        AlphaClip
    } ;
}

#endif
