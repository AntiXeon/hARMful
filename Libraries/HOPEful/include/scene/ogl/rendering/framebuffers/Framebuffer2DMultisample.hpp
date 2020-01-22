#ifndef __HOPE__GL_FRAMEBUFFER_2D_MULTISAMPLE__
#define __HOPE__GL_FRAMEBUFFER_2D_MULTISAMPLE__

#include <scene/ogl/rendering/framebuffers/Framebuffer.hpp>
#include <scene/ogl/GLDefines.hpp>
#include <scene/ogl/textures/TextureImage2DMultisample.hpp>
#include <memory>

namespace Hope::GL {
    /**
     * Framebuffer writing/reading in 2D textures supporting multisample.
     */
    class Framebuffer2DMultisample final : public Framebuffer {
        private:
            /**
             * Default amount of samples for multisampling.
             */
            static const int DefaultSampleAmount = 4 ;


            /**
             * Size of the framebuffer attachments.
             */
            Mind::Dimension2Di m_size ;

            /**
             * Amount of samples for multisampling.
             */
            int m_samples = DefaultSampleAmount ;

            /**
             * Color textures attached to the framebuffer.
             * Stores the textures associated to their attachment point.
             */
            std::vector<std::shared_ptr<TextureImage2DMultisample>> m_colorAttachments ;

            /**
             * Depth buffer attachment.
             */
            std::shared_ptr<TextureImage2DMultisample> m_depthAttachment ;

            /**
             * Stencil buffer attachment.
             */
            std::shared_ptr<TextureImage2DMultisample> m_stencilAttachment ;

            /**
             * Depth + stencil buffer attachment.
             */
            std::shared_ptr<TextureImage2DMultisample> m_depthStencilAttachment ;

        public:
            /**
             * Create a new Framebuffer2D instance.
             */
            Framebuffer2DMultisample() ;

            /**
             * Create a new Framebuffer2D instance with a predefined size.
             * @param   size    Size of the framebuffer attachments in pixels.
             */
            Framebuffer2DMultisample(
                const Mind::Dimension2Di& size,
                const int samples = DefaultSampleAmount
            ) ;

            /**
             * Resize the framebuffer.
             * @param   newSize Size of the framebuffer attachments in pixels.
             */
            void resize(const Mind::Dimension2Di& newSize) ;

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
             * @param   pixelDataFormat Unused.
             * @param   pixelDataType   Unused.
             */
            void attachColor(
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
            void attachColor(
                const unsigned char attachmentIndex,
                const std::shared_ptr<Texture> texture
            ) ;

            /**
             * Attach the depth buffer.
             */
            void attachDepth() override ;

            /**
             * Attach the depth buffer.
             * @param   texture         The external texture to attach to the
             *                          framebuffer.
             */
            void attachDepth(const std::shared_ptr<Texture> texture) ;

            /**
             * Attach the stencil buffer.
             */
            void attachStencil() override ;

            /**
             * Attach the stencil buffer.
             * @param   texture         The external texture to attach to the
             *                          framebuffer.
             */
            void attachStencil(const std::shared_ptr<Texture> texture) ;

            /**
             * Attach the combination of depth+stencil buffer.
             */
            void attachDepthStencil() override ;

            /**
             * Attach the combination of depth+stencil buffer.
             * @param   texture         The external texture to attach to the
             *                          framebuffer.
             */
            void attachDepthStencil(const std::shared_ptr<Texture> texture) ;

            /**
             * Bind the color attachment.
             */
            void bindUnitColor(const unsigned char attachmentIndex) const override {
                m_colorAttachments[attachmentIndex] -> bindUnit(attachmentIndex) ;
            }

            /**
             * Bind the depth attachment.
             */
            void bindUnitDepth(const unsigned char unit) const override {
                m_depthAttachment -> bindUnit(unit) ;
            }

            /**
             * Bind the stencil attachment.
             */
            void bindUnitStencil(const unsigned char unit) const override {
                m_stencilAttachment -> bindUnit(unit) ;
            }

            /**
             * Bind the depth+stencil attachment.
             */
            void bindUnitDepthStencil(const unsigned char unit) const override {
                m_depthStencilAttachment -> bindUnit(unit) ;
            }

            /**
             * Unbind the color attachment.
             */
            void unbindUnitColor(const unsigned char attachmentIndex) const override {
                m_colorAttachments[attachmentIndex] -> unbindUnit(attachmentIndex) ;
            }

            /**
             * Unbind the depth attachment.
             */
            void unbindUnitDepth(const unsigned char unit) const override {
                m_depthAttachment -> unbindUnit(unit) ;
            }

            /**
             * Unbind the stencil attachment.
             */
            void unbindUnitStencil(const unsigned char unit) const override {
                m_stencilAttachment -> unbindUnit(unit) ;
            }

            /**
             * Unbind the depth+stencil attachment.
             */
            void unbindUnitDepthStencil(const unsigned char unit) const override {
                m_depthStencilAttachment -> unbindUnit(unit) ;
            }

            /**
             * Get the size of the framebuffer in pixels.
             */
            const Mind::Dimension2Di& size() const {
                return m_size ;
            }

            /**
             * Get the wanted color attachment.
             * @param   attachmentIndex Attachment index.
             */
            std::shared_ptr<Texture> colorAttachment(const unsigned char attachmentIndex) const override {
                return m_colorAttachments[attachmentIndex] ;
            }

            /**
             * Get the depth attachment.
             */
            std::shared_ptr<Texture> depthAttachment() const override {
                return m_depthAttachment ;
            }

            /**
             * Get the stencil attachment.
             */
            std::shared_ptr<Texture> stencilAttachment() const override {
                return m_stencilAttachment ;
            }

            /**
             * Get the depth & stencil attachment.
             */
            std::shared_ptr<Texture> depthStencilAttachment() const override {
                return m_depthStencilAttachment ;
            }
    } ;
}

#endif
