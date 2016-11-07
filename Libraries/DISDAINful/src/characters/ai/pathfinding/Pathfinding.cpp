#include "Pathfinding.h"


#include <iostream>
using namespace std ;

void Pathfinding::initialize() {
    m_path.clear() ;
    m_open.clear() ;
    m_closed.clear() ;
    m_current -> parent(0) ;
    m_open.insert(m_current) ;

    // Starting point
    m_current -> gScore(0) ;
    m_current -> estimateHeuristic(m_goal) ;
}


void Pathfinding::run() {
    initialize() ;

    bool found = false ;
    while(!m_open.empty() && !found) {
        // Get the node having the lowest f score and remove it from the open list
        
        m_current = *(m_open.begin()) ;
        m_open.erase(m_open.begin()) ;

        // The algorithm stops if the current node is the goal (empty set of nodes)
        if (m_current != m_goal) {
            m_closed.insert(m_current) ;
            processNeighbors(m_current) ;
        }
        else
            found = true ;
    }

    if (found)
        makePath() ;
}

void Pathfinding::makePath() {
    StateNode* node = m_goal ;

    while (node != 0) {
        m_path.insert(m_path.begin(), node) ;
        node = node -> parent() ;
    }
}
