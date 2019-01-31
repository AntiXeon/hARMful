#ifndef __HOPE__GL_CAPABILITY_STENCIL_TEST__
#define __HOPE__GL_CAPABILITY_STENCIL_TEST__

#include <scene/ogl/rendering/capabilities/Capability.hpp>

namespace Hope::GL {
    /**
     * Set front and/or back function and reference value for stencil testing.
     */
    class StencilTest final : public Capability {
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
                 * Possible alpha test function to apply.
                 */
                enum class StencilFunction : GLenum {
                    Never = GL_NEVER,
                    Less = GL_LESS,
                    Equal = GL_EQUAL,
                    LessOrEqual = GL_LEQUAL,
                    Greater = GL_GREATER,
                    GreaterOrEqual = GL_GEQUAL,
                    NotEqual = GL_NOTEQUAL,
                    Always = GL_ALWAYS
                } ;

                /**
                 * Specify whether front and/or back stencil state is updated.
                 */
                FaceMode face ;

                /**
                 * Stencil test function to apply.
                 */
                StencilFunction function = Always ;

                /**
                 * Specify the reference value for the stencil test.
                 */
                GLint reference = 0 ;

                /**
                 * Specify a mask that is ANDed with both the reference value
                 * and the stored stencil value when the test is done.
                 */
                GLuint mask = 0xFFFFFFFF ;
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

                glGetIntegerv(GL_STENCIL_FUNC, &(m_oldFrontFaces.function)) ;
                glGetIntegerv(GL_STENCIL_REF, &(m_oldFrontFaces.reference)) ;
                glGetIntegerv(GL_STENCIL_VALUE_MASK, &(m_oldFrontFaces.mask)) ;

                glGetIntegerv(GL_STENCIL_BACK_FUNC, &(m_oldBackFaces.function)) ;
                glGetIntegerv(GL_STENCIL_BACK_REF, &(m_oldBackFaces.reference)) ;
                glGetIntegerv(GL_STENCIL_BACK_VALUE_MASK, &(m_oldBackFaces.mask)) ;

                glStencilFuncSeparate(
                    m_frontFaces.face,
                    m_frontFaces.function,
                    m_frontFaces.reference,
                    m_frontFaces.mask
                ) ;

                glStencilFuncSeparate(
                    m_backFaces.face,
                    m_backFaces.function,
                    m_backFaces.reference,
                    m_backFaces.mask
                ) ;
            }

            /**
             * Remove the capability.
             */
            void remove() override {
                glStencilFuncSeparate(
                    m_oldFrontFaces.face,
                    m_oldFrontFaces.function,
                    m_oldFrontFaces.reference,
                    m_oldFrontFaces.mask
                ) ;

                glStencilFuncSeparate(
                    m_oldBackFaces.face,
                    m_oldBackFaces.function,
                    m_oldBackFaces.reference,
                    m_oldBackFaces.mask
                ) ;

                disable(GL_STENCIL_TEST) ;
            }
    } ;
}

#endif
