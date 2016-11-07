#ifndef __BODY_H__
#define __BODY_H__

    #ifdef DEBUG_MODE
        #include "../../utils/LogGen.h"
    #endif

#include "limb/Limb.h"
#include "limb/LimbHead.h"
#include "limb/LimbTrunk.h"

/**
 * @brief Representation of the characters body. This is the most basic one
 *        that can be derivated into more precise bodies to create all the
 *        kinds of bodies wanted (mammals, birds, fishes...).
 *        It fully allows dismemberment since its second version.
 * @see Character
 * @see Limb
 * @version 1.0 30/10/2012  Body is only made of varying numeric values
 *                          representing limbs.
 * @version 2.0 01/04/2013  Body is made of limbs.
 */
class Body {
    protected:
        /**
         * @brief Limb representing a head. Most of time, when this limb is
         *        "out of work", the character dies. It is said main head as a
         *        derivated body can embed several heads.
         */
        LimbHead* m_mainHead ;

        /**
         * @brief "Limb" linking all the other ones. It cannot be blown off and
         *        is pretty resistent to attacks. If fractured, the character
         *        dies slowly.
         */
        LimbTrunk* m_trunk ;

    public:
                                                            /** CONSTRUCTORS **/
        /** @brief Creation of a generic body. */
        Body() ;

        /** @brief Destruction of a body. */
        virtual ~Body() ;

                                                                 /** GETTERS **/
        /**
         * @brief Get the limb corresponding to the main head.
         * @return The main head.
         */
        inline LimbHead* getMainHead() {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << " get head: " << m_mainHead ;
                LogGen::print() ;
            #endif

            return m_mainHead ;
        }

        /**
         * @brief Get the limb corresponding to the main head.
         * @return The main head.
         */
        inline LimbTrunk* getTrunk() {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << " get trunk: " << m_trunk ;
                LogGen::print() ;
            #endif

            return m_trunk ;
        }

        /**
         * @brief To know if the body has at least a blown of limb.
         * @return TRUE if one or more limbs are blown off, FALSE if none.
         */
        virtual inline bool hasBlownOffLimb() {
            return ((m_mainHead -> isBlownOff()) || (m_trunk -> isBlownOff())) ;
        } ;

        /**
         * @brief Find the limb.
         * return The limb searched.
         */
         // @TODO use X Y Z to find limb matching coordinates
        virtual Limb* findLimb() = 0 ;
} ;

#endif
