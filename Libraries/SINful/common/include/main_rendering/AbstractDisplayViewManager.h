#ifndef __SIN_ABSTRACT_DISPLAY_VIEW_MANAGER__
#define __SIN_ABSTRACT_DISPLAY_VIEW_MANAGER__


#include <stack>
#include <vector>
#include <AbstractApplicationContext.h>
#include <main_rendering/AbstractDisplayView.h>


namespace Sin {

    /**
     * @brief   Stack screens to save the previous opened screens, letting them
     *          be in pause without update if they are not active. Only one
     *          screen can be active at a time.
     * @author  CB (c) 2016
     * @version 0.1     2016/02/08
     */
    class AbstractDisplayViewManager {
        private:
            /**
             * @brief   Context of the application.
             */
            AbstractApplicationContext* m_context ;

            /**
             * @brief   List of all available screens in the
             *          AbstractDisplayViewManager.
             */
            std::vector<AbstractDisplayView*> m_viewsList ;

            /**
             * @brief   Stack of AbstractDisplayView to keep memory of opened
             *          screens and their order to come back to previous ones.
             */
            std::stack<AbstractDisplayView*> m_viewsStack ;


        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Creation of a new AbstractDisplayViewManager.
             * @param   context Context of the application.
             */
            AbstractDisplayViewManager(AbstractApplicationContext* context) ;

            /**
             * @brief   Destruction of the AbstractDisplayViewManager.
             */
            virtual ~AbstractDisplayViewManager() ;


                                                             /*** UTILITIES ***/
            /**
             * @brief   Add a screen from its file path. This loads the screen
             *          configuration and store it in the list of screens.
             * @param   path    Path to the screen configuration file to load.
             * @return  ID of the loaded view, on success. If loading fails, -1
             *          is then returned.
             */
            virtual unsigned int addView(const std::string& path) = 0 ;

            /**
             * @brief   Remove a screen and its resources from the
             *          AbstractDisplayViewManager. Removing the last screen
             *          frees all in use resources.
             * @param   id  ID of the screen to remove.
             * @warning Be sure the view is not in use when calling this method.
             */
            void removeView(const unsigned int& id) ;

            /**
             * @brief   Remove all screens from the AbstractDisplayViewManager.
             *          This removes all resources used by the application.
             */
            void removeAllViews() ;


            /**
             * @brief   Push a screen on top of the stack, making it the active
             *          screen (the only one to be shown on screen and updated).
             * @param   id  ID of the screen to push.
             */
            void pushView(const unsigned int& id) ;

            /**
             * @brief   Pop the top screen, making the previous being active.
             */
            void popView() ;

        private:
            /**
             * @brief   Free currently loaded resources in the application.
             */
            void freeResources() ;


        protected:
            /**
             * @brief   Store a view in the list of AbstractDisplayView.
             * @param   view    The view to store.
             */
            unsigned int storeView(AbstractDisplayView* view) ;

                                                     /*** SETTERS / GETTERS ***/
            /**
             * @brief   Get the context of the application.
             * @return  The context of the application.
             */
            AbstractApplicationContext* getApplicationContext() const ;


        public:
            /**
             * @brief   Get the current active screen.
             */
            AbstractDisplayView* getCurrentView() ;
    } ;

} ;

#endif
