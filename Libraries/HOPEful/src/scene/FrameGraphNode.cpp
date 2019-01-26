#include <scene/FrameGraphNode.hpp>
#include <algorithm>
#include <cassert>

using namespace Hope ;

FrameGraphNode::FrameGraphNode(FrameGraphNode* parent) {
    if (parent) {
        bool success = parent -> addChild(this) ;

        if (success) {
            m_parent = parent ;
        }
    }
}

FrameGraphNode::~FrameGraphNode() {
    for (FrameGraphNode* child : m_children) {
        delete child ;
    }

    m_children.clear() ;
}

void FrameGraphNode::setParent(FrameGraphNode* parent) {
    if (m_parent) {
        m_parent -> removeChild(this) ;
    }

    m_parent = parent ;

    if (m_parent) {
        m_parent -> addChild(this) ;
    }
}

const FrameGraphNode* FrameGraphNode::parent() const {
    return m_parent ;
}

const std::vector<FrameGraphNode*>& FrameGraphNode::children() const {
    return m_children ;
}

void FrameGraphNode::setSceneGraphRoot(Entity* root) {
    m_sceneGraphRoot = root ;

    for (FrameGraphNode* child : m_children) {
        child -> setSceneGraphRoot(root) ;
    }
}

bool FrameGraphNode::addChild(FrameGraphNode* newChild) {
    assert(newChild != nullptr) ;

    if (newChild == this) {
        // Avoid being its own child...
        return false ;
    }

    auto posNode = std::find(m_children.begin(), m_children.end(), newChild) ;
    bool hasChild = (posNode != m_children.end()) ;

    if (!hasChild) {
        m_children.push_back(newChild) ;
        return true ;
    }

    newChild -> setSceneGraphRoot(m_sceneGraphRoot) ;

    return false ;
}

bool FrameGraphNode::removeChild(FrameGraphNode* child) {
    assert(child != nullptr) ;

    child -> setSceneGraphRoot(nullptr) ;

    auto posNode = std::find(m_children.begin(), m_children.end(), child) ;
    bool hasChild = (posNode != m_children.end()) ;

    if (hasChild) {
        m_children.erase(posNode) ;
        return true ;
    }

    return false ;
}
