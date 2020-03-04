#ifndef __HOPE__NODE__
#define __HOPE__NODE__

#include <utils/Platform.hpp>

#include <string>
#include <vector>

namespace Hope {
    /**
     * Base class for all graph structures.
     * Used to structure a parent - children relationship.
     */
    class Node {
        private:
            /**
             * Parent node.
             */
            Node* m_parent = nullptr ;

            /**
             * Children of the current node.
             */
            std::vector<Node*> m_children ;

        public:
            /**
             * Create a new node instance.
             * @param   parent  Parent node of the new one.
             */
            exported Node(Node* parent = nullptr) ;

            /**
             * Destruction of the node instance.
             */
            exported virtual ~Node() ;

            /**
             * Set the parent of the current node.
             */
            exported void setParent(Node* parent) ;

            /**
             * Get the parent of the current node.
             */
            exported const Node* parent() const ;

            /**
             * Get the list of children.
             */
            exported const std::vector<Node*>& children() const ;

            /**
             * Amount of children.
             */
            exported size_t childrenCount() const ;

            // Remove copy/move operations.
            Node(const Node& copied) = delete;
            Node(Node&& moved) = delete;
            Node& operator=(const Node& copied) = delete;
            Node& operator=(Node&& moved) = delete;

        private:
            /**
             * Add a child.
             * @param   newChild    Child node to add to the children list.
             * @return  true on success; false otherwise.
             */
            bool addChild(Node* newChild) ;

            /**
             * Remove a child.
             * @param   child       Child node to remove from the children list.
             * @return  true on success; false otherwise.
             */
            bool removeChild(Node* child) ;
    } ;
}

#endif
