#include <scene/Node.hpp>
#include <algorithm>
#include <cassert>

using namespace Hope ;

Node::Node(Node* parent) {
    if (parent) {
        bool success = parent -> addChild(this) ;

        if (success) {
            m_parent = parent ;
        }
    }
}

Node::~Node() {
    for (Node* child : m_children) {
        delete child ;
    }

    m_children.clear() ;
}

void Node::setParent(Node* parent) {
    if (m_parent) {
        m_parent -> removeChild(this) ;
    }

    m_parent = parent ;

    if (m_parent) {
        m_parent -> addChild(this) ;
    }
}

const Node* Node::parent() const {
    return m_parent ;
}

const std::vector<Node*>& Node::children() const {
    return m_children ;
}

bool Node::addChild(Node* newChild) {
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

    onChildAdded(newChild) ;

    return false ;
}

bool Node::removeChild(Node* child) {
    assert(child != nullptr) ;

    auto posNode = std::find(m_children.begin(), m_children.end(), child) ;
    bool hasChild = (posNode != m_children.end()) ;

    if (hasChild) {
        m_children.erase(posNode) ;
        return true ;
    }

    onChildRemoved(child) ;

    return false ;
}
