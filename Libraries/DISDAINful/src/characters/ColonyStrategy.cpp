#include "ColonyStrategy.h"

ColonyStrategy::ColonyStrategy(Pathfinding* algorithm) {
    m_algorithm = algorithm ;
    m_membersOnPath = 0 ;
}

ColonyStrategy::~ColonyStrategy() {}



bool ColonyStrategy::setGroupPath(const std::vector<StateNode*>& path) {
    if (m_membersOnPath == 0) {
        // Noone on the path, it can be changed!
        m_groupPath = path ;
        return true ;
    }
    else {
        // At least one member is using the path...
        return false ;
    }
}


void ColonyStrategy::usePath(bool use) {
    if (!use) {
        assert (m_membersOnPath > 0) ;
        m_membersOnPath-- ;
    }
    else {
        m_membersOnPath++ ;
    }
}
