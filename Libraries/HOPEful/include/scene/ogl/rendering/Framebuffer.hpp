#ifndef __HOPE__GL_FRAMEBUFFER__
#define __HOPE__GL_FRAMEBUFFER__

#include <scene/ogl/GLDefines.hpp>
#include <scene/ogl/textures/Texture2D.hpp>
#include <geometry/dimensions/Dimension2Di.hpp>
#include <geometry/dimensions/Dimension2Df.hpp>
#include <GL/glew.h>
#include <list>
#include <memory>
#include <vector>

namespace Hope::GL {
    /**
     * Memory buffer that contains a complete frame of data.
     * This allows off-screen rendering for several tasks: mirrors in a 3D
     * scene, deferred rendering, etc.
     */
    class Framebuffer final {
        private:
            /**
             * To know if mipmaps are automatically generated. Here, no.
             */
            static const bool GenerateMipmaps ;

            /**
             * Mipmap level for the attached textures.
             */
            static const int MipmapLevel = 0 ;

            /**
             * ID of the framebuffer object on GPU side.
             */
            GLuint m_fboID = INVALID_VALUE ;

            /**
             * Size of the framebuffer attachments.
             */
            Mind::Dimension2Di m_size ;

            /**
             * Color textures attached to the framebuffer.
             * Stores the textures associated to their attachment point.
             */
            std::vector<std::unique_ptr<Texture2D>> m_colorAttachments ;

            /**
             * Depth buffer attachment.
             */
            std::unique_ptr<Texture2D> m_depthAttachment ;

            /**
             * Stencil buffer attachment.
             */
            std::unique_ptr<Texture2D> m_stencilAttachment ;

            /**
             * Depth + stencil buffer attachment.
             */
            std::unique_ptr<Texture2D> m_depthStencilAttachment ;

        public:
            /**
             * Create a new Framebuffer instance.
             */
            Framebuffer() ;

            /**
             * Create a new Framebuffer instance with a predefined size.
             * @param   size    Size of the framebuffer attachments in pixels.
             */
            Framebuffer(const Mind::Dimension2Di& size) ;

            /**
             * Destruction of the Framebuffer.
             */
            ~Framebuffer() ;

            /**
             * Bind the framebuffer.
             */
            void bind() {
                glBindFramebuffer(GL_FRAMEBUFFER, m_fboID) ;
            }

            /**
             * Unbind the framebuffer.
             */
            void unbind() {
                glBindFramebuffer(GL_FRAMEBUFFER, 0) ;
            }

            /**
             * Resize the framebuffer.
             */
            void resize(const Mind::Dimension2Di& size) ;

            /**
             * Resize the framebuffer.
             */
            void resize(const Mind::Dimension2Df& size) {
                resize(Mind::Dimension2Di(size.width(), size.height())) ;
            }

            /**
             * Set the color attachments to use.
             * @param   indices List of the attachment indices to use.
             */
            void setDrawBuffers(const std::list<unsigned char> indices) ;

            /**
             * Attach a color texture to the framebuffer.
             * The texture is internally generated and managed.
             * Notice that several textures can be attached to a same
             * framebuffer in order to perform multiple render target
             * operations.
             * @param   attachmentIndex Index of the attachment point to the
             *                          framebuffer. Starts at 0, you can get
             *                          the amount of color attachment with the
             *                          GetColorAttachmentCount() method.
             * @param   textureFormat   Pixel format of the attached texture.
             * @param   pixelDataType   Type of the pixels data.
             */
            void attachColor(
                const unsigned char attachmentIndex,
                const Texture2D::PixelFormat textureFormat,
                const Texture2D::PixelDataType pixelDataType
            ) ;

            /**
             * Attach the depth buffer.
             */
            void attachDepth() ;

            /**
             * Attach the stencil buffer.
             */
            void attachStencil() ;

            /**
             * Attach the combination of depth+stencil buffer.
             */
            void attachDepthStencil() ;

            /**
             * Detach a texture from the framebuffer.
             * @param   attachment      Attachment point to the framebuffer.
             */
            void detachColor(const int attachmentIndex) ;

            /**
             * Detach the depth buffer.
             */
            void detachDepth() ;

            /**
             * Detach the stencil buffer.
             */
            void detachStencil() ;

            /**
             * Detach the combination of depth+stencil buffer.
             */
            void detachDepthStencil() ;

            /**
             * Bind the color attachment.
             */
            void bindUnitColor(const unsigned char attachmentIndex) const {
                m_colorAttachments[attachmentIndex] -> bindUnit(attachmentIndex) ;
            }

            /**
             * Bind the depth attachment.
             */
            void bindUnitDepth(const unsigned char unit) const {
                m_depthAttachment -> bindUnit(unit) ;
            }

            /**
             * Bind the stencil attachment.
             */
            void bindUnitStencil(const unsigned char unit) const {
                m_depthAttachment -> bindUnit(unit) ;
            }

            /**
             * Bind the depth+stencil attachment.
             */
            void bindUnitDepthStencil(const unsigned char unit) const {
                return m_depthStencilAttachment -> bindUnit(unit) ;
            }

            /**
             * Get the size of the framebuffer in pixels.
             */
            const Mind::Dimension2Di& size() const {
                return m_size ;
            }

            /**
             * Check the status of the framebuffer.
             * @return  true if the framebuffer is complete; false otherwise.
             *          In case the framebuffer is not complete, a log message
             *          is registered.
             */
            bool isComplete() ;

            /**
             * Get the amount of color attachments.
             */
            static GLint GetColorAttachmentCount() ;

            /**
             * Get the amount of buffers that can be drawn at the same time.
             */
            static GLint GetMaxDrawBuffers() ;

            // Avoid copy/move operations.
            Framebuffer(const Framebuffer& copied) = delete ;
            Framebuffer(Framebuffer&& moved) = delete ;
            Framebuffer& operator=(const Framebuffer& copied) = delete ;
            Framebuffer& operator=(Framebuffer&& moved) = delete ;
    } ;
} ;

#endif
