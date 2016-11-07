#include <main_rendering/DisplayView.h>


namespace Sin {
                                              /** CONSTRUCTION / DESTRUCTION **/
    DisplayView::DisplayView(
                             ApplicationContext* context,
                             Camera* camera
                            ) : AbstractDisplayView(context, camera) {}

    DisplayView::~DisplayView() {}


                                                             /*** UTILITIES ***/
    void DisplayView::load(const std::string&) {
        // @TODO: once the structure of view file is defined...
        // @TODO: might be put as a parser got from SPITE.
        // @TODO: might be placed in "common".
    }

    void DisplayView::unload() {
        // @TODO: once the structure of views file is defined...
        // @TODO: might be put as a parser got from SPITE.
        // @TODO: might be placed in "common".
    }

} ;
