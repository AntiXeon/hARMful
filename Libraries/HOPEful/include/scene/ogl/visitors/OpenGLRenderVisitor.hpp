#ifndef __HOPE__OPENGL_RENDER_VISITOR__
#define __HOPE__OPENGL_RENDER_VISITOR__

#include <interfaces/visitors/scenegraph/ISceneGraphVisitor.hpp>
#include <scene/framegraph/shading/RenderTechnique.hpp>
#include <scene/framegraph/ProcessedSceneNode.hpp>
#include <scene/framegraph/RenderRequiredData.hpp>
#include <memory>
#include <set>

namespace Hope {
    class MaterialComponent ;
}

namespace Hope::GL {
    class BaseGLSLDataUBO ;
    class ModelGLSLDataUBO ;

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

            /**
             * UBO containing the base data for GLSL shaders.
             * Its binding point index is set to 0.
             */
            BaseGLSLDataUBO* m_baseUBO = nullptr ;

            /**
             * UBO containing the base data of a model for GLSL shaders.
             */
            ModelGLSLDataUBO* m_modelUBO = nullptr ;

        public:
            /**
             * A new frame starts to be rendered.
             */
            void startNewFrame() ;

            /**
             * Get the current frame ID while visiting.
             */
            FrameID currentFrameID() const override {
                return m_currentFrameID ;
            }

            /**
             * Get the require data for rendering.
             */
            RenderRequiredData& requiredData() override {
                return m_requiredData ;
            }

            /**
             * Set the node that is processed.
             */
            void setProcessedNode(const Hope::ProcessedSceneNode& node) override ;

            /**
             * Get the node that is processed.
             */
            Hope::ProcessedSceneNode& processedNode() override {
                return m_processedNode ;
            }

            /**
             * Set the UBOs to be used for rendering.
             * @warning Call setProcessedNode() before!
             */
            void setUBOs(
                BaseGLSLDataUBO* baseUBO,
                ModelGLSLDataUBO* modelUBO
            ) ;

            /**
             * Visit a mesh geometry component.
             */
            void visit(MeshGeometryComponent* component) override ;

            /**
             * Visit a test component.
             */
            void visit(TriangleTestComponent* component) override ;

        private:
            /**
             * Use a material component.
             */
            void useMaterial(const Hope::MaterialComponent* component) ;

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
