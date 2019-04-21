#ifndef __HOPE__IRENDERABLE__
#define __HOPE__IRENDERABLE__

namespace Hope {
    /**
     * Interface for all classes that can draw objects on screen.
     */
    class IRenderable {
        public:
            /**
             * Render the object on screen.
             */
            virtual void render() const = 0 ;
    } ;
}

#endif
