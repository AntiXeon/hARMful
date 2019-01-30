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

                 bool operator==(const Rectangle& left, const Rectangle& right) {
                    return (left.x == right.x) &&
                            (left.y == right.y) &&
                            (left.width == right.width) &&
                            (left.height == right.height) ;
                }

                bool operator!=(const Rectangle& left, const Rectangle& right) {
                    return !(left == right) ;
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
                 m_rectangle.m_height = height ;
             }

         protected:
             /**
              * Apply the capability.
              */
             void apply() override {
                 enable(GL_SCISSOR_TEST) ;

                 GLint values[4] ;
                 glGetIntegerv(GL_SCISSOR_BOX, values) ;
                 m_oldRectangle.x = values[0] ;
                 m_oldRectangle.y = values[1] ;
                 m_oldRectangle.width = values[2] ;
                 m_oldRectangle.height = values[3] ;

                 if (m_rectangle != m_oldRectangle) {
                     glScissor(
                         m_rectangle.x,
                         m_rectangle.y,
                         m_rectangle.width,
                         m_rectangle.height
                     ) ;
                 }
             }

             /**
              * Remove the capability.
              */
             void remove() override {
                 if (m_rectangle != m_oldRectangle) {
                     glScissor(
                         m_oldRectangle.x,
                         m_oldRectangle.y,
                         m_oldRectangle.width,
                         m_oldRectangle.height
                     ) ;
                 }

                 disable(GL_SCISSOR_TEST) ;
             }
    } ;
}

#endif
