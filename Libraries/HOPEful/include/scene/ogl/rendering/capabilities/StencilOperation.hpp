#ifndef __HOPE__GL_CAPABILITY_STENCIL_OPERATION__
#define __HOPE__GL_CAPABILITY_STENCIL_OPERATION__

#include <utils/Platform.hpp>

#include <scene/ogl/rendering/capabilities/Capability.hpp>

namespace Hope::GL {
    /**
     * Set front and back stencil test actions.
     */
    class StencilOperation final : public Capability {
        public:
            struct Parameters final {
                /**
                 * All possible face modes.
                 */
                enum FaceMode : GLenum {
                    Front =  GL_FRONT,
                    Back =  GL_BACK,
                    FrontAndBack =  GL_FRONT_AND_BACK
                } ;

                /**
                 * All possible operations.
                 */
                enum Operation : GLenum {
                    Keep = GL_KEEP,
                    Zero = GL_ZERO,
                    Replace =  GL_REPLACE,
                    Increment = GL_INCR,
                    IncrementWrap = GL_INCR_WRAP,
                    Decrement = GL_DECR,
                    DecrementWrap = GL_DECR_WRAP,
                    Invert = GL_INVERT
                } ;

                /**
                 * Specify whether front and/or back stencil state is updated.
                 */
                FaceMode face ;

                /**
                 * Specify the action to take when the stencil test fails.
                 */
                Operation stencilFail = Keep ;

                /**
                 * Specify the stencil action when the stencil test passes, but
                 * the depth test fails.
                 */
                Operation depthFail = Keep ;

                /**
                 * Specifies the stencil action when both the stencil test and
                 * the depth test pass, or when the stencil test passes and
                 * either there is no depth buffer or depth testing is not
                 * enabled.
                 */
                Operation success = Keep ;
            } ;

        private:
            /**
             * Front faces parameters.
             */
            Parameters m_frontFaces ;

            /**
             * Store parameters for restore.
             */
            Parameters m_oldFrontFaces ;

            /**
             * Back faces parameters.
             */
            Parameters m_backFaces ;

            /**
             * Store parameters for restore.
             */
            Parameters m_oldBackFaces ;

        public:
            /**
             * Create a new StencilOperation instance.
             */
            exported StencilOperation() : Capability(CapabilityType::StencilOperation) {}

            /**
             * Set parameters for front-facing faces.
             */
            exported void setFrontParameters(const Parameters& params) {
                m_frontFaces = params ;
                m_frontFaces.face = Parameters::FaceMode::Front ;
            }

            /**
             * Set parameters for back-facing faces.
             */
            exported void setBackParameters(const Parameters& params) {
                m_backFaces = params ;
                m_frontFaces.face = Parameters::FaceMode::Back ;
            }

        protected:
            /**
             * Apply the capability.
             */
            exported void apply() override ;

            /**
             * Remove the capability.
             */
            exported void remove() override ;
    } ;
}

#endif
