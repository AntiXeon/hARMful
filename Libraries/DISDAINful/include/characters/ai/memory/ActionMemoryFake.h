#ifndef __ACTIONMEMORYFAKE_H__
#define __ACTIONMEMORYFAKE_H__

    #ifdef DEBUG_MODE
        #include "../../../utils/LogGen.h"
    #endif

#include "ActionMemory.h"

#include <stdlib.h>

/**
 * @brief Action memory that does not "say the truth" about the most used action.
 * @see ArtificialIntelligence
 * @version 1.0 01/05/2013
 */
class ActionMemoryFake : public ActionMemory {
    public:
                                                            /** CONSTRUCTORS **/
        /**
         * @brief Creation of an ActionMemory object.
         * @brief init  Type of initialization for the action memory.
         */
        ActionMemoryFake(ActionMemory::INITIALIZE init) ;

        /** @brief Destruction of an ActionMemory object. */
        virtual ~ActionMemoryFake() ;

    protected:
        /**
         * @brief In this class, the most performed action is randomly
         * determined. The goal of this class is to tell lies about the most
         * performed action!
         */
        inline virtual void testMostPerformedAction() {
            unsigned char random = rand() % 4 ;
            switch(random) {
                case 0:
                    m_most_used = ActionMemory::ACTION_NONE ;
                    break ;
                case 1:
                    m_most_used = ActionMemory::ACTION_PHYSICAL ;
                    break ;
                case 2:
                    m_most_used = ActionMemory::ACTION_MAGICAL ;
                    break ;
                case 3:
                    m_most_used = ActionMemory::ACTION_HEALING ;
                    break ;
            }
        }
} ;

#endif
