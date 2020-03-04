#ifndef __HOPE__MEMORY_BARRIER__
#define __HOPE__MEMORY_BARRIER__

#include <utils/Platform.hpp>

#include <scene/FrameGraphNode.hpp>

namespace Hope {
    class IFrameGraphVisitor ;

    /**
     * Defines a barrier ordering memory transactions.
     */
    class MemoryBarrierNode final : public FrameGraphNode {
        private:
            /**
             * Bits of memory barriers to apply when rendering the current
             * framegraph branch.
             */
            uint32_t m_bits ;

        public:
            /**
             * Create a new MemoryBarrierNode node.
             */
            exported MemoryBarrierNode(
                const uint32_t bits,
                Hope::FrameGraphNode* parent = nullptr
            ) ;

            /**
             * Bits of the memory barrier.
             */
            exported uint32_t bits() const {
                return m_bits ;
            }

        protected:
            /**
             * Accept the visitor.
             */
            exported void specificAccept(IFrameGraphVisitor* visitor) override ;
    } ;
}

#endif
