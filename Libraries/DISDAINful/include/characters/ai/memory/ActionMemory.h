#ifndef __ACTIONMEMORY_H__
#define __ACTIONMEMORY_H__

    #ifdef DEBUG_MODE
        #include "../../../utils/LogGen.h"
    #endif

#include <climits>

/**
 * @brief The action memory is used to store all the performed actions by the
 *        character as numeric values.
 *        Inherit your own implementation of this class to improve the detection
 *        of the most used action.
 * @see ArtificialIntelligence
 * @version 1.0 06/04/2013
 */
class ActionMemory {
    public:
        enum INITIALIZE {
                         INIT_CLEAR = 0,
                         INIT_RANDOM_NONE,
                         INIT_RANDOM_PHYSICAL,
                         INIT_RANDOM_MAGIC,
                         INIT_RANDOM_HEALING,
                        } ;

        /**
	     * @brief Actions performed by the character (used to identify the most
	     *        used action by the character).
	     * NONE     No action is mainly performed by the character.
	     * PHYSICAL The character mostly uses physical attacks.
	     * MAGICAL  The character mostly uses magical attacks.
	     * HEALING  The character mostly uses healing actions.
	     */
        enum ACTION {
                        ACTION_NONE = 0,
                        ACTION_PHYSICAL,
                        ACTION_MAGICAL,
                        ACTION_HEALING
                     } ;

    protected:
        /** @brief Maximal value before values are reseted. */
        static const unsigned short MAX_ACTIONS = USHRT_MAX - 1 ;

        /** @brief A cache for fast return of the most used action. */
        ActionMemory::ACTION m_most_used ;
        /** @brief Counter from 0 to 256 hits to update the most used action. */
        unsigned char m_hits_before_update ;
        /** @brief A flag to retest the most used action. */
        bool m_need_update ;

        /** @brief Reset of the physical attacks counter. */
		unsigned short m_physical_reset ;
		/** @brief Amount of physical attacks performed by the character. */
		unsigned short m_physical_hits ;

        /** @brief Reset of the magical attacks counter. */
		unsigned short m_magical_reset ;
        /** @brief Amount of magical attacks performed by the character. */
		unsigned short m_magical_hits ;

        /** @brief Reset of the healing actions counter. */
		unsigned short m_healing_reset ;
        /** @brief Amount of healing actions performed by the character. */
		unsigned short m_healing_hits ;


        /** @brief Type of the last action made by the character. */
        ActionMemory::ACTION m_last_action ;

    public:
                                                            /** CONSTRUCTORS **/
        /**
         * @brief Creation of an ActionMemory object.
         * @brief init  Type of initialization for the action memory.
         */
        ActionMemory(ActionMemory::INITIALIZE init) ;

        /** @brief Destruction of an ActionMemory object. */
        virtual ~ActionMemory() ;
        
                                                                 /** SETTERS **/
        /**
         * @brief Define the last action made by the character.
         * @param last  The last action.
         */
        inline void setLastAction(ActionMemory::ACTION last) {
            m_last_action = last ;
        }

                                                                 /** GETTERS **/
        /**
         * @brief Define the last action made by the character.
         * @param last  The last action.
         */
        inline ActionMemory::ACTION getLastAction() {
            return m_last_action ;
        }

        /**
         * @brief Get the kind of action mostly performed by the character.
         *        It can be a lie!
         * @return The most performed action type.
         */
        inline ActionMemory::ACTION getMostPerformedAction() {
            if (m_need_update)
                testMostPerformedAction() ;
            return m_most_used ;
        }

        /**
         * @brief Get the total amount of physical hits performed.
         * @return Total amount of physical hits.
         */
        inline unsigned int getAllPhysical() {
            // multiply by 2^(number of bits to represent a short variable)
            return (m_physical_reset << sizeof(short)) + m_physical_hits ;
        }

        /**
         * @brief Get the total amount of magical hits performed.
         * @return Total amount of magical hits.
         */
        inline unsigned int getAllMagical() {
            // multiply by 2^(number of bits to represent a short variable)
            return (m_magical_reset << sizeof(short)) + m_magical_hits ;
        }

        /**
         * @brief Get the total amount of healing hits performed.
         * @return Total amount of healing hits.
         */
        inline unsigned int getAllHealing() {
            // multiply by 2^(number of bits to represent a short variable)
            return (m_healing_reset << sizeof(short)) + m_healing_hits ;
        }

                                                                 /** SETTERS **/
        /** @brief Increase the amount of physical attacks. */
        void increasePhysical() ;

        /** @brief Increase the amount of magical attacks. */
        void increaseMagical() ;

        /** @brief Increase the amount of healing actions. */
        void increaseHealing() ;

    protected:
        /**
         * @brief Heuristic to find the most performed action of the character.
         * @warning This is not an accurate method and is made to give fast
         *          result. This is an arbitrary implementation and can be
         *          implemented in a better way for more precise results.
         *          You can develop a probabilist version of this method or
         *          on the contrary disable this by returning a unique value.
         *          This is a property that can make the character "lie" about
         *          its own actions.
         *
         *          You cannot directly interact with it in your AI class, yet
         *          it has a great effect on the management of the AI and can
         *          thus be used to create new behaviors with existing AI.
         */
        virtual void testMostPerformedAction() ;

    private:
                                                         /** INITIALIZATIONS **/
        /** @brief Initialize a clear memory. */
        void initClear() ;

        /** @brief Initialize a memory for characters using no preferred actions. */
        void initForNone() ;

        /** @brief Initialize a memory for characters using physical actions. */
        void initForPhysical() ;

        /** @brief Initialize a memory for characters using magic actions. */
        void initForMagic() ;

        /** @brief Initialize a memory for characters using healing actions. */
        void initForHealing() ;
} ;

#endif
