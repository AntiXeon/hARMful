#ifndef __PATHFINDING_H__
#define __PATHFINDING_H__

#include "StateNode.h"
#include "../../../utils/tools/LevelMap2D.h"

#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>


#include <iostream>
using namespace std ;

// @TODO make it as an interface and implement it in AStarPathfinding
/**
 * @brief Class to allow the creation of pathfinding algorithms. It is done to
 * make the characters move from a location to another one, avoiding obstacles
 * and most expensive paths (traps, etc).
 * @version 1.0 10/05/2013
 */
class Pathfinding {
    protected:
        /** @brief List of the nodes to process. */
        std::set<StateNode*, StateNodeComparator> m_open ;

        /** @brief List of the processed nodes. */
        std::unordered_set<StateNode*> m_closed ;

        /** @brief Representation of the map of created nodes <hash, node>. */
        std::unordered_map<unsigned int, StateNode*> m_created ;

        /** @brief Nodes on the followed path. */
        std::vector<StateNode*> m_path ;

        /** @brief The point to go. */
        StateNode* m_goal ;

        /** @brief The current node. */
        StateNode* m_current ;

        /** @brief Level map used by the algorithm. */
        LevelMap2D* m_map ;


    public:
                                                            /** CONSTRUCTION **/
        /**
         * @brief Creation of a Pathfinding object.
         * @param map   The 2D map on which the pathfinding algorithm is run.
         */
        Pathfinding(LevelMap2D* map) {
            assert(map != 0) ;
            
            m_map = map ;

            m_current = 0 ;
            m_goal = 0 ;
        }

        /** @brief Destruction of a Pathfinding object. */
        virtual ~Pathfinding() {}


                                                                 /** SETTERS **/
        void setStart(unsigned short x, unsigned short y) {
//            if (m_current != 0)
//                delete m_current ;

            m_current = new StateNode(x, y) ;
            unsigned int hash = m_current -> hash() ;
            m_created[hash] = m_current ;
        }

        void setGoal(unsigned short x, unsigned short y) {
//            if (m_goal != 0)
//                delete m_goal ;

            m_goal = new StateNode(x, y) ;
            unsigned int hash = m_goal -> hash() ;
            m_created[hash] = m_goal ;
        }

        /**
         * @brief Change the map.
         * @param map   The 2D map on which the pathfinding algorithm is run.
         */
        void changeMap(LevelMap2D* map) {
            assert(map != 0) ;
            m_map = map ;
        }


                                                               /** ALGORITHM **/
        /** @brief Replan the objective of the algorithm. */
        virtual void replan() {
            m_created.clear() ;
            m_current = 0 ;
            m_goal = 0 ;
        }

        /** @brief Run the algorithm. */
        virtual void run() ;

        /** @brief Get the found path. */
        virtual const std::vector<StateNode*>& getPath() {
            return m_path ;
        }


    protected:
        /** @brief Initialize the algorithm. */
        virtual void initialize() ;

        /** @brief Construct the path from the closed list. */
        virtual void makePath() ;

        /** @brief Process the neighbors of a state. */
        virtual void processNeighbors(StateNode* s) {
            // Get the ranges of the neighbors on S.
            Point min, max ;
            getNeighbors(s, min, max) ;
            unsigned short maxY = max.getY() + 1 ;
            unsigned short maxX = max.getX() + 1 ;
            unsigned int gParent = s -> gScore() ;
            unsigned int nextStepCost = 0 ;

            StateNode* neighbor ;
            unsigned int hash ;    // Used to identify the already created nodes
            for (unsigned short h = min.getY() ; h < maxY ; h++) {
                for (unsigned short w = min.getX() ; w < maxX ; w++) {
                    if ((w != (s -> getX()) || h != (s -> getY()))
                            && !(m_map -> isObstacle(w, h))) {
                        // Do not consider the node itself + avoid obstacles
                        
                        // First, get the corresponding neighbor!
                        hash = Point(w, h).hash() ;
                        if (m_created.count(hash) == 0) {
                            // If the hash is not in the nodes, create it!
                            neighbor = new StateNode(w, h) ;
                            m_created[hash] = neighbor ;
                        }
                        else
                            // Else, get it!
                            neighbor = m_created[hash] ;


                        // Now, test this neighbor :-)
                        if (!m_closed.count(neighbor)) {
                            // If the node is not in the Closed list

                            if (m_open.count(neighbor)) {
                                // If already in the Open list

                                // Search for the neighbor having the lowest cost
                                nextStepCost = gParent + (s -> distance(neighbor)) ;
                                if (nextStepCost < (neighbor -> fScore())) {
                                    neighbor -> gScore(nextStepCost) ;
                                    neighbor -> estimateHeuristic(m_goal) ;
                                    neighbor -> parent(s) ;

                                    // Update the node in the Open list
                                    m_open.erase(neighbor) ;
                                    m_open.insert(neighbor) ;
                                }
                            }
                            else {
                                // If not already in the list, add it!
                                m_open.insert(neighbor) ;
                            }
                        }
                        

//                        // Search for the neighbor having the lowest cost
//                        nextStepCost = gParent + (s -> distance(neighbor)) ;

//                        if (nextStepCost < (neighbor -> gScore())) {
//                            // Remove the neighbor from Open / Closed
//                            if (m_open.count(neighbor))
//                                m_open.erase(neighbor) ;

//                            if (m_closed.count(neighbor)) 
//                                m_closed.erase(neighbor) ;
//                        }

//                        // Neighbor is neither in Open nor in Closed
//                        if (!m_open.count(neighbor) && !m_closed.count(neighbor)) {
//                            neighbor -> gScore(nextStepCost) ;
//                            neighbor -> estimateHeuristic(m_goal) ;
//                            neighbor -> parent(s) ;
//                            m_open.insert(neighbor) ;
//                        }
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
