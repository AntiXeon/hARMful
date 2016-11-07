#ifndef __COLONYSTRATEGY_H__
#define __COLONYSTRATEGY_H__

    #ifdef DEBUG_MODE
        #include "../utils/LogGen.h"
    #endif

#include "ColonyStrategy.h"
#include "ai/pathfinding/Pathfinding.h"
#include "ai/pathfinding/StateNode.h"

#include <assert.h>
#include <vector>

/**
 * @brief The ColonyStrategy class defines the way the whole group can give
 * orders to each other and have a coherent group action. Members of a colony
 * share common data that they can either "read" or "write".
 * For example, when a character detects an enemy, it can tell the others the
 * position of this enemy. So, its allies can follow a common path in order to
 * help him fighting it. It depends on their own AI as they can ignore such
 * orders.
 * It can be overloaded to improve the colony strategy.
 * @version 1.0 12/05/2013
 */
class ColonyStrategy {
    protected:
        /** @brief Algorithm used by the group to find paths in the level. */
        Pathfinding* m_algorithm ;

        /**
         * @brief The group path is the path used by the members of the colony
         * that want to follow the colony strategy.
         */
        std::vector<StateNode*> m_groupPath ;

        /**
         * @brief Used to know if a member is using the path before modifying
         * it. It can be improved by modifying a position that does not
         * change anything for the characters that are on the path.
         */
        unsigned char m_membersOnPath ;

    public:
                                                            /** CONSTRUCTION **/
        /**
         * @brief Creation of a ColonyStrategy.
         * @param algorithm The algorithm used for pathfinding.
         */
        ColonyStrategy(Pathfinding* algorithm) ;

        /** @brief Destruction of a ColonyStrategy. */
        virtual ~ColonyStrategy() ;


                                                                 /** SETTERS **/
        /**
         * @brief Set the path of the group.
         * @param path      Path used by the group.
         * @return TRUE if the path is not in use by another character.
         * Yet, if a member is using the path, it is not modified and the method
         * returns FALSE.
         */
        virtual bool setGroupPath(const std::vector<StateNode*>& path) ;

        /**
         * @brief Used to allow a character to say if it is using or not the
         * path.
         * @param use   TRUE if the character uses the path, FALSE if it uses it
         *              no more.
         */
        virtual void usePath(bool use) ;


                                                                 /** GETTERS **/
        /** @brief Get the path followed by the group. */
        const std::vector<StateNode*>& getGroupPath() const {
            return m_groupPath ;
        }

        /** @brief To know if the path is used by a member of the colony. */
        virtual bool isPathUsed() {
            return (m_membersOnPath > 0) ;
        }

        /** @brief Get the algorithm used by the group to find paths. */
        Pathfinding* getAlgorithm() const {
            return m_algorithm ;
        }

        /** @brief Get the goal of the group path. */
        const Point& getGoal() {
            unsigned int lastPoint = m_groupPath.size() - 1 ;
            return *(m_groupPath[lastPoint]) ;
        }
} ;

#endif
