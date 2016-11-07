#ifndef __SIN_ABSTRACT_WINDOW__
#define __SIN_ABSTRACT_WINDOW__


#include <string>
#include <AbstractApplicationContext.h>
#include <main_rendering/AbstractViewport.h>


namespace Sin {

    /**
     * @brief   Base class for creation of a window containing graphical
     *          content (2D and/or 3D).
     * @author  CB (c) 2016
     * @version 0.1     2016/02/07
     */
    class AbstractWindow {
        private:
            /**
             * @brief   Viewport of the AbstractWindow.
             *          The viewport is used to render the content of the
             *          window.
             */
            AbstractViewport* m_viewport ;


        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Create a new AbstractWindow.
             */
            AbstractWindow() ;

            /**
             * @brief   Destruction of the AbstractWindow.
             */
            virtual ~AbstractWindow() ;

                                                             /*** UTILITIES ***/
            /**
             * @brief   Refresh the AbstractWindow.
             *          This makes its AbstractViewport be updated and rendered.
             */
            void refresh() ;

            /**
             * @brief   Save a screenshot of the current window content.
             * @param   path    Path to the file to save.
             */
            void saveScreenshot(const std::string& path) ;


        protected:
            /**
             * @brief   Perform some stuff before refreshing the AbstractWindow.
             */
            virtual void preRefresh() = 0 ;

            /**
             * @brief   Perform some stuff after refreshing the AbstractWindow.
             */
            virtual void postRefresh() = 0 ;


                                                     /*** SETTERS / GETTERS ***/
            /**
             * @brief   Set the viewport of the AbstractWindow.
             * @param   viewport    Viewport used by the window to display its
             *                      content.
             */
            void setViewport(const AbstractViewport* viewport) ;

            /**
             * @brief   Get the viewport of the AbstractWindow.
             * @return  AbstractWindow of the AbstractWindow.
             */
            AbstractViewport* getViewport() const ;


        public:
            /**
             * @brief   Get the width of the window.
             * @return  The width of the window in pixels.
             */
            virtual unsigned int getWidth() = 0 ;

            /**
             * @brief   Get the height of the window.
             * @return  The height of the window in pixels.
             */
            virtual unsigned int getHeight() = 0 ;
    } ;

} ;

#endif
