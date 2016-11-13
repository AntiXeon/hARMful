/**
 * Singleton.hpp
 * GNU GENERAL PUBLIC LICENSE, Version 3, 29 June 2007
 *
 * @Author:      Denis CARLUS
 * @Created on:  13-Nov-2016
 * @Last change: 13-Nov-2016
 */

#ifndef __DOOM__SINGLETON__
#define __DOOM__SINGLETON__

namespace Doom {
    /**
     * Class to create singletons.
     * @warning     No copy into the subclasses.
     * @warning     Private inheritage required.
     */
    class Singleton {
        private:

            /**
             * @brief   Disable copy constructor.
             */
            Singleton(Singleton&);

            /**
             * @brief   Disable affectation.
             */
            void operator = (const Singleton &);

        protected:

            /**
             * @brief   Allowed default constructor, only for subclasses.
             */
            Singleton() throw();

            /**
             * @brief   Destruction, only for subclasses.
             */
            virtual ~Singleton() throw();
    };
};

#endif /* ifndef __DOOM__SINGLETON__ */
