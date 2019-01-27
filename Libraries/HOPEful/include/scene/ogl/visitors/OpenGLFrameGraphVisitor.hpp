#ifndef __HOPE__OPENGL_FRAMEGRAPH_VISITOR__
#define __HOPE__OPENGL_FRAMEGRAPH_VISITOR__

#include <interfaces/visitors/framegraph/IFrameGraphVisitor.hpp>
#include <geometry/dimensions/Dimension2Df.hpp>
#include <algorithm>

namespace Hope::GL {
    /**
     * Visitor for processing frame graph nodes.
     */
    class OpenGLFrameGraphVisitor final : public IFrameGraphVisitor {
        private:
            /**
             * Size of the window.
             */
            Mind::Dimension2Df m_windowSize ;

        public:
            /**
             * Set the window size.
             */
            void setWindowSize(const Mind::Dimension2Df& size) {
                m_windowSize = size ;

                if (m_windowSize.height() < 1.f) {
                    m_windowSize.setHeight(1.f) ;
                }
            }

            /**
             * Get the window size.
             */
            Mind::Dimension2Df windowSize() const {
                return m_windowSize ;
            }

            /**
             * Visit a camera node.
             */
            void visit(ActiveCamera* node) override ;

            /**
             * Visit a frustum culling node.
             */
            void visit(FrustumCulling* node) override ;

            /**
             * Visit a viewport node.
             */
            void visit(Viewport* node) override ;
    } ;
}

#endif
