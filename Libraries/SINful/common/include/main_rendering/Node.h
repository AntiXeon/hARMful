#ifndef __SIN_NODE__
#define __SIN_NODE__


#include <vector>
#include <scene_objects/AbstractSceneObject.h>
#include <transitions/AbstractTransition.h>


namespace Sin {

    /**
     * @brief   A Node helps at defining a hierarchy in graphical elements.
     * @author  CB (c) 2016
     * @version 0.1     2016/02/08
     */
    class Node {
        private:
            /**
             * @brief   Parent of the Node in the tree hierarchy.
             */
            Node* m_parent ;

            /**
             * @brief   Object linked to the Node that can be displayed on
             *          screen.
             */
            AbstractSceneObject* m_object ;

            /**
             * @brief   List of related Nodes in the tree hierarchy.
             */
            std::vector<Node*> m_children ;
            typedef std::vector<Node*>::iterator ChildrenIterator ;

            /**
             * @brief   List of transitions to provide soft change in different
             *          Node properties.
             */
            std::vector<AbstractTransition*> m_transitions ;


        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Create a new Node.
             * @param   parent  Parent Node of the current Node. If NULL, the
             *                  Node is seen as a root.
             * @param   object  Graphical content of the Node.
             */
            Node(Node* parent = NULL, AbstractSceneObject* object = NULL) ;

            /**
             * @brief   Destruction of the Node.
             * @warning Delete all the children of the Node and its linked
             *          object.
             */
            virtual ~Node() ;

                                                             /*** UTILITIES ***/
            /**
             * @brief   Append a child to the current Node.
             * @param   child                   The child Node to link to the
             *                                  current Node.
             */
            void appendChild(Node* child) ;

            /**
             * @brief   Remove a child Node from the current one.
             * @param   child   Child to remove.
             * @warning The @a child Node must be contained in the children
             *          list. If not, nothing is fine, yet an error is returned.
             * @warning The children of the Node are not removed, they still
             *          attached to the @a child Node.
             * @return  0 on success, 1 if the given child is not found.
             */
            int removeChild(Node* child) ;

            /**
             * @brief   Remove all the children from the current Node.
             */
            void removeAllChildren() ;


            /**
             * @brief   Update the Node.
             */
            void update() ;

            /**
             * @brief   Render the Node and call the rendering of its direct
             *          children.
             */
            void render() ;


        private:
            /**
             * @brief   Get the root Node of the hierarchy.
             * @return  The root Node instance.
             */
            Node* getRoot() ;


        public:
                                                     /*** SETTERS / GETTERS ***/
            /**
             * @brief   Get the patent of the current Node.
             * @return  Parent of the current Node.
             */
            Node* getParent() const ;
    } ;

} ;


#endif
