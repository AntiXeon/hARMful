#ifndef __HOPE__SSAO_UNIFORM_SETTER__
#define __HOPE__SSAO_UNIFORM_SETTER__

#include <scene/components/materials/external/ExternalUniformSetter.hpp>
#include <scene/framegraph/deferred/effects/ao/SSAORenderNode.hpp>
#include <scene/framegraph/shading/ShaderValue.hpp>

namespace Hope {
    /**
     * Setter of uniform values for screen-space ambient occlusion related
     * stuff.
     */
    class SSAOUniformSetter final : public ExternalUniformSetter {
        private:
            /**
             * To know if ambient occlusion must be computed or not.
             */
            bool m_useAO = false ;

            /**
             * Frame graph node that contains all required data for computing
             * ambient occlusion.
             */
            const Hope::SSAORenderNode* m_ssaoNode = nullptr ;

        public:
            /**
             * Create a new SSAOUniformSetter instance.
             */
            SSAOUniformSetter() ;

            /**
             * Update the uniforms.
             */
            void updateUniforms() override ;

            /**
             * Set the frame graph node that contains all required data for
             * computing ambient occlusion.
             */
            void setSSAONode(const Hope::SSAORenderNode* node) ;
    } ;
}

#endif
