#include "AmmoStock.h"

using namespace std ;

AmmoStock::AmmoStock() {}

AmmoStock::~AmmoStock() {}


void AmmoStock::add(Firearm* ammo, unsigned short quantity) {
    assert(ammo != 0) ;

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << " add some ammo for "
                         << (ammo -> getName())
                         << " x" << (int) quantity ;
        LogGen::print() ;
    #endif

    if (m_ammo.count(ammo) > 0)   // L'arme existe, augmenter les quantites
        m_ammo[ammo] += quantity ;
    else                             // Sinon inserer une nouvelle entree
        m_ammo.insert(pair<Firearm*, unsigned short> (ammo, quantity)) ;
}

unsigned short AmmoStock::use(Firearm* a, unsigned short quantity) {
    assert(a != 0) ;

    unsigned short ret ;
    if (m_ammo.count(a) > 0) {
        if (m_ammo[a] > quantity) {     // Il y a assez d'objet pour l'action
            m_ammo[a] -= quantity ;
            ret = quantity ;
        }
        else {                          // Si pas assez, prendre tout les restes
            ret = m_ammo[a] ;
            m_ammo[a] = 0 ;
        }
    }
    else                                // Si l'objet n'est pas stocke, ne peut
        ret = 0 ;                       // etre utilise (quantite nulle)

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << " use some ammo for "
                         << (a -> getName())
                         << " x" << (int) quantity ;
        LogGen::print() ;
    #endif

    return ret ;
}
