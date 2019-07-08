#ifndef __HOPE__TEXTURE_STORAGE_RENDER__
#define __HOPE__TEXTURE_STORAGE_RENDER__

#include <HopeAPI.hpp>

#ifdef OGL
    #include <scene/ogl/rendering/textures/TextureStorage2D.hpp>
    namespace API = Hope::GL ;
#endif

#include <scene/FrameGraphNode.hpp>
#include <scene/SceneTypes.hpp>
#include <vector>

namespace Hope {
    /**
     * Perform an off-screen render pass using a texture storage.
     */
    class TextureStorageRenderNode : public FrameGraphNode {
        friend class FrameGraphBranchState ;

        private:
            /**
             * If true, the size of the framebuffer follows the size of the
             * window. If false, the size of the framebuffer is fixed.
             */
            bool m_windowSize = true ;

            /**
             * List of the storage textures used to render the scene into.
             */
            std::vector<API::TextureStorage2D*> m_storage ;

        public:
            /**
             * Create a new TextureStorageRenderNode.
             */
            TextureStorageRenderNode(
                const Mind::Dimension2Di& size,
                const bool windowSize,
                FrameGraphNode* parent = nullptr
            ) ;

            /**
             * Destruction of the TextureStorageRenderNode.
             */
            virtual ~TextureStorageRenderNode() ;

            /**
             * If true, the size of the framebuffer follows the size of the
             * window. If false, the size of the framebuffer is fixed.
             */
            bool windowSize() const {
                return m_windowSize ;
            }

            // Avoid copy/move operations.
            TextureStorageRenderNode(const TextureStorageRenderNode& copied) = delete ;
            TextureStorageRenderNode(TextureStorageRenderNode&& moved) = delete ;
            TextureStorageRenderNode& operator=(const TextureStorageRenderNode& copied) = delete ;
            TextureStorageRenderNode& operator=(TextureStorageRenderNode&& moved) = delete ;

        protected:
            /**
             * Reserve space to stock some storage textures.
             */
            void reserveStorage(const uint8_t amount) {
                m_storage.reserve(amount) ;
            }

            /**
             * Add a storage texture.
             */
            void addStorage(API::TextureStorage2D* storage) {
                m_storage.push_back(storage) ;
            }

            /**
             * Get the storage texture at the given index.
             */
            const API::TextureStorage2D* storage(const uint8_t index) {
                return m_storage[index] ;
            }
    } ;
}

#endif
