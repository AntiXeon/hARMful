#ifndef __HOPE__GL_CAPABILITY_SCISSOR_TEST__
#define __HOPE__GL_CAPABILITY_SCISSOR_TEST__

#include <scene/ogl/rendering/capabilities/Capability.hpp>

namespace Hope::GL {
    /**
     * Encapsulate the scissor test GL capability.
     */
    class ScissorTest final : public Capability {
         private:
             /**
              * Aggregates all the data for the scissor test rectangle data.
              */
             struct Rectangle {
                 GLint x = 0 ;
                 GLint y = 0 ;
                 GLsizei width = 0 ;
                 GLsizei height = 0 ;

                 bool operator==(const Rectangle& other) {
                    return (x == other.x) &&
                            (y == other.y) &&
                            (width == other.width) &&
                            (height == other.height) ;
                }

                bool operator!=(const Rectangle& other) {
                    return !(*this == other) ;
                }
             } ;

             /**
              * Rectangle of the scissor test with bottom left corner, width and
              * height.
              */
             Rectangle m_rectangle ;

             /**
              * Store the old rectangle data to restore it.
              */
             Rectangle m_oldRectangle ;

         public:
             /**
              * Create a new ScissorTest instance.
              */
             ScissorTest() : Capability(CapabilityType::ScissorTest) {}

             /**
              * Set the position on X axis of the bottom left corner of the
              * scissor test rectangle.
              */
             void setLeftPosition(const int left) {
                 m_rectangle.x = left ;
             }

             /**
              * Set the position on Y axis of the bottom left corner of the
              * scissor test rectangle.
              */
             void setLeftBottom(const int bottom) {
                 m_rectangle.y = bottom ;
             }

             /**
              * Set the width of the scissor test rectangle.
              */
             void setWidth(const int width) {
                 m_rectangle.width = width ;
             }

             /**
              * Set the height of the scissor test rectangle.
              */
             void setHeight(const int height) {
                 m_rectangle.height = height ;
             }

         protected:
             /**
              * Apply the capability.
              */
             void apply() override ;

             /**
              * Remove the capability.
              */
             void remove() override ;
    } ;
}

#endif
