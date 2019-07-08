#ifndef __HOPE__EFFECT_FRAMEGRAPH_NODE__
#define __HOPE__EFFECT_FRAMEGRAPH_NODE__

#include <scene/SceneTypes.hpp>
#include <scene/FrameGraphNode.hpp>
#include <string>

namespace Hope {
    /**
     * Base class for nodes dedicated to rendering effects.
     */
    class EffectFrameGraphNode : public FrameGraphNode {
        public:
            /**
             * Create a new node instance.
             * @param   parent  Parent node of the new one.
             */
            EffectFrameGraphNode(FrameGraphNode* parent = nullptr)
                : FrameGraphNode(parent) {}

            /**
             * Get the type of the effect.
             */
            virtual EffectNodeType effectType() const = 0 ;
    } ;
}

#endif
