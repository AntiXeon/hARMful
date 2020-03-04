#ifndef __HOPE__IRENDERABLE__
#define __HOPE__IRENDERABLE__

#include <utils/Platform.hpp>

namespace Hope {
    /**
     * Interface for all classes that can draw objects on screen.
     */
    class IRenderable {
        public:
            /**
             * Render the object on screen.
             */
            exported virtual void render() const = 0 ;
    } ;
}

#endif
