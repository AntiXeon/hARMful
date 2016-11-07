#ifndef __SIN_PARALLAX_PLANE__
#define __SIN_PARALLAX_PLANE__


#include <MINDTypes.h>
#include <main_rendering/Node.h>


namespace Sin {

    /**
     * @brief   A ParallaxPlane is a set of graphical elements. These planes are
     *          stacked on Z screen axis and move at different speed to mimic
     *          perspective.
     * @author  CB (c) 2016
     * @version 0.1     2016/02/08
     */
    class ParallaxPlane {
        private:
            /**
             * @brief   Scroll speed of the ParallaxPlane. Normal speed is defined
             *          to be 1.0f.
             */
            Mind::Scalar m_scrollSpeed ;

            /**
             * @brief   Root node of the ParallaxPlane.
             */
            Node m_root ;


        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Create a new ParallaxPlane.
             * @param   scrollSpeed Speed of scroll in percentage.
             *                      A value of 1 represents 100%, that is to say
             *                      the speed of the main parallax plane, on
             *                      which main elements are drawn (characters,
             *                      etc).
             *                      A speed between 0 and 1 is slower, more than
             *                      1 is faster. Negative values are used to
             *                      have a reverse movement.
             */
            ParallaxPlane(const Mind::Scalar& scrollSpeed = 1.f) ;

            /**
             * @brief   Destruction of the ParallaxPlane.
             */
            virtual ~ParallaxPlane() ;

                                                             /*** UTILITIES ***/
            /**
             * @brief   Update the ParallaxPlane.
             */
            void update() ;

            /**
             * @brief   Render the ParallaxPlane.
             */
            void render() ;


                                                     /*** SETTERS / GETTERS ***/
            /**
             * @brief   Set the scroll speed of the plane.
             * @param   scrollSpeed Speed of scroll in percentage.
             *                      A value of 1 represents 100%, that is to say
             *                      the speed of the main parallax plane, on
             *                      which main elements are drawn (characters,
             *                      etc).
             *                      A speed between 0 and 1 is slower, more than
             *                      1 is faster. Negative values are used to
             *                      have a reverse movement.
             */
            void setScrollSpeed(const Mind::Scalar& scrollSpeed) ;

    } ;

} ;


#endif
