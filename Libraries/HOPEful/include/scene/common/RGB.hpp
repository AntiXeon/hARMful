#ifndef __HOPE__RGB_CHANNEL_BYTES__
#define __HOPE__RGB_CHANNEL_BYTES__

#include <utils/Platform.hpp>

namespace Hope {
    /**
     * Amount of channels in the HDR maps.
     */
    static const int AmountRGBChannels = 3 ;

    /**
     * Data type for HDR maps.
     */
    using HDRDataType = float ;

    /**
     * Union to easily convert bytes to floats and vice versa.
     * Easier management of channels for looping on them (through array)
     * while processing the map.
     */
    union HDRRGB {
       HDRDataType red ;
       HDRDataType green ;
       HDRDataType blue ;

       HDRDataType array[AmountRGBChannels] ;
       unsigned char bytes[AmountRGBChannels * sizeof(HDRDataType)] ;
    } ;


    /**
     * Data type for bye based pictures.
     */
    using ByteDataType = unsigned char ;

    /**
     * Union to easily convert bytes to RGB and vice versa.
     * Easier management of channels for looping on them (through array)
     * while processing the map.
     */
    union ByteRGB {
        ByteDataType red ;
        ByteDataType green ;
        ByteDataType blue ;

        ByteDataType array[AmountRGBChannels] ;
        unsigned char bytes[AmountRGBChannels * sizeof(ByteDataType)] ;
    } ;
} ;

#endif
