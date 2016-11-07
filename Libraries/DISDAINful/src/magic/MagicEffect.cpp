#include "MagicEffect.h"

using namespace std ;

/* ** CONSTRUCTEURS ** */
MagicEffect::MagicEffect(MagicEffect::TYPES type,
                         const string& name,
                         const string& desc,
                         const string& applied,
				 		 unsigned char last,
				 		 bool repeat,
				 		 bool percent) {
    m_type = type ;
    m_name = name ;
    m_desc = desc ;
    m_applied = applied ;
    m_last = last ;
    m_repeat = repeat ;
    m_percent = percent ;

    m_switchState[0] = MagicEffect::STATE_NONE ;   // silence
    m_switchState[1] = MagicEffect::STATE_NONE ;   // immobile
    m_switchState[2] = MagicEffect::STATE_NONE ;   // paralysed

    m_bonusMalus[0]  = 0 ;       // hp
    m_bonusMalus[1]  = 0 ;       // mp
    m_bonusMalus[2]  = 0 ;       // hpmax
    m_bonusMalus[3]  = 0 ;       // mpmax
    m_bonusMalus[4]  = 0 ;       // str
    m_bonusMalus[5]  = 0 ;       // def
    m_bonusMalus[6]  = 0 ;       // mag
    m_bonusMalus[7]  = 0 ;       // psy
    m_bonusMalus[8]  = 0 ;       // vel
    m_bonusMalus[9]  = 0 ;       // lck
    m_bonusMalus[10] = 0 ;       // prc
}

MagicEffect::~MagicEffect() {}


