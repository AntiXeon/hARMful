#include "AllMagic.h"

using namespace std ;

AllMagic* AllMagic::Singleton = 0 ;
bool AllMagic::Loaded = false ;

unordered_map<string, BlackMagic*> AllMagic::BlackMagicList ;
unordered_map<string, WhiteMagic*> AllMagic::WhiteMagicList ;
unordered_map<string, MagicEffect*> AllMagic::MagicEffects ;
unordered_map<string, MagicElement*> AllMagic::MagicElements ;
AllMagic::ELEMENT_EFFICACITY** AllMagic::ELEMENTS_FORCE = 0 ;


AllMagic::AllMagic() throw() {
    #ifdef DEBUG_MODE
        LogGen::print("Magic singleton creation") ;
    #endif

    AllMagic::Loaded = true ;
}

AllMagic::~AllMagic() throw() {
    #ifdef DEBUG_MODE
        LogGen::print("Magic singleton destruction") ;
    #endif

    AllMagic::Loaded = false ;

    // Delete the singleton
    if (!AllMagic::Singleton == 0)
        delete AllMagic::Singleton ;

    // The singleton is responsible of the creation of new Elements
    for (auto& element : AllMagic::MagicElements)
        delete (&element) ;
    AllMagic::MagicElements.clear() ;

    // Delete the element efficacities too
    if (AllMagic::ELEMENTS_FORCE != 0) {
    	delete[] AllMagic::ELEMENTS_FORCE[0] ;
	    delete[] AllMagic::ELEMENTS_FORCE ;
    }
}


void AllMagic::createMatrixElementsEfficacity() {
    assert(AllMagic::ELEMENTS_FORCE == 0) ;

    unsigned char size = AllMagic::MagicElements.size() ;
    unsigned short sizeSquared = size * size ;

    // Create the 2D matrix dynamically
    AllMagic::ELEMENTS_FORCE = new AllMagic::ELEMENT_EFFICACITY*[size] ;
    // It uses a 1D array for better performances
    AllMagic::ELEMENT_EFFICACITY* dim_2 = new AllMagic::ELEMENT_EFFICACITY[sizeSquared] ;

    // Fill the matrix with the default value
    for (unsigned short i = 0 ; i < sizeSquared ; i++) 
        dim_2[i] = AllMagic::ELEFF_EFF ;

    // Generate the 2D matrix from the 1D array
    for (unsigned char i = 0 ; i < size ; i++)
		AllMagic::ELEMENTS_FORCE[i] = &dim_2[i * size] ;

    // Avoid the creation of new elements
    MagicElement::stopCreation() ;
}
