#ifndef _DOOMFUL_ICONTROLLER_
#define _DOOMFUL_ICONTROLLER_


namespace MVC {

    /**
     * @brief   An IController manages an IModel.
     *          While the IModel handles only its own data, with a lot of
     *          operations on it as inner calculations, the IController makes
     *          the IModel be updated at the right moment with the right data.
     *          It also provides right data to the IView from IModel at the
     *          right moment.
     *
     *          It may ask the IView to update itself too.
     *
     *          It is then an important bridge between the IView and the IModel.
     */
    class IController {
        protected:
            /**
             * @brief   Get the underlying model of the IController.
             */
            virtual IModel* getModel() const = 0 ;

            /**
             * @brief   Get the underlying view of the IController.
             */
            virtual IView* getView() const = 0 ;
    } ;

} ;


#endif