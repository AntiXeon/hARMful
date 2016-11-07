#include "Character.h"

using namespace std ;

set<Character*> Character::AllCharacters ;

Character::Character() {
	/* IMPORTANT: Artificial intelligence, physique and action memory are to be
	   set in the subclasses (Humanoid, etc). Not in this one because AI depends
	   on the physique. Physique depends on the type of character!
   	 */

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << getName() << " added to AllCharacters list! " ;
        LogGen::print() ;
    #endif

    unsigned int size = AllCharacters.size() ;
	AllCharacters.insert(this) ;
	assert(AllCharacters.size() == (size + 1)) ;


	m_actionGauge = new GaugeTimer(Character::MAX_ACTION_GAUGE) ;

	/* Fill the gauge action with a random value to make the characters being
	   desynchronized */
	m_actionGauge -> isReady(rand() % Character::MAX_ACTION_GAUGE) ;
}

Character::~Character() {
    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << getName() << " removed to AllCharacters list! " ;
        LogGen::print() ;
    #endif

    // Tell the other characters that this one is really dead (avoid segfault)...
    ArtificialIntelligence* other ;
    for(auto& character : AllCharacters) {
        other = character -> m_ai ;
        other -> checkLastEnemy(m_ai) ;
    }

    unsigned int size = AllCharacters.size() ;
	AllCharacters.erase(this) ;
	assert(AllCharacters.size() == (size - 1)) ;
}
