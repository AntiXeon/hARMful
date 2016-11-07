#ifndef __STATENODE_H__
#define __STATENODE_H__

#include "../../../utils/tools/Point.h"
#include <stdlib.h>
//#include <ostream>

/**
 * @brief A StateNode is a location that has several additional properties as
 * costs and parent node in a graph. It is use to determine a good path thanks
 * to pathfinding algorithms.
 * @version 1.0 10/05/2013
 */
class StateNode : public Point {
    protected:
        /** @brief Total cost of the node. */
        unsigned int m_fScore ;
        unsigned int m_gScore ;
        bool m_visited ;
        StateNode* m_parent ;
        

    public:
        /** @brief Creation of a node. */
        StateNode(unsigned short x, unsigned short y) : Point(x, y) {
            m_fScore = -1 ; // create an infinite value, better performances
            m_gScore = -1 ; // create an infinite value, better performances
            m_visited = false ;
            m_parent = 0 ;
        }

        /** @brief Destruction of a node. */
        virtual ~StateNode() {}


        unsigned int fScore() const {
            return m_fScore ;
        }

        unsigned int gScore() const {
            return m_gScore ;
        }

        bool visited() const {
            return m_visited ;
        }

        StateNode* parent() const {
            return m_parent ;
        }


        void gScore(unsigned int score) {
            m_gScore = score ;
        }

        void fScore(unsigned int score) {
            m_fScore = score ;
        }

        void visited(bool visited) {
            m_visited = visited ;
        }

        void parent(StateNode* parent) {
            m_parent = parent ;
        }


        /**
         * @brief Estimate the cost of the path from the current state to another one
         * @param s     The ending state of the path to estimate.
         */
        virtual void estimateHeuristic(StateNode* s) {
            m_fScore = m_gScore + distance(s) ;
        }

        /**
         * @brief Compute the distance between two points with different kind
         * of operations.
         */
        virtual unsigned int distance(StateNode* s) {
            const unsigned char CHOICE = rand() % 5 ;
            
            switch(CHOICE) {
                default:
                case 0:
                    return euclideanDistance(s) ;
                case 1:
                    return chebyshevDistance(s) ;
                case 2:
                    return squaredEuclideanDistance(s) ;
                case 3:
                    return manhattanDistance(s) ;
            }
        }
} ;

/** @brief Used to allow the order of StateNode pointers in a std::map or std::set. */
struct StateNodeComparator {
    bool operator() (const StateNode* a, const StateNode* b) const {
        return ((a -> fScore()) < (b -> fScore())) ;
    }
} ;

#endif
