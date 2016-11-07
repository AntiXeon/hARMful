#include "LifePotion.h"

using namespace std ;

LifePotion::LifePotion(const std::string& name,
                       const std::string& desc,
                       POWER_LIMBS power) : Potion(name, desc, Potion::TYPE_LIFE) {
    m_power = power ;
}

LifePotion::~LifePotion() {}
