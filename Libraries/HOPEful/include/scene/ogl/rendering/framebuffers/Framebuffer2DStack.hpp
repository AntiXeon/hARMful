#ifndef __HOPE__GL_FRAMEBUFFER_2D_STACK__
#define __HOPE__GL_FRAMEBUFFER_2D_STACK__

#include <utils/Platform.hpp>

#include <scene/ogl/rendering/framebuffers/Framebuffer.hpp>
#include <scene/ogl/GLDefines.hpp>
#include <scene/ogl/textures/TextureImage2DArray.hpp>
#include <memory>

namespace Hope::GL {
    /**
     * Framebuffer writing/reading in stack of 2D textures.
     */
    class Framebuffer2DStack final : public Framebuffer {
        private:
            /**
             * Layer to use.
             */
            GLint m_layer = -1 ;

            /**
             * Size of the framebuffer attachments.
             */
            Mind::Dimension3Di m_size ;

            /**
             * Color textures attached to the framebuffer.
             * Stores the textures associated to their attachment point.
             */
            std::vector<std::unique_ptr<TextureImage2DArray>> m_colorAttachments ;

            /**
             * Depth buffer attachment.
             */
            std::unique_ptr<TextureImage2DArray> m_depthAttachment ;

            /**
             * Stencil buffer attachment.
             */
            std::unique_ptr<TextureImage2DArray> m_stencilAttachment ;

            /**
             * Depth + stencil buffer attachment.
             */
            std::unique_ptr<TextureImage2DArray> m_depthStencilAttachment ;

        public:
            /**
             * Create a new Framebuffer2DStack instance.
             */
            exported Framebuffer2DStack() ;

            /**
             * Create a new Framebuffer2DStack instance with a predefined size.
             * @param   size    Size of the framebuffer attachments in pixels.
             */
            exported Framebuffer2DStack(const Mind::Dimension3Di& size) ;

            /**
             * Set the layer to use on attachment.
             */
            exported void setLayer(const GLint layer) {
                m_layer = layer ;
            }

            /**
             * Resize the framebuffer.
             * @param   newSize Size of the framebuffer attachments in pixels.
             */
            exported void resize(const Mind::Dimension2Di& newSize) override ;

            /**
             * Resize the framebuffer.
             * @param   newSize Size of the framebuffer attachments in pixels.
             */
            exported void resize(const Mind::Dimension3Di& newSize) ;

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
             * @param   internalFormat  Number of color components in the
             *                          texture.
             * @param   pixelDataFormat Pixel format of the attached texture.
             * @param   pixelDataType   Type of the pixels data.
             */
            exported void attachColor(
                const unsigned char attachmentIndex,
                const InternalFormat internalFormat,
                const PixelFormat pixelDataFormat,
                const PixelDataType pixelDataType
            ) override ;

            /**
             * Attach an external color texture to the framebuffer.
             * Notice that several textures can be attached to a same
             * framebuffer in order to perform multiple render target
             * operations.
             * @param   attachmentIndex Index of the attachment point to the
             *                          framebuffer. Starts at 0, you can get
             *                          the amount of color attachment with the
             *                          GetColorAttachmentCount() method.
             * @param   texture         The external texture to attach to the
             *                          framebuffer.
             */
            exported void attachColor(
                const unsigned char attachmentIndex,
                const Texture* texture
            ) override ;

            /**
             * Attach the depth buffer.
             */
            exported void attachDepth() override ;

            /**
             * Attach the depth buffer.
             * @param   texture         The external texture to attach to the
             *                          framebuffer.
             */
            exported void attachDepth(const Texture* texture) override ;

            /**
             * Attach the stencil buffer.
             */
            exported void attachStencil() override ;

            /**
             * Attach the stencil buffer.
             * @param   texture         The external texture to attach to the
             *                          framebuffer.
             */
            exported void attachStencil(const Texture* texture) override ;

            /**
             * Attach the combination of depth+stencil buffer.
             */
            exported void attachDepthStencil() override ;

            /**
             * Attach the combination of depth+stencil buffer.
             * @param   texture         The external texture to attach to the
             *                          framebuffer.
             */
            exported void attachDepthStencil(const Texture* texture) override ;

            /**
             * Bind the color attachment.
             */
            exported void bindUnitColor(const unsigned char attachmentIndex) const override {
                m_colorAttachments[attachmentIndex] -> bindUnit(attachmentIndex) ;
            }

            /**
             * Bind the depth attachment.
             */
            exported void bindUnitDepth(const unsigned char unit) const override {
                m_depthAttachment -> bindUnit(unit) ;
            }

            /**
             * Bind the stencil attachment.
             */
            exported void bindUnitStencil(const unsigned char unit) const override {
                m_depthAttachment -> bindUnit(unit) ;
            }

            /**
             * Bind the depth+stencil attachment.
             */
            exported void bindUnitDepthStencil(const unsigned char unit) const override {
                return m_depthStencilAttachment -> bindUnit(unit) ;
            }

            /**
             * Unbind the color attachment.
             */
            exported void unbindUnitColor(const unsigned char attachmentIndex) const override {
                m_colorAttachments[attachmentIndex] -> unbindUnit(attachmentIndex) ;
            }

            /**
             * Unbind the depth attachment.
             */
            exported void unbindUnitDepth(const unsigned char unit) const override {
                m_depthAttachment -> unbindUnit(unit) ;
            }

            /**
             * Unbind the stencil attachment.
             */
            exported void unbindUnitStencil(const unsigned char unit) const override {
                m_stencilAttachment -> unbindUnit(unit) ;
            }

            /**
             * Unbind the depth+stencil attachment.
             */
            exported void unbindUnitDepthStencil(const unsigned char unit) const override {
                m_depthStencilAttachment -> unbindUnit(unit) ;
            }

            /**
             * Bind a layer of the color buffer.
             */
            exported void bindColorLayer(
                const unsigned char attachmentIndex,
                const GLint layer
            ) const {
                glFramebufferTextureLayer(
                    GL_FRAMEBUFFER,
                    GL_COLOR_ATTACHMENT0 + attachmentIndex,
                    m_colorAttachments[attachmentIndex] -> id(),
                    Framebuffer::MipmapLevel,
                    layer
                ) ;
            }

            /**
             * Bind a layer of the depth buffer.
             */
            exported void bindDepthLayer(const GLint layer) const {
                glFramebufferTextureLayer(
                    GL_FRAMEBUFFER,
                    GL_DEPTH_ATTACHMENT,
                    m_depthAttachment -> id(),
                    Framebuffer::MipmapLevel,
                    layer
                ) ;
            }

            /**
             * Bind a layer of the stencil buffer.
             */
            exported void bindStencilLayer(const GLint layer) const {
                glFramebufferTextureLayer(
                    GL_FRAMEBUFFER,
                    GL_STENCIL_ATTACHMENT,
                    m_stencilAttachment -> id(),
                    Framebuffer::MipmapLevel,
                    layer
                ) ;
            }

            /**
             * Bind a layer of the depth+stencil buffer.
             */
            exported void bindDepthStencilLayer(const GLint layer) const {
                glFramebufferTextureLayer(
                    GL_FRAMEBUFFER,
                    GL_DEPTH_STENCIL_ATTACHMENT,
                    m_depthStencilAttachment -> id(),
                    Framebuffer::MipmapLevel,
                    layer
                ) ;
            }

            /**
             * Get the wanted color attachment.
             * @param   attachmentIndex Attachment index.
             */
            exported const Texture* colorAttachment(const unsigned char attachmentIndex) const override {
                return m_colorAttachments[attachmentIndex].get() ;
            }

            /**
             * Get the depth attachment.
             */
            exported const Texture* depthAttachment() const override {
                return m_depthAttachment.get() ;
            }

            /**
             * Get the stencil attachment.
             */
            exported const Texture* stencilAttachment() const override {
                return m_stencilAttachment.get() ;
            }

            /**
             * Get the depth & stencil attachment.
             */
            exported const Texture* depthStencilAttachment() const override {
                return m_depthStencilAttachment.get() ;
            }

            /**
             * Get the size of the framebuffer in pixels.
             */
            exported const Mind::Dimension3Di& size3D() const {
                return m_size ;
            }

            /**
             * Get the framebuffer width.
             */
            exported int width() const override {
                return m_size.width() ;
            }

            /**
             * Get the framebuffer height.
             */
            exported int height() const override {
                return m_size.height() ;
            }

            /**
             * Get the framebuffer depth.
             */
            exported int depth() const {
                return m_size.depth() ;
            }
    } ;
}

#endif
