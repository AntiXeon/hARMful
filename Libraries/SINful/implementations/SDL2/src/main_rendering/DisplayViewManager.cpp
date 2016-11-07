#include <main_rendering/DisplayViewManager.h>


namespace Sin {
                                              /** CONSTRUCTION / DESTRUCTION **/
    DisplayViewManager::DisplayViewManager(ApplicationContext* context)
        : AbstractDisplayViewManager(context) {}

    DisplayViewManager::~DisplayViewManager() {}


                                                             /*** UTILITIES ***/
    unsigned int DisplayViewManager::addView(const std::string& path) {
        ApplicationContext* context = (ApplicationContext*) getApplicationContext() ;
        DisplayView* view = new DisplayView(context) ;
        view -> load(path) ;

        unsigned int viewID = storeView(view) ;
        return viewID ;
    }

}
