#ifndef __HOPE__GL_BUFFER_CLEARER__
#define __HOPE__GL_BUFFER_CLEARER__

#include <HopeAPI.hpp>
#include <utils/Platform.hpp>

namespace Hope::GL {
    /**
     * Used to abstract the clearing of buffers (color, depth, ...).
     */
    class BufferClearer final {
        public:
            /**
             * Buffers that can be cleared.
             */
            enum class Buffer {
                Color = GL_COLOR_BUFFER_BIT,
                Depth = GL_DEPTH_BUFFER_BIT,
                Stencil = GL_STENCIL_BUFFER_BIT,
                Accumulation = GL_ACCUM_BUFFER_BIT,
                ColorDepth = Color | Depth,
                DepthStencil = Depth | Stencil,
                ColorDepthStencil = Color | Depth | Stencil,
                All = Color | Depth | Stencil | Accumulation
            } ;

            /**
             * Clear the provided buffers
             */
            exported static void Clear(const Buffer buffers) {
                glClear(static_cast<GLbitfield>(buffers)) ;
            }

        private:
            BufferClearer() = delete ;
            // Avoid copy/move operations.
            BufferClearer(const BufferClearer& copied) = delete ;
            BufferClearer(BufferClearer&& moved) = delete ;
            BufferClearer& operator=(const BufferClearer& copied) = delete ;
            BufferClearer& operator=(BufferClearer&& moved) = delete ;
    } ;
}

#endif
