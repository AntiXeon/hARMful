#ifndef __HOPE__GL_OPTIONS__
#define __HOPE__GL_OPTIONS__

#include <cstdint>

namespace Hope {
    /**
     * @brief   Options to configurate OpenGL.
     */
    class GLOptions {
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
            static void SetGLVersion(const int& major,
                                     const int& minor);

            /**
             * Set the sampling factor to compute antialiasing.
             * @param sampling Value of the sampling factor. Common values are
             *                 0, 2, 4, 8, 16.
             */
            static void SetSamplingFactor(const Sampling& sampling);
    };
}

#endif // ifndef __HOPE__GL_OPTIONS__
