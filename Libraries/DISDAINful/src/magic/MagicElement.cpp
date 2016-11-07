#include "MagicElement.h"

using namespace std ;

bool MagicElement::AllowCreation = true ;
unsigned char MagicElement::CurrentID = 0 ;

/* ** CONSTRUCTEURS ET MODIFIEURS ** */
MagicElement::MagicElement(const string& name) {
    assert(AllowCreation) ;

	m_name = name ;
	m_id = MagicElement::CurrentID ;

    // Increase the ID of the element for the next one (the ID is unique)
	MagicElement::CurrentID++ ;
}

MagicElement::~MagicElement() {}
