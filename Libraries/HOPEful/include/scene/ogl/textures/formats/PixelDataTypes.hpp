#ifndef __HOPE__GL_TEXTURE_PIXEL_DATA_TYPES__
#define __HOPE__GL_TEXTURE_PIXEL_DATA_TYPES__

#include <GL/glew.h>

namespace Hope::GL {
    /**
     * Indication on the way colors are encoded in memory.
     */
    enum class PixelDataType {
        UnsignedByte = GL_UNSIGNED_BYTE,
        Byte = GL_BYTE,
        UnsignedShort = GL_UNSIGNED_SHORT,
        Short = GL_SHORT,
        UnsignedInt = GL_UNSIGNED_INT,
        Int = GL_INT,
        HalfFloat = GL_HALF_FLOAT,
        Float = GL_FLOAT,
        UnsignedByte332 = GL_UNSIGNED_BYTE_3_3_2,
        UnsignedByte233 = GL_UNSIGNED_BYTE_2_3_3_REV,
        UnsignedShort565 = GL_UNSIGNED_SHORT_5_6_5,
        UnsignedShort565Reversed = GL_UNSIGNED_SHORT_5_6_5_REV,
        UnsignedShort4444 = GL_UNSIGNED_SHORT_4_4_4_4,
        UnsignedShort4444Reversed = GL_UNSIGNED_SHORT_4_4_4_4_REV,
        UnsignedShort5551 = GL_UNSIGNED_SHORT_5_5_5_1,
        UnsignedShort1555 = GL_UNSIGNED_SHORT_1_5_5_5_REV,
        UnsignedInt8888 = GL_UNSIGNED_INT_8_8_8_8,
        UnsignedInt8888Reversed = GL_UNSIGNED_INT_8_8_8_8_REV,
        UnsignedInt1010102 = GL_UNSIGNED_INT_10_10_10_2,
        UnsignedInt2101010 = GL_UNSIGNED_INT_2_10_10_10_REV,
        UnsignedInt248 = GL_UNSIGNED_INT_24_8
    } ;
}

#endif
