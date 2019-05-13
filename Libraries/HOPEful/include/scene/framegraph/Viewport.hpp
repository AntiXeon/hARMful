#ifndef __HOPE__VIEWPORT__
#define __HOPE__VIEWPORT__

#include <scene/FrameGraphNode.hpp>
#include <geometry/points/Point2Df.hpp>
#include <geometry/dimensions/Dimension2Df.hpp>
#include <algorithm>

namespace Hope {
    /**
     * The viewport defines the area of the screen / window in which a 3D scene
     * is rendered.
     */
    class Viewport final : public FrameGraphNode {
        private:
            /**
             * Position of the top left corner of the viewport in relative value
             * (between 0 and 1).
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
             * relative value (between 0 and 1).
             */
            void setPosition(const Mind::Point2Df& position) {
                const float MinValue = 0.f ;
                const float MaxValue = 1.f ;

                float x = std::clamp(position.get(Mind::Point2Df::X), MinValue, MaxValue) ;
                float y = std::clamp(position.get(Mind::Point2Df::Y), MinValue, MaxValue) ;
                m_position.set(x, y) ;
            }

            /**
             * Set the dimension of the viewport.
             */
            void setDimension(const Mind::Dimension2Df& dimension) {
                const float MinValue = 0.f ;
                const float MaxValue = 1.f ;

                float w = std::clamp(dimension.width(), MinValue, MaxValue) ;
                float h = std::clamp(dimension.height(), MinValue, MaxValue) ;
                m_dimension.set(w, h) ;
            }

            /**
             * Get the position of the top left corner of the viewport in
             * relative value (between 0 and 1).
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

        protected:
            /**
             * Accept the visitor.
             */
            void specificAccept(IFrameGraphVisitor* visitor) override {
                visitor -> visit(this) ;
            }
    } ;
}

#endif
