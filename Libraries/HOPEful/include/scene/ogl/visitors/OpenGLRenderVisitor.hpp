#ifndef __HOPE__OPENGL_RENDER_VISITOR__
#define __HOPE__OPENGL_RENDER_VISITOR__

#include <interfaces/visitors/scenegraph/ISceneGraphVisitor.hpp>
#include <scene/framegraph/shading/RenderTechnique.hpp>
#include <scene/framegraph/ProcessedSceneNode.hpp>
#include <scene/framegraph/RenderRequiredData.hpp>
#include <memory>
#include <set>

namespace Hope::GL {

    /**
     * Visitor for rendering objects using the OpenGL API.
     */
    class OpenGLRenderVisitor final : public ISceneGraphVisitor {
        private:
            /**
             * The ID of the current frame being rendered.
             */
            FrameID m_currentFrameID = 0 ;

            /**
             * The node that is currently processed.
             */
            Hope::ProcessedSceneNode m_processedNode ;

            /**
             * Required data for the rendering of the current frame.
             */
            RenderRequiredData m_requiredData ;

        public:
            /**
             * A new frame starts to be rendered.
             */
            void startNewFrame() ;

            /**
             * Get the current frame ID while visiting.
             */
            FrameID currentFrameID() const override ;

            /**
             * Get the require data for rendering.
             */
            RenderRequiredData& requiredData() ;

            /**
             * Set the node that is processed.
             */
            void setProcessedNode(const Hope::ProcessedSceneNode& node) override ;

            /**
             * Get the node that is processed.
             */
            Hope::ProcessedSceneNode& processedNode() override ;

            /**
             * Visit a camera component.
             */
            void visit(CameraComponent* component) override ;

            /**
             * Visit a mesh component.
             */
            void visit(MeshComponent* component) override ;

            /**
             * Visit a render configuration component.
             */
            void visit(Hope::RenderConfiguration* component) override ;

            /**
             * Visit a material component.
             */
            void visit(Material* component) override ;

        private:
            /**
             * Select the best material technique of a material. It depends on
             * the GPU supported version of the graphical API.
             */
            std::shared_ptr<RenderTechnique> selectBestMaterialTechnique(
                const std::set<std::shared_ptr<RenderTechnique>>& techniques
            ) ;
    } ;
}

#endif
