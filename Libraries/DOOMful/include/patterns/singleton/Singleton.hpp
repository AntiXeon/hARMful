#ifndef __DOOM__SINGLETON__
#define __DOOM__SINGLETON__

#include <utils/Platform.hpp>

namespace Doom {
    /**
     * Class to create singletons.
     * @warning     No copy into the subclasses.
     * @warning     Private inheritage required.
     */
    class exported Singleton {
        private:

            /**
             * Disable copy constructor.
             */
            Singleton(Singleton&) ;

            /**
             * Disable affectation.
             */
            void operator= (const Singleton &) {}

        protected:

            /**
             * Allowed default constructor, only for subclasses.
             */
            Singleton() noexcept ;

            /**
             * Destruction, only for subclasses.
             */
            virtual ~Singleton() noexcept ;
    };
};

#endif
