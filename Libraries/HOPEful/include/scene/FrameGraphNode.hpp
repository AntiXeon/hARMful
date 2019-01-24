#ifndef __HOPE__FRAMEGRAPH_NODE__
#define __HOPE__FRAMEGRAPH_NODE__

#include <string>
#include <vector>

namespace Hope {
    /**
     * Base of nodes for the frame graph.
     * The frame graph can be used to make rendering passes, layers, post-prod
     * effects, etc.
     * The FrameGraphNode is usually not used as is in a frame graph as it does
     * nothing. However it can interesting to create a group of nodes in a
     * hierarchy.
     */
    class FrameGraphNode
    {
        private:
            /**
             * Parent node.
             */
            FrameGraphNode* m_parent = nullptr ;

            /**
             * Children of the current node.
             */
            std::vector<FrameGraphNode*> m_children ;

        public:
            /**
             * Create a new node instance.
             * @param   parent  Parent node of the new one.
             */
            FrameGraphNode(FrameGraphNode* parent = nullptr) ;

            /**
             * Destruction of the node instance.
             */
            virtual ~FrameGraphNode() ;

            /**
             * Run processing of the frame graph node.
             * It is recursively called for each of the node children.
             */
            void process() ;

            /**
             * Set the parent of the current node.
             */
            void setParent(FrameGraphNode* parent) ;

            /**
             * Get the parent of the current node.
             */
            const FrameGraphNode* parent() const ;

            /**
             * Get the list of children.
             */
            const std::vector<FrameGraphNode*>& children() const ;

            // Remove copy/move operations.
            FrameGraphNode(const FrameGraphNode& copied) = delete;
            FrameGraphNode(FrameGraphNode&& moved) = delete;
            FrameGraphNode& operator=(const FrameGraphNode& copied) = delete;
            FrameGraphNode& operator=(FrameGraphNode&& moved) = delete;

        protected:
            /**
             * Internal implementation of the frame graph node processing.
             */
            virtual void internalProcess() ;

        private:
            /**
             * Add a child.
             * @param   newChild    Child node to add to the children list.
             * @return  true on success; false otherwise.
             */
            bool addChild(FrameGraphNode* newChild) ;

            /**
             * Remove a child.
             * @param   child       Child node to remove from the children list.
             * @return  true on success; false otherwise.
             */
            bool removeChild(FrameGraphNode* child) ;
    };
}

#endif
