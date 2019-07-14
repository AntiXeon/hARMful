#ifndef __HOPE__EFFECT_APPLIER_NODE__
#define __HOPE__EFFECT_APPLIER_NODE__

#include <scene/SceneTypes.hpp>
#include <scene/FrameGraphNode.hpp>
#include <scene/framegraph/deferred/effects/EffectData.hpp>
#include <string>

namespace Hope {
    /**
     * Node that is used to apply a render effect in the framegraph branch(es)
     * it is included in.
     */
    class EffectApplierNode : public FrameGraphNode {
        private:
            /**
             * Effect that is beared by the node.
             */
            EffectData* m_effect = nullptr ;

        public:
            /**
             * Create a new node instance.
             * @param   parent  Parent node of the new one.
             */
            EffectApplierNode(
                EffectData* effect,
                FrameGraphNode* parent = nullptr
            ) ;

            /**
             * Get the type of the effect.
             */
            EffectData* effect() {
                return m_effect ;
            }

        protected:
            /**
             * Accept the visitor.
             */
            void specificAccept(IFrameGraphVisitor* visitor) ;
    } ;
}

#endif
