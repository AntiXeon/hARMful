#ifndef __HOPE__GL_CAPABILITY_STENCIL_OPERATION__
#define __HOPE__GL_CAPABILITY_STENCIL_OPERATION__

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
                enum class FaceMode : GLenum {
                    Front =  GL_FRONT,
                    Back =  GL_BACK,
                    FrontAndBack =  GL_FRONT_AND_BACK
                } ;

                /**
                 * All possible operations.
                 */
                enum class Operation : GLenum {
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
             * Set parameters for front-facing faces.
             */
            void setFrontParameters(const Parameters& params) {
                params.face = Parameters::FaceMode::Front ;
                m_frontFaces = params ;
            }

            /**
             * Set parameters for back-facing faces.
             */
            void setBackParameters(const Parameters& params) {
                params.face = Parameters::FaceMode::Back ;
                m_backFaces = params ;
            }

        protected:
            /**
             * Apply the capability.
             */
            void apply() override {
                enable(GL_STENCIL_TEST) ;

                glGetIntegerv(GL_STENCIL_FAIL, &(m_oldFrontFaces.stencilFail)) ;
                glGetIntegerv(GL_STENCIL_PASS_DEPTH_FAIL, &(m_oldFrontFaces.depthFail)) ;
                glGetIntegerv(GL_STENCIL_PASS_DEPTH_PASS, &(m_oldFrontFaces.success)) ;

                glGetIntegerv(GL_STENCIL_BACK_FAIL, &(m_oldBackFaces.stencilFail)) ;
                glGetIntegerv(GL_STENCIL_BACK_PASS_DEPTH_FAIL, &(m_oldBackFaces.depthFail)) ;
                glGetIntegerv( GL_STENCIL_BACK_PASS_DEPTH_PASS, &(m_oldBackFaces.success)) ;

                glStencilOpSeparate(
                    m_frontFaces.face,
                    m_frontFaces.stencilFail,
                    m_frontFaces.depthFail,
                    m_frontFaces.success
                ) ;

                glStencilOpSeparate(
                    m_backFaces.face,
                    m_backFaces.stencilFail,
                    m_backFaces.depthFail,
                    m_backFaces.success
                ) ;
            }

            /**
             * Remove the capability.
             */
            void remove() override {
                glStencilOpSeparate(
                    m_oldFrontFaces.face,
                    m_oldFrontFaces.stencilFail,
                    m_oldFrontFaces.depthFail,
                    m_oldFrontFaces.success
                ) ;

                glStencilOpSeparate(
                    m_oldBackFaces.face,
                    m_oldBackFaces.stencilFail,
                    m_oldBackFaces.depthFail,
                    m_oldBackFaces.success
                ) ;

                disable(GL_STENCIL_TEST) ;
            }
    } ;
}

#endif
