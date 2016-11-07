#include "Magic.h"

using namespace std ;

Magic::Magic(const string& name,
			 const string& desc,
			 unsigned short damages,
			 unsigned short variance,
			 unsigned short mp_used,
			 MagicElement* el) : m_name(name),
			 					 m_desc(desc),
				 			     m_damages(damages),
				 			     m_variance(variance/2),
				 			     m_mp_used(mp_used) {
	m_element = el ;
}

Magic::~Magic() {}
