#ifndef __ASTARPATHFINDING_H__
#define __ASTARPATHFINDING_H__

#include "Pathfinding.h"
#include "../LevelMap2D.h"
#include "../Point.h"

#include <vector>

#include <iostream>
using namespace std ;

class AStarPathfinding {
    protected:
        /** @brief Nodes on the followed path. */
        std::vector<StateNode*> m_cameFrom ;

        /** @brief Level map used by the algorithm. */
        LevelMap2D* m_map ;

        /** @brief Maximal distance from the start before giving up. */
        unsigned short m_maxDistance ;

    public:
                                                            /** CONSTRUCTION **/
        /**
         * @brief Creation of a AStarPathfinding object.
         * @param map           The map on which the algorithm runs.
         * @param maxDistance   Maximal distance to parse before giving up.
         */
        AStarPathfinding(LevelMap2D* map, unsigned short maxDistance) {
            m_map = map ;
            m_maxDistance = maxDistance ;
        }

        /** @brief Destruction of a AStarPathfinding object. */
        virtual ~AStarPathfinding() {}

        /** @brief Run the algorithm. */
        virtual void run() ;

        /** @brief Replan the objective of the algorithm. */
        virtual void replan() {
            cout << "REPLAN" << endl ;

//            m_createdNodes.clear() ;
//            m_current = 0 ;
//            m_goal = 0 ;
        }

        virtual void setStart(unsigned short x, unsigned short y) {
            m_current = new StateNode(x, y) ;

            m_created[m_current -> hash()] = m_current ;
            m_created.clear() ;
        }

    protected:
        /** @brief Initialize the algorithm. */
        virtual void initialize() ;


        /** @brief Process the neighbors of a state. */
        virtual void processNeighbors(StateNode* s) {
            // Get the ranges of the neighbors on S.
            Point min, max ;
            getNeighbors(s, min, max) ;
            unsigned int gParent = s -> gScore() ;
            unsigned int nextStepCost ;

            StateNode* neighbor ;
            unsigned int hash ;    // Used to identify the already created nodes
            for (unsigned short h = min.getY() ; h < max.getY() ; h++) {
                for (unsigned short w = min.getX() ; w < max.getX() ; w++) {
                    if (!(m_map -> isObstacle(w, h))) {
                        hash = Point(w, h).hash() ;

                        if (m_createdNodes.count(hash) == 0) {
                            // If the hash is not in the nodes, create it!
                            neighbor = new StateNode(w, h) ;
                            m_createdNodes.insert(std::pair<unsigned int, StateNode*>(hash, neighbor)) ;
                        }
                        else {
                            // Else, get it!
                            neighbor = m_createdNodes[hash] ;
                        }

                        // Search for the neighbor having the lowest cost
                        nextStepCost = gParent + (s -> distance(neighbor)) ;
                        if (nextStepCost < (neighbor -> gScore())) {
                            // Remove the neighbor from Open / Closed
                            if (m_open.count(neighbor) > 0)
                                m_open.erase(neighbor) ;
                            
                            if (m_closed.count(neighbor) > 0)
                                m_closed.erase(neighbor) ;
                        }

                        // Neighbor is neither in Open nor in Closed
                        if (!m_open.count(neighbor) && !m_closed.count(neighbor)) {
                            neighbor -> gScore(nextStepCost) ;
                            neighbor -> estimateHeuristic(m_goal) ;
                            m_open.insert(neighbor) ;
                        }
                    }
                }
            }
        }

        /**
         * @brief Get the neighbors coordinates of a state in respect of the map
         * bounds.
         * @param s     The state for which the neighbors are looked for.
         * @param min   Reference to the point representing the minimal coordinates.
         * @param max   Reference to the point representing the maximal coordinates.
         */
        virtual void getNeighbors(StateNode* s, Point& min, Point& max) {
            // Get the location of the StateNode
            unsigned short x = s -> getX() ;
            unsigned short y = s -> getY() ;

            // Get the dimensions of the map
            unsigned short mapWidth = m_map -> getWidth() ;
            unsigned short mapHeight = m_map -> getHeight() ;

            /* Compute the position of the surrounding states in respect of the
             * map bounds */
            unsigned short minX = (x == 0) ? 0 : x - 1 ;
            unsigned short minY = (y == 0) ? 0 : y - 1 ;
            unsigned short maxX = (x == mapWidth - 1) ? x : x + 1 ;
            unsigned short maxY = (y == mapHeight - 1) ? y : y + 1 ;

            min = Point(minX, minY) ;
            max = Point(maxX, maxY) ;
        }
} ;

#endif
