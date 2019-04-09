#ifndef __HOPE__ISCENEGRAPHVISITOR__
#define __HOPE__ISCENEGRAPHVISITOR__

#include <scene/SceneTypes.hpp>

namespace Hope {
    class MeshComponent ;
    class Material ;
    class TriangleTestComponent ;

    class ProcessedSceneNode ;
    class RenderRequiredData ;

    /**
     * Interface for the Visitor design pattern for objects inside the scene
     * graph.
     */
    class ISceneGraphVisitor {
        public:
            /**
             * Get the current frame ID while visiting.
             */
            virtual FrameID currentFrameID() const = 0 ;

            /**
             * Set the node that is processed.
             */
            virtual void setProcessedNode(const Hope::ProcessedSceneNode& node) = 0 ;

            /**
             * Get the node that is processed.
             */
            virtual Hope::ProcessedSceneNode& processedNode() = 0 ;

            /**
             * Get the require data for rendering.
             */
            virtual RenderRequiredData& requiredData() = 0 ;

            /**
             * Visit a mesh component.
             */
            virtual void visit(Hope::MeshComponent* component) = 0 ;

            /**
             * Visit a material component.
             */
            virtual void visit(Material* component) = 0 ;

            /**
             * Visit a test component.
             */
            virtual void visit(TriangleTestComponent* component) = 0 ;
    } ;
}

#endif
