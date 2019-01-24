#ifndef __HOPE__GL_VIEWPORT__
#define __HOPE__GL_VIEWPORT__

#include <scene/FrameGraphNode.hpp>
#include <geometry/points/Point2Df.hpp>
#include <geometry/dimensions/Dimension2Di.hpp>

namespace Hope::GL {
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
             * Dimension of the viewport in pixels.
             */
            Mind::Dimension2Di m_dimension = Mind::Dimension2Di(320, 240) ;

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
            void setDimension(Mind::Dimension2Di& dimension) {
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
            Mind::Dimension2Di dimension() {
                return m_dimension ;
            }
    } ;
}

#endif
