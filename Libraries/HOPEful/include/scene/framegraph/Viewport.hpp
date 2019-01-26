#ifndef __HOPE__GL_VIEWPORT__
#define __HOPE__GL_VIEWPORT__

#include <scene/FrameGraphNode.hpp>
#include <geometry/points/Point2Df.hpp>
#include <geometry/dimensions/Dimension2Df.hpp>

namespace Hope {
    /**
     * The viewport defines the area of the screen / window in which a 3D scene
     * is rendered.
     */
    class Viewport final : public Hope::FrameGraphNode {
        private:
            /**
             * Position of the top left corner of the viewport in pixels.
             */
            Mind::Point2Df m_position = Mind::Point2Df(0.f, 0.f) ;

            /**
             * Dimension of the viewport relatively to the window size.
             */
            Mind::Dimension2Df m_dimension = Mind::Dimension2Df(1.f, 1.f) ;

        public:
            /**
             * Create a new Viewport node.
             */
            Viewport(Hope::FrameGraphNode* parent = nullptr)
                : Hope::FrameGraphNode(parent) {}

            /**
             * Set the position of the top left corner of the viewport in
             * pixels.
             */
            void setPosition(const Mind::Point2Df& position) {
                m_position = position ;
            }

            /**
             * Set the dimension of the viewport.
             */
            void setDimension(Mind::Dimension2Df& dimension) {
                m_dimension = dimension ;
            }

            /**
             * Get the position of the top left corner of the viewport in
             * pixels.
             */
            Mind::Point2Df position() {
                return m_position ;
            }

            /**
             * Get the dimension of the viewport.
             */
            Mind::Dimension2Df dimension() {
                return m_dimension ;
            }
    } ;
}

#endif
