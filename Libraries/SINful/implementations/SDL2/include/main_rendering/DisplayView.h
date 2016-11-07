#ifndef __SIN_SDL2_DISPLAY_VIEW__
#define __SIN_SDL2_DISPLAY_VIEW__


#include <main_rendering/AbstractDisplayView.h>
#include <ApplicationContext.h>
#include <SDL2/SDL.h>


namespace Sin {

    /**
     * @brief   Class for defining the screens of the application with SDL2
     *          library.
     * @author  CB (c) 2016
     * @version 0.1     2016/02/29
     */
    class DisplayView : public AbstractDisplayView {
        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Create a new DisplayView.
             * @param   context     Context of the application.
             * @param   camera      Camera used to render the current screen
             *                      content.
             */
            DisplayView(
                        ApplicationContext* context,
                        Camera* camera = NULL
                       ) ;

            /**
             * @brief   Destruction of the DisplayView.
             */
            virtual ~DisplayView() ;


                                                             /*** UTILITIES ***/
            /**
             * @brief   Load the AbstractDisplayView data and related
             *          resources.
             * @warning Several views can share the same resources. In such
             *          case, resources are only loaded once.
             */
            void load(const std::string& path) ;

            /**
             * @brief   Unload the direct data of the AbstractDisplayView
             *          (but not resources).
             */
            void unload() ;
    } ;

} ;


#endif
