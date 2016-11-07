#ifndef __HARMFUL_H__
#define __HARMFUL_H__

    #ifdef DEBUG_MODE
        #include "utils/LogGen.h"
    #endif

#include "pattern/NoCopy.h"

#include "AllMagic.h"
#include "AllPotions.h"
#include "AllWeapons.h"

/**
 * @brief The hARMful class is a singleton that generates the main singletons
 *        used to allow users of the library to add their own magic, items, etc.
 * @version 1.0 03/05/2013      New singleton management to store the game data
 *                              into the game code itself, not in the library.
 */
class hARMful : private NoCopy {
    private:
        /* ** DATA ** */
		/** @brief Unique instance of the singleton.
		 *         Autocreate the singleton before the main function.
		 */
		static hARMful Singleton ;

        /* ** FUNCTIONS ** */
        /** @brief Private constructor to avoid new instances. */
		hARMful() throw() ;
		
		/** @brief Destructor to delete dynamic instances. */
		~hARMful() throw() ;
} ;

#endif
