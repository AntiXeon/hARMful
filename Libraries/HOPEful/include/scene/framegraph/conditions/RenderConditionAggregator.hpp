#ifndef __HOPE__RENDER_CONDITION_AGGREGATOR__
#define __HOPE__RENDER_CONDITION_AGGREGATOR__

#include <utils/Platform.hpp>

#include <scene/framegraph/conditions/RenderCondition.hpp>

namespace Hope {
    class Entity ;

    /**
     * Aggregation of render conditions.
     * All of them are checked.
     */
    class RenderConditionAggregator {
        private:
            /**
             * List of all the render conditions.
             */
            std::vector<RenderCondition> m_conditions ;

        public:
            /**
             * Create a RenderConditionAggregator instance.
             * By default, a RenderCondition (that checks if an entity is
             * active) is pushed. No need to add it so!
             */
            exported RenderConditionAggregator() {
                RenderCondition defaultCondition ;
                m_conditions.push_back(defaultCondition) ;
            }

            /**
             * Add a condition.
             */
            exported void addCondition(const RenderCondition& condition) {
                m_conditions.push_back(condition) ;
            }

            /**
             * Check if all the conditions are respected for the provided
             * entity of the scene graph.
             */
            exported bool check(const Entity* entity) const {
                bool isChecked = true ;

                for (auto& condition : m_conditions) {
                    isChecked &= condition.check(entity) ;
                }

                return isChecked ;
            }

            /**
             * Clear all conditions.
             */
            exported void clear() {
                m_conditions.clear() ;
            }

            /**
             * Merge another aggregator into the current one.
             */
            exported void merge(const RenderConditionAggregator& other) {
                size_t totalSize = m_conditions.size() + other.m_conditions.size() ;
                m_conditions.reserve(totalSize) ;
                m_conditions.insert(
                    m_conditions.end(),
                    other.m_conditions.begin(),
                    other.m_conditions.end()
                ) ;
            }
    } ;
}

#endif
