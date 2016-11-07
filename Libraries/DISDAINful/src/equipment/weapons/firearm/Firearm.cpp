#include "Firearm.h"

#include <assert.h>

using namespace std ;

Firearm::Firearm(const string& name,
 			     const string& desc,
 		         unsigned short damageShoot,
  		         unsigned short damageStock,
		         unsigned char variance,
		         unsigned char hardness,
		         unsigned char percentHardness,
		         unsigned short distanceShoot,
		         unsigned char ammoMax,
		         unsigned char ammoUsed,
		         MagicElement* el,
		         bool twoHands) : Weapon(name,
             			 				 desc,
                                         damageShoot,
                                         damageStock,
                                         variance,
                                         hardness,
                                         percentHardness,
                                         Weapon::TYPE_FIREARM,
                                         Weapon::EFFECT_RANDOM,
                                         el,
                                         twoHands) {
    assert(distanceShoot > 0) ;
    assert(ammoMax > 0) ;
    assert(ammoUsed > 0) ;

    m_distanceShoot = distanceShoot ;
    m_ammoMax = ammoMax ;
    m_ammoUsed = ammoUsed ;
}
