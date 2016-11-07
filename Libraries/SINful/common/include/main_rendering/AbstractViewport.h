#ifndef __SIN_ABSTRACT_VIEWPORT__
#define __SIN_ABSTRACT_VIEWPORT__


#include <string>
#include <AbstractApplicationContext.h>
#include <main_rendering/AbstractDisplayViewManager.h>


namespace Sin {

    /**
     * @brief   A viewport is used to render the content of a window.
     * @author  CB (c) 2016
     * @version 0.1     2016/02/07
     */
    class AbstractViewport {
        private:
            /**
             * @brief   Context of the application.
             */
            AbstractApplicationContext* m_context ;

            /**
             * @brief   Manager of views (screens) that can be displayed into
             *          the viewport.
             */
            AbstractDisplayViewManager* m_viewManager ;


        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Creation of an AbstractViewport.
             * @param   context     Context of the application.
             * @param   viewManager The view manager used to display the
             *                      different screens of the application.
             */
            AbstractViewport(
                             AbstractApplicationContext* context,
                             AbstractDisplayViewManager* viewManager
                            ) ;

            /**
             * @brief   Destruction of the AbstractViewport.
             * @warning The AbstractViewport destroys itself both
             *          AbstractApplicationContext and
             *          AbstractDisplayViewManager objects.
             */
            virtual ~AbstractViewport() ;


                                                             /*** UTILITIES ***/
            /**
             * @brief   Render the content of the AbstractViewport.
             */
            void render() ;

            /**
             * @brief   Display the content of the AbstractViewport.
             */
            virtual void display() = 0 ;

            /**
             * @brief   Save a picture of the AbstractViewport on disk.
             * @param   path    Path to the file to save.
             */
            virtual void save(const std::string& path) = 0 ;

            /**
             * @brief   Clear the content of the AbstractViewport.
             */
            virtual void clear() = 0 ;


                                                     /*** SETTERS / GETTERS ***/
            /**
             * @brief   Get the AbstractDisplayViewManager of the current
             *          AbstractViewport.
             */
            AbstractDisplayViewManager* getDisplayViewManager() const ;
    } ;

} ;


#endif
