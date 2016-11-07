#include "Limb.h"

#include <stdlib.h>

using namespace std ;

Limb::Limb() : m_health(100), m_state(Limb::STATE_OK) {
    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << " CREATION" ;
        LogGen::print() ;
    #endif
}

Limb::~Limb() {
    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << " DESTRUCTION" ;
        LogGen::print() ;
    #endif
}

void Limb::damage(unsigned char points) {
    invariant() ;

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << "Limb damage BEFORE: "
                         << " [state = " << m_state
                         << " | health = " << (int) m_health << "]" ;
        LogGen::print() ;
    #endif


    if (points >= m_health)
        m_health = 0 ;
    else
        m_health = m_health - points ;

    if ((rand() % 2) == 1)
        testStateAfterDamage(Limb::STATE_FRACTURED) ;
    else
        testStateAfterDamage(Limb::STATE_BLOWNOFF) ;

    // The more the limb is damaged, the more the chance its state changes increases
    if ((rand() % 100) > m_health) {
        if ((rand() % 2) == 1) m_state = Limb::STATE_FRACTURED ;
        else m_state = Limb::STATE_BLOWNOFF ;
    }


    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << "Limb damage AFTER : "
                         << " [state = " << m_state
                         << " | health = " << (int) m_health << "]" ;
        LogGen::print() ;
    #endif

    invariant() ;
}

void Limb::damage(unsigned char points, Limb::STATE type) {
    invariant() ;
    assert(type != Limb::STATE_OK) ;
    assert(type != Limb::STATE_TREATED) ;

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << "Limb damage BEFORE: "
                         << " [state = " << m_state
                         << " | health = " << (int) m_health << "]" ;
        LogGen::print() ;
    #endif


    if (points >= m_health)
        m_health = 0 ;
    else
        m_health = m_health - points ;

    testStateAfterDamage(type) ;


    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << "Limb damage AFTER : "
                         << " [state = " << m_state
                         << " | health = " << (int) m_health << "]" ;
        LogGen::print() ;
    #endif

    invariant() ;
}

void Limb::heal(unsigned char points, bool fractured_only) {
    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << "Limb try healing... Fractured only ? "
                         << fractured_only ;
        LogGen::print() ;
    #endif

    if (!fractured_only || (m_state == Limb::STATE_FRACTURED && fractured_only)) {
        invariant() ;

        #ifdef DEBUG_MODE
            LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                             << "Limb healing BEFORE: "
                             << " [state = " << m_state
                             << " | health = " << (int) m_health << "]" ;
            LogGen::print() ;
        #endif

        m_health = m_health + points ;
        if (m_health > 100) m_health = 100 ;
        m_state = Limb::STATE_OK ;

        #ifdef DEBUG_MODE
            LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                             << "Limb healing AFTER: "
                             << " [state = " << m_state
                             << " | health = " << (int) m_health << "]" ;
            LogGen::print() ;
        #endif

        invariant() ;
    }
}
