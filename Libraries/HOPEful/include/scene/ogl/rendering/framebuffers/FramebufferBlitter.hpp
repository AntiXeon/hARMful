#ifndef __HOPE__GL_FRAMEBUFFER_BLITTER__
#define __HOPE__GL_FRAMEBUFFER_BLITTER__

#include <scene/ogl/GLDefines.hpp>
#include <GL/glew.h>
#include <scene/ogl/rendering/framebuffers/Framebuffer.hpp>
#include <geometry/rectangles/Rectangle2Df.hpp>

namespace Hope::GL {

    /**
     * Perform a blit of framebuffers.
     */
    class FramebufferBlitter final {
        public:
            /**
             * Mask to define which buffers are to be copied.
             */
            enum Mask : GLbitfield {
                ColorBuffer = GL_COLOR_BUFFER_BIT,
                DepthBuffer = GL_DEPTH_BUFFER_BIT,
                StencilBuffer = GL_STENCIL_BUFFER_BIT,
                DepthStencilBuffer = DepthBuffer | StencilBuffer,
                AllBuffers = ColorBuffer | DepthStencilBuffer
            } ;

            /**
             * Interpolation to be applied if the image is stretched.
             */
            enum Filter : GLenum {
                Nearest = GL_NEAREST,
                Linear = GL_LINEAR
            } ;

        private:
            /**
             * Aggregation of data for blitting.
             */
            struct Blit {
                /**
                 * Framebuffer involved in blit process.
                 */
                Framebuffer* fbo = nullptr ;

                /**
                 * Color buffer involved in blit process.
                 */
                unsigned char colorBuffer = GL_NONE ;

                /**
                 * Area involved in blit process.
                 */
                Mind::Rectangle2Df area ;
            } ;

            /**
             * Source of blit process.
             */
            Blit m_source ;

            /**
             * Destination of blit process.
             */
            Blit m_destination ;

            /**
             * Mask to define which buffers are to be copied.
             * Default is AllBuffers.
             */
            Mask m_mask = AllBuffers ;

            /**
             * Interpolation to be applied if the image is stretched.
             * Default is Linear.
             */
            Filter m_filter = Linear ;

        public:
            /**
             * Do the blit process.
             */
            void doBlit() ;

            /**
             * set the source framebuffer.
             */
            FramebufferBlitter& setSourceFBO(Framebuffer* fbo) {
                m_source.fbo = fbo ;
                return *this ;
            }

            /**
             * set the color buffer source.
             */
            FramebufferBlitter& setSourceColor(const int colorID) {
                m_source.colorBuffer = GL_COLOR_ATTACHMENT0 + colorID ;
                return *this ;
            }

            /**
             * set the color buffer source.
             */
            FramebufferBlitter& setSourceArea(const Mind::Rectangle2Df& area) {
                m_source.area = area ;
                return *this ;
            }

            /**
             * set the destination framebuffer.
             */
            FramebufferBlitter& setDestinationFBO(Framebuffer* fbo) {
                m_destination.fbo = fbo ;
                return *this ;
            }

            /**
             * set the color buffer destination.
             */
            FramebufferBlitter& setDestinationColor(const int colorID) {
                m_destination.colorBuffer = GL_COLOR_ATTACHMENT0 + colorID ;
                return *this ;
            }

            /**
             * set the destination buffer source.
             */
            FramebufferBlitter& setDestinationArea(const Mind::Rectangle2Df& area) {
                m_destination.area = area ;
                return *this ;
            }

            /**
             * Set the mask to define which buffers are to be copied.
             */
            FramebufferBlitter& setMask(const Mask mask) {
                m_mask = mask ;
                return *this ;
            }

            /**
             * Set the interpolation to be applied if the image is stretched.
             */
            FramebufferBlitter& setFilter(const Filter filter) {
                m_filter = filter ;
                return *this ;
            }
    } ;
}

#endif
