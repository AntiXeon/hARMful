#ifndef _DOOMFUL_IVIEW_
#define _DOOMFUL_IVIEW_


namespace MVC {

    /**
     * @brief   An IView is used to display elements to user.
     */
    class IView {
        public:
            /**
             * @brief   Update of the view.
             */
            virtual void update() = 0 ;

            /**
             * @brief   Make a render of the view.
             */
            virtual void render() = 0 ;
    } ;

} ;


#endif