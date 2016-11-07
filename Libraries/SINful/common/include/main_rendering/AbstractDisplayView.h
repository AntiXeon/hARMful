#ifndef __SIN_ABSTRACT_DISPLAY_VIEW__
#define __SIN_ABSTRACT_DISPLAY_VIEW__


#include <string>
#include <AbstractApplicationContext.h>
#include <main_rendering/Camera.h>
#include <main_rendering/ParallaxPlane.h>


namespace Sin {

    /**
     * @brief   Base class for defining the screens of the application.
     * @author  CB (c) 2016
     * @version 0.1     2016/02/08
     */
    class AbstractDisplayView {
        private:
            /**
             * @brief   Context of the application.
             */
            AbstractApplicationContext* m_context ;

            /**
             * @brief   Camera used to render the current screen content.
             */
            Camera* m_camera ;

            /**
             * @brief   List of the parallax planes to display layered screens.
             */
            std::vector<ParallaxPlane> m_parallax ;


        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Create a new AbstractDisplayView.
             * @param   context     Context of the application.
             * @param   camera      Camera used to render the current screen
             *                      content.
             */
            AbstractDisplayView(
                                AbstractApplicationContext* context,
                                Camera* camera = NULL
                               ) ;

            /**
             * @brief   Destruction of the AbstractDisplayView.
             */
            virtual ~AbstractDisplayView() ;

                                                             /*** UTILITIES ***/
            /**
             * @brief   Update the AbstractDisplayView.
             */
            void update() ;

            /**
             * @brief   Load the AbstractDisplayView data and related resources.
             * @warning Several views can share the same resources. In such
             *          case, resources are only loaded once.
             */
            virtual void load(const std::string& path) = 0 ;

            /**
             * @brief   Unload the direct data of the AbstractDisplayView (but
             *          not resources).
             */
            virtual void unload() = 0 ;

            /**
             * @brief   Render the content of the screen.
             */
            void render() ;


        protected:
            /**
             * @brief   Add a ParallaxPlane to the AbstractDisplayView.
             * @param   plane   The ParallaxPlane to add.
             * @warning Planes are stacked from farest to nearest.
             */
            void addParallaxPlane(const ParallaxPlane& plane) ;


                                                     /*** SETTERS / GETTERS ***/
            /**
             * @brief   Set the Camera of the AbstractDisplayView.
             * @param   camera  The Camera to define for the current
             *                  AbstractDisplayView.
             */
            void setCamera(Camera* camera) ;

            /**
             * @brief   Get the Camera used by the view.
             * @return  The Camera used to render the AbstractDisplayView.
             */
            Camera* getCamera() const ;
    } ;

} ;


#endif
