#ifndef __HOPE__GL_OPTIONS__
#define __HOPE__GL_OPTIONS__

#include <utils/Platform.hpp>

#include <cstdint>

namespace Hope { namespace GL {
    /**
     * Options to configurate OpenGL.
     */
    class Options {
        public:
            /**
             * Sampling to enable or disable antialiasing.
             */
            enum class Sampling : int8_t {
                Disabled = 0,
                X2       = 2,
                X4       = 4,
                X8       = 8,
                X16      = 16
            };


            /**
             * Set the version of OpenGL to be used.
             * @param major Major version number.
             * @param minor Minor version number.
             */
            exported static void SetGLVersion(
                const int major,
                const int minor
            );

            /**
             * Set the sampling factor to compute antialiasing.
             * @param sampling Value of the sampling factor. Common values are
             *                 0, 2, 4, 8, 16.
             */
            exported static void SetSamplingFactor(const Sampling sampling);
    };
}}

#endif
