#ifndef __HOPE__VIEWPORT__
#define __HOPE__VIEWPORT__

#include <utils/Platform.hpp>

#include <scene/FrameGraphNode.hpp>
#include <geometry/points/Point2Df.hpp>
#include <geometry/dimensions/Dimension2Df.hpp>
#include <algorithm>

namespace Hope {
    class IFrameGraphVisitor ;

    /**
     * The viewport defines the area of the screen / window in which a 3D scene
     * is rendered.
     */
    class ViewportNode final : public FrameGraphNode {
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
             * Create a new ViewportNode node.
             */
            exported ViewportNode(Hope::FrameGraphNode* parent = nullptr)
                : Hope::FrameGraphNode(parent) {}

            /**
             * Set the position of the top left corner of the viewport in
             * relative value (between 0 and 1).
             */
            exported void setPosition(const Mind::Point2Df& position) ;

            /**
             * Set the dimension of the viewport.
             */
            exported void setDimension(const Mind::Dimension2Df& dimension) ;

            /**
             * Get the position of the top left corner of the viewport in
             * relative value (between 0 and 1).
             */
            exported Mind::Point2Df position() {
                return m_position ;
            }

            /**
             * Get the dimension of the viewport.
             */
            exported Mind::Dimension2Df dimension() {
                return m_dimension ;
            }

        protected:
            /**
             * Accept the visitor.
             */
            exported void specificAccept(IFrameGraphVisitor* visitor) override ;
    } ;
}

#endif
