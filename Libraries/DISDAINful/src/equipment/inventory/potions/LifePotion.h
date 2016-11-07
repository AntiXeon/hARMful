#ifndef __LIFEPOTION_H__
#define __LIFEPOTION_H__

    #ifdef DEBUG_MODE
        #include "../../../utils/LogGen.h"
    #endif

#include "Potion.h"

/**
 * @brief A life potion is made to give life points. It has another effect on
 *        limbs to heal more precisely the characters.
 */
class LifePotion : public Potion {
    public:
        /**
         * @brief Power of the potion on limbs.
         *          - LOW:      the potion only stops bleedings.
         *          - MEDIUM:   the potion stops bleeding and heal broken limbs.
         *          - HIGH:     the potion heals blowned off limbs too.
         */
        enum POWER_LIMBS {POWER_LOW = 10, POWER_MEDIUM, POWER_HIGH} ;


    private:
        /** @brief Power of the potion. */
        POWER_LIMBS m_power ;


    public:
                                                            /** CONSTRUCTORS **/
        /**
         * @brief Creation of a life potion.
         * @param name      Name of the potion.
         * @param desc      Description of the potion.
         */
        LifePotion(const std::string& name, const std::string& desc, POWER_LIMBS power) ;

        /** @brief Destruction of a life potion. */
        virtual ~LifePotion() ;

                                                                 /** GETTERS **/
        /**
         * @brief Get the power of the potion.
         * @return Power of the potion on limbs.
         * @see POWER_LIMBS
         */
        inline POWER_LIMBS getPower() {
            return m_power ;
        }
} ;

#endif
