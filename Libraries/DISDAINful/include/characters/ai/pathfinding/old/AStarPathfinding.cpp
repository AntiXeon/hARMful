#include "AStarPathfinding.h"

using namespace std ;

void AStarPathfinding::initialize() {
cout << "INIT: " << m_current << endl ;
    m_closed.clear() ;
    m_cameFrom.clear() ;
    m_open.insert(m_current) ;

    // Starting point
    m_current -> gScore(0) ;
    m_current -> estimateHeuristic(m_goal) ;
}


void AStarPathfinding::run() {
cout << "RUN" << endl ;
    initialize() ;
//    while(!m_open.empty()) {
        // Get the node having the lowest f score and remove it from the open list

        m_current = *(m_open.begin()) ;
//        m_open.erase(m_open.begin()) ;

//        // The algorithm stops if the current node is the goal (empty set of nodes)
//        if (m_current != m_goal) {
//            m_closed.insert(m_current) ;
//            processNeighbors(m_current) ;
//        }
//    }
}
