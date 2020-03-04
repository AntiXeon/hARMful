#ifndef __HOPE__CLEAR_BUFFERS__
#define __HOPE__CLEAR_BUFFERS__

#include <utils/Platform.hpp>

#include <scene/FrameGraphNode.hpp>
#include <HopeAPI.hpp>

#ifdef OGL
    #include <scene/ogl/rendering/BufferClearer.hpp>
    namespace API = Hope::GL ;
#endif

namespace Hope {
    class IFrameGraphVisitor ;

    /**
     * Clear one or several buffers.
     */
    class ClearBuffersNode final : public FrameGraphNode {
        private:
            /**
             * The buffers to clear.
             */
            API::BufferClearer::Buffer m_buffers ;

        public:
            /**
             * Create a new ClearBuffersNode.
             */
            exported ClearBuffersNode(
                const API::BufferClearer::Buffer buffers,
                Hope::FrameGraphNode* parent = nullptr
            ) : FrameGraphNode(parent),
                m_buffers(buffers) {}

            /**
             * The buffers to clear.
             */
            exported API::BufferClearer::Buffer buffers() {
                return m_buffers ;
            }

        protected:
            /**
             * Accept the visitor.
             */
            void specificAccept(IFrameGraphVisitor* visitor) override ;
    } ;
}

#endif
