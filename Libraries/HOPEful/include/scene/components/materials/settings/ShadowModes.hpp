#ifndef __HOPE__SHADOW_MODES__
#define __HOPE__SHADOW_MODES__

namespace Hope {
    /**
     * Shadow modes:
     *  - None does not display shadow for the objects;
     *  - Opaque to compute shadow as for opaque objects. Do not care about
     *  - transparency;
     *  - AlphaClip to compute shadow taking full transparency into account. The
     *    non transparent parts draw shadows as for opaque objects.
     */
    enum class ShadowMode : uint8_t {
        None,
        Opaque,
        AlphaClip
    } ;
}

#endif
