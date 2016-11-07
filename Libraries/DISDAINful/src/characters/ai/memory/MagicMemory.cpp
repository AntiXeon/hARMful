#include "MagicMemory.h"

using namespace std ;

MagicMemory::MagicMemory() {
    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << " CREATION" ;
        LogGen::print() ;
    #endif

    m_lastMagicUsed = 0 ;
}

MagicMemory::~MagicMemory() {
    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << " DESTRUCTION" ;
        LogGen::print() ;
    #endif
}

                                                      /** BLACK MAGIC SPELLS **/
void MagicMemory::learnBlackMagic(const string& magic) {
	BlackMagic* search = (BlackMagic*) AllMagic::getBlackMagic(magic) ;

	if (search != 0)
		learnBlackMagic(search) ;
}

void MagicMemory::forgetBlackMagic(BlackMagic* const magic) {
    bool found = false ;
    unsigned short pos ;
    unsigned short max = m_black_magic.size() ;

    for (pos = 0 ; pos < max && !found ; pos++) {
        if (m_black_magic[pos] == magic)
            found = true ;
    }

    if (found) {
        assert(pos < max) ;
        m_black_magic.erase(m_black_magic.begin() + pos) ;
    }
}

void MagicMemory::forgetBlackMagic(const string& magic) {
	BlackMagic* search = (BlackMagic*) AllMagic::getBlackMagic(magic) ;

	if (search != 0)
		forgetBlackMagic(search) ;
}

bool MagicMemory::hasMagic(BlackMagic* magic) {
    unsigned short max = m_black_magic.size() ;
    for (unsigned short i = 0 ; i < max ; i++)
		if (m_black_magic[i] == magic)
			return true ;
	return false ;
}


                                                      /** WHITE MAGIC SPELLS **/
void MagicMemory::learnWhiteMagic(const string& magic) {
	WhiteMagic* search = (WhiteMagic*) AllMagic::getWhiteMagic(magic) ;
		
	if (search != 0)
		learnWhiteMagic(search) ;
}

void MagicMemory::forgetWhiteMagic(WhiteMagic* const magic) {
    bool found = false ;
    unsigned short pos ;
    unsigned short max = m_white_magic.size() ;

    for (pos = 0 ; pos < max && !found ; pos++) {
        if (m_white_magic[pos] == magic)
            found = true ;
    }

    if (found) {
        assert(pos < max) ;
        m_white_magic.erase(m_white_magic.begin() + pos) ;
    }
}

void MagicMemory::forgetWhiteMagic(const string& magic) {
	WhiteMagic* search = (WhiteMagic*) AllMagic::getWhiteMagic(magic) ;

	if (search != 0)
		forgetWhiteMagic(search) ;
}

bool MagicMemory::hasMagic(WhiteMagic* magic) {
    unsigned short max = m_white_magic.size() ;
	for (unsigned short i = 0 ; i < max ; i++)
		if (m_white_magic[i] == magic)
			return true ;
	return false ;
}
