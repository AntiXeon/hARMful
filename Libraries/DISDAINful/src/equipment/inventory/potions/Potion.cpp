#include "Potion.h"

using namespace std ;

Potion::Potion(const string& name,
               const string& desc,
               Potion::TYPE type) : Item(name, desc, Item::TYPE_POTION) {
    m_type = type ;

    m_points[0] = 0 ;
    m_points[1] = 0 ;
    m_bonus[0]  = 0 ;
    m_bonus[1]  = 0 ;
    m_bonus[2]  = 0 ;
    m_bonus[3]  = 0 ;
    m_bonus[4]  = 0 ;
    m_bonus[5]  = 0 ;
    m_bonus[6]  = 0 ;
    m_bonus[7]  = 0 ;
    m_bonus[8]  = 0 ;
}

Potion::~Potion() {}

void Potion::addClearEffect(MagicEffect* effect) {
    bool inside = false ;
    unsigned short max = m_clear_effect.size() ;

    // Verifier que l'effet n'est pas deja dans la liste...
    for (unsigned short i = 0 ; i < max && inside == false ; i++)
        if (m_clear_effect[i] == effect)
	        inside = true ;

    if (!inside)
        m_clear_effect.push_back(effect) ;
}
