#include <scene/Node.hpp>
#include <cassert>

namespace Hope {
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

        for (Node* existingChild : m_children) {
            // Avoid listing several times the same node.
            if (existingChild == newChild) {
                return false ;
            }
        }

        m_children.push_back(newChild) ;
        return true ;
    }

    bool Node::removeChild(Node* child) {
        assert(child != nullptr) ;

        for (auto it = m_children.begin() ; it != m_children.end() ; ++it) {
            if (*it == child) {
                m_children.erase(it) ;
                return true ;
            }
        }

        return false ;
    }
}
