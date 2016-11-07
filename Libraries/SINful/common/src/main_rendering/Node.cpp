#include <main_rendering/Node.h>


#define HAS_NO_ERROR    0
#define HAS_ERROR       1


namespace Sin {
                                              /** CONSTRUCTION / DESTRUCTION **/
    Node::Node(Node* parent, AbstractSceneObject* object)
        : m_parent(parent), m_object(object) {}

    Node::~Node() {
        ChildrenIterator itChildren = m_children.begin() ;
        for (; itChildren != m_children.end() ; ++itChildren) {
            delete (*itChildren) ;
        }
        m_children.clear() ;

        if (m_object != NULL) {
            delete m_object ;
        }
    }

                                                             /*** UTILITIES ***/
    void Node::appendChild(Node* child) {
        if (child != NULL) {
            Node* previousParent = child -> m_parent ;

            // Detach the node from its parent and cut the link of previous
            // hierarchy.
            if (previousParent != this) {
                if (previousParent != NULL) {
                    previousParent -> removeChild(child) ;
                }

                // Put the child Node as direct child of the current Node.
                child -> m_parent = this ;
                m_children.push_back(child) ;
            }
        }
    }

    int Node::removeChild(Node* child) {
        if ((child -> m_parent) != this) {
            // The current Node is not the parent of the child (or the parent is
            // NULL...).
            return HAS_ERROR ;
        }
        else {
            // The child Node is really a child of the current Node.
            child -> m_parent = getRoot() ;
            // Search the position of the child to remove it in the list.
            ChildrenIterator itChildren = m_children.begin() ;
            for (; itChildren != m_children.end() ; ++itChildren) {
                Node* currentChild = (*itChildren) ;

                if (currentChild == child) {
                    m_children.erase(itChildren) ;
                    return HAS_NO_ERROR ;
                }
            }
        }

        return HAS_ERROR ;
    }

    void Node::removeAllChildren() {
        Node* rootNode = getRoot() ;

        ChildrenIterator itChildren = m_children.begin() ;
        for (; itChildren != m_children.end() ; ++itChildren) {
            // Remove the parent of the Node.
            Node* currentChild = (*itChildren) ;
            currentChild -> m_parent = rootNode ;
        }
        m_children.clear() ;
    }


    void Node::update() {
        if (m_object != NULL) {
            m_object -> update() ;
        }

        // Update the children.
        ChildrenIterator itChildren = m_children.begin() ;
        for (; itChildren != m_children.end() ; ++itChildren) {
            Node* currentChild = (*itChildren) ;
            currentChild -> update() ;
        }
    }

    void Node::render() {
        if (m_object != NULL) {
            m_object -> render() ;
        }

        // Update the children.
        ChildrenIterator itChildren = m_children.begin() ;
        for (; itChildren != m_children.end() ; ++itChildren) {
            Node* currentChild = (*itChildren) ;
            currentChild -> render() ;
        }
    }


    Node* Node::getRoot() {
        Node* currentNode = this ;
        Node* parentNode = m_parent ;

        while (parentNode != NULL) {
            currentNode = parentNode ;
            parentNode = currentNode -> m_parent ;
        }

        return currentNode ;
    }


    Node* Node::getParent() const {
        return m_parent ;
    }

} ;
