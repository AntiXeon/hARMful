#ifndef __HOPE__EFFECT_FRAMEGRAPH_NODE__
#define __HOPE__EFFECT_FRAMEGRAPH_NODE__

#include <utils/Platform.hpp>

#include <scene/SceneTypes.hpp>
#include <scene/FrameGraphNode.hpp>
#include <string>

namespace Hope {
    class EffectData ;

    /**
     * Base class for nodes dedicated to rendering effects.
     */
    class EffectFrameGraphNode : public FrameGraphNode {
        public:
            /**
             * Create a new node instance.
             * @param   parent  Parent node of the new one.
             */
            exported EffectFrameGraphNode(FrameGraphNode* parent = nullptr)
                : FrameGraphNode(parent) {}

            /**
             * Get the type of the effect.
             */
            exported virtual EffectNodeType effectType() const = 0 ;

            /**
             * Get the effect data of the node.
             */
            exported virtual EffectData* data() = 0 ;
    } ;
}

#endif
